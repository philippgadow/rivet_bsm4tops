/**
 * RESOLVED DIFF XS FOR PARTON LEVEL
 * Calculation of the resolved ttbar production differential cross-section @ 13 TeV (2015+2016) for parton level
 ***
 * Author: Francesco La Ruffa
 * francesco.la.ruffa@cern.ch
 * based on <ATLAS_<no assigned number yet>> 13 TeV
 **/


// -*- C++ -*
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/PromptFinalState.hh"
#include "Rivet/Projections/DressedLeptons.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Math/Math.hh"
#include "Rivet/Tools/Utils.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Projections/PartonicTops.hh"

#include "HepMC/PdfInfo.h"
#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/SimpleVector.h"
#include "HepMC/GenVertex.h"

namespace Rivet {
  class Resolved_partonic : public Analysis {
    public:

      /// Constructor
      Resolved_partonic()
        : Analysis("Resolved_partonic")
      {
        setNeedsCrossSection(true);
      }
  public:
      void init() {

        std::vector<double> pttop_bins={0.00,50.00,100.00,160.00,225.00,300.00,360.00,420.00,475.00,530.00,600.00,1000.00};
	_h["ptpseudotophadron_inc"]        = book("pttop",pttop_bins);
        std::vector<double> ptttbar_bins={0.00,40.00,90.00,150.00,230.00,310.00,390.00,470.00,550.00,630.00,800.00};
        _h["ptttbar_inc"]                  = book("ptttbar",ptttbar_bins);
        std::vector<double> ht_bins={0.00,90.00,170.00,260.00,360.00,470.00,580.00,710.00,830.00,970.00,1120.00,2000.00};
	_h["ht_inc"]                       = book("ht",ht_bins);
        std::vector<double> absPout_bins ={0.00,30.00,100.00,230.00,320.00,500.00};
        _h["absPout_inc"]                  = book("absPout",absPout_bins);
	_h["ptpseudotophadron_inc_norm"]        = book("pttop_norm",pttop_bins);
        _h["ptttbar_inc_norm"]                  = book("ptttbar_norm",ptttbar_bins);
	_h["ht_inc_norm"]                       = book("ht_norm",ht_bins);
        _h["absPout_inc_norm"]                  = book("absPout_norm",absPout_bins);

        declare(PartonicTops(), "Tops");
      }

      void analyze(const Event& event) {
	      double weight = event.weight();

        const Particles tops = apply<PartonicTops>(event, "Tops").tops();

        const Particles partontops = apply<ParticleFinder>(event, "Tops").particlesByPt();
        //if (partontops.size() != 2) vetoEvent;
        const Particle top= partontops[0];
        const Particle antitop= partontops[1];




        FourMomentum toplep;
      	FourMomentum tophad;

    bool isTopLep    = hasLeptonicDecay(top);
  	bool isAntiTopLep = hasLeptonicDecay(antitop);
  	if (isTopLep && !isAntiTopLep) {
  	  toplep = top.momentum();
  	  tophad = antitop.momentum();
  	}
    else if (isAntiTopLep && !isTopLep) {
  	  toplep = antitop.momentum();
  	  tophad = top.momentum();
  	}
    else vetoEvent;





  	  //std::cout<<"Top = "<<isTopLep<<" Antitop = "<<isAntiTopLep<<std::endl;

  	  FourMomentum ttbar = top.momentum() + antitop.momentum();
  	  Vector3 z_versor(0,0,1);
  	  Vector3 vtophad = tophad.vector3();
  	  Vector3 vtoplep = toplep.vector3();

  	  double ttbar_pt = ttbar.pt();

  	  double absPout = fabs(vtophad.dot((vtoplep.cross(z_versor))/(vtoplep.cross(z_versor).mod())));

  	  double HT = tophad.pt() + toplep.pt();



  	  // fill only the hadronically decay top quark
  	  

      _h["ptpseudotophadron_inc"]->fill(tophad.pt(), weight); //pT of pseudo top hadron
      _h["ptttbar_inc"]->fill(ttbar_pt, weight);
_h["ht_inc"]->fill(HT, weight);
      _h["absPout_inc"]->fill(absPout, weight);
      _h["ptpseudotophadron_inc_norm"]->fill(tophad.pt(), weight); //pT of pseudo top hadron
      _h["ptttbar_inc_norm"]->fill(ttbar_pt, weight);
_h["ht_inc_norm"]->fill(HT, weight);
      _h["absPout_inc_norm"]->fill(absPout, weight);




        bool debug=false;
        if(debug){
        std::cout << " DEBUG :: Pseudo Top -- "
                  << " pt top had :: > "<< tophad.pt()
                  << std::endl;
        std::cout << " DEBUG :: Pseudo Top -- "
                  << " pt top lep :: > "<< toplep.pt()
                  << std::endl;
        std::cout << " DEBUG :: ******************************************* " << std::endl;
         }

         //if(top) delete top;
         //if(antitop) delete antitop;

      }

      void finalize() {
        const double sf = (crossSection() / sumOfWeights());
        for (map<string, Histo1DPtr>::iterator hit = _h.begin(); hit != _h.end(); ++hit) {
          scale(hit->second, sf);
          // Normalized distributions
          if (hit->first.find("_norm") != string::npos)  normalize(hit->second);
        }
      }

    private:
      bool hasLeptonicDecay(Particle p)
      {
        bool islep = false;

        // find out the decay modes
        vector<Particle> childs = p.children();
        for (unsigned int i=0; i<childs.size(); i++)
  	if (childs[i].abspid() == 24) {
  	  vector<Particle> Wchilds = childs[i].children();
  	  while (Wchilds.size() == 1){
  	    Wchilds = Wchilds[0].children();
  	  }
  	  if (Wchilds[0].abspid() > 10)
  	    islep = true;
  	}
        return islep;
      }


      map<string, Histo1DPtr> _h;


  };

  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(Resolved_partonic);

}


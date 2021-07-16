mkdir -p data
cd data
rucio download --nrandom 1 "mc15_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.evgen.EVNT.e6337"
rucio download --nrandom 1 "mc15_13TeV.700122.Sh_2210_ttbar_SingleLeptonP_maxHTavrgTopPT_SSC.evgen.EVNT.e8253"
rucio download --nrandom 1 "mc15_13TeV.700123.Sh_2210_ttbar_SingleLeptonM_maxHTavrgTopPT_SSC.evgen.EVNT.e8253"
rucio download --nrandom 1 "mc15_13TeV.700124.Sh_2210_ttbar_dilepton_maxHTavrgTopPT_SSC.evgen.EVNT.e8253"

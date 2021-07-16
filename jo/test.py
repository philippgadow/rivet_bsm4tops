theApp.EvtMax = 500

import AthenaPoolCnvSvc.ReadAthenaPool
from os.path import join
svcMgr.EventSelector.InputCollections = [ join('..', 'data', 'dummy', 'mc16_13TeV.102000.EVNT.235547.pool.root') ]

from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

from Rivet_i.Rivet_iConf import Rivet_i
rivet = Rivet_i()
import os
rivet.AnalysisPath = os.environ['PWD']

rivet.Analyses += [ 'MC_JETS' ]
rivet.RunName = ''
rivet.HistoFile = 'MyOutput.yoda.gz'
rivet.CrossSection = 1.0
#rivet.IgnoreBeamCheck = True
#rivet.SkipWeights=True
job += rivet


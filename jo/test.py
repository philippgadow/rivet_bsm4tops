theApp.EvtMax = 500

import AthenaPoolCnvSvc.ReadAthenaPool
from os.path import join
input_file = join('..', 'data', 'mc15_13TeV.310846.MGPy8EG_4toprestt_auto_m1500.evgen.EVNT.e7058', 'EVNT.16103489._000009.pool.root.1')
svcMgr.EventSelector.InputCollections = [ input_file ]

from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

from Rivet_i.Rivet_iConf import Rivet_i
rivet = Rivet_i()
import os
rivet.AnalysisPath = join(os.environ['PWD'], '..', 'rivet')
rivet.Analyses += [ 'BSM4tops' ]
rivet.RunName = ''
rivet.HistoFile = 'MyOutput.yoda.gz'
rivet.CrossSection = 1.0
#rivet.IgnoreBeamCheck = True
#rivet.SkipWeights=True
job += rivet

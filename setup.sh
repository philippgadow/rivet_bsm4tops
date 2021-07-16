# see https://gitlab.cern.ch/atlas/athena/-/tree/21.6/Generators/Rivet_i

# set up release
setupATLAS
asetup 21.6.67,AthGeneration
source setupRivet.sh

# build rivet routine
cd rivet/
rivet-build RivetBSM4tops.so BSM4tops.cc
cd -

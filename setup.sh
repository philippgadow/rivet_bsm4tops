# see https://gitlab.cern.ch/atlas/athena/-/tree/21.6/Generators/Rivet_i

# set up release
setupATLAS
asetup 21.6.67,AthGeneration
source setupRivet.sh

# build rivet routine
cd rivet/
rivet-build RivetTTTT.so TTTT.cc
cd -

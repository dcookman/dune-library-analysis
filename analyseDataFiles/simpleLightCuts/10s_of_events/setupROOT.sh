# setupROOT.sh

#!/bin/bash
# this is a script file that sets up the SBND directories to enable larsoft to be run.

# to run this do: source setupROOT.sh

source /cvmfs/fermilab.opensciencegrid.org/products/larsoft/setups
setup root v6_04_02 -q e7:prof
# setup root -q e9:prof # comment out where appropriate

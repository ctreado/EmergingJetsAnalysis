# install script to build and install code the first time it's checked out

if ! type lsetup > /dev/null/; then
    setupATLAS
fi

if ! type rucio > /dev/null/; then
    lsetup rucio
fi

lsetup panda
#lsetup "root recommended"
lsetup git

asetup AnalysisBase,21.2.51
mkdir ../build/
mkdir ../run/
cd ../build/
cmake ../EmergingJetsAnalysis/
make
source x86*/setup.sh
cd ../

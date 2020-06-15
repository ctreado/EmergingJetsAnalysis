# install script to build and install code the first time it's checked out

echo ""
echo "#####################################################################"
echo "## installing EmergingJetsAnalyis package and setting up work area ##"
echo "#####################################################################"
echo ""

if ! type lsetup &> /dev/null; then
    setupATLAS
fi

if ! type rucio &> /dev/null; then
    lsetup rucio
fi

if ! type pbook &> /dev/null; then
    lsetup panda
fi

if ! [[ `root-config --version` == *"6."* ]]; then
    lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"
fi

function ver { printf "%03d%03d%03d%03d" $(echo "$1" | tr '.' ' '); }
GIT_VERSION=(`git --version`)
GIT_VERSION=${GIT_VERSION[2]}
if [ $(ver ${GIT_VERSION}) -lt $(ver 2.0.0) ]; then
    lsetup git
fi

ANALYSIS_BASE_VERSION=21.2.121
asetup AnalysisBase,${ANALYSIS_BASE_VERSION}

if [ ! -d ../build/ ]; then
    mkdir ../build/
fi

if [ ! -d ../run/ ]; then
    mkdir ../run/
fi

export EJ_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ../build/
cmake $EJ_PATH
make
source x86*/setup.sh
cd $EJ_PATH

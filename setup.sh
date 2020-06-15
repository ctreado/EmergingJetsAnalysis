# setup script to setup environment on subsequent runs

echo ""
echo "#####################################################################"
echo "## setting up environment for running EmergingJetsAnalysis package ##"
echo "#####################################################################"
echo ""

if ! type lsetup &> /dev/null; then
    setupATLAS
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

export EJ_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

asetup --restore
cd ../build/
source x86*/setup.sh
cd $EJ_PATH

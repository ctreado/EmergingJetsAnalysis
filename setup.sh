if ! type lsetup > /dev/null; then
    setupATLAS
fi

if ! type rucio > /dev/null; then
    lsetup rucio
fi

lsetup panda
#lsetup "root recommended"
lsetup git

asetup --restore
cd ../build/
source x86*/setup.sh
cd ../

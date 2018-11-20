# EmergingJetsAnalysis: EJs Analysis Framework

> last modified 20 November 2018 by colleen.jennifer.treado@cern.ch

Welcome to the event-loop analysis code framework for the Run 2 Emerging Jets
search.

Based on the ```xAODAnaHelpers``` framework...

Questions can be sent to **colleen.jennifer.treado@cern.ch** or
**j.beacham@cern.ch**.

For more information on xAODAnaHelpers, see the documentation here: https://xaodanahelpers.readthedocs.io/en/master/
For more information on using git or AnalysisBase, see the software
tutorials here: https://atlassoftwaredocs.web.cern.ch

## Installation and Setup:

For first-time setup and installation, clone the ```EmergingJetsAnalysis```
repository into a fresh work area:

```bash
# the '--recursive' option automatically unpacks the nested xAODAnaHelpers repo
# the https url is easiest for cloning on lxplus, but we can alternatively use the http or ssh url 
git clone --recursive https://:@gitlab.cern.ch:8443/EmergingJets/EmergingJetsAnalysis.git
```

Then cd into the repository and run the install script:

```bash
cd EmergingJetsAnalysis
source install.sh
```

This will setup ATLAS, rucio, panda, and git, setup the release
(AnalysisBase, 21.2.51), make 'build' and 'run' directories, compile
the package (```cmake ../EmergingJetsAnalysis; make```) and setup the
new environment (```source x86*/setup.sh```) from the build directory,
and return to the parent directory that houses the repository.

On subsequent logins, run the setup script to resetup ATLAS, rucio,
panda, and git, restore the release, and source your setup:

```bash
cd EmergingJets
source setup.sh
```


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

This will setup ATLAS, rucio, panda, root, and git, setup the release
(AnalysisBase, 21.2.51), make 'build' and 'run' directories if they
don't already exist, set the local path to the package repository, compile
the package (```cmake ../EmergingJetsAnalysis; make```), and setup the
new environment (```source x86*/setup.sh```).

On subsequent logins, run the setup script from the repository directory to restore the release and
re-setup the environment:

```bash
cd EmergingJetsAnalysis
source setup.sh
```

To re-compile after changes are made to the code:

```
cd build
cmake $EJ_PATH        # or "cmake ../EmergingJetsAnalysis"
make
source x86*/setup.sh
```

Note that "cmake ..." is only necessary when the package structure has been
changed or new packages have been added.


## Running the Job:

Jobs are run using the xAODAnaHelpers steering code,
```xAH_run.py```. The ```EJsAnalysis/scripts/submit_*.sh```
submission scripts provide examples for running jobs locally and on
the grid. The ```EJsAnalysis/scripts/samples.*.txt``` text files
provide lists of input samples for both data and MC.

# EmergingJetsAnalysis: EJs Analysis Framework

> last modified 4 December 2018 by colleen.jennifer.treado@cern.ch

Welcome to the event-loop analysis code framework for the Run 2 Emerging Jets
search.

Based on the `xAODAnaHelpers` framework, with some code
inspiration taken from the BLChargino, Xhh, and Xbb groups...

Questions can be sent to **colleen.jennifer.treado@cern.ch** or
**j.beacham@cern.ch**.

For more information on xAODAnaHelpers, see the documentation here:
https://xaodanahelpers.readthedocs.io/en/master/ .
For more information on using git or AnalysisBase, see the software
tutorials here: https://atlassoftwaredocs.web.cern.ch .


## Installation and Setup:

For first-time setup and installation, clone the `EmergingJetsAnalysis`
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
(AnalysisBase, 21.2.51), make 'build' and 'run' directories in the
repo's parent directory if they
don't already exist, set the local path to the repository, compile
the package(s) (`cmake ../EmergingJetsAnalysis; make`), and setup the
new environment (`source x86*/setup.sh`).

On subsequent logins, run the setup script from the repository directory to restore the release and
re-setup the environment:

```bash
cd EmergingJetsAnalysis
source setup.sh
```

To re-compile after changes are made to the code:

```bash
cd build        # assuming you're initially in the parent directory
cmake $EJ_PATH        # or "cmake ../EmergingJetsAnalysis"
make
source x86*/setup.sh
```

Note that "cmake ..." is only necessary when the package structure has been
changed or new packages have been added.


## Running the Job:

Jobs are run using the xAODAnaHelpers steering code,
`xAH_run.py`, with the following basic command:

```bash
xAH_run.py --files ... file [file ...]
	--config path/to/file.py
	[options]
	driver [driver options]
```

where `--files` is a list of input root files to run over,
`--config` is a configuration file for all algorithms to be run,
`driver` is the driver dictating where to run the code
(i.e. `direct` to run locally or `prun` to run on the grid), and
`[(driver) options]` are additional, not required, steering
options. Make sure you have a valid voms proxy set up
(`voms-proxy-init -voms atlas`) before attempting to run on the grid. 


### Ntuple-Making
The bulk of the analysis is performed in the ntuple-making step, which
runs over xAODs (or DxAODs), doing basic event selection,
object calibration/selection, and analysis selection, and producing an
EJsMiniNtuple output TTree (one for each systematic). A typical ntuple-making job should
configure and run the following set of algorithms:

* **BasicEventSelection** -- performs most basic event selection
  common to all analyses, including GRL selections, pileup
  reweighting, trigger selections, etc.
* **Object Calibrators** -- calibrates objects (jets) according to CP
  group recommendations
* **Object Selectors** -- selects relevant objects (jets, secondary
  vertices, tracks, truth) for analysis
* **TruthMatching** -- matches physics objects to truth-level quantitites
* **EJsxAODAnalysis** -- performs relevant analysis selections
* **EJsMiniNtuple** -- creates output TTree using **EJsHelpTreeBase**
  class, which fills branches according to object container classes

Example
configuration files for EJsMiniNtuple-making can be found under
`EJsAnalysis/config/EJsConfig*.py`. Example submission scripts for
running ntuple-making jobs locally and
on the grid can be found at `EJsAnalysis/scripts/submit_*.sh`. Text
files providing lists of input samples for both data and MC can be
found here: `EJsAnalysis/scripts/samples.*.txt`.


### Retrieving Ntuple Output from the Grid
The xAODAnaHelpers script `downloadAndMerge.py` is used to download
and merge output datasets produced on the Grid for further analysis,
histogramming, and plotting. It includes the
following options:

* **--container** -- name of dataset to be downloaded; may include wildcards
* **--file** -- text file containing names of datasets to be downloaded
* **--ndownloader** -- number of parallel download threads (default = 4)
* **--types** -- comma-separated list of file types to download; may
  include tree, hist, cutflow, logs, metadata, and/or rawDownload
* **--maxSize** -- attempted maximum size [GB] of output files
  (default = -1 (no limit)); files
  larger than this will not be merged
* **--outPath** -- output path (default = "./gridOutput/") where files
are downloaded

See `EJsAnalysis/scripts/get_*sh` example getting scripts for
reference on running `downloadAndMerge.py` to retrieve analysis output from the grid.


### Histogramming
Histogramming is performed through the xAH::Algorithm `HistogramEJsTree`,
which runs over the output EJsMiniNtuple from the ntuple-making step.

Example configuration files for histogramming can be found under
`EJsAnalysis/config/EJsHistoConfig*.py`, and example submission scripts
for running ntuple-to-histogram jobs can be found at
`EJsAnalysis/scripts/run_histos*.sh`.

> NOTE: right now, this is only setup to run locally and over a single
> input TTree file at a time





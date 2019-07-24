import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

sys.path.insert(0, os.environ['EJ_PATH']+"/EJsAnalysis/config/")

from EJsBaseConfig import *

c = xAH_config()


# --- update configurations for mc16a --- ##

data_path = "$EJ_PATH/EJsAnalysis/data/"
data15_path = data_path + "data15/"
data16_path = data_path + "data16/"

GRL_files       = [
    data15_path + "data15_13TeV.periodAllYear_DetStatus-v89-pro21-02_Unknown_PHYS_StandardGRL_All_Good_25ns.xml",
    data16_path + "data16_13TeV.periodAllYear_DetStatus-v89-pro21-01_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml",
    ]   
LumiCalc_files  = [
    data15_path + "PHYS_StandardGRL_All_Good_25ns_276262-284484_OflLumi-13TeV-008.root",
    data16_path + "PHYS_StandardGRL_All_Good_25ns_297730-311481_OflLumi-13TeV-009.root",
    ]
PRW_files       = [
    data_path   + "prw.EJs.mc16a.root"
    ]

GRL_config      = ",".join( GRL_files      )
LumiCalc_config = ",".join( LumiCalc_files )
PRW_config      = ",".join( PRW_files      )

Dict_BasicEventSelection.update ( { "m_applyGRLCut"       : True            } )
Dict_BasicEventSelection.update ( { "m_GRLxml"            : GRL_config      } )
Dict_BasicEventSelection.update ( { "m_lumiCalcFileNames" : LumiCalc_config } )
Dict_BasicEventSelection.update ( { "m_PRWFileNames"      : PRW_config      } )


# --- configure algorithms to run --- ##

# Basic Setup
c.algorithm ( "BasicEventSelection",     Dict_BasicEventSelection     )

# Jet Calibration
c.algorithm ( "JetCalibrator",           Dict_JetCalibrator_EMTopo    )
c.algorithm ( "JetCalibrator",           Dict_JetCalibrator_PFlow     )

# Jet Selection
c.algorithm ( "JetSelector",             Dict_JetSelector_EMTopo      )
c.algorithm ( "JetSelector",             Dict_JetSelector_PFlow       )

# Track Selection
c.algorithm ( "TrackSelector",           Dict_TrackSelector           )

# Secondary Vertex Selection
c.algorithm ( "SecondaryVertexSelector", Dict_SecondaryVertexSelector )

# Truth Vertex Selection
c.algorithm ( "TruthVertexSelector",     Dict_TruthVertexSelector     )

# Vertex Matching
c.algorithm ( "VertexMatcher",           Dict_VertexMatcher           )

# Object Matching
c.algorithm ( "ObjectMatcher",           Dict_ObjectMatcher           )

# EJs Analysis Selection
c.algorithm ( "EJsxAODAnalysis",         Dict_EJsxAODAnalysis         )

# EJs Ntuple
c.algorithm ( "EJsMiniNtuple",           Dict_EJsMiniNtuple           )

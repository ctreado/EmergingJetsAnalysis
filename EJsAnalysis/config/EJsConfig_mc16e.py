import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

sys.path.insert(0, os.environ['EJ_PATH']+"/EJsAnalysis/config/")

from EJsBaseConfig import *

c = xAH_config()


# --- update configurations for mc16e --- ##

data_path   = "EJsAnalysis/"
data18_path = data_path + "data18/"
grl18_path  = "GoodRunsLists/data18_13TeV/20190318/"

GRL_files       = [
    grl18_path  + "data18_13TeV.periodAllYear_DetStatus-v102-pro22-04_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml",
    ]
LumiCalc_files  = [
    data18_path + "ilumicalc_histograms_None_348885-364292_OflLumi-13TeV-010.root",
    ]
PRW_files       = [
    data_path   + "prw.EJs.mc16e.root",
    data18_path + "physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root",
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

# Object Matching
c.algorithm ( "ObjectMatcher",           Dict_ObjectMatcher           )

# Vertex Matching
c.algorithm ( "VertexMatcher",           Dict_VertexMatcher           )

# EJs Analysis Selection
c.algorithm ( "EJsxAODAnalysis",         Dict_EJsxAODAnalysis         )

# EJs Ntuple
c.algorithm ( "EJsMiniNtuple",           Dict_EJsMiniNtuple           )

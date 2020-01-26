import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

sys.path.insert(0, os.environ['EJ_PATH']+"/EJsAnalysis/config/")

from EJsBaseConfig import *

c = xAH_config()


## --- update configurations for mc16d --- ##

data_path   = "EJsAnalysis/"
data17_path = data_path + "data17/"
grl17_path  = "GoodRunsLists/data17_13TeV/20180619/"

GRL_files       = [
    grl17_path  + "data17_13TeV.periodAllYear_DetStatus-v99-pro22-01_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml",
    ]
LumiCalc_files  = [
    data17_path + "physics_25ns_Triggerno17e33prim.lumicalc.OflLumi-13TeV-010.root",
    ]
PRW_files       = [
    data_path   + "prw.EJs.mc16d.root",
    data_path   + "prw.bkgd.mc16d.root", ## --> not working --> turn off prw for bkgd for now and keep testing...
    data17_path + "physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root",
    ]

GRL_config      = ",".join( GRL_files      )
LumiCalc_config = ",".join( LumiCalc_files )
PRW_config      = ",".join( PRW_files      )

Dict_BasicEventSelection.update ( { "m_applyGRLCut"       : True            } )
Dict_BasicEventSelection.update ( { "m_GRLxml"            : GRL_config      } )
Dict_BasicEventSelection.update ( { "m_lumiCalcFileNames" : LumiCalc_config } )
Dict_BasicEventSelection.update ( { "m_PRWFileNames"      : PRW_config      } )


## --- configure algorithms to run --- ##

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

import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

# Basic Setup
c.algorithm ( "BasicEventSelection", { "m_name"        : "BaseEvtSel",
                                       "m_useMetaData" : False         } )

# EJs Ntuple
c.algorithm ( "EJsMiniNtuple", { "m_name" : "MiniNTuple" } )

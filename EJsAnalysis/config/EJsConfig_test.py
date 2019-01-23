import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()


## NOTE: everything set up for nominal case right now (no systematics) -->
## --> all "m_outputAlgo" vectors are empty for now...



## --- trigger lists --- ##

# signal triggers
fourJetTriggerList = [ "HLT_4j90",
                       "HLT_4j100",
                       "HLT_4j110",
                       "HLT_4j120",
                       "HLT_4j130",
                       "HLT_4j140",
                       "HLT_4j150" ]
# background triggers
singleJetTriggerList = [ "HLT_j15",
                         "HLT_j25",
                         "HLT_j35",
                         "HLT_j45",
                         "HLT_j55",
                         "HLT_j60",
                         "HLT_j85",
                         "HLT_j100",
                         "HLT_j110",
                         "HLT_j150",
                         "HLT_j175",
                         "HLT_j200",
                         "HLT_j260",
                         "HLT_j300",
                         "HLT_j320",
                         "HLT_j340",
                         "HLT_j360",
                         "HLT_j380",
                         "HLT_j400",
                         "HLT_j420",
                         "HLT_j440",
                         "HLT_j450",
                         "HLT_j460",
                         "HLT_j480",
                         "HLT_j500",
                         "HLT_j520" ]

fourJetTriggers   = ",".join( fourJetTriggerList )
singleJetTriggers = ",".join( singleJetTriggerList )
triggers          = ",".join( fourJetTriggerList + singleJetTriggerList )


    
## --- algorithm configuration dictionaries --- ##

# basic event selection
Dict_BasicEventSelection = {
    "m_name"                  : "BaseEvtSel",
    "m_msgLevel"              : "info",
    "m_GRLxml"                : "",
    "m_applyGRLCut"           : False, # --> True when GRLxml set
    "m_PRWFileNames"          : "",
    "m_lumiCalcFileNames"     : "",
    "m_doPUreweighting"       : False, # --> True when *FileNames set
    "m_triggerSelection"      : triggers,
    "m_applyTriggerCut"       : False, # True ??
    "m_storeTrigDecisions"    : True, 
    "m_storePassL1"           : True,
    "m_storePassHLT"          : True,
    "m_storeTrigKeys"         : True,
    "m_applyEventCleaningCut" : True,
    "m_applyCoreFlagsCut"     : True,
    "m_applyPrimaryVertexCut" : True,  # False ??
    "m_useMetaData"           : False, # True ??
    #"m_printBranchList"       : True   # TEST
}

    
# object calibration --> everything pretty much set to defaults for now; may need to modify...
Dict_JetCalibrator_EMTopo = { 
    "m_name"                : "JetCalib_AntiKt4EMTopo",
    "m_msgLevel"            : "info",
    "m_inContainerName"     : "AntiKt4EMTopoJets",
    "m_outContainerName"    : "AntiKt4EMTopoJets_Calib",
    "m_jetAlgo"             : "AntiKt4EMTopo",
    "m_outputAlgo"          : "AntiKt4EMTopoJets_Calib_Algo",
    "m_calibConfigData"     : "JES_data2017_2016_2015_Consolidated_EMTopo_2018_Rel21.config",
    "m_calibConfigFullSim"  : "JES_data2017_2016_2015_Consolidated_EMTopo_2018_Rel21.config",
    "m_uncertConfig"        : "rel21/Fall2018/R4_CategoryReduction_FullJER.config" # test --> does nothing w/o systematics (need to set "m_systName" to non-empty string to run systematics ("All" to run all available systematics))
}

Dict_JetCalibrator_PFlow = { 
    "m_name"                : "JetCalib_AntiKt4EMPFlow",
    "m_msgLevel"            : "info",
    "m_inContainerName"     : "AntiKt4EMPFlowJets",
    "m_outContainerName"    : "AntiKt4EMPFlowJets_Calib",
    "m_jetAlgo"             : "AntiKt4EMPFlow",
    "m_outputAlgo"          : "AntiKt4EMPFlowJets_Calib_Algo",
    "m_calibConfigData"     : "JES_data2017_2016_2015_Consolidated_PFlow_2018_Rel21.config",
    "m_calibConfigFullSim"  : "JES_data2017_2016_2015_Consolidated_PFlow_2018_Rel21.config",
    "m_uncertConfig"        : "rel21/Fall2018/R4_CategoryReduction_FullJER.config"
}

    
# object selection
Dict_JetSelector_EMTopo = {
    "m_name"                    : "JetSelect_AntiKt4EMTopo",
    "m_msgLevel"                : "info",
    "m_inContainerName"         : "AntiKt4EMTopoJets_Calib",
    "m_outContainerName"        : "AntiKt4EMTopoJets_Calib_Select",
    "m_inputAlgo"               : "AntiKt4EMTopoJets_Calib_Algo",
    "m_outputAlgo"              : "AntiKt4EMTopoJets_Calib_Select_Algo",
    "m_decorateSelectedObjects" : False,
    "m_createSelectedContainer" : True,
    "m_useCutFlow"              : True,
    #"m_pT_min"                  : 50e3,
    #"m_eta_max"                 : 2.7,
}

Dict_JetSelector_PFlow = {
    "m_name"                    : "JetSelect_AntiKt4EMPFlow",
    "m_msgLevel"                : "info",
    "m_inContainerName"         : "AntiKt4EMPFlowJets_Calib",
    "m_outContainerName"        : "AntiKt4EMPFlowJets_Calib_Select",
    "m_inputAlgo"               : "AntiKt4EMPFlowJets_Calib_Algo",
    "m_outputAlgo"              : "AntiKt4EMPFlowJets_Calib_Select_Algo",
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    "m_useCutFlow"              : False,
    #"m_pT_min"                  : 50e3,
    #"m_eta_max"                 : 2.7,
}


# analysis
Dict_EJsxAODAnalysis = {
    "m_name"     : "EJsAnaly",
    "m_msgLevel" : "info",
}

  
# output
Dict_EJsMiniNtuple = {
    "m_name"             : "EJsMiniNtuple",
    "m_msgLevel"         : "info",
    "m_evtDetailStr"     : "pileup",
    "m_trigDetailStr"    : "basic passTriggers",
    "m_jetDetailStr"     : "kinematic",
    #"m_jetContainerName" : "AntiKt4EMTopoJets_Calib_Select AntiKt4EMPFlowJets_Calib_Select",
    #"m_jetBranchName"    : "jet pflowJet",
    "m_jetContainerName" : "AntiKt4EMTopoJets",
    "m_jetBranchName"    : "jet",
    "m_systsVec"         : "" # empty string = nominal case --> will need to replace w/ final 'm_outputAlgo' from above...
    #"m_systsVec"         : "AntiKt4EMTopoJets_Calib_Algo"
}


    
## --- algorithms --- ##

# Basic Setup
c.algorithm ( "BasicEventSelection", Dict_BasicEventSelection )

## Jet Calibration
#c.algorithm ( "JetCalibrator", Dict_JetCalibrator_EMTopo )
#c.algorithm ( "JetCalibrator", Dict_JetCalibrator_PFlow )

## Jet Selection
#c.algorithm ( "JetSelector", Dict_JetSelector_EMTopo )
#c.algorithm ( "JetSelector", Dict_JetSelector_PFlow )

# Vertex / Track Selection

# Analysis
c.algorithm ( "EJsxAODAnalysis", Dict_EJsxAODAnalysis )

# EJs Ntuple
c.algorithm ( "EJsMiniNtuple", Dict_EJsMiniNtuple )




### NOTE: probably can't put histo alg here, since event-loop loops through entire
### algorithm chain every event (so we won't have written out our tree before
### we try to read it) --> make new separate config file for running histo alg
### after analysis / ntuple chain has run
### --> not sure, though; doesn't seem to be a place where the whole tree is
### finally written out; may happen every event, in which case we add histo alg to chain...

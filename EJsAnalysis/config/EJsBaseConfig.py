#!/usr/bin/env python

# base configurations for EJs analysis algorithms


## --- systematics --- ##

systName = ""        # no systematics --> for data and nominal mc
#systName = "All"     # do systematics

systVal = 0
systematicsValue = 1
if systName != "":
    systVal = systematicsValue


## --- material map --- ##
matMapPath = "EJsAnalysis/material_map/"
### --- metadata --- ##
#metadataPath = "EJsAnalysis/"


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
    "m_name"                      : "BaseEvtSel",
    "m_msgLevel"                  : "info",
    "m_applyGRLCut"               : False,
    "m_GRLxml"                    : "",
    "m_GRLExcludeList"            : "",
    "m_doPUreweighting"           : True,
    "m_doPUreweightingSys"        : bool(systVal), # --> uncomment once PRW config files available...
    "m_lumiCalcFileNames"         : "",
    "m_PRWFileNames"              : "",
    "m_applyPrimaryVertexCut"     : True,
    "m_PVNTrack"                  : 2,
    "m_applyEventCleaningCut"     : True,  # --> may want to turn off if using non-default jet cleaning cut level...
    "m_applyCoreFlagsCut"         : True,
    "m_applyJetCleaningEventFlag" : True,
    "m_applyTriggerCut"           : True,
    "m_triggerSelection"          : triggers,
    "m_storeTrigDecisions"        : True,
    "m_storePassL1"               : True,
    "m_storePassHLT"              : True,
    "m_storeTrigKeys"             : True,
    "m_truthLevelOnly"            : False, # --> change to True for truth-level analyses
    "m_derivationName"            : "EXOT23KernelAug",
    "m_useMetaData"               : True,
    "m_checkDuplicatesData"       : True,
    "m_checkDuplicatesMC"         : True,
}


# object calibration
Dict_JetCalibrator_EMTopo = {
    "m_name"                  : "JetCalib_AntiKt4EMTopo",
    "m_msgLevel"              : "info",
    "m_inContainerName"       : "AntiKt4EMTopoJets",
    "m_outContainerName"      : "AntiKt4EMTopoJets_Calib",
    "m_jetAlgo"               : "AntiKt4EMTopo",
    "m_outputAlgo"            : "AntiKt4EMTopoJets_Calib_Algo",
    "m_calibConfigData"       : "JES_MC16Recommendation_Consolidated_EMTopo_Apr2019_Rel21.config",
    "m_calibConfigFullSim"    : "JES_MC16Recommendation_Consolidated_EMTopo_Apr2019_Rel21.config",
    "m_uncertConfig"          : "rel21/Fall2018/R4_SR_Scenario1_SimpleJER.config", # --> TEST / TMP PLACEHOLDER --> need to test SR scenarios, investigate config files --> may change...
    "m_doCleaning"            : True,
    "m_jetCleanCutLevel"      : "LooseBad", ## --> consider using '(Very)LooseBadLLP' --> investigate cut levels -- may need to do some jet cleaning studies...
    "m_jetCleanUgly"          : False,
    "m_saveAllCleanDecisions" : True,
    "m_redoJVT"               : True,
    "m_calculatefJVT"         : True,
    "m_doJetTileCorr"         : False,      ## --> ERROR IF TRUE but do we want / need to apply jet tile correction ??? leave off for now, but investigate...
    "m_systName"              : systName,
    "m_systVal"               : systVal,
}

Dict_JetCalibrator_PFlow = {
    "m_name"                  : "JetCalib_AntiKt4EMPFlow",
    "m_msgLevel"              : "info",
    "m_inContainerName"       : "AntiKt4EMPFlowJets",
    "m_outContainerName"      : "AntiKt4EMPFlowJets_Calib",
    "m_jetAlgo"               : "AntiKt4EMPFlow",
    "m_outputAlgo"            : "AntiKt4EMPFlowJets_Calib_Algo",
    "m_calibConfigData"       : "JES_MC16Recommendation_Consolidated_PFlow_Apr2019_Rel21.config",
    "m_calibConfigFullSim"    : "JES_MC16Recommendation_Consolidated_PFlow_Apr2019_Rel21.config",
    "m_uncertConfig"          : "rel21/Fall2018/R4_SR_Scenario1_SimpleJER.config", # --> TEST / TMP PLACEHOLDER --> need to test SR scenarios, investigate config files --> may change...
    "m_doCleaning"            : False, # --> skip cleaning for pflow jets -- use EMTopo jet cleaning event cut (R21 rec)
    "m_redoJVT"               : True,
    "m_calculatefJVT"         : True,
    "m_doJetTileCorr"         : False, ## --> ERROR IF TRUE but do we want / need to apply jet tile correction ??? leave off for now, but investigate...
    "m_systName"              : systName,
    "m_systVal"               : systVal,
}


# object selection
Dict_JetSelector_EMTopo = {
    "m_name"                    : "JetSelect_AntiKt4EMTopo",
    "m_msgLevel"                : "info",
    "m_useCutFlow"              : True,
    "m_inContainerName"         : "AntiKt4EMTopoJets_Calib",
    "m_outContainerName"        : "AntiKt4EMTopoJets_Calib_Select",
    "m_inputAlgo"               : "AntiKt4EMTopoJets_Calib_Algo",
    "m_outputAlgo"              : "AntiKt4EMTopoJets_Calib_Select_Algo",
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    "m_cleanJets"               : True,     # --> remove all unclean jets, but only kill events with unclean jets of interest (i.e. passing basic pt, eta cuts -- already taken care of above w/ "applyJetCleaningEventFlag" / EventCleaningTool)
    "m_pass_min"                : 2,
    "m_pT_min"                  : 50e3,
    "m_eta_max"                 : 2.7,
    "m_doJVT"                   : True,
    "m_noJVTVeto"               : True,     # --> keep JVT-rejected jets + decorate w/ passing status
    "m_WorkingPointJVT"         : "Medium", # --> R21 EMTopo rec
    "m_SFFileJVT"               : "JetJvtEfficiency/Moriond2018/JvtSFFile_EMTopoJets.root",
    "m_systNameJVT"             : systName,
    "m_systValJVT"              : systVal,
    "m_dofJVT"                  : True,
    "m_dofJVTVeto"              : False,    # --> keep fJVT-rejected jets + decorate w/ passing status
    "m_WorkingPointfJVT"        : "Medium", # --> R21 EMTopo rec
    "m_SFFilefJVT"              : "JetJvtEfficiency/Moriond2018/fJvtSFFile.root",
    "m_UseMuSFFormatfJVT"       : False,
    "m_systNamefJVT"            : systName,
    "m_systValfJVT"             : systVal,    
}

Dict_JetSelector_PFlow = {
    "m_name"                    : "JetSelect_AntiKt4EMPlow",
    "m_msgLevel"                : "info",
    "m_useCutFlow"              : False, # --> can only use one jet-selector cutflow -- using EMTopo
    "m_inContainerName"         : "AntiKt4EMPFlowJets_Calib",
    "m_outContainerName"        : "AntiKt4EMPFlowJets_Calib_Select",
    "m_inputAlgo"               : "AntiKt4EMPFlowJets_Calib_Algo",
    "m_outputAlgo"              : "AntiKt4EMPFlowJets_Calib_Select_Algo",
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    "m_cleanJets"               : False,   # --> skip cleaning for pflow jets -- use EMTopo jet cleaning event cut (R21 rec)
    "m_pass_min"                : 2,
    "m_pT_min"                  : 50e3,
    "m_eta_max"                 : 2.7,
    "m_doJVT"                   : True,
    "m_noJVTVeto"               : True,    # --> keep JVT-rejected jets + decorate w/ passing status
    "m_WorkingPointJVT"         : "Tight", # --> R21 PFlow rec
    "m_SFFileJVT"               : "JetJvtEfficiency/Moriond2018/JvtSFFile_EMTopoJets.root",
    "m_systNameJVT"             : systName,
    "m_systValJVT"              : systVal,
    "m_dofJVT"                  : False,   # --> fJVT currently unavailable for PFlow jets... 
}

Dict_TrackSelector = {
    "m_name"                    : "TrackSelect",
    "m_msgLevel"                : "info",
    "m_inContainerName"         : "InDetTrackParticles",
    "m_outContainerName"        : "InDetTrackParticles_Select",
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    "m_pT_min"                  : 1e3,   # --> VSI track min-pt requirement
    "m_chi2NdofCut_max"         : 50,    # --> VSI track max-chi2 requirement
}

Dict_SecondaryVertexSelector = {
    "m_name"                    : "SecVtxSelect",
    "m_msgLevel"                : "info",
    "m_inContainerName"         : "VrtSecInclusive_SecondaryVertices",
    "m_outContainerName"        : "VrtSecInclusive_SecondaryVertices_Select",
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    "m_doTrackTrimming"         : True,  ## --> for now, apply (default) track trimming...
    "m_doFiltTrkCut"            : False, ## --> ...but don't apply filtered-track cuts
    "m_doMatMapVeto"            : False,
    "m_matMapInnerFileName"     : matMapPath + "MaterialMap_v3.2_Inner.root",
    "m_matMapInnerHistName"     : "FinalMap_inner",
    "m_matMapInnerMatrixName"   : "FoldingInfo",
    "m_matMapOuterFileName"     : matMapPath + "MaterialMap_v3_Outer.root",
    "m_matMapOuterHistName"     : "matmap_outer",
}

Dict_TruthVertexSelector = {
    "m_name"                    : "TruthVtxSelect",
    "m_msgLevel"                : "info",
    "m_inContainerName"         : "TruthVertices",
    "m_outContainerName"        : "TruthVertices_Select",
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    "m_truthLLP"                : "DarkPion Kshort",
    "m_r_max"                   : 563,
    "m_z_max"                   : 2720,
    "m_nVisOutP_min"            : 2,
}


# object matching
Dict_ObjectMatcher = {
    "m_name"                           : "ObjectMatch",
    "m_msgLevel"                       : "info",
    "m_inTruthJetContainerName"        : "AntiKt4TruthJets",
    "m_inTruthDarkJetContainerName"    : "AntiKt4TruthDarkJets",
    "m_inJetContainerName"             : "AntiKt4EMTopoJets_Calib_Select AntiKt4EMPFlowJets_Calib_Select",
    "m_inTruthPartContainerName"       : "TruthParticles",
    "m_inTrackPartContainerName"       : "InDetTrackParticles_Select",
    "m_inTruthVertexContainerName"     : "TruthVertices_Select",
    "m_inSecondaryVertexContainerName" : "VrtSecInclusive_SecondaryVertices_Select",
    "m_inputAlgo"                      : "AntiKt4EMTopoJets_Calib_Select_Algo",
    "m_jetSystsContainerIndex"         : 1,
    "m_jet_matchRadius"                : 0.3,
    "m_jet_vtx_matchRadius"            : 0.6,
    "m_jet_trk_matchRadius"            : 0.6,
}

Dict_VertexMatcher = {
    "m_name"                           : "VtxMatch",
    "m_msgLevel"                       : "info",
    "m_inTruthPartContainerName"       : "TruthParticles",
    "m_inTrackPartContainerName"       : "InDetTrackParticles_Select",
    "m_inTruthVertexContainerName"     : "TruthVertices_Select",
    "m_inSecondaryVertexContainerName" : "VrtSecInclusive_SecondaryVertices_Select",
    "m_truthLLP"                       : "DarkPion Kshort",
    "m_filterTruthVertex_llp"          : True,
    "m_distanceCutoff"                 : 10, 
    "m_doTruthTrackMatching"           : False, # already done in ObjectMatcher above...
    "m_setObjectIdentifiers"           : False, # already done in ObjectMatcher above...
    "m_vtx_matchScore"                 : 0,     # off for now --> can apply score requirement later (i.e. in histo alg)...
}


# analysis selection
Dict_EJsxAODAnalysis = {
    "m_name"                   : "EJsAna",
    "m_msgLevel"               : "info",
    "m_inJetContainerName"     : "AntiKt4EMTopoJets_Calib_Select AntiKt4EMPFlowJets_Calib_Select",
    "m_inJetBinName"           : "EMTopo PFlow",
    "m_inputAlgo"              : "AntiKt4EMTopoJets_Calib_Select_Algo",
    "m_outputAlgo"             : "AntiKt4EMTopoJets_Calib_Select_EJsxAODAna_Algo",
    "m_jetSystsContainerIndex" : 1,
    "m_cutflowJets"            : "EMTopo", # --> only fill cutflows for one jet container
    "m_signalTrigList"         : fourJetTriggers,
    "m_validTrigList"          : singleJetTriggers,
    #"m_metadataFileName"       : metadataPath + "mc16.metadata.txt"
}


# tree output
Dict_EJsMiniNtuple = {
    "m_name"                         : "EJsMiniNtup",
    "m_msgLevel"                     : "info",
    "m_evtDetailStr"                 : "pileup pileupsys",
    "m_trigDetailStr"                : "basic passTriggers prescales",
    "m_jetDetailStr"                 : "kinematic rapidity clean energy trackAll trackPV allTrack constituent area truth charge ghost match", # add "allTrackDetail", "detail" to regain full ntuple contents
    "m_jetContainerName"             : "AntiKt4EMTopoJets_Calib_Select AntiKt4EMPFlowJets_Calib_Select",
    "m_jetBranchName"                : "jet pflowJet",                           
    "m_jetSystsVec"                  : "AntiKt4EMTopoJets_Calib_Select_EJsxAODAna_Algo",
    "m_jetSystsContainerIndex"       : 1,
    "m_truthJetDetailStr"            : "kinematic rapidity energyLight constituent constituentAll area truthJets truthVerts truthParts", # add "detail" to regain full ntuple contents
    "m_truthJetContainerName"        : "AntiKt4TruthJets AntiKt4TruthDarkJets",
    "m_truthJetBranchName"           : "truthJet darkJet",
    "m_trackPartDetailStr"           : "kinematic vertex",
    "m_trackPartContainerName"       : "InDetTrackParticles_Select",
    "m_trackPartBranchName"          : "track",
    "m_truthPartDetailStr"           : "kinematic parents children",
    "m_truthPartContainerName"       : "TruthParticles",
    "m_truthPartBranchName"          : "truthPart",
    "m_secondaryVertexDetailStr"     : "tracks truthMatching jetMatched",
    "m_secondaryVertexContainerName" : "VrtSecInclusive_SecondaryVertices_Select",
    "m_secondaryVertexBranchName"    : "secVtx",
    "m_truthVertexDetailStr"         : "recoMatching recoMatchDetail jetMatched",
    "m_truthVertexContainerName"     : "TruthVertices_Select",
    "m_truthVertexBranchName"        : "truthVtx",
    "m_truthLLP"                     : "DarkPion Kshort",
}

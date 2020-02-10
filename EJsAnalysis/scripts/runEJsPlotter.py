#!/usr/bin/env python

##########################################
# runEJsPlotter.py                       #
##########################################
# script for running "plotEJsHistograms" #
# ########################################
# Colleen Treado                         #
##########################################

# don't forget to lumi-scale data !!

import os

def main():

    ## NOTE: cannot run all signal samples with all histograms at once (crashes); instead run multiple commands with smaller lists of signal samples or histograms...

    ## take note of which ntrk, 2d histograms to plot (based on what we already have)...
    
    ## --- initialize plotting commands --- ##
    # --> change when needed
    inDir   = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-01_n1/EJsNtupToHistOutput/"
    #inDir   = os.getenv('EJ_PATH') + "/../output/localOutput/tmp_search-minus-one/EJsNtupToHistOutput/"
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsHistograms.py"
    command = "python " + pscript + " --inDir " + inDir

    # signal
    command_s  = command
    command_s += " --sgnlType 312004,312008,312017,312022,312028,312031,312039,312046,312052,312060,312066,312067,312075,312080,312090"

    # background
    command_b  = command
    command_b += " --bkgdType 361024"

    # data
    command_d  = command
    command_d += " --dataType data --scaleData"
    
    # signal vs background
    command_sb  = command
    command_sb += " --bkgdType 361024"
    # --> xdm-1400
    command_sb_14 = command_sb
    command_sb_14 += " --sgnlType 312004,312022,312039,312060,312075"
    command_sb_14 += " --histTitle 'Xdm-1400 signal vs background'"
    command_sb_14 += " --outName xdm-1400"
    # --> xdm-1000
    command_sb_10 = command_sb
    command_sb_10 += " --sgnlType 312008,312028,312046,312066,312080"
    command_sb_10 += " --histTitle 'Xdm-1000 signal vs background'"
    command_sb_10 += " --outName xdm-1000"
    # --> xdm-600
    command_sb_06 = command_sb
    command_sb_06 += " --sgnlType 312017,312031,312052,312067,312090"
    command_sb_06 += " --histTitle 'Xdm-600 signal vs background'"
    command_sb_06 += " --outName xdm-600"

    # background vs data
    command_bd = command + " --scaleData"
    command_bd += " --bkgdType 361024"
    command_bd += " --dataType data"
    command_bd += " --histTitle 'background vs data'"


    
    ## --- update plotting commands --- ##   
    command_S  = " --regionDir search"
    command_S1 = " --regionDir search-minus-one"
    command_V  = " --regionDir valid"

    # --> will eventually want to plot data in search region, but not until unblinding...
    
    ## 1d plots (comparing same histo over different samples) ##
    histList_1d  = "pt_s,pt_xs:darkPionDV" # --> change as needed...
    command_1d   = " --draw1D --outSubdir 1d --legLenEnum 5 --histList " + histList_1d # --> change legLenEnum to 6 ??
    command_sb_l = " --lxint 0.006 --lyint 0.025"
    command_bd_l = " --lxint 0.015 --lyint 0.040"
    # --> xdm-1400 signal vs background
    command_sb_14_1d    = command_sb_14    + command_1d + command_sb_l
    command_sb_14_1d_S  = command_sb_14_1d + command_S
    command_sb_14_1d_S1 = command_sb_14_1d + command_S1
    # --> xdm-1000 signal vs background
    command_sb_10_1d    = command_sb_10    + command_1d + command_sb_l
    command_sb_10_1d_S  = command_sb_10_1d + command_S
    command_sb_10_1d_S1 = command_sb_10_1d + command_S1
    # --> xdm-600 signal vs background
    command_sb_06_1d    = command_sb_06    + command_1d + command_sb_l
    command_sb_06_1d_S  = command_sb_06_1d + command_S
    command_sb_06_1d_S1 = command_sb_06_1d + command_S1
    # --> background vs data
    command_bd_1d       = command_bd       + command_1d + command_bd_l
    command_bd_1d_V     = command_bd_1d    + command_V

    
    ## 2d plots (one histo per plot) ##
    histList_2d = "''" # --> skip dark pions for background; add different hist lists for signal and background
    command_2d  = " --draw2D --outSubdir 2d --histList " + histList_2d
    # --> signal
    command_s_2d_S  = command_s + command_2d + command_S
    command_s_2d_S1 = command_s + command_2d + command_S1
    # --> background
    command_b_2d_S  = command_b + command_2d + command_S
    command_b_2d_S1 = command_b + command_2d + command_S1
    command_b_2d_V  = command_b + command_2d + command_V
    # --> data
    command_d_2d_V  = command_d + command_2d + command_V


    ## multi-hist 1d plots (comparing different histos over SAME sample) ##
    Ntrk = 5
    histList_multi  = "''"
    command_multi   = []
    command_multi1d = " --drawMulti1D --outSubdir multi --legLenEnum 5 --lxint 0.007 --lyint 0.027 --histList " + histList_multi
    # --> different DV types against each other
    histVars, outNames = [], []
    histVars.append( "darkPionDV,kshortDV,nomatchDV"                            )
    histVars.append( "byJetDarkPionDV,byJetKshortDV,byJetNomatchDV"             )
    histVars.append( "byLeadJetDarkPionDV,byLeadJetKshortDV,byLeadJetNomatchDV" )
    histVars.append( "fiducialDarkPionDV,fiducialKshortDV,fiducialNomatchDV"    )
    # bare vs clean vs filt ??
    # [match] vs byJet[match] vs byLeadJet[match] vs fiducial[match] ??
    outNames.append( "match"         )
    outNames.append( "jetMatch"      )
    outNames.append( "leadJetMatch"  )
    outNames.append( "fiducialMatch" )
    for iVar, var in enumerate( histVars ):
        if iVar: lxl = "0.500"
        else:    lxl = "0.600"
        command_multi.append( command_multi1d + " --histVars " + var + " --outName " + outNames[iVar] + " --lxl " + lxl )
        # n-trk DVs
        for itrk in range( 2, Ntrk+1 ):
            ntrk = str(itrk) + "trk"
            ntrkvar = ""
            for iv, v in enumerate( var.split(',') ): ntrkvar += ntrk + v + ","
            if ntrkvar.endswith(','): ntrkvar = ntrkvar[:-1]
            command_multi.append( command_multi1d + " --histVars " + ntrkvar +
                                      " --outName " + outNames[iVar] + "." + ntrk + " --lxl " + lxl )
    # --> different number of track DVs of same type against each other
    ntrkHistVars = []
    for hv in histVars:
        vlist = hv.split(',')
        for v in vlist:
            if v not in ntrkHistVars:
                ntrkHistVars.append( v )
    for iVar, var in enumerate( ntrkHistVars ):
        ntrkvar = ""
        for itrk in range( 2, Ntrk+1 ):
            ntrk = str(itrk) + "trk"
            ntrkvar += ntrk + var + ","
        if ntrkvar.endswith(','):
            ntrkvar = ntrkvar[:-1]
        outvar = var
        if outvar.endswith('DV'):
            outvar = var[:-2]
        command_multi.append( command_multi1d + " --histVars " + ntrkvar + " --outName " + outvar + " --lxl 0.750 --varEnum 2" )
    command_s_multi_S1, command_s_multi_S = [], []
    command_b_multi_S1, command_b_multi_S = [], []
    for command in command_multi:
        command_s_multi_S1.append( command_s + command + command_S1 )
        command_b_multi_S1.append( command_b + command + command_S1 )
        command_s_multi_S .append( command_s + command + command_S  )
        command_b_multi_S .append( command_b + command + command_S  )


    ## multi-hist, multi-sample 1d plots (comparing different histos over DIFFERENT sample) ##
    histList_multismpl  = "'pt_s,pt_xs'"
    command_multismpl   = []
    command_multismpl1d = " --drawMulti1D --doMultiSmpl --outSubdir multismpl" + \
      " --legLenEnum 3 --lxint 0.007 --lyint 0.027 --histList " + histList_multismpl
    outName = []
    # --> different DV types across different samples against each other
    hvars, httls = [], []
    hvars.append( "darkPionDV,bareDV"               )
    hvars.append( "byJetDarkPionDV,byJetDV"         )
    hvars.append( "byLeadJetDarkPionDV,byLeadJetDV" )
    hvars.append( "fiducialDarkPionDV,fiducialDV"   )
    httls.append( "'matched signal vs all background'"                       )
    httls.append( "'by-jet matched signal vs by-jet background'"             )
    httls.append( "'by-lead-jet matched signal vs by-lead-jet background'"   )
    httls.append( "'fiducial-cut matched signal vs fiducial-cut background'" )
    # old ex: hvars = "darkPionDV,nomatchDV,bareDV"; sbdVars = "darkPionDV,nomatchDV:darkPionDV,bareDV"; httls = "'nomatch:bare'"
    for iVar, var in enumerate( hvars ):
        if iVar: lxl = "0.500"
        else:    lxl = "0.600"
        command_multismpl.append( command_multismpl1d + " --histVars " + var + " --sbdVars " + var + \
                                      " --histTitle " + httls[iVar] + " --lxl " + lxl )
        outName.append( "" )
        for itrk in range( 2, Ntrk+1 ):
            ntrk = str(itrk) + "trk"
            ntrkvar = ""
            for iv, v in enumerate( var.split(',') ):
                ntrkvar += ntrk + v + ","
            if ntrkvar.endswith(','):
                ntrkvar = ntrkvar[:-1]
            command_multismpl.append( command_multismpl1d + " --histVars " + ntrkvar + " --sbdVars " + var + \
                                          " --histTitle " + httls[iVar] + " --lxl " + lxl )
            outName.append( ntrk )
    command_sb_14_multismpl_S1, command_sb_10_multismpl_S1, command_sb_06_multismpl_S1 = [], [], []
    command_sb_14_multismpl_S,  command_sb_10_multismpl_S,  command_sb_06_multismpl_S  = [], [], []
    for iC, command in enumerate( command_multismpl ):
        command_sb_14_multismpl_S1.append( command_sb_14 + "." + outName[iC] + command + command_S1 )
        command_sb_10_multismpl_S1.append( command_sb_10 + "." + outName[iC] + command + command_S1 )
        command_sb_06_multismpl_S1.append( command_sb_06 + "." + outName[iC] + command + command_S1 )
        command_sb_14_multismpl_S .append( command_sb_14 + "." + outName[iC] + command + command_S  )
        command_sb_10_multismpl_S .append( command_sb_10 + "." + outName[iC] + command + command_S  )
        command_sb_06_multismpl_S .append( command_sb_06 + "." + outName[iC] + command + command_S  )

    

    
    ## --- run plotting jobs --- ##

    ## 1d: signal vs background
    ## --> xdm-1400
    #os.system( command_sb_14_1d_S  )
    #os.system( command_sb_14_1d_S1 )
    ## --> xdm-1000
    #os.system( command_sb_10_1d_S  )
    #os.system( command_sb_10_1d_S1 )
    ## --> xdm-600
    #os.system( command_sb_06_1d_S  )
    #os.system( command_sb_06_1d_S1 )
    # 1d: background vs data
    os.system( command_bd_1d_V     )

    ## multi 1d
    #for cm_sS1 in command_s_multi_S1:
    #    os.system( cm_sS1 )
    #for cm_bS1 in command_b_multi_S1:
    #    os.system( cm_bS1 )
    #for cm_sS1 in command_s_multi_S:
    #    os.system( cm_sS )
    #for cm_bS1 in command_b_multi_S:
    #    os.system( cm_bS )

    ## multi-sample 1d
    #for cms_sb14S1 in command_sb_14_multismpl_S1:
    #    os.system( cms_sb14S1 )
    for cms_sb10S1 in command_sb_10_multismpl_S1:
        os.system( cms_sb10S1 )
    #for cms_sb06S1 in command_sb_06_multismpl_S1:
    #    os.system( cms_sb06S1 )
    #for cms_sb14S  in command_sb_14_multismpl_S:
    #    os.system( cms_sb14S  )
    #for cms_sb10S  in command_sb_10_multismpl_S:
    #    os.system( cms_sb10S  )
    #for cms_sb06S  in command_sb_06_multismpl_S:
    #    os.system( cms_sb06S  )

    ## 2d: signal
    #os.system( command_s_2d_S  )
    #os.system( command_s_2d_S1 )
    ## 2d: background
    #os.system( command_b_2d_S  )
    #os.system( command_b_2d_S1 )
    #os.system( command_b_2d_V  )
    ## 2d: data
    #os.system( command_d_2d_V  )

    

if __name__ == "__main__":
    main()

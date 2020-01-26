#!/usr/bin/env python

##########################################
# runEJsPlotter.py                       #
##########################################
# script for running "plotEJsHistograms" #
# ########################################
# Colleen Treado                         #
##########################################

import os

def main():

    # --> change when needed
    inDir  = os.getenv('EJ_PATH') + "/../output/localOutput/tmp_search-minus-one/EJsNtupToHistOutput/"
    outDir = os.getenv('EJ_PATH') + "/../output/localOutput/tmp_search-minus-one/plots/"
    
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsHistograms.py"
    command = "python " + pscript + " --inDir " + inDir + " --outDir " + outDir

    ## --- initialize plotting commands --- ##
    
    # signal only
    command_s     = command
    command_s    += " --sgnlType 312008,312028"
    # --> search-minus-one region
    command_s_s1  = command_s
    command_s_s1 += " --regionDir search-minus-one"
    command_s_s1 += " --outTag s.search-1"
    # --> search region
    command_s_s   = command_s
    command_s_s  += " --regionDir search"
    command_s_s  += " --outTag s.search"

    # background only
    command_b     = command
    command_b    += " --bkgdType JZ4W"
    # --> search-minus-one region
    command_b_s1  = command_b
    command_b_s1 += " --regionDir search-minus-one"
    command_b_s1 += " --outTag b.search-1"
    # --> search region
    command_b_s   = command_b
    command_b_s  += " --regionDir search"
    command_b_s  += " --outTag b.search"
    # --> validation region
    command_b_v   = command_b
    command_b_v  += " --regionDir valid"
    command_b_v  += " --outTag b.valid"

    # data only
    command_d     = command
    command_d    += " --dataType data17"
    # --> validation region
    command_d_v   = command_d
    command_d_v  += " --regionDir valid"
    command_d_v  += " --outTag d.valid"

    # signal vs background
    command_sb     = command
    command_sb    += " --sgnlType 312008,312028"
    command_sb    += " --bkgdType JZ4W"
    # --> search-minus-one region
    command_sb_s1  = command_sb
    command_sb_s1 += " --regionDir search-minus-one"
    command_sb_s1 += " --outTag sb.search-1"
    command_sb_s1 += " --histTitle 'signal vs background'"
    # --> search region
    command_sb_s   = command_sb
    command_sb_s  += " --regionDir search"
    command_sb_s  += " --outTag sb.search"
    command_sb_s  += " --histTitle 'signal vs background'"

    # background vs data
    command_bd    = command
    command_bd   += " --bkgdType JZ4W"
    command_bd   += " --dataType data17"
    # --> validation region
    command_bd_v  = command_bd
    command_bd_v += " --regionDir valid"
    command_bd_v += " --outTag bd.valid"
    command_bd_v += " --histTitle 'background vs data'"



    ## --- update commands --- ##
    
    # 1d plots (comparing same histo over different samples)
    command_sb_s1_1d = command_sb_s1 + " --draw1D --histList :darkPionDV"
    command_sb_s_1d  = command_sb_s  + " --draw1D --histList :darkPionDV"
    command_bd_v_1d  = command_bd_v  + " --draw1D"

    
    # 1d plots (comparing different histos over same sample)
    command_multi = []
    Ntrk          = 5
    # --> different DV types against each other
    histVars, outNames = [], []
    histVars.append( "darkPionDV,kshortDV,nomatchDV"                                     )
    histVars.append( "bareDV,cleanDV,filtDV"                                             )
    histVars.append( "bareDV,byJetDV,byLeadJetDV,fiducialDV"                             )
    histVars.append( "byJetDarkPionDV,byJetKshortDV,byJetNomatchDV"                      )
    histVars.append( "byLeadJetDarkPionDV,byLeadJetKshortDV,byLeadJetNomatchDV"          )
    histVars.append( "fiducialDarkPionDV,fiducialKshortDV,fiducialNomatchDV"             )
    histVars.append( "darkPionDV,byJetDarkPionDV,byLeadJetDarkPionDV,fiducialDarkPionDV" )
    histVars.append( "kshortDV,byJetKshortDV,byLeadJetKshortDV,fiducialKshortDV"         )
    histVars.append( "nomatchDV,byJetNomatchDV,byLeadJetNomatchDV,fiducialNomatchDV"     )
    outNames.append( "match"        )
    outNames.append( "trkTrim"      )
    outNames.append( "cut"          )
    outNames.append( "jetMatch"     )
    outNames.append( "leadJetMatch" )
    outNames.append( "fiducMatch"   )
    outNames.append( "cutDarkPion"  )
    outNames.append( "cutKshort"    )
    outNames.append( "cutNomatch"   )
    for iVar, var in enumerate(histVars):
        command_multi.append( " --drawMulti1D --histVars " + var + " --varEnum 1 --outName " + outNames[iVar] )
        for itrk in range( 2, Ntrk + 1 ):
            ntrk = str(itrk) + "trk"
            ntrkvar = ""
            for iv, v in enumerate(var.split(',')):
                ntrkvar += ntrk + v + ","
            if ntrkvar.endswith(','):
                ntrkvar = ntrkvar[:-1]
            command_multi.append( " --drawMulti1D --histVars " + ntrkvar + " --varEnum 1 --outName " + outNames[iVar] + "." + ntrk )
    # --> different number of track DVs of same type against each other
    ntrkHistVars = []
    ntrkHistVars.append( "darkPionDV"          )
    ntrkHistVars.append( "kshortDV"            )
    ntrkHistVars.append( "nomatchDV"           )
    ntrkHistVars.append( "bareDV"              )
    ntrkHistVars.append( "cleanDV"             )
    ntrkHistVars.append( "filtDV"              )
    ntrkHistVars.append( "byJetDV"             )
    ntrkHistVars.append( "byLeadJetDV"         )
    ntrkHistVars.append( "fiducialDV"          )
    ntrkHistVars.append( "byJetDarkPionDV"     )
    ntrkHistVars.append( "byLeadJetDarkPionDV" )
    ntrkHistVars.append( "fiducialDarkPionDV"  )
    ntrkHistVars.append( "byJetKshortDV"       )
    ntrkHistVars.append( "byLeadJetKshortDV"   )
    ntrkHistVars.append( "fiducialKshortDV"    )
    ntrkHistVars.append( "byJetNomatchDV"      )
    ntrkHistVars.append( "byLeadJetNomatchDV"  )
    ntrkHistVars.append( "fiducialNomatchDV"   )
    for iVar, var in enumerate(ntrkHistVars):
        ntrkvar = ""
        for itrk in range( 2, Ntrk + 1 ):
            ntrk = str(itrk) + "trk"
            ntrkvar += ntrk + var + ","
        if ntrkvar.endswith(','):
            ntrkvar = ntrkvar[:-1]
        outvar = var
        if outvar.endswith('DV'):
            outvar = var[:-2]
        command_multi.append( " --drawMulti1D --histVars " + ntrkvar + " --varEnum 2 --outName " + outvar )
    command_s_s1_1dm, command_b_s1_1dm = [], []
    for command in command_multi:
        command_s_s1_1dm.append( command_s_s1 + command )
        command_b_s1_1dm.append( command_b_s1 + command )

        
    # 1d plots (comparing different histos over different samples)
    command_multi_diff = []
    histVars_diff, sbdVars, httlVars = [], [], []
    histVars_diff.append( "darkPionDV,nomatchDV,bareDV"                                            )
    histVars_diff.append( "byJetDarkPionDV,byJetNomatchDV,byJetDV"                                 )
    histVars_diff.append( "byLeadJetDarkPionDV,byLeadJetNomatchDV,byLeadJetDV"                     )
    histVars_diff.append( "fiducialDarkPionDV,fiducialNomatchDV,fiducialDV"                        )
    sbdVars .append( "darkPionDV,nomatchDV:darkPionDV,bareDV"                                 )
    sbdVars .append( "byJetDarkPionDV,byJetNomatchDV:byJetDarkPionDV,byJetDV"                 )
    sbdVars .append( "byLeadJetDarkPionDV,byLeadJetNomatchDV:byLeadJetDarkPionDV,byLeadJetDV" )
    sbdVars .append( "fiducialDarkPionDV,fiducialNomatchDV:fiducialDarkPionDV,fiducialDV"     )
    httlVars.append( "'matched signal vs unmatched background:matched signal vs background'"                                                     )
    httlVars.append( "'by-jet matched signal vs by-jet unmatched background:by-jet matched signal vs by-jet background'"                         )
    httlVars.append( "'by-lead-jet matched signal vs by-lead-jet unmatched background:by-lead-jet matched signal vs by-lead-jet background'"     )
    httlVars.append( "'fiducial-cut matched signal vs fiducial-cut unmatched background:fiducial-cut matched signal vs fiducial-cut background'" )
    Ntrk_diff = 5
    for iVard, vard in enumerate(histVars_diff):
        command_multi_diff.append( " --drawMulti1D --histVars " + vard + " --varEnum 1"
                                   " --doMultiSmpl --sbdVars " + sbdVars[iVard] + " --histTitle " + httlVars[iVard] )
        for itrkd in range( 2, Ntrk_diff + 1 ):
            ntrkd = str(itrkd) + "trk"
            ntrkvard = ""
            for ivd, vd in enumerate(vard.split(',')):
                ntrkvard += ntrkd + vd + ","
            if ntrkvard.endswith(','):
                ntrkvard = ntrkvard[:-1]
            command_multi_diff.append( " --drawMulti1D --histVars " + ntrkvard + " --varEnum 1 --outName " + ntrkd +
                                       " --doMultiSmpl --sbdVars " + sbdVars[iVard] + " --histTitle " + httlVars[iVard] )
    command_sb_s1_1dm = []
    for command in command_multi_diff:
        command_sb_s1_1dm.append( command_sb_s1 + command )

        
    # 2d plots --> one sample per plots
    command_s_s1_2d = command_s_s1 + " --draw2D"
    command_s_s_2d  = command_s_s  + " --draw2D"
    command_b_s1_2d = command_b_s1 + " --draw2D"
    command_b_s_2d  = command_b_s  + " --draw2D"
    command_b_v_2d  = command_b_v  + " --draw2D"
    command_d_v_2d  = command_d_v  + " --draw2D"

    
    # abcd plane plots
    command_sb_s1_abcd = command_sb_s1 + " --drawABCD --doABCD_count --doABCD_est"
    command_sb_s_abcd  = command_sb_s  + " --drawABCD --doABCD_count --doABCD_est"
    command_bd_v_abcd  = command_bd_v  + " --drawABCD --doABCD_count --doABCD_est"

    
    
    ## --- run plotting jobs --- ##
    
    ## ## --> signal vs background
    ## os.system( command_sb_s1_1d + " --outName s.b" )
    ## #os.system( command_sb_s_1d  + " --outName s.b"  )
    ## os.system( command_bd_v_1d  + " --outName b.d"  )
    
    ## ## --> DV types against each other
    ## for cms in command_s_s1_1dm:
    ##     os.system( cms )
    ## for cmb in command_b_s1_1dm:
    ##     os.system( cmb )
    ## for cmsb in command_sb_s1_1dm:
    ##     os.system( cmsb )
        
    ## ## --> 2d plots
    ## os.system( command_s_s1_2d )
    ## #os.system( command_s_s_2d  )
    ## os.system( command_b_s1_2d )
    ## #os.system( command_b_s_2d  )
    ## os.system( command_b_v_2d  )
    ## os.system( command_d_v_2d  )
    
    ## --> abcd plots
    os.system( command_sb_s1_abcd )
    #os.system( command_sb_s_abcd  )
    #os.system( command_bd_v_abcd  )


if __name__ == "__main__":
    main()

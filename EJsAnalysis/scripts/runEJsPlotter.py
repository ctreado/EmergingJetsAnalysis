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

    inDir  = os.getenv('EJ_PATH') + "/../run/local.hists.benchmark.test/EJsNtupToHistOutput/" # --> change
    #outDir = os.getenv('EJ_PATH') + "/../output/localOutput/tmp_search-minus-one/plots/"
    outDir = os.getenv('EJ_PATH') + "/../run/plots.local.hists.benchmark.test/"
    
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsHistograms.py"
    command = "python " + pscript + " --inDir " + inDir + " --outDir " + outDir

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


    # 1d plots (comparing samples)
    command_sb_s1_1d = command_sb_s1 + " --draw1D --histList :darkPionDV=kshortDV=nomatchDV"
    command_sb_s_1d  = command_sb_s  + " --draw1D --histList :darkPionDV=kshortDV=nomatchDVs"
    command_bd_v_1d  = command_bd_v  + " --draw1D"

    
    # 1d plots (comparing variables)
    command_multi = []
    histVars = [ "darkPionDV,kshortDV,nomatchDV", "bareDV,cleanDV,filtDV" ]
    varEnum  = [ 1, 2 ]
    Ntrk     = 5
    for iVar, var in enumerate(histVars):
        venum = str(varEnum[iVar])
        command_multi.append( " --drawMulti1D --histVars " + var + " --varEnum " + venum )
        for itrk in range( 2, Ntrk + 1 ):
            ntrk = str(itrk) + "trk"
            ntrkvar = ""
            for iv, v in enumerate(var.split(',')):
                ntrkvar += ntrk + v + ","
            if ntrkvar.endswith(','):
                ntrkvar = ntrkvar[:-1]
            command_multi.append( " --drawMulti1D --histVars " + ntrkvar + " --varEnum " + venum + " --outName " + ntrk )
    
    ntrkHistVars = ["darkPionDV","kshortDV","nomatchDV","bareDV","cleanDV","filtDV"]
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
        command_multi.append( " --drawMulti1D --histVars " + ntrkvar + " --varEnum 3 --outName " + outvar )

    command_s_s1_1dm, command_b_s1_1dm = [], []
    for command in command_multi:
        command_s_s1_1dm.append( command_s_s1 + command )
        command_b_s1_1dm.append( command_b_s1 + command )

        
    # 2d plots --> one sample per plot
    command_s_s1_2d = command_s_s1 + " --draw2D"
    command_s_s_2d  = command_s_s  + " --draw2D"
    command_b_s1_2d = command_b_s1 + " --draw2D"
    command_b_s_2d  = command_b_s  + " --draw2D"
    command_b_v_2d  = command_b_v  + " --draw2D"
    command_d_v_2d  = command_d_v  + " --draw2D"

    
    # abcd plane plots

    
    # run plotting jobs
    ## --> signal vs background
    #os.system( command_sb_s1_1d )
    ##os.system( command_sb_s_1d  )
    #os.system( command_bd_v_1d  )
    ## --> DV types against each other
    #for cms in command_s_s1_1dm:
    #    os.system( cms )
    #for cmb in command_b_s1_1dm:
    #    os.system( cmb )
    ## --> 2d plots
    #os.system( command_s_s1_2d )
    ##os.system( command_s_s_2d  )
    #os.system( command_b_s1_2d )
    ##os.system( command_b_s_2d  )
    #os.system( command_b_v_2d  )
    os.system( command_d_v_2d  )


if __name__ == "__main__":
    main()

#!/usr/bin/env python

###########################################################################
# runEJsPlotter_trkdveff.py                                               #
###########################################################################
# script for running "plotEJsHistograms" for trk/dv reco efficiency plots #
# #########################################################################
# Colleen Treado                                                          #
###########################################################################

# TO RUN ON LOCAL MACHINE (NOT CERNVM) NEED TO RUN W/ PYTHON3 --> make compatible with both python versions...
# --> also need to source root directory: 'source /usr/local/Cellar/root/6.16.00/bin/thisroot.sh'
# --> also need to set EJ_PATH in EmergingJetsAnalysis repo when running outside athena: 'export EJ_PATH=$(pwd)'
# --> also need to run with 'python3'

# don't forget to lumi-scale data !!

import os

def main():

    ## --- initialize plotting commands --- ##
    # --> change when needed --> UPDATE INPUT/OUTPUT DIRECTORES --> add baseDV type
    inDir   = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-06_mod/EJsNtupToHistOutput/trkVtxEff/"
    outDir  = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-06_mod/plots/trkVtxEff/"
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsHistograms.py"
    command = "python " + pscript + " --inDir " + inDir + " --outDir " + outDir
    #command = "python3 " + pscript + " --inDir " + inDir + " --outDir " + outDir # for running outside of athena

    
    # signal
    s_14          = " --sgnlType 312004,312022,312039,312060,312075" # xdm-1400
    s_10          = " --sgnlType 312008,312028,312046,312066,312080" # xdm-1000
    s_06          = " --sgnlType 312017,312031,312052,312067,312090" # xdm-600
    s_a           = " --sgnlType 312004,312008,312017"               # model a
    s_b           = " --sgnlType 312022,312028,312031"               # model b
    s_c           = " --sgnlType 312039,312046,312052"               # model c
    s_d           = " --sgnlType 312060,312066,312067"               # model d
    s_e           = " --sgnlType 312075,312080,312090"               # model e
    command_s     = command
    command_s_14  = command_s + s_14
    command_s_14 += " --histTitle 'X_{dm} = 1400 GeV signal'"
    command_s_14 += " --outName xdm-1400 --legLenEnum 5"
    command_s_10  = command_s + s_10
    command_s_10 += " --histTitle 'X_{dm} = 1000 GeV signal'"
    command_s_10 += " --outName xdm-1000 --legLenEnum 5"
    command_s_06  = command_s + s_06
    command_s_06 += " --histTitle 'X_{dm} = 600 GeV signal'"
    command_s_06 += " --outName xdm-600 --legLenEnum 5"
    command_s_a   = command_s + s_a
    command_s_a  += " --histTitle 'Model A signal'"
    command_s_a  += " --outName mod-a --legLenEnum 9 --lstyleEnum 3"
    command_s_b   = command_s + s_b
    command_s_b  += " --histTitle 'Model B signal'"
    command_s_b  += " --outName mod-b --legLenEnum 9 --lstyleEnum 3"
    command_s_c   = command_s + s_c
    command_s_c  += " --histTitle 'Model C signal'"
    command_s_c  += " --outName mod-c --legLenEnum 9 --lstyleEnum 3"
    command_s_d   = command_s + s_d
    command_s_d  += " --histTitle 'Model D signal'"
    command_s_d  += " --outName mod-d --legLenEnum 9 --lstyleEnum 3"
    command_s_e   = command_s + s_e
    command_s_e  += " --histTitle 'Model E signal'"
    command_s_e  += " --outName mod-e --legLenEnum 9 --lstyleEnum 3"
    # --> compare across lifetimes
    
    
    ## --- update plotting commands --- ##
    command_S  = " --regionDir search"
    command_S1 = " --regionDir search-minus-one"
    command_V  = " --regionDir valid"

    # 1d plots -- comparing same efficiencies across different samples
    #histList_1d = "darkpion+trk=vtx:kshort=dv=jet"
    histList_1d = "darkpion+vtx+eff=accept:kshort=dv=jet"
    command_1d  = " --draw1D --drawOpt1D 'nostack e1' --outSubdir 1d_trkdveff --histList " + histList_1d + " --doProfileX"
    # -- CONSIDER ALTERNATE DRAW OPTIONS (e0?)
    # --> xdm-1400 signal
    command_s_14_1d    = command_s_14    + command_1d
    command_s_14_1d_S1 = command_s_14_1d + command_S1
    # --> xdm-1000 signal
    command_s_10_1d    = command_s_10    + command_1d
    command_s_10_1d_S1 = command_s_10_1d + command_S1
    # --> xdm-600 signal
    command_s_06_1d    = command_s_06    + command_1d
    command_s_06_1d_S1 = command_s_06_1d + command_S1
    # --> model a signal
    command_s_a_1d     = command_s_a     + command_1d
    command_s_a_1d_S1  = command_s_a_1d  + command_S1
    # --> model b signal
    command_s_b_1d     = command_s_b     + command_1d
    command_s_b_1d_S1  = command_s_b_1d  + command_S1
    # --> model c signal
    command_s_c_1d     = command_s_c     + command_1d
    command_s_c_1d_S1  = command_s_c_1d  + command_S1
    # --> model d signal
    command_s_d_1d     = command_s_d     + command_1d
    command_s_d_1d_S1  = command_s_d_1d  + command_S1
    # --> model e signal
    command_s_e_1d     = command_s_e     + command_1d
    command_s_e_1d_S1  = command_s_e_1d  + command_S1

    # multi-hist 1d plots -- comparing inclusive vs standard vs lrt tracking in same sample
    histList_multi  = ":kshort=dv=jet"
    command_multi   = []
    command_multi1d = " --drawMulti1D --drawOptMulti1D 'nostack e0' --outSubdir multi_trkeff --varEnum 4 --legLenEnum 5 --doProfileX"
    # --> set hist vars for given trk types
    histVars = []
    outNames = []
    lxls     = []
    histVars.append( "recoDarkPionTrk,stdDarkPionTrk,lrtDarkPionTrk" )
    histVars.append( "darkPionTrk_recoEff,darkPionTrk_stdEff,darkPionTrk_lrtEff" )
    outNames.append( "algs" )
    outNames.append( "eff"  )
    lxls    .append( "0.700" )
    lxls    .append( "0.700" )
    #hvtx = [ "recobleDarkPionDecayVtx", "fiducDarkPionDecayVtx" ]
    hvtx = [ "fiducDarkPionDecayVtx" ]
    htrk = [ "Desc", "RecoDesc", "VtxDesc", "LooseVtxDesc", "MediumVtxDesc", "TightVtxDesc" ]
    hp_1 = [ "n",  "n",  "",    "",    "frac", "frac", "frac", "frac" ]
    hp_2 = [ "_r", "_z", "M_r", "M_z", "_r",   "_z",   "M_r",  "M_z"  ]
    for v in hvtx:
        hvarstr = ""
        for ip, p in enumerate( hp_1 ):
            hvarstr = ""
            for t in htrk:
                ttmp = t
                if not hp_1[ip] and t != "VtxDesc": ttmp = ttmp[0].lower() + ttmp[1:]
                hvarstr += v + "_" + hp_1[ip] + ttmp + hp_2[ip] + ","
            if hvarstr.endswith(','):
                hvarstr = hvarstr[:-1]
            histVars.append( hvarstr )
            outNames.append( v + "-" + hp_1[ip] + hp_2[ip] )
            lxls.append( "0.600" )
    # --> loop over hist vars and configure plotting script
    for iVar, var in enumerate( histVars ):
        histList = var
        if histList_multi:
            hlist = histList.split(',')
            histList = ""
            for hl in hlist:
                hl += "+" + histList_multi
                histList += hl + ","
            if histList.endswith(','): histList = histList[:-1]
        command_multi.append( command_multi1d + " --histVars " + var + " --outName " + outNames[iVar] + \
                                  " --histList " + histList + " --lxl " + lxls[iVar] )
    # --> complete commands
    command_s_multi_S1 = []
    for command in command_multi:
        command_s_multi_S1 .append( command_s + " --sgnlType 312004" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312008" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312017" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312022" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312028" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312031" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312039" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312046" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312052" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312060" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312066" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312067" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312075" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312080" + command + command_S1 )
        command_s_multi_S1 .append( command_s + " --sgnlType 312090" + command + command_S1 )


    ## --- run plotting jobs --- ##

    # 1d: comparing signal samples
    os.system( command_s_14_1d_S1 ) # xdm-1400
    os.system( command_s_10_1d_S1 ) # xdm-1000
    os.system( command_s_06_1d_S1 ) # xdm-600
    os.system( command_s_a_1d_S1  ) # model a
    os.system( command_s_b_1d_S1  ) # model b
    os.system( command_s_c_1d_S1  ) # model c
    os.system( command_s_d_1d_S1  ) # model d
    os.system( command_s_e_1d_S1  ) # model e

    # multi-1d: comparing histos across same sample
    #for cm_sS1 in command_s_multi_S1:
    #    os.system( cm_sS1 ) # signal



# run main
if __name__ == "__main__":
    main()

#!/usr/bin/env python

# script to plot graph of EJs signal grid

import ROOT
import math
from array import array




def plotGrid( signalGrid, title = "Signal Grid", gridstr = "" ):
    # set grid string (for saving output)
    if gridstr:
        gridstr = "_" + gridstr
        
    # set canvas
    c = ROOT.TCanvas( "grid" )
    c.SetLogy()
    
    # set model-pidm/x-shift dictionaries
    modeldict = { 'A':5, 'B':2,   'C':10, 'D':20, 'E':0.8 }
    shiftdict = { 'A':0, 'B':-25, 'C':25, 'D':50, 'E':-50 }

    # count number of a, b, c, d, and e points
    n = len(signalGrid)
    x, xa, xb, xc, xd, xe = [], [], [], [], [], []
    y, ya, yb, yc, yd, ye = [], [], [], [], [], []
    z, za, zb, zc, zd, ze = [], [], [], [], [], []
    for i in range(0,n):
        mod = signalGrid[i][1]  # model
        xdm  = signalGrid[i][2] # mediator mass ------- x
        ctau = signalGrid[i][3] # dark pion lifetime -- y
        pidm = modeldict[mod]   # dark pion mass ------ z
        #print( xdm, ctau )
        x.append(xdm)
        y.append(ctau)
        z.append(pidm)
        if   mod == 'A':
            xa.append(xdm)
            ya.append(ctau)
            za.append(pidm)
        elif mod == 'B':
            xb.append(xdm)
            yb.append(ctau)
            zb.append(pidm)
        elif mod == 'C':
            xc.append(xdm)
            yc.append(ctau)
            zc.append(pidm)
        elif mod == 'D':
            xd.append(xdm)
            yd.append(ctau)
            zd.append(pidm)
        elif mod == 'E':
            xe.append(xdm)
            ye.append(ctau)
            ze.append(pidm)

    # initialize model graphs
    ga = ROOT.TGraph( len(xa) )
    ga.SetTitle("test")
    gb = ROOT.TGraph( len(xb) )
    gc = ROOT.TGraph( len(xc) )
    gd = ROOT.TGraph( len(xd) )
    ge = ROOT.TGraph( len(xe) )
    ga.SetTitle( "Model A: #pi_{dm} = 5 GeV"   )
    gb.SetTitle( "Model B: #pi_{dm} = 2 GeV"   )
    gc.SetTitle( "Model C: #pi_{dm} = 10 GeV"  )
    gd.SetTitle( "Model D: #pi_{dm} = 20 GeV"  )
    ge.SetTitle( "Model E: #pi_{dm} = 0.8 GeV" )
    ga.SetMarkerStyle(20)
    gb.SetMarkerStyle(20)
    gc.SetMarkerStyle(20)
    gd.SetMarkerStyle(20)
    ge.SetMarkerStyle(20)
    # initialize 2d graph
    g2 = ROOT.TGraph2D( n )
    g2.SetMarkerStyle(20)

    # fill model graphs
    for ia in range( 0, len(xa) ):
        ga.SetPoint( ia, xa[ia]+shiftdict['A'], ya[ia] )
        ga.SetMarkerColor( ROOT.kRed )
    for ib in range( 0, len(xb) ):
        gb.SetPoint( ib, xb[ib]+shiftdict['B'], yb[ib] )
        gb.SetMarkerColor( ROOT.kGreen+1 )
    for ic in range( 0, len(xc) ):
        gc.SetPoint( ic, xc[ic]+shiftdict['C'], yc[ic] )
        gc.SetMarkerColor( ROOT.kBlue )
    for id in range( 0, len(xd) ):
        gd.SetPoint( id, xd[id]+shiftdict['D'], yd[id] )
        gd.SetMarkerColor( ROOT.kViolet )
    for ie in range( 0, len(xe) ):
        ge.SetPoint( ie, xe[ie]+shiftdict['E'], ye[ie] )
        ge.SetMarkerColor( ROOT.kOrange+1 )

    # fill 2d graph
    for j in range( 0, n ):
        g2.SetPoint( j, x[j], y[j], z[j] )

    # draw multigraph w/ model graphs
    mg = ROOT.TMultiGraph()
    mg.Add(ga)
    mg.Add(gb)
    mg.Add(gc)
    mg.Add(gd)
    mg.Add(ge)
    mg.SetTitle( title )
    mg.GetXaxis().SetTitle( "mediator mass [GeV]" )
    mg.GetYaxis().SetTitle( "dark pion lifetime [mm]" )
    mg.GetXaxis().SetLimits( 400, 1600 )
    mg.Draw("AP")
    # set legend
    c.BuildLegend( 0.7, 0.125, 0.885, 0.25 )
    

    # save graph + clear canvas
    c.SaveAs( "grid1d" + gridstr + ".pdf" )
    c.Clear()

    # draw 2d graph
    g2.SetTitle( title )
    g2.GetXaxis().SetTitle( "mediator mass [GeV]" )
    g2.GetYaxis().SetTitle( "dark pion lifetime [mm]" )
    g2.GetZaxis().SetTitle( "dark pion mass [GeV]" )
    g2.GetXaxis().SetTitleOffset( 1.75 )
    g2.GetYaxis().SetTitleOffset( 1.75 )
    g2.GetZaxis().SetTitleOffset( 1.2  )
    g2.Draw("P")
    # save graph + clear canvas
    c.SaveAs( "grid2d" + gridstr + ".pdf" )
    c.Clear()

    
        



# set signal grid list
def setSignalGrid():
    signalGrid = []
    # Model A
    signalGrid.append( [ 312001, "A", 1400, 300 ] ) # 1400-Xdm
    signalGrid.append( [ 312002, "A", 1400, 150 ] )
    signalGrid.append( [ 312003, "A", 1400,  75 ] )
    signalGrid.append( [ 312004, "A", 1400,  20 ] )
    signalGrid.append( [ 312005, "A", 1400,   5 ] )
    signalGrid.append( [ 312006, "A", 1400,   2 ] )
    signalGrid.append( [ 312007, "A", 1000, 300 ] ) # 1000-Xdm
    signalGrid.append( [ 312008, "A", 1000, 150 ] )
    signalGrid.append( [ 312009, "A", 1000,  75 ] )
    signalGrid.append( [ 312010, "A", 1000,   5 ] )
    signalGrid.append( [ 312011, "A", 1000,   2 ] )
    signalGrid.append( [ 312012, "A", 1000,   1 ] )
    signalGrid.append( [ 312013, "A",  600, 300 ] ) #  600-Xdm
    signalGrid.append( [ 312014, "A",  600, 150 ] )
    signalGrid.append( [ 312015, "A",  600,  20 ] )
    signalGrid.append( [ 312016, "A",  600,   2 ] )
    signalGrid.append( [ 312017, "A",  600,   1 ] )
    signalGrid.append( [ 312018, "A",  600, 0.5 ] )
    # Model B
    signalGrid.append( [ 312019, "B", 1400, 300 ] ) # 1400-Xdm
    signalGrid.append( [ 312020, "B", 1400, 150 ] )
    signalGrid.append( [ 312021, "B", 1400,  75 ] )
    signalGrid.append( [ 312022, "B", 1400,  20 ] )
    signalGrid.append( [ 312023, "B", 1400,   5 ] )
    signalGrid.append( [ 312024, "B", 1400,   2 ] )
    signalGrid.append( [ 312025, "B", 1000, 300 ] ) # 1000-Xdm
    signalGrid.append( [ 312026, "B", 1000, 150 ] )
    signalGrid.append( [ 312027, "B", 1000,  75 ] )
    signalGrid.append( [ 312028, "B", 1000,   5 ] )
    signalGrid.append( [ 312029, "B", 1000,   2 ] )
    signalGrid.append( [ 312030, "B", 1000,   1 ] )
    signalGrid.append( [ 312031, "B",  600, 300 ] ) #  600-Xdm
    signalGrid.append( [ 312032, "B",  600, 150 ] )
    signalGrid.append( [ 312033, "B",  600,  20 ] )
    signalGrid.append( [ 312034, "B",  600,   2 ] )
    signalGrid.append( [ 312035, "B",  600,   1 ] )
    signalGrid.append( [ 312036, "B",  600, 0.5 ] )
    # Model C
    signalGrid.append( [ 312037, "C", 1400, 300 ] ) # 1400-Xdm
    signalGrid.append( [ 312038, "C", 1400, 150 ] )
    signalGrid.append( [ 312039, "C", 1400,  75 ] )
    signalGrid.append( [ 312040, "C", 1400,  20 ] )
    signalGrid.append( [ 312041, "C", 1400,   5 ] )
    signalGrid.append( [ 312042, "C", 1400,   2 ] )
    signalGrid.append( [ 312043, "C", 1000, 300 ] ) # 1000-Xdm
    signalGrid.append( [ 312044, "C", 1000, 150 ] )
    signalGrid.append( [ 312045, "C", 1000,  75 ] )
    signalGrid.append( [ 312046, "C", 1000,   5 ] )
    signalGrid.append( [ 312047, "C", 1000,   2 ] )
    signalGrid.append( [ 312048, "C", 1000,   1 ] )
    signalGrid.append( [ 312049, "C",  600, 300 ] ) #  600-Xdm
    signalGrid.append( [ 312050, "C",  600, 150 ] )
    signalGrid.append( [ 312051, "C",  600,  20 ] )
    signalGrid.append( [ 312052, "C",  600,   2 ] )
    signalGrid.append( [ 312053, "C",  600,   1 ] )
    signalGrid.append( [ 312054, "C",  600, 0.5 ] )
    # Model D
    signalGrid.append( [ 312055, "D", 1400, 300 ] ) # 1400-Xdm
    signalGrid.append( [ 312056, "D", 1400, 150 ] )
    signalGrid.append( [ 312057, "D", 1400,  75 ] )
    signalGrid.append( [ 312058, "D", 1400,  20 ] )
    signalGrid.append( [ 312059, "D", 1400,   5 ] )
    signalGrid.append( [ 312060, "D", 1400,   2 ] )
    signalGrid.append( [ 312061, "D", 1000, 300 ] ) # 1000-Xdm
    signalGrid.append( [ 312062, "D", 1000, 150 ] )
    signalGrid.append( [ 312063, "D", 1000,  75 ] )
    signalGrid.append( [ 312064, "D", 1000,   5 ] )
    signalGrid.append( [ 312065, "D", 1000,   2 ] )
    signalGrid.append( [ 312066, "D", 1000,   1 ] )
    signalGrid.append( [ 312067, "D",  600, 300 ] ) #  600-Xdm
    signalGrid.append( [ 312068, "D",  600, 150 ] )
    signalGrid.append( [ 312069, "D",  600,  20 ] )
    signalGrid.append( [ 312070, "D",  600,   2 ] )
    signalGrid.append( [ 312071, "D",  600,   1 ] )
    signalGrid.append( [ 312072, "D",  600, 0.5 ] )
    # Model E
    signalGrid.append( [ 312073, "E", 1400, 300 ] ) # 1400-Xdm
    signalGrid.append( [ 312074, "E", 1400, 150 ] )
    signalGrid.append( [ 312075, "E", 1400,  75 ] )
    signalGrid.append( [ 312076, "E", 1400,  20 ] )
    signalGrid.append( [ 312077, "E", 1400,   5 ] )
    signalGrid.append( [ 312078, "E", 1400,   2 ] )
    signalGrid.append( [ 312079, "E", 1000, 300 ] ) # 1000-Xdm
    signalGrid.append( [ 312080, "E", 1000, 150 ] )
    signalGrid.append( [ 312081, "E", 1000,  75 ] )
    signalGrid.append( [ 312082, "E", 1000,   5 ] )
    signalGrid.append( [ 312083, "E", 1000,   2 ] )
    signalGrid.append( [ 312084, "E", 1000,   1 ] )
    signalGrid.append( [ 312085, "E",  600, 300 ] ) #  600-Xdm
    signalGrid.append( [ 312086, "E",  600, 150 ] )
    signalGrid.append( [ 312087, "E",  600,  20 ] )
    signalGrid.append( [ 312088, "E",  600,   2 ] )
    signalGrid.append( [ 312089, "E",  600,   1 ] )
    signalGrid.append( [ 312090, "E",  600, 0.5 ] )

    return signalGrid
        
    

if __name__ == "__main__":
    # get signal grids to plots
    signalGrid  = setSignalGrid() # full signal grid
    initialGrid = []              # initial sub-grid
    updatedGrid = []              # updated sub-grid -- initial + new points
    # --> fill sub-grids
    initial_dsids = [ 312004, 312008, 312017, 312022, 312028, 312031, 312039, 312046, 312052, 312060, 312066, 312067, 312075, 312080, 312090 ]
    updated_dsids = initial_dsids + [ 312001, 312006, 312009, 312011, 312015, 312016, 312020, 312023, 312025, 312029, 312035, 312036, 312038, 312043, 312050, 312055, 312063, 312072, 312077, 312084, 312087 ]
    for i in range( 0, len(signalGrid) ):
        for j in range( 0, len(initial_dsids) ):
            if initial_dsids[j] == signalGrid[i][0]:
                initialGrid.append(signalGrid[i])
        for k in range( 0, len(updated_dsids) ):
            if updated_dsids[k] == signalGrid[i][0]:
                updatedGrid.append(signalGrid[i])

    # plot signal grids
    plotGrid( signalGrid,  "Full Signal Grid",        "full"    )
    plotGrid( initialGrid, "Initial Signal Sub-Grid", "initsub" )
    plotGrid( updatedGrid, "Updated Signal Sub-Grid", "updtsub" )

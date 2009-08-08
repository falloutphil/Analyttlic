"""
   
    Things to do:
        * Should your cubic spline really be that bendy
            * It doesn't always look continuous to me either
            * It changes direction on some knots!
        * Your yeild calculations are better
            * But your Day Count Convention is still flakey (improved now)
            * Check against Bloomberg and refine it (still not perfect??)
            * UK Gilts adhere to ACT/365 
                * Each month is considered to have it's normal number of days
                * But every year has 365 days
                * http://www.answers.com/topic/day-count-convention?cat=biz-fin
        * Graph isn't identical because you're plotting ACT/365 rather
          than 1,2,7,10yr like Bloomberg??
"""

import libAnalyttlic as la

import urllib
import wx
from math import fabs

from GraphPlotter import MyFrame
import BloombergHtmlParser as bbgParser
import DmoXmlParser as dmoParser

if __name__ == '__main__':
    print "Accessing UK DMO to get current Gilt prices..."
    dmoXml = dmoParser.DmoXmlParser()
    dmoBondList = dmoXml.createDmoBondListFromXml()
    
    print "Creating Analyttlic bonds from UK DMO quotes..."
    bonds = []
    for bond in dmoBondList:
        #print bond
        tmpStdBond = bond.cloneAsStandardBond()
        tmpStdBond.givenYield = bond.givenYield
        bonds.append( tmpStdBond )
    
    bondVector = la.vBond()
    yieldCurve = []
    print "Displaying Maturity and corresponding calculated Yield To Maturity..."
    for bond in bonds:
        bond.sortCouponsByDate()
        #print
        #print
        #print "Coupons for Bond:"
        #bond.printCoupons()
        #print
        print "Maturity:", bond.maturityIfCouponsAreSorted(),  \
              "\tYield:", bond.ytm()*100, "\tGiven Yield:", bond.givenYield, \
              "\tDiff:", fabs(bond.givenYield - bond.ytm()*100)
        yieldCurve.append( ( bond.maturityIfCouponsAreSorted(), bond.ytm()*100 ) )
        bondVector.append( bond )
   
    print
    print "Create Forward Rates Curve from bonds..."
    forwardCurve = la.ForwardRateCurve( bondVector )
    forwardCurve.printPoints()
    forwardCurve.sortBondsByMaturity()
    
    print "Bootstrapping Curve..."
    forwardCurve.dividedDifferenceBootstrap( 0.1 )
    #forwardCurve.cubicSplineBootstrap( 0.1 )
    print
    print "Output calculated points..."
    #forwardCurve.printInterpolatedPoints()
    
    listOfTuples = forwardCurve.pyListInterpolatedPoints()
    listOfOriginalTuples = forwardCurve.pyListOriginalPoints()
    
    pcTuples = []
    pcOrigTuples = []
    for tuple in listOfTuples:
        #print "tuple:", tuple
        pcTuples.append( ( tuple[0], tuple[1]*100 ) )
    for tuple in listOfOriginalTuples:
        #print "tuple:", tuple
        pcOrigTuples.append( ( tuple[0], tuple[1]*100 ) )   
        
    app = wx.PySimpleApp()
    #frame = wx.Frame( None, wx.ID_ANY, "Analyttlic")
    #frame.Show( True )
    f = MyFrame( pcTuples, pcOrigTuples, yieldCurve)
    #f2 = MyFrame( pcOrigTuples )
    app.MainLoop()
    
    
    
    
    
    
    
    
    
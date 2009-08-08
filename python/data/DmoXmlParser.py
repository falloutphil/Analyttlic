# -*- coding: utf-8 -*-

import libAnalyttlic as la

import urllib 
import xml.dom.minidom as minidom
from datetime import date, timedelta

class DmoBond(object):
    #¼ ½
    __fractionDict = { u'¼'.encode('utf-8') : ".25", u'⅓'.encode('utf-8') : ".333333333", u'½'.encode('utf-8') : ".5", u'¾'.encode('utf-8') : ".75" }
    
    def __init__(self, instrumentName, maturity, cleanPrice, dirtyPrice, givenYield):
        self.__instrumentName = instrumentName.encode('utf8')
        if '%' in self.__instrumentName:
            self.__coupon = self.__instrumentName.split('%')[0]
            for fraction in self.__fractionDict.keys():
                if fraction in self.__coupon:
                    self.__coupon = self.__coupon.replace( fraction, self.__fractionDict[fraction] )
            self.__coupon = float(self.__coupon)        
        else:
            self.__coupon = 0
        dateList = maturity.split('T')[0].split('-')
        self.__maturity = date( int(dateList[0]), int(dateList[1]), int(dateList[2]) )
        timeDeltaToMaturity = self.__maturity - date.today()
        self.__actual365 = float(timeDeltaToMaturity.days) / 365.25
        self.__cleanPrice = float(cleanPrice)
        self.__dirtyPrice = float(dirtyPrice)
        self.givenYield = float(givenYield)
        #print instrumentName, maturity, cleanPrice, dirtyPrice, givenYield
    
    def CalcYearAsDecimal(self):
        oneDay = timedelta( days=1 )
        td = date.today()
        loopDay = lastLoopDay = td
        decimalYear = 0.0
        #Calculate remaining proportion of *this* year
        if self.__maturity.year == td.year:
            pass
        # If we have a span of > 1 year calculate *last* year
        if self.__maturity.year > td.year:
            pass
        #If we have a span of > 2 years we have n full years
        for year in range(date.today().year, self.__maturity.year):
            AccDaysInYear = 0
            yDays = 365
            # Add one for leap years
            if year%4 == 0:
                if year%100 == 0:
                    if year%400 == 0:
                        yDays += 1   
                else:
                    yDays += 1
            
            while( loopDay.year == lastLoopDay.year ):
                AccDaysInYear += 1
                loopDay += oneDay
            
            # Reset to Jan 1st next year
            lastLoopDay = loopDay
            # Calculate decimal of this year
            decimalYear += float(AccDaysInYear) / float(yDays)
        
           
    def __str__(self):
        return "\nInstrument Name: " + str(self.__instrumentName) + \
               "\nCoupon:          " + str(self.__coupon) + \
               "\nMaturity:        " + str(self.__maturity) + \
               "\nActual/365 Mat:  " + str(self.__actual365) + \
               "\nClean Price:     " + str(self.__cleanPrice) + \
               "\nDirty Price:     " + str(self.__dirtyPrice) + \
               "\nGiven Yield:     " + str(self.givenYield)
    
    def __sixMonthsBack(self, currentDate):
        m = currentDate.month
        y = currentDate.year
        m -= 6
        if m < 1:
            y -= 1
            m = 12 + m
        return date( y, m, currentDate.day)
        
    def cloneAsStandardBond(self):
        print "Bond:", self.__instrumentName
        couponValue = (self.__coupon / 2.0)
        #/ parValue
        #print "Coupon Value:", couponValue
        principalValue = 100.0
        couponVector = la.vCoupon()
        # Pay out at maturity
        couponVector.append( la.Coupon( couponValue + principalValue, self.__actual365 ) )
        #print "  Maturity:", self.__maturity
        countBackFromMaturity = self.__sixMonthsBack( self.__maturity )
        today = date.today()
        if couponValue > 0.0:
            # We have coupons!
            while ( countBackFromMaturity > today ):
                #We have a some coupons too!
                #print "   Coupon:", countBackFromMaturity
                couponTimeDelta =  countBackFromMaturity - today
                couponActual365 = float(couponTimeDelta.days) / 365.25
                couponVector.append( la.Coupon( couponValue, couponActual365 ) )
                countBackFromMaturity = self.__sixMonthsBack( countBackFromMaturity )
        
        return la.Bond( self.__cleanPrice, couponVector )
    



class DmoXmlParser(object):
    def __init__(self):
        usock = urllib.urlopen('http://www.dmo.gov.uk/xmlData.aspx?rptCode=D3B.2&page=Gilts/Daily_Prices') 
        self.__dmoXmlDoc = minidom.parse(usock)
        usock.close()
 
    def getXml(self):
        return self.__dmoXmlDoc.toxml()
    
    def createDmoBondListFromXml(self):
        xmlBondList = self.__dmoXmlDoc.getElementsByTagName("SILO_DAILY_PRICES")
        dmoBondList = []
        #print xmlBondList
        for xmlBond in xmlBondList:
            if "REDEMPTION_DATE" in xmlBond.attributes.keys() and not 'Index-linked' in xmlBond.attributes["INSTRUMENT_NAME"].value:
                dmoBondList.append( DmoBond(xmlBond.attributes["INSTRUMENT_NAME"].value,
                                            xmlBond.attributes["REDEMPTION_DATE"].value,
                                            xmlBond.attributes["CLEAN_PRICE"].value,
                                            xmlBond.attributes["DIRTY_PRICE"].value,
                                            xmlBond.attributes["YIELD"].value) 
                                  )
            
        return dmoBondList
        
if __name__ == '__main__':
    dmoXml = DmoXmlParser()
    #print test.getXml()
    dmoBondList = dmoXml.createDmoBondListFromXml()
    for bond in dmoBondList:
        print
        print bond
    
    
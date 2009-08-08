import libAnalyttlic as la

import re
from datetime import date
from datetime import time
from datetime import timedelta
from datetime import datetime
import urllib
from sgmllib import SGMLParser

class BloombergBond(object):
    
    
    __bondGetMonth = { "Month" : lambda m : int(m), "Year" : lambda y : int(y)*12 }
    
    def __init__(self):
        self.months = self.coupon = self.maturity = self.price = self.byield = self.time = "ERROR: NOT SET"
                    
    def __str__(self):
        return "\nBond Output\n-----------\n" + \
               "\nMonths: " + str(self.months) + \
               "\nCoupon: " + str(self.coupon) + \
               "\nMaturity: " + str(self.maturity) + \
               "\nPrice: " + str(self.price) + \
               "\nYield: " + str(self.byield) + \
               "\nTime: " + str(self.time) + "\n"
               
    def returnMemberReference(self, functionName):
        return getattr( self, functionName )
 
    def setMonths(self, value):
        #print "months set to:", value
        monthsList = value.split('-')
        self.months = self.__bondGetMonth[ monthsList[1] ]( monthsList[0] )

    def setCoupon(self, value):
        #print "coupon set to:", value
        if "N.A" in value: value = "0"
        self.coupon = float(value)
        
    def setMaturity(self, value):
        #print "maturity set to:", value
        if "N.A." in value:
            self.maturity = date.min
            # This is just a cop out for now
            self.actual365 = 0
        else: 
            dateList = value.split('/')
            try:
                self.maturity = date( int(dateList[2]), int(dateList[1]), int(dateList[0]) )
            except:
                self.maturity = date( int(dateList[2]), int(dateList[0]), int(dateList[0]) )
            timeDeltaToMaturity = self.maturity - date.today()
            self.actual365 = float(timeDeltaToMaturity.days) / 365.0
            
    def setCurrentPriceAndYield(self, value):
        #print "price/yield set to:", value
        splitValue = value.split('/')
        # This is a horrible fudge assuming that the bond is quoted 
        # at a par value of 100 and the page is wrong!!!
        self.price = float(splitValue[0])
        #if self.price < 30:
            # 30 is arbitary - but if a 100 par bond
            # is being quoted at less than 30 - either
            # the markets have gone seriously mental
            # or they've missed the '9' off the price!
            #self.price += 90
        self.byield = float(splitValue[1])
   
    def setTime(self, value):
        #print "time set to:", value
        if ':' in value:
            # We have a clock time from today
            splitValue = value.split(':')
            today = datetime.today()
            #today.replace( hour = int(splitValue[0]), minute = int(splitValue[1]) )
            self.time = datetime( today.year, today.month, today.day, hour = int(splitValue[0]), minute = int(splitValue[1] ) )
            #time( int(splitValue[0]), int(splitValue[1]) )
        else:
            # Data from a previous date
            splitValue = value.split('/')
            today = datetime.today()
            self.time = datetime( today.year, month = int(splitValue[0]), day = int(splitValue[1]) )
            #today.replace( month = int(splitValue[0]), day = int(splitValue[1]) )
    
    def __sixMonthsBack(self, currentDate):
        m = currentDate.month
        y = currentDate.year
        m -= 6
        if m < 1:
            y -= 1
            m = 12 + m
        return date( y, m, currentDate.day)
        
    def cloneAsStandardBond(self):
        parValue = 100.0
        couponValue = (self.coupon / 2) / parValue
        principalValue = 1.0
        couponVector = la.vCoupon()
        # Pay out at maturity
        couponVector.append( la.Coupon( couponValue + principalValue, self.actual365 ) )
        #print "Maturity:", self.maturity
        countBackFromMaturity = self.__sixMonthsBack( self.maturity )
        today = date.today()
        while ( countBackFromMaturity > today ):
            #We have a some coupons too!
            #print "   Coupon:", countBackFromMaturity
            couponTimeDelta =  countBackFromMaturity - today
            couponActual365 = float(couponTimeDelta.days) / 365.0
            couponVector.append( la.Coupon( couponValue, couponActual365 ) )
            countBackFromMaturity = self.__sixMonthsBack( countBackFromMaturity )
        
        """    
        if self.months >= 12:
            # Coupon baring bond
            numberOfCoupons = self.months / 6
            #print "numberOfCoupons", numberOfCoupons
            for couponDate in range( 1, numberOfCoupons ):
                couponVector.append( la.Coupon( couponValue, couponDate * 0.5 ) )
            couponVector.append( la.Coupon( principalValue + couponValue, numberOfCoupons * 0.5 ) )
            #print "Returning Cloned Coupon Bond..."
        else:
            #print "Maturity of ZCB:", float(self.months)/12.0
            couponVector.append( la.Coupon( principalValue, float(self.months) / 12.0 ) )
            #print "Returning Cloned Zero Bond..."
        """
        
        return la.Bond( self.price / parValue, couponVector )
        
class BloombergHtmlParser(SGMLParser):
    
    __BloombergBondFunctionIndexer =  [ "setMonths", "setCoupon", "setMaturity", "setCurrentPriceAndYield", \
                                        "setTime" ]                                
    __SpanExclusionList = [ "COUPON", "MATURITY", "DATE", "CURRENT", "PRICE/YIELD", "CHANGE", "TIME", "CURRENT VALUE", \
                            "CURRENTVALUE:" ]
    
    BondList = []
    
    def reset(self):
        SGMLParser.reset(self)
        self.__inside_table_span = False
        # YUK! - Price/Yield Change field uses extra HTML
        # for colour - we don't need it so we ignore it
        self.__bad_change_field = False
        # Set when we hit the last <span> in a Price/Yield
        # field - this tells the end_span to reset bad_change_field
        self.__release_bad_change_field = False
        self.__bond_data = False
        # More tedium due to inconsistent format of Bloomberg webpage
        self.__moreToDo = True
        self.__index = 0
    
    def start_span(self, attrs):
        for tuple in attrs: 
            if tuple[0] == "class":
                #print "Found a class in <span>"
                if "tbl_" in tuple[1]: 
                    #print tuple[1], "is a table class!"
                    self.__inside_table_span = True
                if "green" in tuple[1] or "red" in tuple[1]:
                    self.__bad_change_field = True
                    self.__release_bad_change_field = True
        
    def end_span(self):
           if self.__bond_data == True and self.__index >= len( self.__BloombergBondFunctionIndexer ):
               #print "Appending bond to list"
               self.BondList.append( self.__newBond )
               self.__bond_data = False
               self.__index = 0
           if self.__release_bad_change_field == True:
               self.__bad_change_field = self.__release_bad_change_field = False
           self.__inside_table_span = False
           
    def handle_data(self, data):
        data = re.sub("\s+", "", data)
        #print "Data:"
        #print data
        #print "inside_table_span:", self.__inside_table_span
        #print "bad_change_field:", self.__bad_change_field
        #print "data not in exclusion:", not data in self.__SpanExclusionList
        #print "more to do:", self.__moreToDo
        naInChange = self.__index == 4 and (data == "/" or "N.A." in data)
        #print "naInChange:", naInChange, "index:", self.__index
        if self.__inside_table_span and not self.__bad_change_field and not data in self.__SpanExclusionList and self.__moreToDo and not naInChange:
            #print "Inside table span of interest"
            if self.__bond_data == False:
                #print
                #print "Creating new bond"
                self.__newBond = BloombergBond()
                self.__bond_data = True
            #print self.__index
            self.__newBond.returnMemberReference( self.__BloombergBondFunctionIndexer[ self.__index ] )( data )
            self.__index += 1
            #print re.sub("\s+", "", data)
        elif "CURRENTVALUE" in data:
            # This is a mess - this data will occur after the
            # the last bond, although it's caught itself
            # subsequent fields might not be so tell
            # the parser to ignore everything else.
            #print "And we're done!:", data
            self.__moreToDo = False
            return
            
            
          


if __name__ == '__main__':
    usock = urllib.urlopen("http://www.bloomberg.com/markets/rates/uk.html")
    BloombergParser = BloombergHtmlParser();
    BloombergParser.feed( usock.read() )
    usock.close()
    BloombergParser.close()
    for bond in BloombergParser.BondList:
        print bond
        
    
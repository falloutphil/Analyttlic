/*
 *  coupon.cpp
 *  bootsrapper
 *
 *  Created by Philip Beadling on 15/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <math.h>

#include "coupon.h"

using namespace std;
//using namespace boost::python;

Coupon::Coupon( const double value, const double maturity ) : value( value ), maturity ( maturity ) 
{
	//cout << "\nCoupon contructor called";
};

// Needed by Py++
bool Coupon::operator==( const Coupon& rhs ) const
{
	return ( (value == rhs.value) && (maturity == rhs.maturity));
}


double Coupon::pv( const double r ) const
{
	return ( value * exp( -r * maturity ) );
}

double Coupon::getMaturity() const
{
	return ( maturity );
}

double Coupon::getValue() const
{
	return ( value );
}

double Coupon::getSortItem() const
{
	return ( maturity );
}

/*
Coupons::Coupons() : coupons( objects )
{
	
}

void Coupons::set( boost::python::list list )
 {
    coupons.clear();
    	 
    int listLength = extract<int>( list.attr( "__len__" )() );
    //std::cout << "List length: " << listLength;
    for( int  i=0; i < listLength; ++i )
    {
       	//std::cout << "\nPush back list item: " << i;
       	extract<Coupon> x( list.pop( 0 ) );
        if( x.check() ) 
        {
           	//std::cout << "\nValue: " << x().getValue () << " Maturity: " << x().getMaturity();
           	coupons.push_back( x() );
        } 
     }  
}
    
const std::vector<Coupon>& Coupons::getVector() const
{
	return coupons;
}
*/

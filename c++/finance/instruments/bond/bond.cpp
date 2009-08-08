/*
 *  bond.cpp
 *  bootsrapper
 *
 *  Created by Philip Beadling on 01/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "bond.h"



#include <vector>
#include <math.h>
#include <iostream>



using namespace std;
//using namespace boost::python;


Bond::Bond( const double marketPrice, const vector<Coupon>& _coupons ) 
	: NewtonRaphson( 1e-6, 1000), QuickSort<Coupon>( _coupons ), marketPrice( marketPrice ), coupons( objects ), givenYield( 0.0 ) 
{
	//cout << "\nBond contructor called";
}

/*
Bond::Bond( const double marketPrice, const Coupons& _coupons ) 
	: NewtonRaphson( 1e-16, 1000), QuickSort<Coupon>( _coupons.getVector() ), marketPrice( marketPrice ), coupons( objects ) 
{
	//cout << "\nBond contructor called";
}
*/
 
Bond::Bond(const Bond& other) 
	: NewtonRaphson( 1e-6, 1000), QuickSort<Coupon>( other.coupons ), marketPrice( other.marketPrice ), coupons( objects )
{
	//cout << "\nBond copy constructor called";
}
 
Bond& Bond::operator=(const Bond& other)
{
	//cout << "\nBond assignment operator called";
	if ( this != &other )
	{
		marketPrice = other.marketPrice;
		objects = other.objects;
		coupons = objects;
	}
	// Return yourself just in case something
	// is defined by the result of the assignment a=(b=c)
	// you'd want a=b which is now the value of c, a = b.operator=(c)
	// This is not returned as a const referance to allow chaining of = with objects
	// being returned writable (a bit odd, but 'do what the ints do').
	return *this;
}

bool Bond::operator==( const Bond& rhs )
{		
	return ( (marketPrice==rhs.marketPrice) && (coupons==rhs.coupons) );
}


double Bond::ytm() const
{
	return solve( 0.05 ); 
}

double Bond::duration( const double r ) const
{
	return dervOfFunction( r );	
}

int Bond::numberOfCoupons() const
{
	return static_cast<int>(coupons.size());
}

void Bond::sortCouponsByDate()
{
	sort( 0, numberOfCoupons() - 1 );
}

void Bond::printCoupons() const
{
	for( vector<Coupon>::iterator iter = coupons.begin(); iter != coupons.end();  ++iter )
	{
		cout << "\nCoupon: " << iter->getMaturity() << " Value: " << iter->getValue();
	}
}

double Bond::maturityIfCouponsAreSorted() const
{
	return getSortItem();
}

double Bond::function( const double x ) const
{
	double pv = 0.0;
	for( vector<Coupon>::iterator couponIter = coupons.begin(); couponIter != coupons.end(); ++couponIter )
	{
		// Sum( Ci*(exp(-yTi) )
		pv += couponIter->pv( x );
	}
	
	return ( pv - marketPrice );
}

double Bond::dervOfFunction( const double x ) const
{
	double duration = 0.0;
	for( vector<Coupon>::iterator couponIter = coupons.begin(); couponIter != coupons.end(); ++couponIter )
	{
		// Sum( Ci*(Ti)(exp(-yTi) )
		duration -= couponIter->getMaturity() * couponIter->pv( x );
	}
	
	return ( duration );
}


double Bond::getSortItem() const
{
	return coupons.back().getMaturity();
}


/*
Bonds::Bonds() : bonds( objects )
{
	
}

void Bonds::set( boost::python::list list )
 {
    bonds.clear();
    	 
    int listLength = extract<int>( list.attr( "__len__" )() );
    // THIS MAKES NO SENSE AT ALL
    // You're not getting clean arrays
    // so this pop is a poor attempt at removing 
    // some weird nan that shouldn't even be here!
    extract<Bond> x( list.pop( 0 ) );
    std::cout << "List length: " << listLength;
    for( int  i=0; i < listLength - 1; ++i )
    {
       	std::cout << "\nPush back list item: " << i;
       	extract<Bond> x( list.pop( 0 ) );
        if( x.check() ) 
        {
           	bonds.push_back( x() );
        } 
     }  
}
    
const std::vector<Bond>& Bonds::getVector() const
{
	return bonds;
}
*/


void Bond::test()
{
	cout << "\nCreate coupons vector";
	vector<Coupon> coupons;
	coupons.push_back( Coupon(1.03, 5.0) );
	for (double i=0.5;i<4.6;i+=0.5)
	{
		coupons.push_back( Coupon(0.03, i) );
	}
	
	
	cout << "\nCreate bond from coupons";

	Bond myBond( 0.9600, coupons );

	cout << "\nBEFORE:";
	myBond.printCoupons();
	myBond.sortCouponsByDate();
	cout << "\nAFTER:";
	myBond.printCoupons();


	cout << "\nGet YTM of bond";
	
	double ytm = myBond.ytm();
	cout << "\n\nYield: " << ytm*100;
	
	vector<Bond> bonds;
	vector<Coupon> cb1, cb2, cb3, cb4, cb5, cb6, cb7, cb8;
	cb7.push_back( Coupon(1, 7) );
	Bond b7( 0.5288, cb7 );
	bonds.push_back( b7 );
	cb8.push_back( Coupon(1, 10) );
	Bond b8( 0.3985, cb8 );
	bonds.push_back( b8 );
	cb1.push_back( Coupon(1, 0.25) );
	Bond b1( 0.9809, cb1 );
	bonds.push_back( b1 );
	cb2.push_back( Coupon(1, 0.5) );
	Bond b2( 0.9612, cb2 );
	bonds.push_back( b2 );
	cb3.push_back( Coupon(1, 1) );
	Bond b3( 0.9194, cb3 );
	bonds.push_back( b3 );
	cb4.push_back( Coupon(1, 2) );
	Bond b4( 0.8436, cb4 );
	bonds.push_back( b4 );
	cb5.push_back( Coupon(1, 3) );
	Bond b5( 0.7772, cb5 );
	bonds.push_back( b5 );
	cb6.push_back( Coupon(1, 5) );
	Bond b6( 0.644, cb6 );
	bonds.push_back( b6 );

	
	
	for( vector<Bond>::iterator bondIter = bonds.begin(); bondIter != bonds.end();  ++bondIter )
	{
		cout <<  "\nCalculating...";
		double myYtm = bondIter->ytm()*100;
		cout << "\nNumber of coupons: " << bondIter->numberOfCoupons();
		bondIter->printCoupons();
		cout << "\nYield To Maturity(%): " << myYtm;
	}
	

}


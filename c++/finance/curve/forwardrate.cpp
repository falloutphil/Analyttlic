/*
 *  forwardrate.cpp
 *  bootsrapper
 *
 *  Created by Philip Beadling on 01/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */


#include <vector>
#include <iostream>


#include "forwardrate.h"

#include "../../maths/basic/cartesian.h"

using namespace std;

ForwardRate::ForwardRate( const double time, const double rate ) : time( time ), rate( rate )
{
}


ForwardRateCurve::ForwardRateCurve( vector<Bond>& _bonds ) 
	: QuickSort<Bond>( _bonds ), bonds( objects ) 
{
	//cout << "\nForwardRates contructor called";

	// Put bonds in order of maturity
	sortBondsByMaturity();
	
	vector<Bond>::iterator bondIter = bonds.begin();
	//cout << "\n\nCalculating YTM for bond with maturity: " << bondIter->maturityIfCouponsAreSorted();
	points.push_back( dCartesian2D( bondIter->maturityIfCouponsAreSorted(), bondIter->ytm() ) );
	++bondIter;
	for( ; bondIter != bonds.end();  ++bondIter )
	{ 
		double currentTimeToMaturity = bondIter->maturityIfCouponsAreSorted();
		//cout << "\n\nCalculating YTM for bond with maturity: " << currentTimeToMaturity;
		double current = bondIter->ytm()*currentTimeToMaturity;
		--bondIter;
		double previousTimeToMaturity = bondIter->maturityIfCouponsAreSorted();
		double before =  bondIter->ytm()*previousTimeToMaturity;
		++bondIter;
		points.push_back( dCartesian2D( currentTimeToMaturity, (current-before)/(currentTimeToMaturity-previousTimeToMaturity) ) );
	}
}

/*
ForwardRateCurve::ForwardRateCurve( Bonds& _bonds ) 
	: QuickSort<Bond>( _bonds.getVector() ), bonds( objects ) 
{
	//cout << "\nForwardRates contructor called";

	// Put bonds in order of maturity
	sortBondsByMaturity();
	
	vector<Bond>::iterator bondIter = bonds.begin();
	cout << "\n\nCalculating YTM for bond with maturity: " << bondIter->maturityIfCouponsAreSorted();
	points.push_back( dCartesian2D( bondIter->maturityIfCouponsAreSorted(), bondIter->ytm() ) );
	++bondIter;
	for( ; bondIter != bonds.end();  ++bondIter )
	{ 
		double currentTimeToMaturity = bondIter->maturityIfCouponsAreSorted();
		cout << "\n\nCalculating YTM for bond with maturity: " << currentTimeToMaturity;
		double current = bondIter->ytm()*currentTimeToMaturity;
		--bondIter;
		double previousTimeToMaturity = bondIter->maturityIfCouponsAreSorted();
		double before =  bondIter->ytm()*previousTimeToMaturity;
		++bondIter;
		points.push_back( dCartesian2D( currentTimeToMaturity, (current-before)/(currentTimeToMaturity-previousTimeToMaturity) ) );
	}
}
*/

void ForwardRateCurve::sortBondsByMaturity()
{
	sort( 0, static_cast<int>(bonds.size()) - 1 );
}




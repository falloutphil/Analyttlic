/*
 *  dividedDifference.cpp
 *  Bond
 *
 *  Created by Philip Beadling on 23/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
 
#include <iostream>

#include "dividedDifference.h"

using namespace std;


DividedDifference::DividedDifference(  const dSetCartesian2D& coordinates ) : InterpolationBase( coordinates )
{
	//cout << "\nDD Constructor called";
	
	// We need an even number here - need to think about that! Do we? Nah?
	int currentVectorSize = coordinates.size();
	
	differenceTable.resize( currentVectorSize );
	
	differenceTable[0].resize( currentVectorSize );
	for( int i=0; i < currentVectorSize; ++i )
	{
		differenceTable[0][i] = coordinates[i].y;
	}
	// One down, the rest can be looped
	--currentVectorSize;
	// We will have as many columnns as we have forward rates 
	// but we've done the first one
	for( unsigned int column=1; column < coordinates.size() ; ++column )
	{
		differenceTable[column].resize( currentVectorSize );
		for( int row=0; row < currentVectorSize; ++row )
		{
			differenceTable[column][row] = 
				( differenceTable[column-1][row+1] - differenceTable[column-1][row] ) / ( coordinates[column+row].x - coordinates[row].x );
		}
		--currentVectorSize;
	}
}

double DividedDifference::getInterpolatedRate( double x ) const
{
	
	double rate = differenceTable[0][0];
	
	for( unsigned int i=1; i< coordinates.size(); ++i )
	{
		double xPoly = 1;
		
		for( unsigned int j=0; j < i; ++j )
		{
			xPoly *= ( x - coordinates[j].x );
		
		}
		
		rate += ( xPoly * differenceTable[i][0] );
	}
	
	return rate;
}



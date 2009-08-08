/*
 *  lagrange.cpp
 *  Bond
 *
 *  Created by Philip Beadling on 22/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>

#include "lagrange.h"

using namespace std;



Lagrange::Lagrange(const dSetCartesian2D& coordinates  ) : InterpolationBase( coordinates )
{
	// We can probably take some of the weight out the interpolation function here?
}

double Lagrange::getInterpolatedRate( double x )  const
{	
	vector<double> lOnX;
	vector<double> lOnX_k;
	// Assign '1' to all 'l' functions
	lOnX.assign( coordinates.size(), 1 );
	lOnX_k.assign( coordinates.size(), 1 );
	double p = 0;
	for( unsigned int k=0; k<coordinates.size(); k++ )
	{
		for( unsigned int i=0; i<coordinates.size(); i++ )
		{
			if ( k != i )
			{
				lOnX[k] *= ( x - coordinates[i].x );
				// Perhaps this can be precalculated?
				lOnX_k[k] *= ( coordinates[k].x - coordinates[i].x );
			}
			//cout << "\nlOnX[" << k << "] = " << lOnX[k];
			//cout << "\nlOnX_k[" << k << "] = " << lOnX_k[k];
		}
		double L = lOnX[k] / lOnX_k[k];
		//cout << "\nL[" << k << "] = " << L;
		p += L * coordinates[k].y;
	}
	
	return p;
}


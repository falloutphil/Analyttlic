/*
 *  cubicSpline.cpp
 *  Bond
 *
 *  Created by Philip Beadling on 29/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <math.h>

#include "cubicSpline.h"

using namespace std;


CubicSpline::CubicSpline( const dSetCartesian2D& coordinates ) 
	: InterpolationBase( coordinates ), augmentedLinearEquations( coordinates.size() - 2, coordinates.size() - 1 )
	// We have forwardRates.size()=N+1 points but matrix is m1 -> m_N-1 + u column = N-1 + 1 = N.  Thus we have (N+1)-2 = N-1 dim.
{
	const unsigned int N = coordinates.size() - 1;
	
	// Vector of h=x_k - x_k+1
	for( unsigned int k=0; k < N; ++k )
	{
		h.push_back( coordinates[k+1].x - coordinates[k].x );
	}
	// Vector of 2(h_k + h_k+1)
	for( unsigned int k=0; k < N; ++k )
	{ 
		twoTimesAdjacentH.push_back( 2 * ( h[k] + h[k+1] ) );
	}
	// Vector of d_k = ( y_k+1 - y_k ) / h_k
	for( unsigned int k=0; k < N; ++k )
	{ 
		d.push_back( ( coordinates[k+1].y - coordinates[k].y ) / h[k] );
	}
	// Vector of u_k = 6( d_k - d_k-1 )
	for( unsigned int k=1; k < N+1; ++k )
	{ 
		u.push_back( 6 * ( d[k] - d[k-1] ) );
	}
	

	for( unsigned int i=0; i < N-1; ++i )
	{
		for( unsigned int j=0; j < N-1; ++j )
		{
			if ( i == j )
			{
				//Main diagonal

			}
			else if ( ( i - j ) == 1 )
			{
				//Lower diagonal
				augmentedLinearEquations(i,j) = h[i+1];
			}
			else if ( ( j - i ) == 1 )
			{
				//Upper diagonal
				augmentedLinearEquations(i,j) = h[i];
			}
			else
			{
				augmentedLinearEquations(i,j) = 0;
			}
			
		}
		augmentedLinearEquations(i,N-1) = u[i];
	
	}
	
	cout << augmentedLinearEquations;
	
	augmentedLinearEquations.gaussElimination();
	
	cout << augmentedLinearEquations;
	
	vector<double> results = augmentedLinearEquations.backSubstitute();
	
	// Let's start with a natural spline
	// let m_0=m_N = 0
	m.push_back(0);
	for (unsigned int i=0;i<results.size();++i)
		m.push_back(results[i]);
	m.push_back(0);
	
	
}



double CubicSpline::getInterpolatedRate( double x ) const
{
	// Work out which cubic section we need
	unsigned int k=0;
	while( coordinates[k+1].x < x )
	{
		//cout << "\nforwardRates[k].time: " << forwardRates[k].time << " time: " << time;
		++k;
	}
	//cout << "\nFor time: " << time << " Using k: " << k;
	
	const double s_k0 = coordinates[k].y;
	const double s_k1 = d[k] - ( ( h[k] * ( (2 * m[k] ) + m[k+1] ) / 6 ) );
	const double s_k2 = m[k] / 2;
	const double s_k3 = ( m[k+1] - m[k] ) / ( 6 * h[k] );
	return ( s_k0 + ( s_k1 * ( x - coordinates[k].x ) ) + 
					( s_k2 * pow( ( x - coordinates[k].x ), 2 ) ) + 
					( s_k3 * pow( ( x - coordinates[k].x ), 3 ) ) );

}


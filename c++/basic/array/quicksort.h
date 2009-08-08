/*
 *  quicksort.h
 *  bootsrapper
 *
 *  Created by Philip Beadling on 15/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <iostream>

template <class T_OBJECT>
class QuickSort;

template<class T_SORTABLE>
class IQuickSortable
{			
	protected:
		virtual ~IQuickSortable() {};
		typedef T_SORTABLE sortableType;
		template <class T_OBJECT> friend class QuickSort;
		virtual sortableType getSortItem() const=0;
};

template <class T_OBJECT>
class QuickSort
{
	protected:
		QuickSort(  const std::vector< T_OBJECT >& objects ) : objects( objects ) 
		{
			//std::cout << "\nQuickSort contructor called";
		}
		
		//void sort( int top, int bottom );

		void sort( int top, int bottom )
		{
			// top = subscript of beginning of vector being considered
			// bottom = subscript of end of vector being considered
			// this process uses recursion - the process of calling itself
			//std::cout << "\nsort called";
			int middle;
			if (top < bottom)
			{
				middle = partition(top, bottom);
				sort(top, middle);   // sort top partition
				sort(middle+1, bottom);  // sort bottom partition
			}
			return;
		}

		//int partition( int top, int bottom );

		int partition(int top, int bottom)
		{
			// dynamic_cast is good for two reasons - ensures that our objects are children of
			// IQuickSortable<sortableType>, and it prevents the possibility that the object itself (I think)
			// has visibility of two getSortItem functions as it is a sorter AND can be sorted (see Bond for example).
			typename T_OBJECT::sortableType x 
				= dynamic_cast< IQuickSortable< typename T_OBJECT::sortableType >& > (objects[top]).getSortItem();

			int i = top - 1;
			int j = bottom + 1;
			do
			{
				do     
				{
                  j--;
				} while(x < dynamic_cast< IQuickSortable< typename T_OBJECT::sortableType >& > (objects[j]).getSortItem());

				do  
				{
                 i++;
				} while(x > dynamic_cast< IQuickSortable< typename T_OBJECT::sortableType >& > (objects[i]).getSortItem());

				if (i < j)
				{ 
                 //std::cout << "\nSwapping objects " << i << " and " << j;
				 T_OBJECT temp( objects[i] );    // switch elements at positions i and j
                 objects[i] = objects[j];
                 objects[j] = temp;
				}
			} while(i < j);    
			
			return j;           // returns middle index
		}

		std::vector<T_OBJECT> objects;	
};


#endif

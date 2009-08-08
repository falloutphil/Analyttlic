/*
 *  quicksort.cpp
 *  bootsrapper
 *
 *  Created by Philip Beadling on 15/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>

#include "quicksort.h"

using namespace std;

// This screws up if I take it out the header!
/*
template <class T_OBJECT, class T_SORTABLE> 
QuickSort<T_OBJECT, T_SORTABLE>::QuickSort(  const vector< T_OBJECT >& objects ) : objects( objects ) 
{
	cout << "\nQuickSort contructor called";
}
*/

/*
template <class T_OBJECT, class T_SORTABLE>
void QuickSort<T_OBJECT, T_SORTABLE>::sort( int top, int bottom )
{
      // top = subscript of beginning of vector being considered
      // bottom = subscript of end of vector being considered
      // this process uses recursion - the process of calling itself
     int middle;
     if (top < bottom)
    {
          middle = partition(top, bottom);
          sort(top, middle);   // sort top partition
          sort(middle+1, bottom);  // sort bottom partition
     }
     return;
}
*/

/*
template <class T_OBJECT, class T_SORTABLE>
int QuickSort<T_OBJECT, T_SORTABLE>::partition(int top, int bottom)
{
     T_SORTABLE x = objects[top].getSortItem();
     int i = top - 1;
     int j = bottom + 1;
     do
     {
           do     
           {
                  j--;
           } while(x < objects[j].getSortItem());

          do  
         {
                 i++;
          } while(x > objects[i].getSortItem());

          if (i < j)
         { 
                 T_OBJECT temp( objects[i] );    // switch elements at positions i and j
                 objects[i] = objects[j];
                 objects[j] = temp;
         }
     } while(i < j);    
     return j;           // returns middle index
}
*/


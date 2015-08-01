// bogosort.h
// Chris Bowers

/**
 *	This is an implementation of bogosort.
 */

#ifndef __BOGOSORT_H__
#define __BOGOSORT_H__

#include <algorithm>

template<typename Iterator>
void bogosort(Iterator first, Iterator last){
	while (!std::is_sorted(first, last))
		std::random_shuffle(first, last);
}

#endif // __BOGOSORT_H__

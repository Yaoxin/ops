/*
 * common.h
 *
 *  Created on: 2015-1-22
 *      Author: fyliu
 */

#ifndef OPS_COMMON_H_
#define OPS_COMMON_H_

#include <assert.h>

#define OPS_ASSERT(condition)	assert(condition);

template<class T>
inline T ops_max(T t1, T t2) {
	return (t1 < t2) ? t2 : t1;
}

template<class T>
inline T ops_min(T t1, T t2)
{
	return (t1 < t2)?t1:t2;
}

#endif /* OPS_COMMON_H_ */

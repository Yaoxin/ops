/*
 * ops_array.h
 *
 *  Created on: 2015-1-22
 *      Author: fyliu
 */

#ifndef	__OPS_ARRAY_H_
#define	__OPS_ARRAY_H_
#include <assert.h>
#include <iostream>

template<class T>
class array {
public:
	array(int num) {
		len = num;
		a = new T[len];
	}
	~array() {
		if (a != NULL)
			delete[] a;
	}
	int length();
	T& operator[](int i);
	array<T>& operator=(array<T> &);
	//friend array<T> operator+(const array<T>& t1, const array<T>& t2);

private:
	T *a;
	int len;
};

template<class T>
int array<T>::length() {
	return len;
}

template<class T>
T& array<T>::operator [](int i) {
	assert(i >= 0 && i < len);
	return a[i];
}

template<class T>
array<T>& array<T>::operator =(array<T> & b) {
	if (this == &b)
		return *this;
	if (a != NULL)
		delete[] a;
	a = b.a;
	b.a = NULL;
	len = b.len;
	return *this;
}

#endif

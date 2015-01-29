/*
 * ops_array_deque.h
 *
 *  Created on: 2015-1-23
 *      Author: fyliu
 */

#ifndef OPS_ARRAY_DEQUE_H_
#define OPS_ARRAY_DEQUE_H_

#include <assert.h>
#include "ops_array.h"
#include "ops_common.h"

//deque can add or remove any location
template<class T>
class array_deque {
public:
	array_deque() :
		a(1) {
		j = 0;
		n = 0;
	}
	array_deque(int b):a(b){
		j = 0;
		n = 0;
	}
	int size() {
		return n;
	}
	T get(int i);
	T set(int i, T x);
	void add(int i, T x);//O(1 + min(i , n - i))
	T remove(int i);//O(1 + min(i, n - i))
	void resize(int num, T x);
private:
	void resize_auto();
	array<T> a;
	int j;
	int n;
};

//O(1)
template<class T>
T array_deque<T>::get(int i) {
	assert(i >= 0 && i < n);
	return a[(j + i) % a.length()];
}

//O(1)
template<class T>
T array_deque<T>::set(int i, T x) {
	assert(i >= 0 && i < n);
	T b = a[(j + i) % a.length()];
	a[(j + i) % a.length()] = x;

	return b;
}

template<class T>
void array_deque<T>::add(int i, T x) {
//	assert(i >= 0 && i < n);
	if (n + 1 > a.length())
		resize_auto();
	if (n / 2 < 0)//left shift
	{
//		j = (j != 0) ? j-- : (a.length() - 1);//it have warning about undefined
		if(j != 0){
			j--;
		}else
		{
			j = a.length() - 1;
		}
		for (int k = 0; k <= i - 1; k++) {
			a[(j + k) % a.length()] = a[(j + k + 1) % a.length()];
		}
	} else//right shift
	{
		for (int k = n; k > i; k--) {
			a[(j + k) % a.length()] = a[(j + k - 1) % a.length()];
		}
	}
	a[(j + i) % a.length()] = x;
	n++;
}

template<class T>
void array_deque<T>::resize(int num, T x) {
	if (n > num) {
		n = num;
		if (a.length() > 3 * n)
			resize_auto();
	} else {
		int m = n;
		n = num;
		if (num > a.length())
			resize_auto();
		for (int i = m; i < num; i++) {
			a[i] = x;
		}
	}
}

template<class T>
T array_deque<T>::remove(int i) {
//	assert(i >= 0 && i < n);
	T b = a[(j + i) % a.length()];
	if (n / 2)//left
	{
		for (int k = i; k > 0; k--) {
			a[(j + k) % a.length()] = a[(j + k - 1) % a.length()];
		}
		j = (j + 1) % a.length();
	} else {
		for (int k = i; k < n - 1; k++) {
			a[(j + k) % a.length()] = a[(j + k + 1) % a.length()];
		}
	}
	n--;

	if (a.length() > 3 * n)
		resize_auto();

	return b;
}

template<class T>
void array_deque<T>::resize_auto() {
	array<T> b(ops_max(2 * n, 1));
	for (int i = 0; i < n; i++) {
		b[i] = a[(j + i) % a.length()];
	}
	a = b;
	j = 0;
}

#endif /* OPS_ARRAY_DEQUE_H_ */

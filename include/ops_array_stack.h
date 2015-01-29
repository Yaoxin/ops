/*
 * ops_array_stack.h
 *
 *  Created on: 2015-1-22
 *      Author: fyliu
 */

#ifndef OPS_ARRAY_STACK_H_
#define OPS_ARRAY_STACK_H_

#include <assert.h>
//#include <algorithm>
#include "ops_array.h"
#include "ops_common.h"

template<class T>
class array_stack {
public:
	array_stack():a(1){ n = 0;}
	array_stack<T> & operator=(array_stack<T> &);
	int size() {
		return n;
	}
	T get(int i) {
		assert(i >= 0 && i < n);
		return a[i];
	}
	T set(int i, T x) {
		assert(i >= 0 && i < n);
		T y = a[i];
		a[i] = x;
		return y;
	}
	void add(int i, T x);
	T remove(int i);
private:
	void resize();
private:
	int n;
	array<T> a;
};

template<class T>
void array_stack<T>::add(int i, T x) {
	if (n + 1 > a.length())
		resize();
	//std::copy_backward(a[i], a[n], a[n+1]);
	for(int j = n; j > i; j--)
	{
		a[j] = a[j - 1];
	}
	a[i] = x;
	n++;
}

template<class T>
T array_stack<T>::remove(int i) {
	//std::copy(a[i+1], a[n], a[i]);
	T x = a[i];
	for(int j = i; j < n - 1; j++)
	{
		a[j] = a[j + 1];
	}
	n--;
	if (a.length() >= 3 * n)
		resize();
	return x;
}

template<class T>
void array_stack<T>::resize() {
	array<T> b(ops_max(2*n, 1));
	//std::copy(a[0], a[n], b);
	for(int i = 0; i < n; i++)
	{
		b[i] = a[i];
	}
	a = b;
}

template <class T>
array_stack<T>& array_stack<T>::operator= (array_stack<T> & as)
{
	if(this == &as)
	{
		return *this;
	}
	a = as.a;
	n = as.n;

	return *this;
}

#endif /* OPS_ARRAY_STACK_H_ */

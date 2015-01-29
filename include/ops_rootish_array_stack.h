/*
 * ops_rootish_array_stack.h
 *
 *  Created on: 2015-1-27
 *      Author: fyliu
 */

#ifndef OPS_ROOTISH_ARRAY_STACK_H_
#define OPS_ROOTISH_ARRAY_STACK_H_
#include <cmath>
#include <iostream>
#include "ops_array_stack.h"


template<class T>
class rootish_array_stack {
public:
	rootish_array_stack(){n = 0;}
	~rootish_array_stack();
	T get(int i) {
		int b = itob(i);
		int j = i - b * (b + 1) / 2;
		return blocks.get(b)[j];
	}
	T set(int i, T x) {
		int b = itob(i);
		int j = i - b * (b + 1) / 2;
		T y = blocks.get(b)[j];
		blocks.get(b)[j] = x;

		return y;
	}
	void add(int i, T x);
	T remove(int i );
	void print();
private:
	int itob(int i) {
		double db = (-3.0 + sqrt(9 + 8 * i)) / 2.0;
		int b = ceil(db);// upward
		return b;
	}
	void grow();
	void shrink();
private:
	array_stack<T*> blocks;
	int n;
};

template<class T>
rootish_array_stack<T>::~rootish_array_stack()
{
	n = 0;
	shrink();
}

template<class T>
void rootish_array_stack<T>::add(int i, T x) {
	int r = blocks.size();
	if(r*(r + 1)/2 < n + 1)
		grow();
	n++;
	for(int j = n - 1; j > i; j--)
	{
		set(j, get(j - 1));
	}
	set(i, x);
}

template<class T>
T rootish_array_stack<T>::remove(int i)
{
	T x = get(i);
	for(int j = i; j < n - 1; j++ )
	{
		set(j, get(j+1));
	}
	n--;
	int r = blocks.size();
	if((r - 2)*(r -1)/2 >= n)
		shrink();
	return x;
}

template <class T>
void rootish_array_stack<T>::grow()
{
	blocks.add(blocks.size(), new T[blocks.size() + 1]);
}

template<class T>
void rootish_array_stack<T>::shrink()
{
	int r = blocks.size();
	while(r > 0 && (r -2)*(r -1)/2 >= n)
	{
		delete []blocks.remove(blocks.size() - 1);
		r--;
	}
}

template <class T>
void rootish_array_stack<T>::print()
{
	int r = blocks.size();
	for(int i = 0; i < r; i++)
	{
		std::cout << "block " << i << std::endl;
		for(int j = 0; j < i + 1; j++)
		{
			int elem = i *(i + 1)/2 + j;
			std::cout <<" "<< "elem "<< "j= "<< get(elem) << std::endl;
		}
	}
}

#endif /* OPS_ROOTISH_ARRAY_STACK_H_ */

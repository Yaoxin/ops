/*
 * ops_dual_array_deque.h
 *
 *  Created on: 2015-1-26
 *      Author: fyliu
 */

#ifndef OPS_DUAL_ARRAY_DEQUE_H_
#define OPS_DUAL_ARRAY_DEQUE_H_
#include "ops_array_stack.h"
#include <iostream>

template<class T>
class dual_array_deque {
public:
	int size() {
		return front.size() + back.size();
	}
	//	O(1)
	T get(int i) {
		assert(i >= 0 && i < size());
		if (i < front.size()) {
			return front.get(front.size() - i - 1);
		} else {
			return back.get(i - front.size());
		}
	}
	//	O(1)
	T set(int i, T x) {
		assert(i >= 0 && i < size());

		if (i < front.size()) {
			return front.set(front.size() - i - 1);
		} else {
			return back.set(i - front.size());
		}
	}
	void add(int i, T x);
	T remove(int i);
private:
	void balance();
private:
	array_stack<T> front;//store them is reserve order
	array_stack<T> back;//store them is normal order
};

template<class T>
void dual_array_deque<T>::add(int i, T x) {
//	assert(i >= 0 && i < size());
	if (i < front.size()) {
		front.add(front.size() - i - 1, x);
	} else {
		back.add(i - front.size(), x);
	}
	balance();
}

template<class T>
T dual_array_deque<T>::remove(int i) {
//	assert(i >= 0 && i < size());
	T x;
	if (i < front.size()) {
		x =  front.remove(front.size() - i - 1);
	} else {
		x =  back.remove(i - front.size());
	}
	balance();
	return x;
}

template <class T>
void dual_array_deque<T>::balance()
{
	std::cout << "front.size()" << front.size() << "back.size()" << back.size() << std::endl;
	if(3*front.size() < back.size() || 3*back.size() < front.size())
	{
		std::cout << "balance start" << std::endl;
		int n = front.size() + back.size();
		int nf = n/2;
		array_stack<T> af;
		for(int i = 0; i < nf; i ++)
		{
			af.add(i, get(i));
		}
		array_stack<T> ab;
		int nb = n - nf;
		for(int i = 0; i < nb; i++)
		{
			ab.add(i, get(i + nf));
		}
		front = af;
		back = ab;
	}
}

#endif /* OPS_DUAL_ARRAY_DEQUE_H_ */

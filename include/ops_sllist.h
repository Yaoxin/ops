/*
 * ops_sllist.h
 *
 *  Created on: 2015-1-28
 *      Author: fyliu
 */

#ifndef OPS_SLLIST_H_
#define OPS_SLLIST_H_

#include <cassert>


template<classt T>
class Node {
public:
	T x;
	Node<T> *next;
	Node(T a) {
		x = a;
		next = NULL;
	}
};

template<class T>
class sllist {
public:
	sllist() {
		head = NULL;
		tail = NULL;
		n = 0;
	}
	~sllist()
	{
		for(;n>0;n--)
		{
			remove();//O(n)
		}
	}
	T push(T x);//stack head O(1)
	T pop();//stack head O(1)
	T remove();//FIFO head O(1)
	void add(T x)// FIFO tail O(1)
private:
	Node<T> *head;
	Node<T> *tail;
	int n;
};

template<class T>
T sllist<T>::push(T x) {
	Node<T> *u = new Node<T> (x);
	u->next = head;
	head = u;
	if (n == 0) {
		tail = u;
	}
	n++;
	return x;
}

template<class T>
T sllist<T>::pop() {
	assert(n > 0);
	Node<T> *u = head;
	T x = head->x;
	head = head->next;
	delete u;
	if (--n == 0)
		tail = NULL;
}

template<class T>
T sllist<T>::remove() {
	assert(n > 0);
	Node<T> *u = head;
	T x = head->x;
	head = head->next;
	delete u;
	if (--n == 0)
		tail = NULL;
}

template<class T>
void sllist<T>::add(T x) {
	Node<T> * u = new Node<T> (x);
	if (n == 0) {
		head = u;
	} else {
		tail->next = u;
	}
	tail = u;
	n++;
}
#endif /* OPS_SLLIST_H_ */

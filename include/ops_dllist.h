/*
 * ops_dllist.h
 *
 *  Created on: 2015-1-28
 *      Author: fyliu
 */

#ifndef OPS_DLLIST_H_
#define OPS_DLLIST_H_

#include <cassert>
#include <iostream>

template<class T>
class DNode {
public:
	DNode() {
		//		here how to init a
		prev = next = NULL;
	}
	DNode(T a) {
		x = a;
		prev = next = NULL;
	}
	T x;
	DNode<T> *prev, *next;
};

template<class T>
class dllist {
public:
	dllist() :
		n(0) {
		dummy.prev = &dummy;
		dummy.next = &dummy;
	}
public:
	T get(int i) {
		return getNode(i)->x;
	}
	T set(int i, T x) {
		DNode<T> *u = getNode(i);
		assert(u != NULL);
		T y = u->x;
		u->x = x;
		return y;
	}
	void add(int i, T x) {
		addBefore(getNode(i), x);
	}
	T remove(int i) {
		DNode<T> * u = getNode(i);
		assert(u != NULL);
		T y = u->x;
		remove(u);
		return y;
	}
	void print();

private:
	DNode<T> *getNode(int i);
	DNode<T> *addBefore(DNode<T> *w, T x);
	void remove(DNode<T> *w);
private:
	DNode<T> dummy;
	int n;
};

//O(1 + min{i, n - i}
template<class T>
DNode<T>* dllist<T>::getNode(int i) {
	//assert(i >= 0 && i < n);
	DNode<T> *p = NULL;
	if (i < n / 2) {
		p = dummy.next;
		for (int j = 0; j < i; j++)
			p = p->next;
	} else {
		p = &dummy;
		for (int j = n; j < i; j--)
			p = p->prev;
	}
	return p;
}

template<class T>
DNode<T> * dllist<T>::addBefore(DNode<T>*w, T x) {
	assert(w != NULL);
	DNode<T> * u = new DNode<T> (x);
	u->next = w;
	u->prev = w->prev;
	w->prev->next = u;
	w->prev = u;
	n++;
	return u;
}

template<class T>
void dllist<T>::remove(DNode<T> *w) {
	w->prev->next = w->next;
	w->next->prev = w->prev;
	delete w;
	n--;
}

template<class T>
void dllist<T>::print() {
	std::cout << "elem:" << std::endl;
	DNode<T> *u = dummy.next;
	for (int i = 0; i < n; i++) {
		std::cout << " " << u->x << std::endl;
		u = u->next;
	}
}

#endif /* OPS_DLLIST_H_ */

/*
 * ops_selist.h
 *
 *  Created on: 2015-1-29
 *      Author: fyliu
 */

#ifndef OPS_SELIST_H_
#define OPS_SELIST_H_
//a space-efficient list

#include "ops_array_deque.h"
#include <iostream>

#define		BLOCK_SIZE	10

template<class T>
class BDeque: public array_deque<T> {
public:
	BDeque(int b): array_deque<T>(b){}
	~BDeque() {
	}
	bool add(T x) {
		array_deque<T>::add(array_deque<T>::size(), x);
		return true;
	}
	void add(int i, T x) {
		array_deque<T>::add(i, x);
	}
private:
	void resize_auto() {
	}// do not shrink or grow
};

template<class T>
class BNode {
public:
	BNode(int b):d(b){
		prev = next = NULL;
	}
	BNode():d(1){
		prev = next = NULL;
	}
	BDeque<T> d;
	BNode<T> *prev, *next;
};

template <class T>
class location
{
public:
	location()
	{
		u = NULL;
		j = 0;
	}
	BNode<T> *u;
	int j;
};

template <class T>
class selist
{
public:
	selist(){
		dummy.prev = &dummy;
		dummy.next = &dummy;
		n = 0;
	}
	T get(int i);//getLocation
	T set(int i , T x);// getLocation
	void add(T x);// at the last
	void add(int i, T x);
	T remove(int i);
	void print();

private:
	void getLocation(int i, location<T> &ell);
	BNode<T> *addBefore(BNode<T>*w);
	void remove(BNode<T> *w);
	void spread(BNode<T> *w);
	void gather(BNode<T> *w);

private:
	BNode<T> dummy;
	int n;
};

template <class T>
void selist<T>::getLocation(int i , location<T> &ell)//O(1 + min{i, n -i}/b)
{
	if(i < n/2)
	{
		BNode<T> *u = dummy.next;
		while(i >= u->d.size())
		{
			i -= u->d.size();
			u = u->next;
		}
		ell.u = u;
		ell.j = i;
	}
	else
	{
		BNode<T> *u = &dummy;
		int idx = n;
		while(i < idx)
		{
			u = u->prev;
			idx -= u->d.size();
		}
		ell.u = u;
		ell.j = i - idx;
	}
}

template <class T>
T selist<T>::get(int i)
{
	T y;
	location<T> l;
	getLocation(i, l);
	if(l.u != NULL)
	{
		y = l.u->d.get(l.j);
	}
	return y;
}

template <class T>
T selist<T>::set(int i, T x)
{
	T y;
	location<T> l;
	getLocation(i, l);
	if(l.u != NULL)
	{
		y = l.u->d.set(l.j, x);
	}
	return y;
}

template <class T>
void selist<T>::add(T x){
	BNode<T> *last = dummy.prev;
	if(last == &dummy || last->d.size() == BLOCK_SIZE + 1)
		last = addBefore(&dummy);
	last->d.add(x);
	n++;
}

template <class T>
void selist<T>::add(int i, T x){
	if(i == n){//O(1)
		add(x);
		return;
	}
	location<T> l;
	getLocation(i, l);//O(1 + min{i, n-i}/b)
	BNode<T> *u = l.u;
	int r = 0;
	while(r < BLOCK_SIZE && u != &dummy && u->d.size() == BLOCK_SIZE + 1){//O(b)
		u = u->next;
		r++;
	}
	if(r == BLOCK_SIZE)
	{
		spread(l.u);//O(b(b+1)
		u = l.u;
	}
	else if(u == &dummy)//O(b)
	{
		u = addBefore(&dummy);
	}
	while(u != l.u)
	{
		u->d.add(0, u->prev->d.remove(u->prev->d.size() - 1));
		u = u->prev;
	}
	u->d.add(l.j, x);//O(1 + min{i, b - i})
	n++;
}

template <class T>
T selist<T>::remove(int i)
{
	location<T> l;
	getLocation(i, l);
	T y = l.d.get(l.j);
	BNode<T> *u = l.u;
	int r = 0;
	while(r < BLOCK_SIZE && u != &dummy && u->d.size() == BLOCK_SIZE - 1){
		u = u->next;
		r++;
	}
	if( r == BLOCK_SIZE)
	{
		gather(l.u);
	}
	u = l.u;
	u->d.remove(l.j);
	while(u->d.size() < BLOCK_SIZE - 1 && u->next != &dummy){
		u->d.add(u->next->d.remove(0));
		u = u->next;
	}
	if(u->d.size() == 0){
		remove(u);
	}
	n--;
}

template <class T>
void selist<T>::remove(BNode<T> *w)
{
	w->prev->next = w->next;
	w->next->prev = w->prev;
	delete w;
}

template <class T>
BNode<T> *selist<T>::addBefore(BNode<T>*w){
	assert(w != NULL);
	BNode<T> *u = new BNode<T> (BLOCK_SIZE + 1);
	u->next = w;
	u->prev = w->prev;
	w->prev->next = u;
	w->prev = u;
	return u;
}

template <class T>
void selist<T>::spread(BNode<T> *w)
{
	BNode<T> *u = w;
	for(int j = 0; j < BLOCK_SIZE; j++)//O(b)
	{
		u = u->next;
	}
	u = addBefore(u);
	while(u != w){//O(b)
		while(u->d.size() < BLOCK_SIZE)//O(b + 1)
		{
			u->d.add(0, u->prev->d.remove(u->prev->d.size() - 1));
		}
		u = u->prev;
	}
}

template <class T>
void selist<T>::gather(BNode<T> *w)
{
	BNode<T> *u = w;
	for(int j = 0; j < BLOCK_SIZE - 1; j++){
		while(u->d.size() < BLOCK_SIZE){
			u->d.add(u->next->d.remove(0));
		}
		u = u->next;
	}
	remove(u);
}

template <class T>
void selist<T>::print(){
	BNode<T> *u = dummy.next;
	int i = 0;
	while(u != &dummy){
		std::cout << "Block " << ++i << std::endl;
		for(int j = 0; j < u->d.size(); j++){
			std::cout << " ";
			std::cout << u->d.get(j);
		}
		std::cout << std::endl;
		u = u->next;
	}
}




#endif /* OPS_SELIST_H_ */

/*
 * ops_array_queue.h
 *
 *  Created on: 2015-1-22
 *      Author: fyliu
 */

#ifndef OPS_ARRAY_QUEUE_H_
#define OPS_ARRAY_QUEUE_H_
#include "ops_array.h"
#include "ops_common.h"

//very beautiful... FIFO
template <class T>
class array_queue
{
public:
	array_queue():a(1){
		cur = 0;
		n = 0;
	}
	int size(){return n;}
	void add(T x);
	T remove();
private:
	void resize();
private:
	array<T> a;
	int cur;
	int n;
};
//O(1)
template <class T>
void array_queue<T>::add(T x)
{
	if(n + 1 > a.length())
		resize();
	a[(cur + n)%a.length()] = x;
	n++;
}
//O(1)
template <class T>
T array_queue<T>::remove()
{
	T x = a[cur];
	cur = (cur + 1)%a.length();
	n--;

	if(a.length() > 3 *n)
		resize();
	return x;
}

template <class T>
void array_queue<T>::resize()
{
	array<T> b(ops_max(2*n, 1));
	for(int i = 0; i < n; i++)
	{
		b[i] = a[(cur +i)%a.length()];
	}
	a = b;
	cur = 0;
}




#endif /* OPS_ARRAY_QUEUE_H_ */

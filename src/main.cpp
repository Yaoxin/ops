/*
 * main.cpp
 *
 *  Created on: 2015-1-22
 *      Author: fyliu
 */

#include <iostream>
#include "ops_array_stack.h"
#include "ops_array_queue.h"
#include "ops_array_deque.h"
#include "ops_singleton_class.h"
#include "ops_trait_class.h"
#include "ops_dual_array_deque.h"
#include "ops_rootish_array_stack.h"
#include "ops_dllist.h"
#include "ops_selist.h"

using namespace std;

void test_for_array_stack() {
	array_stack<string> a;
	a.add(0, "abc");
	a.add(1, "bcd");
	a.add(2, "add");
	a.add(3, "dag");
	a.remove(3);

	int n = a.size();
	cout << "n = " << n << endl;
	for (int i = 0; i < n; i++) {
		cout << "a.get(" << i << ") = " << a.get(i) << endl;
	}
	/*
	 array_stack<string> s;
	 s.add(0, "good");
	 s.add(1, "daono");
	 s.add(2, "gagda");
	 s.add(3, "daonong");
	 s.remove(3);

	 n = s.size();
	 cout << "n = " << n << endl;
	 for (int i = 0; i < n; i++) {
	 cout << "a.get(" << i << ") = " << s.get(i) << endl;
	 }
	 */
}

void test_array_queue() {
	array_queue<int> q;
	for (int i = 0; i < 12; i++) {
		q.add(i);
	}
	int n = q.size();
	cout << "size = " << n << endl;
	for (int i = 0; i < n; i++) {
		cout << q.remove() << endl;
	}
	n = q.size();
	cout << "size = " << n << endl;
}

void test_array_deque() {
	array_deque<string> ds;
	ds.resize(10, "abc");
	//ds.resize(5);
	int n = ds.size();
	for (int i = 0; i < n; i++) {
		cout << ds.get(i) << endl;
	}
}

void test_dual_array_deque()
{
	dual_array_deque<int> da;
	for(int i = 0; i < 10; i++)
	{
		cout << "i= " << i << endl;
		da.add(i, i+2);
		cout <<da.size() << endl;
	}
	for(int i = 9; i > 0; i--)
	{
		da.remove(i);
		cout << "i= " << i << endl;
		cout <<da.size() << endl;
	}
}

void test_rootish_array_stack()
{
	rootish_array_stack<int> ras;
	for(int i = 0; i < 10; i++)
	{
		ras.add(i, i + 2);
	}
	ras.print();
	for(int i = 9; i >= 0; i--)
	{
		ras.remove(i);
	}
	ras.print();

	rootish_array_stack<string> rast;
	for(int i = 0; i < 10; i++)
	{
		rast.add(i, "abc");
	}
	rast.print();
	for(int i = 9; i >= 0; i--)
	{
		rast.remove(i);
	}
	rast.print();
}

void test_dllist()
{
	dllist<int> dl;
	for(int i = 0; i < 10; i++)
	{
		dl.add(i, i + 2);
	}
	dl.print();
	int a = dl.get(3);
	std::cout << "dl.get(3) = " << a << endl;
	dl.remove(3);
	dl.print();

	dllist<string> ds;
	for(int i = 0; i < 10; i++)
	{
		ds.add(i, "abc");
	}
	ds.print();
}

void test_selist()
{
	selist<int> sl;
	for(int i = 0; i < 110; i++){
		sl.add(i, i + 1);
	}
	sl.print();
	sl.add(3, 121);
	sl.print();
}

/*
 class MyClass:public SingletonClass<MyClass>
 {
 public:
 void print_myclass()
 {
 cout << "a" << a << "b " << b << endl;
 }
 public:
 MyClass()
 {
 a = 3;
 b = 4;
 }
 ~MyClass(){}

 private:
 int a;
 int b;

 };
 */

/*
template<class T>
class InnerClass {
public:
	static void DoTest() {
		cout << "hello world" << endl;
	}
};

template<class T>
class outClass {
public:
	template<class T2>
	void fun() {
		T2::DoTest();
	}
};

template <class T>
void DoTest(outClass<T> &out)
{
	out.template fun<InnerClass<T> >();
}

*/


int main(void) {
	//test_for_array_stack();
	//test_array_queue();
	//test_array_deque();

	//MyClass::GetInstance()->print_myclass();
	//MyClass::ReleaseInstance();

	//outClass<int> out;
	//out.fun<InnerClass<int> >();

	//outClass<int> out;
	//DoTest(out);

//	int a[5] = {1, 2, 3, 4, 5};
//	long ret = accumulate(&a[0], &a[5]);
//	cout << ret << endl;

//	char b[5] = {'a', 'b', 'c', 'd', 'e'};
//	 ret = accumulate(&b[0], &b[5]);
//	 cout << ret << endl;

//	test_dual_array_deque();

//	test_rootish_array_stack();

	//test_dllist();

	test_selist();

	return 0;
}


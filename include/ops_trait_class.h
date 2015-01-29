/*
 * ops_trait_class.h
 *
 *  Created on: 2015-1-24
 *      Author: fyliu
 */

#ifndef OPS_TRAIT_CLASS_H_
#define OPS_TRAIT_CLASS_H_

template <typename T>
class Ops_Traits;

template <>
class Ops_Traits<char>
{
public:
	typedef char T;
	typedef int OT;
	static OT zero(){return 0;}
	static T init(){return 0;};
};

template <>
class Ops_Traits<short>
{
public:
	typedef short T;
	typedef int OT;
	static OT zero(){return 0;}
	static T init(){return 0;}
};

template <>
class Ops_Traits<int>
{
public:
	typedef int T;
	typedef long long OT;
	static OT zero(){return 0;}
	static T init(){return 0;}
};

template <>
class Ops_Traits<unsigned int>
{
public:
	typedef unsigned int T;
	typedef unsigned long long OT;
	static OT zero(){return 0;}
	static T init(){return 0;}

};


template <>
class Ops_Traits<float>
{
public:
	typedef float T;
	typedef double OT;
	static OT zero() {return 0;}
	static T init() {return 0.0;}
};


template <typename T, typename AT = Ops_Traits<T> >
class Accum
{
public:
	static typename AT::OT accumulate(T const *begin, T const *end)
	{
		typedef typename AT::OT	R;
		R total = AT::zero();
		while(begin != end)
		{
			total += *begin;
			++begin;
		}
		return total;
	}
};

template <typename T>
typename Ops_Traits<T>::OT accumulate(T const *begin, T const *end)
{
	return Accum<T>::accumulate(begin, end);
}

template <typename Traits, typename T>
typename Traits::OT accumulate(T const *begin, T const *end)
{
	return Accum<T, Traits>::accumulate(begin, end);
}





#endif /* OPS_TRAIT_CLASS_H_ */

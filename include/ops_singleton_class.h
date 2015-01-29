/*
 * ops_singleton_class.h
 *
 *  Created on: 2015-1-23
 *      Author: fyliu
 */

#ifndef OPS_SINGLETON_CLASS_H_
#define OPS_SINGLETON_CLASS_H_

template <class T>
class SingletonClass
{
public:
	static T* GetInstance()
	{
		if(NULL == _instance)
			_instance = new T();//T() will call constructor
		return _instance;
	}
	static void ReleaseInstance()
	{
		if(NULL != _instance)
			delete _instance;
		_instance = NULL;
	}
private:
	static T* _instance;
};

template <class T>
T* SingletonClass<T>::_instance = NULL;

#endif /* OPS_SINGLETON_CLASS_H_ */

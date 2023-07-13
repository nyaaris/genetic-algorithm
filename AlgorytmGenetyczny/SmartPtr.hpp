#pragma once


class RefCounter
{
public:
	RefCounter() { count = 0; }

	int add() { return (++count); }
	int subtract() { return (--count); }
	int get() { return count; }

private:
	int count;
};


template <typename T>
class SmartPtr
{

public:
	SmartPtr()
	{
		pointer = nullptr;
		counter = nullptr;
	}

	SmartPtr(T* pointer)
	{
		this->pointer = pointer;
		counter = new RefCounter();
		counter->add();
	}

	SmartPtr(const SmartPtr& other)
	{
		pointer = other.pointer;
		counter = other.counter;
		if (pointer != nullptr)
			counter->add();
	}

	~SmartPtr()
	{
		if (pointer != nullptr && counter->subtract() == 0)
		{
			delete pointer;
			delete counter;
		}
	}

	T& operator*() { return *pointer; }
	T* operator->() { return pointer; }

	SmartPtr& operator=(const SmartPtr& other);

private:
	T* pointer;
	RefCounter* counter;
};


template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& other)
{
	if (pointer != nullptr && counter->subtract() == 0)
	{
		delete pointer;
		delete counter;
	}
	pointer = other.pointer;
	counter = other.counter;
	if (pointer != nullptr)
		counter->add();
}


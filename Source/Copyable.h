#pragma once
#include "JuceHeader.h"
#include "Object.h"

template <class T>
class CopyableObject:
virtual public Object
{
public:
	virtual void operator =(const T& otherObject){};
	virtual void undone(){};
	virtual void performed(){};
    virtual ~CopyableObject(){}
};

template <class T>
class CopyableUndoableAction:
public UndoableAction
{
public:
	CopyableUndoableAction(T * actual ,const T & before , const T & after )
	{
		this->oldVersion = (before);
		this->newVersion = (after);
		this->actual = actual;
	}
	CopyableUndoableAction(T * actual  , const T & after )
	{
		this->oldVersion = (*actual);
		this->newVersion = (after);
		this->actual = actual;
	}
    
	~CopyableUndoableAction()
	{
	}
    
	bool perform()
	{
        jassert(actual);
        if(actual)
        {
            actual->operator=( newVersion );
            actual->performed();
            return true;
            
        }
        return false;
        
	}
	bool undo()
	{
        jassert(actual);
        if(actual)
        {
            actual->operator=( oldVersion );
            actual->undone();
            return true;
        }
        return false;
	}
private:
	T oldVersion;
	T newVersion;
	WeakReference<T> actual;
};

#pragma once
#include "List.h"
#include "ListItem.h"

template <class T=ListItem>
class OwnedList :
virtual public List,
public ListBoxModel
{
public:
	OwnedList(D3CKHistory* history = 0)
	{
		setListHistory( history);
	}
    ~OwnedList()
    {
        this->items.clear();
    }
	virtual void remove(ListItem* item) override
	{
		T* t = dynamic_cast<T*>(item);
		if(t)
			items.removeObject(t,false);
		sendChangeMessage();
	}
    virtual ListItem* getItem(int i) const override
    {
        return items.getUnchecked(i);
    }
	virtual void add(ListItem* item,int index) override
	{
		T* t = dynamic_cast<T*>(item);
		if(t)
		{
			if(items.contains(t))
			{
				jassertfalse
			}
			else
				items.insert(index,t);
		}
		sendChangeMessage();
	}
	virtual int indexOf(const ListItem* item)const override
	{
		const T* t = dynamic_cast<const T*>(item);
		return items.indexOf(t);
	}
	int getNumRows() override
	{
		const OwnedList<T>* l = this;
		return l->getNumRows();
	}
	virtual int getNumRows() const override
	{
		return items.size();
	}
    
	virtual void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override
	{
		if(rowIsSelected)
		{
			g.setColour(Colours::red);
			g.fillRect(0,0,width,height);
		}
		g.setColour(Colours::black);
		g.drawHorizontalLine(height-1,0,width);
	}
	OwnedArray<T> items;
};

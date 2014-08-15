#pragma once
#include "JuceHeader.h"

template <class T>
class OwnedList;

template <class T>
class OwnedListGUI :
public ListBox,
public ChangeListener
{
public:
	OwnedListGUI(OwnedList<T>* list ):
	ListBox("list",list)
	{
		this->list = list;
		list->addChangeListener(this);
        setRowHeight(24);
        //		//setRowHeight(ShottyLook::defaultControllHeight);
		changeListenerCallback(list);
	}
	void changeListenerCallback(ChangeBroadcaster* obj)
	{
		if(obj == list)
		{
			setSize(getWidth(),getRowHeight() * list->getNumRows());
			updateContent();
		}
	}
	void paintOverChildren(Graphics& g)
	{
		ListBox::paintOverChildren(g);
		g.drawRect(0,0,getWidth(),getHeight(),1);
	}
	~OwnedListGUI()
	{
		list->removeChangeListener(this);
	}
	int getOptimalHeight()
	{
		return list->getNumRows() * getRowHeight();
	}
	void setOptimalBounds(int x ,int y, int w)
	{
		setBounds(x,y,w,getOptimalHeight());
	}
    
	OwnedList<T>* list;
};
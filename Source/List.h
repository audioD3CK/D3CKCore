#pragma once
#include "JuceHeader.h"
#include "VirtualDragAndDropTarget.h"
#include "NamableObject.h"

class ListItemFactory;
class MoveListItem;
class ListItem;
class D3CKHistory;

class List :
virtual public ChangeBroadcaster,
virtual public VirtualDragAndDropTarget
{
public:

	friend class ListItem;
	friend class MoveListItem;

	List(D3CKHistory* history = 0);
    virtual ~List();
    
	virtual D3CKHistory* getListHistory();
	virtual void setListHistory(D3CKHistory* history);
	virtual int getNumRows() const = 0;
    virtual ListItem* getItem(int i) const = 0;
    virtual int getMinNumItems();
    virtual ListItem* getLast();
    virtual ListItem* genericAdd();
    
    const Array<ListItem*> toArray();
    
    ListItemFactory* factory;
    SelectedItemSet<ListItem*> selectedItems;

    virtual int indexOf(const ListItem* item) const;

protected:
	virtual void remove(ListItem* item) = 0;
	virtual void add(ListItem* item,int index = -1) = 0;

private:
	D3CKHistory* history;
    
    WeakReference<List>::Master masterReference;
    friend class WeakReference<List>;

};






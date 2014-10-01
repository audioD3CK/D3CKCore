#pragma once
#include "VirtualDragAndDropTarget.h"
#include "NamableObject.h"
#include "Object.h"

class D3CKHistory;
class List;

class ListItem :
virtual public VirtualDragAndDropTarget,
virtual public ChangeBroadcaster,
virtual public NamableObject,
virtual public Object
{
	friend class MoveListItem;
public:
	ListItem(D3CKHistory* man = nullptr);
	virtual ~ListItem();
	virtual bool deleteFromHistory();
	virtual void listChanged(List* newList);
	virtual void moveToTrash(bool useHistory = false, D3CKHistory* history = 0 );
	virtual void movedToTrash(bool wasUnodable);
    virtual void movingToTrash(D3CKHistory* history);
    
    ListItem* getPreviousListItem()const;
    ListItem* getNextListItem()const;

    virtual bool canDelete()const;
    void setHover(bool hover);
    bool hovers();
    
    virtual void mouseUp(const MouseEvent& e);
    
    virtual Component* createItemComponent();
    
	virtual void listWillChange(List* list);
    
	void setList(List* list,int index = -1, bool useHistory = false, D3CKHistory* historyToUse = 0);
	List* getList();
	virtual void setItemHistory(D3CKHistory* history);
	virtual D3CKHistory* getItemHistory();
    
private:
    bool hover;
	D3CKHistory* history;
	List* list;
    
    WeakReference<ListItem>::Master masterReference;
    friend class WeakReference<ListItem>;
};
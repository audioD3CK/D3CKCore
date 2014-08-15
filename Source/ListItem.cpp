#include "ListItem.h"
#include "D3CKHistory.h"
#include "MoveListItem.h"

ListItem::ListItem(D3CKHistory* history):
NamableObject(this)
{
    hover = false;
	this->list = nullptr;
	this->history = history;
}
ListItem::~ListItem()
{
    masterReference.clear();
}
bool ListItem::deleteFromHistory()
{
	return false;
}
void ListItem::listChanged(List* newList)
{
}
void ListItem::moveToTrash(bool useHistory, D3CKHistory* historyp)
{
	D3CKHistory* history = historyp ? historyp : this->history;
	if(history )
    {
        setList(&history->getTrash(),-1,useHistory,history);

    }
    
    //jassert(useHistory && history)
	
	movedToTrash(historyp);
}
void ListItem::movedToTrash(bool wasUnodable)
{
}
void ListItem::movingToTrash(D3CKHistory* history)
{
    
}
bool ListItem::canDelete()const
{
    return true;
}
void ListItem::setHover(bool hover)
{
    if(this->hover != hover)
    {
        this->hover = hover;
        sendChangeMessage();
    }
}
bool ListItem::hovers()
{
    return hover;
}
void ListItem::mouseUp(const MouseEvent& e)
{
    
}
Component* ListItem::createItemComponent()
{
    return 0;
}

void ListItem::listWillChange(List* list)
{
    
}
void ListItem::setList(List* list,int index, bool useHistory, D3CKHistory* historyToUse)
{
	if(useHistory && (this->history || historyToUse))
	{
		D3CKHistory* h = historyToUse ? historyToUse : this->history;
        MoveListItem* act = new MoveListItem(this,list,historyToUse ? historyToUse : history ,index);
        
        if(list != this->list)
            listWillChange(list);
        
        if(list == &h->getTrash())
            movingToTrash(h);
        
		h->perform(act);
	}
	else
	{
		bool changeList = this->list != list;
		bool changeIndex = this->list && this->list->indexOf(this) != index;
		if(changeList || changeIndex)
		{
			if(this->list)
			{
				this->list->remove(this);
			}
			this->list = list;
			if(list)
			{
				if(list->getListHistory() == 0 && getItemHistory())
					list->setListHistory(getItemHistory());
				else if(list->getListHistory())
					setItemHistory(list->getListHistory());
                
				list->add(this,index);
			}
			listChanged(list);
		}
	}
}
List* ListItem::getList()
{
	return list;
}

void ListItem::setItemHistory(D3CKHistory* history)
{
	this->history = history;
}

D3CKHistory* ListItem::getItemHistory()
{
	if(this->history)
		return this->history;
	else if(this->list)
	{
		return this->list->getListHistory();
	}
	return 0;
}

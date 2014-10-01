#include "List.h"
#include "D3CKHistory.h"
#include "ListItemFactory.h"
#include "ListItem.h"

List::List(D3CKHistory* history)
{
    factory = 0;
	this->history = history;
}
List::~List()
{
    masterReference.clear();
}
D3CKHistory* List::getListHistory()
{
	return history;
}
void List::setListHistory(D3CKHistory* history)
{
	if(this->history != history && history)
    {
		this->history = history;
    }
}
int List::getMinNumItems()
{
    return 0;
}
ListItem* List::getLast()
{
    return getItem(getNumRows()-1);
}


ListItem* List::genericAdd()
{
    if(factory)
    {
        ListItem* item = factory->createListItem(0);
        if(item)
        {
            item->setList(this,-1,true,getListHistory());
            return item;
        }
    }
    return 0;
}
const Array<ListItem*> List::toArray()
{
    Array<ListItem*> items;
    for(int i = 0 ; i < getNumRows() ; i++)
    {
        items.add(getItem(i));
    }
    return items;
}
int List::indexOf(const ListItem* item) const
{
    for(int i = getNumRows() ; --i >= 0 ; )
    {
        if( getItem(i) == item)
        {
            return i;
        }
    }
    return 0;
}


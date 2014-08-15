#include "MoveListItem.h"
#include "ListItem.h"
#include "List.h"
#include "D3CKHistory.h"

MoveListItem::MoveListItem(ListItem* item, List* targetList, D3CKHistory* man, int index)
{
	this->targetList = targetList;
	this->sourceList = item->list;
	this->item = item;
	this->oldIndex = sourceList ? sourceList->indexOf(item) : -1;
	this->newIndex = index;
	this->sourceList = sourceList ? sourceList : &man->getTrash();
}
MoveListItem::~MoveListItem()
{
}
void MoveListItem::move(List* sourceList , List* targetList , int targetIndex)
{
	if(item)
		item->setList(currentList = targetList,targetIndex,false);
}
bool MoveListItem::perform()
{
	move(sourceList,targetList,newIndex);
	return item;
}
bool MoveListItem::undo()
{
	move(targetList,sourceList,oldIndex);
	return item;
}

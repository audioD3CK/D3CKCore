#pragma once
#include "JuceHeader.h"
class List;
class D3CKHistory;
class ListItem;

class MoveListItem :
public UndoableAction
{
public:
    
	MoveListItem(ListItem* item, List* targetList, D3CKHistory* man, int index = -1);
	~MoveListItem();
	bool perform();
	bool undo();
    
private:
	void move(List* sourceList , List* targetList, int targetIndex);
	int oldIndex;
	int newIndex;
	WeakReference<ListItem> item;
	WeakReference<List> sourceList;
	WeakReference<List> targetList;
	WeakReference<List> currentList;
};

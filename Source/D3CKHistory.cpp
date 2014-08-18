#include "D3CKHistory.h"
#include "HistorySource.h"

D3CKHistory::D3CKHistory(CriticalSection* sharedLock):
trash(this)
{
	this->sharedLock = sharedLock;
    if(sharedLock == nullptr)
    {
        this->sharedLock = &this->privateLock;
    }
    
}
D3CKHistory::~D3CKHistory()
{
}

D3CKHistory* D3CKHistory::find(Component *comp)
{
    HistorySource* g = comp->findParentComponentOfClass<HistorySource>();
    return g ? g->getHistory() : nullptr;
}

bool D3CKHistory::tryPerform(UndoableAction* action,Component* comp)
{
    D3CKHistory* h = find(comp);
    if(h)
    {
        return h->perform(action);
    }
    else
    {
        action->perform();
        deleteAndZero(action);
        return false;
    }
}


void D3CKHistory::beginNewTransaction(const String& name, Component* comp)
{
    D3CKHistory::find(comp)->beginNewTransaction(name);
}

void D3CKHistory::beginNewTransaction (const String& actionName)
{

    UndoManager::beginNewTransaction(actionName);
}
void D3CKHistory::clearUndoHistory()
{
	UndoManager::clearUndoHistory();
	trash.items.clear();
}
bool D3CKHistory::undo()
{
    return UndoManager::undo();
}
bool D3CKHistory::redo()
{
    return UndoManager::redo();
}

CriticalSection* D3CKHistory::getLock()const
{
    return this->sharedLock;
}

OwnedList<ListItem>& D3CKHistory::getTrash()
{
    return this->trash;
}

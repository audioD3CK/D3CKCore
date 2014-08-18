#pragma once
#include "JuceHeader.h"
#include "OwnedList.h"

class D3CKFrame;

class D3CKHistory :
public UndoManager
{
public:
	D3CKHistory(CriticalSection* sharedLock = nullptr);
	~D3CKHistory();
	void clearUndoHistory();
    void beginNewTransaction (const String& actionName = String::empty);
    bool redo();
    bool undo();

    OwnedList<ListItem>& getTrash();
    CriticalSection* getLock()const;
    static D3CKHistory* find( Component* comp);
    static void beginNewTransaction(const String& name, Component* comp);
    static bool tryPerform(UndoableAction* action,Component* comp);

private:
    CriticalSection privateLock;
	CriticalSection* sharedLock;
    
	OwnedList<ListItem> trash;
    
};


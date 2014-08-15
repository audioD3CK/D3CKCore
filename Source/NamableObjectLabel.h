#pragma once
#include "JuceHeader.h"

class NamableObject;

class NamableObjectLabel :
public Label,
public ChangeListener
{
public:
	NamableObjectLabel(NamableObject* obj,ChangeBroadcaster* changeBroadcaster = 0);
	~NamableObjectLabel();
	void changeListenerCallback(ChangeBroadcaster* obj);
	void visibilityChanged();
    void resized();
    
    ChangeBroadcaster* changeBroadcaster;

private:
	WeakReference<NamableObject> obj;
};
#pragma once
#include "JuceHeader.h"
#include "NamedObject.h"

class NamableObject :
public LabelListener,
virtual public ChangeBroadcaster,
virtual public NamedObject
{
public:
	NamableObject(ChangeBroadcaster* nameChangeBroadcaster = 0);
    virtual ~NamableObject();

	void labelTextChanged(Label* label);
	virtual void setName(const String& newName) = 0;
	void focusEditor();
    bool isEditorArmed()const;
    void editorUsed();
    
private:
	bool editorArmed;
    
    WeakReference<NamableObject>::Master masterReference;
    friend class WeakReference<NamableObject>;
};

class SimpleNamableObject :
virtual public NamableObject
{
public:
	SimpleNamableObject(ChangeBroadcaster* nameChangeBroadcaster = 0);
	virtual void setName(const String& newName, bool sendChange);
    virtual void setName(const String& name)override;
	virtual const String getName() const;
protected:
    
    virtual void nameChanged(const String& newName);
private:
	String name;
};


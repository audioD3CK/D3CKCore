#include "NamableObject.h"
NamableObject::NamableObject(ChangeBroadcaster* nameChangeBroadcaster)
{
	editorArmed = false;
}

void NamableObject::labelTextChanged(Label* label)
{
	setName(label->getText());
}
void NamableObject::focusEditor()
{
	editorArmed = true;
	
    sendChangeMessage();
}

NamableObject::~NamableObject()
{
    masterReference.clear();
}


SimpleNamableObject::SimpleNamableObject(ChangeBroadcaster* nameChangeBroadcaster):
NamableObject(nameChangeBroadcaster)
{
    
}
bool NamableObject::isEditorArmed()const
{
    return this->editorArmed;
}

void NamableObject::editorUsed()
{
    editorArmed =false;
}

void SimpleNamableObject::setName(const String& newName,bool sendChange)
{
	this->name = newName;
    if(sendChange)
    {
        nameChanged(newName);
    }
}
const String SimpleNamableObject::getName() const
{
	return name;
}
void SimpleNamableObject::nameChanged(const String& newName)
{
    sendChangeMessage();
}


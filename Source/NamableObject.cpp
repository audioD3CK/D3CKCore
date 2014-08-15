#include "NamableObject.h"
#include "ShottyLook.h"
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
//NamableObjectLabel::NamableObjectLabel(NamableObject* obj,ChangeBroadcaster* changeBroadcaster):
//Label("name",obj->getName())
//{
//	this->changeBroadcaster = changeBroadcaster ? changeBroadcaster : obj;
//	this->obj = obj;
//	if(this->changeBroadcaster)
//    {
//		this->changeBroadcaster->addChangeListener(this);
//    }
//	addListener(obj);
//	setEditable(false,true);
//    setBufferedToImage(true);
//
//}
//void NamableObjectLabel::resized()
//{
//    Label::resized();
//    Label::setFont(ShottyLook::getOptimalFont(getWidth(), getHeight()));
//
//}
//NamableObjectLabel::~NamableObjectLabel()
//{
//	if(changeBroadcaster)
//    {
//		changeBroadcaster->removeChangeListener(this);
//    }
//}

//void NamableObjectLabel::changeListenerCallback(ChangeBroadcaster* obj)
//{
//	if(obj == this->obj)
//	{
//        if(getText() != this->obj->getName())
//        {
//            setText(this->obj->getName(),NotificationType::dontSendNotification);
//        }
//
//	}
//}
//void NamableObjectLabel::visibilityChanged()
//{
//    if(this->obj->editorArmed)
//    {
//        grabKeyboardFocus();
//        showEditor();
//        obj->editorArmed = false;
//    }
//}

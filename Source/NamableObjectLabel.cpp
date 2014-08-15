#include "NamableObjectLabel.h"
#include "NamableObject.h"
#include "ShottyLook.h"

NamableObjectLabel::NamableObjectLabel(NamableObject* obj,ChangeBroadcaster* changeBroadcaster):
Label("name",obj->getName())
{
	this->changeBroadcaster = changeBroadcaster ? changeBroadcaster : obj;
	this->obj = obj;
	if(this->changeBroadcaster)
		this->changeBroadcaster->addChangeListener(this);
	addListener(obj);
	setEditable(false,true);
    setBufferedToImage(true);

}
void NamableObjectLabel::resized()
{
    Label::resized();
    Label::setFont(ShottyLook::getOptimalFont(getWidth(), getHeight()));

}
NamableObjectLabel::~NamableObjectLabel()
{
	if(changeBroadcaster)
		changeBroadcaster->removeChangeListener(this);
}
void NamableObjectLabel::changeListenerCallback(ChangeBroadcaster* obj)
{
	if(obj == this->obj)
	{
        if(getText() != this->obj->getName())
            setText(this->obj->getName(),NotificationType::dontSendNotification);

	}
}
void NamableObjectLabel::visibilityChanged()
{
		if(this->obj->isEditorArmed())
		{
			grabKeyboardFocus();
			showEditor();
			obj->editorUsed();
		}
}
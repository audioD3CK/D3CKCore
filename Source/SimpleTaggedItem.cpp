#include "SimpleTaggedItem.h"

SimpleTaggedItem::SimpleTaggedItem()
{
    
}

SimpleTaggedItem::SimpleTaggedItem(const File& file, const String& type, const String& name )
{
    this->setName(name);
    this->type = type;
    this->file = file;
}

TaggedItemBase* SimpleTaggedItem::clone() const
{
    return new SimpleTaggedItem(this->getFile(),this->getType(),this->getName());
}

String SimpleTaggedItem::getIconName()const
{
    return "star";
}


SimpleTaggedItem::SimpleTaggedItem(const TaggedItemBase& other)
{
    this->type = other.getType();
    this->file = other.getFile();
}


String SimpleTaggedItem::getType()const
{
    return this->type;
}

File SimpleTaggedItem::getFile()const
{
    return this->file;
}
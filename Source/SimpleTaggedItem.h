#pragma once
#include "TaggedItemBase.h"
#include "NamableObject.h"

class SimpleTaggedItem :
public TaggedItemBase,
public SimpleNamableObject
{
public:
    SimpleTaggedItem();
    SimpleTaggedItem(const File& file, const String& type, const String& name );
    SimpleTaggedItem(const TaggedItemBase& other);
    virtual String getType()const override;
    virtual File getFile()const override;
    virtual String getIconName()const;
    virtual TaggedItemBase* clone() const override;

protected:
    String type;
    File file;
};
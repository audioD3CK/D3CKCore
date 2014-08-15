#pragma once
#include "JuceHeader.h"

class PropertySource
{
public:
    virtual ~PropertySource();
 
    virtual Array<PropertyComponent*> getPropertyComponents() const;
    virtual void fillPropertyPanel(PropertyPanel& panelToFill) const;
    virtual String getPropertySectionName()const;
};
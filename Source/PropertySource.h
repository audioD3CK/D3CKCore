#pragma once
#include "JuceHeader.h"

class PropertySource
{
public:
    virtual ~PropertySource();
    virtual String getPropertySectionName()const;
    virtual Array<PropertyComponent*> getPropertyComponents();
    
    virtual void fillPropertyPanel(PropertyPanel& panelToFill) const;
    
    static void putPropertysToPanel(PropertyPanel& panelToFill,const Array<PropertyComponent*>&,const String &name);
};
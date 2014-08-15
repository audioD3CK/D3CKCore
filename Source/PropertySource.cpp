
#include "PropertySource.h"


PropertySource::~PropertySource()
{
    
}

Array<PropertyComponent*> PropertySource::getPropertyComponents() const
{
    Array<PropertyComponent*> arr;
    return arr;
}

void PropertySource::fillPropertyPanel(PropertyPanel& panelToFill) const 
{
    panelToFill.addSection(this->getPropertySectionName(), this->getPropertyComponents());
}

String PropertySource::getPropertySectionName()const
{
    return "properties";
}

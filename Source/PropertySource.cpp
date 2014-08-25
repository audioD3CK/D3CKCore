
#include "PropertySource.h"


PropertySource::~PropertySource()
{
    
}

Array<PropertyComponent*> PropertySource::getPropertyComponents()
{
    Array<PropertyComponent*> arr;
    return arr;
}

void PropertySource::fillPropertyPanel(PropertyPanel& panelToFill) const
{
    const Array<PropertyComponent*> comps = const_cast<PropertySource*>(this)->getPropertyComponents();
    const String name = this->getPropertySectionName();
    
    PropertySource::putPropertysToPanel(panelToFill, comps, name);
}

String PropertySource::getPropertySectionName()const
{
    return "properties";
}

void PropertySource::putPropertysToPanel(PropertyPanel& panelToFill,const Array<PropertyComponent*>& comps,const String &name)
{
    if(comps.size())
    {
        for(int i = 0 ; i < comps.size() ; ++i)
        {
            PropertyComponent * c = comps.getUnchecked(i);
            c->setPreferredHeight(20);
            c->setOpaque(false);
            c->setColour(PropertyComponent::ColourIds::labelTextColourId,Colours::white);
            for(int i = c->getNumChildComponents() ; -- i >= 0 ;)
            {
                c->getChildComponent(i)->setOpaque(false);
            }
        }
        panelToFill.addSection(name,comps);
    }
}

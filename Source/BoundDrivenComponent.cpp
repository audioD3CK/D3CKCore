#include "BoundDrivenComponent.h"

BoundDrivenComponent::BoundDrivenComponent(BoundsDriver* driver)
{
    this->driver = driver;
    driver->addChangeListener(this);
    changeListenerCallback(driver);
}
BoundDrivenComponent::~BoundDrivenComponent()
{
    if(driver)
    {
        driver->removeChangeListener(this);
    }
}
void BoundDrivenComponent::changeListenerCallback(ChangeBroadcaster* obj)
{
    Component* c = dynamic_cast<Component*>(this);
    if(c)
    {
        c->setBounds((*driver+ this->getOffset()) * this->getScale() );
    }
}

Point<int> BoundDrivenComponent::getOffset()const
{
    return Point<int>(0,0);
}


double BoundDrivenComponent::getScale() const
{
    return 1;
}

BoundsDriver* BoundDrivenComponent::getDriver()const
{
    return this->driver;
}
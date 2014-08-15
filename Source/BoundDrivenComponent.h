#pragma once
#include "Juceheader.h"

#include "BoundsDriver.h"

class BoundDrivenComponent :
	public ChangeListener,
	public Component
{
public:
	BoundDrivenComponent(BoundsDriver* driver);
	virtual ~BoundDrivenComponent();
	virtual void changeListenerCallback(ChangeBroadcaster* obj);
    virtual double getScale() const;
    virtual Point<int> getOffset()const;
    virtual BoundsDriver* getDriver()const;
protected:
	WeakReference<BoundsDriver> driver;
};
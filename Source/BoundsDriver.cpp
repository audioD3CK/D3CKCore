#include "BoundsDriver.h"

BoundsDriver::BoundsDriver(void)
{
}

BoundsDriver::~BoundsDriver(void)
{
    masterReference.clear();
}

void BoundsDriver::setBounds(int x , int y , int width, int height)
{
    Rectangle<int>::setBounds(x,y,width,height);
    sendChangeMessage();
}

void BoundsDriver::operator= (const BoundsDriver& other)
{
    Rectangle<int>::operator=(other);
    sendChangeMessage();
}

void BoundsDriver::operator= (const Rectangle<int>& other)
{
    Rectangle<int>::operator=(other);
    sendChangeMessage();
}

BoundsDriver::UndoableBoundChange::~UndoableBoundChange()
{
    masterReference.clear();
}

BoundsDriver::UndoableBoundChange::UndoableBoundChange(BoundsDriver* driver,const Rectangle<int>& from,const Rectangle<int>& to)
{
    this->driver = driver;
    this->from = from;
    this->to = to;
}

bool BoundsDriver::UndoableBoundChange::perform()
{
    if(this->driver)
    {
        *driver = to;
        return true;
    }
    else
    {
        return false;
    }
}

bool BoundsDriver::UndoableBoundChange::undo()
{
    if(this->driver)
    {
        *driver = from;
        return true;
    }
    else
    {
        return false;
    }
}
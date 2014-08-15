#include "PlacementRect.h"
#include "HistorySource.h"
#include "D3CKHistory.h"

PlacementRect::PlacementRect(BoundsDriver* driver,ComponentBoundsConstrainer* limits):
BoundDrivenComponent(driver),
resizer(this,limits)
{
    resizer.addMouseListener(this,false);
    addAndMakeVisible(&resizer);
    this->limits = limits;
    resized();
}
bool PlacementRect::hitTest(int x , int y)
{
    return y < 15 || y > (getHeight() - resizer.getBorderThickness().getBottom())
    || x < resizer.getBorderThickness().getLeft()
    || x > (getWidth() - resizer.getBorderThickness().getRight());
}
void PlacementRect::mouseDown(const MouseEvent& e)
{
    lastBounds = *this->driver;
    
    toFront(true);
    if(e.originalComponent == this)
    {
        dragger.startDraggingComponent(this,e);
    }
}
void PlacementRect::mouseDrag(const MouseEvent& e)
{
    if(e.originalComponent == this)
    {
        dragger.dragComponent(this,e,limits);
    }
    *driver = getBounds() / this->getScale();
}
void PlacementRect::mouseUp(const MouseEvent& e)
{
    
    HistorySource* h = this->findParentComponentOfClass<HistorySource>();
    if(h)
    {
        h->getHistory()->beginNewTransaction("change bounds");
        h->getHistory()->perform(new BoundsDriver::UndoableBoundChange(driver,this->lastBounds,getBounds() / this->getScale()));
    }
    else
    {
        *driver = getBounds() / this->getScale();
    }
}
void PlacementRect::resized()
{
    resizer.setBounds(0,0,getWidth(),getHeight());
}
const Colour& PlacementRect::getColour() const
{
    return this->colour;
}

void PlacementRect::paintOverChildren(Graphics& g)
{
    PlacementRect::paint(g,this,this->getColour());
    g.drawText(getName(),0,0,getWidth(),15,Justification::centred,true);
}

void PlacementRect::paint(Graphics& g, Component* c,const Colour& col)
{
    g.setColour(col.withAlpha(0.5f));
    g.drawRect(0,0,c->getWidth(),c->getHeight());
    g.drawLine(0,15,c->getWidth(),15);
}

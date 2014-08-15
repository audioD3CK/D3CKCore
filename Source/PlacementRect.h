#pragma once
#include "BoundDrivenComponent.h"

class PlacementRect :
public BoundDrivenComponent
{
public:
	PlacementRect(BoundsDriver* driver,ComponentBoundsConstrainer* limits = 0);
    
	bool hitTest(int x , int y)override;
	void mouseDown(const MouseEvent& e)override;
	void mouseDrag(const MouseEvent& e)override;
	void mouseUp(const MouseEvent& e)override;
	void resized()override;
    void paintOverChildren(Graphics& g)override;
    
    virtual const Colour& getColour() const;
    
    static void paint(Graphics& g, Component* c,const Colour& col = Colours::white);
    
    Colour colour;
    
protected:
	ResizableBorderComponent resizer;
	ComponentDragger dragger;
	ComponentBoundsConstrainer* limits;
    
    Rectangle<int> lastBounds;
   
};
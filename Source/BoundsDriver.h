#pragma once
#include "JuceHeader.h"

class BoundsDriver :
public Rectangle<int>,
public ChangeBroadcaster
{
public:
	BoundsDriver(void);
	~BoundsDriver(void);
	
	void setBounds(int x , int y , int width, int height);
	void operator= (const BoundsDriver& other);
	void operator= (const Rectangle<int>& other);
	
	class UndoableBoundChange :
	public UndoableAction
    {
    public:
        UndoableBoundChange(BoundsDriver* driver,const Rectangle<int>& from,const Rectangle<int>& to);
        ~UndoableBoundChange();
        virtual bool perform();
        virtual bool undo();
    private:
        WeakReference<BoundsDriver> driver;
        Rectangle<int> to;
        Rectangle<int> from;
        
        WeakReference<UndoableBoundChange>::Master masterReference;
        friend class WeakReference<UndoableBoundChange>;
    };
    
private:
    WeakReference<BoundsDriver>::Master masterReference;
    friend class WeakReference<BoundsDriver>;
};
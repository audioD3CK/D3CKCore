#pragma once
#include "JuceHeader.h"

class BigShotTreeItemDragAndDropComponent;

class VirtualDragAndDropTarget
{
public:
    virtual ~VirtualDragAndDropTarget();
	virtual bool wantsD3cknDSource(BigShotTreeItemDragAndDropComponent* comp);
	virtual void audioDataDropped(int x,int y, BigShotTreeItemDragAndDropComponent* comp );
	virtual void getOptionZones(StringArray& names, BigShotTreeItemDragAndDropComponent* d3ckDnDComp);
};
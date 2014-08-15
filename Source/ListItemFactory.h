#pragma once

class ListItem;

class ListItemFactory
{
public:
    virtual ListItem* createListItem(int flags) = 0;
    virtual ~ListItemFactory();
};
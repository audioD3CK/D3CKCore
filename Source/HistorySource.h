#pragma once

class D3CKHistory;

class HistorySource
{
public:
    virtual D3CKHistory* getHistory()const = 0;
    virtual ~HistorySource(){}
};
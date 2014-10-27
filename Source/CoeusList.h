//
//  CoeusList.h
//  Coeus
//
//  Created by - on 8/10/14.
//
//

#ifndef __Coeus__CoeusList__
#define __Coeus__CoeusList__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"

class CoeusHeap
{
public:
    CoeusHeap();
    void update();
    int findIndexForSum(int sum) const;
    int findSumForIndex(int index) const;
    void setNewValueAtIndex(int value, int index);
    void setNewValues(int *values, int size);
    int getValueAt(int index);
    int getSum() const;
    
private:
    HeapBlock<int> heap;
    size_t heapSize;
    int numEl;
};

class CoeusListRowComponent :   public Component,
                                public ChangeBroadcaster
{
public:
    virtual int getCoeusListHeight() = 0;
    virtual void updateFromQueryForRow(QueryEntry *qe, int row, bool dView) = 0;
    virtual void setDetailedView(bool s, bool force=false) = 0;
    virtual void shouldShowControls(bool show) = 0;
    int row;

protected:
    bool detailedView, editView, showControls;

};

class CoeusList :   public Component,
                    public ScrollBar::Listener
{
public:
    CoeusList();
    ~CoeusList();
    
    virtual int getNumRows() = 0;
    virtual void paintRowBackground(Graphics &/*g*/, int /*rowNumber*/, int /*x*/, int /*y*/,
                                    int /*width*/, int /*height*/,
                                    bool /*rowIsSelected*/) {}
    
    virtual CoeusListRowComponent * refreshComponentForRow(int rowNumber, bool isRowSelected,
                                               CoeusListRowComponent *existingComponentToUpdate) {
        return nullptr;
    };
    
    virtual int getMinRowSize() = 0;
    virtual int getMaxRowSize() = 0;
    virtual int getRowSize(int rowNumber) = 0;
    virtual int *getRowSizes(int *pointer) { return nullptr; }
    CoeusListRowComponent *getComponentForRow(int row) const;

    void rowChangedSize(int rowNumber, int newSize);
    void update();
    void resized() override;
    void selectRow(int rowNumber);
    void repaintRow(int rowNumber);
    void scrollBarMoved (ScrollBar *scrollBarThatHasMoved, double newRangeStart) override;
    
    virtual int getRowIndexAt(int y);
    
protected:
    int selectedRow;
    virtual int getYStartForRow(int index) const;
    int getViewStartHeight() const;
    
private:
    virtual void updateComponents();
    virtual void positionComponents();
    
    Array<CoeusListRowComponent *> items;
    Array<CoeusListRowComponent *> pool;
    Array<int> itemsToRows;
    ScrollBar sb;
    CoeusHeap heap;
    int viewFirstRow;
    int viewLastRow;
};


#endif /* defined(__Coeus__CoeusList__) */

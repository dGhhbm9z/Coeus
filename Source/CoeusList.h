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
    int findIndexForSum(int sum);
    int findSumForIndex(int index);
    void setNewValueAtIndex(int value, int index);
    void setNewValues(int *values, int size);
    int getValueAt(int index);
    int getSum();
    
private:
    HeapBlock<int> heap;
    size_t heapSize;
    int numEl;
};

class CoeusList :   public Component,
                    public ScrollBar::Listener
{
public:
    CoeusList();
    ~CoeusList();
    
    virtual int getNumRows() = 0;
    virtual void paintRowBackground(Graphics &g, int rowNumber,
                                    int width, int height,
                                    bool rowIsSelected) {};
    
    virtual void paintRow(Graphics &g, int rowNumber,
                          int width, int height,
                          bool rowIsSelected) {};
    
    virtual Component * refreshComponentForRow(int rowNumber, bool isRowSelected,
                                               Component *existingComponentToUpdate) {
        return nullptr;
    };
    
    virtual int getMinRowSize() = 0;
    virtual int getMaxRowSize() = 0;
    virtual int getRowSize(int rowNumber) = 0;
    virtual int *getRowSizes(int *pointer) { return nullptr; };
    
    void rowChangedSize(int rowNumber, int newSize);
    void update();
    void resized() override;
    void selectRow(int rowNumber);
    void repaintRow(int rowNumber);
    void scrollBarMoved (ScrollBar *scrollBarThatHasMoved, double newRangeStart) override;
    
    virtual int getRowIndexAt(int y);
    
private:
    virtual int getYStartForRow(int index);
    virtual void updateComponents();
    virtual void positionComponents();
    
    Array<Component *> items;
    Array<Component *> pool;
    Array<int> itemsToRows;
    ScrollBar sb;
    CoeusHeap heap;
    int selectedRow;
    int viewFirstRow;
    int viewLastRow;
};


#endif /* defined(__Coeus__CoeusList__) */

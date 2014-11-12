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
                                public ChangeBroadcaster,
                                public ButtonListener
{
public:
    CoeusListRowComponent();
    virtual int getCoeusListHeight() = 0;
    virtual void updateFromQueryForRow(QueryEntry *qe, int row, bool dView) = 0;
    virtual int getMinRowSize() = 0;
    virtual int getMaxRowSize() = 0;
    virtual void resizeForSummary() = 0;
    virtual void resizeForDetailed() = 0;
    void resized() override;
    virtual void shouldShowControls(bool show);
    
    virtual void updateRow() = 0;
    virtual void insertRow() = 0;
    
    void buttonClicked (Button *btn) override;
    
    int getRow() const;
    void setRow(int r);

protected:
    void setDetailedView(bool s, bool force=false);

    // control buttons
    ScopedPointer<TextButton> edit, save, remove;
    
    bool detailedView, editView, showControls;
    int row;
    
};

class CoeusList :   public Component,
                    public ScrollBar::Listener,
                    public ChangeListener
{
public:
    CoeusList();
    ~CoeusList();
    
    virtual int getNumRows() = 0;
    virtual int getRowSize(int rowNumber) = 0;
    
    void paint(Graphics &g) override;
    void repaintRow(int rowNumber);
    virtual void paintRowBackground(Graphics &/*g*/, int /*rowNumber*/, int /*x*/, int /*y*/,
                                    int /*width*/, int /*height*/,
                                    bool /*rowIsSelected*/) {}
    
    virtual CoeusListRowComponent * refreshComponentForRow(int rowNumber, bool isRowSelected,
                                               CoeusListRowComponent *existingComponentToUpdate) {
        return nullptr;
    };
    
    virtual int *getRowSizes(int *pointer) { return nullptr; }
    CoeusListRowComponent *getComponentForRow(int row) const;

    void rowChangedSize(int rowNumber, int newSize);
    void update();
    void resized() override;
    void selectRow(int rowNumber);
    
    //
    void scrollBarMoved (ScrollBar *scrollBarThatHasMoved, double newRangeStart) override;
    
    //
    virtual int getRowIndexAt(int y);
    
    //
    void setQueryEntry(QueryEntry *qe_);
    
    //
    void changeListenerCallback(ChangeBroadcaster *source) override;
    void mouseMove(const MouseEvent &event) override;
    void mouseExit(const MouseEvent &event) override;
    void mouseDown (const MouseEvent &event) override;
    void mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) override;
    
    //
    virtual int getMinRowSize() = 0;
    virtual int getMaxRowSize() = 0;
    
protected:
    Array<int> selectedRow;
    virtual int getYStartForRow(int index) const;
    int getViewStartHeight() const;
    ScrollBar sb;
    
    QueryEntry *qe;
    int rowUnderMouse;
    HeapBlock<int> rowSizes;
    
private:
    virtual void updateComponents();
    virtual void positionComponents();
    
    Array<CoeusListRowComponent *> items;
    Array<CoeusListRowComponent *> pool;
    Array<int> itemsToRows;
    CoeusHeap heap;
    int viewFirstRow;
    int viewLastRow;
};


#endif /* defined(__Coeus__CoeusList__) */

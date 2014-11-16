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
#include <map>

//==============================================================================

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

class CoeusList;

class CoeusListRowComponent :   public Component,
                                public ChangeBroadcaster,
                                public ButtonListener
{
public:
    CoeusListRowComponent(CoeusList &owner_);
    virtual int getCoeusListHeight() = 0;
    virtual void updateFromQueryForRow(QueryEntry *qe, int row, bool dView, bool edit);
    virtual void updateFromMapForRow(QueryEntry *qe, std::map<String, String>, int row, bool dView, bool edit);
    virtual int getMinRowSize() = 0;
    virtual int getMaxRowSize() = 0;
    virtual void resizeForSummary() = 0;
    virtual void resizeForDetailed() = 0;
    void resized() override;
    virtual void shouldShowControls(bool show);
    
    virtual void updateRow() = 0;
    virtual void insertRow() = 0;
    virtual int fieldNameToIndex(String fname) const = 0;
    virtual void setEdit(bool ed) { };
    
    void buttonClicked (Button *btn) override;
    
    int getRow() const;
    void setRow(int r);
    
protected:
    void setDetailedView(bool s, bool force=false);

    // control buttons
    Image imageNormal, imageMouseOver, imageMouseDown;
    ScopedPointer<ImageButton> details;
    
    bool detailedView, editView, showControls;
    int row;

    CoeusList &owner;
};

class CoeusList :   public Component,
                    public ScrollBar::Listener,
                    public TextEditor::Listener,
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
    virtual int getKeyField() { return 0; };

    void rowChangedSize(int rowNumber, int newSize);
    void update();
    void resized() override;
    void selectRow(int rowNumber);
    void addSelectRow(int rowNumber);
    virtual void setEdit(bool ed) { edit = ed; };
    
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
    
    //
    void textEditorTextChanged (TextEditor &) override;
    void textEditorReturnKeyPressed (TextEditor &te) override;    
    
protected:
    std::map<String, std::map<String, String>> rowsToUpdate;
    Array<int> selectedRow;
    virtual int getYStartForRow(int index) const;
    int getViewStartHeight() const;
    ScrollBar sb;
    
    QueryEntry *qe;
    int rowUnderMouse;
    HeapBlock<int> rowSizes;
    bool edit;
    
private:
    virtual void updateComponents();
    virtual void positionComponents();
    
    template <typename PointerType, typename ExcludedType> PointerType getFirstAncestorOf(Component * component) const;
    
    Array<CoeusListRowComponent *> items;
    Array<CoeusListRowComponent *> pool;
    Array<int> itemsToRows;
    CoeusHeap heap;
    int viewFirstRow;
    int viewLastRow;
};


#endif /* defined(__Coeus__CoeusList__) */

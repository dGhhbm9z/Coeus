//
//  CoeusList.cpp
//  Coeus
//
//  Created by - on 8/10/14.
//
//

#include "CoeusList.h"

//================================================

CoeusHeap::CoeusHeap()
:   heap(0)
{
    heapSize = 0;
    numEl = 0;
}

void CoeusHeap::update()
{
    for(int i=heapSize/2 - 1; i>=0; --i) {
        heap[i] = heap[2*i+1] + heap[2*i+2];
    }
}

int CoeusHeap::findIndexForSum(int sum) const
{
    int next = 0;
    
    if (heapSize == 0 ){
        return -1;
    }
    else if (heap[0] < sum) {
        return numEl-1;
    }

    
    while(next >=0 && next < heapSize/2) {
        const int lchld = 2*next+1;
        const int rchld = 2*next+2;
        next = heap[lchld] >= sum ? lchld : rchld;
        sum -= heap[lchld] >= sum ? 0 : heap[lchld];
        sum = jmax(sum, 0);
    }
    
    return next - heapSize/2;
}

int CoeusHeap::findSumForIndex(int index) const
{
    if (index < 0 || index >= numEl) {
        return 0;
    }

    int sum = 0;
    int next = heapSize/2 + index;
    sum += next % 2 ? 0 : heap[next-1];
    next = (next - 1) >> 1;
    
    while(next > 0) {
        sum += next % 2 ? 0 : heap[next-1];
        next = (next - 1) >> 1;
    }

    return sum;
}

void CoeusHeap::setNewValueAtIndex(int value, int index)
{
    if (index < 0 || index >= numEl) {
        return;
    }

    int next = (heapSize/2 + index);
    heap[next] = value;
    
    next = (next - 1) >> 1;
    while(next >= 0) {
        heap[next] = heap[2*next+1] + heap[2*next+2];
        if (!next) {
            break;
        }
        next = (next - 1) >> 1;
    }
}

void CoeusHeap::setNewValues(int *values, int size)
{
    numEl = size;
    int exp = 1;
    while(size > 0) {
        size >>= 1;
        ++exp;
    }
    
    heapSize = pow(2.0, exp) - 1;
    heap.realloc(heapSize);
    
    heap.clear(heapSize);
    memcpy(heap + heapSize/2, values, numEl*sizeof(int));
}

int CoeusHeap::getValueAt(int index)
{
    return heapSize ? heap[heapSize/2 + index] : 0;
}

int CoeusHeap::getSum() const
{
    return heapSize ? heap[0] : 0;
}

//===============================================================================

CoeusList::CoeusList()
:   sb(true)
{
    selectedRow.add(-1);
    sb.setRangeLimits(0.0, 1.0);
    sb.setCurrentRange(0.0, 0.5, dontSendNotification);
    sb.setAutoHide(true);
    sb.addListener(this);
    sb.setAlwaysOnTop(true);
    addAndMakeVisible(&sb);
}

CoeusList::~CoeusList()
{
    for(int i=0; i < items.size(); i++) {
        if (items[i] != nullptr) {
            delete items[i];
            items.set(i, nullptr);
        }
    }
    
    for(int i=0; i < pool.size(); i++) {
        if (pool[i] != nullptr) {
            delete pool[i];
            pool.set(i, nullptr);
        }
    }
}

CoeusListRowComponent *CoeusList::getComponentForRow(int row) const
{
    return items[itemsToRows.indexOf(row)];
}

void CoeusList::rowChangedSize(int rowNumber, int newSize)
{
    double viewHeight = getViewStartHeight();
    
    heap.setNewValueAtIndex(newSize, rowNumber);
    
    double sbsize = getHeight()/static_cast<double>(heap.getSum());
    sb.setCurrentRange(viewHeight/static_cast<double>(heap.getSum()), sbsize, dontSendNotification);
    
    updateComponents();
    positionComponents();
}

void CoeusList::update()
{
    HeapBlock<int> hb(getNumRows());
    for(int i=0; i<getNumRows(); i++) {
        hb[i] = getRowSize(i);
    }
    
    heap.setNewValues(hb, getNumRows());
    heap.update();
    
    for(int i=0; i<items.size(); i++) {
        if (items[i] != nullptr) {
            removeChildComponent(items[i]);
            items[i]->setVisible(false);
        }
    }
    
    pool.addArray(items);
    items.clear();
    itemsToRows.clear();
    
    double sbsize = getHeight()/static_cast<double>(heap.getSum());
    sb.setCurrentRange(0.0, sbsize, dontSendNotification);
    
    updateComponents();
    positionComponents();
}

void CoeusList::resized()
{
    sb.setBounds(getWidth() - 10, 0, 10, getHeight());
    double sbsize = getHeight()/static_cast<double>(heap.getSum());
    sb.setCurrentRange(0.0, sbsize, dontSendNotification);
    
    updateComponents();
    
    positionComponents();
    
}

void CoeusList::selectRow(int rowNumber)
{
    selectedRow.clear();
    selectedRow.add(rowNumber);
    repaintRow(rowNumber);
}

void CoeusList::paint(Graphics &g)
{
    const int viewHeight = sb.getCurrentRangeStart()*heap.getSum();
    const int startRow = getRowIndexAt(viewHeight);
    const int endRow = jmax(getRowIndexAt(viewHeight+getHeight()+3*getMinRowSize()), startRow);
    for(int i=startRow; i<endRow; i++) {
        paintRowBackground(g, i, 0, getYStartForRow(i)-viewHeight, getWidth(), getRowSize(i), selectedRow.contains(i));
    }
}

void CoeusList::repaintRow(int rowNumber)
{
    // TODO : actually repaint only the requested row...
    repaint();
}

int CoeusList::getRowIndexAt(int y)
{
    return heap.findIndexForSum(y);
}

int CoeusList::getYStartForRow(int index) const
{
    return heap.findSumForIndex(index);
}

int CoeusList::getViewStartHeight() const
{
    return sb.getCurrentRangeStart()*heap.getSum();
}

void CoeusList::updateComponents()
{
    const int viewHeight = getViewStartHeight();
    const int startRow = getRowIndexAt(viewHeight);
    const int endRow = jmax(getRowIndexAt(viewHeight+getHeight()), startRow);
    
    // refresh children content
    for(int r = startRow; r <= endRow; r++) {
        if (items.size() <= r-endRow) {
            CoeusListRowComponent *res = refreshComponentForRow(r, selectedRow.contains(r), nullptr);
            addAndMakeVisible(res);
            items.insert(r-startRow, res);
            itemsToRows.insert(r-startRow, r);
            res->repaint();            
        }
        else {
            CoeusListRowComponent *res = refreshComponentForRow(r, selectedRow.contains(r), items[r-startRow]);
            if (res != items[r-startRow]) {
                if (items[r-startRow] != nullptr) {
                    items[r-startRow]->setVisible(false);
                }
                removeChildComponent(items[r-startRow]);
                addAndMakeVisible(res);
                items.set(r-startRow, res);
            }
            itemsToRows.set(r-startRow, r);
            res->setVisible(true);
            res->repaint();
        }
    }
    
    for (int r=endRow+1 - startRow; r<items.size(); r++) {
        items[r]->setVisible(false);
    }
}

void CoeusList::positionComponents()
{
    const int viewHeight = sb.getCurrentRangeStart()*heap.getSum();
    const int startRow = getRowIndexAt(viewHeight);
    const int endRow = jmax(getRowIndexAt(viewHeight+getHeight()), startRow);
    
    // set bounds
    for(int i=0; i<=endRow-startRow; i++) {
        if (items[i] != nullptr) {
            int itemStartHeight = getYStartForRow(itemsToRows[i]) - viewHeight;
            const int height = heap.getValueAt(startRow+i);
            items[i]->setBounds(0, itemStartHeight, getWidth()-sb.getWidth(), height);
        }
    }
}

void CoeusList::scrollBarMoved (ScrollBar *scrollBarThatHasMoved, double newRangeStart)
{
    // update children content
    // if needed
    updateComponents();
    
    // update children position
    positionComponents();
}

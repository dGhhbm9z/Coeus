//
//  CoeusList.cpp
//  Coeus
//
//  Created by - on 8/10/14.
//
//

#include "CoeusList.h"

//================================================

void CoeusHeap::update()
{
    for(int i=heapSize/2 - 1; i>=0; --i) {
        heap[i] = heap[2*i+1] + heap[2*i+2];
    }
}

int CoeusHeap::findIndexForSum(int sum)
{
    int next = 0;
    
    if (heap[0] < sum) {
        return -1;
    }
    
    while(next >=0 && next < heapSize/2) {
        const int lchld = 2*next+1;
        const int rchld = 2*next+2;
        next = heap[lchld] > sum ? lchld : rchld;
    }
    
    return next;
}

int CoeusHeap::findSumForIndex(int index)
{
    if (index < 0 || index >= numEl) {
        return 0;
    }
    
    int sum = heap[heapSize/2 + index];
    int next = (heapSize/2 + index - 1)  >> 1;
    while(next > 0) {
        sum += next % 2 ? 0 : heap[next-1] + heap[next];
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
    while(next > 0) {
        heap[next] = heap[2*next+1] + heap[2*next+2];
        next = (next - 1) >> 1;
    }
    
}

void CoeusHeap::setNewValues(int *values, int size)
{
    int exp = 0;
    while((size >>= 1) > 1) {++exp;}
    
    heapSize = pow(2.0, exp) - 1;
    heap.realloc(heapSize);
    
    heap.clear(heapSize);
    memcpy(heap + heapSize/2, values, size*sizeof(int));
    numEl = size;
}

//================================================

CoeusList::CoeusList()
:   selectedRow(-1)
{
}

void CoeusList::rowChangedSize(int rowNumber, int newSize)
{
    heap.setNewValueAtIndex(newSize, rowNumber);
}

void CoeusList::update()
{
    HeapBlock<int> hb(getNumRows());
    for(int i=0; i<getNumRows(); i++) {
        hb[i] = getRowSize(i);
    }
    
    heap.setNewValues(hb, getNumRows());
    heap.update();
    
    pool.addArray(items);
    items.clear();
    
    
    
    repaint();
}

void CoeusList::resized()
{
    
}

void CoeusList::selectRow(int rowNumber)
{
    // repaint = sceduling that's why it works
    repaintRow(selectedRow);
    selectedRow = rowNumber;
    repaintRow(selectedRow);
}

void CoeusList::repaintRow(int rowNumber)
{
    
}

int CoeusList::getRowIndexAt(int y)
{
    return heap.findIndexForSum(y);
}

int CoeusList::getYStartForRow(int index)
{
    return heap.findSumForIndex(index);
}
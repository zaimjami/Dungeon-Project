#include "PriorityQueue.hpp"
#include <limits.h>
using namespace std;

void swap(ItemInfo *a, ItemInfo *b)
{
    ItemInfo temp = *a;
    *a = *b;
    *b = temp;
}

/*
Constructor for our heap implementation
Default capacity = 50
*/
PriorityQ::PriorityQ()
{
    capacity = 50;
    heapArr = new ItemInfo[capacity];
    currentSize = 0;
}

PriorityQ::PriorityQ(int cap)
{
    capacity = cap;
    heapArr = new ItemInfo[capacity];
    currentSize = 0;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    if (index == 0) return 0;
    return (index - 1) / 2;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    return 2 * index + 1;
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
    return 2 * index + 2;
}

ItemInfo* PriorityQ::peek()
{
    if (currentSize == 0)
        return nullptr;
    return &heapArr[0];
}

void PriorityQ::heapify(int i)
{
    int largest = i;
    int l = leftChild(i);
    int r = rightChild(i);

    if (l < currentSize && heapArr[l].damage > heapArr[largest].damage)
        largest = l;
    if (r < currentSize && heapArr[r].damage > heapArr[largest].damage)
        largest = r;

    if (largest != i)
    {
        swap(&heapArr[i], &heapArr[largest]);
        heapify(largest);
    }
}

void PriorityQ::insertElement(ItemInfo item)
{
    if (currentSize == capacity)
    {
        cout << "Heap full, cannot insert" << endl;
        return;
    }

    int i = currentSize;
    heapArr[i] = item;
    currentSize++;

    while (i != 0 && heapArr[parent(i)].damage < heapArr[i].damage)
    {
        swap(&heapArr[i], &heapArr[parent(i)]);
        i = parent(i);
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    for (int i = 0; i < currentSize; i++)
    {
        cout << "\t" << "Item: " << heapArr[i].itemName << endl;
        cout << "\t" << "Damage: " << heapArr[i].damage << endl;
        cout << "\t" << "Comment: " << heapArr[i].comment << endl;
        cout << "\t" << "=================" << endl;
    }
}

// Optional function, use if you need to
void PriorityQ::popHelper(int i) {
    // We can just reuse heapify here if needed
    heapify(i);
}

// Method to remove maximum element (root) from max heap
void PriorityQ::pop()
{
    if (currentSize == 0)
    {
        return;
    }

    if (currentSize == 1)
    {
        currentSize = 0;
        return;
    }

    heapArr[0] = heapArr[currentSize - 1];
    currentSize--;
    heapify(0);
}

//
// Created by Admin on 25/05/2018.
//

#ifndef HW2_PRIORITYQUEUE_H
#define HW2_PRIORITYQUEUE_H



#include "Station.h"

#include <vector>
#include <memory>
using namespace std;

// Data structure for Min Heap
class PriorityQueue
{
private:
    // vector to store heap elements
    vector<weak_ptr<Station>> A;

    // return parent of A[i]
    // don't call this function if it is already a root node
    int PARENT(int i)
    {
        return (i - 1) / 2;
    }

    // return left child of A[i]
    int LEFT(int i)
    {
        return (2 * i + 1);
    }

    // return right child of A[i]
    int RIGHT(int i)
    {
        return (2 * i + 2);
    }

    // Recursive Heapify-down algorithm
    // the node at index i and its two direct children
    // violates the heap property
    void heapify_down(unsigned int i);


    // Recursive Heapify-up algorithm
    void heapify_up(unsigned int i);


public:


    // return size of the heap
    unsigned int size()
    {
        return A.size();
    }

    // function to check if heap is empty or not
    bool empty()
    {
        return size() == 0;
    }

    // insert key into the heap

    void push(weak_ptr<Station> key);

    // function to remove element with highest priority (present at root)
    void pop();

    // function to return element with highest priority (present at root)
    Station& top();

    void swap(weak_ptr<Station>x, weak_ptr<Station> y);
};


#endif //HW2_PRIORITYQUEUE_H

//
// Created by Admin on 25/05/2018.
//

#include "PriorityQueue.h"



void PriorityQueue::heapify_down(unsigned int i){
        // get left and right child of node at index i
        unsigned int left = LEFT(i);
        unsigned int right = RIGHT(i);

        unsigned int smallest = i;

        // compare A[i] with its left and right child
        // and find smallest value
        if (left < size() && A[left].lock() < A[i].lock())
            smallest = left;

        if (right < size() && A[right].lock() < A[smallest].lock())
            smallest = right;

        // swap with child having lesser value and
        // call heapify-down on the child
        if (smallest != i) {
            swap(A[i], A[smallest]);
            heapify_down(smallest);
        }
}

void PriorityQueue::heapify_up(unsigned int i) {
        // check if node at index i and its parent violates
        // the heap property
        if (i && A[PARENT(i)].lock() > A[i].lock()) {
            // swap the two if heap property is violated
            swap(A[i], A[PARENT(i)]);

            // call Heapify-up on the parent
            heapify_up(PARENT(i));
        }
}


void PriorityQueue::push(weak_ptr<Station> key) {

    // insert the new element to the end of the vector
    A.push_back(key);

    // get element index and call heapify-up procedure
    unsigned int index = size() - 1;
    heapify_up(index);
}

void PriorityQueue::pop() {
    try {
        // if heap has no elements, throw an exception
        if (size() == 0)
            throw out_of_range("Heap UnderFlow : Out of range index in heap\n");

        // replace the root of the heap with the last element
        // of the vector
        A[0] = A.back();
        A.pop_back();

        // call heapify-down on root node
        heapify_down(0);
    }
        // catch and print the exception
    catch (const out_of_range& oor) {
        cout << "\n" << oor.what();
    }
}

Station& PriorityQueue::top() {
    try {
        // if heap has no elements, throw an exception
        if (size() == 0)
            throw out_of_range("Heap UnderFlow : Out of range index in heap\n");
    }
        // catch and print the exception
    catch (const out_of_range& oor) {
        cout << "\n" << oor.what();
    }
    // else return the top (first) element
        return *(A.at(0).lock());   // or return A[0];
}

void PriorityQueue::swap(weak_ptr<Station> x, weak_ptr<Station> y) {
    weak_ptr<Station> temp = x;
    x=y;
    y=temp;
}


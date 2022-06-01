//
// Created by Utilizador on 30/05/2022.
//

#ifndef DA_PROJECT2_MAXHEAP_H
#define DA_PROJECT2_MAXHEAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <class T>
struct maxHeap{
private:
    std::vector<
            std::pair<int, T>> A;

    int PARENT(int i){ return (i - 1) / 2; }
    int LEFT(int i)  { return (2*i + 1);   }
    int RIGHT(int i) { return (2*i + 2);   }

    void swapValues( std::pair<int, T> &V1,std::pair<int, T> &V2){
        auto temp = V1;
        V1 = V2;
        V2 = temp;
    }

    void heapify_down(int i)
    {
        int left = LEFT(i);
        int right = RIGHT(i);

        int largest = i;


        if (left < size() && A[left].first > A[i].first) {
            largest = left;
        }

        if (right < size() && A[right].first > A[largest].first ) {
            largest = right;
        }

        if (largest != i)
        {
            swapValues(A[i], A[largest]);
            heapify_down(largest);
        }
    }

    void heapify_up(int i)
    {
        if (i && A[PARENT(i)].first < A[i].first)
        {
            // swap the two if heap property is violated
            swapValues(A[i], A[PARENT(i)]);

            // call heapify-up on the parent
            heapify_up(PARENT(i));
        }
    }

public:
    // return size of the heap
    unsigned int size() {
        return A.size();
    }

    // Function to check if the heap is empty or not
    bool empty() {
        return size() == 0;
    }

    // insert key into the heap
    void push(int i, T value)
    {
        // insert a new element at the end of the vector
        A.push_back(
                std::pair<int, T>(
                        i,
                        value
                        ));

        // get element index and call heapify-up procedure
        int index = size() - 1;
        heapify_up(index);
    }

// Function to remove an element with the highest priority (present at the root)
    void pop()
    {
        try {
            // if the heap has no elements, throw an exception
            if (size() == 0)
            {
                throw std::out_of_range("Vector<X>::at() : "
                                   "index is out of range(Heap underflow)");
            }

            // replace the root of the heap with the last element
            // of the vector
            A[0] = A.back();
            A.pop_back();

            // call heapify-down on the root node
            heapify_down(0);
        }
            // catch and print the exception
        catch (const std::out_of_range &oor) {
            std::cout << std::endl << oor.what();
        }
    }
// Function to return an element with the highest priority (present at the root)
    std::pair<int, T> top()
    {
        try {
            // if the heap has no elements, throw an exception
            if (size() == 0)
            {
                throw std::out_of_range("Vector<X>::at() : "
                                   "index is out of range(Heap underflow)");
            }

            // otherwise, return the top (first) element
            return A.at(0);        // or return A[0];
        }
            // catch and print the exception
        catch (const std::out_of_range &oor) {
            std::cout << std::endl << oor.what();
        }
        //return std::pair<int, T> (0, NULL);
    }
};

#endif //DA_PROJECT2_MAXHEAP_H

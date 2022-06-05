#ifndef DA_PROJECT2_MAXHEAP_H
#define DA_PROJECT2_MAXHEAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


template <class T>

struct maxHeap{
private:
    /**
     * Elements of a MaxHeap, with the capacity of the path until a node and the node's index in the graph.
     */
    std::vector<
            std::pair<int, T>> A;

    /**
     * This method calculates the parent of an element.
     * @param i Element of the maxHeap.
     * @return Parent of i.
     */
    int PARENT(int i){ return (i - 1) / 2; }

    /**
     * This method calculates the left child of an element.
     * @param i Element of the maxHeap.
     * @return Left child of i.
     */
    int LEFT(int i)  { return (2*i + 1);   }
    /**
    * This method calculates the right child of an element.
    * @param i Element of the maxHeap.
    * @return Right child of i.
    */
    int RIGHT(int i) { return (2*i + 2);   }

    /**
     * This method swaps positions of 2 elements of the maxHeap.
     * @param V1 First value to be swapped.
     * @param V2 Second value that will swap position with V1.
     */
    void swapValues( std::pair<int, T> &V1,std::pair<int, T> &V2){
        auto temp = V1;
        V1 = V2;
        V2 = temp;
    }

    /**
     * This method will make an element "goes" down in the maxHeap, by comparing with its children and swapping with the parent.
     * @param i Element to heapify down.
     */
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

    /**
     * This method will make an element "goes" up in the maxHeap, by comparing with its children and swapping with the parent.
     * @param i Element to heapify up.
     */
    void heapify_up(int i)
    {
        if (i && A[PARENT(i)].first < A[i].first)
        {
            swapValues(A[i], A[PARENT(i)]);
            heapify_up(PARENT(i));
        }
    }

public:
    /**
     *
     * @return maxHeap's size.
     */
    unsigned int size() {
        return A.size();
    }

    /**
     * This method checks whether the maxHeap is empty or not.
     * @return Returns true if the maxHeap is empty, otherwise it returns false.
     */
    bool empty() {
        return size() == 0;
    }

    /**
     * This method inserts an element in the maxHeap and puts it in the correct position.
     * @param i Capacity of the path until the input node.
     * @param value Index of the input node in the graph.
     */
    void push(int i, T value)
    {
        A.push_back(
                std::pair<int, T>(
                        i,
                        value
                        ));

        int index = size() - 1;
        heapify_up(index);
    }

    /**
     * This method removes an element of the maxHeap and corrects the position of the other elements.
     */
    void pop()
    {
        try {
            if (size() == 0)
            {
                throw std::out_of_range("Vector<X>::at() : "
                                   "index is out of range(Heap underflow)");
            }
            A[0] = A.back();
            A.pop_back();

            heapify_down(0);
        }
        catch (const std::out_of_range &oor) {
            std::cout << std::endl << oor.what();
        }
    }
    /**
     * This method gives the first element inserted in the maxHeap, in case it is not empty.
     * @return It returns the first element of the maxHeap.
     */
    std::pair<int, T> top()
    {
        try {
            if (size() == 0)
            {
                throw std::out_of_range("Vector<X>::at() : "
                                   "index is out of range(Heap underflow)");
            }

        }
        catch (const std::out_of_range &oor) {
            std::cout << std::endl << oor.what();
        }
        return A.at(0);
    }
};

#endif //DA_PROJECT2_MAXHEAP_H

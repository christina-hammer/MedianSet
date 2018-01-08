//Author: Christina Hammer
//Last Edit: 1/06/2018
//Status: In the middle of writing functionality for the MedianSet class

/*
Created to solve this HackerRank exercise: https://www.hackerrank.com/challenges/ctci-find-the-running-median/problem

This solution will be able to generalizes beyond the problem in that:
-MedianSet will dynamically resize to continue functiong normally if given more elements than the initially specified number
-MedianSet will handle negative values in addition to positive values
-MedianSet will support a 'pop()' function to remove and replace the current Median element if possible
*/

#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>


using namespace std;

class BinaryHeap{
    public:
    BinaryHeap(int _capacity): size(0), capacity(_capacity) {
        theheap = new int[capacity];
    }
    virtual ~BinaryHeap() {delete [] theHeap;}
    
    int checkTop() const {
        if (size < 1) return -1;
        return theheap[0];
    }
    int size() const {return size;}
    
    void insert(int const val) {_insert(val)};
    int extractTop() {return _extractTop();}
    
    protected:
    int* theheap;
    int capacity;
    int size;
    int invalid;
    
    virtual bool swapUpCheck(int i);
    virtual bool swapDownCheck(int i, int check);
    
    void doubleCapacity() {        
        int* doubletheheap = new int[capacity*2];
        memcpy(doubletheheap, theheap, size*sizeof(int));
        capacity = capacity*2;
        delete [] theheap;
        theheap = doubletheheap;        
    }
    
    void bubbleUp(int i) {   
         if (swapUpCheck(i)) {swap(i, parent(i));}
         else {return;}
         bubbleUp(parent(i));
    }
    
    void bubbleDown(int i) {              
         int swap_with = swapDownCheck(i, left(i)));
         swap_with = swapDownCheck(swap_with, right(i));
         if (swap(i, swap_with)) bubbleDown(swap_with);
    }
    
    //add value to heap
    void _insert(int const val) {
        if (capacity == size) {doubleCapacity();}       
        //put new value in next available space
        theheap[size] = val;
        size++;
        if (size > 2) bubbleUp(size-1);      
    }
    
    //return top value and remove from heap
    int extractTop() {
        if (size < 1) return -1;        
        int old_top = theheap[0];
        theheap[0] = theheap[size-1];
        size--;
        if (size > 2) bubbleDown(0);
        return old_top;
    }
    
    int parent(int i) { return i/2; }    
    int left(int i) { return 2*i+1; }    
    int right(int i) { return 2*i+2; }
    
    bool swap(int i, int j) {
        if (i == j) return false;
        if (i < 0 || i >= size) return false;
        if (j < 0 || j >= size) return false;
        int temp = theheap[i];
        theheap[i] = theheap[j];
        theheap[j] = temp;
        return true;
    }
    
};


class MinHeap : public BinaryHeap {
    public:
        ~MinHeap() { delete [] theheap; }
    private:
    
    bool swapUpCheck(int i) {
        if (i == 0) return false;
        return theheap[i] < theheap[parent(i)];
    }
    
    int swapDownCheck(int i, int check) {
        if (check > size || theheap[i] < theheap[check]) return i;
        return check;
    }
    
};

class MaxHeap : public BinaryHeap {
    public:
        ~MaxHeap() { delete [] theheap; }
    private:   
    
    bool swapUpCheck(int i) {return theheap[i] > theheap[parent(i)];}
    int swapDownCheck(int i, int check) {
        if (check > size || theheap[i] > theheap[check]) return i;
        return check;
    }
    
};

class MedianSet {
    public:
    MedianSet(int _set_size) {
        median = INT_MIN; //default value indicating an empty MedianSet
        num_elements = 0;
        smaller = new MaxHeap(_set_size);
        larger = new MinHeap(_set_size);
    }
    
    int getMedian() {
        if (isEmpty()) { cerr<<"ERROR: MedianSet is empty\n"; }//
        return median;
    }
    
    bool isEmpty() {return num_elements==0;}
    void add
    
    private:
    int median;
    int num_elements;
    MaxHeap smaller; //numbers smaller than the median are stored in this MaxHeap
    MinHeap larger; //numbers larger than the median are stored in this MinHeap
    
    
};


int main(){
    int n, a;
    cin >> n;
    
    MedianSet* med = new MedianSet(n);

    for(int i = 0; i < n; i++){
       cin>>a;
       med->add(a);
       med.getMedian();
    }

    delete med;
    return 0;
}

//Author: Christina Hammer
//Last Edit: 1/06/2018
//Status: In the middle of writing functionality for the MedianSet class

/*
Created to solve this HackerRank exercise: https://www.hackerrank.com/challenges/ctci-find-the-running-median/problem

This solution will be able to generalizes beyond the problem in that:
-MedianSet will dynamically resize to continue functiong normally if given more elements than the initially specified number
-MedianSet will handle negative values in addition to positive values
*/

#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace std;

class BinaryHeap{
    public:
    BinaryHeap(int _capacity): heapsize(0), capacity(_capacity) {
        theheap = new int[capacity];
    }
    virtual ~BinaryHeap() {delete [] theheap;}
    
    //ACCESSORS
    int checkTop() const {
        if (heapsize < 1) return -1;
        return theheap[0];
    }
    int size() const {return heapsize;}
    
    //MODIFERS
    void insert(int const val) {_insert(val);}
    int extractTop() {return _extractTop();}
    
    protected:
    int* theheap;
    int capacity;
    int heapsize;
    int invalid;
    
    virtual bool swapUpCheck(int i) = 0;
    virtual int swapDownCheck(int i, int check) = 0;
    
    void doubleCapacity() {        
        int* doubletheheap = new int[capacity*2];
        memcpy(doubletheheap, theheap, heapsize*sizeof(int));
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
         int swap_with = swapDownCheck(i, left(i));
         swap_with = swapDownCheck(swap_with, right(i));
         if (swap(i, swap_with)) bubbleDown(swap_with);
    }
    
    //add value to heap
    void _insert(int const val) {
        if (capacity == heapsize) {doubleCapacity();}       
        //put new value in next available space
        theheap[heapsize] = val;
        heapsize++;
        if (heapsize > 2) bubbleUp(heapsize-1);      
    }
    
    //return top value and remove from heap
    int _extractTop() {
        if (heapsize < 1) return -1;        
        int old_top = theheap[0];
        theheap[0] = theheap[heapsize-1];
        heapsize--;
        if (heapsize > 2) bubbleDown(0);
        return old_top;
    }
    
    int parent(int i) { return i/2; }    
    int left(int i) { return 2*i+1; }    
    int right(int i) { return 2*i+2; }
    
    bool swap(int i, int j) {
        if (i == j) return false;
        if (i < 0 || i >= heapsize) return false;
        if (j < 0 || j >= heapsize) return false;
        int temp = theheap[i];
        theheap[i] = theheap[j];
        theheap[j] = temp;
        return true;
    }
    
};


class MinHeap : public BinaryHeap {
    public:
        MinHeap(int set_size):BinaryHeap(set_size){}
        ~MinHeap() { delete [] theheap; }
    private:
    
    bool swapUpCheck(int i) {
        if (i == 0) return false;
        return theheap[i] < theheap[parent(i)];
    }
    
    int swapDownCheck(int i, int check) {
        if (check > heapsize || theheap[i] < theheap[check]) return i;
        return check;
    }
    
};

class MaxHeap : public BinaryHeap {
    public:
        MaxHeap(int set_size):BinaryHeap(set_size){}
        ~MaxHeap() { delete [] theheap; }
    private:   
    
    bool swapUpCheck(int i) {return theheap[i] > theheap[parent(i)];}
    int swapDownCheck(int i, int check) {
        if (check > heapsize || theheap[i] > theheap[check]) return i;
        return check;
    }
    
};

class MedianSet {
    public:
    MedianSet(int _set_size) {
        
        num_elements = 0;
        smaller = new MaxHeap(_set_size);
        larger = new MinHeap(_set_size);
    }
   ~MedianSet() {
       delete smaller;
       delete larger;
   }
    //ACCESSORS
    int getMedian() {
        if (num_elements == 0) { 
            cerr<<"ERROR: MedianSet is empty\n"; 
            return INT_MIN;
        }
        return _calcMedian();
    }
    
    bool isEmpty() {return num_elements==0;} //indicates whether the MedianSet is empty
    
    //MODIFIERS
    void add(int const value) {_add(value);} //adds value to the MedianSet
    
    private:
    
    int num_elements;
    MaxHeap* smaller; //numbers smaller than the median are stored in this MaxHeap
    MinHeap* larger; //numbers larger than the median are stored in this MinHeap
    
    void _add(int const value) {
        if (num_elements == 0) {
            num_elements++;
            smaller->insert(value);
        }
        if (value >= smaller->checkTop() && value <= larger->checkTop()) {
            if (smaller->size() > larger->size()) larger->insert(value);
            else{
                smaller->insert(value);
            }
        }
        else if (value < smaller->checkTop()) {
            larger->insert(smaller->extractTop());
            smaller->insert(value);
        }
        else {
            smaller->insert(larger->extractTop());
            larger->insert(value);
        }
        num_elements++;
        return;
    }
    
    int _calcMedian(){
        if (smaller->size() > larger->size()) return smaller->checkTop();
        if (larger->size() > smaller->size()) return larger->checkTop();
        return (smaller->checkTop() + larger->checkTop())/2;
    }
    
    
};


int main(){
    int n, a;
    cin >> n;
    
    MedianSet* med = new MedianSet(n);

    for(int i = 0; i < n; i++){
       cin>>a;
       med->add(a);
       cout<<med->getMedian()<<endl;
    }

    delete med;
    return 0;
}

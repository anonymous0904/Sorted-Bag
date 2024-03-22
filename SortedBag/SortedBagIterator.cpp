#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>
using namespace std;


SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	current=bag.root;//position of current elem in sortedBag array
    stack_size=0;
    stack_capacity=10;
    stack=new int [stack_capacity];//stack with the positions of the elements in the sortedBag
    while (current!=-1){//in-order traversal
        stack[stack_size]=current;
        stack_size++;
        if(stack_size==stack_capacity){
            extend_stack();
        }
        current=bag.sortedBag[current].left;
    }
    if(stack_size){//stack is not empty
        current=stack[stack_size-1];
    }
    else{
        current=-1;
    }
}



TComp SortedBagIterator::getCurrent() {
    if(not valid()){
        throw runtime_error("");
    }
    return bag.sortedBag[current].info;

}

bool SortedBagIterator::valid() {
	if(current!=-1){
        return true;
    }
	return false;
}

void SortedBagIterator::next() {
    if (not valid()) {
        throw runtime_error("");
    }
    int pos=0;
    if(stack_size){
        pos=stack[stack_size-1];
        stack_size--;
    }
    if (bag.sortedBag[pos].right != -1) {
        pos = bag.sortedBag[pos].right;
        while (pos != -1) {
            if (stack_size == stack_capacity) {
                extend_stack();
            }
            stack[stack_size] = pos;
            pos = bag.sortedBag[pos].left;
            stack_size++;
        }
    }

    if (stack_size) {
        current = stack[stack_size - 1];
    }
    else{
        current = -1;
    }
}

void SortedBagIterator::first() {
	current=bag.root;
    stack_size=0;
    while (current!=-1){//in-order traversal
        stack[stack_size]=current;
        stack_size++;
        if(stack_size==stack_capacity){
            extend_stack();
        }
        current=bag.sortedBag[current].left;
    }
    if(stack_size){//stack is not empty
        current=stack[stack_size-1];
        stack_size--;
    }
    else{
        current=-1;
    }
}

void SortedBagIterator::extend_stack() {
    auto *aux=new int [stack_capacity*2];
    for(int i=0;i<stack_capacity;i++){
        aux[i]=stack[i];
    }
    delete[] stack;
    stack=aux;
    stack_capacity*=2;
}

void SortedBagIterator::shrink_stack() {
    auto *aux=new int [stack_capacity/2];
    for(int i=0;i<stack_size;i++){
        aux[i]=stack[i];
    }
    delete[]stack;
    stack=aux;
    stack_capacity/=2;
}

#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

SortedBag::SortedBag(Relation r) {
	relation=r;
    nrElem=0;
    root=-1;
    capacity=10;
    firstEmpty=0;
    sizeArray=0;
    sortedBag=new Node[capacity];

    for(int i=0;i<capacity-1;i++){
        sortedBag[i].right=i+1;
    }
    sortedBag[capacity-1].right=-1;

    for(int i=0;i<capacity;i++){
        sortedBag[i].left=-1;
    }
}

SortedBag::SortedBag(const SortedBag&original) {
    this->relation=original.relation;
    this->nrElem=original.nrElem;
    this->root=original.root;
    this->capacity=original.capacity;
    this->firstEmpty=original.firstEmpty;
    this->sizeArray=original.sizeArray;
    this->sortedBag=new Node[this->capacity];
    for(int i=0;i<capacity;i++){
        this->sortedBag[i].info=original.sortedBag[i].info;
        this->sortedBag[i].left=original.sortedBag[i].left;
        this->sortedBag[i].right=original.sortedBag[i].right;
        this->sortedBag[i].frequenz=original.sortedBag[i].frequenz;
    }
}


void SortedBag::add(TComp e) {
    nrElem++;
    int currentPos=root;
    int parentPos=-1;
    while(currentPos!=-1 and sortedBag[currentPos].info!=e){
        parentPos=currentPos;
        if(relation(sortedBag[currentPos].info,e)){
            currentPos=sortedBag[currentPos].right;
        }
        else{
            currentPos=sortedBag[currentPos].left;
        }
    }
    if(currentPos!=-1){
        if(sortedBag[currentPos].info==e) {
            sortedBag[currentPos].frequenz++;
        }
    }
    else{
        if(sizeArray+1==capacity){
            extendArray();
        }

        int newPos=firstEmpty;//add new value
        firstEmpty=sortedBag[firstEmpty].right;
        sortedBag[newPos].info=e;
        sortedBag[newPos].frequenz=1;
        sortedBag[newPos].left=sortedBag[newPos].right=-1;
        sizeArray++;
        if(parentPos==-1){//array is empty
            root=newPos;
        }
        else{
            if(relation(sortedBag[parentPos].info,e)){
                sortedBag[parentPos].right=newPos;
            }
            else{
                sortedBag[parentPos].left=newPos;
            }
        }
    }
}

bool SortedBag::remove(TComp e) {
    int currentPos=root;
    int parentPos=-1;
    while(currentPos!=-1 and sortedBag[currentPos].info!=e){//search the correct position of e
        parentPos=currentPos;
        if(relation(sortedBag[currentPos].info,e)){
            currentPos=sortedBag[currentPos].right;
        }
        else{
            currentPos=sortedBag[currentPos].left;
        }
    }
    if(currentPos==-1){//e is not in the BST
        return false;
    }
    if(sortedBag[currentPos].frequenz>1){
        sortedBag[currentPos].frequenz--;
        nrElem--;
        return true;
    }
    else{
        if(sortedBag[currentPos].left==-1){//only a single occurrence of e in BST
            if(parentPos==-1){//remove the root
                root=sortedBag[currentPos].right;
            }
            else{
                if(relation(sortedBag[parentPos].info,e)){
                    sortedBag[parentPos].right=sortedBag[currentPos].right;
                }
                else{
                    sortedBag[parentPos].left=sortedBag[currentPos].right;
                }
            }
            //the node is deleted from the subtree
            int next_empty=firstEmpty;
            firstEmpty=currentPos;
            sortedBag[firstEmpty].right=next_empty;
            sortedBag[firstEmpty].left=-1;
            sizeArray--;
            nrElem--;
            return true;
        }
        else if(sortedBag[currentPos].right==-1){
            if(parentPos==-1){
                root=sortedBag[currentPos].left;
            }
            else{
                if(relation(sortedBag[parentPos].info,e)){
                    sortedBag[parentPos].right=sortedBag[currentPos].left;
                }
                else{
                    sortedBag[parentPos].left=sortedBag[currentPos].left;
                }
            }

            int next_empty=firstEmpty;
            firstEmpty=currentPos;
            sortedBag[firstEmpty].right=next_empty;
            sortedBag[firstEmpty].left=-1;
            sizeArray--;
            nrElem--;
            return true;
        }
        else{//e has both a left and a right child
            //replace the element with the leftmost neighbour from the right subtree
            int next_node_pos=sortedBag[currentPos].right;
            int prev_next=currentPos;
            while(sortedBag[next_node_pos].left!=-1){
                prev_next=next_node_pos;
                next_node_pos=sortedBag[next_node_pos].left;
            }
            sortedBag[currentPos].info=sortedBag[next_node_pos].info;
            sortedBag[currentPos].frequenz=sortedBag[next_node_pos].frequenz;
            sortedBag[prev_next].left=-1;
            sizeArray--;
            nrElem--;
            return true;
        }
    }
}

void SortedBag::extendArray() {
    Node *aux=new Node[capacity*2];
    for(int i=0;i<capacity;i++){
        aux[i]=sortedBag[i];
    }
    delete[]sortedBag;
    sortedBag=aux;
    if(firstEmpty==-1){
        firstEmpty=capacity;
    }
    capacity*=2;
    for(int i=firstEmpty;i<capacity-1;i++){
        sortedBag[i].right=i+1;
    }
    sortedBag[capacity-1].right=-1;
    sortedBag[firstEmpty].left=-1;
    for(int i=firstEmpty+1;i<capacity;i++){
        sortedBag[i].left=-1;
    }
}

bool SortedBag::search(TComp elem) const {
	int currentPos=root;
    while (currentPos!=-1){
        if(sortedBag[currentPos].info==elem){
            return true;
        }
        else if(relation(sortedBag[currentPos].info,elem)){
            currentPos=sortedBag[currentPos].right;
        }
        else{
            currentPos=sortedBag[currentPos].left;
        }
    }
	return false;
}

int SortedBag::nrOccurrences(TComp elem) const {
	int currentPos=root;
    while (currentPos!=-1){
        if(sortedBag[currentPos].info==elem){
            return sortedBag[currentPos].frequenz;
        }
        else if(relation(sortedBag[currentPos].info,elem)){
            currentPos=sortedBag[currentPos].right;
        }
        else{
            currentPos=sortedBag[currentPos].left;
        }
    }
	return 0;
}



int SortedBag::size() const {
    return nrElem;
}


bool SortedBag::isEmpty() const {
    return nrElem==0;
}

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

SortedBag::~SortedBag() {
	delete[]sortedBag;
}

void SortedBag::print() {
    SortedBagIterator it= this->iterator();
    while(it.valid()){
        cout<<it.getCurrent()<<" ";
        it.next();
    }
}


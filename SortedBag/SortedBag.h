#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

struct Node{
    TComp info;
    int frequenz;
    int left;
    int right;
};

class SortedBag {
	friend class SortedBagIterator;

private:
	Relation relation;
    int capacity;
    int root;
    int nrElem;
    int sizeArray;
    int firstEmpty;
    Node *sortedBag;
    void extendArray();

public:
	//constructor
	SortedBag(Relation r);
    //copy constructor
    SortedBag(const SortedBag&original);

	//adds an element to the sorted bag
	void add(TComp e);

    //prints the elements of the bag
    void print();

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();
};
#pragma once
#include "SortedBag.h"
using namespace std;
class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	int current;
    int *stack;
    int stack_size;
    int stack_capacity;


public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
    void extend_stack();
    void shrink_stack();
};


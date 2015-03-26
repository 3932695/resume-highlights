#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

template <class T>
class node {
public:  
    node(T value, node<T>* plink = NULL, node<T>* nlink = NULL) 
    	: data(value), prior(plink), next(nlink) 
    {}
	
	T data;
	node<T>* prior;
	node<T>* next;
};
#endif

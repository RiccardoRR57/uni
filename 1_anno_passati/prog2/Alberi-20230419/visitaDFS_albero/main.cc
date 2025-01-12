/*
 * main.cc
 *
 *  Created on: 21 mag 2018
 *      Author: federica
 */


#define DEBUG

#include <iostream>
using namespace std;

#include "tipo.h"
#include "tree.h"
#include "coda-bfs.h"

void serialize(tree t){
	cout<<"(";
	print(get_info(t));
	tree t1 = get_firstChild(t);
	while(t1!=NULL){
		serialize(t1);
		t1 = get_nextSibling(t1);
	}
	cout<<")";
}

int altezza(tree t) {
	tree t1 = get_firstChild(t);

	int alt = 0;
	while(t1 != NULL) {
		if(altezza(t1) >= alt) {
			alt = altezza(t1) + 1;
		}
		t1 = get_nextSibling(t1);
	}

	return alt;
}

int dimensione(tree t) {
	int dim = 0;
	node *n, *son;
	codaBFS q = newQueue();
	q = enqueue(q, t);
	
	while(!isEmpty(q)) {
		n = dequeue(q);
		dim++;
		
		son = get_firstChild(n);
		while(son != NULL) {
			q = enqueue(q, son);
			son = get_nextSibling(son);
		}
	}
	return dim;
}

int main(){
	tree t=NULL;

	t=new_node("Luca");
	node* n=new_node("Paolo");
	insert_child(t,n);
	n=new_node("Marco");
	insert_sibling(t->firstChild,n);
	n=new_node("Lucia");
	insert_child(t->firstChild->nextSibling,n);
	node* m=new_node("Anna");
	insert_sibling(n->parent,m);
#ifdef DEBUG
	serialize(t);
	cout << endl << dimensione(t) << endl;
#endif

}

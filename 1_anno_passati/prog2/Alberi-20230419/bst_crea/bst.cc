/*
 * tree.cc
 *
 *  Created on: 14 mag 2018
 *      Author: federica
 */
#include <iostream>
using namespace std;

#include <cstring>

#include "tipo.h"
#include "bst.h"

static tipo_key copy_key(tipo_key& s,tipo_key s1){
	s=s1;
	return s;
}

static tipo_key compare_key(tipo_key s,tipo_key s1){
		return s-s1;
}

tipo_key get_key(bnode* n){
	return (n->key);
}

tipo_inf get_value(bnode* n){
	return (n->inf);
}

bst get_left(bst t){
	return (t->left);
}

bst get_right(bst t){
	return (t->right);
}

bnode* get_parent(bnode* n){
	return (n->parent);
}

bnode* bst_newNode(tipo_key k, tipo_inf i){
	bnode* n=new bnode;
	copy(n->inf,i);
	copy_key(n->key,k);
	n->right=n->left=n->parent=NULL;
	return n;
}

void bst_insert(bst& b, bnode* n){
	
	if(b == NULL) {
		b = n;
		return;
	}
	bst next;
	if(compare_key(get_key(n), get_key(b)) <= 0) {
		next = get_left(b);
	}
	else {
		next = get_right(b);
	}

	if(next == NULL) {
		n->parent = b;
	}

	bst_insert(next, n);
}

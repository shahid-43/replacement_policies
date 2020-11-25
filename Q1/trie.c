#include <stdio.h>
#include <stdlib.h>
#include "trie.h"


typedef struct node { 
    int value;
    bool is_end;
    // #ifndef _NO_HOH_LOCK_TRIE
    // pthread_mutex_t node_lock;
    // #endif
    struct node* children[26];   // Array mapping character to the next node
} _trie_node_t;

typedef _trie_node_t* trie_node_t;

typedef struct {
    trie_node_t head; // The head/start node of trie
    // Add whatever variables you require for locking here
} _trie_t;

typedef _trie_t* trie_t;


trie_t init_trie(void){
    // Write your code here
    trie_t trie = (_trie_t*)malloc(sizeof(_trie_t));
    
    trie_node_t node = (_trie_node_t*)malloc(sizeof(_trie_node_t));
    node->is_end = true;
    node->value = -1;
    for (int i = 0; i < 26; i+=1)
    {
        node->children[i] = NULL;
    }
    trie->head = node;
    
    return trie;
}
    
 

void insert(trie_t trie, char* key, int value){
    trie_node_t curr = trie->head;
	while (*key)
	{
		// create a new node if path doesn't exists
		if (curr->children[*key - 'a'] == NULL){
			curr->children[*key - 'a'] = init_trie()->head;
        }

		// go to next node
		curr = curr->children[*key - 'a'];

		// move to next character
		key++;
	}

	// mark current node as leaf
	curr->is_end = true;
    curr->value = value;
    return;

}

int find(trie_t trie,char* key, int* val_ptr){
   // return 0 if Trie is empty
	if (trie->head == NULL){
        printf("-1");
    
		return 0;
    }

	trie_node_t curr = trie->head;
	while (*key)
	{
		// go to next node
		curr = curr->children[*key - 'a'];

		// if string is invalid (reached end of path in Trie)
		if (curr == NULL ){

            
			return -1;
        }
        
		// move to next character
		key++;
	}
    if (curr != NULL){
        if(curr->is_end == true){
            return 0;
        }
    else{
        curr->value = *val_ptr;
    }
	// if current node is a leaf and we have reached the
	// end of the string, return 1
    
	return 0;

} 
}

void delete_kv(trie_t trie, char* key){
    return;
}


char** keys_with_prefix(trie_t trie, char* prefix){
    // Write your code here
    char** list = malloc(sizeof(char*));
    list[0] = NULL;
    return list;
}

void delete_trie(trie_t trie){
    return ;
}

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//#define Not_Found 65535 // for 2 bytes
#define Not_Found  4294967295 // for 4 bytes
//#define Not_Found  16777216 // for 3 bytes

typedef struct Node_element {
  char character; // character of the node 
  struct Node_element * parent;// parent for lexical order
  struct Node_element * right_child; // next character in the string
  struct Node_element * left_child; // replacement of the curent character
  unsigned int index; // index
} Node_element ; 

typedef Node_element* Dictionary_tree; 

Node_element * create_Node_element (char c ,Node_element * parent, Node_element * right_child, Node_element * left_child , int index);
unsigned int rec_research_in_dico_tree ( char * list_c, int size, Dictionary_tree dico_tree, Node_element ** last_position_research , int * r_or_l, int * is_smaller_then_last) ;
unsigned int research_in_dico_tree ( char * list_c, int size, Dictionary_tree dico_tree, Node_element ** last_position_research , int * r_or_l, int * is_smaller_then_last);
void add_char_dico_tree(Dictionary_tree* dico_tree, char c, Node_element * last_position_research , int * r_or_l , unsigned int place, int * is_smaller_then_last);
void add_base_dico_tree(Dictionary_tree* dico_tree);
void print_dico_tree(Dictionary_tree dico_tree);
void free_dico_tree(Dictionary_tree dico_tree);
void print_simple_dico_tree(Dictionary_tree dico_tree);

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define Not_Found  4294967295 // for 4 bytes

typedef struct element {
  int size_element;
  unsigned int* list_unsigned_int;
} element ; 

typedef struct dictionary {
  int size;
  element* list_elements;
} dictionary; 


element create_element( unsigned int* list_element, int size_element);
/*fuction that print elements for debuging*/
void print_elem(element e);
/*print dictionary for debuging*/
void print_dico(dictionary dico);
/*put all base alphabet in dico*/
void put_all_base_alphabet(int size_base, dictionary* dico);
/*put a new element in dico*/
void put_new_element(unsigned int* list_element, int size_elem, dictionary* dico);
unsigned int research_element_decomp (unsigned int place, dictionary dico);

void free_elem(element* e );
void free_dico(dictionary* dico);


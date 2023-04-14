#include "temporary_lists_gestion.h"
#include "dictionary_table.h"

element create_element( unsigned int* list_element, int size_element){
	element elem ;
	elem.size_element = size_element;
	elem.list_unsigned_int = list_element; 
	return elem;
}


/*fuction that print elements for debuging*/
void print_elem(element e){
	int i, size = e.size_element;
	unsigned int* list_s = e.list_unsigned_int;
	
	printf("\nList size: %d, ", size);
	for(i=0; i<size; i++){
		printf("%hd, ",list_s[i]);
	}
}

/*print dictionary for debuging*/
void print_dico(dictionary dico){
	int i, size = dico.size;
	element* list_e = dico.list_elements;
	
	printf("\nDico size : %d, ", size);
	for(i=0; i<size; i++){
		print_elem(list_e[i]);
	}
}

/*put all base alphabet in dico*/
void put_all_base_alphabet(int size_base, dictionary* dico){
	int i;
	dico->list_elements = (element*)malloc( size_base * sizeof(element));
	assert( dico->list_elements!= NULL );
	 
	dico->size = size_base;
	
	unsigned int* list_unsigned_int =(unsigned int*)malloc(sizeof(unsigned int));
	assert( list_unsigned_int != NULL );
		
	for(i=0;i<size_base;i++){
		list_unsigned_int[0] =(unsigned int) i;
		dico->list_elements[i] = create_element( copy_unsigned_int_list (list_unsigned_int, 1),1);
	};
	free(list_unsigned_int);
}

/*put a new element in dico*/
void put_new_element(unsigned int* list_element, int size_elem, dictionary* dico){
	dico->size++;
	dico->list_elements = (element*)realloc(dico->list_elements, dico->size * sizeof(element));
	assert( dico->list_elements!= NULL );
	dico->list_elements[dico->size-1] = create_element(list_element, size_elem);
}

unsigned int research_element_decomp (unsigned int place, dictionary dico){
	if (place >= (unsigned int)dico.size){return Not_Found;}
	return place;
}


void free_elem(element* e ){
	
	free(e->list_unsigned_int);
}

void free_dico(dictionary* dico){
	int i, size = dico->size;
	element* list_e = dico->list_elements;
	
	for(i=0; i<size; i++){
		free_elem(&list_e[i]);
	}
	/*fprintf(stdout, "in \033[31m<free_dico>\033[39m: free(\033[33m%p\033[39m);\n", dico->list_elements);*/
	 free(dico->list_elements);
}



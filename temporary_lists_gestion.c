#include "temporary_lists_gestion.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*int list*/
Temp_list_int create_temp_list_int (unsigned int * list, int size) {
	Temp_list_int tl;
	tl.size = size;
	tl.list_int = list;
 return tl;
}

void add_int_temp_list ( Temp_list_int * temp_list, unsigned int sho){
	temp_list->size++; 
	temp_list->list_int =(unsigned int*)realloc(temp_list->list_int, temp_list->size * sizeof(unsigned int));
	assert( temp_list->list_int!= NULL );
	temp_list->list_int[temp_list->size-1] = sho ;
}

void free_temp_list_int ( Temp_list_int* tl ) {
	tl->size = 0;
	free(tl->list_int);
}

void print_Temp_list_int (Temp_list_int tl){
	int i;
    printf("\n");
	printf("Size list = %d ",tl.size );
	for(i=0;i<tl.size;i++){
		printf("%u, ",tl.list_int[i] );
	}
}

void add_unsigned_int_temp_list ( Temp_list_int * temp_list, unsigned int sho){
	temp_list->size++; 
	temp_list->list_int = (unsigned int*)realloc(temp_list->list_int, temp_list->size * sizeof(unsigned int));
	assert( temp_list->list_int != NULL );
	temp_list->list_int[temp_list->size-1] = sho ;
}


void overwrite_int (Temp_list_int * old_temp_list, Temp_list_int * new_temp_list){
	int i;
	
	old_temp_list->size = new_temp_list->size;
	old_temp_list->list_int = (unsigned int*)realloc(old_temp_list->list_int, new_temp_list->size * sizeof(unsigned int));
	
	if (new_temp_list->size!=0 ){
		assert( old_temp_list->list_int!= NULL );
	}
	for(i=0;i<old_temp_list->size;i++){
		old_temp_list->list_int[i] = new_temp_list->list_int[i];
	}
}

void copy_int_list_in ( Temp_list_int * a, unsigned int* list , int size ) {
	if ( a->size != size) { 
		a->list_int = (unsigned int*) realloc ( a->list_int, size * sizeof(unsigned int));
		assert( a->list_int!= NULL );
		a->size = size;
	}
	for(int i =0; i < size ; i++){
		a->list_int[i] = list[i];
	}

}
unsigned int* copy_unsigned_int_list (unsigned int* list, int size){
	unsigned int* new_list;
	int i;
	
	new_list = (unsigned int*)malloc( size * sizeof(unsigned int));
	assert( new_list != NULL);
	
	for(i=0;i<size;i++){
		new_list[i] = list[i];
	} 
	
	return new_list;
}


/*char list*/
Temp_list_char create_temp_list_char (char * list, int size) {
	Temp_list_char tl;
	tl.size = size;
	tl.list = list;
 return tl;
}
void free_temp_list ( Temp_list_char* tl ) {
	tl->size = 0;
	free(tl->list);
}
void add_char_temp_list ( Temp_list_char * temp_list, char c){
	temp_list->size++; 
	temp_list->list =(char*)realloc(temp_list->list, temp_list->size * sizeof(char));
	assert( temp_list->list!= NULL );
	temp_list->list[temp_list->size-1] = c ;
}
void overwrite_char (Temp_list_char* old_temp_list, Temp_list_char * new_temp_list){
	int i;
	if (old_temp_list->size != new_temp_list->size){
        old_temp_list->size = new_temp_list->size;
	    old_temp_list->list = (char*)realloc(old_temp_list->list, new_temp_list->size * sizeof(char));
    }
	if (new_temp_list->size!=0 ){
		assert( old_temp_list->list!= NULL );
	}
	for(i=0;i<old_temp_list->size;i++){
		old_temp_list->list[i] = new_temp_list->list[i];
	}
} 

void print_Temp_list_char (Temp_list_char tl){
	int i;
    /*printf("\n");
    printf("\n");*/
	printf("Size list = %d ",tl.size );
	for(i=0;i<tl.size;i++){
		printf("%d, ",tl.list[i] );
	}
    printf("\n");
}





/*Temporary lists gestion*/

typedef struct Temp_list_int {
  int size;
  unsigned int* list_int;
} Temp_list_int ; 

typedef struct Temp_list_char {
    char * list;
    int size;
}Temp_list_char;

Temp_list_int create_temp_list_int (unsigned int * list, int size);
void add_int_temp_list ( Temp_list_int * temp_list, unsigned int sho);
void free_temp_list_int ( Temp_list_int* tl );
void print_Temp_list_int (Temp_list_int tl);
void add_unsigned_int_temp_list ( Temp_list_int * temp_list, unsigned int sho);
void overwrite_int (Temp_list_int * old_temp_list, Temp_list_int * new_temp_list);
void copy_int_list_in ( Temp_list_int * a, unsigned int* list , int size );
unsigned int* copy_unsigned_int_list (unsigned int* list, int size);

Temp_list_char create_temp_list_char (char * list, int size);
void free_temp_list ( Temp_list_char* tl );
void add_char_temp_list ( Temp_list_char * temp_list, char c);
void overwrite_char (Temp_list_char* old_temp_list, Temp_list_char * new_temp_list);
void print_Temp_list_char (Temp_list_char tl);


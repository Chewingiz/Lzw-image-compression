/* il s agit de prendre une image et de la modifier */

#include "ima.h"
#include <limits.h>

void gris_uniform(Image *i) {
    int j, size;
    GLubyte *im, val;
    val = 128;
    size = 3 * i->sizeY * i->sizeX;
    im = i->data;
    for (j = 0; j < size; j++) {
        *im++ = val;
    }
}
void gris_uniforme(Image *i) {
    int j, size, v;
    GLubyte *imr, *img, *imb, val;

    size = i->sizeY * i->sizeX;
    imr = i->data;
    img = i->data + 1;
    imb = i->data + 2;
    for (j = 0; j < size; j++) {
        v = *imr + (int)*imr;
        v += 3 * (int)*img;
        v += *imb;
        v /= 6;
        val = (GLubyte)v;
        *imr = val;
        *img = val;
        *imb = val;

        imr += 3;
        img += 3;
        imb += 3;
    }
}

void rouge_uniform(Image *i) {
    int j, size;
    GLubyte *im, val;
    val = 128;
    size = 3 * i->sizeY * i->sizeX;
    im = i->data;
    for (j = 0; j < size; j++) {
        *im++ = val;
    }
}


/* for simplification  https://www.youtube.com/watch?v=X51XaKfJiJc&t=1052s */
int LZW_Compresser(char* to_compress, char * file_name){
	FILE *file = fopen(to_compress, "rb");
	if (!file){exit(1);}
	
	char c;
    unsigned int temp_for_writing;
	Dictionary_tree dico_tree = NULL ;
    add_base_dico_tree(&dico_tree);

    unsigned int place = (int) 255;
    Node_element * last_position_research = dico_tree;
    int rl = 0, ismtl = 0;
    int * r_or_l = &rl;
    int * is_smaller_then_last = &ismtl;
    int fond = 0; // = 1 if the last one was found,  0 otherwise 
    unsigned int research_result;
	
	Temp_list_char w = create_temp_list_char(NULL, 0);
	Temp_list_char p = create_temp_list_char(NULL, 0);
	Temp_list_char only_c = create_temp_list_char(NULL, 1);
    
    Temp_list_int reponse = create_temp_list_int(NULL, 0);
    
    int last_in_dico_tree = 1;// if the last char is just a part of what is in the Dictionary_tree it is not added ! 
	// 1 if it is in the Dictionary_tree 0 otherwise
    c=fgetc(file);
   //printf("place : %u, \n", place);
	//FILE *fptr = fopen("./compressed","w");
	FILE *fptr = fopen(file_name,"w"); 
	if (!fptr){exit(1);}
	
    while ( c != EOF){
        
    	overwrite_char  (&p, &w);
    	add_char_temp_list ( &p, c);

        if (fond == 0){
            research_result = research_in_dico_tree ( p.list, p.size, dico_tree, &last_position_research, r_or_l, is_smaller_then_last);
        }else{
            //research_result = rec_research_in_dico_tree ( &p.list[p.size-1], 1, last_position_research, &last_position_research, r_or_l, is_smaller_then_last);
            research_result = research_in_dico_tree ( p.list, p.size, dico_tree, &last_position_research, r_or_l, is_smaller_then_last);

        }
    	if (research_result != Not_Found){
            fond = 1;
    		overwrite_char (&w, &p);
			last_in_dico_tree = 1;
    	}else{
            fond = 0;
            place++;
            if ( place == Not_Found){
                printf("Overfow ! you might whant to consider using an other type ");
                exit(1);
            }
            
            add_char_dico_tree(&dico_tree, p.list[p.size-1], last_position_research , r_or_l , place, is_smaller_then_last);

        temp_for_writing = research_in_dico_tree ( w.list, w.size, dico_tree, &last_position_research, r_or_l, is_smaller_then_last);
            
        if ( (long unsigned int)1 != fwrite( &temp_for_writing , sizeof(unsigned int), 1 , fptr ) ) {
            fprintf( stderr, "Cannot write block in file\n" );
        }
    		char copy_c = c;
    		only_c.list= &copy_c ;
    		overwrite_char  (&w, &only_c);
			last_in_dico_tree = 0;
    	}
    	c=fgetc(file);
        printf("%c = %d, ", c, c);
    }
     if ((last_in_dico_tree == 1) && (dico_tree != NULL)){
        temp_for_writing = research_in_dico_tree ( w.list, w.size, dico_tree, &last_position_research, r_or_l, is_smaller_then_last);
        if ( (long unsigned int)1 != fwrite( &temp_for_writing , sizeof(unsigned int), 1 , fptr ) ) {
            fprintf( stderr, "Cannot write block in file\n" );
        }
	 }

	printf("\n Size Dictionary_tree = %u ", place);
    
	fclose(fptr);
	fclose(file);
    //printf("\n Size Dictionary_tree = %u ", place);
    free_temp_list_int ( &reponse );
    free_dico_tree(dico_tree);
	free_temp_list(&w);
	free_temp_list(&p);

    return 0;
}


int LZW_Decompresser(char* to_uncompress, char * file_name){ //, FILE * dictionary
	 FILE *file = fopen(to_uncompress,"r");
	 if (!file){exit(1);}

	unsigned int v;
	dictionary dico;
	put_all_base_alphabet(256, &dico);
	int research_result;
	unsigned int * s;
	int i;
	int count = fread(&v, sizeof(unsigned int) , 1, file);

	Temp_list_int w = create_temp_list_int(copy_unsigned_int_list (&v, 1), 1);
	Temp_list_int v_list = create_temp_list_int(copy_unsigned_int_list (&v, 1), 1);
	Temp_list_int entre = create_temp_list_int(copy_unsigned_int_list (&v, 1), 1);
	
	Temp_list_int reponse =  create_temp_list_int(copy_unsigned_int_list (&v, 1), 1);
	
	copy_int_list_in( &entre, dico.list_elements[(int)v].list_unsigned_int , dico.list_elements[(int)v].size_element);

	count = fread(&v, sizeof(unsigned int), 1, file);
    while ( count != 0){
     
    	v_list.list_int[0] = v; 
    	research_result = research_element_decomp( (int) v , dico);
    	
    	if (research_result!=-1){
    			copy_int_list_in( &entre, dico.list_elements[research_result].list_unsigned_int , dico.list_elements[research_result].size_element);

    	}else {

    			copy_int_list_in ( &entre, w.list_int, w.size );
    			add_int_temp_list ( &entre , w.list_int[0]);

    	}
    		for(i=0 ; i < entre.size ; i++){
    			add_int_temp_list ( &reponse, entre.list_int[i]);
    			
    		}
    			
    		add_int_temp_list ( &w , entre.list_int[0] );
    		
    		s = copy_unsigned_int_list (w.list_int, w.size);
    		put_new_element( s, w.size , &dico);
    		

    		overwrite_int(&w, &entre);// w <- entree 
    		
    	
    	count = fread(&v, sizeof(unsigned int) , 1, file);
   	}
   	//print_dico(dico);
	 printf(" size dictionary = %d\n",dico.size );
    free_dico(&dico);
    free_temp_list_int(&w);
    free_temp_list_int(&v_list);
    free_temp_list_int(&entre);
    
    FILE *fptr = fopen(file_name,"w"); 
    if (!fptr){exit(1);}

	char * rps = (char *) malloc(sizeof(char) * reponse.size);
	assert( rps != NULL);
	for ( i =0 ; i< reponse.size;i++){
		rps[i] = (char)reponse.list_int[i];
		//printf("%c, ",rps[i]);
	}
	 printf("\n" );
	
	if ( (long unsigned int)reponse.size != fwrite( rps, sizeof(char), reponse.size , fptr ) ) {
		fprintf( stderr, "Cannot write block in file\n" );
	}
	fclose(fptr);
	fclose(file);
 	
	free_temp_list_int(&reponse);
    free(rps);

    return 0;
}

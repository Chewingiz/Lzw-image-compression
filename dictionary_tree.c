#include "dictionary_tree.h"

Node_element * create_Node_element (char c ,Node_element * parent, Node_element * right_child, Node_element * left_child , int index){
    Node_element* elem = malloc(sizeof (Node_element));
    assert(elem != NULL);
    elem->parent = parent;///
    elem->character = c; // character of the node 
    elem->right_child = right_child; // next character in the string
    elem->left_child = left_child; // replacement of the curent character
    elem->index = index; // index in Dictionary_tree
    return elem;
}

unsigned int rec_research_in_dico_tree ( char * list_c, int size, Dictionary_tree dico_tree, Node_element ** last_position_research , int * r_or_l, int * is_smaller_then_last) {
    //int r_l_result, is_smaller_result ;
    if (dico_tree == NULL){
        // printf("dico_tree null  ");
         //last_position_research = dico_tree;
        return Not_Found;
    }
    if (list_c == NULL){
       // printf("list null  ");
        return Not_Found;
    }
    //char c = list_c[0];
    if (list_c[0] == dico_tree->character){
        if ( size ==1){
            // printf("trouve! ");
            *last_position_research = dico_tree;
            *r_or_l = 0;// put next on the right side 
            return dico_tree -> index;
            // if found we only need to search for the new Node_element
            // !!!!with this fuction!!! 
            //after adding it to list we need do 
            // rec_research_in_dico_tree ( list_c[size-1], 1, last_position_research, NULL , NULL);
        }
        if (dico_tree -> right_child != NULL){
           //  printf("droite ");
            return rec_research_in_dico_tree( &list_c[1], size-1, dico_tree -> right_child, last_position_research, r_or_l, is_smaller_then_last );
        }else {
            // is not in it needs to be added
            *r_or_l = 0;// put new one on the right side 
            *last_position_research = dico_tree;
             //printf("pas trouve 1  ");
            return Not_Found;
        }
    }else{
        /*if (dico_tree->character > c){  // bug ordre alphabétique
            // printf("pas trouve 2  ");
            *is_smaller_then_last = 1;
            *r_or_l =  1;
            *last_position_research = dico_tree;
            return Not_Found;
        }*/
        if (dico_tree -> left_child != NULL){ 
               // printf("gauche ");
                return rec_research_in_dico_tree( list_c, size, dico_tree -> left_child, last_position_research, r_or_l, is_smaller_then_last );
        }else {
            // is not in it needs to be added
            //add missing letter dico_tree in research for the next one will be root
            *r_or_l =  1;// put new one on the left side 
            // if left we need to see the order if list_[0] < dico_tree->character 
            // the new one become the left son af the parent and dico_tree becomes left child of new one
            //is_smaller_result = 0;
            // printf("pas trouve 3  ");
            *is_smaller_then_last = 0;
            *last_position_research = dico_tree;
            return Not_Found;
        }
    }    
}
/*Research from root*/
unsigned int research_in_dico_tree ( char * list_c, int size, Dictionary_tree dico_tree, Node_element ** last_position_research , int * r_or_l, int * is_smaller_then_last){
     // so the first one is in it becose all the base is already in Dictionary_tree no need to add it
     return rec_research_in_dico_tree( list_c, size, dico_tree , last_position_research, r_or_l ,is_smaller_then_last);
   /* if ( size ==1){
        *last_position_research = dico_tree;
        return (int)list_c[0];
    }else{
        *last_position_research = dico_tree;

        if (dico_tree != NULL){
            if (dico_tree -> right_child !=NULL){
                return rec_research_in_dico_tree( &list_c[1], size-1, dico_tree , last_position_research, r_or_l ,is_smaller_then_last);
            }else{
                *r_or_l = 0;// put new one on the right side 
                return -1;
            }
        }else{
            return -1;
        }  
    }*/
}

void add_char_dico_tree(Dictionary_tree* dico_tree, char c, Node_element * last_position_research , int * r_or_l , unsigned int place, int * is_smaller_then_last){

    Node_element * new_node = create_Node_element (c ,NULL, NULL, NULL, place);
    if ((dico_tree == NULL) || (last_position_research == NULL) ){
        *dico_tree = new_node;
        return;
    }
    if ( *r_or_l == 1){      // add to the left
        if ( *is_smaller_then_last == 1  ){
            new_node->left_child = last_position_research;
            if (last_position_research->parent != NULL){ 
                last_position_research->parent->right_child = new_node; 
                new_node->parent = last_position_research->parent;
            }else{
                *dico_tree = new_node;
            }
            last_position_research->parent = new_node;
        }else{
            last_position_research->left_child = new_node;
            new_node->parent = last_position_research;
        }

    }else{                  //add to the right
    	new_node->parent = last_position_research;
    	new_node->left_child = last_position_research->right_child;// to avoid memorry leaks 
        last_position_research->right_child = new_node;
        
    }
}


void add_base_dico_tree(Dictionary_tree* dico_tree){
    int i ;
    Node_element * new_node = create_Node_element ((unsigned int)0 ,NULL, NULL, NULL, 0);
    *dico_tree = new_node;
    Node_element * last_position = *dico_tree;


    for (i = 1 ; i<256 ; i++){
        new_node = create_Node_element (( unsigned int)i ,NULL, NULL, NULL, i);
        last_position->left_child = new_node;
        last_position = new_node;
    }
}

void free_dico_tree(Dictionary_tree dico_tree){
    if(dico_tree != NULL){
    	if (dico_tree->right_child != NULL){
    		free_dico_tree(dico_tree->right_child);
    		//free(dico_tree->right_child);
    	}
    	
    	if (dico_tree->left_child!= NULL ){
    		 free_dico_tree(dico_tree->left_child);
    		// free(dico_tree->left_child);
    	}

        free(dico_tree);
    }
}


void print_dico_tree(Dictionary_tree dico_tree){
    if (dico_tree != NULL){
        //printf("%c, ", dico_tree->character);
      //  fprintf(stdout, "%p: {character: '%c', left_child: %p parent: %p, right_child: %p}\n", dico_tree, dico_tree->character, dico_tree->left_child, dico_tree->parent, dico_tree->right_child);
        print_dico_tree(dico_tree->left_child );
        print_dico_tree(dico_tree->right_child );
    }else{
    	//printf("NULL ");
    }
}
void print_simple_dico_tree(Dictionary_tree dico_tree){
    if (dico_tree != NULL){
        printf("%c, ", dico_tree->character);
        printf("( ");
        //fprintf(stdout, "%p: {character: '%c', left_child: %p parent: %p, right_child: %p}\n", dico_tree, dico_tree->character, dico_tree->left_child, dico_tree->parent, dico_tree->right_child);
        print_simple_dico_tree(dico_tree->left_child );
        print_simple_dico_tree(dico_tree->right_child );
        printf(")    ");
        return;
    }
    printf("NULL ");
    

}

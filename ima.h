#include <GL/gl.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "temporary_lists_gestion.h"
#include "dictionary_tree.h"
#include "dictionary_table.h"

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;
typedef unsigned short utab[3][3][3];

int Image_white(Image *img);
int ImageLoad_PPM(char *filename, Image *image);
void imagesave_PPM(char *filename, Image *image);
void upsidedown(Image *);
void gris_uniforme(Image *);
void gris(Image *);
void sobel(Image *);
void rouge_uniform(Image *i);

int LZW_Compresser(char* to_compress, char * file_name);
int LZW_Decompresser(char* to_uncompress, char * file_name);

/* Transforme l'image en vert (vert en allemand = grune) */
void grune(Image *);

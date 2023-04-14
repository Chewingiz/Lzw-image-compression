#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "ima.h"

Image *image;
char * name;
#define ESCAPE 27

/*https://stackoverflow.com/questions/20292866/get-a-files-extension-with-c*/
char *getFileNameExtension(char *filename){
    char *ext = strrchr(filename, '.');
    return ext;
}

void keyboard(unsigned char key, int x, int y) {
    (void)x, (void)y;
    switch (key) {
    case ESCAPE:
        exit(0);
        break;
    default:
        fprintf(stderr, "Unused key\n");
    }
}

void mouse(int button, int state, int x, int y) {
    (void)state, (void)x, (void)y;
    switch (button) {
    case GLUT_LEFT_BUTTON:
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    }
    glutPostRedisplay();
}

int init(char *s) {

    image = (Image *)realloc(image,sizeof(Image));
        if (image == NULL) {
            fprintf(stderr, "Out of memory\n");
            return (-1);
        }

    if (strcmp(getFileNameExtension(s), ".ppm") == 0){
        
        if (ImageLoad_PPM(s, image) == -1)
            return (-1);
        printf("taille : %dx%d\n", (int)image->sizeX, (int)image->sizeY);

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glShadeModel(GL_FLAT);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glutReshapeWindow(image->sizeX, image->sizeY);
    }else{
        printf("Impossible d'afficher une image compréssée.\n");
        Image_white(image);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glShadeModel(GL_FLAT);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glutReshapeWindow(1000, 780);
    }

    return (0);
}
int reInit(void) {
    /*
    if (ImageLoad_PPM(s, image)==-1)
          return(-1);
    */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glutReshapeWindow(image->sizeX, image->sizeY);

    return (0);
}

void display(void) {

    // GLint w, h;

    glClear(GL_COLOR_BUFFER_BIT);

    // w = glutGet(GLUT_WINDOW_WIDTH);
    // h = glutGet(GLUT_WINDOW_HEIGHT);
    glDrawPixels(image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
                 image->data);

    glFlush();
}

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void menuFunc(int item) {
    char s[256];
    clock_t td, ta;
    switch (item) {
    case 0:
        free(image);
        exit(0);
        break;
    case 1:
        printf("Gris pondéré\n");
        gris(image);
        display();
        break;
    case 2:
        printf("Sobel\n");
        sobel(image);
        display();
        break;
    case 3:
        break;
    case 4:
        printf("Revenir image départ\n");
        gris_uniforme(image);
        display();
        break;
    case 5:
        printf("Entrer le nom pour l'image dans cette taille\n");
        scanf("%s", &s[0]);
        imagesave_PPM(s, image);
        break;
    case 6:
        printf("Taille de l image : %d %d\n", (int)image->sizeX,
               (int)image->sizeY);
        break;
    case 7:
        printf("Grune\n");
        grune(image);
        display();
        break;
    case 8: //compresser
        printf("Entrer le nom pour l'image compressée\n");
        scanf("%s", &s[0]);
        strcat(s, ".comp");
        td = clock();
        LZW_Compresser(name, s);
        ta = clock();
        printf ("time : %ld clock ticks \n",(int) ta-td);
        printf ("				%ld s\n",(int) (ta-td)/CLOCKS_PER_SEC);
        printf ("				%d min\n",(int) ((ta-td)/CLOCKS_PER_SEC)/60);
        display();
        break;
    case 9: //décompresser
        printf("Entrer le nom pour l'image décompressée\n");
        scanf("%s", &s[0]);
        strcat(s, ".ppm");
        td = clock();
        LZW_Decompresser(name, s);
        ta = clock();
        printf ("time : %ld clock ticks \n",(int) ta-td);
        printf ("				%ld s\n",(int) (ta-td)/CLOCKS_PER_SEC);
        printf ("				%d min\n",(int) ((ta-td)/CLOCKS_PER_SEC)/60);
        init(s);
        display();
        break;
    default:
        break;
    }
}

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Usage : palette nom_de_fichier\n");
        exit(0);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("VPUP8");

    init(argv[1]);
    name = argv[1];

    glutCreateMenu(menuFunc);
    glutAddMenuEntry("Quit", 0);
   /* glutAddMenuEntry("gris", 1);
    glutAddMenuEntry("Sobel", 2);
    glutAddMenuEntry("GRIS", 3);*/
    glutAddMenuEntry("Compresser", 8);
    glutAddMenuEntry("Decompresser", 9);
  /*  glutAddMenuEntry("grey", 4);
    glutAddMenuEntry("grune", 7);*/
    glutAddMenuEntry("Sauver", 5);
    glutAddMenuEntry("Informations", 6);
    glutAttachMenu(GLUT_LEFT_BUTTON);

    glutDisplayFunc(display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);

    glutMainLoop();

    return 1;
}

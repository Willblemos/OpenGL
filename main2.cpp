#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "imageloader.h"

GLuint _texturafundo;
GLUquadric* a;
GLfloat RodaX, RodaY = 0.0;


void reshape(int x, int y) {
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,121.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); 
	glBindTexture(GL_TEXTURE_2D, textureId); //qual textura editar
	//Mapeamento da imagem para a textura
	glTexImage2D(GL_TEXTURE_2D,                
				 0,                            
				 GL_RGB,                       
				 image->width, image->height,  //Width e height
				 0,                            //borda da imagem
				 GL_RGB, //GL_RGB, porque os pixels são armazenados no formato RGB
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, porque os pixels são armazenados como unsigned numbers
				                   
				 image->pixels);               //O pixel como um dado
	return textureId; //Rotorna o id da textura 
}


void init(void) {

    double r = 0.86415094; 
    double g = 0.86328125; 
    double b = 0.8515625;

    a = gluNewQuadric();
    gluQuadricNormals(a, GLU_SMOOTH);

    Image* image = loadBMP("texturafundo.bmp");
	_texturafundo = loadTexture(image);
	delete image;

    GLfloat luzAmbiente[4]={r,g,b,1.0};
	GLfloat luzDifusa[4]={r,g,b,1.0};	   // "cor"
	GLfloat luzEspecular[4]={r, g, b, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 0.0, 0.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 1;
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void RotateUP(void) {
    RodaX -= 2;
    if (RodaX < -360.0) {
        RodaX += 360.0;
    }
    glutPostRedisplay();
}
void RotateDOWN(void) {
    RodaX += 2;
    if (RodaX > 360.0) {
        RodaX -= 360.0;
    }
    glutPostRedisplay();
}
void RotateRIGHT(void) {
   RodaY += 2;
    if (RodaY > 360.0) {
        RodaY -= 360.0;
    }
    glutPostRedisplay();
}
void RotateLEFT(void) {
    RodaY -= 2;
    if (RodaY < -360.0) {
        RodaY += 360.0;
    }
    glutPostRedisplay();
}
void teclado(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            RotateUP();
            break;
        case GLUT_KEY_DOWN:
            RotateDOWN();
            break;
        case GLUT_KEY_RIGHT:
            RotateRIGHT();
            break;
        case GLUT_KEY_LEFT:
            RotateLEFT();
            break;
        case GLUT_KEY_END:
            RodaX = 0;
            RodaY = 0;
    }
}

void circulo_solido(GLfloat x, GLfloat y, GLfloat z, GLfloat radius) {
	int i;
	int triangleAmount = 50; //# of triangles used to draw circle
	
	GLfloat twicePi = 2.0f * 3.1415926;
	
	glBegin(GL_TRIANGLE_FAN);
	for(i = 0; i <= triangleAmount; i++) { 
		glVertex3f(
	        x + (radius * cos(i *  twicePi / triangleAmount)), 
		    y + (radius * sin(i * twicePi / triangleAmount)),
            z
		);
	}
	glEnd();
}
void circuferencia(GLfloat x, GLfloat y, GLfloat z, GLfloat radius){
	int i;
	int lineAmount = 50; //# of triangles used to draw circle
	
	GLfloat twicePi = 2.0f * 3.1415926;
	
	glBegin(GL_LINE_LOOP);
	for(i = 0; i <= lineAmount;i++) { 
		glVertex3f(
			x + (radius * cos(i *  twicePi / lineAmount)), 
			y + (radius* sin(i * twicePi / lineAmount)),
            z
		);
	}
	glEnd();
}

void display() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1,1,1,1);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity();

    // // Paralelepípedo amarelo
    glTranslatef(0.0,0.5,-15.0);
    glPushMatrix();
    glRotatef(RodaX,1,0,0);
    glRotatef(RodaY,0,1,0);
    glColor3f(1.0,0.7,0.1);
    glScalef(2.4,5.1,4.8);
    glutSolidCube(1);
    glPopMatrix();
    //Cubo branco
    glPushMatrix();
    glRotatef(RodaX,1,0,0);
    glRotatef(RodaY,0,1,0);
    glColor3f(1.0,1.0,1.0);
    glScalef(3.12,4.7,4.2);
    glTranslatef(0.0,-0.1,0.0);
    glutSolidCube(1);
    glPopMatrix();
    //Cubo vermelho
    glPushMatrix();
    glRotatef(RodaX,1,0,0);
    glRotatef(RodaY,0,1,0);
    glColor3f(0.8,0.0,0.0);
    glScalef(4.8,5.4,3.6);
    glTranslatef(0.0,-0.156,0.0);
    glutSolidCube(1);
    glPopMatrix();
    //Cubo branco de fora
    glPushMatrix();
    glRotatef(RodaX,1,0,0);
    glRotatef(RodaY,0,1,0);
    glColor3f(1.0,1.0,1.0);
    glScalef(5.64,5.16,3.0);
    glTranslatef(0.0,-0.28,0.0);
    glutSolidCube(1);
    glPopMatrix();
    //Cilindro
    glPushMatrix();
    glRotatef(RodaX,1,0,0);
    glRotatef(RodaY,0,1,0);
    glColor3f(0.9,0.45,0.0);
    glTranslatef(0.0,-1.2,-0.8);
    gluCylinder(a,3.7,3.7,1.92,50,10);
    glTranslatef(0.0,1.5,0.8);
    circulo_solido(0,-1.5,1.13,3.72);
    circulo_solido(0,-1.49,-0.8,3.71);
    glPopMatrix();

    // Fundo 
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _texturafundo);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-10);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,10.0,0.1);  glVertex3f(-20,20,0);
            glTexCoord3f(10.0,10.0,0.1);  glVertex3f(20,20,0);
            glTexCoord3f(10.0,0.0,0.1);  glVertex3f(20,-20,0);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-20,-20,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1080,1080);
    glutCreateWindow("Furg");
    glEnable(GL_DEPTH_TEST);
    
    glutSpecialFunc(teclado);
    glutDisplayFunc(display);
    init();
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
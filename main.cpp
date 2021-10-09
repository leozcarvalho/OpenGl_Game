#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include "Restricoes.cpp"

float angulo = 0;

float scale = 0.1f;
float quantidade = 0.1f;
float paredeDireita = 1.0f;
float obstaculo = 1.0f;
float velocidade = -0.03f;
float paredeEsquerda = -1.0f;
float chao = -1.0f;
float posX = -0.9;
float posY = -0.95f;
float gap_escada = 0.02f;
float escada = -0.95f;
//DEBUG printf("%f", variavel);

void desenhaBoneco(){
	glBegin(GL_QUADS);
		glVertex2f( posX, posY);
		glVertex2f( posX + 0.05f, posY);
		glVertex2f( posX + 0.05f, posY + 0.15f);
		glVertex2f( posX, posY + 0.15f);
	glEnd();
}
void desenhaObstasculos()
{	
	glTranslatef(obstaculo,-0.50f, 0.0f);
    glutSolidSphere(0.05f,20.0f,2.0f);
	
}
void desenhaFase(){
	for(int i = 0; i <= 4; i++) {
		float gap = 0.40f;

		glBegin(GL_QUADS);
			glVertex2f( paredeEsquerda, (chao + (gap * i)));
			glVertex2f( paredeDireita , (chao + (gap * i)));
			glVertex2f( paredeDireita, (chao + (gap * i)) + 0.05f);
			glVertex2f( paredeEsquerda, (chao + (gap * i)) + 0.05f);
		glEnd();
	}
	for(int j = -1; j <= 1; j++) {
		if(j==0) { j++; }
		for(int i = 1; i <= 80; i+=2) {
			glBegin(GL_QUADS);
				glVertex2f( j * 0.80f, escada + gap_escada * i);
				glVertex2f( j * 0.70f, escada + gap_escada * i);
				glVertex2f( j * 0.70f, escada + (gap_escada * (i + 1)));
				glVertex2f( j * 0.80f, escada + (gap_escada * (i + 1)));
			glEnd();
			glBegin(GL_QUADS);
				glVertex2f( j * 0.50f, escada + gap_escada * i);
				glVertex2f( j * 0.40f, escada + gap_escada * i);
				glVertex2f( j * 0.40f, escada + (gap_escada * (i + 1)));
				glVertex2f( j * 0.50f, escada + (gap_escada * (i + 1)));
			glEnd();
		}
	}
}

void desenho(){

	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glColor3f(0.0f,0.0f,1.0f);
	desenhaFase();

	glColor3f(1.0f,1.0f,0.0f);
	desenhaObstasculos();

	glLoadIdentity();

	glColor3f(1.0f,0.0f,0.0f);
	desenhaBoneco();
	
	// Apresentar a cena na tela
	glutSwapBuffers();
}

void timer(int t){
	if(obstaculo <= paredeEsquerda){
		
		velocidade = velocidade * -1;
	}
	if(obstaculo >= paredeDireita) {
		velocidade = -0.03f;
	}
	obstaculo += velocidade;
	glutPostRedisplay();		
	glutTimerFunc(60, timer, 0);
}

void teclado(unsigned char tecla, int xt, int yt){

	if(tecla == 'd') {
		if(direita(&posX, paredeDireita) && podeAndar(&posY)) {
			posX += 0.05f;
		}
		//printf("%f", posX);
	}
	if(tecla == 'a') {
		if(esquerda(&posX, paredeEsquerda) && podeAndar(&posY)) {
			posX -= 0.05f;
		}
	}
	if(tecla == 'w') {
		if(subir(&posX, &posY)) {
			posY += 0.05f;
		}
	}
	if(tecla == 's') {
		if(descer(&posX, &posY)) {
			posY -= 0.05f;
		}
	}
	if(tecla == 'v') {
		glutTimerFunc(0, timer, 0);
	}
	glutPostRedisplay();
}

int main(int argc, char * argv[]){

	glutInit(&argc, argv);

	// Criar uma janela
	glutInitWindowSize(800, 600);
	glutCreateWindow("Donkey Kong OPENGL");

	// definir a função de callback de display
	glutDisplayFunc(desenho);
	glutKeyboardFunc(teclado);
	// definir a função de callback do timer
	glutTimerFunc(0, timer, 0);
	// Laço principal do OpenGL.
	glutMainLoop();

	return 0;
}



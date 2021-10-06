#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include "Restricoes.cpp"

float angulo = 0;

float scale = 0.1f;
float quantidade = 0.1f;
float paredeDireita = 1.0f;
float paredeEsquerda = -1.0f;
float chao = -0.95f;
float posX = -0.9;
float posY = chao;

void desenhaBoneco(){
	glBegin(GL_QUADS);
		glVertex2f( posX, posY);
		glVertex2f( posX + 0.05f, posY);
		glVertex2f( posX + 0.05f, posY + 0.15f);
		glVertex2f( posX, posY + 0.15f);
	glEnd();
}
void desenhaFase(){
	glBegin(GL_QUADS);
		glVertex2f( -1.0f, -1.0f);
		glVertex2f( 1.0f , -1.0f);
		glVertex2f( 1.0f, chao);
		glVertex2f( -1.0f, chao);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f( -1.0f, -0.5f);
		glVertex2f( 1.0f , -0.5f);
		glVertex2f( 1.0f, -0.55);
		glVertex2f( -1.0f, -0.55);
	glEnd();
}

void desenho(){
	// limpar a tela, apagando os dados do FrameBuffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Mudar a cor do fundo
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Desenhar uma primitiva

	glColor3f(0.0f,0.0f,1.0f);
	desenhaFase();

	glLoadIdentity();

	glColor3f(1.0f,0.0f,0.0f);
	desenhaBoneco();
	
	// Apresentar a cena na tela
	glutSwapBuffers();
}

void timer(int t){
	posY += 0.01f;
	if(posY <= -0.8f) {
		glutTimerFunc(10, timer, 0);
		glutPostRedisplay();
	}
	// Agendar a próxima executação após 60 ms.
}

void teclado(unsigned char tecla, int xt, int yt){

	if(tecla == 'd') {
		if(direita(&posX, paredeDireita)) {
			posX += 0.05f;
			glutPostRedisplay();
		}
		//printf("%f", posX);
	}
	if(tecla == 'a') {
		if(esquerda(&posX, paredeEsquerda)) {
			posX -= 0.05f;
			glutPostRedisplay();
		}
	}
	if(tecla == 'v') {
		glutTimerFunc(0, timer, 0);
		glutPostRedisplay();
	}
}

int main(int argc, char * argv[]){

	glutInit(&argc, argv);

	// Criar uma janela
	glutInitWindowSize(800, 600);
	glutCreateWindow("Primeiro exemplo em OpenGL");

	// definir a função de callback de display
	glutDisplayFunc(desenho);
	glutKeyboardFunc(teclado);
	// definir a função de callback do timer
	
	// Laço principal do OpenGL.
	glutMainLoop();

	return 0;
}



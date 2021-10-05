#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <stdio.h>

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
bool direita(float argX) {
	if ((argX < paredeDireita - 0.05f)) {
		return true;
	}
	return false;
}
bool esquerda(float argX) {
	if ((argX > paredeEsquerda)) {
		return true;
	}
	return false;
}
void teclado(unsigned char tecla, int xt, int yt){

	if(tecla == 'd') {
		if(direita(posX)) {
			posX += 0.05f;
		}
		//printf("%f", posX);
	}
	if(tecla == 'a') {
		if(esquerda(posX)) {
			posX -= 0.05f;
		}
	}
}
void timer(int t){
	// redesenhar (chama a função de display de novo)
	glutPostRedisplay();
	//posX += 0.01f;
	// Agendar a próxima executação após 60 ms.
	glutTimerFunc(60, timer, 0);
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
	glutTimerFunc(0, timer, 0);

	// Laço principal do OpenGL.
	glutMainLoop();

	return 0;
}



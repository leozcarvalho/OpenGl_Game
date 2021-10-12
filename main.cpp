#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include "Restricoes.cpp"

float angulo = 0;

float scale = 0.1f;
float quantidade = 0.1f;
float paredeDireita = 1.0f;
float obstaculoX = 1.0f;
float obstaculoXD = -1.0f;
float velocidade = -0.03f;
float paredeEsquerda = -1.0f;
float chao = -1.0f;
float posX = -0.9;
float larguraBoneco = 0.05f;
float posY = -0.95f;
float alturaBoneco = 0.15f;
float gap_escada = 0.02f;
float escada = -0.95f;
float raio = 0.05f;
float g = 0.09f;

//DEBUG printf("%f", variavel);

void desenhaBoneco(){
	glBegin(GL_QUADS);
		glVertex2f( posX, posY );
		glVertex2f( posX + larguraBoneco, posY );
		glVertex2f( posX + larguraBoneco, posY + alturaBoneco );
		glVertex2f( posX, posY + alturaBoneco );
	glEnd();
}
void desenhaObstasculos() {	
	glTranslatef(obstaculoX,-0.50f, 0.0f);
    glutSolidSphere(raio,20.0f,2.0f);
	glLoadIdentity();
	glTranslatef(-obstaculoX,-0.10f, 0.0f);
    glutSolidSphere(raio,20.0f,2.0f);
	glLoadIdentity();
	glTranslatef(obstaculoX,0.30f, 0.0f);
    glutSolidSphere(raio,20.0f,2.0f);
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
	
	glutSwapBuffers();
}

void timer(int t){
	//printf("%f", posY);
	//printf("%d", colidiu(posX, posY, obstaculoX, -0.50f, raio));
	//if(!colidiu(posX, posY, obstaculoX, -0.50f, raio)) {
		if(obstaculoX <= paredeEsquerda){
			
			velocidade = velocidade * -1;
		}
		if(obstaculoX >= paredeDireita) {
			velocidade = -0.05f;
		}
		obstaculoX += velocidade;
		glutPostRedisplay();		
		glutTimerFunc(60, timer, 0);
	//}
}
void pulo(int t){
	if(posY < -0.80f) {
		posY+= (0.05f * g);
		glutPostRedisplay();
		glutTimerFunc(10, pulo, 0);
	}
	g = g*g;
}

void teclado(unsigned char tecla, int xt, int yt){
	if(tecla == 'd') {
		if(direita(&posX, paredeDireita) && podeAndar(posX + 0.05f, &posY)) {
			posX += 0.05f;
		}
		//printf("%f", posX);
	}
	if(tecla == 'a') {
		if(esquerda(&posX, paredeEsquerda) && podeAndar(posX - 0.05f, &posY)) {
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
		glutTimerFunc(0, pulo, 0);
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



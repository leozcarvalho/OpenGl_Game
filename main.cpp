#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include "Restricoes.cpp"
#include <unistd.h>
#include <string.h>

//Fase
float andares[] = { -1.0f, -0.60f, -0.20f, 0.20f, 0.60f };
float alturaDosAndares = 0.05f;
float paredeDireita = 1.0f;
float paredeEsquerda = -1.0f;

float obstaculos[] = { 1.0f, -1.0f, 1.0f };
float velocidade = -0.03f;
float larguraBoneco = 0.05f;
float larguraObstaculo = 0.05f;
float alturaBoneco = 0.15f;
float gap_escada = 0.02f;
float escada = -0.95f;
bool estaPulando = false;
bool bateu;
// Posicao inicial do Boneco
float posX = -0.95;
float posY = -0.95f;

//DEBUG printf("%f", variavel);

void resetaJogo() {
	posX = -0.95;
	posY = -0.95f;
	bateu = false;
	glutPostRedisplay();
}

void desenhaBoneco(){
	glBegin(GL_QUADS);
		glVertex2f( posX, posY );
		glVertex2f( posX + larguraBoneco, posY );
		glVertex2f( posX + larguraBoneco, posY + alturaBoneco );
		glVertex2f( posX, posY + alturaBoneco );
	glEnd();
}
void desenhaObstasculos() {
	for(int i = 0; i < 3; i++) {
		glBegin(GL_QUADS);
			glVertex2f( obstaculos[i], andares[i + 1] + alturaDosAndares );
			glVertex2f( obstaculos[i] + larguraObstaculo, andares[i + 1] + alturaDosAndares );
			glVertex2f( obstaculos[i] + larguraObstaculo, andares[i + 1] + alturaDosAndares + larguraObstaculo);
			glVertex2f( obstaculos[i], andares[i + 1] + alturaDosAndares + larguraObstaculo);
		glEnd();
	}
}
void desenhaFase(){
	for(int i = 0; i <= 4; i++) {
		float gap = 0.40f;
		glBegin(GL_QUADS);
			glVertex2f( paredeEsquerda, andares[i]);
			glVertex2f( paredeDireita , andares[i]);
			glVertex2f( paredeDireita, andares[i] + alturaDosAndares);
			glVertex2f( paredeEsquerda, andares[i] + alturaDosAndares);
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
	
	for(int i = 1; i <= 3; i++) {
		bateu = colidiu(posX, posY, obstaculos[i-1], andares[i] + alturaDosAndares + larguraObstaculo, larguraBoneco, alturaBoneco);
		if(bateu) {
			resetaJogo();
			break;
		}
	}
	
	if(!bateu) {
		if(eIgual(obstaculos[0], paredeEsquerda)){
			velocidade = velocidade * -1;
		}
		if(eIgual(obstaculos[0], paredeDireita)) {
			velocidade = -0.05f;
		}
		obstaculos[0] += velocidade;
		obstaculos[1] -= velocidade;
		obstaculos[2] += velocidade;
		glutPostRedisplay();		
		glutTimerFunc(60, timer, 0);
	}
}
void pulo(int t){
	if (estaPulando) {
		posY-= 0.1f;
		estaPulando = false;
	}
	else {
		posY+= 0.1f;
		glutTimerFunc(300, pulo, 0);
		estaPulando = true;
	}
	glutPostRedisplay();
}

void teclado(unsigned char tecla, int xt, int yt){
	if(tecla == 'd') {
		if(direita(&posX, paredeDireita) && podeAndar(posX + 0.05f, posY)) {
			posX += 0.05f;
		}
	}
	if(tecla == 'a') {
		if(esquerda(&posX, paredeEsquerda) && podeAndar(posX - 0.05f, posY)) {
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
		if(estaNoChao(posY)) {
			glutTimerFunc(0, pulo, 0);
		}
	}
	glutPostRedisplay();
}

int main(int argc, char * argv[]){

	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Donkey Kong OPENGL");
	glutDisplayFunc(desenho);
	glutKeyboardFunc(teclado);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();

	return 0;
}



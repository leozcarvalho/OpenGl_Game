#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include <string>
#include "Condicoes.cpp"
#include <unistd.h>
#include <string.h>

//Fase
float andares[] = { -1.0f, -0.60f, -0.20f, 0.20f, 0.60f };
float alturaDosAndares = 0.05f;
float paredeDireita = 1.0f;
float paredeEsquerda = -1.0f;
float velocidadeObstaculo = -0.05f;
float velocidadeBoneco = 0.05f;
float obstaculos[] = { 1.0f, -1.0f, 1.0f };
float larguraBoneco = 0.05f;
float larguraObstaculo = 0.05f;
float alturaBoneco = 0.15f;
float gap_escada = 0.02f;
float escada = -0.95f;

//Variaveis Booleanas
bool estaPulando = false;
bool bateu;
bool comecou = false;
bool objetivo = false;
bool acabou = false;

// Posicao inicial do Boneco
float posX = -0.95;
float posY = -0.95f;

//Posicao inicial do Objetivo largura e altura sao iguais
float posObjX = 0.0f;
float posObjY = 0.35f;
float larguraObj = 0.05f;

const char *letreiro = "Pegue o bloco verde";

//DEBUG printf("%f", variavel);

void resetaJogo() {
	posX = -0.95;
	posY = -0.95f;
	bateu = false;
	objetivo = false;
	letreiro = "Pegue o bloco verde";
	glutPostRedisplay();
}

void escreve(const char *texto){
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRasterPos2i(0, 0);
	const unsigned char* t = reinterpret_cast<const unsigned char *>(texto);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,t);
}

void desenhaBoneco(){
	glBegin(GL_QUADS);
		glVertex2f( posX, posY );
		glVertex2f( posX + larguraBoneco, posY );
		glVertex2f( posX + larguraBoneco, posY + alturaBoneco );
		glVertex2f( posX, posY + alturaBoneco );
	glEnd();
}
void desenhaObjetivo(){
	glBegin(GL_QUADS);
		glVertex2f( posObjX, posObjY );
		glVertex2f( larguraObj, posObjY );
		glVertex2f( larguraObj, posObjY + larguraObj );
		glVertex2f( posObjX, posObjY + larguraObj );
	glEnd();
}

void desenhaPorta(){
	glBegin(GL_QUADS);
		glVertex2f( 0.90f, -0.80f );
		glVertex2f( 0.95f, -0.80f );
		glVertex2f( 0.95f, -0.95f );
		glVertex2f( 0.90f, -0.95f );
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
	if(!comecou && !acabou) {
		glTranslatef(-0.5f,0.5f,0.0f);
		escreve("DONKEY KONG em OPENGL\n\nControles:\n(w) - Sobe as escadas\n(s) - Desce as escadas\
		\n(a) - Anda para a esquerda\n(d) - Anda para a direita\n(SPACE) - Pula\nObjetivo:\nO objetivo eh\
		capturar o bloco verde e\nescapar pela porta branca. Qualquer colisao\ncom os obstaculos\
		amnarelos, o jogo eh retomado do inicio.\n\nPRESSIONE ( ENTER ) PARA INICIAR O JOGO");
		glLoadIdentity();
	}

	if(comecou && !acabou) {

		glColor3f(0.0f,0.0f,1.0f);
		desenhaFase();

		glColor3f(1.0f,1.0f,0.0f);
		desenhaObstasculos();
		
		glTranslatef(0.4f,0.8f,0.0f);
		escreve(letreiro);
		glLoadIdentity();

		glColor3f(1.0f,1.0f,1.0f);
		desenhaPorta();
		
		glColor3f(1.0f,0.0f,0.0f);
		desenhaBoneco();
		
		if(!objetivo) {
			glColor3f(0.0f,1.0f,0.0f);
			desenhaObjetivo();
		}
	}
	if(acabou) {
		glTranslatef(-0.1f,0.2f,0.0f);
		escreve("PARABENS");
		glLoadIdentity();
		glTranslatef(-0.4,-0.1f,0.0f);
		escreve("\nPRESSIONE ( ENTER ) PARA JOGAR NOVAMENTE");
		glLoadIdentity();
		resetaJogo();
	}
	glutSwapBuffers();
}

void timer(int t){
	
	//Verifica se o boneco pegou o objetivo
	if(colidiu(posX, posY, posObjX, posObjY, larguraObj, alturaBoneco)) {
		objetivo = true;
		letreiro = "Escape pela porta branca";
	}
	
	//Verifica se o objetivo foi concluido e o boneco esta na mesma posicao da porta
	if(colidiu(posX, posY, 0.90f, -0.80f, 0.05f, alturaBoneco) && objetivo) {
		acabou = true;
	}

	//Verifica colisoes com os obstaculos
	for(int i = 1; i <= 3; i++) {
		bateu = colidiu(posX, posY, obstaculos[i-1], andares[i] + alturaDosAndares + larguraObstaculo, larguraBoneco, alturaBoneco);
		if(bateu) {
			resetaJogo();
			glutPostRedisplay();
			break;
		}
	}
	
	if(!bateu) {
		if(eIgual(obstaculos[0], paredeEsquerda)){
			velocidadeObstaculo = velocidadeObstaculo * -1;
		}
		if(eIgual(obstaculos[0], paredeDireita)) {
			velocidadeObstaculo = -0.05f;
		}
		obstaculos[0] += velocidadeObstaculo;
		obstaculos[1] -= velocidadeObstaculo;
		obstaculos[2] += velocidadeObstaculo;		
		glutTimerFunc(35, timer, 0);
	}
	glutPostRedisplay();
}
void pulo(int t){
	if (estaPulando) {
		posY-= 0.1f;
		estaPulando = false;
	}
	else {
		posY+= 0.1f;
		glutTimerFunc(250, pulo, 0);
		estaPulando = true;
	}
	glutPostRedisplay();
}

void teclado(unsigned char tecla, int xt, int yt){
	if(tecla == 'd')
		if(direita(&posX, paredeDireita) && podeAndar(posX + velocidadeBoneco, posY) || estaPulando)
			posX += velocidadeBoneco;

	if(tecla == 'a')
		if(esquerda(&posX, paredeEsquerda) && podeAndar(posX - velocidadeBoneco, posY) || estaPulando)
			posX -= velocidadeBoneco;

	if(tecla == 'w')
		if(subir(&posX, &posY))
			posY += velocidadeBoneco;

	if(tecla == 's')
		if(descer(&posX, &posY))
			posY -= velocidadeBoneco;

	if(tecla == ' ')
		if(estaNoChao(posY))
			glutTimerFunc(0, pulo, 0);

	if(tecla == 13) {
		comecou = true;
		acabou = false;
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



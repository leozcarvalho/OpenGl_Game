#define EPSILON 0.01f

bool eIgual(float a, float b) {
	float diff = a - b;
	if(diff < EPSILON && -diff < EPSILON) {
		return true;
	}
   	return false;
}

bool direita(float *argX, float parede) {
	if ((*argX <  parede - 0.05f)) {
		return true;
	}
	return false;
}
bool esquerda(float *argX, float parede) {
	if ((*argX > parede)) {
		return true;
	}
	return false;
}
bool estaNaEscada(float argX) {
	if((argX > 0.4f && argX < 0.5f) || (argX > 0.7f && argX < 0.8f) || ( argX > -0.5f && argX < -0.4f) || ( argX > -0.8f && argX < -0.7f)) {
		return true;
	}
	return false;
}
bool subir(float *argX, float *argY) {
	if(*argY < 0.65f) {
		if(estaNaEscada(*argX)) {
			return true;
		}
	}
	return false;
}
bool descer(float *argX, float *argY) {
	if(*argY > -0.95f) {
		if (estaNaEscada(*argX)) {
			return true;
		}
	}
	return false;
}
bool podeAndar(float argX, float *argY) {
	if((eIgual(*argY, -0.95f) || eIgual(*argY, 0.65f)) || eIgual(*argY, -0.55f) || eIgual(*argY, -0.15f) || eIgual(*argY, 0.25f) || (estaNaEscada(argX))) {
		return true;
	}
	return false;
}
bool colidiu(float posX, float posY, float obsX, float obsY, float largura, float alturaBoneco) {
	//posX < obsX + 0.075f && posX + largura > obsX && posY > obsY + 0.05f && posY + 0.15f > obsY
	printf("------------------------------------\n");
	printf("condicao 1 %d\n", posX < obsX + 0.075f);
	printf("condicao 2 %d\n", posX + largura > obsX);
	printf("condicao 3 %d\n", posY > obsY + 0.05f);
	printf("condicao 4 %d\n", posY + 0.15f > obsY);
	printf("------------------------------------");
	if (posX < obsX + 0.075f && posX + largura > obsX && posY > obsY + 0.05f && posY + 0.15f > obsY) {
		return true;
	}
	return false;
}
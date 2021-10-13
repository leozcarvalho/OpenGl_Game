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
bool colidiu(float posX, float posY, float obsX, float obsY, float raio) {
	if((eIgual(posY + 0.15f, obsY - raio)) && obsX) {
		return true;
	}
	if((eIgual(posX + raio + raio, obsX) || eIgual(posX - raio, obsX)) && eIgual(posY + raio, obsY)) {
		printf("%f, %f", posX,obsX);
		return true;
	}
	return false;
}
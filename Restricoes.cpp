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
bool podeAndar(float *argY) {
	if((*argY == -0.95f || *argY > 0.64f) || (*argY <= -0.54f && *argY >= -0.56f) || (*argY <= -0.14f && *argY >= -0.16f) || (*argY >= 0.25f && *argY <= 0.26f)) {
		return true;
	}
	return false;
}
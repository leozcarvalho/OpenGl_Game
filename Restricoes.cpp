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
bool subir(float *argX, float *argY) {
	if(*argY < 0.75f) {
		if ((*argX > 0.4f && *argX < 0.5f) || (*argX > 0.7f && *argX < 0.8f)) {
			return true;
		}
	}
	return false;
}
bool descer(float *argX, float *argY) {
	if(*argY > -0.95f) {
		if(*argY >= -0.95f) {
			if ((*argX > 0.4f && *argX < 0.5f) || (*argX > 0.7f && *argX < 0.8f)) {
				return true;
			}
		}
	}
	return false;
}
bool podeAndar(float *argY) {
	if(*argY == -0.95f || *argY == -0.65f || *argY == -0.3f) {
		return true;
	}
	return false;
}
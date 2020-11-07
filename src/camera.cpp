#include "camera.h"

Camera::Camera(int direcao, int alcance, int x, int y, int n, int m) {
	this->Visao = new int*[m];
	for (int j = 0; j < n; ++j)
    		Visao[j] = new int[n];
	this->direcao = direcao;
	this->alcance = alcance;
	this->deteccao = 0;
	this->x = x;
	this->y = y;
}

int Camera::get_direcao() {
	return (this->direcao);
}

int Camera::get_alcance() {
	return (this->alcance);
}

int** Camera::get_visao() {
	return (this->Visao);
}

int Camera::get_x() {
	return (this->x);
}

int Camera::get_y() {
	return (this->y);
}

int Camera::get_deteccao() {
	return (this->deteccao);
}

void Camera::set_deteccao(int deteccao) {
	this->deteccao = deteccao;
}

void Camera::set_visao(int** V, int n, int m) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			this->Visao[j][i] = V[j][i];
		}
	}
}

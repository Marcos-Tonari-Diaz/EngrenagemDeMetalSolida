#include "camera.h"

Camera::Camera(int direcao, int alcance, int x, int y) {
	this->direcao = direcao;
	this->alcance = alcance;
	this->avistado = 0;
	this->detectado = 0;
	this->x_vis = x;
	this->y_vis = y;
	setPosition(x,y);
}

int Camera::get_direcao() {
	return (this->direcao);
}

int Camera::get_x_vis() {
	return (this->x_vis);
}

int Camera::get_y_vis() {
	return (this->y_vis);
}

int Camera::get_alcance() {
	return (this->alcance);
}

int Camera::get_detectado() {
	return (this->detectado);
}

int Camera::get_avistado() {
	return (this->avistado);
}

void Camera::set_avistado(int avistado) {
	this->avistado = avistado;
}

void Camera::set_detectado(int detectado) {
	this->detectado = detectado;
}

void Camera::set_x_vis(int x_vis) {
	this->x_vis = x_vis;
}

void Camera::set_y_vis(int y_vis) {
	this->y_vis = y_vis;
}

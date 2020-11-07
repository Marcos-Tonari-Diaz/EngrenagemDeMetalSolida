#ifndef CAMERA_H
#define CAMERA_H

class Camera {
	private:
		int** Visao;
		int direcao;
		int alcance;
		int x;
		int y;
		int deteccao;
	public:
		Camera(int direcao, int alcance, int x, int y, int n, int m);
		int get_direcao();
		int get_alcance();
		int** get_visao();
		int get_x();
		int get_y();
		int get_detec();
		void set_detec(int deteccao);
		void set_visao(int** V, int n, int m);
};

#endif

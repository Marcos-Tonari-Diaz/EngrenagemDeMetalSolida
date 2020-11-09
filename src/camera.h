#ifndef CAMERA_H
#define CAMERA_H

class Camera : public Element {
	private:
		int direcao;
		int alcance;
		int detectado;
		int avistado;
		int x_vis;
		int y_vis;
	public:
		Camera(int direcao, int alcance, int x, int y, int n, int m);
		int get_direcao();
		int get_alcance();
		int get_detectado();
		int get_avistado();
		int get_x_vis();
		int get_y_vis();
		void set_avistado(int avistado);
		void set_x_vis();
		void set_y_vis();
		void set_detectado(int detectado);
};

#endif

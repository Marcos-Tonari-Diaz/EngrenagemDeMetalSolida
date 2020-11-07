#ifndef PORTA_H
#define PORTA_H

class Porta {
	private:
		int x;
		int y;
		int flag;
	public:
		Porta(int x, int y);
		int get_x();
		int get_y();
		int get_flag();
		void set_flag(int flag);
};

#endif

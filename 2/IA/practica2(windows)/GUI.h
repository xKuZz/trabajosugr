#ifndef GUI_H
#define GUI_H

#include<fstream>
#include"belkan.h"
#include"include/GL/glui.h"
namespace GUI{
	void myGlutReshape(int,int);
	void myGlutDisplay();
	void myGlutIdle();
	void myGlutTimer(int x);
	void myGlutTimer2(int x);
	void Load_Conf();
	void Save_Conf();
	void control_cb(int);
	int startDraw(int,char *[]);
	void showScore();
	void cerrar();
	void UpdateButton();
	void UpdateButton2();
	void UpdateButton_Sin_Reiniciar();


    bool doNextMove();
	void doOneStep();
	void doOneRun();
	void doAllRun();
	void nextRun();
	void newGame();
	void do_move(Agent::ActionType action);
	bool Juego_Terminado();
	void reshape(int width, int height);
	void display();
	void idle();
	void keyboard(unsigned char key, int x, int y);
};



#endif

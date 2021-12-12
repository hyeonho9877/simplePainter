#pragma once
#ifndef __INIT_HEAD__
#define __INIT_HEAD__
void motion(int x, int y);
void mouse(int button, int state, int x, int y);
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void init();
void mainMenuHandler(int value);
void objectSubmenuHandler(int value);
void lineSubmenuHandler(int value);
void fillSubmenuHandler(int value);
void createBorderBoxList();
#endif // !__INIT_HEAD__

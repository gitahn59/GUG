//============================================================================
// Name        : Main.java
// Author      : gitahn59
// Version     : 1.0
// Copyright   : MIT
// Description : Main thread 
//============================================================================

#include <iostream>
#include <glut.h>
#include "State.h"

using namespace std;

IState* st;
VaribleSelection varibleSelection;
Equation equation;
OperationSetting operationSetting;
GraphDrawing graphDrawing;

void mouseCallback(int button, int state, int x, int y) {
	if (state != GLUT_DOWN)
		return;
	int type = st->getType();

	if (button == GLUT_LEFT_BUTTON) {
		switch (type) {
		case 0:
			break;
		case 1:
			st = &varibleSelection;
			break;
		case 2:
			st = &equation;
			break;
		case 3:
			st = &operationSetting;
			break;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		switch (type) {
		case 0:
			st = &equation;
			break;
		case 1:
			st = &operationSetting;
			break;
		case 2:
			st = &graphDrawing;
			break;
		case 3:
			break;
		}
	}

	st->mouseCallback(button, state, x, y);
}

void displayCallback() {
	st->displayCallback();
}


int main(int argc, char** argv) {
	st = &varibleSelection;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GUG TEST");
	// Callback Setting Up
	glutDisplayFunc(displayCallback);
	glutMouseFunc(mouseCallback);

	glutMainLoop();
	return 0;
}

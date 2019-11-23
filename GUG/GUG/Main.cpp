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
#include "Control.h"

using namespace std;

IState* st;
VaribleSelection varibleSelection;
Equation equation;
OperationSetting operationSetting;
GraphDrawing graphDrawing;

void mouseCallback(int button, int state, int x, int y) {
	if (state != GLUT_DOWN)
		return;
	y = glutGet(GLUT_WINDOW_HEIGHT)-y;
	st->mouseCallback(button, state, x, y);
	int type = st->getType();
	switch (type) {
	case 1:
		Equation * pE = (Equation *)st;
		if (pE->isNextBtnClicked()) {
			st = &graphDrawing;
		}
	}
}

void displayCallback() {
	st->displayCallback();
	glutSwapBuffers();
}

void reshapeCallback(int width, int height) {
	st->reshpeCallback(width,height);
	glutPostRedisplay();
}

void specialCallback(int key, int x, int y) {
	int type = st->getType();
	if (key == GLUT_KEY_LEFT) {
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
	else if (key == GLUT_KEY_RIGHT) {
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
	glutPostRedisplay();
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
	glutReshapeFunc(reshapeCallback);
	glutSpecialFunc(specialCallback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();
	return 0;
}

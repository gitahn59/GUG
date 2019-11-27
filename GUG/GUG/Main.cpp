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
#include "MathExpression.h"

using namespace std;

IState* st;
VaribleSelection varibleSelection;
Equation equation;
OperationSetting operationSetting;
GraphDrawing graphDrawing;
Expression* expression;

void mouseCallback(int button, int state, int x, int y) {
	if (state != GLUT_DOWN)
		return;
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	st->mouseCallback(button, state, x, y);
	int type = st->getType();
	if (type == 1) {
		Equation* pE = (Equation*)st;
		if (pE->isNextBtnClicked()) {
			expression = new Expression(pE->getExpression());
			st = &graphDrawing;
			GraphDrawing* pG = (GraphDrawing*)st;
			pG->setExpressions(expression);
		}
	}
	else if (type == 3) {
		GraphDrawing* pG = (GraphDrawing*)st;
		if (pG->isBackBtnClicked()) {
			st = &equation;
		}
	}

	glutPostRedisplay();
}

void displayCallback() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	st->displayCallback();
	glutSwapBuffers();
}

void reshapeCallback(int width, int height) {
	glutPostRedisplay();
}

void specialCallback(int key, int x, int y) {
	int type = st->getType();
	st->specialCallback(key, x, y);
	glutPostRedisplay();
	/*if (key == GLUT_KEY_LEFT) {
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
	glutPostRedisplay();*/
}

int main(int argc, char** argv) {
	st = &equation;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GUG TEST");
	// Callback Setting Up
	glutDisplayFunc(displayCallback);
	glutMouseFunc(mouseCallback);
	glutReshapeFunc(reshapeCallback);
	glutSpecialFunc(specialCallback);

	
	glEnable(GL_DEPTH_TEST);//은면제거
	glEnable(GL_BLEND);//투명도
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();
	return 0;
}

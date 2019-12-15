//============================================================================
// Name        : Main.cpp
// Version     : 1.0
// Copyright   : MIT
// Description : Main thread. ������� �̺�Ʈ�� �� State�� �����Ѵ�
//============================================================================

#include <iostream>
#include <glut.h>
#include <windows.h>
#include "State.h"
#include "Control.h"
#include "MathExpression.h"

using namespace std;

IState* st;
Equation equation;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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
}

void passiveMotionCallback(int x, int y) {
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	int type = st->getType();
	if (type == 1) {
		Equation* pE = (Equation*)st;
		pE->passiveMotionCallback(x, y);
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GUG");
	
	// Callback Setting Up
	glutDisplayFunc(displayCallback);
	glutMouseFunc(mouseCallback);
	glutSpecialFunc(specialCallback);
	glutPassiveMotionFunc(passiveMotionCallback);
	
	glEnable(GL_BLEND);//����
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);//�ĸ� ���� Ȱ��ȭ
	glFrontFace(GL_CCW);//�ĸ� ����
	glCullFace(GL_BACK);// ����
	st = &equation;
	graphDrawing.loadTexture();
	glutMainLoop();
	return 0;
}

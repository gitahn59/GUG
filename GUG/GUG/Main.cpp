//============================================================================
// Name        : Main.cpp
// Author      : gitahn59
// Version     : 1.0
// Copyright   : MIT
// Description : Main thread. 사용자의 이벤트를 각 State로 전달한다
//============================================================================

#include <iostream>
#include <glut.h>
#include <windows.h>
#include <glaux.h>
#include "State.h"
#include "Control.h"
#include "MathExpression.h"

#pragma comment(lib, "glaux.lib")
#pragma comment (lib,"legacy_stdio_definitions.lib")

using namespace std;

IState* st;
Equation equation;
GraphDrawing graphDrawing;
Expression* expression;

void loadTexture(void) {
	AUX_RGBImageRec* pTextureImage = auxDIBImageLoad("apple.bmp"); // 유니코드 스트링임을 명시

	if (pTextureImage != NULL) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pTextureImage->sizeX, pTextureImage->sizeY, 0,
			GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
	}

	if (pTextureImage) {
		if (pTextureImage->data)
			free(pTextureImage->data);
		free(pTextureImage);
	}
}

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
}

void passiveMotionCallback(int x, int y) {
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	int type = st->getType();
	if (type == 1) {
		Equation* pE = (Equation*)st;
		pE->passiveMotionCallback(x, y);
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	loadTexture();
	st = &equation;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GUG");
	// Callback Setting Up
	glutDisplayFunc(displayCallback);
	glutMouseFunc(mouseCallback);
	glutReshapeFunc(reshapeCallback);
	glutSpecialFunc(specialCallback);
	glutPassiveMotionFunc(passiveMotionCallback);

	glEnable(GL_TEXTURE_2D);//은면제거
	glEnable(GL_DEPTH_TEST);//은면제거
	glEnable(GL_BLEND);//투명도
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();
	return 0;
}

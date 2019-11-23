#pragma once

#include "State.h"
#include "Control.h"
#include "MathExpression.h"
#include <iostream>
#include <glut.h>

using namespace std;

void VaribleSelection::displayCallback() {
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
}

void VaribleSelection::keyboardCallback(unsigned char key, int state, int x, int y) {

}
void VaribleSelection::mouseCallback(int button, int state, int x, int y) {
	cout << "Current State is VaribleSelection\n";
	glutPostRedisplay();
}
int VaribleSelection::getType() {
	return 0;
}
void VaribleSelection::reshpeCallback(int width, int height) {
	this->width = width;
	this->height = height;
}


Equation::Equation() {
	this->width = 500;
	this->height = 500;
	float a = this->width / 6.0;
	float b = this->height / 5.0;
	setControlsPosition(width, height);
	
	buttons[3][0].setText("root");
	buttons[3][1].setText("7");
	buttons[3][2].setText("8");
	buttons[3][3].setText("9");
	buttons[3][4].setText("<-");

	buttons[2][0].setText("log");
	buttons[2][1].setText("4");
	buttons[2][2].setText("5");
	buttons[2][3].setText("6");
	buttons[2][4].setText("sin");

	buttons[1][0].setText("a^b");
	buttons[1][1].setText("1");
	buttons[1][2].setText("2");
	buttons[1][3].setText("3");
	buttons[1][4].setText("cos");

	buttons[0][0].setText("(");
	buttons[0][1].setText(")");
	buttons[0][2].setText("0");
	buttons[0][3].setText(".");
	buttons[0][4].setText("tan");
}

void Equation::setControlsPosition(int width,int height) {
	float a = width / 5.0;
	float b = height / 5.0;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 5; k++) {
			buttons[i][k].setArea(Rect(k*a,i*b,a,b));
		}
	}
	textBox.setArea(Rect(a*1.5, b * 4, a * 4.5, b));
}

void Equation::displayCallback() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_VIEWPORT);
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glPushMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);
		glColor4f(0.35, 0.16, 0.55,1);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glColor4f(0.26, 0.52, 0.63, 1);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);
	glEnd();
	glPopMatrix();
	
	setControlsPosition(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 5; k++) {
			buttons[i][k].draw();
		}
	}
	textBox.draw();
	
	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();

}

void Equation::reshpeCallback(int width, int height) {
	this->width = width;
	this->height = height;
}

void Equation::keyboardCallback(unsigned char key, int state, int x, int y) {

}
void Equation::mouseCallback(int button, int state, int x, int y) {
	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 6; k++) {
			if (buttons[i][k].isHover(x, y)) {
				cout << buttons[i][k].toString() << endl;
				i=5;
				break;
			}
		}
	}

	cout << "Current State is Equation\n";
	glutPostRedisplay();
}

int Equation::getType() {
	return 1;
}

void OperationSetting::displayCallback() {
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

}

void OperationSetting::keyboardCallback(unsigned char key, int state, int x, int y) {

}
void OperationSetting::mouseCallback(int button, int state, int x, int y) {
	cout << "Current State is OperationSetting\n";
	glutPostRedisplay();
}

void OperationSetting::reshpeCallback(int width, int height) {
	this->width = width;
	this->height = height;
}

int OperationSetting::getType() {
	return 2;
}

void GraphDrawing::displayCallback() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
}

void GraphDrawing::keyboardCallback(unsigned char key, int state, int x, int y) {

}
void GraphDrawing::mouseCallback(int button, int state, int x, int y) {
	cout << "Current State is GraphDrawing\n";
	glutPostRedisplay();
}

void GraphDrawing::reshpeCallback(int width, int height) {
	this->width = width;
	this->height = height;
}

int  GraphDrawing::getType() {
	return 3;
}

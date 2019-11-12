#pragma once

#include "State.h"
#include <iostream>
#include <glut.h>

using namespace std;

void VaribleSelection::displayCallback() {
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
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


void Equation::displayCallback() {
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void Equation::keyboardCallback(unsigned char key, int state, int x, int y) {

}
void Equation::mouseCallback(int button, int state, int x, int y) {
	cout << "Current State is Equation\n";
	glutPostRedisplay();
}
int Equation::getType() {
	return 1;
}

void OperationSetting::displayCallback() {
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void OperationSetting::keyboardCallback(unsigned char key, int state, int x, int y) {

}
void OperationSetting::mouseCallback(int button, int state, int x, int y) {
	cout << "Current State is OperationSetting\n";
	glutPostRedisplay();
}
int OperationSetting::getType() {
	return 2;
}



void  GraphDrawing::displayCallback() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void  GraphDrawing::keyboardCallback(unsigned char key, int state, int x, int y) {

}
void  GraphDrawing::mouseCallback(int button, int state, int x, int y) {
	cout << "Current State is GraphDrawing\n";
	glutPostRedisplay();
}
int  GraphDrawing::getType() {
	return 3;
}

#pragma once

#include "State.h"
#include "Control.h"
#include "MathExpression.h"
#include <iostream>
#include <glut.h>

using namespace std;

void VaribleSelection::displayCallback() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_VIEWPORT);
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);
	glColor4f(0.35, 0.16, 0.55, 1);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glColor4f(0.26, 0.52, 0.63, 1);
	glVertex3f(1, 1, 0);
	glVertex3f(-1, 1, 0);
	glEnd();
	glPopMatrix();
	
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
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_VIEWPORT);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);
	glColor4f(0.35, 0.16, 0.55, 1);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glColor4f(0.26, 0.52, 0.63, 1);
	glVertex3f(1, 1, 0);
	glVertex3f(-1, 1, 0);
	glEnd();
	glPopMatrix();

	glMatrixMode(GL_VIEWPORT);
	glLoadIdentity();
	float w = width * 0.7;
	float h;
	if (w < height) {
		h = w;
	}
	else {
		w = height * 0.9;
		h = w;
	}
	glViewport(width/2-w/2, height/2-h/2, w,h);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glOrtho(-5, 5, -5, 5, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);
	glColor4f(1,1,1,0.4);
	glVertex3f(-5, -5, 0);
	glVertex3f(5, -5, 0);
	glVertex3f(5, 5, 0);
	glVertex3f(-5, 5, 0);
	glEnd();
	
	glColor4f(0, 0, 0, 0.9);
	glBegin(GL_LINES);
	/*for (float x = -3; x <= 3; x += 0.0005) {
		float f = (x - 0.0005);
		float ff = f * f;
		glVertex3f(f, ff, 1);
		glVertex3f(x, x*x, 1);
	}*/
	for (float x = -5; x <= 5; x += 0.0005) {
		float f = (x - 0.0005);
		float ff = sin(f);
		glVertex3f(f, ff, 1);
		glVertex3f(x, sin(x), 1);
	}
	glEnd();
	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

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

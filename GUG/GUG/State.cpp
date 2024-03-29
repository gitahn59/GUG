//============================================================================
// Name        : Main.cpp
// Author      : gitahn59
// Version     : 1.0
// Copyright   : MIT
// Description : State.h�� ����
//============================================================================

#pragma once
#include "State.h"
#include "Control.h"
#include "MathExpression.h"
#include <iostream>
#include <glut.h>

using namespace std;

void renderBitmapCharacher(float x, float y, float z, void* font, string s)
{
	glRasterPos3f(x, y, z);
	for (int i = 0; i < s.length(); i++) {
		glutBitmapCharacter(font, s[i]);
	}
}

void GraphDrawing::displayCallback() {
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);
	
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

	btn.setArea(Rect(width / 2 + w / 1.9, height / 8, w / 6, height / 6));
	btn.draw();

	glViewport(width/2-w/2, height/2-h/2, w,h);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glOrtho(-rangeW, rangeW, -rangeH, rangeH, -2, 2);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, -1, 0, 1, 0);
	glColor4f(1, 1, 1, 0.5);
	int font = (int)GLUT_BITMAP_HELVETICA_18;
	renderBitmapCharacher(0, -0.1, 0.5, (void*)font, "text");

	glBegin(GL_QUADS);
	glColor4f(1,1,1,0.4);
	glVertex3f(-rangeW, -rangeH, 0.2);
	glVertex3f(rangeW, -rangeH, 0.2);
	glVertex3f(rangeW, rangeH, 0.2);
	glVertex3f(-rangeW, rangeH, 0.2);
	glEnd();
	
	vector<bff> vbff = expression->calculate(-rangeW, rangeW, 0.01);

	glColor4f(0, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(-rangeW, 0, 0.4);
	glVertex3f(rangeW, 0, 0.4);
	glVertex3f(0, -rangeH, 0.4);
	glVertex3f(0, rangeH, 0.4);
	glEnd();

	glColor4f(0.66, 0.26, 0.25, 0.9);
	glBegin(GL_LINES);
	int len = vbff.size();
	for (int i = 0; i < len - 1; i++){
		if (vbff[i].first && vbff[i+1].first) {
			glVertex3f(vbff[i].second.first, vbff[i].second.second, 0.6);
			glVertex3f(vbff[i + 1].second.first, vbff[i + 1].second.second, 0.6);
		}
	}
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	

}

void GraphDrawing::keyboardCallback(unsigned char key, int state, int x, int y) {

}

void GraphDrawing::specialCallback(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		reduceRangeW();
		break;
	case GLUT_KEY_RIGHT:
		raiseRangeW();
		break;
	case GLUT_KEY_UP:
		raiseRangeH();
		break;
	case GLUT_KEY_DOWN:
		reduceRangeH();
		break;
	}
}

void GraphDrawing::mouseCallback(int button, int state, int x, int y) {
	if (btn.isHover(x, y)) {
		backBtnClicked = true;
	}
	cout << "Current State is GraphDrawing\n";
}

void GraphDrawing::reshpeCallback(int width, int height) {
	this->width = width;
	this->height = height;
}

int  GraphDrawing::getType() {
	return 3;
}
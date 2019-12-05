//============================================================================
// Name        : Equation.cpp
// Author      : gitahn59
// Version     : 1.0
// Copyright   : MIT
// Description : IState.h의 Class중에서 GraphDrawing Class를 구현
//               GraphDrawing는 Equation에서 입력받은 수식을 바탕으로
//               그래프를 화면에 도시한다.
//============================================================================

#pragma once

#include "State.h"
#include "Control.h"
#include "MathExpression.h"
#include <iostream>
#include <glut.h>

using namespace std;

void GraphDrawing::displayCallback() {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	
	drawPanel();

	float w = width * 0.7;
	float h;
	if (w < height) {
		h = w;
	}
	else {
		w = height * 0.9;
		h = w;
	}

	glMatrixMode(GL_VIEWPORT);
	glLoadIdentity();
	
	btn.setText("BACK");
	btn.setArea(Rect(width/40, height/2-height/12, w / 7, height / 6));
	glEnable(GL_TEXTURE_2D);
	btn.drawTexture();
	glDisable(GL_TEXTURE_2D);

	// graph : s
	glViewport(width/2-w/2, height/2-h/2, w,h);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glOrtho(-rangeW, rangeW, -rangeH, rangeH, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor4f(0, 0, 0, 0.5);
	int font = (int)GLUT_BITMAP_HELVETICA_18;
	renderBitmapCharacher(0, rangeH*0.95,0.5, (void*)font,to_string(rangeH));
	renderBitmapCharacher(0, -rangeH, 0.5, (void*)font, "-"+to_string(rangeH));
	renderBitmapCharacher(rangeW * 0.95,0, 0.5, (void*)font, to_string(rangeW));
	renderBitmapCharacher(-rangeW,0, 0.5, (void*)font, "-" + to_string(rangeW));

	glBegin(GL_QUADS);
	glColor4f(1,1,1,0.4);
	glVertex3f(-rangeW, -rangeH, 0.2);
	glVertex3f(rangeW, -rangeH, 0.2);
	glVertex3f(rangeW, rangeH, 0.2);
	glVertex3f(-rangeW, rangeH, 0.2);
	glEnd();
	
	glColor4f(0, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(-rangeW, 0, 0.4);
	glVertex3f(rangeW, 0, 0.4);
	glVertex3f(0, -rangeH, 0.4);
	glVertex3f(0, rangeH, 0.4);
	glEnd();

	vector<bff> vbff = expression->calculate(-rangeW, rangeW, 0.01);

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
	//graph : e
	

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
	
}

int  GraphDrawing::getType() {
	return 3;
}
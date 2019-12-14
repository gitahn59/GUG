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

	float w = width * 0.6;
	float h;
	if (w < height) {
		h = w;
	}
	else {
		w = height * 0.85;
		h = w;
	}

	glMatrixMode(GL_VIEWPORT);
	glLoadIdentity();
	
	backBtn.setArea(Rect(width/40, height/2-height/12, w / 7, height / 6));
	leftBtn.setArea(Rect(width / 2 + w / 2 - 115, height / 2 + h / 2 + 4, 33, 33));
	rightBtn.setArea(Rect(width / 2 + w / 2 - 75, height / 2 + h / 2 + 4, 33, 33));
	swapBtn.setArea(Rect(width / 2 + w /2-35, height / 2+h/2+4, 33, 33));

	backBtn.drawTriangleTexture(textureObjectID[0]);
	leftBtn.drawQuadsTexture(textureObjectID[1]);
	rightBtn.drawQuadsTexture(textureObjectID[2]);
	swapBtn.drawQuadsTexture(textureObjectID[3]);

	// graph : s
	glViewport(width/2-w/2, height/2-h/2, w,h);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glOrtho(-rangeW, rangeW, -rangeH, rangeH, -5, 5);

	glEnable(GL_DEPTH_TEST);
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

	if (swap)
		glScalef(-1, 1, 1);
	glRotatef(angle, 0, 0, -1);
	
	glColor4f(0.66, 0.26, 0.25, 0.9);
	glBegin(GL_LINES);
	vector<Node> leftNodes = expression->calculate(-rangeW, 0, 0.01);
	int len = leftNodes.size();
	for (int i = 0; i < len - 1; i++){
		glVertex3f(leftNodes[i].x, leftNodes[i].y, 0.6);
		glVertex3f(leftNodes[i+1].x, leftNodes[i+1].y, 0.6);
	}
	glEnd();

	glColor4f(0.66, 0.26, 0.25, 0.9);
	glBegin(GL_LINES);
	vector<Node> rightNodes = expression->calculate(0, rangeW, 0.01);
	len = rightNodes.size();
	for (int i = 0; i < len - 1; i++) {
		glVertex3f(rightNodes[i].x, rightNodes[i].y, 0.6);
		glVertex3f(rightNodes[i + 1].x, rightNodes[i + 1].y, 0.6);
	}
	glEnd();

	
	glDisable(GL_DEPTH_TEST);
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
	if (backBtn.isHover(x, y)) {
		backBtnClicked = true;
	}else if (rightBtn.isHover(x, y)) {
		angle += 90;
	}
	else if (leftBtn.isHover(x, y)) {
		angle -= 90;
	}
	else if (swapBtn.isHover(x, y)) {
		swap = !swap;
	}

	cout << "Current State is GraphDrawing\n";
}

int  GraphDrawing::getType() {
	return 3;
}

void GraphDrawing::loadTexture(void) {
	glGenTextures(3, textureObjectID);

	AUX_RGBImageRec* pTextureImage = auxDIBImageLoad("arrow.bmp"); // 유니코드 스트링임을 명시

	if (pTextureImage != NULL) {
		glBindTexture(GL_TEXTURE_2D, textureObjectID[0]);
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

	pTextureImage = auxDIBImageLoad("left.bmp"); // 유니코드 스트링임을 명시
	if (pTextureImage != NULL) {
		glBindTexture(GL_TEXTURE_2D, textureObjectID[1]);
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


	pTextureImage = auxDIBImageLoad("right.bmp"); // 유니코드 스트링임을 명시
	if (pTextureImage != NULL) {
		glBindTexture(GL_TEXTURE_2D, textureObjectID[2]);
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

	pTextureImage = auxDIBImageLoad("swap.bmp"); // 유니코드 스트링임을 명시
	if (pTextureImage != NULL) {
		glBindTexture(GL_TEXTURE_2D, textureObjectID[3]);
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
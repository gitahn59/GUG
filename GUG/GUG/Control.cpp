//============================================================================
// Name        : Control.cpp
// Author      : gitahn59
// Version     : 1.0
// Copyright   : MIT
// Description : Control.h¸¦ ±¸Çö 
//============================================================================

#pragma once
#include "Control.h"
#include <glut.h>

// Rect : s
Rect::Rect(int x, int y,int width, int heigth) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = heigth;
}

bool Rect::isIn(int x, int y) {
	if (this->x < x && x < this->x + width) {
		if (this->y < y && y < this->y + height) {
			return true;
		}
	}
	return false;
}
// Rect : e

void IControl::renderBitmapCharacher(float x, float y, float z, void* font, string s)
{
	glRasterPos3f(x, y, z);
	for (int i = 0; i < s.length(); i++) {
		glutBitmapCharacter(font, s[i]);
	}
}

// Button : s
void Button::setArea(Rect area) {
	this->area = area;
}

Button::Button(Rect area,string text){
	this->area = area;
	this->text = text;
}

string Button::toString(){
	return this->text;
}

void Button::draw() {
	glMatrixMode(GL_VIEWPORT);
	glPushMatrix();
	glViewport(area.getX(), area.getY(), area.getWidth(), area.getHeight());
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
	glColor4f(1, 1, 1,0.5);
	int font = (int)GLUT_BITMAP_HELVETICA_18;
	renderBitmapCharacher(center[0], center[1], center[2], (void*)font, printedText);

	glColor4f(1,1,1, 0.05);
	glBegin(GL_QUADS);
	glVertex3f(-0.95, -0.95, -1);
	glVertex3f(0.95, -0.95,-1);
	glVertex3f(0.95,0.95, -1);
	glVertex3f(-0.95, 0.95,-1);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();
}

void Button::drawLight() {
	hovered = false;

	const GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
	const GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
	const GLfloat white[] = { 1.0, 1.0, 1.0, 0.1 };
	const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
	const GLfloat polished[] = { 100.0 };
	const GLfloat light_pos[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat const_att = 2.5;

	glMatrixMode(GL_VIEWPORT);
	glPushMatrix();//viewport:s
	glViewport(area.getX(), area.getY(), area.getWidth(), area.getHeight());
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();//light:s
	glTranslatef(0, 0, 1);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, const_att);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
	glPopMatrix();//light:e
	
	glPushMatrix();//model:s
		glLoadIdentity();
		gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
		glMaterialfv(GL_FRONT, GL_SPECULAR, black);
		glMaterialfv(GL_FRONT, GL_SHININESS, polished);
		glDisable(GL_LIGHTING);
		glColor4f(1, 1, 1, 0.7);
		int font = (int)GLUT_BITMAP_HELVETICA_18;
		renderBitmapCharacher(center[0], center[1], center[2], (void*)font, printedText);
		glColor4f(1, 1, 1, 0.2);
		glBegin(GL_QUADS);
		glVertex3f(-0.95, -0.95, -1);
		glVertex3f(0.95, -0.95, -1);
		glVertex3f(0.95, 0.95, -1);
		glVertex3f(-0.95, 0.95, -1);
		glEnd();
		glEnable(GL_LIGHTING);
	glPopMatrix();//model:e
	
	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();//viewport:e
	glDisable(GL_LIGHTING);
}

void Button::drawTexture() {
	Vertex quadVertices[] = {
		{ 0.0f,0.0f, -1.0f,-1.0f, 1.0f },
		{ 1.0f,0.0f,  1.0f,-1.0f, 1.0f },
		{ 1.0f,1.0f,  1.0f, 1.0f, 1.0f },
		{ 0.0f,1.0f, -1.0f, 1.0f, 1.0f }
	};

	glMatrixMode(GL_VIEWPORT); //viewport : s
	glPushMatrix();
	glViewport(area.getX(), area.getY(), area.getWidth(), area.getHeight());
	
	glMatrixMode(GL_PROJECTION); // projection : s
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.2, 1, -1.6, 1.6, -5, 5);
	
	glMatrixMode(GL_MODELVIEW); //model : s
	glPushMatrix(); 
	glLoadIdentity();
	glColor4f(1, 1, 1, 0.3);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(-0.2f, 0.5f); glVertex3f(-1, 0, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1.6, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1.6, 1.0f);
	glEnd();
	glPopMatrix(); //model : e
	
	glMatrixMode(GL_PROJECTION); 
	glPopMatrix(); // projection : e

	glMatrixMode(GL_VIEWPORT);
	glPopMatrix(); //viewport : e
}

bool Button::isHover(int x, int y) {
	return area.isIn(x, y);
}

//Button : e

//TextBox : s
string expToText(string expression) {
	int len = expression.length();

	string temp="";
	for (int i = 0; i < len; i++) {
		switch (expression[i]) {
		case 'l': temp += "log"; break;
		case 'r': temp += "sqrt"; break;
		case 'c': temp += "cos"; break;
		case 's': temp += "sin"; break;
		case 't': temp += "tan"; break;
		case '*': temp += "x"; break;
		default: temp += expression[i];
		}
	}
	return temp;
}

void TextBox::draw(string expression) {
	glMatrixMode(GL_VIEWPORT);
	glPushMatrix();
	glViewport(area.getX(), area.getY(), area.getWidth(), area.getHeight());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
	glColor4f(1, 1, 1, 0.5);
	int font = (int)GLUT_BITMAP_HELVETICA_18;

	string temp = expToText(expression);
	renderBitmapCharacher(0.95-temp.length()*0.032, -0.1, -0.5, (void*)font, temp);

	glColor4f(1, 1, 1, 0.05);
	glBegin(GL_QUADS);
	glVertex3f(-0.97, -0.95, -1);
	glVertex3f(0.97, -0.95, -1);
	glVertex3f(0.97, 0.95, -1);
	glVertex3f(-0.97, 0.95, -1);
	glEnd();
	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();
}

bool TextBox::isHover(int x, int y) {
	return area.isIn(x, y);
}
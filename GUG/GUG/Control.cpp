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

void IControl::drawStringAtCenter(float width, float y, float z, string s)
{
	int font = (int)GLUT_BITMAP_HELVETICA_18;
	int sum = 0;
	for (int i = 0; i < s.length(); i++) {
		sum+= glutBitmapWidth((void*)font, (int)s[i]);
	}
	float centerX = (float)sum / width;
	glRasterPos3f(-centerX, y, z);
	for (int i = 0; i < s.length(); i++) {
		glutBitmapCharacter((void*)font, s[i]);
	}
}

void IControl::drawStringAtRight(float width, float y, float z, string s)
{
	int font = (int)GLUT_BITMAP_HELVETICA_18;
	int sum = 0; 
	for (int i = 0; i < s.length(); i++) {
		sum += glutBitmapWidth((void*)font, (int)s[i]);
	}
	float rightX = (float)sum*2 / (width);
	glRasterPos3f(0.945-rightX, y, z);
	for (int i = 0; i < s.length(); i++) {
		glutBitmapCharacter((void*)font, s[i]);
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
	
	drawStringAtCenter(area.getWidth(), center[1], center[2], printedText);

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
	const GLfloat white[] = { 1.0, 1.0, 1.0, 0.15 };
	const GLfloat polished[] = { 100.0 };
	const GLfloat light_pos[] = { 0.0, 0.0, 1.0, 1.0 };

	glMatrixMode(GL_VIEWPORT);
	glPushMatrix();//viewport:s
	glViewport(area.getX(), area.getY(), area.getWidth(), area.getHeight());
	
	glMatrixMode(GL_MODELVIEW);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  white);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);
	
	glPushMatrix();//model:s
		glLoadIdentity();
		gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
		glColor4f(1, 1, 1, 0.7);
		int font = (int)GLUT_BITMAP_HELVETICA_18;
		drawStringAtCenter(area.getWidth(), center[1], center[2], printedText);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glBegin(GL_QUADS);
		glVertex3f(-0.95, -0.95, -1);
		glVertex3f(0.95, -0.95, -1);
		glVertex3f(0.95, 0.95, -1);
		glVertex3f(-0.95, 0.95, -1);
		glEnd();
	glPopMatrix();//model:e
	
	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();//viewport:e
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

void Button::drawTriangleTexture(GLuint id) {
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
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(-0.2f, 0.5f); glVertex3f(-1, 0, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1.6, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1.6, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix(); //model : e
	
	glMatrixMode(GL_PROJECTION); 
	glPopMatrix(); // projection : e

	glMatrixMode(GL_VIEWPORT);
	glPopMatrix(); //viewport : e
}

void Button::drawQuadsTexture(GLuint id) {
	glMatrixMode(GL_VIEWPORT); //viewport : s
	glPushMatrix();
	glViewport(area.getX(), area.getY(), area.getWidth(), area.getHeight());

	glMatrixMode(GL_PROJECTION); // projection : s
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-0.75, 0.75, -0.65, 0.65, -1, 1);
	
	glMatrixMode(GL_MODELVIEW); //model : s
	glPushMatrix();
	glLoadIdentity();
	glColor4f(1, 1, 1, 0.3);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 1, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
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
	drawStringAtRight(area.getWidth(), -0.1, -0.5, temp);

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

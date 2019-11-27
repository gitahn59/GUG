#include "Control.h"
#include <glut.h>

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
int Rect::getX() {
	return x;
}
int Rect::getY() {
	return y;
}
int Rect::getWidth() {
	return width;
}
int Rect::getHeight() {
	return height;
}

// Button : s
void Button::setArea(Rect area) {
	this->area = area;
}

Button::Button(Rect area,string text){
	this->area = area;
	this->text = text;
}

void Button::setText(string text) {
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
	glLoadIdentity();
	glColor4f(1,1,1, 0.05);
	glBegin(GL_QUADS);
		glVertex3f(-0.95, -0.95, -1);
		glVertex3f(0.95, -0.95,-1);
		glVertex3f(0.95,0.95, -1);
		glVertex3f(-0.95, 0.95,-1);
	glEnd();
	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();
}

bool Button::isHover(int x, int y) {
	return area.isIn(x, y);
}

//Button : e

//TextBox : s
void TextBox::setArea(Rect area) {
	this->area = area;
}

TextBox::TextBox(Rect area) {
	this->area = area;
}

void TextBox::draw() {
	glMatrixMode(GL_VIEWPORT);
	glPushMatrix();
	glViewport(area.getX(), area.getY(), area.getWidth(), area.getHeight());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
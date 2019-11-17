#include "Control.h"
#include <glut.h>

Rectangle::Rectangle(int x, int y,int width, int heigth) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = heigth;
}
bool Rectangle::isIn(int x, int y) {
	if (this->x < x && x < this->x + width) {
		if (this->y < y && y < this->y + height) {
			return true;
		}
	}
	return false;
}
int Rectangle::getX() {
	return x;
}
int Rectangle::getY() {
	return y;
}
int Rectangle::getWidth() {
	return width;
}
int Rectangle::getHeight() {
	return height;
}

void Button::setArea(Rectangle area) {
	this->area = area;
}

Button::Button(Rectangle area){
	this->area = area;
}

void Button::draw() {
	glMatrixMode(GL_VIEWPORT);
	glPushMatrix();
	glViewport(area.getX(), area.getY(), area.getWidth(), area.getHeight());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor4f(1,1,1, 0.05);
	glBegin(GL_QUADS);
		glVertex3f(-0.95, -0.95, 0);
		glVertex3f(0.95, -0.95, 0);
		glVertex3f(0.95,0.95, 0);
		glVertex3f(-0.95, 0.95, 0);
	glEnd();
	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();
}

bool Button::isHover(int x, int y) {
	return area.isIn(x, y);
}


void TextBox::setArea(Rectangle area) {
	this->area = area;
}

TextBox::TextBox(Rectangle area) {
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
	glVertex3f(-0.97, -0.95, 0);
	glVertex3f(0.97, -0.95, 0);
	glVertex3f(0.97, 0.95, 0);
	glVertex3f(-0.97, 0.95, 0);
	glEnd();
	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();
}

bool TextBox::isHover(int x, int y) {
	return area.isIn(x, y);
}
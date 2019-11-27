#include "State.h"
#include "Control.h"
#include "MathExpression.h"
#include <iostream>
#include <glut.h>

using namespace std;

Equation::Equation() {
	this->width = 500;
	this->height = 500;
	setControlsPosition(width, height);

	buttons[3][0].setText("r");
	buttons[3][1].setText("7");
	buttons[3][2].setText("8");
	buttons[3][3].setText("9");
	buttons[3][4].setText("/");
	buttons[3][5].setText("<-");
	buttons[3][6].setText("X");

	buttons[2][0].setText("l");
	buttons[2][1].setText("4");
	buttons[2][2].setText("5");
	buttons[2][3].setText("6");
	buttons[2][4].setText("*");
	buttons[2][5].setText("s");

	buttons[1][0].setText("^");
	buttons[1][1].setText("1");
	buttons[1][2].setText("2");
	buttons[1][3].setText("3");
	buttons[1][4].setText("-");
	buttons[1][5].setText("c");

	buttons[0][0].setText("(");
	buttons[0][1].setText(")");
	buttons[0][2].setText("0");
	buttons[0][3].setText(".");
	buttons[0][4].setText("+");
	buttons[0][5].setText("t");
	buttons[0][6].setText("NEXT");
}

void Equation::setControlsPosition(int width, int height) {
	float a = width / 7.0;
	float b = height / 5.0;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 7; k++) {
			buttons[i][k].setArea(Rect(k * a, i * b, a, b));
		}
	}
	textBox.setArea(Rect(a * 1.5, b * 4, a * 5.5, b));
}

void Equation::displayCallback() {
	setControlsPosition(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

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

	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 7; k++) {
			buttons[i][k].draw();
		}
	}
	textBox.draw();

}

void Equation::reshpeCallback(int width, int height) {
	this->width = width;
	this->height = height;
}

void Equation::keyboardCallback(unsigned char key, int state, int x, int y) {

}

bool validation(string expression) {
	if (expression == "")
		return true;
	int len = expression.length();

	for (int i = 0; i < len - 1; i++) {
		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
			if (expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' || expression[i + 1] == '/') {
				return false;
			}
		}

		if (expression[i] == 'c' || expression[i] == 's' ||
			expression[i] == 't' || expression[i] == 'r' ||
			expression[i] == 'l') {
			if (expression[i + 1] == 'c' || expression[i + 1] == 's' ||
				expression[i + 1] == 't' || expression[i + 1] == 'r' ||
				expression[i + 1] == 'l') {
				return false;
			}
		}
	}
}



void Equation::mouseCallback(int button, int state, int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 7; k++) {
			if (buttons[i][k].isHover(x, y)) {
				string text = buttons[i][k].toString();
				if (text == "<-") {
					if (expression != "") {
						expression = expression.substr(0, expression.length() - 1);
					}
				}
				else if (text == "NEXT") {
					nextBtnClicked = true;
				}
				else {
					if (validation(expression + text))
						expression += text;
				}
				cout << expression << endl;
				
				i = 5;
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

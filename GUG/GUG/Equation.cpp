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

	setControlsPosition(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 7; k++) {
			buttons[i][k].draw();
		}
	}
	textBox.draw();

	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();

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

Operand stringToOperand(string s) {
	if (s == "X") {
		return Operand(true,OP_NUMBER);
	}

	try {
		if (s == "sX") {
			return Operand(true,OP_SIN);
		}
		else if (s == "cX") {
			return Operand(true,OP_COS);
		}
		else if (s == "tX") {
			return Operand(true,OP_TAN);
		}
		else if (s == "lX") {
			return Operand(true,OP_LOG);
		}
		else if (s == "rX") {
			return Operand(true,OP_ROOT);
		}

		if (s.length() >= 2)
			switch (s[0]) {
			case 's':
				return Operand(OP_SIN, stof(s.substr(1, s.length() - 1)));
			case 'c':
				return Operand(OP_COS, stof(s.substr(1, s.length() - 1)));
			case 't':
				return Operand(OP_TAN, stof(s.substr(1, s.length() - 1)));
			case 'l':
				return Operand(OP_LOG, stof(s.substr(1, s.length() - 1)));
			case 'r':
				return Operand(OP_ROOT, stof(s.substr(1, s.length() - 1)));
			case 'X':
				if (s[1] == '^') {
					return Operand(true,OP_EXPONENTIATION, stof(s.substr(2, s.length() - 2)));
				}
			}

		return Operand(OP_NUMBER, stof(s));
	}
	catch (std::invalid_argument ia) {
		return Operand(OP_NUMBER, 0.0);
	}
}

vector<MathExpression*> Equation::getExpression() {
	vector<MathExpression*> vm;

	int len = expression.length();
	std::string s = expression;

	vector<string> voperand;
	vector<char> voperator;

	int pos = 0;
	for (int i = 0; i < len; i++) {
		string temp = "";
		switch (s[i]) {
		case '/':
			temp = s.substr(pos, i);
			if (temp != "") {
				vm.push_back(&stringToOperand(temp));
			}
			pos = i + 1;
			vm.push_back(&Operator(OP_DEVIDE));
			break;
		case '*':
			temp = s.substr(pos, i);
			if (temp != "")
				vm.push_back(&stringToOperand(temp));
			pos = i + 1;
			vm.push_back(&Operator(OP_MULTIPLE));
			break;
		case '+':
			temp = s.substr(pos, i);
			if (temp != "")
				vm.push_back(&stringToOperand(temp));
			pos = i + 1;
			vm.push_back(&Operator(OP_PLUS));
			break;
		case '-':
			temp = s.substr(pos, i);
			if (temp != "")
				vm.push_back(&stringToOperand(temp));
			pos = i + 1;
			vm.push_back(&Operator(OP_MINUS));
			break;
		case '(':
			temp = s.substr(pos, i);
			if (temp != "")
				vm.push_back(&stringToOperand(temp));
			pos = i + 1;
			vm.push_back(&Operator(OP_LEFT_BRACKET));
			break;
		case ')':
			temp = s.substr(pos, i);
			if (temp != "")
				vm.push_back(&stringToOperand(temp));
			pos = i + 1;
			vm.push_back(&Operator(OP_RIGHT_BRACKET));
			break;
		}
	}
	string temp = s.substr(pos, len);
	if (temp != "")
		vm.push_back(&stringToOperand(temp));

	return vm;
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
				getExpression();
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

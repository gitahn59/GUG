//============================================================================
// Name        : State.h
// Author      : gitahn59
// Version     : 1.0
// Copyright   : MIT
// Description : State에 관련된 클래스의 헤더파일, 프로그램의 State를 정의한다. 
//               그리고 State들의 Interface인 IState를 정의한다.
//============================================================================

#pragma once
#include "Control.h"
#include "MathExpression.h"

class IState
{
public:
	virtual void displayCallback() = 0;
	virtual void keyboardCallback(unsigned char key, int state, int x, int y) = 0;
	virtual void specialCallback(int key, int x, int y) = 0;
	virtual void mouseCallback(int btn, int state, int x, int y) = 0;
	virtual void reshpeCallback(int x, int y) = 0;
	virtual int getType() = 0;
	void drawPanel() {
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

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
	}

	void renderBitmapCharacher(float x, float y, float z, void* font, string s)
	{
		glRasterPos3f(x, y, z);
		for (int i = 0; i < s.length(); i++) {
			glutBitmapCharacter(font, s[i]);
		}
	}
};

class Equation : public IState {
private:
	Button buttons[4][7];
	TextBox textBox;
	int width;
	int height;
	string expression = "";
	bool nextBtnClicked=false;
public:
	Equation();
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void specialCallback(int key, int x, int y) override {}
	void mouseCallback(int btn, int state, int x, int y) override;
	void reshpeCallback(int width, int height) override;
	void passiveMotionCallback(int x, int y);

	int getType() override;
	void setControlsPosition(int width, int height);
	bool isNextBtnClicked() {
		if (nextBtnClicked) {
			nextBtnClicked = false;
			return true;
		}
		return false;
	}
	string getExpression() {
		return expression;
	}

};

class GraphDrawing : public IState {
private:
	Expression* expression;
	Button btn;
	int rangeW = 3;
	int rangeH = 3;
	bool backBtnClicked = false;
	void raiseRangeW() {
		rangeW++;
	}
	void raiseRangeH() {
		rangeH++;
	}
	void reduceRangeW() {
		if (rangeW >= 2)
			rangeW--;
	}
	void reduceRangeH() {
		if (rangeH >= 2)
			rangeH--;
	}
public:
	GraphDrawing() {
		btn = Button(Rect(0, 0, 0, 0), "Back");
	}
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void specialCallback(int key, int x, int y) override;
	void mouseCallback(int btn, int state, int x, int y) override;
	void reshpeCallback(int width, int height) override;
	int getType() override;
	void setExpressions(Expression* expression) {
		rangeW = 3;
		rangeH = 3;
		this->expression = expression;
	}
	bool isBackBtnClicked() {
		if (backBtnClicked) {
			backBtnClicked = false;
			return true;
		}
		return false;
	}

};



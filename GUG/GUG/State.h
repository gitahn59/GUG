#pragma once

#include "Control.h"
#include "MathExpression.h"
/*
interface class
*/
class IState
{
public:
	int width;
	int height;
	virtual void displayCallback() = 0;
	virtual void keyboardCallback(unsigned char key, int state, int x, int y) = 0;
	virtual void specialCallback(int key, int x, int y) = 0;
	virtual void mouseCallback(int btn, int state, int x, int y) = 0;
	virtual void reshpeCallback(int x, int y) = 0;
	virtual int getType() = 0;
};

class VaribleSelection : public IState {
public:
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void specialCallback(int key, int x, int y) override {}
	void mouseCallback(int btn, int state, int x, int y) override;
	void reshpeCallback(int width, int height) override;
	int getType() override;
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

class OperationSetting : public IState {
public:
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void specialCallback(int key, int x, int y) override {}
	void mouseCallback(int btn, int state, int x, int y) override;
	void reshpeCallback(int width, int height) override;
	int getType() override;
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



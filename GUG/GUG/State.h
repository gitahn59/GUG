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
	//virtual void specialCallback(int key, int x, int y) = 0;
	virtual void mouseCallback(int btn, int state, int x, int y) = 0;
	virtual void reshpeCallback(int x, int y) = 0;
	virtual int getType() = 0;
};

class VaribleSelection : public IState {
public:
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
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
	void mouseCallback(int btn, int state, int x, int y) override;
	void reshpeCallback(int width, int height) override;
	int getType() override;
	void setControlsPosition(int width, int height);
	vector<MathExpression*> getExpression();
	bool isNextBtnClicked() {
		if (nextBtnClicked) {
			nextBtnClicked = false;
			return true;
		}
		return false;
	}
};

class OperationSetting : public IState {
public:
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void mouseCallback(int btn, int state, int x, int y) override;
	void reshpeCallback(int width, int height) override;
	int getType() override;
};

class GraphDrawing : public IState {
public:
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void mouseCallback(int btn, int state, int x, int y) override;
	void reshpeCallback(int width, int height) override;
	int getType() override;
};



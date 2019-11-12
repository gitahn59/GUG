#pragma once

/*
interface class
*/
class IState
{
public:
	virtual void displayCallback() = 0;
	virtual void keyboardCallback(unsigned char key, int state, int x, int y) = 0;
	virtual void mouseCallback(int btn, int state, int x, int y) = 0;
	virtual int getType() = 0;
};

class VaribleSelection : public IState {
public:
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void mouseCallback(int btn, int state, int x, int y) override;
	int getType() override;
};

class Equation : public IState {
public:
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void mouseCallback(int btn, int state, int x, int y) override;
	int getType() override;
};

class OperationSetting : public IState {
public:
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void mouseCallback(int btn, int state, int x, int y) override;
	int getType() override;
};

class GraphDrawing : public IState {
public:
	void displayCallback() override;
	void keyboardCallback(unsigned char key, int state, int x, int y) override;
	void mouseCallback(int btn, int state, int x, int y) override;
	int getType() override;
};



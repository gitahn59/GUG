#pragma once

/*
interface class
*/
#include <string>

using namespace std;

class IControl
{
public:
	virtual void draw() = 0;
	virtual bool isHover(int x,int y) = 0;
};

class Rect {
private:
	int x;
	int y;
	int width;
	int height;
public:
	Rect() {}
	Rect(int x, int y, int width, int height);
	bool isIn(int x,int y);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
};

class Button : public IControl {
private:
		Rect area;
		string text;
public:
	Button() {}
	Button(Rect area,string text);
	void draw() override;
	bool isHover(int x, int y) override;
	void setArea(Rect area);
	string toString();
	void setText(string text);
};

class TextBox : public IControl {
private:
	Rect area;
public:
	TextBox() {}
	TextBox(Rect area);
	void draw() override;
	bool isHover(int x, int y) override;
	void setArea(Rect area);
};


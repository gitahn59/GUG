#pragma once

/*
interface class
*/
class IControl
{
public:
	virtual void draw() = 0;
	virtual bool isHover(int x,int y) = 0;
};

class Rectangle {
private:
	int x;
	int y;
	int width;
	int height;
public:
	Rectangle() {}
	Rectangle(int x, int y, int width, int height);
	bool isIn(int x,int y);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
};

class Button : public IControl {
private:
		Rectangle area;
public:
	Button() {}
	Button(Rectangle area);
	void draw() override;
	bool isHover(int x, int y) override;
	void setArea(Rectangle area);
};

class TextBox : public IControl {
private:
	Rectangle area;
public:
	TextBox() {}
	TextBox(Rectangle area);
	void draw() override;
	bool isHover(int x, int y) override;
	void setArea(Rectangle area);
};


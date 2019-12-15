/*
============================================================================
Name        : Control.h
Version     : 1.0
Copyright   : MIT
Description : Control에 대한 헤더파일
사용자의 컨트롤의 interface IControl을 정의하고 이를 상속하는 Button, TextBox를 선언한다.
구성 클래스
IControl, Button, TextBox
============================================================================
*/

#pragma once
#include <string>
#include <glut.h>

using namespace std;

struct Vertex {
	// GL_T2F_V3F
	float tu, tv;
	float x, y, z;
};

class IControl
{
public:
	virtual void draw() = 0;
	virtual bool isHover(int x,int y) = 0;
	void drawStringAtCenter(float width, float y, float z, string s);
	void drawStringAtRight(float width, float y, float z, string s);
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
	int getX() { return x; }
	int getY() { return y; }
	int getWidth() { return width; }
	int getHeight() { return height; }
};

class Button : public IControl {
private:
		Rect area;
		string text;
		string printedText;
		bool hovered;
		float center[3];
public:
	Button() {}
	Button(Rect area,string text);
	void draw() override;
	void drawLight();
	void drawTriangleTexture(GLuint id);
	void drawQuadsTexture(GLuint id);
	bool isHover(int x, int y) override;
	void setArea(Rect area);
	string toString();
	void setText(string text) {
		this->text = text;
		setPrintedText(text);
	}

	void setPrintedText(string text) {
		printedText = text;
		center[0] = -(printedText.length() * 0.075);
		center[1] = -0.05;
		center[2] = -0.3;
	}
	string getPrintedText(string text) {
		return printedText;
	}
	void setCenter(float x, float y, float z) {
		center[0] = x;
		center[1] = y;
		center[2] = z;
	}
	
	void setIsHover() {
		hovered = true;
	}
	bool getIsHover() {
		return hovered;
	}
};

class TextBox : public IControl {
private:
	Rect area;
public:
	TextBox() {}
	TextBox(Rect area) {
		this->area = area;
	}
	void draw() override {};
	void draw(string expression);
	bool isHover(int x, int y) override;
	void setArea(Rect area) {
		this->area = area;
	}
};


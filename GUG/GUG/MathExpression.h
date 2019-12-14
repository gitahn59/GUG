/*
============================================================================
Name        : MathExpression.h
Author      : gitahn59
Version     : 1.0
Copyright   : MIT
Description : ���� ���� Ŭ������ �����Ѵ�.
               string���� �ۼ��� ������ ����ǥ������� ��ȯ�Ͽ� ����ϰ�
               ���� �� ����� vector�� ��ȯ�Ͽ� �����Ѵ�.
			   Node, OP. Operand, Operator, Expression
============================================================================
*/

#pragma once
#include <cmath>
#include <stack>
#include <vector>
#include <string>

using namespace std;

class Node{
private:
public:
	float x, y;
	Node(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

class OP {
public:
	virtual bool isOperator() = 0;
};

enum op {
	OP_PLUS, OP_MINUS, OP_DEVIDE, OP_MULTIPLE, OP_LEFT_BRACKET, OP_RIGHT_BRACKET
};

enum oprd {
	OP_SIN, OP_COS, OP_TAN, OP_ROOT, OP_LOG, OP_EXPONENTIATION, OP_NUMBER
};

class Operand :public OP {
private:
	double a=0, b=0;
	enum oprd type;
	bool usingX;

public:
	//number, sin, cos, tan ������
	Operand(enum oprd type, double a);

	//root a(root(b)), logab, exponentiation(b^a)
	Operand(enum oprd type, double a, double b);

	// x�� ����ϴ� NUMBER, SIN, COS, TAN
	Operand(bool usingX, enum oprd type);

	//root a(root(b)), logab, exponentiation(b^a)
	Operand(bool usingX, enum oprd type, double a);

	double getValue(double x);

	bool isOperator() override;
};

class Operator :public OP {
private:
	enum op type = OP_PLUS;
	int priority = 0;
public:
	Operator(enum op type);
	bool isOperator() override { return true; }
	int getPriority() { return priority; }
	enum op getType() { return type; }
};

class Expression {
private:
	vector<OP*> inorderExpression;
	vector<OP*> postorderExpression;

	void inToPost();
	Operand* stringToOperand(string s);
public:
	Expression() {}
	Expression(string exp);
	~Expression();
	vector<Node> calculate(float start, float end, float interver);
};
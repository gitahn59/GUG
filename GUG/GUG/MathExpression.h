#pragma once

#include <cmath>
#include <stack>
#include <vector>

using namespace std;

class MathExpression {
public:
	virtual bool isOperator() = 0;
	static vector<MathExpression*> postOrder(vector<MathExpression*> ve);
};

enum op {
	OP_PLUS, OP_MINUS, OP_DEVIDE, OP_MULTIPLE, OP_LEFT_BRACKET, OP_RIGHT_BRACKET
};

enum oprd {
	OP_SIN, OP_COS, OP_TAN, OP_ROOT, OP_LOG, OP_EXPONENTIATION, OP_NUMBER
};

class Operand :public MathExpression {
private:
	double a=0, b=0;
	enum oprd type;
	bool usingX;

public:
	//number, sin, cos, tan 고정값
	Operand(enum oprd type, double a);

	//root a(root(b)), logab, exponentiation(b^a)
	Operand(enum oprd type, double a, double b);

	// x를 사용하는 NUMBER, SIN, COS, TAN
	Operand(enum oprd type, bool usingX);

	//root a(root(b)), logab, exponentiation(b^a)
	Operand(enum oprd type, bool usingX, double a);

	double getValue(double x);

	bool isOperator() override;
};

class Operator :public MathExpression {
private:
	enum op type = OP_PLUS;
	int priority = 0;
public:
	Operator(enum op type);
	bool isOperator() override;
	int getPriority();
	enum op getType();
};


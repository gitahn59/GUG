#include "MathExpression.h"
#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
#include <float.h>

using namespace std;

//number, sin, cos, tan, log,고정값
Operand::Operand(enum oprd type, double a) {
	this->type = type;
	this->a = a;
	usingX = false;
}

//root a(root(b)), exponentiation(b^a)
Operand::Operand(enum oprd type, double a, double b) {
	this->type = type;
	this->a = a;
	this->b = b;
	usingX = false;
}

// x를 사용하는 NUMBER, SIN, COS, TAN, log
Operand::Operand(bool usingX,enum oprd type ) {
	this->type = type;
	usingX = true;
}

//x를 사용하는 root a(root(b)), exponentiation(b^a)
Operand::Operand(bool usingX,enum oprd type, double a) {
	this->type = type;
	this->a = a;
	usingX = true;
}

double Operand::getValue(double x) {
	switch (type) {
	case OP_NUMBER:
		if (usingX)
			return x;
		return a;
	case OP_SIN:
		if (usingX)
			return sin(x);
		return sin(a);
	case OP_COS:
		if (usingX)
			return cos(x);
		return cos(a);
	case OP_TAN:
		if (usingX)
			return tan(x);
		return tan(a);
	case OP_EXPONENTIATION:
		if (usingX)
			return pow(x, a);
		return pow(b,a);
	case OP_LOG:
		if (usingX)
			return log(x);
		return log(a);
	case OP_ROOT:
		if (usingX)
			return sqrt(x);
		return sqrt(a);
	}
}

bool Operand::isOperator() {
	return false;
}

Operator::Operator(enum op type) {
	this->type = type;
	switch (type) {
	case OP_LEFT_BRACKET:
		priority = 0;
		break;
	case OP_PLUS:
	case OP_MINUS:
		priority = 1;
		break;
	case OP_MULTIPLE:
	case OP_DEVIDE:
		priority = 2;
	}

}

bool Operator::isOperator(){
	return true;
}

int Operator::getPriority() {
	return priority;
}

enum op Operator::getType() {
	return type;
}

Operand* Expression::stringToOperand(string s) {
	if (s == "X") {
		return new Operand(true, OP_NUMBER);
	}

	try {
		if (s == "sX") {
			return new Operand(true, OP_SIN);
		}
		else if (s == "cX") {
			return new Operand(true, OP_COS);
		}
		else if (s == "tX") {
			return new Operand(true, OP_TAN);
		}
		else if (s == "lX") {
			return new Operand(true, OP_LOG);
		}
		else if (s == "rX") {
			return new Operand(true, OP_ROOT);
		}

		if (s.length() >= 2)
			switch (s[0]) {
			case 's':
				return new Operand(OP_SIN, stof(s.substr(1, s.length() - 1)));
			case 'c':
				return new Operand(OP_COS, stof(s.substr(1, s.length() - 1)));
			case 't':
				return new Operand(OP_TAN, stof(s.substr(1, s.length() - 1)));
			case 'l':
				return new Operand(OP_LOG, stof(s.substr(1, s.length() - 1)));
			case 'r':
				return new Operand(OP_ROOT, stof(s.substr(1, s.length() - 1)));
			case 'X':
				if (s[1] == '^') {
					return new Operand(true, OP_EXPONENTIATION, stof(s.substr(2, s.length() - 2)));
				}
			}
		return new Operand(OP_NUMBER, stof(s));
	}
	catch (std::invalid_argument ia) {
		return new Operand(OP_NUMBER, 0.0);
	}
}

void Expression::inToPost() {
	int len = inorderExpression.size();
	stack<Operator*> so;
	for (int i = 0; i < len; i++) {
		//연산자인 경우
		if (inorderExpression[i]->isOperator()) {
			Operator* p = (Operator*)inorderExpression[i];
			//왼쪽 괄호인 경우
			if (p->getType() == OP_LEFT_BRACKET) {
				so.push(p);
				continue;
			}
			//오른쪽 괄호인 경우
			else if (p->getType() == OP_RIGHT_BRACKET) {
				while (so.top()->getType() != OP_LEFT_BRACKET) {
					postorderExpression.push_back(so.top());
					so.pop();
				}
				so.pop();
				continue;
			}

			if (so.empty()) {
				so.push(p);
			}
			else {
				//우선순위가 높으면 그냥 스택에 push
				if (so.top()->getPriority() < p->getPriority()) {
					so.push(p);
				}
				//낮으면 스택에 있는 연산자를 pop하고 push
				else {
					postorderExpression.push_back(so.top());
					so.pop();
					so.push(p);
				}
			}
		}
		//피연산자
		else {
			postorderExpression.push_back(inorderExpression[i]);
		}

	}

	while (!so.empty()) {
		postorderExpression.push_back(so.top());
		so.pop();
	}
}

Expression::Expression(string expression) {
	int len = expression.length();
	std::string s = expression;

	vector<string> voperand;
	vector<char> voperator;

	int pos = 0;
	for (int i = 0; i < len; i++) {
		string temp = "";
		if (s[i] == '/' || s[i] == '*' || s[i] == '+' ||
			s[i] == '-' || s[i] == '(' || s[i] == ')') {
			temp = s.substr(pos, i-pos);
			if (temp != "") {
				inorderExpression.push_back(stringToOperand(temp));
			}
			pos = i + 1;
		}
		switch (s[i]) {
		case '/':
			inorderExpression.push_back(new Operator(OP_DEVIDE));
			break;
		case '*':
			inorderExpression.push_back(new Operator(OP_MULTIPLE));
			break;
		case '+':
			inorderExpression.push_back(new Operator(OP_PLUS));
			break;
		case '-':
			inorderExpression.push_back(new Operator(OP_MINUS));
			break;
		case '(':
			inorderExpression.push_back(new Operator(OP_LEFT_BRACKET));
			break;
		case ')':
			inorderExpression.push_back(new Operator(OP_RIGHT_BRACKET));
			break;
		}
	}
	string temp = s.substr(pos, len);
	if (temp != "")
		inorderExpression.push_back(stringToOperand(temp));

	inToPost();
}

Expression::~Expression() {
	for (int i = 0; i < inorderExpression.size(); i++) {
		free(inorderExpression[i]);
	}
}

float arithmetic(float a, float b, enum op operation,bool *flag) {
	switch (operation) {
	case OP_PLUS:
		return a + b;
	case OP_MINUS:
		return a - b;
	case OP_MULTIPLE:
		return a * b;
	case OP_DEVIDE:
		if (abs(b)<= 0.00001) {
			*flag = false;
			return 0;
		}
		return a / b;
	}
	return 0;
}

vector<bff> Expression::calculate(float start, float end, float interver) {
	vector<bff> vbff;
	int len = postorderExpression.size();
	for (start; start <= end; start += interver) {
		stack<float> soperand;
		bool flag = true;
		for (int i = 0; i < len; i++) {
			if (postorderExpression[i]->isOperator()) {
				Operator* op = (Operator*)postorderExpression[i];
				if (soperand.empty())
					break;
				float b = soperand.top();
				soperand.pop();
				if (soperand.empty())
					break;
				float a = soperand.top();
				soperand.pop();

				soperand.push(arithmetic(a, b, op->getType(), &flag));
				if (!flag)
					break;
			}
			else {
				soperand.push(((Operand*)postorderExpression[i])->getValue(start));
			}
		}
		if(!soperand.empty())
			vbff.push_back(make_pair(flag,make_pair(start, soperand.top())));
	}
	return vbff;
}

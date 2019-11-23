#include "MathExpression.h"
#include <string>

using namespace std;

vector<MathExpression*> MathExpression::postOrder(vector<MathExpression*> ve) {
	int len = ve.size();
	vector<MathExpression*> post;
	stack<Operator*> so;

	for (int i = 0; i < len; i++) {
		//�������� ���
		if (ve[i]->isOperator()) {
			Operator* p = (Operator*)ve[i];
			//���� ��ȣ�� ���
			if (p->getType() == OP_LEFT_BRACKET) {
				so.push(p);
				continue;
			}
			//������ ��ȣ�� ���
			else if (p->getType() == OP_RIGHT_BRACKET) {
				while (so.top()->getType() != OP_LEFT_BRACKET) {
					post.push_back(so.top());
					so.pop();
				}
				so.pop();
				continue;
			}

			if (so.empty()) {
				so.push(p);
			}
			else {
				//�켱������ ������ �׳� ���ÿ� push
				if (so.top()->getPriority() < p->getPriority()) {
					so.push(p);
				}
				//������ ���ÿ� �ִ� �����ڸ� pop�ϰ� push
				else {
					post.push_back(so.top());
					so.pop();
					so.push(p);
				}
			}
		}
		//�ǿ�����
		else {
			post.push_back(ve[i]);
		}

	}

	while (!so.empty()) {
		post.push_back(so.top());
		so.pop();
	}

	return post;
}



//number, sin, cos, tan, log,������
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

// x�� ����ϴ� NUMBER, SIN, COS, TAN, log
Operand::Operand(bool usingX,enum oprd type ) {
	this->type = type;
	usingX = true;
}

//x�� ����ϴ� root a(root(b)), exponentiation(b^a)
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
		return a;
	case OP_COS:
		if (usingX)
			return cos(x);
		return a;
	case OP_TAN:
		if (usingX)
			return tan(x);
		return a;
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
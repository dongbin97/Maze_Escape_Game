#include "pointer.h"

POINTER::POINTER() { //������
};

void POINTER::getnum(int value) { //value�� �Է¹޾� ��� ���� data�� �����ϴ� �Լ�
	this->data = value;
}

int POINTER::num() { //������� data�� ���� ��ȯ�ϴ� �Լ�
	return this->data;
}
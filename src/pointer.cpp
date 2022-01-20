#include "pointer.h"

POINTER::POINTER() { //생성자
};

void POINTER::getnum(int value) { //value를 입력받아 멤버 변수 data에 저장하는 함수
	this->data = value;
}

int POINTER::num() { //멤버변수 data의 값을 반환하는 함수
	return this->data;
}
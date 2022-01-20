#ifndef __POINTER__
#define __POINTER__

class POINTER { //미로에서 움직이는 각 점을 의미하는 클래스 POINTER 정의
protected:
	int data; //멤버변수로서는 미로에서의 위치를 의미하는 data를 가짐
public:
	POINTER(); //생성자

	void getnum(int value); //value를 입력받아 멤버 변수 data에 저장하는 함수
	int num();//멤버변수 data의 값을 반환하는 함수

};

#endif
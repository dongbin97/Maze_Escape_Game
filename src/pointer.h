#ifndef __POINTER__
#define __POINTER__

class POINTER { //�̷ο��� �����̴� �� ���� �ǹ��ϴ� Ŭ���� POINTER ����
protected:
	int data; //��������μ��� �̷ο����� ��ġ�� �ǹ��ϴ� data�� ����
public:
	POINTER(); //������

	void getnum(int value); //value�� �Է¹޾� ��� ���� data�� �����ϴ� �Լ�
	int num();//������� data�� ���� ��ȯ�ϴ� �Լ�

};

#endif
#pragma once

#include "ofMain.h"
#include "pointer.h"
#include <string.h>

typedef struct maze { //�̷��� ������ ������ ����ü
	short int up; //�̷��� ����ĭ���� ���� ���� �շ��ִٸ� 1 ���������� 0
	short int down; //�̷��� ����ĭ���� �Ʒ��� ���� �շ��ִٸ� 1 ���������� 0
	short int right; //�̷��� ����ĭ���� ������ ���� �շ��ִٸ� 1 ���������� 0
	short int left; //�̷��� ����ĭ���� ���� ���� �շ��ִٸ� 1 ���������� 0
}maze;

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key); 
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		/////////////////////////////////////////////

		float windowWidth; //windowâ�� �ʺ�
		float windowHeight; //windowâ�� ����
		ofTrueTypeFont myFont; //���α׷� ������ �޽����� ����ϱ� ���� ����

		int stageNo; //���� stage�� ��Ÿ���� ����(1~5)

		int isOpen; //������ ���ȴ����� �Ǵ��ϴ� flag, 0: �ȿ��� 1: ����
		int isStart; //���������� ���� flag, 0: �������� ���� 1: ����
		int isGoal; //�������� ȭ�鿡 �׷����� ������ �����ϴ� flag, 0: �׷����� ���� 1: �׷���
		int isAttack; //attack�� ���������� ���� flag, 0: �������� ���� 1: ����
		int isHint; //hint�� ȭ�鿡 �׷����� ������ �����ϴ� flag, 0: �׷����� ���� 1: �׷���
		int isMeet; //point�� hint�� ���������� �˷��ִ� flag, 0: ������ ���� 1: ����
		int isPause; //pause�� ������� ������ �ǹ��ϴ� flag, 0: �������� ���� 1: ������
		int isClear; // game clear������ ���� flag, 0: clear�� ���°� �ƴ� 1: clear�� ����
		int isGameOver; // game over������ ���� flag, 0: game over�ƴ� ���� 1: game over�� ����

		bool readFile(); //.maz������ �а� �̷��� ������ �迭 m�� �����ϴ� �Լ�
		maze *m; //�̷��� ������ ���� 1���� �迭
		int height; //�̷��� ���̸� ��Ÿ���� ����
		int width; //�̷��� �ʺ� ��Ÿ���� ����
		float startX; //�̷θ� �׸��� �����ϴ� x��ǥ
		float startY; //�̷θ� �׸��� �����ϴ� y��ǥ
		float size; //�̷� �� ĭ�� ũ�⸦ ��Ÿ���� ����

		POINTER point; //Ű����� control�� point�� ��Ÿ���� ����
		float pointX; //point�� x��ǥ
		float pointY; //point�� y��ǥ
		float radius;//pointer�� �������� ��Ÿ���� ����
		int cur; //���� point�� ��ȣ�� ��Ÿ���� ����

		POINTER *attacker; //�����Ӱ� ������ attacker���� �迭
		float *attackerX; //attacker���� x��ǥ�� ��Ÿ���� �迭
		float *attackerY; //attacker���� y��ǥ�� ��Ÿ���� �迭
		int attackNo; //attacker�� ������ ��Ÿ���� ����
		void Set_Attack(); //attacker�� ������ ��ġ�� �ʱ�ȭ�� �Լ�
		void Move_Attack(); //attacker�� �����̰� �� �Լ�
		

		POINTER* hint; //play�� ������ �� hint�迭
		float* hintX; //hint���� x��ǥ�� ��Ÿ���� �迭
		float* hintY; //hint���� y��ǥ�� ��Ÿ���� �迭
		int hintNo; //hint�� ������ ��Ÿ���� ����
		void Set_Hint(); //hint�� ������ ��ġ�� �ʱ�ȭ�� �Լ�
		int Check_Same(int num); //point�� attacker�� ��ġ�� hint�� ������ ���θ� �Ǻ��ϴ� �Լ�
		void Meet_Hint(); //point�� hint�� ������ �� ������ ��Ÿ���� �Լ�
		float meetX; //point�� ���� hint�� x��ǥ
		float meetY; //point�� ���� hint�� y��ǥ
		
		void explosion(float x, float y); //point�� attacker�� hint, �������� ������ �� (x,y)��ǥ���� �ð����� ȿ���� �ִ� �Լ�

		void freeMemory(); //�Ҵ�� �޸𸮸� �������ִ� �Լ�
		void reset(); //��� flag���� �ʱ�ȭ �ϰ� �޸𸮸� �����ϴ� �Լ�

};

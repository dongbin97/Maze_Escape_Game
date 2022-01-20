#pragma once

#include "ofMain.h"
#include "pointer.h"
#include <string.h>

typedef struct maze { //미로의 구조를 저장할 구조체
	short int up; //미로의 현재칸에서 위쪽 벽이 뚫려있다면 1 막혀있으면 0
	short int down; //미로의 현재칸에서 아래쪽 벽이 뚫려있다면 1 막혀있으면 0
	short int right; //미로의 현재칸에서 오른쪽 벽이 뚫려있다면 1 막혀있으면 0
	short int left; //미로의 현재칸에서 왼쪽 벽이 뚫려있다면 1 막혀있으면 0
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

		float windowWidth; //window창의 너비
		float windowHeight; //window창의 높이
		ofTrueTypeFont myFont; //프로그램 내에서 메시지를 출력하기 위한 변수

		int stageNo; //현재 stage를 나타내는 변수(1~5)

		int isOpen; //파일이 열렸는지를 판단하는 flag, 0: 안열림 1: 열림
		int isStart; //시작할지에 대한 flag, 0: 시작하지 않음 1: 시작
		int isGoal; //도착점을 화면에 그려줄지 말지를 결정하는 flag, 0: 그려주지 않음 1: 그려줌
		int isAttack; //attack을 시작할지에 대한 flag, 0: 시작하지 않음 1: 시작
		int isHint; //hint를 화면에 그려줄지 말지를 결정하는 flag, 0: 그려주지 않음 1: 그려줌
		int isMeet; //point가 hint와 만났는지를 알려주는 flag, 0: 만나지 않음 1: 만남
		int isPause; //pause가 실행될지 말지를 의미하는 flag, 0: 중지하지 않음 1: 중지함
		int isClear; // game clear인지에 대한 flag, 0: clear된 상태가 아님 1: clear된 상태
		int isGameOver; // game over인지에 대한 flag, 0: game over아닌 상태 1: game over된 상태

		bool readFile(); //.maz파일을 읽고 미로의 구조를 배열 m에 저장하는 함수
		maze *m; //미로의 구조를 담을 1차원 배열
		int height; //미로의 높이를 나타내는 변수
		int width; //미로의 너비를 나타내는 변수
		float startX; //미로를 그리기 시작하는 x좌표
		float startY; //미로를 그리기 시작하는 y좌표
		float size; //미로 한 칸의 크기를 나타내는 변수

		POINTER point; //키보드로 control할 point를 나타내는 변수
		float pointX; //point의 x좌표
		float pointY; //point의 y좌표
		float radius;//pointer의 반지름을 나타내는 변수
		int cur; //현재 point의 번호를 나타내는 변수

		POINTER *attacker; //자유롭게 움직일 attacker들의 배열
		float *attackerX; //attacker들의 x좌표를 나타내는 배열
		float *attackerY; //attacker들의 y좌표를 나타내는 배열
		int attackNo; //attacker의 개수를 나타내는 변수
		void Set_Attack(); //attacker의 개수와 위치를 초기화할 함수
		void Move_Attack(); //attacker를 움직이게 할 함수
		

		POINTER* hint; //play에 도움이 될 hint배열
		float* hintX; //hint들의 x좌표를 나타내는 배열
		float* hintY; //hint들의 y좌표를 나타내는 배열
		int hintNo; //hint의 개수를 나타내는 변수
		void Set_Hint(); //hint의 개수와 위치를 초기화할 함수
		int Check_Same(int num); //point나 attacker의 위치가 hint와 같은지 여부를 판별하는 함수
		void Meet_Hint(); //point가 hint를 만났을 때 동작을 나타내는 함수
		float meetX; //point와 만난 hint의 x좌표
		float meetY; //point와 만난 hint의 y좌표
		
		void explosion(float x, float y); //point가 attacker나 hint, 도착점을 만났을 때 (x,y)좌표에서 시각적인 효과를 주는 함수

		void freeMemory(); //할당된 메모리를 해제해주는 함수
		void reset(); //모든 flag들을 초기화 하고 메모리를 해제하는 함수

};

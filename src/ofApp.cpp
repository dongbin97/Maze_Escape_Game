#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	//window창에 대한 기본 설정
	ofSetWindowTitle("FINAL PROJECT"); // window창 상단에 title을 적어줌
	ofSetFrameRate(4); //1초에 4번 움직이도록 설정 attacker가 너무 빠르게 움직이는 것을 방지하기 위함
	ofBackground(255, 255, 255); //window화면을 배경을 흰색으로 설정
	windowWidth = ofGetWidth(); //window창의 너비를 구해 windowWidth변수에 저장
	windowHeight = ofGetHeight();  //window창의 높이를 구해 windowWidth변수에 저장
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2); //window창을 컴퓨터 화면의 중앙에 나타나게 함
	
	//프로그램에 필요한 flag들 초기화
	stageNo = 1; //처음 stage는 1단계를 의미함
	isOpen = 0; //아직 파일이 open되지 않았음을 의미함
	isStart = 0; //아직 게임을 시작하지 않음을 의미함
	isGoal = 0; //아직 도착점을 그려주지 않음을 의미함
	isAttack = 0; //아직 attacker들을 그려주지 않음을 의미함
	isHint = 0; //아직 hint들을 그려주지 않음을 의미함
	isMeet = 0; //아직 hint와 pointer가 만나지 않았음을 의미함
	isPause = 0; //아직 프로그램이 중단하라는 명령이 없음을 의미함
	isClear = 0; //아직 stage를 clear하지 않았음을 의미함
	isGameOver = 0; //아직 game over가 이루어지지 않았음을 의미함
	
	myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"폰트를 크기 20으로 load함

	point.getnum(0); //point의 처음 위치는 미로의 (0,0)칸임을 의미함

} // end Setup

//--------------------------------------------------------------
void ofApp::update() {
	//게임이 진행되는 동안(isAttack은 1이여야 하고, stage clear, game over, pause가 아닌 상황에서만 아래가 작동함)
	if (isAttack == 1 && isClear == 0 && isGameOver == 0 && isPause == 0) {
		Move_Attack(); //attacker들의 움직임을 표현해 줄 함수
		Meet_Hint(); //point와 hint가 만났을 경우 처리를 해주는 함수
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	char str[256]; //화면에 출력할 메시지를 저장할 문자열
	ofSetColor(50); //미로의 벽을 그려줄 선의 색을 회색으로 설정
	ofSetLineWidth(3); //미로의 벽을 의미하는 선의 폭은 3으로 설정

	int i; //반복문을 실행하기 위한 변수

	if (isOpen) { //파일이 open된 경우 아래를 수행한다
		//window창의 크기에 미로의 크기를 맞추어 그려주기 위해 더 작은 값을 미로 한칸의 크기로 설정
		size = ((windowWidth-80)/width > (windowHeight-80)/height) ? (windowHeight - 80) /height : (windowWidth - 80) /width;
		//위에서 구한 size를 이용해 미로를 그려주기 시작할 x좌표, y좌표를 설정
		startX = (windowWidth-size*width)/2, startY = (windowHeight-size*height)/2.5;

		//미로의 큰 테두리 벽을 선을 이용해 그려준다
		ofDrawLine(startX, startY, startX + size * width, startY);
		ofDrawLine(startX, startY, startX, startY + size * height);
		ofDrawLine(startX + size * width, startY, startX + size * width, startY + size * height);
		ofDrawLine(startX, startY + size * height, startX + size * width, startY + size * height);

		//미로 내부의 벽을 그려준다
		//현재칸의 오른쪽 벽과 오른쪽 칸의 왼쪽 벽, 현재칸의 아래쪽 벽과 아래쪽 칸의 위쪽 벽이 겹침을 이용하여
		//각 미로의 칸에서 오른쪽 벽과 아래쪽 벽의 유무를 확인하여 미로의 벽을 그려준다
		for (i = 0; i < width * height; i++) {
			if (m[i].right == 0) { //현재칸의 오른쪽 벽이 있으면 미로의 벽을 그려준다
				ofDrawLine(startX + size * (i % width + 1), startY + size * (i / width), startX + size * (i % width + 1), startY + size * (i / width + 1));
			}
			if (m[i].down == 0) { //현재칸의 아래쪽 벽이 있으면 미로의 벽을 그려준다
				ofDrawLine(startX + size * (i % width), startY + size * (i / width + 1), startX + size * (i % width + 1), startY + size * (i / width + 1));
			}
		}
		
		if (isStart) { //start명령이 들어와서 isStart flag가 1이 되면
			//point를 하늘색 원으로 그려준다
			ofSetColor(135, 206, 250); //light sky blue색으로 설정
			radius = size / 4; //point의 반지름은 미로 한 칸의 1/4
			pointX = startX + size / 2 + size * (point.num() % width); //point의 x좌표는 현재 point의 data를 width로 나눈 나머지에 해당
			pointY = startY + size / 2 + size * (point.num() / width); //point의 y좌표는 현재 point의 data를 width로 나눈 몫에 해당
			ofDrawCircle(pointX, pointY, radius); //(pointX, pointY)위치에 반지름이 radius인 원을 그림

			if (isGoal) { //isStart가 1인 경우에 isGoal flag가 1이 되면 
				ofSetColor(152, 251, 152); //pale green 색으로 설정
				//도착점 (width-1,height-1) 지점에 사각형으로 도착점을 그려줌
				ofDrawRectangle(startX + size / 4 + size * ((width * height - 1) % width), startY + size / 4 + size * ((width * height - 1) / width), size / 2, size / 2);
			}
		}

		if (isAttack) { //isAttack flag가 1이 되면
			
			ofSetColor(255, 0, 0); //red색으로 설정
			radius = size / 4; //attacker의 반지름은 미로 한 칸의 1/4
			for (i = 0; i < attackNo; i++) { //모든 attacker들의 위치를 원으로 그려줌
				attackerX[i] = startX + size / 2 + size * (attacker[i].num() % width); //attacker의 x좌표는 현재 attacker의 data를 width로 나눈 나머지에 해당
				attackerY[i] = startY + size / 2 + size * (attacker[i].num() / width); //attacker의 y좌표는 현재 attacker의 data를 width로 나눈 몫에 해당
				ofDrawCircle(attackerX[i], attackerY[i], radius); //(attackerX, attackerY)위치에 반지름이 radius인 원을 그림
			}
		}

		if (isHint) { //isHint flag가 1이 되면
			ofSetColor(255, 215, 0); //gold색으로 설정
			radius = size / 4; //hint의 반지름은 미로 한 칸의 1/4
			for (i = 0; i < hintNo; i++) { //모든 hint들의 위치를 원으로 그려줌
				if (hint[i].num() > 0) { //이미 point와 만난 hint는 Meet_Hint()함수에 의해 음수값의 data를 가지게 되고 그려주지 않음
					hintX[i] = startX + size / 2 + size * (hint[i].num() % width); //hint의 x좌표는 현재 hint의 data를 width로 나눈 나머지에 해당
					hintY[i] = startY + size / 2 + size * (hint[i].num() / width); //hint의 x좌표는 현재 hint의 data를 width로 나눈 몫에 해당
					ofDrawCircle(hintX[i], hintY[i], radius); //(hintX, hintY)위치에 반지름이 radius인 원을 그림
				}
			}
		}

		if (isMeet) { //isMeet flag가 1이 되면; point가 hint중 하나와 만나면
			ofSetColor(255, 215,0); //gold색으로 설정
			explosion(meetX,meetY); //point가 hint를 만났을 때, 효과를 화면에 그려줌
			ofSetColor(255, 0, 0); //red색으로 설정
			explosion(attackerX[attackNo - 1], attackerY[attackNo - 1]); //point가 hint를 만났을 때, attacker가 하나 사라지는 효과를 화면에 그려줌
			attackNo--; //attacker의 개수를 하나 줄인다
			isMeet = 0; //다시 isMeet을 0으로 설정해준다
		}

		if (isPause) { //isPause flag가 1이 되면; 중지 명령이 들어오면
			ofSetColor(255, 255, 255); //white색으로 설정
			ofDrawRectangle(windowWidth / 6, windowHeight / 4, windowWidth * 4 / 6, windowHeight * 2 / 4); //메시지 창을 나타낼 직사각형을 그림
			ofSetColor(152, 251, 152); //pale green색으로 설정
			//메시지 창의 테두리를 선으로 그려준다 
			ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth * 5 / 6, windowHeight / 4);
			ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth / 6, windowHeight * 3 / 4);
			ofDrawLine(windowWidth * 5 / 6, windowHeight / 4, windowWidth * 5 / 6, windowHeight * 3 / 4);
			ofDrawLine(windowWidth / 6, windowHeight * 3 / 4, windowWidth * 5 / 6, windowHeight * 3 / 4);
			ofSetColor(0); //black색으로 설정
			myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"폰트를 크기 20으로 load함
			strcpy(str, "PAUSE"); //str에 메시지를 복사함
			myFont.drawString(str, windowWidth / 2.4, windowHeight / 2.5); //설정해준 위치에 str의 내용을 출력한다
			myFont.loadFont("verdana.ttf", 12, true, true); //"verdana.ttf"폰트를 크기 12로 load함
			if (stageNo < 5) { //stage가 5 미만인 경우에는 p, j 두가지 선택지가 있음
				strcpy(str, "p: Continue	j: Nest Stage"); //str에 메시지를 복사함
				myFont.drawString(str, windowWidth / 3, windowHeight / 1.6); //설정해준 위치에 str의 내용을 출력한다
			}
			else { //stage5에서는 다음 stage로 jump할 수 없으므로 p메시지만 알림
				strcpy(str, "p: Continue"); //str에 메시지를 복사함
				myFont.drawString(str, windowWidth / 2.5, windowHeight / 1.6);  //설정해준 위치에 str의 내용을 출력한다
			}
		}
	}

	if (isClear) { //isClear flag가 1이 되면; 현재 stage에서 point가 도착점에 도달하면
		isGoal = 0; //도착점을 그려주지 않도록 하고
		ofSetColor(152, ofRandom(230,255), 152); //random으로 pale green 주변의 색을 설정 
		explosion(pointX, pointY); //point가 도착점 만났을 때, 효과를 화면에 그려줌
		ofSetColor(255, 255, 255); //white색으로 설정
		ofDrawRectangle(windowWidth / 6, windowHeight / 4, windowWidth * 4 / 6, windowHeight * 2 / 4);//메시지 창을 나타낼 직사각형을 그림
		ofSetColor(65, 105, 225); //royal blue색으로 설정
		//메시지 창의 테두리를 선으로 그려준다 
		ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth*5 / 6, windowHeight / 4);
		ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth / 6 , windowHeight*3/4);
		ofDrawLine(windowWidth*5/6, windowHeight / 4, windowWidth*5/6, windowHeight*3/4);
		ofDrawLine(windowWidth / 6 , windowHeight*3/4, windowWidth*5/6, windowHeight*3/4);
		ofSetColor(0); //black색으로 설정
		if (stageNo < 5) { //stageNo가 5미만일 때는 "STAGE CLEAR"라는 메세지를 출력
			myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"폰트를 크기 20으로 load함
			strcpy(str, "STAGE CLEAR!"); //str에 메시지를 복사함
			myFont.drawString(str, windowWidth / 2.8, windowHeight / 2.5);//설정해준 위치에 str의 내용을 출력한다
			myFont.loadFont("verdana.ttf", 12, true, true); //"verdana.ttf"폰트를 크기 12으로 load함
			strcpy(str, "y: Next Stage	n: Quit");  //str에 메시지를 복사함; y,n 두가지 선택지가 있음
			myFont.drawString(str, windowWidth / 3, windowHeight / 1.6); //설정해준 위치에 str의 내용을 출력한다
		}
		else { //stageNo가 5미만일 때는 "CONGRATULATION"라는 메세지를 출력
			myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"폰트를 크기 20으로 load함
			strcpy(str, "CONGRATULATION!"); //str에 메시지를 복사함
			myFont.drawString(str, windowWidth / 3.4, windowHeight / 2.5); //설정해준 위치에 str의 내용을 출력한다
			myFont.loadFont("verdana.ttf", 12, true, true);  //"verdana.ttf"폰트를 크기 12으로 load함
			strcpy(str, "n: Quit");   //str에 메시지를 복사함; 마지막 stage이므로 선택지가 n만 있음
			myFont.drawString(str, windowWidth / 2.3, windowHeight / 1.6); //설정해준 위치에 str의 내용을 출력한다
		}
	}

	if (isGameOver) { //isClear flag가 1이 되면; point가 attacker와 만나면
		ofSetColor(ofRandom(50, 255), 0, 0); //random으로 red 주변의 색을 설정 
		explosion(pointX, pointY); //point가 attacker와 만났을 때, 효과를 화면에 그려줌
		ofSetColor(255, 255, 255);//white색으로 설정
		ofDrawRectangle(windowWidth / 6, windowHeight / 4, windowWidth * 4 / 6, windowHeight * 2 / 4);//메시지 창을 나타낼 직사각형을 그림
		ofSetColor(128, 0, 0); //maroon색으로 설정
		//메시지 창의 테두리를 선으로 그려준다 
		ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth * 5 / 6, windowHeight / 4);
		ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth / 6, windowHeight * 3 / 4);
		ofDrawLine(windowWidth * 5 / 6, windowHeight / 4, windowWidth * 5 / 6, windowHeight * 3 / 4);
		ofDrawLine(windowWidth / 6, windowHeight * 3 / 4, windowWidth * 5 / 6, windowHeight * 3 / 4);
		ofSetColor(0); //black색으로 설정
		myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"폰트를 크기 20으로 load함
		strcpy(str, "Game Over!"); //str에 메시지를 복사함
		myFont.drawString(str, windowWidth / 2.8, windowHeight / 2.5); //설정해준 위치에 str의 내용을 출력한다
		myFont.loadFont("verdana.ttf", 12, true, true);  //"verdana.ttf"폰트를 크기 12으로 load함
		strcpy(str, "r: Retry			n: Quit"); //str에 메시지를 복사함; r,n 두가지 선택지가 있음
		myFont.drawString(str, windowWidth / 3, windowHeight / 1.6); //설정해준 위치에 str의 내용을 출력한다
	}
} // end Draw

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	//키보드의 esc키를 누르면 언제든 프로그램 종료
	if(key == VK_ESCAPE) {
		freeMemory(); //할당한 메모리를 해제한다
		ofExit(); //프로그램을 종료한다
	}

	//키보드의 'd' 키를 누르면 미로구조가 그려짐 (stage1에서 게임을 시작할 때만 사용, 이외의 경우 자동적으로 그려짐) 
	if (key == 'd') { //draw
		if (isOpen == 0) { //파일이 아직 열리지 않은 경우에
			readFile(); //파일로부터 미로의 구조를 읽어 m에 저장한다.
		}
	}

	//키보드의 's' 키를 누르면 게임이 시작됨(stage1에서 게임을 시작할 때만 사용, 이외의 경우 자동적으로 시작됨)
	if (key == 's') { // start
		if (isOpen == 1 && isStart == 0) { //파일이 열렸고, 아직 게임이 시작되지 않은 경우에만 작동
			isStart = 1; //isStart flag를 1로 설정함으로써 point를 화면에 그려줌
			isGoal = 1; //isGoal flag를 1로 설정함으로써 도착점을 화면에 그려줌
			Set_Hint(); //hint들의 개수와 위치를 설정해줌
			isHint = 1; //isHint flag를 1로 설정함으로써 hint들을 화면에 그려줌
			Set_Attack(); //attacker들의 개수와 위치를 설정해줌
			isAttack = 1; //isAttack flag를 1로 설정함으로써 attacker들을 화면에 그려줌
		}
	}

	//키보드의 'r'  키를 누르면 게임이 다시 시작됨(game over 상태에서만 작동)
	if (key == 'r') { //retry
		if (isGameOver == 1) { //game over상태에서만 'r'을 눌렀을 때 작동
			reset(); //할당한 메모리를 해제하고 모든 flag를 초기화함
			readFile(); //다시 파일로부터 미로의 구조를 읽어 m에 저장한다.
			isStart = 1; //isStart flag를 1로 설정함으로써 point를 화면에 그려줌
			isGoal = 1; //isGoal flag를 1로 설정함으로써 도착점을 화면에 그려줌
			Set_Hint(); //hint들의 개수와 위치를 설정해줌
			isHint = 1;  //isHint flag를 1로 설정함으로써 hint들을 화면에 그려줌
			Set_Attack();  //attacker들의 개수와 위치를 설정해줌
			isAttack = 1; //isAttack flag를 1로 설정함으로써 attacker들을 화면에 그려줌
		}
	}

	//키보드의 'y' 키를 누르면 다음 stage의 게임이 바로 시작됨(stage clear 상태에서만 작동)
	if (key == 'y') { //yes
		if (isClear == 1 && stageNo < 5) { //stageNo가 5 미만일 때 stage clear상태에서만 작동 (stage5에서는 다음 단계가 없으므로)
			reset();  //할당한 메모리를 해제하고 모든 flag를 초기화함
			stageNo++; //stageNo를 1 증가시켜 다음 stage로 넘어감
			readFile(); //다시 파일로부터 미로의 구조를 읽어 m에 저장한다.
			isStart = 1; //isStart flag를 1로 설정함으로써 point를 화면에 그려줌
			isGoal = 1; //isGoal flag를 1로 설정함으로써 도착점을 화면에 그려줌
			Set_Hint(); //hint들의 개수와 위치를 설정해줌
			isHint = 1;  //isHint flag를 1로 설정함으로써 hint들을 화면에 그려줌
			Set_Attack(); //attacker들의 개수와 위치를 설정해줌
			isAttack = 1; //isAttack flag를 1로 설정함으로써 attacker들을 화면에 그려줌
		}
	}

	//키보드의 'n' 키를 누르면 프로그램이 종료됨 (stage clear나 game over 상태에서만 작동)
	if (key == 'n') { //no
		if (isClear == 1 || isGameOver == 1) { //stage clear나 game over 상태에서만 작동
			freeMemory(); //할당한 메모리를 해제한다
			ofExit(); //프로그램을 종료한다
		}
	}

	//키보드의 'p' 키를 누르면 프로그램이 일시정지됨 (게임이 진행중인 상황에서만 작동)
	if (key == 'p') { //pause
		if (isStart == 1 && isClear == 0 && isGameOver == 0) { //게임이 진행중인 상황에서만 작동
			if (isPause == 0) //일시정지 상태가 아니었다면
				isPause = 1; //프로그램을 일시정지 하고 메세지 창을 출력하도록 함
			else //이미 일시정지 상태였을 경우
				isPause = 0; //프로그램의 일시정지 상태를 해제하고 메세지 창을 지움
		}
	}

	//키보드의 'j' 키를 누르면 다음 stage로 넘어감 (stageNo가 5미만일 때 게임이 일시정지인 상황에서만 작동)
	if (key == 'j') { //jump
		if (isPause == 1 && stageNo < 5) { //stageNo가 5미만일 때 게임이 일시정지인 상황에서만 작동
			reset(); //할당한 메모리를 해제하고 모든 flag를 초기화함
			stageNo++; //stageNo를 1 증가시켜 다음 stage로 넘어감
			readFile(); //다시 파일로부터 미로의 구조를 읽어 m에 저장한다.
			isStart = 1; //isStart flag를 1로 설정함으로써 point를 화면에 그려줌
			isGoal = 1; //isGoal flag를 1로 설정함으로써 도착점을 화면에 그려줌
			Set_Hint(); //hint들의 개수와 위치를 설정해줌
			isHint = 1;  //isHint flag를 1로 설정함으로써 hint들을 화면에 그려줌
			Set_Attack(); //attacker들의 개수와 위치를 설정해줌
			isAttack = 1; //isAttack flag를 1로 설정함으로써 attacker들을 화면에 그려줌
		}
	}

	//키보드의 위쪽 방향키를 누르면 point가 위로 이동함 (게임이 진행중인 상황에서만 작동)
	if (key == OF_KEY_UP) { // up
		if (isOpen == 1 && isStart == 1 && isClear == 0 && isGameOver == 0 && isPause == 0) { //게임이 진행중인 상황에서만 작동
			cur = point.num(); //현재 point의 위치를 파악하여 cur에 저장
			if (m[cur].up == 1) { //미로구조에서 현재 칸의 위쪽 벽이 뚫려있다면
				cur -= width; //point의 위치는 width만큼 작아짐
				point.getnum(cur); //point의 새로운 위치를 저장
			}
			if (cur == width * height - 1) //point의 새로운 위치가 도착점이라면
				isClear = 1; //isClear flag를 1로 설정
		}
	}

	//키보드의 아래쪽 방향키를 누르면 point가 아래로 이동함 (게임이 진행중인 상황에서만 작동)
	if (key == OF_KEY_DOWN) { // down
		if (isOpen == 1 && isStart == 1&&isClear == 0 && isGameOver == 0 && isPause == 0) { //게임이 진행중인 상황에서만 작동
			cur = point.num(); //현재 point의 위치를 파악하여 cur에 저장
			if (m[cur].down == 1) { //미로구조에서 현재 칸의 아래쪽 벽이 뚫려있다면
				cur += width; //point의 위치는 width만큼 커짐
				point.getnum(cur); //point의 새로운 위치를 저장
			}
			if (cur == width * height - 1) //point의 새로운 위치가 도착점이라면
				isClear = 1; //isClear flag를 1로 설정
		}
	}

	//키보드의 오른쪽 방향키를 누르면 point가 오른쪽으로 이동함 (게임이 진행중인 상황에서만 작동)
	if (key == OF_KEY_RIGHT) { // right
		if (isOpen == 1 && isStart == 1 && isClear == 0 && isGameOver == 0 && isPause == 0) { //게임이 진행중인 상황에서만 작동
			cur = point.num(); //현재 point의 위치를 파악하여 cur에 저장
			if (m[cur].right == 1) { //미로구조에서 현재 칸의 오른쪽 벽이 뚫려있다면
				cur += 1; //point의 위치는 1만큼 커짐
				point.getnum(cur); //point의 새로운 위치를 저장
			}
			if (cur == width * height - 1) //point의 새로운 위치가 도착점이라면
				isClear = 1; //isClear flag를 1로 설정
		}
	}

	//키보드의 왼쪽 방향키를 누르면 point가 왼쪽으로 이동함 (게임이 진행중인 상황에서만 작동)
	if (key == OF_KEY_LEFT) { // left
		if (isOpen == 1 && isStart == 1 && isClear == 0 && isGameOver == 0 && isPause == 0) { //게임이 진행중인 상황에서만 작동
			cur = point.num(); //현재 point의 위치를 파악하여 cur에 저장
			if (m[cur].left == 1) {  //미로구조에서 현재 칸의 왼쪽 벽이 뚫려있다면
				cur -= 1; //point의 위치는 1만큼 작아짐
				point.getnum(cur); //point의 새로운 위치를 저장
			}
			if (cur == width * height - 1) //point의 새로운 위치가 도착점이라면
				isClear = 1; //isClear flag를 1로 설정
		}
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
bool ofApp::readFile() //.maz파일을 읽고 미로의 구조를 배열 m에 저장하는 함수
{
	ofFile file; //파일을 읽기 위해 file변수 선언
	switch (stageNo) { //stageNo에 따라 각각 알맞은 파일을 오픈
	case 1: //stageNo가 1이면 stage1.maz파일을 읽기모드로 오픈한다
		file.open(ofToDataPath("stage1.maz"), ofFile::ReadOnly, false);
		break;
	case 2: //stageNo가 2이면 stage2.maz파일을 읽기모드로 오픈한다
		file.open(ofToDataPath("stage2.maz"), ofFile::ReadOnly, false);
		break;
	case 3: //stageNo가 3이면 stage3.maz파일을 읽기모드로 오픈한다
		file.open(ofToDataPath("stage3.maz"), ofFile::ReadOnly, false);
		break;
	case 4: //stageNo가 4이면 stage4.maz파일을 읽기모드로 오픈한다
		file.open(ofToDataPath("stage4.maz"), ofFile::ReadOnly, false);
		break;
	case 5: //stageNo가 5이면 stage5.maz파일을 읽기모드로 오픈한다
		file.open(ofToDataPath("stage5.maz"), ofFile::ReadOnly, false);
	}
	ofBuffer buffer = file.readToBuffer(); //buffer변수를 선언하고 오픈한 파일의 버퍼를 읽는다

	if (!file.exists()) { //파일이 정상적으로 오픈되지 않았을 경우 에러메시지를 출력한다
		cout << "Target file does not exists." << endl;
		return false;
	}
	else { //파일이 정상적으로 오픈되었을 경우에도 확인메시지를 출력한다
		cout << "We found the target file." << endl;
		isOpen = 1; //isOpen flag를 1로 설정해주어 게임이 진행될 수 있도록 한다
	}

	
	vector<string> LinesofFile; //vector를 이용해 LinesofFile에 동적으로 메모리를 할당
	for (auto line : buffer.getLines()) { //버퍼의 내용을 한줄 씩 line에 저장
		LinesofFile.push_back(line); //LinesofFile에 내용을 한줄씩 삽입
		height++; //미로의 높이를 나타내는 변수 height를 1씩 증가
	}
	width = (LinesofFile[0].size() - 1) / 2; //.maz파일은 실제 미로의 너비보다 2*N+1만큼 데이커를 가지고 있으므로 이를 이용해 width를 구한다
	height = (height - 1) / 2; //.maz파일은 실제 미로의 높이보다 2*M+1만큼 데이커를 가지고 있으므로 이를 이용해 height를 구한다

	m = (maze*)malloc(sizeof(maze) * width * height); //m배열에 width*height 만큼 메모리를 동적으로 할당한다.

	int i, j; //반복문을 수행하기 위한 변수; LinesofFile에 저장된 .maz파일의 정보에 접근 
	int count1, count2; //반복문을 수행하기 위한 변수; LinesofFile에 저장된 .maz파일의 실제 미로의 칸에 해당하는 정보에 접근 
	int num = 0; //미로의 각 칸에 대해 접근

	//i는 LinesofFIle에서 유의미한 칸을 탐색하기 위해 2칸씩 증가 count1은 1씩 증가하여 width에 도달할 때까지
	for (i = 1, count1 = 0; count1 < height; i = i + 2, count1++) { 
		//j도 LinesofFIle에서 유의미한 칸을 탐색하기 위해 2칸씩 증가 count2은 1씩 증가하여 height에 도달할 때까지
		for (j = 1, count2 = 0; count2 < width; j = j + 2, count2++) {
			//up
			if (LinesofFile[i - 1][j] == ' ')  //현재 칸의 위쪽 벽이 없다면
				m[num].up = 1; 
			else ////현재 칸의 위쪽 벽이 있다면
				m[num].up = 0;
			//down
			if (LinesofFile[i + 1][j] == ' ')  //현재 칸의 아래쪽 벽이 없다면
				m[num].down = 1;
			else //현재 칸의 아래쪽 벽이 있다면
				m[num].down = 0;
			//right
			if (LinesofFile[i][j + 1] == ' ')  //현재 칸의 오른쪽 벽이 없다면
				m[num].right = 1;
			else //현재 칸의 오른쪽 벽이 있다면
				m[num].right = 0;
			//left
			if (LinesofFile[i][j - 1] == ' ')  //현재 칸의 왼쪽 벽이 없다면
				m[num].left = 1;
			else //현재 칸의 왼쪽 벽이 있다면
				m[num].left = 0;

			num++; //현재 칸의 상하좌우를 모두 살피고 다음 칸으로 넘어감 
		}
	}

	file.close(); //파일 읽기를 완료하면 파일을 닫아준다
		
}

void ofApp::Set_Hint() { //hint의 개수와 위치를 초기화할 함수
	if (width * height < 50) // width*height가 50미만이면
		hintNo = 1; //hint는 1개
	else if (width * height < 100) // width*height가 50이상 100미만이면
		hintNo = 2; //hint는 2개
	else if (width * height < 150) // width*height가 100이상 150미만이면
		hintNo = 3; //hint는 3개
	else if (width * height < 200) // width*height가 150이상 200미만이면
		hintNo = 4; //hint는 4개
	else hintNo = 5; // width*height가 200이상이면 hint가 5개

	hint = (POINTER*)malloc(sizeof(POINTER) * hintNo); //hint배열에 hintNo만큼 메모리를 동적으로 할당한다.
	hintX = (float*)malloc(sizeof(float) * hintNo); //hintX배열에 hintNo만큼 메모리를 동적으로 할당한다.
	hintY = (float*)malloc(sizeof(float) * hintNo); //hintY배열에 hintNo만큼 메모리를 동적으로 할당한다.

	for (int i = 0; i < hintNo; i++) { //힌트의 개수만큼
		int rad = (rand() % (width * height - 2)) + 1; //힌트의 위치를 랜덤으로 결정한다(1~(width*height-2)); 출발점과 도착점 제외
		hint[i].getnum(rad); //랜덤으로 얻은 위치를 hint의 data에 저장한다.
	}
}

int ofApp::Check_Same(int num) { //num의 위치가 hint의 위치와 동일한지 판단; 같으면 같은 힌트의 번호를 반환, 아니면 -1 반환
	int i; //반복문을 실행하기 위한 변수
	for (i = 0; i < hintNo; i++) { //모든 힌트와 비교
		if (num == hint[i].num()) //num의 위치와 hint의 위치가 같다면 break
			break;
	}
	if (i == hintNo) //num의 위치가 모든 hint의 위치와 달랐을 경우 -1을 반환
		return -1;
	else //하나라도 같은 위치가 있었다면 그 위치의 hint번호를 반환(0~hintNo)
		return i;
}

void ofApp::Set_Attack() { //attacker의 개수와 위치를 초기화할 함수
	if (width * height < 50)// width*height가 50미만이면
		attackNo = 1; //attacker는 1개
	else if (width * height < 100) // width*height가 50이상 100미만이면
		attackNo = 2; //attacker는 2개
	else if (width * height < 150) // width*height가 100이상 150미만이면
		attackNo = 3; //attacker는 3개
	else if (width * height < 200) // width*height가 150이상 200미만이면
		attackNo = 4; //attacker는 4개
	else attackNo = 5; // width*height가 200이상이면 attacker가 5개

	attacker = (POINTER*)malloc(sizeof(POINTER) * attackNo); //attacker배열에 attackNo만큼 메모리를 동적으로 할당한다.
	attackerX = (float*)malloc(sizeof(float) * attackNo); //attackerX배열에 attackNo만큼 메모리를 동적으로 할당한다.
	attackerY = (float*)malloc(sizeof(float) * attackNo); //attackerY배열에 attackNo만큼 메모리를 동적으로 할당한다.

	int i = 0; //반복문을 실행하기 위한 변수 
	while (i < attackNo) {// 모든 attacker들에 대해
		int rad = (rand() % (width * height - 2)) + 1; //힌트의 위치를 랜덤으로 결정한다(1~(width*height-2)); 출발점과 도착점 제외
		if(Check_Same(rad)>=0) //만약 랜덤으로 얻은 attacker의 위치가 적어도 하나의 hint와 겹친다면 다시 위치를 결정
			continue;
		else { //모든 hint와 위치가 겹치지 않는다면 
			attacker[i].getnum(rad); //attacker의 data에 위치를 저장하고
			i++; //다음 attacker의 위치를 결정함
		}
	}
}
void ofApp::Move_Attack() { //attacker를 움직이게 할 함수
	int i;//반복문을 실행하기 위한 변수
	for (i = 0; i < attackNo; i++) { // 모든 attacker들에 대해
		int loc = attacker[i].num(); //attacker의 위치를 변수 loc에 저장
		int count=0; //아래의 while문이 무한loop를 돌지않게 하기 위한 변수
		int dir; //attacker가 나아갈 방향을 나타내는 변수
		
		while (1) {
			dir = rand() % 4; //attacker가 진행할 방향은 랜덤으로 결정(0:up/1:down/2:right/3:left로 설정)
			if (dir == 0 && m[loc].up == 1 && Check_Same(loc - width) < 0) { //dir이 0일때 위쪽 벽이 뚫려있으며 위 칸에 hint가 위치해있지 않는 경우
				loc -= width; //loc의 값에서 width만큼 빼준다
				break;
			}
			else if (dir == 1 && m[loc].down == 1 && Check_Same(loc + width) < 0) { //dir이 1일때 아래쪽 벽이 뚫려있으며 아래 칸에 hint가 위치해있지 않는 경우
				loc += width; //loc의 값에서 width만큼 더해준다
				break;
			}
			else if (dir == 2 && m[loc].right == 1 && Check_Same(loc + 1) < 0) { //dir이 2일때 오른쪽 벽이 뚫려있으며 오른쪽 칸에 hint가 위치해있지 않는 경우
				loc += 1; //loc의 값에서 1만큼 더해준다
				break;
			}
			else if (dir == 3 && m[loc].left == 1 && Check_Same(loc - 1) < 0) { //dir이 3일때 왼쪽 벽이 뚫려있으며 왼쪽 칸에 hint가 위치해있지 않는 경우
				loc -= 1;  //loc의 값에서 1만큼 빼준다
				break;
			}
			count++; //만약 위의 경우에 해당하지 못하는 경우라면 다시 이동을 시도한다
			if (count > 4) //만약 이동 시도가 4번을 초과했다면 이동하지 않도록한다 ;무한 loop가 생성되는걸 방지한다
				break;
		}
			
		attacker[i].getnum(loc); //attacker의 data에 새로운 위치를 저장한다
		if (loc == point.num()) //attacker의 새 위치가 point와 같아지면 
			isGameOver = 1; //isGameOver flag를 1로 설정한다
	}
}

void ofApp::Meet_Hint() { //point가 hint를 만났을 때 동작을 나타내는 함수
	int num = Check_Same(point.num()); //point의 위치가 hint들 중 하나라도 만나는지를 확인하여 num에 값을 저장한다
	if (num>=0) { //num>=0이라면 point와 만나는 hint가 존재한다는 의미이므로
		isMeet = 1; //isMeet flag는 1로 설정
		meetX = hintX[num]; //그 hint의 x좌표를 meetX에 저장
		meetY = hintY[num]; //그 hint의 y좌표를 meetY에 저장
		hint[num].getnum(-1); //그 hint는 더이상 사용할 수 없으므로 데이터를 음수값 -1을 저장한다
	}
}

void ofApp::explosion(float x, float y) { //point가 attacker나 hint, 도착점을 만났을 때 (x,y)좌표에서 시각적인 효과를 주는 함수
	int num = 10; //파편의 개수를 나타내는 변수 
	for (int r = 0; r < num; r++) { //파편의 개수만큼
		float radi = ofRandom(2, 10); //반지름의 길이는 2~10사이로 random하게 결정
		float xOffset = ofRandom(-20, 20); //파편이 그려질 위치의 x좌표를 -20~20사이로 random하게 결정
		float yOffset = ofRandom(-20, 20); //파편이 그려질 위치의 y좌표를 -20~20사이로 random하게 결정
		ofDrawCircle(x + xOffset,y + yOffset, radi); //설정한 위치에 원을 그려 폭발을 시각적으로 표현 
	}
}

void ofApp::reset() { //모든 flag들을 초기화 하고 메모리를 해제하는 함수
	isOpen = 0; //isOpen flag를 0으로 초기화
	isStart = 0; //isStart flag를 0으로 초기화
	isGoal = 0; //isGoal flag를 0으로 초기화
	isAttack = 0; //isAttack flag를 0으로 초기화
	isHint = 0; //isHint flag를 0으로 초기화
	isPause = 0; //isPause flag를 0으로 초기화
	isClear = 0; //isClear flag를 0으로 초기화
	isGameOver = 0; //isGameOver flag를 0으로 초기화
	width = 0; //width를 0으로 초기화
	height = 0; //height를 0으로 초기화
	point.getnum(0); //point의 위치를 0으로 초기화
	freeMemory(); //동적으로 할당한 메모리를 해제하는 함수
}

void ofApp::freeMemory() { // malloc한 memory들을 free해주는 함수

	free(m); //m의 메모리를 해제
	free(attacker); //attacker의 메모리를 해제
	free(attackerX); //attackerX의 메모리를 해제
	free(attackerY); //attackerY의 메모리를 해제
	free(hint); //hint의 메모리를 해제
	free(hintX); //hintX의 메모리를 해제
	free(hintY); //hintY의 메모리를 해제

}

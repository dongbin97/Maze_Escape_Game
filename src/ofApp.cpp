#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	//windowâ�� ���� �⺻ ����
	ofSetWindowTitle("FINAL PROJECT"); // windowâ ��ܿ� title�� ������
	ofSetFrameRate(4); //1�ʿ� 4�� �����̵��� ���� attacker�� �ʹ� ������ �����̴� ���� �����ϱ� ����
	ofBackground(255, 255, 255); //windowȭ���� ����� ������� ����
	windowWidth = ofGetWidth(); //windowâ�� �ʺ� ���� windowWidth������ ����
	windowHeight = ofGetHeight();  //windowâ�� ���̸� ���� windowWidth������ ����
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2); //windowâ�� ��ǻ�� ȭ���� �߾ӿ� ��Ÿ���� ��
	
	//���α׷��� �ʿ��� flag�� �ʱ�ȭ
	stageNo = 1; //ó�� stage�� 1�ܰ踦 �ǹ���
	isOpen = 0; //���� ������ open���� �ʾ����� �ǹ���
	isStart = 0; //���� ������ �������� ������ �ǹ���
	isGoal = 0; //���� �������� �׷����� ������ �ǹ���
	isAttack = 0; //���� attacker���� �׷����� ������ �ǹ���
	isHint = 0; //���� hint���� �׷����� ������ �ǹ���
	isMeet = 0; //���� hint�� pointer�� ������ �ʾ����� �ǹ���
	isPause = 0; //���� ���α׷��� �ߴ��϶�� ����� ������ �ǹ���
	isClear = 0; //���� stage�� clear���� �ʾ����� �ǹ���
	isGameOver = 0; //���� game over�� �̷������ �ʾ����� �ǹ���
	
	myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"��Ʈ�� ũ�� 20���� load��

	point.getnum(0); //point�� ó�� ��ġ�� �̷��� (0,0)ĭ���� �ǹ���

} // end Setup

//--------------------------------------------------------------
void ofApp::update() {
	//������ ����Ǵ� ����(isAttack�� 1�̿��� �ϰ�, stage clear, game over, pause�� �ƴ� ��Ȳ������ �Ʒ��� �۵���)
	if (isAttack == 1 && isClear == 0 && isGameOver == 0 && isPause == 0) {
		Move_Attack(); //attacker���� �������� ǥ���� �� �Լ�
		Meet_Hint(); //point�� hint�� ������ ��� ó���� ���ִ� �Լ�
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	char str[256]; //ȭ�鿡 ����� �޽����� ������ ���ڿ�
	ofSetColor(50); //�̷��� ���� �׷��� ���� ���� ȸ������ ����
	ofSetLineWidth(3); //�̷��� ���� �ǹ��ϴ� ���� ���� 3���� ����

	int i; //�ݺ����� �����ϱ� ���� ����

	if (isOpen) { //������ open�� ��� �Ʒ��� �����Ѵ�
		//windowâ�� ũ�⿡ �̷��� ũ�⸦ ���߾� �׷��ֱ� ���� �� ���� ���� �̷� ��ĭ�� ũ��� ����
		size = ((windowWidth-80)/width > (windowHeight-80)/height) ? (windowHeight - 80) /height : (windowWidth - 80) /width;
		//������ ���� size�� �̿��� �̷θ� �׷��ֱ� ������ x��ǥ, y��ǥ�� ����
		startX = (windowWidth-size*width)/2, startY = (windowHeight-size*height)/2.5;

		//�̷��� ū �׵θ� ���� ���� �̿��� �׷��ش�
		ofDrawLine(startX, startY, startX + size * width, startY);
		ofDrawLine(startX, startY, startX, startY + size * height);
		ofDrawLine(startX + size * width, startY, startX + size * width, startY + size * height);
		ofDrawLine(startX, startY + size * height, startX + size * width, startY + size * height);

		//�̷� ������ ���� �׷��ش�
		//����ĭ�� ������ ���� ������ ĭ�� ���� ��, ����ĭ�� �Ʒ��� ���� �Ʒ��� ĭ�� ���� ���� ��ħ�� �̿��Ͽ�
		//�� �̷��� ĭ���� ������ ���� �Ʒ��� ���� ������ Ȯ���Ͽ� �̷��� ���� �׷��ش�
		for (i = 0; i < width * height; i++) {
			if (m[i].right == 0) { //����ĭ�� ������ ���� ������ �̷��� ���� �׷��ش�
				ofDrawLine(startX + size * (i % width + 1), startY + size * (i / width), startX + size * (i % width + 1), startY + size * (i / width + 1));
			}
			if (m[i].down == 0) { //����ĭ�� �Ʒ��� ���� ������ �̷��� ���� �׷��ش�
				ofDrawLine(startX + size * (i % width), startY + size * (i / width + 1), startX + size * (i % width + 1), startY + size * (i / width + 1));
			}
		}
		
		if (isStart) { //start����� ���ͼ� isStart flag�� 1�� �Ǹ�
			//point�� �ϴû� ������ �׷��ش�
			ofSetColor(135, 206, 250); //light sky blue������ ����
			radius = size / 4; //point�� �������� �̷� �� ĭ�� 1/4
			pointX = startX + size / 2 + size * (point.num() % width); //point�� x��ǥ�� ���� point�� data�� width�� ���� �������� �ش�
			pointY = startY + size / 2 + size * (point.num() / width); //point�� y��ǥ�� ���� point�� data�� width�� ���� �� �ش�
			ofDrawCircle(pointX, pointY, radius); //(pointX, pointY)��ġ�� �������� radius�� ���� �׸�

			if (isGoal) { //isStart�� 1�� ��쿡 isGoal flag�� 1�� �Ǹ� 
				ofSetColor(152, 251, 152); //pale green ������ ����
				//������ (width-1,height-1) ������ �簢������ �������� �׷���
				ofDrawRectangle(startX + size / 4 + size * ((width * height - 1) % width), startY + size / 4 + size * ((width * height - 1) / width), size / 2, size / 2);
			}
		}

		if (isAttack) { //isAttack flag�� 1�� �Ǹ�
			
			ofSetColor(255, 0, 0); //red������ ����
			radius = size / 4; //attacker�� �������� �̷� �� ĭ�� 1/4
			for (i = 0; i < attackNo; i++) { //��� attacker���� ��ġ�� ������ �׷���
				attackerX[i] = startX + size / 2 + size * (attacker[i].num() % width); //attacker�� x��ǥ�� ���� attacker�� data�� width�� ���� �������� �ش�
				attackerY[i] = startY + size / 2 + size * (attacker[i].num() / width); //attacker�� y��ǥ�� ���� attacker�� data�� width�� ���� �� �ش�
				ofDrawCircle(attackerX[i], attackerY[i], radius); //(attackerX, attackerY)��ġ�� �������� radius�� ���� �׸�
			}
		}

		if (isHint) { //isHint flag�� 1�� �Ǹ�
			ofSetColor(255, 215, 0); //gold������ ����
			radius = size / 4; //hint�� �������� �̷� �� ĭ�� 1/4
			for (i = 0; i < hintNo; i++) { //��� hint���� ��ġ�� ������ �׷���
				if (hint[i].num() > 0) { //�̹� point�� ���� hint�� Meet_Hint()�Լ��� ���� �������� data�� ������ �ǰ� �׷����� ����
					hintX[i] = startX + size / 2 + size * (hint[i].num() % width); //hint�� x��ǥ�� ���� hint�� data�� width�� ���� �������� �ش�
					hintY[i] = startY + size / 2 + size * (hint[i].num() / width); //hint�� x��ǥ�� ���� hint�� data�� width�� ���� �� �ش�
					ofDrawCircle(hintX[i], hintY[i], radius); //(hintX, hintY)��ġ�� �������� radius�� ���� �׸�
				}
			}
		}

		if (isMeet) { //isMeet flag�� 1�� �Ǹ�; point�� hint�� �ϳ��� ������
			ofSetColor(255, 215,0); //gold������ ����
			explosion(meetX,meetY); //point�� hint�� ������ ��, ȿ���� ȭ�鿡 �׷���
			ofSetColor(255, 0, 0); //red������ ����
			explosion(attackerX[attackNo - 1], attackerY[attackNo - 1]); //point�� hint�� ������ ��, attacker�� �ϳ� ������� ȿ���� ȭ�鿡 �׷���
			attackNo--; //attacker�� ������ �ϳ� ���δ�
			isMeet = 0; //�ٽ� isMeet�� 0���� �������ش�
		}

		if (isPause) { //isPause flag�� 1�� �Ǹ�; ���� ����� ������
			ofSetColor(255, 255, 255); //white������ ����
			ofDrawRectangle(windowWidth / 6, windowHeight / 4, windowWidth * 4 / 6, windowHeight * 2 / 4); //�޽��� â�� ��Ÿ�� ���簢���� �׸�
			ofSetColor(152, 251, 152); //pale green������ ����
			//�޽��� â�� �׵θ��� ������ �׷��ش� 
			ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth * 5 / 6, windowHeight / 4);
			ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth / 6, windowHeight * 3 / 4);
			ofDrawLine(windowWidth * 5 / 6, windowHeight / 4, windowWidth * 5 / 6, windowHeight * 3 / 4);
			ofDrawLine(windowWidth / 6, windowHeight * 3 / 4, windowWidth * 5 / 6, windowHeight * 3 / 4);
			ofSetColor(0); //black������ ����
			myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"��Ʈ�� ũ�� 20���� load��
			strcpy(str, "PAUSE"); //str�� �޽����� ������
			myFont.drawString(str, windowWidth / 2.4, windowHeight / 2.5); //�������� ��ġ�� str�� ������ ����Ѵ�
			myFont.loadFont("verdana.ttf", 12, true, true); //"verdana.ttf"��Ʈ�� ũ�� 12�� load��
			if (stageNo < 5) { //stage�� 5 �̸��� ��쿡�� p, j �ΰ��� �������� ����
				strcpy(str, "p: Continue	j: Nest Stage"); //str�� �޽����� ������
				myFont.drawString(str, windowWidth / 3, windowHeight / 1.6); //�������� ��ġ�� str�� ������ ����Ѵ�
			}
			else { //stage5������ ���� stage�� jump�� �� �����Ƿ� p�޽����� �˸�
				strcpy(str, "p: Continue"); //str�� �޽����� ������
				myFont.drawString(str, windowWidth / 2.5, windowHeight / 1.6);  //�������� ��ġ�� str�� ������ ����Ѵ�
			}
		}
	}

	if (isClear) { //isClear flag�� 1�� �Ǹ�; ���� stage���� point�� �������� �����ϸ�
		isGoal = 0; //�������� �׷����� �ʵ��� �ϰ�
		ofSetColor(152, ofRandom(230,255), 152); //random���� pale green �ֺ��� ���� ���� 
		explosion(pointX, pointY); //point�� ������ ������ ��, ȿ���� ȭ�鿡 �׷���
		ofSetColor(255, 255, 255); //white������ ����
		ofDrawRectangle(windowWidth / 6, windowHeight / 4, windowWidth * 4 / 6, windowHeight * 2 / 4);//�޽��� â�� ��Ÿ�� ���簢���� �׸�
		ofSetColor(65, 105, 225); //royal blue������ ����
		//�޽��� â�� �׵θ��� ������ �׷��ش� 
		ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth*5 / 6, windowHeight / 4);
		ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth / 6 , windowHeight*3/4);
		ofDrawLine(windowWidth*5/6, windowHeight / 4, windowWidth*5/6, windowHeight*3/4);
		ofDrawLine(windowWidth / 6 , windowHeight*3/4, windowWidth*5/6, windowHeight*3/4);
		ofSetColor(0); //black������ ����
		if (stageNo < 5) { //stageNo�� 5�̸��� ���� "STAGE CLEAR"��� �޼����� ���
			myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"��Ʈ�� ũ�� 20���� load��
			strcpy(str, "STAGE CLEAR!"); //str�� �޽����� ������
			myFont.drawString(str, windowWidth / 2.8, windowHeight / 2.5);//�������� ��ġ�� str�� ������ ����Ѵ�
			myFont.loadFont("verdana.ttf", 12, true, true); //"verdana.ttf"��Ʈ�� ũ�� 12���� load��
			strcpy(str, "y: Next Stage	n: Quit");  //str�� �޽����� ������; y,n �ΰ��� �������� ����
			myFont.drawString(str, windowWidth / 3, windowHeight / 1.6); //�������� ��ġ�� str�� ������ ����Ѵ�
		}
		else { //stageNo�� 5�̸��� ���� "CONGRATULATION"��� �޼����� ���
			myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"��Ʈ�� ũ�� 20���� load��
			strcpy(str, "CONGRATULATION!"); //str�� �޽����� ������
			myFont.drawString(str, windowWidth / 3.4, windowHeight / 2.5); //�������� ��ġ�� str�� ������ ����Ѵ�
			myFont.loadFont("verdana.ttf", 12, true, true);  //"verdana.ttf"��Ʈ�� ũ�� 12���� load��
			strcpy(str, "n: Quit");   //str�� �޽����� ������; ������ stage�̹Ƿ� �������� n�� ����
			myFont.drawString(str, windowWidth / 2.3, windowHeight / 1.6); //�������� ��ġ�� str�� ������ ����Ѵ�
		}
	}

	if (isGameOver) { //isClear flag�� 1�� �Ǹ�; point�� attacker�� ������
		ofSetColor(ofRandom(50, 255), 0, 0); //random���� red �ֺ��� ���� ���� 
		explosion(pointX, pointY); //point�� attacker�� ������ ��, ȿ���� ȭ�鿡 �׷���
		ofSetColor(255, 255, 255);//white������ ����
		ofDrawRectangle(windowWidth / 6, windowHeight / 4, windowWidth * 4 / 6, windowHeight * 2 / 4);//�޽��� â�� ��Ÿ�� ���簢���� �׸�
		ofSetColor(128, 0, 0); //maroon������ ����
		//�޽��� â�� �׵θ��� ������ �׷��ش� 
		ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth * 5 / 6, windowHeight / 4);
		ofDrawLine(windowWidth / 6, windowHeight / 4, windowWidth / 6, windowHeight * 3 / 4);
		ofDrawLine(windowWidth * 5 / 6, windowHeight / 4, windowWidth * 5 / 6, windowHeight * 3 / 4);
		ofDrawLine(windowWidth / 6, windowHeight * 3 / 4, windowWidth * 5 / 6, windowHeight * 3 / 4);
		ofSetColor(0); //black������ ����
		myFont.loadFont("verdana.ttf", 20, true, true); //"verdana.ttf"��Ʈ�� ũ�� 20���� load��
		strcpy(str, "Game Over!"); //str�� �޽����� ������
		myFont.drawString(str, windowWidth / 2.8, windowHeight / 2.5); //�������� ��ġ�� str�� ������ ����Ѵ�
		myFont.loadFont("verdana.ttf", 12, true, true);  //"verdana.ttf"��Ʈ�� ũ�� 12���� load��
		strcpy(str, "r: Retry			n: Quit"); //str�� �޽����� ������; r,n �ΰ��� �������� ����
		myFont.drawString(str, windowWidth / 3, windowHeight / 1.6); //�������� ��ġ�� str�� ������ ����Ѵ�
	}
} // end Draw

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	//Ű������ escŰ�� ������ ������ ���α׷� ����
	if(key == VK_ESCAPE) {
		freeMemory(); //�Ҵ��� �޸𸮸� �����Ѵ�
		ofExit(); //���α׷��� �����Ѵ�
	}

	//Ű������ 'd' Ű�� ������ �̷α����� �׷��� (stage1���� ������ ������ ���� ���, �̿��� ��� �ڵ������� �׷���) 
	if (key == 'd') { //draw
		if (isOpen == 0) { //������ ���� ������ ���� ��쿡
			readFile(); //���Ϸκ��� �̷��� ������ �о� m�� �����Ѵ�.
		}
	}

	//Ű������ 's' Ű�� ������ ������ ���۵�(stage1���� ������ ������ ���� ���, �̿��� ��� �ڵ������� ���۵�)
	if (key == 's') { // start
		if (isOpen == 1 && isStart == 0) { //������ ���Ȱ�, ���� ������ ���۵��� ���� ��쿡�� �۵�
			isStart = 1; //isStart flag�� 1�� ���������ν� point�� ȭ�鿡 �׷���
			isGoal = 1; //isGoal flag�� 1�� ���������ν� �������� ȭ�鿡 �׷���
			Set_Hint(); //hint���� ������ ��ġ�� ��������
			isHint = 1; //isHint flag�� 1�� ���������ν� hint���� ȭ�鿡 �׷���
			Set_Attack(); //attacker���� ������ ��ġ�� ��������
			isAttack = 1; //isAttack flag�� 1�� ���������ν� attacker���� ȭ�鿡 �׷���
		}
	}

	//Ű������ 'r'  Ű�� ������ ������ �ٽ� ���۵�(game over ���¿����� �۵�)
	if (key == 'r') { //retry
		if (isGameOver == 1) { //game over���¿����� 'r'�� ������ �� �۵�
			reset(); //�Ҵ��� �޸𸮸� �����ϰ� ��� flag�� �ʱ�ȭ��
			readFile(); //�ٽ� ���Ϸκ��� �̷��� ������ �о� m�� �����Ѵ�.
			isStart = 1; //isStart flag�� 1�� ���������ν� point�� ȭ�鿡 �׷���
			isGoal = 1; //isGoal flag�� 1�� ���������ν� �������� ȭ�鿡 �׷���
			Set_Hint(); //hint���� ������ ��ġ�� ��������
			isHint = 1;  //isHint flag�� 1�� ���������ν� hint���� ȭ�鿡 �׷���
			Set_Attack();  //attacker���� ������ ��ġ�� ��������
			isAttack = 1; //isAttack flag�� 1�� ���������ν� attacker���� ȭ�鿡 �׷���
		}
	}

	//Ű������ 'y' Ű�� ������ ���� stage�� ������ �ٷ� ���۵�(stage clear ���¿����� �۵�)
	if (key == 'y') { //yes
		if (isClear == 1 && stageNo < 5) { //stageNo�� 5 �̸��� �� stage clear���¿����� �۵� (stage5������ ���� �ܰ谡 �����Ƿ�)
			reset();  //�Ҵ��� �޸𸮸� �����ϰ� ��� flag�� �ʱ�ȭ��
			stageNo++; //stageNo�� 1 �������� ���� stage�� �Ѿ
			readFile(); //�ٽ� ���Ϸκ��� �̷��� ������ �о� m�� �����Ѵ�.
			isStart = 1; //isStart flag�� 1�� ���������ν� point�� ȭ�鿡 �׷���
			isGoal = 1; //isGoal flag�� 1�� ���������ν� �������� ȭ�鿡 �׷���
			Set_Hint(); //hint���� ������ ��ġ�� ��������
			isHint = 1;  //isHint flag�� 1�� ���������ν� hint���� ȭ�鿡 �׷���
			Set_Attack(); //attacker���� ������ ��ġ�� ��������
			isAttack = 1; //isAttack flag�� 1�� ���������ν� attacker���� ȭ�鿡 �׷���
		}
	}

	//Ű������ 'n' Ű�� ������ ���α׷��� ����� (stage clear�� game over ���¿����� �۵�)
	if (key == 'n') { //no
		if (isClear == 1 || isGameOver == 1) { //stage clear�� game over ���¿����� �۵�
			freeMemory(); //�Ҵ��� �޸𸮸� �����Ѵ�
			ofExit(); //���α׷��� �����Ѵ�
		}
	}

	//Ű������ 'p' Ű�� ������ ���α׷��� �Ͻ������� (������ �������� ��Ȳ������ �۵�)
	if (key == 'p') { //pause
		if (isStart == 1 && isClear == 0 && isGameOver == 0) { //������ �������� ��Ȳ������ �۵�
			if (isPause == 0) //�Ͻ����� ���°� �ƴϾ��ٸ�
				isPause = 1; //���α׷��� �Ͻ����� �ϰ� �޼��� â�� ����ϵ��� ��
			else //�̹� �Ͻ����� ���¿��� ���
				isPause = 0; //���α׷��� �Ͻ����� ���¸� �����ϰ� �޼��� â�� ����
		}
	}

	//Ű������ 'j' Ű�� ������ ���� stage�� �Ѿ (stageNo�� 5�̸��� �� ������ �Ͻ������� ��Ȳ������ �۵�)
	if (key == 'j') { //jump
		if (isPause == 1 && stageNo < 5) { //stageNo�� 5�̸��� �� ������ �Ͻ������� ��Ȳ������ �۵�
			reset(); //�Ҵ��� �޸𸮸� �����ϰ� ��� flag�� �ʱ�ȭ��
			stageNo++; //stageNo�� 1 �������� ���� stage�� �Ѿ
			readFile(); //�ٽ� ���Ϸκ��� �̷��� ������ �о� m�� �����Ѵ�.
			isStart = 1; //isStart flag�� 1�� ���������ν� point�� ȭ�鿡 �׷���
			isGoal = 1; //isGoal flag�� 1�� ���������ν� �������� ȭ�鿡 �׷���
			Set_Hint(); //hint���� ������ ��ġ�� ��������
			isHint = 1;  //isHint flag�� 1�� ���������ν� hint���� ȭ�鿡 �׷���
			Set_Attack(); //attacker���� ������ ��ġ�� ��������
			isAttack = 1; //isAttack flag�� 1�� ���������ν� attacker���� ȭ�鿡 �׷���
		}
	}

	//Ű������ ���� ����Ű�� ������ point�� ���� �̵��� (������ �������� ��Ȳ������ �۵�)
	if (key == OF_KEY_UP) { // up
		if (isOpen == 1 && isStart == 1 && isClear == 0 && isGameOver == 0 && isPause == 0) { //������ �������� ��Ȳ������ �۵�
			cur = point.num(); //���� point�� ��ġ�� �ľ��Ͽ� cur�� ����
			if (m[cur].up == 1) { //�̷α������� ���� ĭ�� ���� ���� �շ��ִٸ�
				cur -= width; //point�� ��ġ�� width��ŭ �۾���
				point.getnum(cur); //point�� ���ο� ��ġ�� ����
			}
			if (cur == width * height - 1) //point�� ���ο� ��ġ�� �������̶��
				isClear = 1; //isClear flag�� 1�� ����
		}
	}

	//Ű������ �Ʒ��� ����Ű�� ������ point�� �Ʒ��� �̵��� (������ �������� ��Ȳ������ �۵�)
	if (key == OF_KEY_DOWN) { // down
		if (isOpen == 1 && isStart == 1&&isClear == 0 && isGameOver == 0 && isPause == 0) { //������ �������� ��Ȳ������ �۵�
			cur = point.num(); //���� point�� ��ġ�� �ľ��Ͽ� cur�� ����
			if (m[cur].down == 1) { //�̷α������� ���� ĭ�� �Ʒ��� ���� �շ��ִٸ�
				cur += width; //point�� ��ġ�� width��ŭ Ŀ��
				point.getnum(cur); //point�� ���ο� ��ġ�� ����
			}
			if (cur == width * height - 1) //point�� ���ο� ��ġ�� �������̶��
				isClear = 1; //isClear flag�� 1�� ����
		}
	}

	//Ű������ ������ ����Ű�� ������ point�� ���������� �̵��� (������ �������� ��Ȳ������ �۵�)
	if (key == OF_KEY_RIGHT) { // right
		if (isOpen == 1 && isStart == 1 && isClear == 0 && isGameOver == 0 && isPause == 0) { //������ �������� ��Ȳ������ �۵�
			cur = point.num(); //���� point�� ��ġ�� �ľ��Ͽ� cur�� ����
			if (m[cur].right == 1) { //�̷α������� ���� ĭ�� ������ ���� �շ��ִٸ�
				cur += 1; //point�� ��ġ�� 1��ŭ Ŀ��
				point.getnum(cur); //point�� ���ο� ��ġ�� ����
			}
			if (cur == width * height - 1) //point�� ���ο� ��ġ�� �������̶��
				isClear = 1; //isClear flag�� 1�� ����
		}
	}

	//Ű������ ���� ����Ű�� ������ point�� �������� �̵��� (������ �������� ��Ȳ������ �۵�)
	if (key == OF_KEY_LEFT) { // left
		if (isOpen == 1 && isStart == 1 && isClear == 0 && isGameOver == 0 && isPause == 0) { //������ �������� ��Ȳ������ �۵�
			cur = point.num(); //���� point�� ��ġ�� �ľ��Ͽ� cur�� ����
			if (m[cur].left == 1) {  //�̷α������� ���� ĭ�� ���� ���� �շ��ִٸ�
				cur -= 1; //point�� ��ġ�� 1��ŭ �۾���
				point.getnum(cur); //point�� ���ο� ��ġ�� ����
			}
			if (cur == width * height - 1) //point�� ���ο� ��ġ�� �������̶��
				isClear = 1; //isClear flag�� 1�� ����
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
bool ofApp::readFile() //.maz������ �а� �̷��� ������ �迭 m�� �����ϴ� �Լ�
{
	ofFile file; //������ �б� ���� file���� ����
	switch (stageNo) { //stageNo�� ���� ���� �˸��� ������ ����
	case 1: //stageNo�� 1�̸� stage1.maz������ �б���� �����Ѵ�
		file.open(ofToDataPath("stage1.maz"), ofFile::ReadOnly, false);
		break;
	case 2: //stageNo�� 2�̸� stage2.maz������ �б���� �����Ѵ�
		file.open(ofToDataPath("stage2.maz"), ofFile::ReadOnly, false);
		break;
	case 3: //stageNo�� 3�̸� stage3.maz������ �б���� �����Ѵ�
		file.open(ofToDataPath("stage3.maz"), ofFile::ReadOnly, false);
		break;
	case 4: //stageNo�� 4�̸� stage4.maz������ �б���� �����Ѵ�
		file.open(ofToDataPath("stage4.maz"), ofFile::ReadOnly, false);
		break;
	case 5: //stageNo�� 5�̸� stage5.maz������ �б���� �����Ѵ�
		file.open(ofToDataPath("stage5.maz"), ofFile::ReadOnly, false);
	}
	ofBuffer buffer = file.readToBuffer(); //buffer������ �����ϰ� ������ ������ ���۸� �д´�

	if (!file.exists()) { //������ ���������� ���µ��� �ʾ��� ��� �����޽����� ����Ѵ�
		cout << "Target file does not exists." << endl;
		return false;
	}
	else { //������ ���������� ���µǾ��� ��쿡�� Ȯ�θ޽����� ����Ѵ�
		cout << "We found the target file." << endl;
		isOpen = 1; //isOpen flag�� 1�� �������־� ������ ����� �� �ֵ��� �Ѵ�
	}

	
	vector<string> LinesofFile; //vector�� �̿��� LinesofFile�� �������� �޸𸮸� �Ҵ�
	for (auto line : buffer.getLines()) { //������ ������ ���� �� line�� ����
		LinesofFile.push_back(line); //LinesofFile�� ������ ���پ� ����
		height++; //�̷��� ���̸� ��Ÿ���� ���� height�� 1�� ����
	}
	width = (LinesofFile[0].size() - 1) / 2; //.maz������ ���� �̷��� �ʺ񺸴� 2*N+1��ŭ ����Ŀ�� ������ �����Ƿ� �̸� �̿��� width�� ���Ѵ�
	height = (height - 1) / 2; //.maz������ ���� �̷��� ���̺��� 2*M+1��ŭ ����Ŀ�� ������ �����Ƿ� �̸� �̿��� height�� ���Ѵ�

	m = (maze*)malloc(sizeof(maze) * width * height); //m�迭�� width*height ��ŭ �޸𸮸� �������� �Ҵ��Ѵ�.

	int i, j; //�ݺ����� �����ϱ� ���� ����; LinesofFile�� ����� .maz������ ������ ���� 
	int count1, count2; //�ݺ����� �����ϱ� ���� ����; LinesofFile�� ����� .maz������ ���� �̷��� ĭ�� �ش��ϴ� ������ ���� 
	int num = 0; //�̷��� �� ĭ�� ���� ����

	//i�� LinesofFIle���� ���ǹ��� ĭ�� Ž���ϱ� ���� 2ĭ�� ���� count1�� 1�� �����Ͽ� width�� ������ ������
	for (i = 1, count1 = 0; count1 < height; i = i + 2, count1++) { 
		//j�� LinesofFIle���� ���ǹ��� ĭ�� Ž���ϱ� ���� 2ĭ�� ���� count2�� 1�� �����Ͽ� height�� ������ ������
		for (j = 1, count2 = 0; count2 < width; j = j + 2, count2++) {
			//up
			if (LinesofFile[i - 1][j] == ' ')  //���� ĭ�� ���� ���� ���ٸ�
				m[num].up = 1; 
			else ////���� ĭ�� ���� ���� �ִٸ�
				m[num].up = 0;
			//down
			if (LinesofFile[i + 1][j] == ' ')  //���� ĭ�� �Ʒ��� ���� ���ٸ�
				m[num].down = 1;
			else //���� ĭ�� �Ʒ��� ���� �ִٸ�
				m[num].down = 0;
			//right
			if (LinesofFile[i][j + 1] == ' ')  //���� ĭ�� ������ ���� ���ٸ�
				m[num].right = 1;
			else //���� ĭ�� ������ ���� �ִٸ�
				m[num].right = 0;
			//left
			if (LinesofFile[i][j - 1] == ' ')  //���� ĭ�� ���� ���� ���ٸ�
				m[num].left = 1;
			else //���� ĭ�� ���� ���� �ִٸ�
				m[num].left = 0;

			num++; //���� ĭ�� �����¿츦 ��� ���ǰ� ���� ĭ���� �Ѿ 
		}
	}

	file.close(); //���� �б⸦ �Ϸ��ϸ� ������ �ݾ��ش�
		
}

void ofApp::Set_Hint() { //hint�� ������ ��ġ�� �ʱ�ȭ�� �Լ�
	if (width * height < 50) // width*height�� 50�̸��̸�
		hintNo = 1; //hint�� 1��
	else if (width * height < 100) // width*height�� 50�̻� 100�̸��̸�
		hintNo = 2; //hint�� 2��
	else if (width * height < 150) // width*height�� 100�̻� 150�̸��̸�
		hintNo = 3; //hint�� 3��
	else if (width * height < 200) // width*height�� 150�̻� 200�̸��̸�
		hintNo = 4; //hint�� 4��
	else hintNo = 5; // width*height�� 200�̻��̸� hint�� 5��

	hint = (POINTER*)malloc(sizeof(POINTER) * hintNo); //hint�迭�� hintNo��ŭ �޸𸮸� �������� �Ҵ��Ѵ�.
	hintX = (float*)malloc(sizeof(float) * hintNo); //hintX�迭�� hintNo��ŭ �޸𸮸� �������� �Ҵ��Ѵ�.
	hintY = (float*)malloc(sizeof(float) * hintNo); //hintY�迭�� hintNo��ŭ �޸𸮸� �������� �Ҵ��Ѵ�.

	for (int i = 0; i < hintNo; i++) { //��Ʈ�� ������ŭ
		int rad = (rand() % (width * height - 2)) + 1; //��Ʈ�� ��ġ�� �������� �����Ѵ�(1~(width*height-2)); ������� ������ ����
		hint[i].getnum(rad); //�������� ���� ��ġ�� hint�� data�� �����Ѵ�.
	}
}

int ofApp::Check_Same(int num) { //num�� ��ġ�� hint�� ��ġ�� �������� �Ǵ�; ������ ���� ��Ʈ�� ��ȣ�� ��ȯ, �ƴϸ� -1 ��ȯ
	int i; //�ݺ����� �����ϱ� ���� ����
	for (i = 0; i < hintNo; i++) { //��� ��Ʈ�� ��
		if (num == hint[i].num()) //num�� ��ġ�� hint�� ��ġ�� ���ٸ� break
			break;
	}
	if (i == hintNo) //num�� ��ġ�� ��� hint�� ��ġ�� �޶��� ��� -1�� ��ȯ
		return -1;
	else //�ϳ��� ���� ��ġ�� �־��ٸ� �� ��ġ�� hint��ȣ�� ��ȯ(0~hintNo)
		return i;
}

void ofApp::Set_Attack() { //attacker�� ������ ��ġ�� �ʱ�ȭ�� �Լ�
	if (width * height < 50)// width*height�� 50�̸��̸�
		attackNo = 1; //attacker�� 1��
	else if (width * height < 100) // width*height�� 50�̻� 100�̸��̸�
		attackNo = 2; //attacker�� 2��
	else if (width * height < 150) // width*height�� 100�̻� 150�̸��̸�
		attackNo = 3; //attacker�� 3��
	else if (width * height < 200) // width*height�� 150�̻� 200�̸��̸�
		attackNo = 4; //attacker�� 4��
	else attackNo = 5; // width*height�� 200�̻��̸� attacker�� 5��

	attacker = (POINTER*)malloc(sizeof(POINTER) * attackNo); //attacker�迭�� attackNo��ŭ �޸𸮸� �������� �Ҵ��Ѵ�.
	attackerX = (float*)malloc(sizeof(float) * attackNo); //attackerX�迭�� attackNo��ŭ �޸𸮸� �������� �Ҵ��Ѵ�.
	attackerY = (float*)malloc(sizeof(float) * attackNo); //attackerY�迭�� attackNo��ŭ �޸𸮸� �������� �Ҵ��Ѵ�.

	int i = 0; //�ݺ����� �����ϱ� ���� ���� 
	while (i < attackNo) {// ��� attacker�鿡 ����
		int rad = (rand() % (width * height - 2)) + 1; //��Ʈ�� ��ġ�� �������� �����Ѵ�(1~(width*height-2)); ������� ������ ����
		if(Check_Same(rad)>=0) //���� �������� ���� attacker�� ��ġ�� ��� �ϳ��� hint�� ��ģ�ٸ� �ٽ� ��ġ�� ����
			continue;
		else { //��� hint�� ��ġ�� ��ġ�� �ʴ´ٸ� 
			attacker[i].getnum(rad); //attacker�� data�� ��ġ�� �����ϰ�
			i++; //���� attacker�� ��ġ�� ������
		}
	}
}
void ofApp::Move_Attack() { //attacker�� �����̰� �� �Լ�
	int i;//�ݺ����� �����ϱ� ���� ����
	for (i = 0; i < attackNo; i++) { // ��� attacker�鿡 ����
		int loc = attacker[i].num(); //attacker�� ��ġ�� ���� loc�� ����
		int count=0; //�Ʒ��� while���� ����loop�� �����ʰ� �ϱ� ���� ����
		int dir; //attacker�� ���ư� ������ ��Ÿ���� ����
		
		while (1) {
			dir = rand() % 4; //attacker�� ������ ������ �������� ����(0:up/1:down/2:right/3:left�� ����)
			if (dir == 0 && m[loc].up == 1 && Check_Same(loc - width) < 0) { //dir�� 0�϶� ���� ���� �շ������� �� ĭ�� hint�� ��ġ������ �ʴ� ���
				loc -= width; //loc�� ������ width��ŭ ���ش�
				break;
			}
			else if (dir == 1 && m[loc].down == 1 && Check_Same(loc + width) < 0) { //dir�� 1�϶� �Ʒ��� ���� �շ������� �Ʒ� ĭ�� hint�� ��ġ������ �ʴ� ���
				loc += width; //loc�� ������ width��ŭ �����ش�
				break;
			}
			else if (dir == 2 && m[loc].right == 1 && Check_Same(loc + 1) < 0) { //dir�� 2�϶� ������ ���� �շ������� ������ ĭ�� hint�� ��ġ������ �ʴ� ���
				loc += 1; //loc�� ������ 1��ŭ �����ش�
				break;
			}
			else if (dir == 3 && m[loc].left == 1 && Check_Same(loc - 1) < 0) { //dir�� 3�϶� ���� ���� �շ������� ���� ĭ�� hint�� ��ġ������ �ʴ� ���
				loc -= 1;  //loc�� ������ 1��ŭ ���ش�
				break;
			}
			count++; //���� ���� ��쿡 �ش����� ���ϴ� ����� �ٽ� �̵��� �õ��Ѵ�
			if (count > 4) //���� �̵� �õ��� 4���� �ʰ��ߴٸ� �̵����� �ʵ����Ѵ� ;���� loop�� �����Ǵ°� �����Ѵ�
				break;
		}
			
		attacker[i].getnum(loc); //attacker�� data�� ���ο� ��ġ�� �����Ѵ�
		if (loc == point.num()) //attacker�� �� ��ġ�� point�� �������� 
			isGameOver = 1; //isGameOver flag�� 1�� �����Ѵ�
	}
}

void ofApp::Meet_Hint() { //point�� hint�� ������ �� ������ ��Ÿ���� �Լ�
	int num = Check_Same(point.num()); //point�� ��ġ�� hint�� �� �ϳ��� ���������� Ȯ���Ͽ� num�� ���� �����Ѵ�
	if (num>=0) { //num>=0�̶�� point�� ������ hint�� �����Ѵٴ� �ǹ��̹Ƿ�
		isMeet = 1; //isMeet flag�� 1�� ����
		meetX = hintX[num]; //�� hint�� x��ǥ�� meetX�� ����
		meetY = hintY[num]; //�� hint�� y��ǥ�� meetY�� ����
		hint[num].getnum(-1); //�� hint�� ���̻� ����� �� �����Ƿ� �����͸� ������ -1�� �����Ѵ�
	}
}

void ofApp::explosion(float x, float y) { //point�� attacker�� hint, �������� ������ �� (x,y)��ǥ���� �ð����� ȿ���� �ִ� �Լ�
	int num = 10; //������ ������ ��Ÿ���� ���� 
	for (int r = 0; r < num; r++) { //������ ������ŭ
		float radi = ofRandom(2, 10); //�������� ���̴� 2~10���̷� random�ϰ� ����
		float xOffset = ofRandom(-20, 20); //������ �׷��� ��ġ�� x��ǥ�� -20~20���̷� random�ϰ� ����
		float yOffset = ofRandom(-20, 20); //������ �׷��� ��ġ�� y��ǥ�� -20~20���̷� random�ϰ� ����
		ofDrawCircle(x + xOffset,y + yOffset, radi); //������ ��ġ�� ���� �׷� ������ �ð������� ǥ�� 
	}
}

void ofApp::reset() { //��� flag���� �ʱ�ȭ �ϰ� �޸𸮸� �����ϴ� �Լ�
	isOpen = 0; //isOpen flag�� 0���� �ʱ�ȭ
	isStart = 0; //isStart flag�� 0���� �ʱ�ȭ
	isGoal = 0; //isGoal flag�� 0���� �ʱ�ȭ
	isAttack = 0; //isAttack flag�� 0���� �ʱ�ȭ
	isHint = 0; //isHint flag�� 0���� �ʱ�ȭ
	isPause = 0; //isPause flag�� 0���� �ʱ�ȭ
	isClear = 0; //isClear flag�� 0���� �ʱ�ȭ
	isGameOver = 0; //isGameOver flag�� 0���� �ʱ�ȭ
	width = 0; //width�� 0���� �ʱ�ȭ
	height = 0; //height�� 0���� �ʱ�ȭ
	point.getnum(0); //point�� ��ġ�� 0���� �ʱ�ȭ
	freeMemory(); //�������� �Ҵ��� �޸𸮸� �����ϴ� �Լ�
}

void ofApp::freeMemory() { // malloc�� memory���� free���ִ� �Լ�

	free(m); //m�� �޸𸮸� ����
	free(attacker); //attacker�� �޸𸮸� ����
	free(attackerX); //attackerX�� �޸𸮸� ����
	free(attackerY); //attackerY�� �޸𸮸� ����
	free(hint); //hint�� �޸𸮸� ����
	free(hintX); //hintX�� �޸𸮸� ����
	free(hintY); //hintY�� �޸𸮸� ����

}

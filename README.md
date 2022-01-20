# Maze_Escape_Game
OpenFrameworks를 이용한 미로 탈출 게임
 
#### environment
window 8.1   
openfreameworks v0.11.0 vs2017  
visual studio 2019  

#### 실행방법
1.OpenFrameworks projectGenerator를 이용해 프로젝트를 생성한다.  
2. stage1.maz ,stage2.maz, stage3.maz, stage4.maz, stage5.maz, Verdana.ttf 파일을 프로젝트의 bin폴더 내의 data폴더에 넣는다.  
3. main.cpp, ofApp.cpp, ofApp.h, pointer.cpp, pointer.h 파일을 프로젝트의 src폴더에 넣는다.  

#### 게임 진행 방법
방향키:  미로에서 길이 뚫려 있을 경우 각 방향으로 point가 움직인다.  
‘d’ :  stage 1에서 게임을 시작하기 전 미로를 그려준다.  
‘s’ :  stage 1에서 point와 attacker, hint를 그려주고 게임을 시작한다.  
‘r’ :  game over 상태에서 현재 stage를 다시 도전한다.  
‘p’ :  게임을 일시 정지한다.  
‘j’ :  일시 정지상태에서 게임의 다음 stage로 점프한다.  
‘y’ :  stage clear 상태에서 다음 stage로의 게임을 이어서 진행한다.  
‘n’ :  stage clear또는 game over 상태에서 프로그램을 종료한다.  
Esc키 :  언제든지 게임을 종료한다.  

###### 1. 초기화 & 게임 시작
먼저 실행시키면 흰색 아무것도 없는 window창이 생성된다.  
이 상태에서 'd'키를 누르면 미로구조가 화면에 그려진다.  
여기서 's'키를 누르면 하늘색 원으로 point와 빨간색 원으로 attacker, 노란색 원으로 hint, 초록색 사각형으로 도착점이 화면에 그려진다.  
'd','s'키는 stage1에서 처음 게임을 시작할 때만 작동하고 나머지 stage에서는 자동으로 게임이 시작된다.  

###### 2. 게임 진행
현재 상태에서 키보드의 방향키를 조작하면 미로의 벽으로 막혀있지 않은 경우 point가 움직이게 된다.  
미로 내부에서 키를 이용해 이동하다가 attacker를 만나게 될 경우 game over가 된다.  
game over인 경우에는 두가지 선택지가 있다. 'r'키를 눌러 현재 stage를 다시 게임을 진행하거나 'n'을 눌러 프로그램을 종료할 수 있다.  

###### 3. stage clear
미로에서 도착점에 도달하면 stage clear가 된다.  
이때 1~4단계의 경우에는 두가지 선택지가 존재한다. 'y'키를 눌러 다음stage로 게임을 진행하거나 'n'을 눌러 프로그램을 종료할 수 있다.  
stage5에서 도착점에 도달하시면 'y'키가 작동을 하지 않고 'n'을 눌러 프로그램을 종료할 수 있다.  

###### 4. 유의 사항
stage clear나 game over가 아닌 상태에서는 'p'키를 눌러 일시 정지할 수 있다.  
1~4단계의 일시 정지상태에서는 두가지 선택지가 있다.  
다시 'p'를 누르면 게임을 계속해서 진행할 수 있고 'j'를 누르면 다음 stage로 바로 jump할 수 있다.    
stage5에서는 'p'를 눌러 일시 정지 상태가 되더라도 다시 'p'키를 눌러 게임을 계속할 수는 있지만 'j'키는 작동하지 않는다.     
 

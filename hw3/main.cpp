#include <iostream>
#include <cmath>
#include "SMFLoader.h"	// (1)  Include header file 
#include <GL/freeglut.h>
using namespace std;

GLfloat spin = 0;
GLfloat x = 50, y = 50, z = 50;
GLfloat A1sy = 0;
GLfloat p = 1.0;
GLfloat A2sx = 0, A2sy = 0, A2sz = 0;
GLfloat R = 1.0, G = 0.0, B = 1.0;
int cnt = 1;
bool isClaw = false;
bool isLight = true;


// 太陽光源
const GLfloat lightPosition[] = { 500.0, 500.0, 300.0, 1.0 }; // 光源位置
const GLfloat lightAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // 環境光
const GLfloat lightDiffuse[] = { 0.8, 0.8, 0.8, 1.0 }; // 漫反射光
const GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // 鏡面光


// duck材質
GLfloat matAmbient[] = { 0.5, 0.5, 0.0, 1.0 }; // 環境
GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // 鏡面
GLfloat matDiffuse[] = { 1.0, 1.0, 0.0, 1.0 }; // 漫反射
GLfloat matShininess[] = { 50.0 }; // 光澤
// 地面
GLfloat FmatAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // 環境
GLfloat FmatSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // 鏡面
GLfloat FmatDiffuse[] = { 0.0, 1.0, 0.0, 1.0 }; // 漫反射
GLfloat FmatShininess[] = { 100.0 }; // 光澤
// arm材質
GLfloat AmatAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // 環境
GLfloat AmatSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // 鏡面
GLfloat AmatDiffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // 漫反射
GLfloat AmatShininess[] = { 100.0 }; // 光澤

// 繪製地面
void drawFloor()
{
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, FmatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FmatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FmatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, FmatShininess);

	glTranslatef(0.0, -2.0, 0.0);
	glScalef(2000, 1, 2000);
	glutSolidCube(1);

	glPopMatrix();
}

// 機械手臂各部件
void drawBase() // 底座
{
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0); // 平放
	glutSolidCylinder(100.0, 10.0, 20, 20);
	glPopMatrix();
}

void drawArm1() // 上臂
{
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0); // 平放
	glutSolidCylinder(20.0, 150.0, 20, 20);
	glPopMatrix();
}

void drawArm2() // 前臂
{
	glPushMatrix();

	glRotatef(90.0, 1.0, 0.0, 0.0); // 平放
	glutSolidCylinder(10.0, 150.0, 20, 20);
	glPopMatrix();
}

void drawClaw() //夾子
{
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0); // 平放
	glutSolidCylinder(30.0, 10.0, 20, 20);
	glPopMatrix();
	// 開關控制
	if (!isClaw) // 打開
	{
		glPushMatrix();
		glTranslatef(-20, 15, 0);
		glScalef(10, 30, 30);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(20, 15, 0);
		glScalef(10, 30, 30);
		glutSolidCube(1);
		glPopMatrix();
	}
	else // 合起來
	{
		glPushMatrix();
		glTranslatef(-5, 15, 0);
		glScalef(10, 30, 30);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5, 15, 0);
		glScalef(10, 30, 30);
		glutSolidCube(1);
		glPopMatrix();
	}



}

// 繪製機械手臂
void display_arm()
{
	glPushMatrix();
	// 材質設定
	glMaterialfv(GL_FRONT, GL_AMBIENT, AmatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, AmatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, AmatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, AmatShininess);

	// 畫底座
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(x, y, z); // 位置移動
	drawBase();
	// 畫上臂
	glTranslatef(0, 150, 0); 
	glRotatef(A1sy, 0.0, 1.0, 0.0); // 沿y軸旋轉
	drawArm1(); 
	// 畫前臂
	glRotatef(A2sx, 1.0, 0.0, 0.0); // 沿x軸旋轉
	glRotatef(A2sy, 0.0, 1.0, 0.0); // 沿y軸旋轉
	glRotatef(A2sz, 0.0, 0.0, 1.0); // 沿z軸旋轉
	glTranslatef(0, 150, 0);
	drawArm2();
	// 畫夾子
	glTranslatef(0, 10, 0);
	drawClaw();
	glPopMatrix();


}

// 繪製鴨子
void display_duck()
{
	
	SMFLoader loader;   //(2) declare SMFLoader
	const char* ducky = "./ducky.smf";
	loader.load(ducky);	// (3) Load model file contant

	//	(4) Draw model
	
	float* vertex = NULL;
	float* color = NULL;
	glTranslatef(x, y + 150, z); // 從原點移到x y+150 z

	glPushMatrix();
	// 轉正
	glRotatef(spin, 0.0, -1.0, 0.0);
	glTranslatef(400, 0, 0);
	// 材質設定
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	
	// 從SMFL讀入
	for(int i=0;i<loader.getFaceSize();i++)	//每一迴圈畫一個三角面
	{
		// 得到一個面上的3個點  總共9個數值
		// { x1,y1,z1,x2,y2,z2,x3,y3,z3 }
		vertex = loader.getFace(i);
		//cout << vertex[0] << endl;
		// 得到一個面上的每個點的顏色 總共9個數值
		// { r1,g1,b1,r2,g2,b2,r3,g3,b3 }
		color = loader.getFaceColor(i);

		// 以三角形繪製鴨子
		glBegin(GL_TRIANGLES);

		if(color)
			glColor3f(vertex[0],vertex[1],vertex[2]);
		glVertex3f(vertex[0],vertex[1],vertex[2]);

		if(color)
			glColor3f(vertex[3],vertex[4],vertex[5]);
		glVertex3f(vertex[3],vertex[4],vertex[5]);

		if(color)
			glColor3f(vertex[6],vertex[7],vertex[8]);
		glVertex3f(vertex[6],vertex[7],vertex[8]);

		glEnd();
	}

	glPopMatrix();

	
}

// 畫面呈現
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 100, 250, 0, 0, 0, 0, 1, 0); // 攝影機視點
	
	glPushMatrix();
	// 聚光燈
	GLfloat spotPosition[] = { x, 512.0, z, 1.0 }; // 光源位置
	GLfloat spotAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // 環境光
	GLfloat spotDiffuse[] = { R, G, B, 1.0 }; // 漫反射光
	GLfloat spotSpecular[] = { 0.0, 1.0, 0.0, 1.0 }; // 鏡面光
	GLfloat spotDirectoin[] = { 0.0, -1.0, 0.0 }; // 打光方向
	GLfloat spotExponent[] = { 0.5 }; // 聚光指數
	GLfloat spotCutoff[] = { 30.0 }; // 聚光截止夾角
	// 開啟聚光燈
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirectoin); // 設置點光源
	glLightfv(GL_LIGHT1, GL_POSITION, spotPosition); // 設置光源位置
	//glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent); // 設置聚光指數
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff); // 設置截止夾角
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotDiffuse); // 設置漫射光
	glLightfv(GL_LIGHT1, GL_SPECULAR, spotSpecular); // 設置反射光
	glLightfv(GL_LIGHT1, GL_AMBIENT, spotAmbient); // 設置環境光
	glEnable(GL_LIGHTING);
	if (isLight)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
	

	drawFloor(); // 畫地板
	display_arm(); // 畫機械手臂
	display_duck(); // 畫鴨子
	
	glPopMatrix();
	glFlush();

	Sleep(0.2);
}

// 鴨子旋轉
void Idle()
{
	spin += 20.0;
	if (spin >= 360.0)
		spin = 0.0;
	display();
}

// 調整畫面大小
void reshape(int w, int h)
{
	glViewport(0.0, 0.0, w, h);
}

// 滑鼠控制
void mouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mx -= 400;
		my -= 400;
		// 計算手臂角度
		if (mx == x)
			A2sz = 90;
		else
			A2sz = atan((my - y) / (mx - x))* 180.0 / 3.14;
		//cout << mx << " " << my << endl;
		
		if (A2sz >= 0)
			A2sz = 90 - A2sz;
		else
			A2sz = -(90 + A2sz);
		//cout << A2sz << endl;
		display();
		isClaw = !isClaw;
		display();
		isClaw = !isClaw;
		//cout << A2sz << endl;
	}

}

// 鍵盤控制
void keyboard(unsigned char key, int kx, int ky)
{
	// 滑鼠控制模式
	if (key == 'p')
		glutMouseFunc(mouse);
	else
		switch (key)
		{
		// 關閉視窗
		case 27:
			exit(0);
			break;

		// 手臂移動
		case 'w':
			z -= 100;
			display();
			break;
		case 's':
			z += 100;
			display();
			break;
		case 'a':
			x -= 100;
			display();
			break;
		case 'd':
			x += 100;
			display();
			break;

		// 手臂旋轉
		case 'z':
			A1sy += 30;
			if (A1sy >= 360.0)
				A1sy = 0.0;
			display();
			break;
		case 'x':
			A2sx += 30;
			if (A2sx >= 360.0)
				A2sx = 0.0;
			display();
			break;
		case 'c':
			A2sy += 30;
			if (A2sy >= 360.0)
				A2sy = 0.0;
			display();
			break;
		case 'v':
			A2sz += 30;
			if (A2sz >= 360.0)
				A2sz = 0.0;
			display();
			break;

		// 夾子夾一下
		case 'f':
			isClaw = !isClaw;
			display();
			isClaw = !isClaw;
			display();
			break;

		// 開關聚光燈
		case 'l':
			isLight = !isLight;
			display();
			break;
		
		// 聚光燈顏色
		case 'g':
			if (cnt == 0) // 紫光
			{
				R = 1;
				G = 0;
				B = 1;
				cnt += 1;
			}
			else if (cnt == 1) // 紅光
			{
				R = 1;
				G = 0;
				B = 0;
				cnt += 1;
			}
			else if (cnt == 2) // 綠光
			{
				R = 0;
				G = 1;
				B = 0;
				cnt += 1;
			}
			else if (cnt == 3) // 藍光
			{
				R = 0;
				G = 0;
				B = 1;
				cnt = 0;
			}
			display();
			break;
		}

		
}

void Init()
{
	glClearColor(0.3, 0.3, 0.3, 1.0); // 背景色
	glClearDepth(1.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1024.0, 1024.0, -1024.0, 1024.0, -1024.0, 1024.0);

	// 設置太陽光
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); // 設置光源位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient); // 設置環境光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse); // 設置漫射光
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); // 設置反射光

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	//glutInitWindowPosition(150, 150);
	glutCreateWindow("Ducky");
	Init();
	glutDisplayFunc(display);
	glutIdleFunc(Idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	//glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}

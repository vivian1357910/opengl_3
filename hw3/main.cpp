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


// �Ӷ�����
const GLfloat lightPosition[] = { 500.0, 500.0, 300.0, 1.0 }; // ������m
const GLfloat lightAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // ���ҥ�
const GLfloat lightDiffuse[] = { 0.8, 0.8, 0.8, 1.0 }; // ���Ϯg��
const GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // �譱��


// duck����
GLfloat matAmbient[] = { 0.5, 0.5, 0.0, 1.0 }; // ����
GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // �譱
GLfloat matDiffuse[] = { 1.0, 1.0, 0.0, 1.0 }; // ���Ϯg
GLfloat matShininess[] = { 50.0 }; // ���A
// �a��
GLfloat FmatAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // ����
GLfloat FmatSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // �譱
GLfloat FmatDiffuse[] = { 0.0, 1.0, 0.0, 1.0 }; // ���Ϯg
GLfloat FmatShininess[] = { 100.0 }; // ���A
// arm����
GLfloat AmatAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // ����
GLfloat AmatSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // �譱
GLfloat AmatDiffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // ���Ϯg
GLfloat AmatShininess[] = { 100.0 }; // ���A

// ø�s�a��
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

// ������u�U����
void drawBase() // ���y
{
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0); // ����
	glutSolidCylinder(100.0, 10.0, 20, 20);
	glPopMatrix();
}

void drawArm1() // �W�u
{
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0); // ����
	glutSolidCylinder(20.0, 150.0, 20, 20);
	glPopMatrix();
}

void drawArm2() // �e�u
{
	glPushMatrix();

	glRotatef(90.0, 1.0, 0.0, 0.0); // ����
	glutSolidCylinder(10.0, 150.0, 20, 20);
	glPopMatrix();
}

void drawClaw() //���l
{
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0); // ����
	glutSolidCylinder(30.0, 10.0, 20, 20);
	glPopMatrix();
	// �}������
	if (!isClaw) // ���}
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
	else // �X�_��
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

// ø�s������u
void display_arm()
{
	glPushMatrix();
	// ����]�w
	glMaterialfv(GL_FRONT, GL_AMBIENT, AmatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, AmatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, AmatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, AmatShininess);

	// �e���y
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(x, y, z); // ��m����
	drawBase();
	// �e�W�u
	glTranslatef(0, 150, 0); 
	glRotatef(A1sy, 0.0, 1.0, 0.0); // �uy�b����
	drawArm1(); 
	// �e�e�u
	glRotatef(A2sx, 1.0, 0.0, 0.0); // �ux�b����
	glRotatef(A2sy, 0.0, 1.0, 0.0); // �uy�b����
	glRotatef(A2sz, 0.0, 0.0, 1.0); // �uz�b����
	glTranslatef(0, 150, 0);
	drawArm2();
	// �e���l
	glTranslatef(0, 10, 0);
	drawClaw();
	glPopMatrix();


}

// ø�s�n�l
void display_duck()
{
	
	SMFLoader loader;   //(2) declare SMFLoader
	const char* ducky = "./ducky.smf";
	loader.load(ducky);	// (3) Load model file contant

	//	(4) Draw model
	
	float* vertex = NULL;
	float* color = NULL;
	glTranslatef(x, y + 150, z); // �q���I����x y+150 z

	glPushMatrix();
	// �ॿ
	glRotatef(spin, 0.0, -1.0, 0.0);
	glTranslatef(400, 0, 0);
	// ����]�w
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	
	// �qSMFLŪ�J
	for(int i=0;i<loader.getFaceSize();i++)	//�C�@�j��e�@�ӤT����
	{
		// �o��@�ӭ��W��3���I  �`�@9�Ӽƭ�
		// { x1,y1,z1,x2,y2,z2,x3,y3,z3 }
		vertex = loader.getFace(i);
		//cout << vertex[0] << endl;
		// �o��@�ӭ��W���C���I���C�� �`�@9�Ӽƭ�
		// { r1,g1,b1,r2,g2,b2,r3,g3,b3 }
		color = loader.getFaceColor(i);

		// �H�T����ø�s�n�l
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

// �e���e�{
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 100, 250, 0, 0, 0, 0, 1, 0); // ��v�����I
	
	glPushMatrix();
	// �E���O
	GLfloat spotPosition[] = { x, 512.0, z, 1.0 }; // ������m
	GLfloat spotAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // ���ҥ�
	GLfloat spotDiffuse[] = { R, G, B, 1.0 }; // ���Ϯg��
	GLfloat spotSpecular[] = { 0.0, 1.0, 0.0, 1.0 }; // �譱��
	GLfloat spotDirectoin[] = { 0.0, -1.0, 0.0 }; // ������V
	GLfloat spotExponent[] = { 0.5 }; // �E������
	GLfloat spotCutoff[] = { 30.0 }; // �E���I���
	// �}�һE���O
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirectoin); // �]�m�I����
	glLightfv(GL_LIGHT1, GL_POSITION, spotPosition); // �]�m������m
	//glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent); // �]�m�E������
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff); // �]�m�I���
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotDiffuse); // �]�m���g��
	glLightfv(GL_LIGHT1, GL_SPECULAR, spotSpecular); // �]�m�Ϯg��
	glLightfv(GL_LIGHT1, GL_AMBIENT, spotAmbient); // �]�m���ҥ�
	glEnable(GL_LIGHTING);
	if (isLight)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
	

	drawFloor(); // �e�a�O
	display_arm(); // �e������u
	display_duck(); // �e�n�l
	
	glPopMatrix();
	glFlush();

	Sleep(0.2);
}

// �n�l����
void Idle()
{
	spin += 20.0;
	if (spin >= 360.0)
		spin = 0.0;
	display();
}

// �վ�e���j�p
void reshape(int w, int h)
{
	glViewport(0.0, 0.0, w, h);
}

// �ƹ�����
void mouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mx -= 400;
		my -= 400;
		// �p����u����
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

// ��L����
void keyboard(unsigned char key, int kx, int ky)
{
	// �ƹ�����Ҧ�
	if (key == 'p')
		glutMouseFunc(mouse);
	else
		switch (key)
		{
		// ��������
		case 27:
			exit(0);
			break;

		// ���u����
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

		// ���u����
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

		// ���l���@�U
		case 'f':
			isClaw = !isClaw;
			display();
			isClaw = !isClaw;
			display();
			break;

		// �}���E���O
		case 'l':
			isLight = !isLight;
			display();
			break;
		
		// �E���O�C��
		case 'g':
			if (cnt == 0) // ����
			{
				R = 1;
				G = 0;
				B = 1;
				cnt += 1;
			}
			else if (cnt == 1) // ����
			{
				R = 1;
				G = 0;
				B = 0;
				cnt += 1;
			}
			else if (cnt == 2) // ���
			{
				R = 0;
				G = 1;
				B = 0;
				cnt += 1;
			}
			else if (cnt == 3) // �ť�
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
	glClearColor(0.3, 0.3, 0.3, 1.0); // �I����
	glClearDepth(1.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1024.0, 1024.0, -1024.0, 1024.0, -1024.0, 1024.0);

	// �]�m�Ӷ���
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); // �]�m������m
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient); // �]�m���ҥ�
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse); // �]�m���g��
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); // �]�m�Ϯg��

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

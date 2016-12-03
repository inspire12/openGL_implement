#include <Windows.h>
#include<glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <math.h>
#include <stdio.h>
#include "resource.h"
typedef struct color {
	double r;
	double g;
	double b;
}color;
static double Power[2] = { 1000, 1000 }; 
static double moveAX = 0.4, moveAH = 0.4, rotateA = 1, accA = 1;
double size = 1;
static double moveBX = -0.4, moveBH = 0.4, rotateB = 1, accB = 1;

void initLight();
void reshape(int w, int h);

// 시간 가는 거 즉, 회전하는 것과 힘을 조금씩 줄이는 것
void timeGoesOn() {
	moveAX = (moveAX - 1);
	if (moveAX > 360) moveAX -= 360;
	moveBX = (moveBX - 1);
	if (moveBX > 360) moveBX -= 360;
	Sleep(20);
	glutPostRedisplay();
}

//팽이 만드는 것, 위치와 크기, 회전까지 

void makeArena() {
	// 지형을 그립니다.
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUAD_STRIP);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);

		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
}
void makeSpinTop(double move, double moveZ, int rv) {
	glLoadIdentity();
	gluLookAt(0.3, 0.15, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	//	gluLookAt(0.1, 0., 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

	glTranslatef(0.0, 0.0, moveZ);		//상하 움직임

	double distance = size - moveZ;

	glRotatef((GLfloat)move, 0.0, 0.0, 1.0);//좌우 움직임
	glTranslatef(sqrt(distance), sqrt(distance), 0.0);	//distance 값 계산 필요 경기장 위치의 반지름

	glRotatef((GLfloat)rv, 0.0, 1.0, 0.0); //회전 
	glColor3f(3, 0, 1);
	glutSolidCone(0.03, 0.05, 80, 80); //원뿔 출력
}

void MyDisplay() {
	initLight();

	gluLookAt(0.3, 0.15, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
//	makeArena();
	//glutSolidSphere((GLdouble)0.3, 2000, 1600); // 태양을 그려냄
	//경기장 그리기!
	glPushMatrix(); 
	//for (int i = 0; i<8; i++) {
	
		makeSpinTop(moveAX, moveAH, rotateA);
		makeSpinTop(moveBX, moveBH, rotateB);
	//}
	timeGoesOn();
	glPopMatrix();
	glutSwapBuffers();
}

bool buffer[256];

void MyKeyboard(unsigned char key, int x, int y) {
	buffer[key] = true;

	switch (key) {
	case 'd':
		moveBX = (moveBX + 5);
		if (moveBX > 360) moveBX -= 360;
		glutPostRedisplay();
		break;
	case 's':
		moveBH = (moveBH + 0.01);
		if (moveBH>size) moveBH = (moveBH - 0.01);
		glutPostRedisplay();
		break;
	case 'a':
		moveBX = (moveBX - 5);
		if (moveBX > 360) moveBX -= 360;
		glutPostRedisplay();
		break;
	case 'w':
		moveBH = (moveBH - 0.01);
		if (moveBH<0) moveBH = (moveBH + 0.01);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void inputKey(int key, int x, int y)
{
	fflush(stdin);
	switch (key)
	{
	case GLUT_KEY_LEFT:
		moveAX = (moveAX - 5);
		if (moveAX > 360) moveAX -= 360;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		moveAX = (moveAX + 5);
		if (moveAX > 360) moveAX -= 360;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		moveAH = (moveAH - 0.01);
		if (moveAH<0) moveAH = (moveAH + 0.01);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		moveAH = (moveAH + 0.01);
		if (moveAH>size) moveAH = (moveAH - 0.01);
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 1200);

	glutCreateWindow("Solar System");
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(reshape);
	glMatrixMode(GL_PROJECTION);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(inputKey);
	//timeGoesOn();
	glutMainLoop();

	return 0;
}

void initLight() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	// 빛 설정
	glEnable(GL_COLOR_MATERIAL);	//색깔 주기
	glEnable(GL_DEPTH_TEST);	//깊이 비교
	glEnable(GL_CULL_FACE);		//은면 제거
	glEnable(GL_SMOOTH);	//좀 더 자연스런 빛표현 위해
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position); //광원의 위치 설정하는 param
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);	//주변광을 설정하는 param
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);	//난반사 설정하는 param
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);	//정반사 설정하는 param
}

void reshape(int w, int h) {
	float ratio = 1;
	glViewport(0, 100, w, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(0, ratio, 1, 1);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

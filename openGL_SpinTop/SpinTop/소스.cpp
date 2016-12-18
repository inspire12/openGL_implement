#include <Windows.h>
#include<glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <math.h>
#include <stdio.h>
#include "resource.h"
#include "imageloader.h"
#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "glaux.lib")
#define spinTL 0.00001;
#define spinBL 0.06;

typedef struct SpinInfo {
	double moveX; //����
	double moveZ;
	int rotate;
	double vR;//���ӵ� ��ȭ��
	double power;
	double m;
} Spin;

GLuint _textureId[2]; //The id of the textur
GLUquadricObj *quad;

double gymSize = 1;
Spin player[2];

void initLight();
void reshape(int w, int h);
unsigned int ids[2];
GLuint loadTexture(Image* image);
void initRendering();
int time = 1;

void SetSpin() {
	player[0].moveX = 0.1;
	player[0].moveZ = 0.6;
	player[0].vR = -1;
	player[0].rotate = 7000;

	
	player[1].moveX = -0.5;
	player[1].moveZ = 0.6;
	player[1].vR = 1;
	player[1].rotate = 7000;
}


// �ð� ���� �� ��, ȸ���ϴ� �Ͱ� ���� ���ݾ� ���̴� ��/
void timeGoesOn() {
	for (int i = 0; i < 2; i++) {
		player[i].moveX += player[i].vR;
		player[i].rotate -= 0.0000000001;
	}

	if (player[0].rotate <= 0&& player[1].rotate <= 0) {
		printf("������ �������ϴ�. ���º��Դϴ�..");
		Sleep(2000);
		exit(0);
	}
	if (player[0].rotate <= 0) {
		printf("������ �������ϴ�. player 1�� �¸��Դϴ�.");
		//exit(0);
	}
	if (player[1].rotate <= 0) {
		printf("������ �������ϴ�. player 2�� �¸��Դϴ�.");
		//exit(0);
	}
	Sleep(20);
	glutPostRedisplay();
}



void makeArena() {
	// ������ �׸��ϴ�.
	glColor3f(0.9f, 0.9f, 0.9f);
//	glutWireTorus();
}


//���� ����� ��, ��ġ�� ũ��, ȸ������ 
void makeSpinTop(double move, double moveZ, int rv,int i) {
	glLoadIdentity();
	glPushMatrix();
	gluLookAt(0, 0, 0, 
		10, 4, 4, 
		1.0, 1.0, -1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId[i]); /* specify the texture to be used */
												 /* Auto-generation of texture coordinates */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTranslatef(0.0, 0.0, moveZ);		//���� ������

	double distance = gymSize - moveZ;

	//glRotatef((GLfloat)move, (GLfloat)move, 0.0, 1.0);//�¿� ������
	glTranslatef( distance * sin(move/10)/2, distance* cos(move/10)/2, 0);	//distance �� ��� �ʿ� ����� ��ġ�� ������
	//glRotatef((GLfloat)-move, (GLfloat)-move, 0.0, -1.0);//�¿� ������
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	gluQuadricTexture(quad, 1);
	glRotatef((GLfloat)rv, 0.0, 0.0, 1.0); //ȸ�� 
	gluCylinder(quad,0.06, 0.00001, 0.1, 100, 100);
	glPopMatrix();

	//
	//glColor3f(c.r, c.g, c.b);
	//glutSolidCone(0.03, 0.05, 80, 80); //���� ���
}

double rangeX = 25, rangeY = 0.06; //x�� ����
bool isCollapse() {
	if (player[0].moveZ < player[1].moveZ + rangeY &&  
		player[0].moveZ > player[1].moveZ - rangeY &&
		player[0].moveX >player[1].moveX +rangeX &&  //r�� ���� �ʿ䰡 �ֳ�
		player[0].moveX >player[1].moveX + rangeX ) {
	
		return true;
	} 
	return false;
}


void MyDisplay() {
	initLight();
	initRendering();
	//gluLookAt(0.3, 15, 0.1, 0.0, 0.0, -10.0, 0.0, 0.0, -1.0); //eye, center, 1
	makeArena();
	
	//����� �׸���!
	glPushMatrix();

	//���⼱ ���� ���� �ӵ��� ���� move�� �����ش�. 

	//���⼱ �浹ó��
	if (isCollapse()){  // �� 0.02
		//������ �ݴ��� �� �ӵ��� �ٲ��ְ� �Ÿ��� �������� 
		if(player[0].vR * player[1].vR <0){
			double tmp = player[0].vR;
			player[1].vR = player[0].vR;
			player[0].vR = tmp;
		}
		//������ ���� �� 
		else {
			double tmp = player[0].vR;
			player[1].vR = player[0].vR;
			player[0].vR = tmp;
		}
	}
	timeGoesOn();
	makeSpinTop(player[0].moveX, player[0].moveZ, player[0].rotate, 0);
	makeSpinTop(player[1].moveX, player[1].moveZ, player[1].rotate, 1);

	glPopMatrix();
	glutSwapBuffers();
}


// Ű�Է� 1 player
void MyKeyboard(unsigned char key, int x, int y) {
	fflush(stdin);
	switch (key) {
	case 27: //ESC
		exit(0);
		break;
	case 'd':
		if (player[0].vR > 0) {
			player[0].vR = -1;
		}
		else {
			player[0].vR -= 0.5;
			if (player[0].vR  < -3) player[0].vR += 0.5;
		}
		if (player[0].vR > 360) player[0].vR -= 360;
		glutPostRedisplay();
		break;
	case 'a':
		if (player[0].vR < 0) {
			player[0].vR += 1;
		}
		else {
			player[0].vR += 0.5;
			if (player[0].vR > 3) player[0].vR -= 0.5;
		}
		if (player[0].vR > 360) player[0].vR -= 360;
		glutPostRedisplay();
		break;
	case 'w':
		player[0].moveZ = (player[0].moveZ - 0.01);
		if (player[0].moveZ<0) player[0].moveZ = (player[0].moveZ + 0.01);
		glutPostRedisplay();
		break;
	case 's':
		player[0].moveZ = (player[0].moveZ + 0.01);
		if (player[0].moveZ> gymSize) player[0].moveZ = (player[0].moveZ - 0.01);
		glutPostRedisplay();
		break;

		// test 
	case 'f':
		printf("�����Դϴ�.\n ws�� play1�� ���� ������ ad�� �¿� �������Դϴ�.\n");
		printf(" ����Ű ���Ʒ��� play2�� ���� ������ ����Ű �¿�� �¿�������Դϴ�.");
		break;
	default:
		break;
	}
}
// Ű�Է� 2 player
void inputKey(int key, int x, int y)
{
	fflush(stdin);
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		if (player[1].vR > 0) {
			player[1].vR = -1;
		}
		else {
			player[1].vR -= 0.5;
			if (player[1].vR  < -3) player[1].vR += 0.5;
		}
		if (player[1].vR > 360) player[1].vR -= 360;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		if (player[1].vR < 0) {
			player[1].vR += 1;
		}
		else {
			player[1].vR += 0.5;
			if (player[1].vR > 3) player[1].vR -= 0.5;
		}
		if (player[1].vR > 360) player[1].vR -= 360;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		player[1].moveZ = (player[1].moveZ - 0.01);
		if (player[1].moveZ<0) player[1].moveZ = (player[1].moveZ + 0.01);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		player[1].moveZ = (player[1].moveZ + 0.01);
		if (player[1].moveZ> gymSize) player[1].moveZ = (player[1].moveZ - 0.01);
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char** argv) {

	SetSpin();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1500, 1200);

	glutCreateWindow("SpinTop System");
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

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	quad = gluNewQuadric();
	//
	Image* image = loadBMP(textureRoot[0]);
	_textureId[0] = loadTexture(image);

	image = loadBMP(textureRoot[1]);
	_textureId[1] = loadTexture(image);

	delete image;
}

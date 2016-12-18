#pragma once

#define MercurySiderealPeriod 0.24
#define VenusSiderealPeriod 0.62
#define EarthSiderealPeriod 1
#define MoonSiderealPeriod 0.8
#define MarsSiderealPeriod 1.88
#define JupiterSiderealPeriod 11.86 
#define SaturnSiderealPeriod 29.46
#define UranusSiderealPeriod 84.02
#define NeptuneSiderealPeriod 164.77

#define MercuryDistance 0.4
#define VenusDistance 0.7
#define EarthDistance 1.0
#define MoonToEarth 0.24
#define MarsDistance 1.5
#define JupiterDistance 2.2
#define SaturnDistance 2.6
#define UranusDistance 3.1
#define NeptuneDistance 3.7
GLfloat light0_diffuse[] = { 5.0f, 5.0f, 5.0f, 1.0f };
GLfloat light0_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light0_position[] = { 0.0f, 0.0f, 0.0f, 10.0f };



void initLight() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	// �� ����
	glEnable(GL_COLOR_MATERIAL);	//���� �ֱ�
	glEnable(GL_DEPTH_TEST);	//���� ��
	glEnable(GL_CULL_FACE);		//���� ����
	glEnable(GL_SMOOTH);	//�� �� �ڿ����� ��ǥ�� ����
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position); //������ ��ġ �����ϴ� param
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);	//�ֺ����� �����ϴ� param
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);	//���ݻ� �����ϴ� param
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);	//���ݻ� �����ϴ� param
}

void reshape(int w, int h) {
	float ratio = 1;
	glViewport(100, 200, w, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(0, ratio, 1, 1);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

double abs(double a) {
	if (a < 0)return -a;
	else return a;
}
typedef struct color {
	double r;
	double g;
	double b;
}color;

char* textureRoot[8] = {
	"E:/visual studio/Projects/solarSystemSub/data/mars.bmp",
	"E:/visual studio/Projects/solarSystemSub/data/jupiter.bmp",

	"E:/visual studio/Projects/solarSystemSub/data/mercury.bmp",
	"E:/visual studio/Projects/solarSystemSub/data/venus.bmp",
	"E:/visual studio/Projects/solarSystemSub/data/earth.bmp",
	"E:/visual studio/Projects/solarSystemSub/data/saturn.bmp",
	"E:/visual studio/Projects/solarSystemSub/data/uranus.bmp",
	"E:/visual studio/Projects/solarSystemSub/data/neptune.bmp"
};
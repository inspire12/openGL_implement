#include <Windows.h>
#include<glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

typedef struct color {
	double r;
	double g;
	double b;
}color;

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

#define SunRadius 3
#define MercuryRadius 0.4
#define VenusRadius 0.9
#define EarthRadius 1
#define MoonRadius 0.6 
#define MarsRadius 0.5
#define JupiterRadius 2
#define SaturnRadius 1.5
#define UranusRadius 1.2
#define NeptuneRadius 1.1

#define ratioRadius 0.03
#define ratioDistance 0.32

GLUquadricObj *disk;
int forSlow = 0;

//행성들의 값만 추가했다. 위성들은 따로 처리해야함
static double Day[8] = { 0, }; static int Time = 0;
static color c[8] = {
	{ 0.0,0.4,0.3 },
	{ 0.6,0.6,0.1 },
	{ 0.3,0.6,0.6 },
	{ 1.0,0.2,0.2 },
	{ 1.0,0.5,0.3 },
	{ 1.0,0.5,0.5 },
	{ 0.3,0.0,0.6 },
	{ 0.6,0.0,0.3 }
};
static double period[8] = { 
	MercurySiderealPeriod,
	VenusSiderealPeriod ,
	EarthSiderealPeriod ,
	MarsSiderealPeriod ,
	JupiterSiderealPeriod,
	SaturnSiderealPeriod ,
	UranusSiderealPeriod ,
	NeptuneSiderealPeriod 
};
static double dist[8] = { 
	MercuryDistance,
	VenusDistance,
	EarthDistance,
	MarsDistance ,
	JupiterDistance,
	SaturnDistance ,
	UranusDistance ,
	NeptuneDistance
};
static double radius[8] = {
	MercuryRadius,
	VenusRadius,
	EarthRadius,
	MarsRadius ,
	JupiterRadius,
	SaturnRadius ,
	UranusRadius ,
	NeptuneRadius
};
static double orbit[8] = {
	1.5,1.3,1.4,1.3,1.6,1.5,1.3,1.5
};
void makePlanet(double Day, int Time, double distance, double radius, color c, double o);

void makeEarth(double Day, int Time, double distance, double radius, color c) {
	glLoadIdentity();
	gluLookAt(0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 1.0, 1.5, 0.0);
	glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
	glTranslatef(distance* ratioDistance, 0.0, 0.0); 
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); //
	glColor3f(c.r, c.g, c.b);
	glutSolidSphere(EarthRadius* ratioRadius, 100, 80); // 지구를 그려냄
														//
	glPushMatrix();
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.06, 0.0, 0.0); 
	glColor3f(0.3, 0.4, 0.2);  // 위성 색은 통일
	glutSolidSphere(0.015, 1000, 800); // 달을 그려냄

	glPopMatrix();
}
void makeSaturn(double Day, int Time, double distance, double radius, color c) {
	glLoadIdentity();
	gluLookAt(0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 1.0, 1.5, 0.0);
	glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
	glTranslatef(distance* ratioDistance, 0.0, 0.0); // 
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); //
	glColor3f(c.r, c.g, c.b);
	glutSolidSphere(radius* ratioRadius, 100, 80); // 목성을 그려냄
	
	glPushMatrix(); // 토성의 위치를 기준으로 하기 위해 push를 해줌
	disk = gluNewQuadric(); // 일단 물체를 만든다.
	gluDisk(disk, 0.05f, 0.1f, 16, 4); //물체는 Disk로 지정해준다. 
	glPopMatrix();
}
void makeJupiter(double Day, int Time, double distance, double radius, color c) {
	glLoadIdentity();
	gluLookAt(0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 1.0, 1.5, 0.0);
	glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
	glTranslatef(distance* ratioDistance, 0.0, 0.0); 
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); //
	glColor3f(c.r, c.g, c.b);
	glutSolidSphere(radius* ratioRadius, 100, 80); // 목성을 그려냄
							
	glPushMatrix();
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.12, 0.0, 0.0); 
	glColor3f(0.3, 0.4, 0.2); 
	glutSolidSphere(0.015, 1000, 800); 
	glPopMatrix();
	glPushMatrix();
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
	gluLookAt(0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 1.0, 1.5, 0.0);
	glTranslatef(0.06, 0.0, 0.0);
	glColor3f(0.3, 0.4, 0.2);
	glutSolidSphere(0.015, 1000, 800);
	glPopMatrix();
}
void timeGoesOn() {
	for (int i = 0; i < 8; i++) {
		Day[i] = Day[i] + (int)((dist[i])*30 / period[i]);
		if ((int)((dist[i]) * 30 / period[i]) == 0) {
			forSlow += 1;
			if(forSlow %3==0)Day[i] += 1;
		}
			
		glutPostRedisplay();
	}
	Time = (Time + 10) % 360;
	glutPostRedisplay();
}

void MyDisplay() {
	GLfloat light0_diffuse[] = { 5.0f, 5.0f, 5.0f, 1.0f };	
	GLfloat light0_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	
	GLfloat light0_position[] = { 0.0f, 0.0f, 0.0f, 10.0f };

	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	
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

	gluLookAt(0.1, 0.1, 0.1,	//eye
			0, 0, 0,			//center
			0.0, 1.5, 0.0);  //	ups		전체 모델을 기울임
	//gluLookAt(0.1, 0.1, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0); // 태양의 색

	glutSolidSphere((GLdouble)SunRadius*ratioRadius, 2000, 1600); // 태양을 그려냄
	glPushMatrix(); // 태양기준의 좌표계를 스택에 푸시하여 저장

	
	for(int i=0; i<8; i++){
		if (i == 2 ) {
			makeEarth(Day[i], Time, dist[i], radius[i], c[i]);
		}//earth 
		else if (i == 4) {
			makeJupiter(Day[i], Time, dist[i], radius[i], c[i]);
		}
		else if (i == 5) {
			makeSaturn(Day[i], Time, dist[i], radius[i], c[i]);
		}
		else {
			makePlanet(Day[i], Time, dist[i], radius[i], c[i], orbit[i]);
		}
	}
	//timeGoesOn();
	glutSwapBuffers();
}

void makePlanet(double Day, int Time, double distance, 
				double radius, color c, double o) {
	glLoadIdentity();
	gluLookAt(0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 1.0, o, 0.0); 												 
//	gluLookAt(0.1, 0., 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
	glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
	glTranslatef(distance * ratioDistance, 0.0, 0.0); 
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); 
	glColor3f(c.r, c.g, c.b); 
	glutSolidSphere(radius * ratioRadius, 10, 8);
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		timeGoesOn();
		break;
	default:
		break;
	}
}
void reshape(int w, int h) {
	float ratio = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(0, ratio, 1, 1);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
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
	gluDeleteQuadric(disk);
	
	glutMainLoop();

	return 0;
}

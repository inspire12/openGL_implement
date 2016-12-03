#include <glut.h>
#include <gl\GL.h>
void init() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(+1.0, +1.0, +1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void display() {
	//각 매개변수 값은 rgba 속성 a는 투명도
	GLfloat light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 10.0f };	//정반사 - 하이라이트(관찰자의 위치에 따라있는 명암)
	GLfloat light0_ambient[] = { 10.0f, 1.0f, 1.0f, 10.0f };	//주변광,환경광 - 물체의 반사에 의해 나타나는 빛, 주의 모든 방향에서 오는 빛
	GLfloat light0_specular[] = { 100.0f, 1.0f, 1.0f, 10.0f };	//난반사 - 관찰자와는 상관관계가 없음
																// 광원의 위치- 빛이 출발하는 점 x, y , z, w(w는 x,y,z를 w로 나눔- 비율)
	GLfloat light0_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	/* https://www.opengl.org/sdk/docs/man2/xhtml/glLight.xml
	https://www.quora.com/What-is-the-difference-between-Ambient-Diffuse-and-Specular-Light-in-OpenGL
	*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0); //관점 세팅

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position); //광원의 위치 설정하는 param
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);	//주변광을 설정하는 param
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);	//난반사 설정하는 param
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);	//정반사 설정하는 param

														//두개의 원을 통해 비교
	glPushMatrix();
	glTranslatef(-1.0f, +0.0f, +0.0f);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();

	glPushMatrix();
	//	glRotatef(45, +1.0f, +1.0f, +0.0f);
	glTranslatef(+3.0f, +0.0f, +0.0f);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();
	glPushMatrix();
	//	glRotatef(45, +1.0f, +1.0f, +0.0f);
	glTranslatef(+30.0f, +30.0f, +10.0f);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();

	glFlush();

}

void reshape(int w, int h) {
	float ratio = w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 10, 100);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("test");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
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
	//�� �Ű����� ���� rgba �Ӽ� a�� ����
	GLfloat light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 10.0f };	//���ݻ� - ���̶���Ʈ(�������� ��ġ�� �����ִ� ���)
	GLfloat light0_ambient[] = { 10.0f, 1.0f, 1.0f, 10.0f };	//�ֺ���,ȯ�汤 - ��ü�� �ݻ翡 ���� ��Ÿ���� ��, ���� ��� ���⿡�� ���� ��
	GLfloat light0_specular[] = { 100.0f, 1.0f, 1.0f, 10.0f };	//���ݻ� - �����ڿʹ� ������谡 ����
																// ������ ��ġ- ���� ����ϴ� �� x, y , z, w(w�� x,y,z�� w�� ����- ����)
	GLfloat light0_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	/* https://www.opengl.org/sdk/docs/man2/xhtml/glLight.xml
	https://www.quora.com/What-is-the-difference-between-Ambient-Diffuse-and-Specular-Light-in-OpenGL
	*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0); //���� ����

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position); //������ ��ġ �����ϴ� param
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);	//�ֺ����� �����ϴ� param
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);	//���ݻ� �����ϴ� param
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);	//���ݻ� �����ϴ� param

														//�ΰ��� ���� ���� ��
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
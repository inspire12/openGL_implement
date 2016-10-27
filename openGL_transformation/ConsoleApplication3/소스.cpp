#include <windows.h>
#include <C:\Program Files (x86)\Windows Kits\8.1\Include\um\gl\glut.h>

void display();
void reshape(int w, int h) ;

int main(int argc, char **argv) {
	
	/*������ �κ��� â�� �׸��� �׸� �ʱⰪ�� �����Ѵ�.*/
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480); //��Ÿ�� â�� ũ�⸦ ���Ѵ�.
	glutCreateWindow("test"); //��Ÿ�� â�� ����ǥ������ ���Ѵ�.
	//15~17 �ʱ� ���� �����Ѵ�. ���⼱ ��� ũ�� ����� ����.
	glClearColor(0, 0, 0, 0); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0, 1.0, 1.0);
		
	glutDisplayFunc(display);//�Լ��� �ҷ� �׸��� �׸���.
	glutReshapeFunc(reshape); //â�� ���� �׸��� �����Ѵ�.
	
	glutMainLoop();//���������� �����Ѵ�.
	return 0;
}
void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	gluLookAt(0, 0, 20, // ī�޶� �����Ѵ�. ī�޶��� ��ġ
			0, 0, 0,    // ī�޶� �ٶ󺸴� ����
			0, 1, 0);	// ī�޶��� ���ʹ����� ���Ѵ�.
	glScaled(1, 1, 1);
	glutWireSphere(1, 100, 100); //��ȯ�Ǳ���. ���� �׸���. 
	//�������� 1�̰�, �ι�° �Ű� ������ ����° �Ű������� ��Ȯ����.
	glFlush(); //�޸� ���� ����ش�.

	
	//lightenging
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.8, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shine = 100.0;
	for(int i=0; i<4 ;i++){
		glMaterialf(GL_FRONT, GL_AMBIENT, ambient[i]);
		glMaterialf(GL_FRONT, GL_DIFFUSE, diffuse[i]);
		glMaterialf(GL_FRONT, GL_SPECULAR, specular[i]);
	}
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	
	glutWireSphere(1, 100, 100); //��ȯ�� ������ ���� �׸���. 
	glFlush(); //�޸� ���� ����ش�.
	
}

void reshape(int w, int h) {
	float ratio = w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 10, 100);
}

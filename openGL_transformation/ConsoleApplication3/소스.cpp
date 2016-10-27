#include <windows.h>
#include <C:\Program Files (x86)\Windows Kits\8.1\Include\um\gl\glut.h>

void display();
void reshape(int w, int h) ;

int main(int argc, char **argv) {
	
	/*메인의 부분은 창과 그림을 그릴 초기값을 세팅한다.*/
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480); //나타날 창의 크기를 정한다.
	glutCreateWindow("test"); //나타날 창의 제목표시줄을 정한다.
	//15~17 초기 색을 설정한다. 여기선 없어도 크게 상관은 없다.
	glClearColor(0, 0, 0, 0); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0, 1.0, 1.0);
		
	glutDisplayFunc(display);//함수를 불러 그림을 그린다.
	glutReshapeFunc(reshape); //창에 따라 그림이 반응한다.
	
	glutMainLoop();//지속적으로 유지한다.
	return 0;
}
void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	gluLookAt(0, 0, 20, // 카메라를 설정한다. 카메라의 위치
			0, 0, 0,    // 카메라가 바라보는 지점
			0, 1, 0);	// 카메라의 위쪽방향을 뜻한다.
	glScaled(1, 1, 1);
	glutWireSphere(1, 100, 100); //변환되기전. 원을 그린다. 
	//반지름이 1이고, 두번째 매개 변수는 세번째 매개변수는 정확도다.
	glFlush(); //메모리 값을 비워준다.

	
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
	
	glutWireSphere(1, 100, 100); //변환한 이후의 원을 그린다. 
	glFlush(); //메모리 값을 비워준다.
	
}

void reshape(int w, int h) {
	float ratio = w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 10, 100);
}

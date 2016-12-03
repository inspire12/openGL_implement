#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <vector>

#include <string.h>

#define MODELVIEW 0
#define PROJECTION 1   //Matrix Mode Setting macro

#define Pi 3.141592

typedef struct Vertex {
	float vertex[4];
}Vertex;            //Vertex x, y, z, w;

typedef struct Matrix {   //List style Matrix Stack
	float matrix[4][4];
	struct Matrix *next;   //Pointer for next Matrix
	struct Matrix *prev;
}Matrix;


Matrix* operator * (const Matrix &a, const Matrix &b) {
	int n = 4;
	Matrix* c = (Matrix *)malloc(sizeof(Matrix));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c->matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				c->matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
			}
		}
	}
	return c;
}


/* 전역 변수 */
int MatrixMode;            //Variable for set matrixmode
Matrix *ptr = NULL;         //Variable for point Stack top

void print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%.3f ",ptr->matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void mySetMatrixMode() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)(*ptr).matrix[i][j] = 1;
			else (*ptr).matrix[i][j] = 0;
		}
	}
}
void myLoadIdentity() {
	ptr = (Matrix *)malloc(sizeof(Matrix));
}
void myPushMatrix() {// push into current matrix stack
	Matrix *rep = (Matrix *)malloc(sizeof(Matrix));
	for(int i=0; i<4; i++){
		for(int j=0; j<4 ;j++)	rep->matrix[i][j] = ptr->matrix[i][j];
	}
	rep->next = ptr->next;
	rep->prev = ptr;
	
	ptr = rep;

}
void myPopMatrix() {//
	Matrix* a = ptr;
	ptr = (ptr->prev);
	free(a);
}
void myMatrixMul(Matrix m) {// multiply a matrix m with current stack top & replace top with the result
	myPushMatrix();
	
	Matrix* c = *ptr* * &m;
	ptr = c;
}
void myRunMatrix(Vertex v) {// multiply a vertex v with current stack top
	Matrix *rep = (Matrix *)malloc(sizeof(Matrix));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) if (i == j)rep->matrix[i][j] = v.vertex[i]; else rep->matrix[i][j] = 0;

	Matrix* c = *ptr* *rep;
	ptr = c;
	free(rep);

}
void myTranslateX(float d) {// set matrix for translation in x-axis by 'd' & multiply with current stack top
	myPushMatrix();
	for (int i = 0; i < 4; i++)
		ptr->matrix[0][i] = ptr->matrix[0][i] + d;

}
void myTranslateY(float d){// set matrix for translation in y-axis by 'd' & multiply with current stack top
	myPushMatrix();
	for (int i = 0; i < 4; i++)
		ptr->matrix[1][i] = ptr->matrix[1][i] + d;
}
void myTranslateZ(float d) {// set matrix for translation in z-axis by 'd' & multiply with current stack top
	myPushMatrix();
	for (int i = 0; i < 4; i++)
		ptr->matrix[2][i] = ptr->matrix[2][i] + d;
}
void myRotateX(float r) {// set matrix for rotation around x-axis by 'r' degree & multiply with current stack top
	myPushMatrix();
	Matrix *rep = (Matrix *)malloc(sizeof(Matrix));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) rep->matrix[i][j] = 0;
	}

	r = r* Pi / 180;
	rep->matrix[1][1] = cos(r); rep->matrix[1][2] = -sin(r);
	rep->matrix[2][1] = sin(r); rep->matrix[2][2] = cos(r);
	rep->matrix[0][0] = 1; rep->matrix[3][3] = 1;

	Matrix *c = *ptr * *rep;
	ptr = c;
	free(rep);
}
void myRotateY(float r) {// set matrix for rotation around y-axis by 'r' degree & multiply with current stack top
	myPushMatrix();
	Matrix *rep = (Matrix *)malloc(sizeof(Matrix));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) rep->matrix[i][j] = 0;
	}

	r = r* Pi / 180;
	rep->matrix[0][0] = cos(r); rep->matrix[0][2] = sin(r);
	rep->matrix[2][0] = -sin(r); rep->matrix[2][2] = cos(r);
	rep->matrix[1][1] = 1; rep->matrix[3][3] = 1;
	ptr = *ptr * *rep;
	free(rep);
}
void myRotateZ(float r) {// set matrix for rotation around z-axis by 'r' degree & multiply with current stack top
	myPushMatrix();
	Matrix *rep = (Matrix *)malloc(sizeof(Matrix));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) rep->matrix[i][j] = 0;
	}
	r = r* Pi / 180;
	rep->matrix[0][0] = cos(r); rep->matrix[0][1] = -sin(r);
	rep->matrix[1][0] = sin(r); rep->matrix[1][1] = cos(r);
	rep->matrix[2][2] = 1; rep->matrix[3][3] = 1;
	ptr = *ptr * *rep;
	free(rep);
}
void myScaleX(float s) {// set matrix for scaling in x-axis by 's' & multiply with current stack top
	myPushMatrix();
	for (int i = 0; i < 4; i++)
		ptr->matrix[0][i] = ptr->matrix[0][i] * s;
}
void myScaleY(float s) {// set matrix for scaling in x-axis by 's' & multiply with current stack top
	myPushMatrix();
	for (int i = 0; i < 4; i++)
		ptr->matrix[1][i] = ptr->matrix[1][i] * s;
}
void myScaleZ(float s) {// set matrix for scaling in x-axis by 's' & multiply with current stack top
	myPushMatrix();
	for (int i = 0; i < 4; i++)
		ptr->matrix[2][i] = ptr->matrix[2][i] * s;
}


//테스트 
int main() {

	
	myLoadIdentity();
	mySetMatrixMode();
	print();
	////rotate
	//myRotateX(45);
	//print();
	//myRotateY(45);
	//print();
	//myRotateZ(45);
	//print();
	////translate
	myTranslateX(10);
	print();
	myTranslateY(10);
	print();
	myTranslateZ(10);
	print();
	myPopMatrix();
	print();
/*
	myScaleX(3);
	print();
	myScaleY(3);
	print();
	myScaleZ(3);
	print();
*/

	return 0;
}
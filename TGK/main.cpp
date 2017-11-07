#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include "Tree.h"
#include "Texture.h"

float boundX = 36.0f, boundY = 10.0f;
float cameraX, cameraY, cameraZ;
float radiusInner, radiusOuter;
float cameraInitPostionX, cameraInitPostionY, cameraInitPostionZ;
float cameraOffsetX, cameraOffsetY, cameraOffsetZ;
float lookAtInitPostionX, lookAtInitPostionY, lookAtInitPostionZ;
float lookAtX, lookAtY, lookAtZ;
int lightColor = 1;
float lightPosX = -1.0f, lightPosY = -0.5f, lightPosZ = 0.1f;
bool lightState = true;
float rotateTree;
static GLuint ground_tex;

Tree *tree;

void renderPrimitive(void) {
	//glColor3f(0.15, 0.6, 0.15f);
	setupTexDefault("F:/Studia/Sem 2 mgr/TGK/Projekt/data/grass.tga", ground_tex);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ground_tex);
	glBegin(GL_QUADS);

	glTexCoord2d(0, 0);
	glVertex3f(-boundX, -boundY, 0.0f); // lewy dolny
	glTexCoord2d(1, 0);
	glVertex3f(-boundX, boundY, 0.0f); // lewy górny
	glTexCoord2d(1, 1);
	glVertex3f(boundX, boundY, 0.0f); // prawy górny
	glTexCoord2d(0, 1);
	glVertex3f(boundX, -boundY, 0.0f); // prawy dolny
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void renderScene(void) {
	GLfloat R, G, B;
	GLfloat ambientcolor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientcolor);

	//œwiat³o punktowe
	GLfloat lightColor0[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat lightPosition0[] = { 4.0f, 0.0f, 5.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);


	//œwiat³o kierunkowe
	switch (lightColor) {
	case 1:
		R = 1.0f;
		G = 1.0f;
		B = 1.0f;
		break;
	case 2:
		R = 0.15f;
		G = 0.7f;
		B = 1.0f;
		break;
	case 3:
		R = 0.5f;
		G = 1.0f;
		B = 0.15f;
		break;
	case 4:
		R = 0.5f;
		G = 0.0f;
		B = 0.45f;
		break;
	}
	GLfloat lightColor1[] = { R, G, B, 0.0f };
	GLfloat lightPosition1[] = { lightPosX, lightPosY, lightPosZ, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
}

void renderObject() {
	tree->render();
}

void render() {
	glClearColor(0.05, 0.29, 0.54f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(cameraX, cameraY, cameraZ, lookAtX, lookAtY, lookAtZ, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
	renderPrimitive();
	renderScene();
	renderObject();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void reshape(int width, int height) {
	if (height == 0) {
		height = 1;
	}
	float ratio = width*1.0f / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	gluPerspective(50.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void updateView() {
	cameraX = cameraInitPostionX + cameraOffsetX, cameraY = cameraInitPostionY + cameraOffsetY, cameraZ = cameraInitPostionZ + cameraOffsetZ;
	lookAtX = lookAtInitPostionX, lookAtY = lookAtInitPostionY, lookAtZ = lookAtInitPostionZ;
}

void initRender() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	if (lightState) {
		glEnable(GL_LIGHTING);
	}
	else glDisable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

void initScene() {
	rotateTree = 0.0f;
	radiusInner = 2.5f;
	radiusOuter = 18.0f;
	cameraInitPostionX = 0.0f, cameraInitPostionY = -radiusOuter, cameraInitPostionZ = 15.0f;
	cameraOffsetX = 0.0f, cameraOffsetY = 0.0f, cameraOffsetZ = 0.0f;
	lookAtInitPostionX = 0.0f, lookAtInitPostionY = radiusInner, lookAtInitPostionZ = 0.0f;
}

void init() {
	initScene();
	initRender();

	tree = new Tree(0.0f, 0.0f, 0.0f, 3.0f, 0.3f, 1.0f);//parametry drzewa
	tree->buildTree();

	updateView();
}

void animateTree(int offset) {
	rotateTree += offset;
	tree->animate(rotateTree);
}

void keyPressed(unsigned char key, int x, int y) {
	switch (key) {
	case 'u':
		animateTree(-5);
		break;
	case 'i':
		animateTree(5);
		break;
	case 'o':
		initScene();
		animateTree(-rotateTree);
		lightColor = 1;
		lightState = true;
		initRender();
		break;
	case 'a':
		cameraOffsetX += 0.25;
		break;
	case 'd':
		cameraOffsetX -= 0.25;
		break;
	case 'e':
		cameraOffsetZ -= 0.25;
		break;
	case 'q':
		cameraOffsetZ += 0.25;
		break;
	case 's':
		cameraOffsetY -= 0.25;
		break;
	case 'w':
		cameraOffsetY += 0.25;
		break;
	case 'v':
		lightPosZ--;
		break;
	case 'b':
		lightPosZ++;
		break;
	case 'r':
		lightPosY--;
		break;
	case 't':
		lightPosY++;
		break;
	case 'f':
		lightPosX--;
		break;
	case 'g':
		lightPosX++;
		break;
	case 'x':
		lightPosX = -1.0f, lightPosY = -0.5f, lightPosZ = 0.1f;
		break;
	case 'l':
		lightState = !lightState;
		initRender();
		break;
	case 49:
		lightColor = 1;
		break;
	case 50:
		lightColor = 2;
		break;
	case 51:
		lightColor = 3;
		break;
	case 52:
		lightColor = 4;
		break;
	}
}

void update(int value) {
	updateView();
	glutPostRedisplay();
	glutTimerFunc(10, update, 1);
}

void menu() {
	printf("A - kamera X+\nD - kamera X-\n");
	printf("S - kamera Y+\nW - kamera Y-\n");
	printf("Q - kamera Z+\nE - kamera Z-\n");
	printf("T - swiatlo Y+\nR - swiatlo Y-\n");
	printf("G - swiatlo X+\nF - swiatlo X-\n");
	printf("B - swiatlo Z+\nV - swiatlo Z-\n");
	printf("1-4 - zmiana koloru swiatla kierunkowego\n");
	printf("X - swiatlo kierunkowe reset\n");
	printf("I - obrot drzewa+\nU - obrot drzewa-\n");
	printf("L - swiatlo punktowe +/-\n");
	printf("O - reset sceny\n");
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 10);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Drzewo");

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);

	init();
	menu();

	glutTimerFunc(10, update, 0);

	glutMainLoop();

	return 1;
}
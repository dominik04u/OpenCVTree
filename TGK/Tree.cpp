#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "Tree.h"
#include "Texture.h"



Tree::Tree(float posX, float posY, float posZ, float height, float base, float size) {
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->height = height;
	this->base = base;
	this->size = size;
	init();
}

void Tree::init() {
	this->angle = 0.0f;
	this->treeBranch = 4;
	this->makeaTree = glGenLists(1);
	this->staticAngle = 45.0f;

	/*this->trunkR = 0.545f;
	this->trunkG = 0.271f;
	this->trunkB = 0.075f;

	this->leafR = 0.0f;
	this->leafG = 0.5f;
	this->leafB = 0.0f;*/
}

void Tree::buildTree() {
	glNewList(this->makeaTree, GL_COMPILE);
	this->makeTree(this->height, this->base);
	glEndList();
}

void Tree::animate(float offset) {
	this->angle = offset;
	if (this->angle>360) {
		this->angle -= 360.0;
	}else if (this->angle<0) {
		this->angle += 360.0;
	}
}

void Tree::render() {
	glPushMatrix();
	glTranslatef(this->posX, this->posY, this->posZ);
	glScaled(this->size, this->size, this->size);
	glRotatef(90, 1.0f, 0, 0);
	glRotatef(angle, 0, 1.0f, 0);
	glCallList(makeaTree);
	glPopMatrix();
}

void Tree::makeCylinder(float height, float base) {
	GLUquadric *obj = gluNewQuadric();
	//glColor3f(this->trunkR, this->trunkG, this->trunkB);
	static GLuint tree_tex;
	setupTexDefault("F:/Studia/Sem 2 mgr/TGK/Projekt/data/bark.tga", tree_tex);
	
	glPushMatrix();
	glRotatef(-90, 1.0f, 0.0, 0.0);
	gluQuadricTexture(obj, tree_tex);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tree_tex);
	gluCylinder(obj, base, base - (0.5*base), height, 10, 10);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glutSwapBuffers();
	
}

void Tree::makeTree(float height, float base) {
	float angle;
	int i;
	int direction;
	int binaryAngle;
	makeCylinder(height, base);
	glTranslatef(0.0, height, 0.0);

	height -= height*0.2f;
	base -= base*0.3;

	for (i = 0; i<treeBranch; i++) {
		direction = rand() % 4;
			binaryAngle = rand() % 2;
			if (binaryAngle == 0) {
				angle = staticAngle;
			}
			else angle = -staticAngle;
		if (height >1) {
			glPushMatrix();
			switch (direction) {
			case 0:
				glRotatef(angle, 1.0f, 1.0f, 1.0f);
				break;
			case 1:
				glRotatef(angle, 1.0f, -1.0f, 1.0f);
				break;
			case 2:
				glRotatef(angle, -1.0f, 1.0f, 1.0f);
				break;
			case 3:
				glRotatef(angle, -1.0f, -1.0f, 1.0f);
				break;
			}
			makeTree(height, base);
			glPopMatrix();
		}
		else {
			/*glBegin(GL_POLYGON);
				glColor3f(this->leafR, this->leafG, this->leafB);

				glVertex2f(0, 0.25);
				glVertex2f(-0.125, 0.125);
				glVertex2f(-0.075, -0.025);
				glVertex2f(0.075, -0.025);
				glVertex2f(0.125, 0.125);
			glEnd();
			return;*/

			static GLuint leaf_tex;
			setupTexDefault("F:/Studia/Sem 2 mgr/TGK/Projekt/data/grass.tga", leaf_tex);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, leaf_tex);
			//glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_QUADS);

			glTexCoord2d(0, 0);
			glVertex2f(0, 1);
			glTexCoord2d(1, 0); 
			glVertex2f(-0.5 , 0.5 );
			glTexCoord2d(1, 1);
			glVertex2f(-0.25 , -0.1);
			glTexCoord2d(1, 0);
			glVertex2f(0.5, -0.1);
			glVertex2f(0.5, 0.5);

			glEnd();

			glDisable(GL_TEXTURE_2D);
			return;
		}
	}
}

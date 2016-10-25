//#include "stdafx.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

using namespace std;

class Triangle
{
public:
	Triangle(vector<float>, float*);
	void Draw() const;
	float *a, *b, *c, *color;
};

Triangle::Triangle(vector<float> abc, float* color1)
{
	this->a = new float[2]{ abc[0], abc[1] };
	this->b = new float[2]{ abc[0] + abc[2], abc[1] };
	this->c = new float[2]{ abc[0], abc[1] + abc[2] };
	this->color = new float[4]{ color1[0], color1[1],color1[2], color1[3] };
}

void Triangle::Draw() const
{
	glBegin(GL_POLYGON);
	glColor4fv(this->color);//Red;
	glVertex2fv(this->a);
	glVertex2fv(this->b);
	glVertex2fv(this->c);
	glEnd();
}


void MyDisplay(void)
{
	// Wyswietlana scena - poczatek
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	float colors[6][4] = {
		{1,0,0,1},
		{1,1,0,1},
		{1,1,1,1},
		{1,0,1,1},
		{0,1,0,1},
		{0,0,1,1}
	};

	vector<vector<float>> points;

	vector<Triangle> triangles;
	float a = 80;
	float sx = 100, sy = 100;

	for (auto i = 0, j = 3; i < 3; i++, j--)
	{
		for (auto k = 0; k < j; k++)
		{
			points.push_back({ sx + (a * i),sy + (a * k), a });
		}
	}

	for (auto i = 0; i < 6; i++)
	{
		Triangle(points.at(i), colors[i]).Draw();
	}

	glFlush();//start processing buffered OpenGL routines
}

void MyInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);//select clearing (background) color
	glViewport(0, 0, 300, 300);//pocz•tek u.ws. lewy górny róg
	glMatrixMode(GL_PROJECTION);//Nast•pne 2 wiersze b•d• modyfikowa³y m. PROJECTION
	glLoadIdentity();//inicjalizacja
	gluOrtho2D(0.0, 500.0 * 1.2, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW); //Nast•pny wiersz b•dzie modyfikowa³ m. MODELVIEW
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//single buffer and RGBA
	glutInitWindowSize(250, 250);//initial window size
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My window");//create widnow, hello title bar
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutMainLoop();//enter main loop and process events
	return 0;
}

#include <GL/freeglut.h>

class Tree {
public:
	float posX, posY, posZ;
	float height;
	float base;
	float size;
	int treeBranch;
	int treeLevel;
	GLuint makeaTree;

	Tree(float posX, float posY, float posZ, float height, float base, float size);
	void Tree::render();
	void Tree::buildTree();
	void Tree::animate(float offset);


private:
	float angle;
	//float leafR, leafG, leafB;
	//float trunkR, trunkG, trunkB;
	float staticAngle;

	void Tree::init();
	void Tree::makeCylinder(float height, float base);
	void Tree::makeTree(float height, float base);

};
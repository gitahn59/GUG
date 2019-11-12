//============================================================================
// Name        : Main.java
// Author      : gitahn59
// Version     : 1.0
// Copyright   : MIT
// Description : Main thread 
//============================================================================

#include <iostream>
#include <glut.h>

using namespace std;

void displayCallback();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GUG");
	glutDisplayFunc(displayCallback);

	glutMainLoop();
	return 0;
}

void displayCallback() {

}
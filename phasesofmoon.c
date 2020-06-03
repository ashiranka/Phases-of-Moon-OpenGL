#include<stdlib.h>
#include<GL\glut.h>
#include<Windows.h>
#include<math.h>
#define MOON 1

  double radius=3.0;
  double u=0.0;
  void star1(int starpos1,int starpos2);
  void create() 
  {
    glNewList(MOON, GL_COMPILE);
    GLfloat direction[] = {-1.0, -1.0, -1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    glutSolidSphere(1.0, 45, 45);
    glEndList();
  }
  void draw() {
    
	
	glCallList(MOON);
  }
  void advance(double delta) {u += delta;}
  void getPosition(double& x, double& y, double& z) {
    x = radius * cos(u);
    y = 0;
    z = radius * sin(u);
  }
  void init() 
  {
  glEnable(GL_DEPTH_TEST);
  GLfloat yellow[] = {1.0, 1.0, 0.5, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  create();
}
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  double x, y, z;
  getPosition(x, y, z);
  gluLookAt(x, y, z, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
  draw();
  init();
  glPopMatrix();
  glutSwapBuffers();
  glFlush();
}
void timer(int v) {
  advance(0.005);
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, v);
}
void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80.0, GLfloat(w) / GLfloat(h), 1.0, 10.0);
}
int main(int argc, char** argv) 
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1200,1200);
  glutCreateWindow("The Moon");
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,1200,0,1200);
  //glutDisplayFunc(display);
 // nightsky();
  glutDisplayFunc(display);
  glutTimerFunc(100, timer, 0);
  glutReshapeFunc(reshape);
  //init();
  glutMainLoop();
}


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

float posX=0.0f,posY = 1.0f, posZ=3.0f;    // x,z position of the camera

typedef float vec3_t[3];

vec3_t gRot = {0,0,0};

void drawTeapot()
{
    glColor3f(0.0f, 0.4f, 0.8f);

    glutWireTeapot(10.0);
}

void renderScene(void)
{
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    gluLookAt (posX , posY , posZ   ,
               0.0   , posY , 0.0 ,
               0.0f  , posY , 0.0f);

    glTranslatef (0, 0, -40);
    /* apply the rotation from the mouse */
    glRotatef (gRot[0], 0.1, 0.0, 0.0);
    glRotatef (gRot[1], 0.0, 0.1, 0.0);
    // Draw teapot
    glPushMatrix();
    drawTeapot();
    glPopMatrix();

    glutSwapBuffers();
}



void onMouseMove(int x, int y)
{
    gRot[0] -= (((posY - y) * 180.0f) / 100.0f);
    gRot[1] -= (((posX - x) * 180.0f) / 100.0f);
    glutPostRedisplay();
}


void changeSize(int w, int h)
{
    if (h == 0)
      h = 1;

    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set the view port to be the entire window
    glViewport(0, 0, w, h);

    // set the correct perspective
    gluPerspective(60.0f, ratio, 0.1f, 100.0);

    // go back to model view
    glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Camera Movement Animation");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutPassiveMotionFunc(onMouseMove);
    glutMainLoop();
}

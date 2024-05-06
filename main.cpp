//Punto extra: Ping Pong
#include <GLUT/glut.h>
#include <math.h>

const double paddleWidth = 5.0;
const double paddleHeight = 30.0;
double xpos, ypos, ydir, xdir;
double sx, sy, squash;
int SPEED = 50;
int paddle_speed = 20;
GLfloat T[16] = {1.,0.,0.,0.,\
                 0., 1., 0., 0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};

GLint circle_points = 100; 
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius){
  GLint i;
  GLdouble angle;
  glBegin(GL_POLYGON); 
  for (i = 0; i < circle_points; i++) {    
    angle = 2*M_PI*i/circle_points; 
    glVertex2f(centerx+radius*cos(angle), centery+radius*sin(angle)); 
  } 
  glEnd();
}

GLfloat RadiusOfBall = 3.;

void draw_ball() {
  glColor3f(0.6,0.3,0.);
  MyCircle2f(0.,0.,RadiusOfBall);
}

void draw_paddle(double x, double y) {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x - paddleWidth / 2, y - paddleHeight / 2);
    glVertex2f(x + paddleWidth / 2, y - paddleHeight / 2);
    glVertex2f(x + paddleWidth / 2, y + paddleHeight / 2);
    glVertex2f(x - paddleWidth / 2, y + paddleHeight / 2);
    glEnd();
}

double paddleYLeft = 60.0;
double paddleYRight = 60.0;

void Display(void) {
    glutSwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT);

    xpos += xdir * 1.009;
    ypos += ydir * 1.009;

    if ((xpos - RadiusOfBall <= 25.0 && xpos - RadiusOfBall >= 20.0 && fabs(ypos - paddleYLeft) <= paddleHeight / 2) ||
        (xpos + RadiusOfBall >= 135.0 && xpos + RadiusOfBall <= 140.0 && fabs(ypos - paddleYRight) <= paddleHeight / 2)) {
        xdir = -xdir; 
    }

    if (ypos >= 120.0 - RadiusOfBall || ypos <= RadiusOfBall)
    {
        ydir = -ydir;
    }

    if (xpos >= 160.0 - RadiusOfBall || xpos <= RadiusOfBall)
    {
        xpos = 80.;
        ypos = 60.;
        xdir = -xdir;
    }

    if (paddleYLeft + paddleHeight / 2 > 120.0) {
        paddleYLeft = 120.0 - paddleHeight / 2;
    } else if (paddleYLeft - paddleHeight / 2 < 0.0) {
        paddleYLeft = paddleHeight / 2;
    }

    if (paddleYRight + paddleHeight / 2 > 120.0) {
        paddleYRight = 120.0 - paddleHeight / 2;
    } else if (paddleYRight - paddleHeight / 2 < 0.0) {
        paddleYRight = paddleHeight / 2;
    }

    glLoadIdentity();
    glPushMatrix();
    glTranslatef(xpos, ypos, 0.);
    glTranslatef(0., -RadiusOfBall, 0.);
    glScalef(sx, sy, 1.);
    glTranslatef(0., RadiusOfBall, 0.);
    draw_ball();
    glPopMatrix();

    draw_paddle(20., paddleYLeft); 
    draw_paddle(140., paddleYRight);

    glutPostRedisplay();
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0.0, 160.0, 0.0, 120.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}

void SpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            paddleYRight += paddle_speed;
            break;
        case GLUT_KEY_DOWN:
            paddleYRight -= paddle_speed;
            break;
    }
    glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            paddleYLeft += paddle_speed;
            break;
        case 's':
            paddleYLeft -= paddle_speed;
            break;
    }
    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.0,0.8,0.0,1.0);
    xpos = 80.; ypos = RadiusOfBall; xdir = 1; ydir = 1;
    sx = 1.; sy = 1.; squash = 0.9;
}

int main(int argc, char* argv[]) {
    glutInit( & argc, argv );
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (320, 240);
    glutCreateWindow("Bouncing Ball");
    init();
    glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();

    return 1;
}

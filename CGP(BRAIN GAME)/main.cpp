#include<cstdio>
#include <windows.h>
#include<math.h>
#include <vector>
#include <cstdlib>
# define PI 3.14159265358979323846
#include <GL/gl.h>
#include <GL/glut.h>
#include<MMSystem.h>



GLint i, j, k;
GLfloat sun_spin=0, sun_x=0, sun_y=0;
GLfloat ax=0,bx=0,cx=0,dx=0,str=500.0,mn=500.0;
GLfloat sr=0.0,sg=0.749,sb=1.0;
GLfloat spin = 0.0; int _CarMoveReverse = 0; float TireRotateAngle = 0.0f; bool Human = false;

float pos = 0.0; bool done = false;
int pipeStuckX = 0, pipeStuckY = 0, pipeEndX = 0, pipeEndY = 0;
int pipePos = 0, winLeft = 0, winRight = 0;

void circle(GLdouble rad)
{
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;

    glBegin(GL_POLYGON);
    {
        for( i = 0; i <=50; i++, theta += delTheta )
        {
            glVertex2f(rad * cos(theta),rad * sin(theta));
        }
    }
    glEnd();
}

void Sun_Model(){
    glPushMatrix();
    glTranslatef(500,0,0);
    circle(30);
    glPopMatrix();

}

void Moving_Sun_Model(){
    glPushMatrix();
    glRotatef(-sun_spin, 0,0,-.009);
    Sun_Model();
    glPopMatrix();

}

void Sun(){
    glColor3f(1, 1, 0);
    glPushMatrix();
    Moving_Sun_Model();
    glPopMatrix();
}

void sun_move(){

    sun_spin = sun_spin + 0.0008;

}

void move_right(){

    sun_move();

    spin = spin +.1;
    ax = ax + .05;
    bx = bx + .08;
    cx = cx + .10;
    dx = dx + .15;

    if(cx>1000){
        cx = -300;
    }
    if(bx>1000){
            bx= -400;

    }
    if(cx>1000){
            cx= -400;

    }
    if(dx>1000){
            dx= -500;

    }


    glutPostRedisplay();
}

void cloud_model_one(){

    glColor3f(1.25, 0.924, 0.930);

    ///Top_Left

    glPushMatrix();
    glTranslatef(320,210,0);
    circle(15);
    glPopMatrix();

    ///Top

    glPushMatrix();
    glTranslatef(340, 225, 0);
    circle(16);
    glPopMatrix();

    ///Right

    glPushMatrix();
    glTranslatef(360,210,0);
    circle(16);
    glPopMatrix();


    ///middle_Fill
    glPushMatrix();
    glTranslatef(355,210,0);
    circle(16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(350,210,0);
    circle(16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(345,204,0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(340,204,0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(335,204,0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(330,204,0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(325,204,0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(320,204,0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(315,204,0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(310,204,0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(305,204,0);
    circle(10);
    glPopMatrix();

    ///****Fill End****

}

void cloud_model_Two(){
    glColor3f(1.25, 0.924, 0.930);

    ///Left_Part
    glPushMatrix();
    glTranslatef(305,205,0);
    circle(10);
    glPopMatrix();

    ///Top

    glPushMatrix();
    glTranslatef(320,210,0);
    circle(15);
    glPopMatrix();

    ///Right_Part
    glPushMatrix();
    glTranslatef(334,207,0);
    circle(10);
    glPopMatrix();

    ///Bottom_Part
    glPushMatrix();
    glTranslatef(320,207,0);
    circle(10);
    glPopMatrix();
}

void cloud_model_Three(){
    glColor3f(1.25, 0.924, 0.930);

    ///Left_Part
    glPushMatrix();
    glTranslatef(300,200,0);
    circle(15);
    glPopMatrix();

    ///Top_Left

    glPushMatrix();
    glTranslatef(320,210,0);
    circle(15);
    glPopMatrix();

    ///Top
    glPushMatrix();
    glTranslatef(340,220,0);
    circle(16);
    glPopMatrix();

    ///Top_Right
    glPushMatrix();
    glTranslatef(360,210,0);
    circle(15);
    glPopMatrix();

    ///Right_Part
    glPushMatrix();
    glTranslatef(380,200,0);
    circle(15);
    glPopMatrix();

    ///Bottom_Right
    glPushMatrix();
    glTranslatef(360,190,0);
    circle(20);
    glPopMatrix();

    ///Bottom_Left
    glPushMatrix();
    glTranslatef(320,190,0);
    circle(20);
    glPopMatrix();

    ///Bottom
    glPushMatrix();
    glTranslatef(340,190,0);
    circle(20);
    glPopMatrix();

}

void cloud_one(){
    glPushMatrix();
    glTranslatef(cx,-40,0);
    cloud_model_one();
    glPopMatrix();
}

void cloud_two(){
    glPushMatrix();
    glTranslatef(bx+100,150,0);
    cloud_model_one();
    glPopMatrix();

}

void cloud_three(){
    glPushMatrix();
    glTranslatef(ax-80,80,0);
    cloud_model_Two();
    glPopMatrix();

}

void cloud_four(){
    glPushMatrix();
    glTranslatef(dx+300,125,0);
    cloud_model_Two();
    glPopMatrix();

}

void cloud_five(){

    glPushMatrix();
    glTranslatef(ax+-300,170,0);
    cloud_model_Three();
    glPopMatrix();
}

void cloud_six(){


    glPushMatrix();
    glTranslatef(cx+-500,20,0);
    cloud_model_Three();
    glPopMatrix();
}

void CarTire(int xx, int yy, float r)
{

    glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
glTranslatef(0.0f,0.0f,0.0f);
glRotatef(TireRotateAngle, 0.0f, 0.0f,1.0f);
glTranslatef(-0.0f,-0.0f,0.0f);
glBegin(GL_POLYGON); // Red 1x1 Square centered at origin
    for (int i = 0; i < 200; i++)
    {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + xx, y + yy);
    }
glEnd();

    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(-0.075,0);
    glVertex2f(0.075,0);

    glVertex2f(-0.05,-0.075);
    glVertex2f(0.05,0.075);

    glVertex2f(0.05,-0.075);
    glVertex2f(-0.05,0.075);

    glVertex2f(0,-0.1);
    glVertex2f(0,0.1);
    glEnd();

    glPopMatrix();

}
void ScaledTire()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(140.1,95,0);
    glScalef(80,80,0);
    glColor3ub(0,0,0);//black-tire
    CarTire(0, 0, 0.2);
    glColor3ub(192,192,192);//silver-tire-rim
    CarTire(0,0,0.13);
    glColor3ub(211,211,255);//grey-tire-rim
    CarTire(0,0,0.09);
    glPopMatrix();
}

void CarBody()
{



    glColor3f(0.2, 0.95, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(240, 127);
    glVertex2f(240, 92);
    glVertex2f(110, 92);
    glVertex2f(110, 127);
    glVertex2f(130, 127);
    glVertex2f(140, 152);
    glEnd();

    glBegin(GL_POLYGON); //window
    glColor3ub(0, 0, 0);
    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(210, 127);
    glVertex2f(120, 127);
    glVertex2f(130, 127);
    glEnd();

    glBegin(GL_POLYGON); //window-Divider
    glColor3ub(192, 192, 192);
    glVertex2f(170, 152);
    glVertex2f(165, 152);
    glVertex2f(165, 127);
    glVertex2f(170, 127);
    glEnd();

    glBegin(GL_POLYGON); //roof-plate
    glColor3ub(168, 169, 173);

    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(185, 157);
    glVertex2f(140, 157);
    glEnd();

    glBegin(GL_POLYGON); //window-holder-front
    glColor3ub(168, 169, 173);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(210, 127);
    glVertex2f(185, 152);
    glEnd();

    glBegin(GL_POLYGON); //window-holder-back
    glColor3ub(168, 169, 173);
    glVertex2f(140, 157);
    glVertex2f(115, 127);
    glVertex2f(125, 127);
    glVertex2f(140, 152);
    glEnd();

    glBegin(GL_POLYGON); //foot-holder
    glColor3ub(168, 169, 173);
    glVertex2f(242, 92);
    glVertex2f(110, 92);
    glVertex2f(110, 97);
    glVertex2f(242, 97);

    glEnd();

    glBegin(GL_POLYGON);      //mirror
    glColor3f(0.3, 0.9, 0.6); //body
    glVertex2f(211.5, 134.5);
    glVertex2f(204.5, 135.5);
    glVertex2f(203.5, 129);
    glVertex2f(210.5, 127);
    glEnd();

    glBegin(GL_POLYGON);      //Yellow-headlight
    glColor3f(1.0, 1.0, 0.0); //body
    glVertex2f(210.5+28, 134.5-10);
    glVertex2f(203.5+28, 135.5-10);
    glVertex2f(203.5+28, 129-10);
    glVertex2f(210.5+28, 127-10);
    glEnd();

    glBegin(GL_POLYGON); //window-opener-1
    glColor3ub(192, 192, 192);
    glVertex2f(150-15-5, 127-5-3);
    glVertex2f(155-5-5, 127-5-3);
    glVertex2f(155-5-5, 129-5);
    glVertex2f(150-15-5, 129-5);
    glEnd();
    glBegin(GL_POLYGON); //window-opener-2
    glColor3ub(192, 192, 192);
    glVertex2f(150-15+40, 127-5-3);
    glVertex2f(155-5+40, 127-5-3);
    glVertex2f(155-5+40, 129-5);
    glVertex2f(150-15+40, 129-5);
    glEnd();
}
void CarThrust()
{


    glBegin(GL_POLYGON);
    glColor3ub(168, 169, 173);
    glVertex2f(110, 92);
    glColor3ub(255, 255, 255);
    glVertex2f(00, 80);
    glVertex2f(00, 110);
    glColor3ub(0, 0, 0);
    glVertex2f(110, 97);
    glEnd();

}
void fullCar()
{


    //CarThrust();
    CarBody();
    ScaledTire();
    glPushMatrix();
    glTranslatef(65,0,0);
    ScaledTire();
    glPopMatrix();

}
void CarReverse()
{
    glLineWidth(1);
    glTranslatef(-100.5, 0, 0);
    fullCar();
}

void ScaledCarReverse()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(500,140,0);
    glScalef(-0.5,0.5,0);
    CarReverse();
    glPopMatrix();
}

void MovingScaledCarReverse()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_CarMoveReverse % 550, 0, 0);
    ScaledCarReverse();
    glPopMatrix();
}
void TireRotate(int value)
{

    TireRotateAngle-= 5.0f;
    glutPostRedisplay();

    glutTimerFunc(05, TireRotate, 0); //Notify GLUT to call update again in 25 milliseconds
}
void MoveCarReverse(int value) {

 _CarMoveReverse -= 1;

glutPostRedisplay();
glutTimerFunc(20, MoveCarReverse, 0);
}

void drawRiver  () {
    glBegin(GL_POLYGON);
     glColor3ub(47, 134, 166);
     glVertex2i(200,600-600);
     glVertex2i(200,600-560);
     glVertex2i(700,600-560);
     glVertex2i(700,600-600);
     glEnd();
}

void drawBridge () {
    glBegin(GL_POLYGON);
     glColor3ub(0, 0, 0);
     glVertex2i(250,600-600);
     glVertex2i(250,600-530);
     glVertex2i(270,600-530);
     glVertex2i(270,600-600);
     glEnd();

     glBegin(GL_POLYGON);
     glColor3ub(0, 0, 0);
     glVertex2i(220,600-550);
     glVertex2i(220,600-540);
     glVertex2i(670,600-540);
     glVertex2i(670,600-550);
     glEnd();

     glBegin(GL_POLYGON);
     glColor3ub(0, 0, 0);
     glVertex2i(250+400-20,600-600);
     glVertex2i(250+400-20,600-530);
     glVertex2i(270+400-20,600-530);
     glVertex2i(270+400-20,600-600);
     glEnd();

}

void drawGrass (int ex) {
    glBegin(GL_POLYGON);
     glColor3ub(28, 121, 71);
     glVertex2i(0+ex,600-600);
     glVertex2i(0+ex,600-560);
     glVertex2i(200+ex,600-560);
     glVertex2i(200+ex,600-600);
    glEnd();
}

void drawPipe() {

        glBegin(GL_POLYGON);
        glColor3ub(68, 68, 68);
        glVertex2i(370-40,600-540+2);
        glVertex2i(370-40,600-520+2);
        glVertex2i(530+40,600-520+2);
        glVertex2i(530+40,600-540+2);
        glEnd();

}

void drawUVwater () {
    glBegin(GL_POLYGON);
     glColor3ub(47, 134, 166);
     glVertex2i(0,600-560);
     glVertex2i(0,600-500);
     glVertex2i(190,600-500);
     glVertex2i(190,600-560);
    glEnd();

    glBegin(GL_POLYGON);
     glColor3ub(47, 134, 166);
     glVertex2i(05+700,600-560);
     glVertex2i(05+700,600-500);
     glVertex2i(900,600-500);
     glVertex2i(900,600-560);
    glEnd();

    glBegin(GL_TRIANGLES);
     glColor3ub(47, 134, 166);
     glVertex2i(190,600-580);
     glVertex2i(190,600-500);
     glVertex2i(250,600-580);
    glEnd();

    glBegin(GL_TRIANGLES);
     glColor3ub(47, 134, 166);
     glVertex2i(705,600-580);
     glVertex2i(705,600-500);
     glVertex2i(650,600-580);
    glEnd();
}

int winPos(int winx, int winy) {

    if(winx >= 770 && winx <= 830 && winy >= 240 && winy <= 290)
        {pipeStuckX = 770; pipeStuckY = 600-240; return 1;}
    else if(winx >= 770 && winx <= 830 && winy >= 305 && winy <= 355)
        {pipeStuckX = 770; pipeStuckY = 600-305; return 2;}
    else if(winx >= 770 && winx <= 830 && winy >= 370 && winy <= 420)
        {pipeStuckX = 770; pipeStuckY = 600-370; return 3;}
    else if(winx >= 770 && winx <= 830 && winy >= 435 && winy <= 485)
        {pipeStuckX = 770; pipeStuckY = 600-435; return 4;}
    else if(winx >= 70 && winx <= 130 && winy >= 240 && winy <= 290)
        {pipeEndX = 130; pipeEndY = 600-240; return 5;}
    else if(winx >= 70 && winx <= 130 && winy >= 305 && winy <= 355)
        {pipeEndX = 130; pipeEndY = 600-305; return 6;}
    else if(winx >= 70 && winx <= 130 && winy >= 370 && winy <= 420)
        {pipeEndX = 130; pipeEndY = 600-370; return 7;}
    else if(winx >= 70 && winx <= 130 && winy >= 435 && winy <= 485)
        {pipeEndX = 130; pipeEndY = 600-435; return 8;}
    return 0;
}

bool pipeArea(int pipex, int pipey) {
    if(pipex >=370-40 && pipex <= 530+40 && pipey >= 520-2 && pipey <= 540-2)
            return true;
    return false;
}

void stuckPipe() {
     glBegin(GL_POLYGON);
        glColor3ub(151, 191, 180);
        glVertex2i(pipeStuckX - 100,pipeStuckY - 5);
        glVertex2i(pipeStuckX,pipeStuckY - 5);
        glVertex2i(pipeStuckX,pipeStuckY - 45);
        glVertex2i(pipeStuckX - 100,pipeStuckY - 45);
    glEnd();
}


void pipeLined(int StuckX, int StuckY, int EndX, int EndY) {
    glBegin(GL_POLYGON);
        glColor3ub(151, 191, 180);
        glVertex2i(StuckX,StuckY - 45);
        glVertex2i(StuckX,StuckY - 5);
        glVertex2i(EndX,EndY - 5);
        glVertex2i(EndX,EndY - 45);
        glEnd();
}

void checkPipePos() {
    if(pipePos == 0)
        drawPipe();
    else if (pipePos == 1) {
         glBegin(GL_POLYGON);
        glColor3ub(162, 219, 250);
        glVertex2i(310-20,600-540+2+5);
        glVertex2i(310-20,600-520+2+5);
        glVertex2i(530+60,600-520+2+5);
        glVertex2i(530+60,600-540+2+5);
        glEnd();
    }
    else if (pipePos == 2)
        stuckPipe();
    else if (pipePos == 3)
        pipeLined(pipeStuckX, pipeStuckY, pipeEndX, pipeEndY);
}

void drawHouseOne (void) {
    // Building

//Main
    glBegin(GL_POLYGON);
     glColor3ub(63, 7, 19);
     glVertex2i(30,600-500);
     glVertex2i(30,600-220+20);
     glVertex2i(170,600-220+20);
     glVertex2i(170,600-500);
    glEnd();
//Side Shadow
    glBegin(GL_POLYGON);
     glColor3ub(38, 0, 27);
     glVertex2i(170,600-500);
     glVertex2i(170,600-220+20);
     glVertex2i(185,600-240);
     glVertex2i(185,600-500);
    glEnd();
//Stripe
    glBegin(GL_POLYGON);
     glColor3ub(248, 248, 248);
     glVertex2i(30,600-235+20);
     glVertex2i(30,600-225+20);
     glVertex2i(170,600-225+20);
     glVertex2i(170,600-235+20);
    glEnd();
//Window
int Y1 = 600-240, Y2 = 600-290;
for (int i = 0; i < 4; i++) {
    glBegin(GL_POLYGON);
     glColor3ub(221, 221, 221);
     glVertex2i(70,Y2);
     glVertex2i(70,Y1);
     glVertex2i(130,Y1);
     glVertex2i(130,Y2);
    glEnd();
    Y1 = Y1 - (50 + 15);
    Y2 = Y2 - (50 + 15);
}

}

void drawHouseTwo(void) {
        // Building2

//Main2
    glBegin(GL_POLYGON);
     glColor3ub(52, 91, 99);
     glVertex2i(30+700,600-500);
     glVertex2i(30+700,600-220+20);
     glVertex2i(170+700,600-220+20);
     glVertex2i(170+700,600-500);
    glEnd();
//Side Shadow2
    glBegin(GL_POLYGON);
     glColor3ub(44, 57, 75);
     glVertex2i(170+700,600-500);
     glVertex2i(170+700,600-220+20);
     glVertex2i(185+700,600-240);
     glVertex2i(185+700,600-500);
    glEnd();
//Stripe2
    glBegin(GL_POLYGON);
     glColor3ub(212, 236, 221);
     glVertex2i(730,600-235+20);
     glVertex2i(730,600-225+20);
     glVertex2i(870,600-225+20);
     glVertex2i(870,600-235+20);
    glEnd();
//Window2
int Y1 = 600-240, Y2 = 600-290;
for (int i = 0; i < 4; i++) {
    glBegin(GL_POLYGON);
     glColor3ub(221, 221, 221);
     glVertex2i(770,Y2);
     glVertex2i(770,Y1);
     glVertex2i(830,Y1);
     glVertex2i(830,Y2);
    glEnd();
    Y1 = Y1 - (50 + 15);
    Y2 = Y2 - (50 + 15);
}

}

void myDisplay(void){


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    MovingScaledCarReverse();
    Sun();
    cloud_three();
    cloud_four();
    cloud_one();
    cloud_two();
    cloud_five();
    cloud_six();
    drawRiver();
    drawUVwater();
    drawBridge();
    drawHouseOne();
    drawHouseTwo();
    drawGrass(0);
    drawGrass(700);

    checkPipePos();

	glFlush();
}

void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            printf("clicked at (%d, %d)\n", x, y);
            if (pipeArea(x, y)) {
                    pipePos++;
                    glutPostRedisplay();
            }
            else if(winPos(x, y) >= 1 && winPos(x, y) <= 4) {
                winRight = winPos(x,y);
                Human = true;
                pipePos++;
                glutPostRedisplay();
            }
            else if(winPos(x, y) >= 5 && winPos(x, y) <= 8) {
                winLeft = winPos(x,y);
                pipePos++;
                printf("piped at (%d, %d)\n", pipeEndX, pipeEndY);
                glutPostRedisplay();
            }
        }
        }


    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(move_right);
        }
        break;
    case GLUT_MIDDLE_BUTTON:
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(NULL);
        }
        break;
    default:
        break;
    }
}

void myInit (void) {
glClearColor(.40, .110, 1.0, 0.0);;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,900.0,0.0,600.0);
}

int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (900, 600);
glutInitWindowPosition (150, 100);
glutCreateWindow ("Polaroid");
glutDisplayFunc(myDisplay);
glutMouseFunc(handleMouse);
myInit ();
glutTimerFunc(20, TireRotate, 0);
glutTimerFunc(20, MoveCarReverse, 0);
glutMainLoop();
}

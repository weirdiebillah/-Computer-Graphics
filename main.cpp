#include<bits/stdc++.h>
#define PI 3.14159265
#include<cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include<windows.h>
using namespace std;



GLfloat positionsunn = 0.0f;
GLfloat speedsunn = 0.001f;
GLfloat positionCloud1 = 0.0f;
GLfloat speedCloud1 = 0.002f;
GLfloat positionCloud2 = 0.0f;
GLfloat speedCloud2 = 0.0025f;
GLfloat positionCloud3 = 0.0f;
GLfloat speedCloud3 = 0.00209f;
GLfloat positionBoat1 = 0.0f;
GLfloat speedBoat1 = 0.008f;
GLfloat positionPlane = 0.0f;
GLfloat speedPlane = -0.0155f;
GLfloat positionBus = 0.0f;
GLfloat speedBus = -0.01f;

GLfloat position1 = 0.0f;
GLfloat position2 = 0.0f;
GLfloat fishpos = 0.0f;
GLfloat fishpos2 = 0.0f;
GLfloat fishspeed = 0.01f;
bool flagfish=true;
GLfloat speed = 5.0f;
float angle=45.0;
bool rainday=false;
float _rain=0.0f;
float sky_r=0.0f;
float sky_g=0.745f;
float sky_b=1.0f;
GLfloat sunpos = 0.0f;
GLfloat boat_clr1 = 102;
GLfloat boat_clr2 = 0;
GLfloat boat_clr3 = 255;
GLfloat house_clr1 = 255;
GLfloat house_clr2 = 153;
GLfloat house_clr3 = 0;
GLfloat house_roofclr1 = 255;
GLfloat house_roofclr2 = 153;
GLfloat house_roofclr3 = 0;

void rain_sound()
{
    PlaySound("rain1.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
}

void night_sound()
{
    PlaySound("night.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
}

void bus_sound()
{
    PlaySound("bus1.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
}

void dinrat(int value)
{
    if (positionsunn>=0.5 && positionsunn<=1.0)
    {
        rainday=true;
        sky_r=0.172;
        sky_g=0.219;
        sky_b=0.271;
        boat_clr1=153;
        boat_clr2=255;
        boat_clr3=204;
        house_clr1 = 153;
        house_clr2 = 204;
        house_clr3 = 255;
        glutTimerFunc(2000,dinrat,0);
        night_sound();
    }

    else if (positionsunn>=0.0)
    {
        sky_r=0.0f;
        sky_g=0.745f;
        sky_b=1.0f;
        boat_clr1=255;
        boat_clr2=102;
        boat_clr3=255;
        house_clr1 = 255;
        house_clr2 = 153;
        house_clr3 = 0;
        glutTimerFunc(2000,dinrat,0);

    }
    else
    {

        sky_r=0.0f;
        sky_g=0.0f;
        sky_b=0.0f;
        boat_clr1=255;
        boat_clr2=255;
        boat_clr3=255;
        house_clr1 = 51;
        house_clr2 = 204;
        house_clr3 = 255;
        house_roofclr1 = 26;
        house_roofclr2 = 117;
        house_roofclr3 = 255;

        glutTimerFunc(100,dinrat,0);

    }
}

void draw_circle(float x,float y,float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 255, 0);
    int i;
    int lineAmount = 100;
    GLfloat twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}

void updatesunn(int value)
{
    if(positionsunn > 1.0)
        positionsunn = -1.0f;
    positionsunn += speedsunn;
    glutPostRedisplay();
    glutTimerFunc(10, updatesunn, 0);
}


void updatesun(int value)
{

    glBegin(GL_POLYGON);

    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/100;
        float r=0.1;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y);
    }
    glEnd();
    glutPostRedisplay();


}

void upfish(int val)
{
    if(fishpos==.3&&flagfish)
    {
        flagfish=false;
    }
    else
        flagfish =true;
    if(fishpos>.6)
    {
        fishpos=0;
        fishpos2=0;
        flagfish=true;
    }


    if (fishpos>.3&&flagfish)
    {
        fishpos2-=fishspeed;
        glutTimerFunc(100, upfish, 0);
    }
    else
    {
        glutTimerFunc(100, upfish, 0);
    }
    fishpos+=fishspeed;
}

void update(int value)
{
    positionCloud1 += speedCloud1;
    if(positionCloud1 > 1.8)
    {
        positionCloud1 = -0.2f;
    }
    positionCloud2 += speedCloud2;
    if(positionCloud2 > 1.5)
    {
        positionCloud2 = -0.4f;
    }
    positionCloud3 += speedCloud3;
    if(positionCloud3 > 1.0)
    {
        positionCloud3 = -1.6f;
    }
    positionBoat1 += speedBoat1;
    if(positionBoat1 > 1.875)
    {
        positionBoat1 = -1.0f;
    }
    positionPlane += speedPlane;
    if(positionPlane < -1.875)
    {
        positionPlane = 0.8f;
    }

    positionBus += speedBus;
    if(positionBus < -1.875)
    {
        bus_sound();
        positionBus = 0.5f;
    }

    glutPostRedisplay();

    glutTimerFunc(100, update, 0);
}



void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

///Rain Add
void Rain(int value)
{
    if(rainday)
    {
        _rain+=0.01f;
        glBegin(GL_POINTS);
        for(int i=1; i<=100; i++)
        {
            int x=rand(),y=rand();
            x%=820;
            y%=520;
            float tmpx=float(x)/820;
            float tmpy=float(y)/520;
            float mintmpx=(-1)*tmpx;
            float mintmpy=(-1)*tmpy;

            ///+ + AXIS RAIN
            glBegin(GL_LINES);
            glColor3f(1.0, 1.0, 1.0);
            glVertex2d(tmpx,tmpy);
            glVertex2d(tmpx+0.05,tmpy+0.05);
            glEnd();

            ///+ - AXIS RAIN
            glBegin(GL_LINES);
            glVertex2d(tmpx,mintmpy);
            glVertex2d(tmpx+0.05,mintmpy+0.05);
            glEnd();

            ///- + Axis Rain
            glBegin(GL_LINES);
            glColor3f(1.0, 1.0, 1.0);
            glVertex2d(mintmpx,tmpy);
            glVertex2d(mintmpx+0.05,tmpy+0.05);
            glEnd();
            ///- - Axis Rain
            glBegin(GL_LINES);
            glColor3f(1.0, 1.0, 1.0);
            glVertex2d(mintmpx,mintmpy);
            glVertex2d(mintmpx+0.05,mintmpy+0.05);
            glEnd();
        }
        glutPostRedisplay();
        glutTimerFunc(5,Rain,0);
        glFlush();
    }
}

void drawSun() //sun
{


    glPushMatrix();
    glTranslatef(0.0f,-positionsunn, 0.0f);

    glBegin(GL_POLYGON);

    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50;
        float r=0.1;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y);
    }
    glEnd();
     glPopMatrix();
    glutPostRedisplay();
}


void drawCircle(float x,float y,float radius)
{

    glPushMatrix();
    glTranslatef(positionsunn,0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 255);
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
    glPopMatrix();
    glutPostRedisplay();
}
void fish(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2)
{
    glTranslatef(x1,y1,0);
    glScalef(x2,y2,1);
    //fish body
    glBegin (GL_QUADS);
    glColor3ub(255,255,0);
    glVertex2f(-0.2f,0.0f);
    glVertex2f(0.0f,-0.1f);
    glVertex2f(0.3f,0.0f);
    glVertex2f(0.00f,0.1f);
    glEnd();
    //eye
    int i;
    GLfloat x=-0.1f;
    GLfloat y=0.0f;
    GLfloat radius =.03f;
    int triangleAmount = 50; //# of triangles used to draw circle
    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0,0,0);
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
//dana of fish
    glBegin (GL_TRIANGLES);
    glColor3ub(255,255,0);
    glVertex2f(0.1f,0.120f);
    glVertex2f(0.05f,0.08f);
    glVertex2f(0.2f,0.03f);
    //tail
    glVertex2f(0.290f,0.0f);
    glVertex2f(0.350f,-0.05f);
    glVertex2f(0.350f,0.05f);
    glEnd();
    glLoadIdentity();
}

void drawCloud1(float x,float y,float radius) //cloud1
{
    //GLfloat  x=-.97f;GLfloat y=0.88; GLfloat radius =.035f;       //cloud1
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(61, 131, 231);
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();

    x=-.92f;
    y=0.88;
    radius =.055f;       //cloud1
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(61, 131, 231);
    i;
    lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();


    x=-.86f;
    y=0.88;
    radius =.035f;       //cloud1
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(61, 131, 231);
    i;
    lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
    glutPostRedisplay();
}

void drawCloud2(float x,float y,float radius) //cloud2
{
    //x=-.57f; y=0.88;  radius =.035f;       //cloud2
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 255);
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();


    x=-.52f;
    y=0.88;
    radius =.055f;       //cloud2
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 255);
    i;
    lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();

    x=-.46f;
    y=0.88;
    radius =.035f;       //cloud2
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 255);
    i;
    lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
    glutPostRedisplay();

}

void drawCloud3(float x,float y,float radius) //cloud3
{
    //x=.46f; y=0.88;  radius =.035f;       //cloud3
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(61, 131, 231);
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();


    x=.52f;
    y=0.88;
    radius =.055f;       //cloud3
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(61, 131, 231);
    i;
    lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();

    x=.57f;
    y=0.88;
    radius =.035f;       //cloud3
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(61, 131, 231);
    i;
    lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
    glutPostRedisplay();

}

void drawBoat1()
{
    glBegin(GL_POLYGON);//boat2
    glColor3f(0.0,1.0, 1.0);
    glVertex2f(-0.833f, -0.66f);
    glVertex2f(-0.33f, -0.66f);
    glVertex2f(-0.25f, -0.583f);
    glVertex2f(-0.916f, -0.583f);
    glEnd();
    glBegin(GL_POLYGON);
    //glColor3f(1.0,1.0, 0.4);
    glColor3ub(0,0,0);
    glVertex2f(-0.833f, -0.583f);
    glVertex2f(-0.33f, -0.583f);
    glVertex2f(-0.416f, -0.5f);
    glVertex2f(-0.75f, -0.5f);
    glEnd();

    ////Boat windows
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.75f,-0.566f);
    glVertex2f(-0.7f,-0.566f);
    glVertex2f(-0.7,-0.516f);
    glVertex2f(-0.75f,-0.516f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.633f,-0.566f);
    glVertex2f(-0.583f,-0.566f);
    glVertex2f(-0.583,-0.516f);
    glVertex2f(-0.633f,-0.516f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.516f,-0.566f);
    glVertex2f(-0.46f,-0.566f);
    glVertex2f(-0.46f,-0.516f);
    glVertex2f(-0.516f,-0.516f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.833f,-0.6833f);
    glVertex2f(-0.33f,-0.6833f);
    glVertex2f(-0.33f,-0.66f);
    glVertex2f(-0.833f,-0.66f);
    glEnd();

//end of boat 1

    glTranslatef(-0.6,-0.6,0.0);
    glScalef(0.7,.5,.0);
    glBegin(GL_POLYGON);//boat2
    glColor3f(0.0,0.0, 1.0);
    glVertex2f(-0.833f, -0.66f);
    glVertex2f(-0.33f, -0.66f);
    glVertex2f(-0.25f, -0.583f);
    glVertex2f(-0.916f, -0.583f);
    glEnd();
    glBegin(GL_POLYGON);
    //glColor3f(1.0,1.0, 0.4);
    glColor3ub(0,0,0);
    glVertex2f(-0.833f, -0.583f);
    glVertex2f(-0.33f, -0.583f);
    glVertex2f(-0.416f, -0.5f);
    glVertex2f(-0.75f, -0.5f);
    glEnd();

    ////Boat windows
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.75f,-0.566f);
    glVertex2f(-0.7f,-0.566f);
    glVertex2f(-0.7,-0.516f);
    glVertex2f(-0.75f,-0.516f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.633f,-0.566f);
    glVertex2f(-0.583f,-0.566f);
    glVertex2f(-0.583,-0.516f);
    glVertex2f(-0.633f,-0.516f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.516f,-0.566f);
    glVertex2f(-0.46f,-0.566f);
    glVertex2f(-0.46f,-0.516f);
    glVertex2f(-0.516f,-0.516f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.833f,-0.6833f);
    glVertex2f(-0.33f,-0.6833f);
    glVertex2f(-0.33f,-0.66f);
    glVertex2f(-0.833f,-0.66f);
    glEnd();
    ///end of boat 2

    glTranslatef(2.5,0.7,0.0);
    glScalef(0.7,.7,.0);
    glBegin(GL_POLYGON);//boat2
    glColor3f(1.0,0.0, 1.0);
    glVertex2f(-0.833f, -0.66f);
    glVertex2f(-0.33f, -0.66f);
    glVertex2f(-0.25f, -0.583f);
    glVertex2f(-0.916f, -0.583f);
    glEnd();
    glBegin(GL_POLYGON);
    //glColor3f(1.0,1.0, 0.4);
    glColor3ub(0,0,0);
    glVertex2f(-0.833f, -0.583f);
    glVertex2f(-0.33f, -0.583f);
    glVertex2f(-0.416f, -0.5f);
    glVertex2f(-0.75f, -0.5f);
    glEnd();

    ////Boat windows
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.75f,-0.566f);
    glVertex2f(-0.7f,-0.566f);
    glVertex2f(-0.7,-0.516f);
    glVertex2f(-0.75f,-0.516f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.633f,-0.566f);
    glVertex2f(-0.583f,-0.566f);
    glVertex2f(-0.583,-0.516f);
    glVertex2f(-0.633f,-0.516f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.516f,-0.566f);
    glVertex2f(-0.46f,-0.566f);
    glVertex2f(-0.46f,-0.516f);
    glVertex2f(-0.516f,-0.516f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(boat_clr1,boat_clr2,boat_clr3);
    glVertex2f(-0.833f,-0.6833f);
    glVertex2f(-0.33f,-0.6833f);
    glVertex2f(-0.33f,-0.66f);
    glVertex2f(-0.833f,-0.66f);
    glEnd();

//end of boat 3
}

void drawPlane() //plane...check
{
    glTranslatef(0.43,1.50,0);
    glBegin(GL_TRIANGLES);
//front
    glColor3ub(205, 133, 118);
    glVertex2f(0.3f,-0.750f);
    glVertex2f(0.4f,-0.8f);
    glVertex2f(0.4f,-0.7f);
    glEnd();

//body
    glBegin(GL_POLYGON);

    glColor3ub(255, 255, 204);
    glVertex2f(0.4f,-0.7f);
    glVertex2f(0.4f,-0.8f);
    glVertex2f(0.650f,-0.8f);
    glVertex2f(0.650f,-0.7f);

    glEnd();
//back
    glBegin(GL_QUADS);

    glColor3ub(255, 255, 204);
    glVertex2f(0.650f,-0.7f);
    glVertex2f(0.650f,-0.8f);
    glVertex2f(0.7f,-0.8f);
    glVertex2f(0.7f,-0.620f);

    //wind
    glColor3ub(173, 191, 88);
    glVertex2f(0.550f,-0.610f);
    glVertex2f(0.450f,-0.7f);
    glVertex2f(0.520f,-0.7f);
    glVertex2f(0.6f,-0.630f);
//window
    glColor3ub(97, 198, 195);
    glVertex2f(0.450f,-0.730f);
    glVertex2f(0.450f,-0.760f);
    glVertex2f(0.5f,-0.760f);
    glVertex2f(0.5f,-0.730f);
//window
    glColor3ub(97, 198, 195);
    glVertex2f(0.550f,-0.730f);
    glVertex2f(0.550f,-0.760f);
    glVertex2f(0.6f,-0.760f);
    glVertex2f(0.6f,-0.730f);
    glEnd();

//wheel

//1st wheel

    int i;
    GLfloat x=0.450f;
    GLfloat y=-0.820f;
    GLfloat radius =0.02;
    int triangleAmount = 20;

    GLfloat twicePi = 2.0f * PI;
    glColor3ub(255,0,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();


    //2nd wheel
    int i1;
    GLfloat x1=0.570f;
    GLfloat y1=-0.820f;
    GLfloat radius1 =0.02;
    int triangleAmount1 = 20;

    GLfloat twicePi1 = 2.0f * PI;
    glColor3ub(255,0,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    for(i1 = 0; i1 <= triangleAmount1; i1++)
    {
        glVertex2f(
            x1 + (radius1 * cos(i1 *  twicePi1 / triangleAmount1)),
            y1+ (radius1 * sin(i1 * twicePi1 / triangleAmount1))
        );
    }
    glEnd();

    //3rd wheel
    int i2;
    GLfloat x2=0.63f;
    GLfloat y2=-0.820f;
    GLfloat radius2 =0.02;
    int triangleAmount2 = 20;

    GLfloat twicePi2 = 2.0f * PI;
    glColor3ub(255,0,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x2, y2);
    for(i2 = 0; i2 <= triangleAmount2; i2++)
    {
        glVertex2f(
            x2 + (radius2 * cos(i2 *  twicePi2 / triangleAmount2)),
            y2+ (radius2 * sin(i2 * twicePi2 / triangleAmount2))
        );
    }
    glEnd();
}

void drawBus1()
{
    glScalef(0.5,0.5,0.0);
//glTranslatef(position,0.0,0.0);
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(0.5f, -0.166f);
    glVertex2f(1.0f, -0.166f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(0.55f, 0.0f);
    glVertex2f(0.5f, -0.033f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(0.5f, -0.1f);
    glVertex2f(0.5166f, -0.1f);
    glVertex2f(0.5166f, -0.066f);
    glVertex2f(0.5f, -0.066f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(0.55f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 0.116f);
    glVertex2f(0.55f, 0.116f);
    glEnd();

    ////Buswindows///
    glBegin(GL_POLYGON);
    glColor3f(0.26,0.26,0.26);
    glVertex2f(0.5833f, 0.016f);
    glVertex2f(0.633f, 0.016f);
    glVertex2f(0.633f, 0.1f);
    glVertex2f(0.5833f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.26,0.26,0.26);
    glVertex2f(0.65f, 0.016f);
    glVertex2f(0.7f, 0.016f);
    glVertex2f(0.7f, 0.1f);
    glVertex2f(0.65f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.26,0.26,0.26);
    glVertex2f(0.716f, 0.016f);
    glVertex2f(0.766f, 0.016f);
    glVertex2f(0.766f, 0.1f);
    glVertex2f(0.716f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.26,0.26,0.26);
    glVertex2f(0.783f, 0.016f);
    glVertex2f(0.833f, 0.016f);
    glVertex2f(0.833f, 0.1f);
    glVertex2f(0.783f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.26,0.26,0.26);
    glVertex2f(0.85f, 0.016f);
    glVertex2f(0.9f, 0.016f);
    glVertex2f(0.9f, 0.1f);
    glVertex2f(0.85f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.26,0.26,0.26);
    glVertex2f(0.916f, 0.016f);
    glVertex2f(0.966f, 0.016f);
    glVertex2f(0.966f, 0.1f);
    glVertex2f(0.916f, 0.1f);
    glEnd();

    float x=.58f;
    float y=-0.18;
    float radius =.025f;       //first wheel
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 204, 255);
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();

    x=.88f;
    y=-0.18;
    radius =.025f;       //second wheel
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 204, 255);
    i;
    lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    twicePi = 2.0f * PI;
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();
    glClearColor(sky_r, sky_g, sky_b, 1.0f); // Set background color to black and opaque
    //glClear(GL_COLOR_BUFFER_BIT);
    //gluOrtho2D(-2.0,2.0,-2.0,2.0);

    glPushMatrix(); //Sun
    glTranslatef(0.8, 0.8, 0.0);
    glColor3f(1.0,1.0,0.0);
    drawSun();
    glPopMatrix();




    glBegin(GL_QUADS);//road
    glColor3f(0.698,0.745, 0.7098);
    glVertex2f(-1.0,-.3);
    glVertex2f(1.0,-.3);
    glVertex2f(1.0,0.0);
    glVertex2f(-1.0,0.0);
    glEnd();
    glBegin(GL_QUADS);//road black
    glColor3ub(32,32,32);
    glVertex2f(-1.0,-0.0);
    glVertex2f(-1.0,-.15);
    glVertex2f(1.0,-.15);
    glVertex2f(1.0,-0.0);
    glEnd();

    glBegin(GL_QUADS);//road black
    glColor3ub(32,32,32);
    glVertex2f(-1.0,-0.18);
    glVertex2f(-1.0,-.35);
    glVertex2f(1.0,-.35);
    glVertex2f(1.0,-0.18);
    glEnd();

    ////Border///

    glBegin(GL_POLYGON);
    glColor3f(0.2,0.098, 0.0);
    glVertex2f(-1.0f, -0.33f);
    glVertex2f(1.0f, -0.33f);
    glVertex2f(1.0f, -0.416f);
    glVertex2f(-1.0f, -0.416f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0, 0.0);
    glVertex2f(-1.0f, -0.35f);
    glVertex2f(1.0f, -0.35f);
    glVertex2f(1.0f, -0.33f);
    glVertex2f(-1.0f, -0.33f);
    glEnd();

    glBegin(GL_QUADS);//water
    glColor3ub(65, 108, 198);
    glVertex2f(-1.0,-1.0);
    glVertex2f(1.0,-1.0);
    glVertex2f(1.0,-.3);
    glVertex2f(-1.0,-.3);
    glEnd();

    glTranslatef(-fishpos,fishpos+(fishpos2*2),0);
    fish(.5,-.9,.5,.5);
    glLoadIdentity();

    glBegin(GL_QUADS);//water
    glColor3ub(65, 108, 198);
    glVertex2f(-1.0,-1.0);
    glVertex2f(1.0,-1.0);
    glVertex2f(1.0,-.7);
    glVertex2f(-1.0,-.7);
    glEnd();

    glPushMatrix(); //plane
    glTranslatef(positionPlane, 0.0f, 0.0f);
    drawPlane();
    glPopMatrix();

///tree on the left2
    glTranslatef(1.35,0.2,0.0);//tree on the right left corner
    glScalef(0.65,0.4,1.0);
    glBegin(GL_QUADS);
    glColor3ub(153, 51, 0);//tree main
    glVertex2f(-0.9f,0.0f);
    glVertex2f(-0.9f,0.4f);
    glVertex2f(-0.95f,0.4f);
    glVertex2f(-0.95f,0.0f);

    glVertex2f(-0.95f,0.12f);//tree hand left
    glVertex2f(-0.95f,0.15f);
    glVertex2f(-0.98f,0.25f);
    glVertex2f(-0.98f,0.22f);

    glVertex2f(-0.9f,0.17f);//tree right hand
    glVertex2f(-0.9f,0.14f);
    glVertex2f(-0.87f,0.25f);
    glVertex2f(-0.87f,0.22f);

    glEnd();



    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.47f,.1f);//for tree circle middle 1.0

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.35f,.05f);//for tree circle 1.1


    glColor3ub(0, 153, 0);
    draw_circle(-0.95,0.35f,.05f);//for tree circle 1.2


    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.52f,.05f);//for tree circle 1.3

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.4f,.05f);//for tree circle 1.4

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.47f,.05f);//for tree circle 1.5

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.5f,.05f);//for tree circle 1.6

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.54f,.05f);//for tree circle 1.7

    glColor3ub(0, 153, 0);
    draw_circle(-0.92,0.54f,.05f);//for tree circle 1.8

    glColor3ub(0, 153, 0);
    draw_circle(-0.98,0.25f,.03f);//for tree circle left

    glColor3ub(0, 153, 0);
    draw_circle(-0.87,0.25f,.03f);//for tree circle right

    glLoadIdentity();




///house on the left

    glTranslatef(-1.0f,0.0f, 0.0f);
    glScalef(0.6,0.6,1.0);
    glRotatef(180,0.0,1.0,0.0);
    glBegin(GL_POLYGON);//house Quads
    glColor3ub(153, 51, 51);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.3f);
    glVertex2f(-0.3f,0.3f);
    glVertex2f(-0.3f,0.5f);
    glVertex2f(-0.6f,0.7f);
    glVertex2f(-0.8f,0.5f);
    glVertex2f(-0.8f,0.0f);
    glEnd();
    glBegin(GL_POLYGON);//house rooftop
    glColor3ub(house_roofclr1,house_roofclr2,house_roofclr3);
    glVertex2f(-0.05f,0.3f);
    glVertex2f(-0.1f,0.45f);
    glVertex2f(-0.3f,0.45f);
    glVertex2f(-0.3f,0.3f);
    glEnd();
    glBegin(GL_QUADS);//house rooftop window
    glColor3ub(0, 153, 255);
    glVertex2f(-0.15f,0.35f);
    glVertex2f(-0.15f,0.4f);
    glVertex2f(-0.2f,0.4f);
    glVertex2f(-0.2f,0.35f);
    glBegin(GL_QUADS);//house window 1
    glColor3ub(0, 153, 255);
    glVertex2f(-0.7f,0.35f);
    glVertex2f(-0.6f,0.35f);
    glVertex2f(-0.6f,0.5f);
    glVertex2f(-0.7f,0.5f);
    glColor3ub(0, 153, 255);//house down window 1
    glVertex2f(-0.7f,0.25f);
    glVertex2f(-0.6f,0.25f);
    glVertex2f(-0.6f,0.1f);
    glVertex2f(-0.7f,0.1f);
    glBegin(GL_QUADS);//house window 2
    glColor3ub(0, 153, 255);
    glVertex2f(-0.5f,0.35f);
    glVertex2f(-0.4f,0.35f);
    glVertex2f(-0.4f,0.5f);
    glVertex2f(-0.5f,0.5f);
    glColor3ub(0, 153, 255);//house down door 2
    glVertex2f(-0.15f,0.1f);
    glVertex2f(-0.15f,0.2f);
    glVertex2f(-0.25f,0.2f);
    glVertex2f(-0.25f,0.1f);
    glColor3ub(153, 102, 51);//house down door 2
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-0.4f,0.25f);
    glVertex2f(-0.4f,0.02f);
    glVertex2f(-0.5f,0.02f);
    glEnd();
    glBegin(GL_LINES);//house window 1 lines
    glColor3ub(0, 0, 0);
    glVertex2f(-0.7f,0.4f);
    glVertex2f(-0.6f,0.4f);
    glVertex2f(-0.65f,0.425f);
    glVertex2f(-0.65f,0.5f);
    glVertex2f(-0.5f,0.4f);//house window 2 lines
    glVertex2f(-0.4f,0.4f);
    glVertex2f(-0.45f,0.425f);
    glVertex2f(-0.45f,0.5f);
    glEnd();
    glLoadIdentity();



    glTranslatef(1.0f,0.0f, 0.0f);//house on the middle 3
    glScalef(0.4,0.4,1.0);
    glBegin(GL_POLYGON);//house Quads
    glColor3ub(153, 51, 51);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.3f);
    glVertex2f(-0.3f,0.3f);
    glVertex2f(-0.3f,0.5f);
    glVertex2f(-0.6f,0.7f);
    glVertex2f(-0.8f,0.5f);
    glVertex2f(-0.8f,0.0f);
    glEnd();
    glBegin(GL_POLYGON);//house rooftop
    glColor3ub(house_roofclr1,house_roofclr2,house_roofclr3);
    glVertex2f(-0.05f,0.3f);
    glVertex2f(-0.1f,0.45f);
    glVertex2f(-0.3f,0.45f);
    glVertex2f(-0.3f,0.3f);
    glEnd();
    glBegin(GL_QUADS);//house rooftop window
    glColor3ub(0, 153, 255);
    glVertex2f(-0.15f,0.35f);
    glVertex2f(-0.15f,0.4f);
    glVertex2f(-0.2f,0.4f);
    glVertex2f(-0.2f,0.35f);
    glBegin(GL_QUADS);//house window 1
    glColor3ub(0, 153, 255);
    glVertex2f(-0.7f,0.35f);
    glVertex2f(-0.6f,0.35f);
    glVertex2f(-0.6f,0.5f);
    glVertex2f(-0.7f,0.5f);
    glColor3ub(0, 153, 255);//house down window 1
    glVertex2f(-0.7f,0.25f);
    glVertex2f(-0.6f,0.25f);
    glVertex2f(-0.6f,0.1f);
    glVertex2f(-0.7f,0.1f);
    glBegin(GL_QUADS);//house window 2
    glColor3ub(0, 153, 255);
    glVertex2f(-0.5f,0.35f);
    glVertex2f(-0.4f,0.35f);
    glVertex2f(-0.4f,0.5f);
    glVertex2f(-0.5f,0.5f);
    glColor3ub(0, 153, 255);//house down door 2
    glVertex2f(-0.15f,0.1f);
    glVertex2f(-0.15f,0.2f);
    glVertex2f(-0.25f,0.2f);
    glVertex2f(-0.25f,0.1f);
    glColor3ub(153, 102, 51);//house down door 2
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-0.4f,0.25f);
    glVertex2f(-0.4f,0.02f);
    glVertex2f(-0.5f,0.02f);
    glEnd();
    glBegin(GL_LINES);//house window 1 lines
    glColor3ub(0, 0, 0);
    glVertex2f(-0.7f,0.4f);
    glVertex2f(-0.6f,0.4f);
    glVertex2f(-0.65f,0.425f);
    glVertex2f(-0.65f,0.5f);
    glVertex2f(-0.5f,0.4f);//house window 2 lines
    glVertex2f(-0.4f,0.4f);
    glVertex2f(-0.45f,0.425f);
    glVertex2f(-0.45f,0.5f);
    glEnd();
    glLoadIdentity();


    glTranslatef(0.4f,0.4f, 0.0f);//right side house
    glScalef(0.4,0.6,1.0);
    glBegin(GL_POLYGON);//house Quads
    glColor3ub(153, 51, 51);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.3f);
    glVertex2f(-0.3f,0.3f);
    glVertex2f(-0.3f,0.5f);
    glVertex2f(-0.6f,0.7f);
    glVertex2f(-0.8f,0.5f);
    glVertex2f(-0.8f,0.0f);
    glEnd();

    glBegin(GL_POLYGON);//house rooftop
    glColor3ub(house_roofclr1,house_roofclr2,house_roofclr3);
    glVertex2f(-0.05f,0.3f);
    glVertex2f(-0.1f,0.45f);
    glVertex2f(-0.3f,0.45f);
    glVertex2f(-0.3f,0.3f);
    glEnd();


    glBegin(GL_QUADS);//house rooftop window
    glColor3ub(0, 153, 255);
    glVertex2f(-0.15f,0.35f);
    glVertex2f(-0.15f,0.4f);
    glVertex2f(-0.2f,0.4f);
    glVertex2f(-0.2f,0.35f);

    glBegin(GL_QUADS);//house window 1
    glColor3ub(0, 153, 255);
    glVertex2f(-0.7f,0.35f);
    glVertex2f(-0.6f,0.35f);
    glVertex2f(-0.6f,0.5f);
    glVertex2f(-0.7f,0.5f);

    glColor3ub(0, 153, 255);//house down window 1
    glVertex2f(-0.7f,0.25f);
    glVertex2f(-0.6f,0.25f);
    glVertex2f(-0.6f,0.1f);
    glVertex2f(-0.7f,0.1f);

    glBegin(GL_QUADS);//house window 2
    glColor3ub(0, 153, 255);
    glVertex2f(-0.5f,0.35f);
    glVertex2f(-0.4f,0.35f);
    glVertex2f(-0.4f,0.5f);
    glVertex2f(-0.5f,0.5f);


    glColor3ub(0, 153, 255);//house down door 2
    glVertex2f(-0.15f,0.1f);
    glVertex2f(-0.15f,0.2f);
    glVertex2f(-0.25f,0.2f);
    glVertex2f(-0.25f,0.1f);


    glColor3ub(153, 102, 51);//house down door 2
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-0.4f,0.25f);
    glVertex2f(-0.4f,0.02f);
    glVertex2f(-0.5f,0.02f);
    glEnd();

    glBegin(GL_LINES);//house window 1 lines
    glColor3ub(0, 0, 0);
    glVertex2f(-0.7f,0.4f);
    glVertex2f(-0.6f,0.4f);

    glVertex2f(-0.65f,0.425f);
    glVertex2f(-0.65f,0.5f);

    glVertex2f(-0.5f,0.4f);//house window 2 lines
    glVertex2f(-0.4f,0.4f);

    glVertex2f(-0.45f,0.425f);
    glVertex2f(-0.45f,0.5f);
    glEnd();

    glLoadIdentity();

//tree on the road....................


    glTranslatef(0.1,0.0,0.0);//tree on the middle
    glRotatef(180,0.0,1.0,0.0);
    glBegin(GL_QUADS);
    glColor3ub(153, 51, 0);//tree main
    glVertex2f(-0.9f,0.0f);
    glVertex2f(-0.9f,0.4f);
    glVertex2f(-0.95f,0.4f);
    glVertex2f(-0.95f,0.0f);

    glVertex2f(-0.95f,0.12f);//tree hand left
    glVertex2f(-0.95f,0.15f);
    glVertex2f(-0.98f,0.25f);
    glVertex2f(-0.98f,0.22f);

    glVertex2f(-0.9f,0.17f);//tree right hand
    glVertex2f(-0.9f,0.14f);
    glVertex2f(-0.87f,0.25f);
    glVertex2f(-0.87f,0.22f);

    glEnd();



    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.47f,.1f);//for tree circle middle 1.0

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.35f,.05f);//for tree circle 1.1


    glColor3ub(0, 153, 0);
    draw_circle(-0.95,0.35f,.05f);//for tree circle 1.2


    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.52f,.05f);//for tree circle 1.3

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.4f,.05f);//for tree circle 1.4

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.47f,.05f);//for tree circle 1.5

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.5f,.05f);//for tree circle 1.6

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.54f,.05f);//for tree circle 1.7

    glColor3ub(0, 153, 0);
    draw_circle(-0.92,0.54f,.05f);//for tree circle 1.8

    glColor3ub(0, 153, 0);
    draw_circle(-0.98,0.25f,.03f);//for tree circle left

    glColor3ub(0, 153, 0);
    draw_circle(-0.87,0.25f,.03f);//for tree circle right

    glLoadIdentity();


    glTranslatef(0.55,0.0,0.0);//tree on the middle
    glScalef(0.65,0.55,1.0);
    glBegin(GL_QUADS);
    glColor3ub(153, 51, 0);//tree main
    glVertex2f(-0.9f,0.0f);
    glVertex2f(-0.9f,0.4f);
    glVertex2f(-0.95f,0.4f);
    glVertex2f(-0.95f,0.0f);

    glVertex2f(-0.95f,0.12f);//tree hand left
    glVertex2f(-0.95f,0.15f);
    glVertex2f(-0.98f,0.25f);
    glVertex2f(-0.98f,0.22f);

    glVertex2f(-0.9f,0.17f);//tree right hand
    glVertex2f(-0.9f,0.14f);
    glVertex2f(-0.87f,0.25f);
    glVertex2f(-0.87f,0.22f);

    glEnd();



    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.47f,.1f);//for tree circle middle 1.0

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.35f,.05f);//for tree circle 1.1


    glColor3ub(0, 153, 0);
    draw_circle(-0.95,0.35f,.05f);//for tree circle 1.2


    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.52f,.05f);//for tree circle 1.3

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.4f,.05f);//for tree circle 1.4

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.47f,.05f);//for tree circle 1.5

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.5f,.05f);//for tree circle 1.6

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.54f,.05f);//for tree circle 1.7

    glColor3ub(0, 153, 0);
    draw_circle(-0.92,0.54f,.05f);//for tree circle 1.8

    glColor3ub(0, 153, 0);
    draw_circle(-0.98,0.25f,.03f);//for tree circle left

    glColor3ub(0, 153, 0);
    draw_circle(-0.87,0.25f,.03f);//for tree circle right

    glLoadIdentity();



    glTranslatef(0.1,0.55,0.0);//tree on the left  corner
    glScalef(0.65,0.4,1.0);
    glBegin(GL_QUADS);
    glColor3ub(153, 51, 0);//tree main
    glVertex2f(-0.9f,0.0f);
    glVertex2f(-0.9f,0.4f);
    glVertex2f(-0.95f,0.4f);
    glVertex2f(-0.95f,0.0f);

    glVertex2f(-0.95f,0.12f);//tree hand left
    glVertex2f(-0.95f,0.15f);
    glVertex2f(-0.98f,0.25f);
    glVertex2f(-0.98f,0.22f);

    glVertex2f(-0.9f,0.17f);//tree right hand
    glVertex2f(-0.9f,0.14f);
    glVertex2f(-0.87f,0.25f);
    glVertex2f(-0.87f,0.22f);

    glEnd();



    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.47f,.1f);//for tree circle middle 1.0

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.35f,.05f);//for tree circle 1.1


    glColor3ub(0, 153, 0);
    draw_circle(-0.95,0.35f,.05f);//for tree circle 1.2


    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.52f,.05f);//for tree circle 1.3

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.4f,.05f);//for tree circle 1.4

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.47f,.05f);//for tree circle 1.5

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.5f,.05f);//for tree circle 1.6

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.54f,.05f);//for tree circle 1.7

    glColor3ub(0, 153, 0);
    draw_circle(-0.92,0.54f,.05f);//for tree circle 1.8

    glColor3ub(0, 153, 0);
    draw_circle(-0.98,0.25f,.03f);//for tree circle left

    glColor3ub(0, 153, 0);
    draw_circle(-0.87,0.25f,.03f);//for tree circle right

    glLoadIdentity();

    glBegin(GL_QUADS);
    glColor3ub(153, 51, 0);//tree main
    glVertex2f(-0.9f,0.0f);
    glVertex2f(-0.9f,0.4f);
    glVertex2f(-0.95f,0.4f);
    glVertex2f(-0.95f,0.0f);

    glVertex2f(-0.95f,0.12f);//tree hand left
    glVertex2f(-0.95f,0.15f);
    glVertex2f(-0.98f,0.25f);
    glVertex2f(-0.98f,0.22f);

    glVertex2f(-0.9f,0.17f);//tree right hand
    glVertex2f(-0.9f,0.14f);
    glVertex2f(-0.87f,0.25f);
    glVertex2f(-0.87f,0.22f);

    glEnd();



    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.47f,.1f);//for tree circle middle 1.0

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.35f,.05f);//for tree circle 1.1


    glColor3ub(0, 153, 0);
    draw_circle(-0.95,0.35f,.05f);//for tree circle 1.2


    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.52f,.05f);//for tree circle 1.3

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.4f,.05f);//for tree circle 1.4

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.47f,.05f);//for tree circle 1.5

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.5f,.05f);//for tree circle 1.6

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.54f,.05f);//for tree circle 1.7

    glColor3ub(0, 153, 0);
    draw_circle(-0.92,0.54f,.05f);//for tree circle 1.8

    glColor3ub(0, 153, 0);
    draw_circle(-0.98,0.25f,.03f);//for tree circle left

    glColor3ub(0, 153, 0);
    draw_circle(-0.87,0.25f,.03f);//for tree circle right



    glTranslatef(-0.8f,0.0f, 0.0f);//side house rotated
    glRotatef(180,0.0,1.0,0.0);

    glBegin(GL_QUADS);
    glColor3ub(153, 51, 0);//tree main
    glVertex2f(-0.9f,0.0f);
    glVertex2f(-0.9f,0.4f);
    glVertex2f(-0.95f,0.4f);
    glVertex2f(-0.95f,0.0f);

    glVertex2f(-0.95f,0.12f);//tree hand left
    glVertex2f(-0.95f,0.15f);
    glVertex2f(-0.98f,0.25f);
    glVertex2f(-0.98f,0.22f);

    glVertex2f(-0.9f,0.17f);//tree right hand
    glVertex2f(-0.9f,0.14f);
    glVertex2f(-0.87f,0.25f);
    glVertex2f(-0.87f,0.22f);

    glEnd();



    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.47f,.1f);//for tree circle middle 1.0

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.35f,.05f);//for tree circle 1.1


    glColor3ub(0, 153, 0);
    draw_circle(-0.95,0.35f,.05f);//for tree circle 1.2


    glColor3ub(0, 153, 0);
    draw_circle(-0.925,0.52f,.05f);//for tree circle 1.3

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.4f,.05f);//for tree circle 1.4

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.47f,.05f);//for tree circle 1.5

    glColor3ub(0, 153, 0);
    draw_circle(-0.85,0.5f,.05f);//for tree circle 1.6

    glColor3ub(0, 153, 0);
    draw_circle(-0.88,0.54f,.05f);//for tree circle 1.7

    glColor3ub(0, 153, 0);
    draw_circle(-0.92,0.54f,.05f);//for tree circle 1.8

    glColor3ub(0, 153, 0);
    draw_circle(-0.98,0.25f,.03f);//for tree circle left

    glColor3ub(0, 153, 0);
    draw_circle(-0.87,0.25f,.03f);//for tree circle right





    //house on the road......................



    glTranslatef(-0.2f,0.8f, 0.0f);//right side house
    glScalef(-0.0,0.6,1.0);
    glBegin(GL_POLYGON);//house Quads
    glColor3ub(153, 51, 51);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.3f);
    glVertex2f(-0.3f,0.3f);
    glVertex2f(-0.3f,0.5f);
    glVertex2f(-0.6f,0.7f);
    glVertex2f(-0.8f,0.5f);
    glVertex2f(-0.8f,0.0f);
    glEnd();

    glBegin(GL_POLYGON);//house rooftop
    glColor3ub(house_roofclr1,house_roofclr2,house_roofclr3);
    glVertex2f(-0.05f,0.3f);
    glVertex2f(-0.1f,0.45f);
    glVertex2f(-0.3f,0.45f);
    glVertex2f(-0.3f,0.3f);
    glEnd();


    glBegin(GL_QUADS);//house rooftop window
    glColor3ub(0, 153, 255);
    glVertex2f(-0.15f,0.35f);
    glVertex2f(-0.15f,0.4f);
    glVertex2f(-0.2f,0.4f);
    glVertex2f(-0.2f,0.35f);

    glBegin(GL_QUADS);//house window 1
    glColor3ub(0, 153, 255);
    glVertex2f(-0.7f,0.35f);
    glVertex2f(-0.6f,0.35f);
    glVertex2f(-0.6f,0.5f);
    glVertex2f(-0.7f,0.5f);

    glColor3ub(0, 153, 255);//house down window 1
    glVertex2f(-0.7f,0.25f);
    glVertex2f(-0.6f,0.25f);
    glVertex2f(-0.6f,0.1f);
    glVertex2f(-0.7f,0.1f);

    glBegin(GL_QUADS);//house window 2
    glColor3ub(0, 153, 255);
    glVertex2f(-0.5f,0.35f);
    glVertex2f(-0.4f,0.35f);
    glVertex2f(-0.4f,0.5f);
    glVertex2f(-0.5f,0.5f);


    glColor3ub(0, 153, 255);//house down door 2
    glVertex2f(-0.15f,0.1f);
    glVertex2f(-0.15f,0.2f);
    glVertex2f(-0.25f,0.2f);
    glVertex2f(-0.25f,0.1f);


    glColor3ub(153, 102, 51);//house down door 2
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-0.4f,0.25f);
    glVertex2f(-0.4f,0.02f);
    glVertex2f(-0.5f,0.02f);
    glEnd();

    glBegin(GL_LINES);//house window 1 lines
    glColor3ub(0, 0, 0);
    glVertex2f(-0.7f,0.4f);
    glVertex2f(-0.6f,0.4f);

    glVertex2f(-0.65f,0.425f);
    glVertex2f(-0.65f,0.5f);

    glVertex2f(-0.5f,0.4f);//house window 2 lines
    glVertex2f(-0.4f,0.4f);

    glVertex2f(-0.45f,0.425f);
    glVertex2f(-0.45f,0.5f);
    glEnd();

    glLoadIdentity();



    glTranslatef(-0.2f,0.6f, 0.0f);
    glScalef(-0.0,0.6,1.0);
    glBegin(GL_POLYGON);//house Quads
    glColor3ub(153, 51, 51);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.3f);
    glVertex2f(-0.3f,0.3f);
    glVertex2f(-0.3f,0.5f);
    glVertex2f(-0.6f,0.7f);
    glVertex2f(-0.8f,0.5f);
    glVertex2f(-0.8f,0.0f);
    glEnd();

    glBegin(GL_POLYGON);//house rooftop
    glColor3ub(house_roofclr1,house_roofclr2,house_roofclr3);
    glVertex2f(-0.05f,0.3f);
    glVertex2f(-0.1f,0.45f);
    glVertex2f(-0.3f,0.45f);
    glVertex2f(-0.3f,0.3f);
    glEnd();


    glBegin(GL_QUADS);//house rooftop window
    glColor3ub(0, 153, 255);
    glVertex2f(-0.15f,0.35f);
    glVertex2f(-0.15f,0.4f);
    glVertex2f(-0.2f,0.4f);
    glVertex2f(-0.2f,0.35f);

    glBegin(GL_QUADS);//house window 1
    glColor3ub(0, 153, 255);
    glVertex2f(-0.7f,0.35f);
    glVertex2f(-0.6f,0.35f);
    glVertex2f(-0.6f,0.5f);
    glVertex2f(-0.7f,0.5f);

    glColor3ub(0, 153, 255);//house down window 1
    glVertex2f(-0.7f,0.25f);
    glVertex2f(-0.6f,0.25f);
    glVertex2f(-0.6f,0.1f);
    glVertex2f(-0.7f,0.1f);

    glBegin(GL_QUADS);//house window 2
    glColor3ub(0, 153, 255);
    glVertex2f(-0.5f,0.35f);
    glVertex2f(-0.4f,0.35f);
    glVertex2f(-0.4f,0.5f);
    glVertex2f(-0.5f,0.5f);


    glColor3ub(0, 153, 255);//house down door 2
    glVertex2f(-0.15f,0.1f);
    glVertex2f(-0.15f,0.2f);
    glVertex2f(-0.25f,0.2f);
    glVertex2f(-0.25f,0.1f);


    glColor3ub(153, 102, 51);//house down door 2
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-0.4f,0.25f);
    glVertex2f(-0.4f,0.02f);
    glVertex2f(-0.5f,0.02f);
    glEnd();

    glBegin(GL_LINES);//house window 1 lines
    glColor3ub(0, 0, 0);
    glVertex2f(-0.7f,0.4f);
    glVertex2f(-0.6f,0.4f);

    glVertex2f(-0.65f,0.425f);
    glVertex2f(-0.65f,0.5f);

    glVertex2f(-0.5f,0.4f);//house window 2 lines
    glVertex2f(-0.4f,0.4f);

    glVertex2f(-0.45f,0.425f);
    glVertex2f(-0.45f,0.5f);
    glEnd();

    glLoadIdentity();

    glTranslatef(-0.2f,0.3f, 0.0f);//upper house 2
    glScalef(-0.3,0.8,1.0);
    glBegin(GL_POLYGON);//house Quads
    glColor3ub(102, 51, 0);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.3f);
    glVertex2f(-0.3f,0.3f);
    glVertex2f(-0.3f,0.5f);
    glVertex2f(-0.6f,0.7f);
    glVertex2f(-0.8f,0.5f);
    glVertex2f(-0.8f,0.0f);
    glEnd();

    glBegin(GL_POLYGON);//house rooftop
    glColor3ub(house_roofclr1,house_roofclr2,house_roofclr3);
    glVertex2f(-0.05f,0.3f);
    glVertex2f(-0.1f,0.45f);
    glVertex2f(-0.3f,0.45f);
    glVertex2f(-0.3f,0.3f);
    glEnd();


    glBegin(GL_QUADS);//house rooftop window
    glColor3ub(0, 153, 255);
    glVertex2f(-0.15f,0.35f);
    glVertex2f(-0.15f,0.4f);
    glVertex2f(-0.2f,0.4f);
    glVertex2f(-0.2f,0.35f);

    glBegin(GL_QUADS);//house window 1
    glColor3ub(0, 153, 255);
    glVertex2f(-0.7f,0.35f);
    glVertex2f(-0.6f,0.35f);
    glVertex2f(-0.6f,0.5f);
    glVertex2f(-0.7f,0.5f);

    glColor3ub(0, 153, 255);//house down window 1
    glVertex2f(-0.7f,0.25f);
    glVertex2f(-0.6f,0.25f);
    glVertex2f(-0.6f,0.1f);
    glVertex2f(-0.7f,0.1f);

    glBegin(GL_QUADS);//house window 2
    glColor3ub(0, 153, 255);
    glVertex2f(-0.5f,0.35f);
    glVertex2f(-0.4f,0.35f);
    glVertex2f(-0.4f,0.5f);
    glVertex2f(-0.5f,0.5f);

    glColor3ub(0, 153, 255);//house down door 2
    glVertex2f(-0.15f,0.1f);
    glVertex2f(-0.15f,0.2f);
    glVertex2f(-0.25f,0.2f);
    glVertex2f(-0.25f,0.1f);

    glColor3ub(153, 102, 51);//house down door 2
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-0.4f,0.25f);
    glVertex2f(-0.4f,0.02f);
    glVertex2f(-0.5f,0.02f);
    glEnd();

    glBegin(GL_LINES);//house window 1 lines
    glColor3ub(0, 0, 0);
    glVertex2f(-0.7f,0.4f);
    glVertex2f(-0.6f,0.4f);

    glVertex2f(-0.65f,0.425f);
    glVertex2f(-0.65f,0.5f);

    glVertex2f(-0.5f,0.4f);//house window 2 lines
    glVertex2f(-0.4f,0.4f);

    glVertex2f(-0.45f,0.425f);
    glVertex2f(-0.45f,0.5f);
    glEnd();

    glLoadIdentity();

    glTranslatef(-0.4f,0.4f, 0.0f);//upper house 1
    glScalef(-0.3,0.8,1.0);
    glBegin(GL_POLYGON);//house Quads
    glColor3ub(102, 51, 0);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.3f);
    glVertex2f(-0.3f,0.3f);
    glVertex2f(-0.3f,0.5f);
    glVertex2f(-0.6f,0.7f);
    glVertex2f(-0.8f,0.5f);
    glVertex2f(-0.8f,0.0f);
    glEnd();

    glBegin(GL_POLYGON);//house rooftop
    glColor3ub(house_roofclr1,house_roofclr2,house_roofclr3);
    glVertex2f(-0.05f,0.3f);
    glVertex2f(-0.1f,0.45f);
    glVertex2f(-0.3f,0.45f);
    glVertex2f(-0.3f,0.3f);
    glEnd();


    glBegin(GL_QUADS);//house rooftop window
    glColor3ub(0, 153, 255);
    glVertex2f(-0.15f,0.35f);
    glVertex2f(-0.15f,0.4f);
    glVertex2f(-0.2f,0.4f);
    glVertex2f(-0.2f,0.35f);

    glBegin(GL_QUADS);//house window 1
    glColor3ub(0, 153, 255);
    glVertex2f(-0.7f,0.35f);
    glVertex2f(-0.6f,0.35f);
    glVertex2f(-0.6f,0.5f);
    glVertex2f(-0.7f,0.5f);

    glColor3ub(0, 153, 255);//house down window 1
    glVertex2f(-0.7f,0.25f);
    glVertex2f(-0.6f,0.25f);
    glVertex2f(-0.6f,0.1f);
    glVertex2f(-0.7f,0.1f);

    glBegin(GL_QUADS);//house window 2
    glColor3ub(0, 153, 255);
    glVertex2f(-0.5f,0.35f);
    glVertex2f(-0.4f,0.35f);
    glVertex2f(-0.4f,0.5f);
    glVertex2f(-0.5f,0.5f);


    glColor3ub(0, 153, 255);//house down door 2
    glVertex2f(-0.15f,0.1f);
    glVertex2f(-0.15f,0.2f);
    glVertex2f(-0.25f,0.2f);
    glVertex2f(-0.25f,0.1f);

    glColor3ub(153, 102, 51);//house down door 2
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-0.4f,0.25f);
    glVertex2f(-0.4f,0.02f);
    glVertex2f(-0.5f,0.02f);
    glEnd();

    glBegin(GL_LINES);//house window 1 lines
    glColor3ub(0, 0, 0);
    glVertex2f(-0.7f,0.4f);
    glVertex2f(-0.6f,0.4f);

    glVertex2f(-0.65f,0.425f);
    glVertex2f(-0.65f,0.5f);

    glVertex2f(-0.5f,0.4f);//house window 2 lines
    glVertex2f(-0.4f,0.4f);

    glVertex2f(-0.45f,0.425f);
    glVertex2f(-0.45f,0.5f);
    glEnd();

    glLoadIdentity();

    glBegin(GL_POLYGON);//house Quads
    glColor3ub(house_clr1,house_clr2,house_clr3);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.3f);
    glVertex2f(-0.3f,0.3f);
    glVertex2f(-0.3f,0.5f);
    glVertex2f(-0.6f,0.7f);
    glVertex2f(-0.8f,0.5f);
    glVertex2f(-0.8f,0.0f);
    glEnd();

    glBegin(GL_POLYGON);//house rooftop
    glColor3ub(house_roofclr1,house_roofclr2,house_roofclr3);
    glVertex2f(-0.05f,0.3f);
    glVertex2f(-0.1f,0.45f);
    glVertex2f(-0.3f,0.45f);
    glVertex2f(-0.3f,0.3f);
    glEnd();


    glBegin(GL_QUADS);//house rooftop window
    glColor3ub(0, 153, 255);
    glVertex2f(-0.15f,0.35f);
    glVertex2f(-0.15f,0.4f);
    glVertex2f(-0.2f,0.4f);
    glVertex2f(-0.2f,0.35f);

    glBegin(GL_QUADS);//house window 1
    glColor3ub(0, 153, 255);
    glVertex2f(-0.7f,0.35f);
    glVertex2f(-0.6f,0.35f);
    glVertex2f(-0.6f,0.5f);
    glVertex2f(-0.7f,0.5f);

    glColor3ub(0, 153, 255);//house down window 1
    glVertex2f(-0.7f,0.25f);
    glVertex2f(-0.6f,0.25f);
    glVertex2f(-0.6f,0.1f);
    glVertex2f(-0.7f,0.1f);

    glBegin(GL_QUADS);//house window 2
    glColor3ub(0, 153, 255);
    glVertex2f(-0.5f,0.35f);
    glVertex2f(-0.4f,0.35f);
    glVertex2f(-0.4f,0.5f);
    glVertex2f(-0.5f,0.5f);


    glColor3ub(0, 153, 255);//house down door 2
    glVertex2f(-0.15f,0.1f);
    glVertex2f(-0.15f,0.2f);
    glVertex2f(-0.25f,0.2f);
    glVertex2f(-0.25f,0.1f);

    glColor3ub(153, 102, 51);//house down door 2
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-0.4f,0.25f);
    glVertex2f(-0.4f,0.02f);
    glVertex2f(-0.5f,0.02f);
    glEnd();

    glBegin(GL_LINES);//house window 1 lines
    glColor3ub(0, 0, 0);
    glVertex2f(-0.7f,0.4f);
    glVertex2f(-0.6f,0.4f);

    glVertex2f(-0.65f,0.425f);
    glVertex2f(-0.65f,0.5f);

    glVertex2f(-0.5f,0.4f);//house window 2 lines
    glVertex2f(-0.4f,0.4f);

    glVertex2f(-0.45f,0.425f);
    glVertex2f(-0.45f,0.5f);
    glEnd();

    glTranslatef(-0.1f,0.0f, 0.0f);//side house rotated
    glRotatef(180,0.0,1.0,0.0);
    glBegin(GL_POLYGON);//house Quads
    glColor3ub(house_clr1,house_clr2,house_clr3);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.3f);
    glVertex2f(-0.3f,0.3f);
    glVertex2f(-0.3f,0.5f);
    glVertex2f(-0.6f,0.7f);
    glVertex2f(-0.8f,0.5f);
    glVertex2f(-0.8f,0.0f);
    glEnd();

    glBegin(GL_POLYGON);//house rooftop
    glColor3ub(house_roofclr1,house_roofclr2,house_roofclr3);
    glVertex2f(-0.05f,0.3f);
    glVertex2f(-0.1f,0.45f);
    glVertex2f(-0.3f,0.45f);
    glVertex2f(-0.3f,0.3f);
    glEnd();


    glBegin(GL_QUADS);//house rooftop window
    glColor3ub(0, 153, 255);
    glVertex2f(-0.15f,0.35f);
    glVertex2f(-0.15f,0.4f);
    glVertex2f(-0.2f,0.4f);
    glVertex2f(-0.2f,0.35f);

    glBegin(GL_QUADS);//house window 1
    glColor3ub(0, 153, 255);
    glVertex2f(-0.7f,0.35f);
    glVertex2f(-0.6f,0.35f);
    glVertex2f(-0.6f,0.5f);
    glVertex2f(-0.7f,0.5f);

    glColor3ub(0, 153, 255);//house down window 1
    glVertex2f(-0.7f,0.25f);
    glVertex2f(-0.6f,0.25f);
    glVertex2f(-0.6f,0.1f);
    glVertex2f(-0.7f,0.1f);

    glBegin(GL_QUADS);//house window 2
    glColor3ub(0, 153, 255);
    glVertex2f(-0.5f,0.35f);
    glVertex2f(-0.4f,0.35f);
    glVertex2f(-0.4f,0.5f);
    glVertex2f(-0.5f,0.5f);


    glColor3ub(0, 153, 255);//house down door 2
    glVertex2f(-0.15f,0.1f);
    glVertex2f(-0.15f,0.2f);
    glVertex2f(-0.25f,0.2f);
    glVertex2f(-0.25f,0.1f);


    glColor3ub(153, 102, 51);//house down door 2
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-0.4f,0.25f);
    glVertex2f(-0.4f,0.02f);
    glVertex2f(-0.5f,0.02f);
    glEnd();

    glBegin(GL_LINES);//house window 1 lines
    glColor3ub(0, 0, 0);
    glVertex2f(-0.7f,0.4f);
    glVertex2f(-0.6f,0.4f);

    glVertex2f(-0.65f,0.425f);
    glVertex2f(-0.65f,0.5f);

    glVertex2f(-0.5f,0.4f);//house window 2 lines
    glVertex2f(-0.4f,0.4f);

    glVertex2f(-0.45f,0.425f);
    glVertex2f(-0.45f,0.5f);
    glEnd();
    glLoadIdentity();


//end of building

    glPushMatrix();
    glTranslatef(positionBus, 0.0f, 0.0f);
    drawBus1();
    glPopMatrix();

    glPushMatrix(); //cloud1
    glTranslatef(positionCloud1, 0.0f, 0.0f);
    drawCloud1(-.97f,0.88,0.035);
    glPopMatrix();

    glPushMatrix(); //cloud2
    glTranslatef(positionCloud2, 0.0f, 0.0f);
    drawCloud2(-.57,0.88,0.035);
    glPopMatrix();

    glPushMatrix(); //cloud3
    glTranslatef(positionCloud3, 0.0f, 0.0f);
    drawCloud3(0.46,0.88,0.035);
    glPopMatrix();

    glPushMatrix(); //boat1
    glTranslatef(positionBoat1, 0.0f, 0.0f);
    drawBoat1();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}


void handleKeypress(unsigned char key, int x, int y)
{
    if(key=='r'||key=='R')
    {
        rainday=true;
        rain_sound();
        Rain(_rain);
        sky_r=0.172;
        sky_g=0.219;
        sky_b=0.271;
    }
    else if(key=='S'||key=='s')
    {
        rainday=false;
        sky_r=0.0f;
        sky_g=0.745f;
        sky_b=1.0f;
    }

    else if(key=='N'||key=='n')
    {
        rainday=false;
        night_sound();
        sky_r=0.25f;
        sky_g=0.26f;
        sky_b=0.28f;
    }

    else if(key=='M'||key=='m')
    {
        rainday=false;
        sky_r=0.08f; //90,31,133
        sky_g=0.081f;
        sky_b=0.08f;


    }
}





int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(820,520);
    glutCreateWindow("IT'S A PROJECT");
    glutDisplayFunc(display);
    init();
    glutTimerFunc(1000, update, 0);
    glutTimerFunc(100, upfish, 0);
    glutTimerFunc(1, updatesunn, 0);
    glutTimerFunc(2000,dinrat,0);
    glutKeyboardFunc(handleKeypress);
    bus_sound();
    glutMainLoop();
    return 0;
}

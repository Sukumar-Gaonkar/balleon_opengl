#include <stdio.h>
#include <math.h>
#include <windows.h>
#ifdef __APPLE__
#include<GLUT/glut.h>
#include<openGL/openGL.h>

#else
#include<GL/glut.h>
#endif

typedef struct
{
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
} ball;

void const_ball(float x,float y,float a,float b,ball *e);

int i,j,cursor_pos_x=0,cursor_pos_y=0;
int ball_no=4;
float speed=0.02;
ball enemy[4];


//float x1=-1.0,x2=2.0,y11=0.0,y2=-2.0;
//float x1_i=0.015,x2_i=-0.015,x1_j=0.000,x2_j=0.015;
static int flag=1;

void const_ball(float x,float y,float a,float b,ball *obj)
{
    obj->pos_x=x;
    obj->pos_y=y;
    obj->vel_x=a * speed;
    obj->vel_y=b * speed;

}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(45,w/h,1,200);

}

void keyPressed(int key,int x,int y)
{
    if(key==GLUT_KEY_LEFT)
    {}
}

void mouse_click(int button, int state, int x, int y) {
if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    printf("Left click\n");
}

void mouse_co_ordinates(int x,int y)
{
    //printf("x: %d  y: %d\n",x,y);

}

void drawBall(ball *obj)
{

    glColor3f(1.0,0.0,0.0);

    glPushMatrix();

    glTranslatef(obj->pos_x,obj->pos_y,-5.0);
    //glTranslatef(x1,y11,-5.0);
    glutSolidSphere(0.2,20,20);

    glPopMatrix();

}


void ball_ball_coll(ball *obj1,ball *obj2)
{

    // Ball - Ball collision
    float val = sqrt((obj2->pos_x - obj1->pos_x)*(obj2->pos_x - obj1->pos_x) + (obj2->pos_y - obj1->pos_y)*(obj2->pos_y - obj1->pos_y));
    if(val < 0.4)
    {
         //printf("coll: %f - %f : %f - %f\n",obj1->pos_x,obj1->pos_y,obj2->pos_x,obj2->pos_y);

        //printf("%f %f %f %f %f %f\n",x1,x2,x1_i,x1_j,x2_i,x2_j);
        float temp = obj1->vel_x;
        obj1->vel_x = obj2->vel_x;
        obj2->vel_x = temp;

        temp = obj1->vel_y;
        obj1->vel_y = obj2->vel_y;
        obj2->vel_y = temp;
        //printf("%f %f %f %f %f %f\n",x1,x2,x1_i,x1_j,x2_i,x2_j);
        //flag = 0;

    }

}


void ball_wall_coll(ball *obj)
{
    if((obj->pos_x + 0.4) >= 2 || (obj->pos_x - 0.4) <= -2)
    {
        obj->vel_x = obj->vel_x * -1;
                //printf("coll x");
    }
    if((obj->pos_y + 0.4) >= 2 || (obj->pos_y - 0.4) <= -2)
    {
        obj->vel_y = obj->vel_y * -1;
        //printf("coll y");
    }

}


void update()
{

    if(flag)
        {
            for(i=0;i<ball_no;i++)
            {
                // Detect Ball - Wall collision
                ball_wall_coll(&enemy[i]);

                // Detect Ball - Ball collision
                for(j=i+1;j<ball_no;j++)
                {
                    if(i == 3)
                        break;

                    ball_ball_coll(&enemy[i],&enemy[j]);
                }

                enemy[i].pos_x += enemy[i].vel_x;
                enemy[i].pos_y += enemy[i].vel_y;
            }

        }
        else
        {
            //printf("stoped\n");

        }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    //glShadeModel(GL_SMOOTH);
    //drawBall1();

    //drawBall2();
    for(i=0;i<ball_no;i++)
    {
        //printf("%d\n",i);
         drawBall(&enemy[i]);
    }

    update();

    glutSwapBuffers();
}


int main(int argc,char **argv)
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize(500,500);

    glutCreateWindow("Collision Window");

    initRendering();
    //printf("%d %d",GLUT_SCREEN_WIDTH,GLUT_SCREEN_WIDTH);
    glutDisplayFunc(display);

    //Init
    const_ball(1.0,1.0,-.857,-0.514,&enemy[0]);
    const_ball(-1.5,0.2,0.514,-0.857,&enemy[1]);
    const_ball(0.6,-1.0,-0.919,0.394,&enemy[2]);
    const_ball(-0.4,-1.4,0.965,0.263,&enemy[3]);



    glutIdleFunc(display);

    glutReshapeFunc(reshape);

    glutMouseFunc(mouse_click);
    glutPassiveMotionFunc(mouse_co_ordinates);

    glutSpecialFunc(keyPressed);

    glutMainLoop();

    return(0);
}

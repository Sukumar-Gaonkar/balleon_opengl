#include <stdio.h>
#include <ctype.h>
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

}
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;

} ball;

void const_ball(float x,float y,float a,float b,ball *e);

int i,j,window_width=500,window_height=500,player_life = 3;
int ball_no=4;
float enemy_speed=0.07,player_speed=0.05;
ball enemy[4], player;
float cursor_pos_x=0,cursor_pos_y=0;


//float x1=-1.0,x2=2.0,y11=0.0,y2=-2.0;
//float x1_i=0.015,x2_i=-0.015,x1_j=0.000,x2_j=0.015;
static int flag=0;

void const_ball(float x,float y,float a,float b,ball *obj)
{
    obj->pos_x=x;
    obj->pos_y=y;
    obj->vel_x=a * enemy_speed;
    obj->vel_y=b * enemy_speed;

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
    {
         printf("Left click\n");
         flag = 1;
    }
}

void mouse_co_ordinates(int x,int y)
{
        cursor_pos_x = ((float)x/window_width - 0.5 ) * 4;
        cursor_pos_y = ((float)y/window_height - 0.5 ) * -4;

//      player.pos_x = 2;
//      player.pos_y = 2;


//        player.vel_x = (cursor_pos_x - player.pos_x) * player_speed;
//        player.vel_y = (cursor_pos_y - player.pos_y) * player_speed;
//printf("diff: %f  vel: %f\n",(cursor_pos_x - player.pos_x),player.vel_x);
//
//        player.vel_x = cursor_pos_x - player.pos_x;
//        player.vel_y = cursor_pos_y - player.pos_y;
//
        printf("player pos: %f %f  vel : %f %f\n",player.pos_x,player.pos_y,player.vel_x,player.vel_y);
}

void drawBall(ball *obj)
{
    //printf("Drawing ball\n");

    glColor3f(1.0,0.0,0.0);

    glPushMatrix();
    //printf("pos_x: %f  pos_y: %f\n",obj->pos_x,obj->pos_y);
    glTranslatef(obj->pos_x,obj->pos_y,-5.0);
    //printf("pos_x: %f  pos_y: %f\n",obj->pos_x,obj->pos_y);
    //glTranslatef(x1,y11,-5.0);
    glutSolidSphere(0.2,20,20);

    glPopMatrix();

}

void enemy_player_coll(ball *enemy)
{/*
    float val = sqrt((player.pos_x - enemy->pos_x)*(player.pos_x - enemy->pos_x) + (player.pos_y - enemy->pos_y)*(player.pos_y - enemy->pos_y));
    if(val < 0.4)
    {
        player_life--;
        if(player_life == 0);
            //flag = 0;
        float temp = player.vel_x;
        player.vel_x = enemy->vel_x;
        enemy->vel_x = temp;

        temp = player.vel_y;
        player.vel_y = enemy->vel_y;
        enemy->vel_y = temp;

    }
    */
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

        obj1->pos_x += obj1->vel_x;
        obj1->pos_y += obj1->vel_y;
        obj2->pos_x += obj2->vel_x;
        obj2->pos_y += obj2->vel_y;

        //printf("%f %f %f %f %f %f\n",x1,x2,x1_i,x1_j,x2_i,x2_j);
        //flag = 0;

    }

}


void ball_wall_coll(ball *obj)
{
    if((obj->pos_x + 0.2) >= 2)
    {
        obj->vel_x = obj->vel_x * -1;
        obj->pos_x = 1.8;
    }
    else if((obj->pos_x - 0.2) <= -2)
    {
        //printf("coll x %f\n",obj->vel_x);
        obj->vel_x = obj->vel_x * -1;
        obj->pos_x = -1.8;

    }
    if((obj->pos_y + 0.2) >= 2)
    {
        obj->vel_y = obj->vel_y * -1;
        obj->pos_y = 1.8;
    }
    else if((obj->pos_y - 0.2) <= -2)
    {
        obj->vel_y = obj->vel_y * -1;
        obj->pos_y = -1.8;
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
            if(i == 2)
                printf("%d: %f %f  %f %f\n",i,enemy[i].pos_x,enemy[i].pos_y,enemy[i].vel_y,enemy[i].vel_y);
        }



    }

    for(i=0;i<ball_no;i++)
    {
         enemy_player_coll(&enemy[i]);
    }


    float temp_x = (cursor_pos_x - player.pos_x);
    float temp_y = (cursor_pos_y - player.pos_y);
    float temp_xy = sqrt((temp_x * temp_x) + (temp_y * temp_y));
    //printf("temp: %f %f %f\n",temp_x,temp_y,temp_xy);
    if(temp_xy != 0)
    {
        player.vel_x = temp_x / temp_xy * player_speed;
        player.vel_y = temp_y / temp_xy * player_speed;
        //flag=0;
    }
//printf("done calculating vel  %f %f\n",player.vel_x,player.vel_y);
 //printf("before updating %f %f %f %f\n",player.pos_x,player.pos_y,player.vel_x,player.vel_y);
    player.pos_x += player.vel_x;
    player.pos_y += player.vel_y;
    //printf("updating player pos: %f %f vel: %f %f\n",player.pos_x,player.pos_y,player.vel_x,player.vel_y);
    //flag=0;


}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    //glShadeModel(GL_SMOOTH);
    //drawBall1();

    //drawBall2();
    if(flag)
     update();

    // Draw Enemies

    for(i=0;i<ball_no;i++)
    {
        //printf("%d\n",i);
         drawBall(&enemy[i]);
    }


    // Draw player
    drawBall(&player);


    glutSwapBuffers();
}


int main(int argc,char **argv)
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize(window_width,window_height);

    glutCreateWindow("Collision Window");

    initRendering();
    //printf("%d %d",GLUT_SCREEN_WIDTH,GLUT_SCREEN_WIDTH);
    glutDisplayFunc(display);

    //Init
    // instantiate Enemies

    const_ball(1.0,1.0,-0.857,-0.514,&enemy[0]);
    const_ball(-1.5,0.2,0.514,-0.857,&enemy[1]);
    const_ball(0.6,-1.0,-0.919,0.394,&enemy[2]);
    const_ball(-0.4,-1.4,0.965,0.263,&enemy[3]);


    // Instantiate player
    const_ball(0,0,0,0,&player);
//printf("Creating object %f %f\n",player.vel_x,player.vel_y);


    glutIdleFunc(display);

    glutReshapeFunc(reshape);

    glutMouseFunc(mouse_click);
    glutPassiveMotionFunc(mouse_co_ordinates);

    glutSpecialFunc(keyPressed);

    glutMainLoop();

    return(0);
}

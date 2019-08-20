#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdlib>
#include <cmath>
#define pi (2*acos(0.0))
int xx=0,yy=0,zz=0;
int c=0;
int bx=0,by=0,bz=0,b=0,fb=0,sb=0;
int cxx=0,cyy=0,czz=0;
int rxx=0,ryy=0,rzz=0;
char score_value[5];
int score=0;
using namespace std;
int mn1,mn2,mn3;
int startGame=0;
int gameEnd=0;
int gameOver=0;
int gameMenu=0;
int backToMenu=0;
int chaneWeapon=0;
int initial=0;
int flag=0;
int look=1;
int run=0;
int incri=0,startFly=0;
int add=0;
int cameraUp=0,cameraDown=0;
 int flg_fan_ang=0,fan_ang=0;
 double   ncameraAngle;

 double   ncameraAngleDelta;
 double   ncameraRadius;
 double    ncameraHeight;

int sph,scl,posx,inc;
double ang;
int drawgrid;
int drawaxes;
double angle;

struct point
{
	double x,y,z;
}position[10];
double cameraLookingX = 0;
double cameraLookingY = 0;
double cameraLookingZ = 0;


double cameraAngle =1.0;
double cameraRadius = 300;

double cameraX = 30;
double cameraY = 300;
double cameraHeight = 150;

double cameraAngleDelta = -0.0003;

double move_X = 0;
double move_Y = 0;
double move_Z = 0;
double speed = 30;
double ang_speed = 0.5;
int num_texture = -1;

GLuint menu0,menu1,mirror,paint1,paint2,grass,grass1,skyImage, abc,def,one,tree_w,tree_l,brek,flame;



/***************************** Texture Functions *******************************/
void initGame()
{

       cameraAngle=ncameraAngle;
    cameraAngleDelta=ncameraRadius;
    cameraAngleDelta=ncameraAngleDelta;

}
int loadBitmapImage(char *filename)
{
	int i, j = 0;
	FILE *l_file;
	unsigned char *l_texture;

	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++;

	if ((l_file = fopen(filename, "rb")) == NULL)
	{
		return (-1);
	}

	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);

	l_texture = (byte *)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i = 0; i < infoheader.biWidth * infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file);

		l_texture[j + 0] = rgb.rgbtRed;
		l_texture[j + 1] = rgb.rgbtGreen;
		l_texture[j + 2] = rgb.rgbtBlue;
		l_texture[j + 3] = 255;
		j += 4;
	}
	fclose(l_file);

	glBindTexture(GL_TEXTURE_2D, num_texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture);

	return (num_texture);
}

void loadAllImages()
{   menu0 = loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\menu.bmp");
    menu1 = loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\menu1.bmp");
	abc = loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images/floor.bmp");
	skyImage= loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images/sky2.bmp");
	paint1= loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\paint1.bmp");
	paint2= loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\paint2.bmp");
	mirror= loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\mirror.bmp");
	grass= loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\grass.bmp");
	grass1= loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\grass1.bmp");
	brek=loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\break.bmp");
	tree_w=loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\tree_w.bmp");
	tree_l=loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\tree_l.bmp");
	flame=loadBitmapImage("D:\\15th trimester\\Graphics Lab\\Computer Graphic\\Computer Graphic\\Lab\\Project\\images\\flame.bmp");
}

void welcome()
{

    glEnable(GL_TEXTURE_2D);
    {


     glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, menu0);


       glTranslated(0,-10,0);
        // glRotated(180,0,0,1);
       // glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{   glTexCoord2f(1, 0);
			glVertex3f(-150,-155, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-150,155, 0);
			glTexCoord2f(0, 1);
			glVertex3f(150,155, 0);

			glTexCoord2f(0, 0);
			glVertex3f(150,-155, 0);



		}
		glEnd();
}
 glPopMatrix();

}


}
void drawBitmapText(char *string,float x,float y,float z)
{
	char *c;
	glRasterPos3f(x, y,z);




	for (c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);


	}


}

void gameOverFunc()
{
	int heroVisible=0;
	int bulletVisible=0;

	/*

	glColor3f(1,0,0);
	drawBitmapText("Game Over ",0,-5,40);
	glColor3f(0,1,0);

	drawBitmapText("Score: ",0,-5,20);

	itoa(score, score_value, 10);
	drawBitmapText(score_value,6,-5,20);
	*/

	glColor3f(1,0,0);
	drawBitmapText("GAME OVER",22,-5,40);
	glColor3f(1,0,0);

	drawBitmapText("YOUR SCORE",22,-5,35);
	itoa(2, "a", 10);
	glColor3f(0,1,0);
	drawBitmapText("a",36,-5,35);

	glColor3f(1,1,1);
	drawBitmapText("THNKS FOR PLAYING",14,-5,20);

	drawBitmapText("FOR GOING TO MENU PRESS M",14,-5,16);


}


void gameStartFunc()
{
    glPushMatrix();
    {

	drawBitmapText("PRESS 'ENTER'",14,-12,100);
  }glPopMatrix();
}


void menuBG()
{

    glEnable(GL_TEXTURE_2D);
    {


     glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, menu1);


       glTranslated(0,-10,0);
        // glRotated(180,0,0,1);
       // glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{   glTexCoord2f(1, 0);
			glVertex3f(-150,-155, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-150,155, 0);
			glTexCoord2f(0, 1);
			glVertex3f(150,155, 0);

			glTexCoord2f(0, 0);
			glVertex3f(150,-155, 0);



		}
		glEnd();
}
 glPopMatrix();

}
}
void menuList()
{
    glPushMatrix();
    {

	drawBitmapText("PRESS 'p' FOR PLAY" ,14,-17,50);
	drawBitmapText("PRESS 'a' FOR ABOUT" ,14,-18,40);
    drawBitmapText("PRESS 's' FOR SELECT WEAPON" ,14,-25,30);
	drawBitmapText("PRESS 'Esc' FOR END" ,14,-18,20);
  }glPopMatrix();
}


void field()
{

    glEnable(GL_TEXTURE_2D);
    {
     // glScaled(.7,.5,.7);

     glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, grass);


       glTranslated(0,-10,0);
        // glRotated(180,0,0,1);
       // glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{   glTexCoord2f(1, 0);
			glVertex3f(-150,-155, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-150,155, 0);
			glTexCoord2f(0, 1);
			glVertex3f(150,155, 0);

			glTexCoord2f(0, 0);
			glVertex3f(150,-155, 0);



		}
		glEnd();
}
 glPopMatrix();

}


}

void field1()
{


     //glScaled(.3,.3,.3);

     glPushMatrix();
			{

			        glEnable(GL_TEXTURE_2D);
    {
       glBindTexture(GL_TEXTURE_2D, grass1);


       glTranslated(0,-10,0);
        // glRotated(180,0,0,1);
       // glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{   glTexCoord2f(1, 0);
			glVertex3f(-150,-155, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-150,155, 0);
			glTexCoord2f(0, 1);
			glVertex3f(150,155, 0);

			glTexCoord2f(0, 0);
			glVertex3f(150,-155, 0);



		}
		glEnd();
}
			}
 glPopMatrix();




}
/****************************** GridLines and Axes ***********************************/

void drawAxes()
{

		glBegin(GL_LINES);{
		    glColor3f(0, 1.0, 0);
//glVertex3f( 1000,0,0);
			//glVertex3f(-1000,0,0);

			glColor3f(0, 0, 1.0);
			//glVertex3f(0,-1000,0);
			//glVertex3f(0, 1000,0);

			glColor3f(1.0, 1.0, 1.0);
			//glVertex3f(0,0, 1000);
			//glVertex3f(0,0,-1000);
		}glEnd();

}
void triangle(){
    glEnable(GL_TEXTURE_2D);
    {


     glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);


       glTranslated(0,-10,0);
        // glRotated(180,0,0,1);
       // glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{   glTexCoord2f(1, 0);
			glVertex3f(0,11, 0);

			glTexCoord2f(1, 1);
			glVertex3f(0, 11, 0);
			glTexCoord2f(0, 1);
			glVertex3f(0,-10, 0);

			glTexCoord2f(0, 0);
			glVertex3f(1.7,-10, 0);



		}
		glEnd();
}
 glPopMatrix();

}

}

void rectangle()
{
    glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-100, 100, 0);

			glTexCoord2f(0, 0);
			glVertex3f(100, 100, 0);

			glTexCoord2f(1, 0);
			glVertex3f(100, -100, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-100, -100, 0);
		}
		glEnd();
}


void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);


		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}


void drawCircle(double radius)
{
    int i,segments=150;
    struct point points[200];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}
void filledCircle(){
    glPushMatrix();
    {

        double an=0;
        int i;
     for(i=0;i<380;i++){

         glRotated(an,0,0,1);
            triangle();
            an+=.9;

            }



     }glPopMatrix();


}

void coin()
{
    glPushMatrix();
    {
      filledCircle();
      glTranslated(0,0,5);
      filledCircle();

    }
    glPopMatrix();
    glPushMatrix();
			{

				glColor3f(.7, .6, 1);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,20,20,5,50,50);
			}
    glPopMatrix();

}
void drawCylinder(double radius,double height)
{
    int segments=250;
    int i;
    struct point points1[300];
    struct point points2[300];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points1[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points1[i].z=radius*sin(((double)i/(double)segments)*2*pi);
        points2[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points2[i].z=radius*sin(((double)i/(double)segments)*2*pi);
        points2[i].y=-height;
    }

    //draw segments using generated points
    int stacks=segments;
    for(i=0;i<segments;i++)
    {
        //glColor3f(0,.8,.5);
        glBegin(GL_LINES);
        {
			glVertex3f(points1[i].x,0,points1[i].z);
			glVertex3f(points1[i+1].x,0,points1[i+1].z);

			glVertex3f(points2[i].x,-height,points2[i].z);
			glVertex3f(points2[i+1].x,-height,points2[i+1].z);

			glVertex3f(points1[i].x,0,points1[i].z);
			glVertex3f(points2[i].x,-height,points2[i].z);


        }
        glEnd();
    }

}


void drawCone(double radius,double height)
{
    int i,segments=100;
    double shade;
    struct point points[200];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawSphere(double radius)
{
    int slices=100;
    int stacks=100;
	struct point points[200][300];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks+.3,(double)i/(double)stacks+.1,(double)i/(double)stacks+.3);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = r;//we start at angle = 0
    float y = 0;

    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}
void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0
    float y = 0;

    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}




//////HELICOPTER/////

void helicopter()
{
    glPushMatrix();
	{

		glEnable(GL_TEXTURE_2D);
		{

///#####helicoptor

    // *****body*****//
//glScaled(.4,.4,.4);
			glPushMatrix();
			{
                 glBindTexture(GL_TEXTURE_2D, paint1);
			     glTranslated(0,15,0);
				//glColor3f(1, .5, 1);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluSphere(obj,15,50, 50);
			}
			glPopMatrix();
		}

            glPushMatrix();
			{   glTranslated(0,-15,0);
				//glColor3f(1, .5, 1);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluSphere(obj,15,50, 50);
			}
			glPopMatrix();

            glPushMatrix();
			{
			    glTranslated(0,15,0);
			    glRotated(90,1,0,0);
				//glColor3f(.7, .6, 1);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,15,15,30,50,50);
			}
			glPopMatrix();

            glPushMatrix();
			{
			    glTranslated(0,15,0);
			    glRotated(90,1,0,0);
				//glColor3f(.7, .6, 1);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,15,15,30,50,50);
			}
			glPopMatrix();

            glPushMatrix();
			{   glTranslated(0,12,5);
			    glBindTexture(GL_TEXTURE_2D, paint2);
				//glColor3f(1, .5, .7);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluSphere(obj,15,50, 50);
			}
			glPopMatrix();

			glPushMatrix();
			{   glTranslated(0,-11,5);
				//glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluSphere(obj,15,50, 50);
			}
			glPopMatrix();

            glPushMatrix();
			{
			    glTranslated(0,15,5);
			    glRotated(90,1,0,0);
				//glColor3f(.7, .6, .7);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,15,15,24,50,50);
			}
			glPopMatrix();

			glPushMatrix();
			{   glTranslated(0,0,16);
				//glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluSphere(obj,8,50, 50);
			}glPopMatrix();




///*************Arm************************///

///111111111111111111111111111111111
glPushMatrix();
			{
			    glTranslated(25,4,0);
glScaled(.8,.5,.6);
glRotated(90,0,0,1);

      glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-100);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 10, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 4, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -4, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -4, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,-4,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-30, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

  glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,4,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-30, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,10);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-4, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(4, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(4, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-4, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,-20);

        glRotated(22,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-4, 27, 0);

			glTexCoord2f(0, 0);
			glVertex3f(4, 27, 0);

			glTexCoord2f(1, 0);
			glVertex3f(4, -27, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-4, -27, 0);
		}
		glEnd();
}
 glPopMatrix();

  glPushMatrix();
			{
     glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(10,70,-30);


        GLUquadricObj *obj = gluNewQuadric();
        gluQuadricTexture(obj, GL_TRUE);
        gluCylinder(obj,7,7,40,50,50);
        gluSphere(obj,7,50, 50);



}
 glPopMatrix();
 }
 glPopMatrix();


 ///2222222222222222222222222
 glPushMatrix();
			{
glRotated(180,0,1,0);
glTranslated(25,4,0);
glScaled(.8,.5,.6);
glRotated(90,0,0,1);

      glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-100);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 4, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 4, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -4, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -10, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,-4,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-30, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

  glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,4,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-30, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,10);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-4, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(4, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(4, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-4, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,-20);

        glRotated(22,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-4, 27, 0);

			glTexCoord2f(0, 0);
			glVertex3f(4, 27, 0);

			glTexCoord2f(1, 0);
			glVertex3f(4, -27, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-4, -27, 0);
		}
		glEnd();
}
 glPopMatrix();
   glPushMatrix();
			{
     glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(-10,70,-30);


        GLUquadricObj *obj = gluNewQuadric();
        gluQuadricTexture(obj, GL_TRUE);
        gluCylinder(obj,7,7,40,50,50);
        gluSphere(obj,7,50, 50);



}
 glPopMatrix();


 }
 glPopMatrix();







//************FAN*************//


			glPushMatrix();
			{   glTranslated(0,0,18);
				glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,1,1,15,50,50);
			}
			glPopMatrix();


 //111111111111//
  glPushMatrix();
      {    glRotated(30+fan_ang,0,0,1);
           glTranslated(0,-56,33);
           glScaled(.2,.75,.5);
      glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-100);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 1, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 1, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -1, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -1, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-50);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 1, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 1, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -1, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -1, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,-1,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

  glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,1,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,5);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-1, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(1, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(1, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-1, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,-5);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-1, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(1, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(1, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-1, -25, 0);
		}
		glEnd();
}
 glPopMatrix();
 }
 glPopMatrix();
    //222222222222222222222222////
 glPushMatrix();
      {    glRotated(120+fan_ang,0,0,1);
           glTranslated(0,-56,33);
           glScaled(.2,.75,.5);
      glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-100);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 1, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 1, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -1, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -1, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-50);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 1, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 1, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -1, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -1, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,-1,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

  glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,1,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,5);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-1, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(1, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(1, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-1, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,-5);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-1, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(1, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(1, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-1, -25, 0);
		}
		glEnd();
}
 glPopMatrix();
 }
 glPopMatrix();

 //************TAIL**********//

            glPushMatrix();
			{   glTranslated(0,75,0);
			    glRotated(90,1,0,0);
				//glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,2,2.5,45,50,50);
			}
			glPopMatrix();

            glPushMatrix();
			{   glTranslated(0,40,0);
			    glRotated(90,1,0,0);
				//glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,2.5,7,15,50,50);
			}
			glPopMatrix();


			glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,0,1,0);
        glTranslated(0,68,-2);
        glScaled(.055,.035,1);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-200, 100, 0);

			glTexCoord2f(0, 0);
			glVertex3f(100, 100, 0);

			glTexCoord2f(1, 0);
			glVertex3f(100, -100, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-100, -100, 0);
		}
		glEnd();
}
 glPopMatrix();

   glPushMatrix();
      {
    glTranslated(-19,65,0);
    glRotated(90,0,1,0);
    glScaled(.5,.5,.5);
    glColor3f(1,1,1);
//**********FAN OnTAIL*************//
 //111111111111//
  glPushMatrix();
      {    glRotated(30+fan_ang,0,0,1);
           glTranslated(0,-56,33);
           glScaled(.2,.75,.5);
      glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-100);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 1, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 1, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -1, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -1, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-50);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 1, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 1, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -1, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -1, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,-1,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

  glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,1,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,5);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-1, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(1, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(1, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-1, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,-5);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-1, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(1, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(1, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-1, -25, 0);
		}
		glEnd();
}
 glPopMatrix();
 }
 glPopMatrix();
    //222222222222222222222222////
 glPushMatrix();
      {    glRotated(120+fan_ang,0,0,1);
           glTranslated(0,-56,33);
           glScaled(.2,.75,.5);
      glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-100);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 1, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 1, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -1, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -1, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,0,-50);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 1, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 1, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -1, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -1, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,-1,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

  glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

        glRotated(90,1,0,0);
        glTranslated(0,1,-75);
        glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-10, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(10, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(10, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-10, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,5);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-1, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(1, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(1, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-1, -25, 0);
		}
		glEnd();
}
 glPopMatrix();

 glPushMatrix();
			{
       glBindTexture(GL_TEXTURE_2D, one);

       glRotated(90,0,1,0);
        glTranslated(0,75,-5);
        //glRotated(90,1,0,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 1);
			glVertex3f(-1, 25, 0);

			glTexCoord2f(0, 0);
			glVertex3f(1, 25, 0);

			glTexCoord2f(1, 0);
			glVertex3f(1, -25, 0);

			glTexCoord2f(1, 1);
			glVertex3f(-1, -25, 0);
		}
		glEnd();
}
 glPopMatrix();
 }
 glPopMatrix();
  }
 glPopMatrix();

//***********FOOT STEAR***********//
  glPushMatrix();
			{

			    glTranslated(0,-4.3,0);

            glPushMatrix();
			{   glTranslated(15,20,-15);
			    glRotated(90,1,0,0);
				glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,1,1,30,50,50);
			}
			glPopMatrix();

            glPushMatrix();
			{   glTranslated(16,16,-15);
			    glRotated(-45,0,1,0);
				glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,1,1,15,50,50);
			}
			glPopMatrix();

            glPushMatrix();
			{   glTranslated(16,-6,-15);
			    glRotated(-45,0,1,0);
				glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,1,1,15,50,50);
			}
			glPopMatrix();





            glPushMatrix();
			{   glTranslated(-15,20,-15);
			    glRotated(90,1,0,0);
				glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,1,1,30,50,50);
			}
			glPopMatrix();

            glPushMatrix();
			{   glTranslated(-16,16,-15);
			    glRotated(45,0,1,0);
				glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,1,1,15,50,50);
			}
			glPopMatrix();

            glPushMatrix();
			{   glTranslated(-16,-6,-15);
			    glRotated(45,0,1,0);
				glColor3f(.4, .5, .9);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				gluCylinder(obj,1,1,15,50,50);
			}
			glPopMatrix();
				}
			glPopMatrix();






			}
			glPopMatrix();
}

void bulet()
{
   glPushMatrix();
			{
            glBindTexture(GL_TEXTURE_2D, flame);


            glTranslated(20,-26,-10);
            glRotated(90,1,0,0);

            GLUquadricObj *obj = gluNewQuadric();
            gluQuadricTexture(obj, GL_TRUE);
            gluCylinder(obj,7,0,30,50,50);
            gluSphere(obj,7,50, 50);

          }
          glPopMatrix();
  glPushMatrix();
			{
     glBindTexture(GL_TEXTURE_2D, flame);
       glTranslated(-20,-26,-10);
       glRotated(90,1,0,0);



        GLUquadricObj *obj = gluNewQuadric();
        gluQuadricTexture(obj, GL_TRUE);
        gluCylinder(obj,7,0,30,50,50);
        gluSphere(obj,7,50, 50);



}
 glPopMatrix();

}



void ground1(){


glPushMatrix();
    {

      glTranslated(0,-0,-25-incri);
      field1();

	}glPopMatrix();


    glPushMatrix();
    {

      glTranslated(0,-300,-25-incri);
      field1();

	}glPopMatrix();
	    glPushMatrix();
    {

      glTranslated(-300,0,-25-incri);
      field1();

	}glPopMatrix();
	    glPushMatrix();
    {

      glTranslated(-300,-300,-25-incri);
      field1();

	}glPopMatrix();
	glPushMatrix();
    {

      glTranslated(0,300,-25-incri);
      field1();

	}glPopMatrix();
		glPushMatrix();
    {

      glTranslated(-300,300,-25-incri);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,0,-25-incri);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,300,-25-incri);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,-300,-25-incri);
      field1();

	}glPopMatrix();


}


void ground(){
glTranslated(-15,0,0);
glRotated(90,0,0,1);
glPushMatrix();
    {

      glTranslated(0,-0,-25-incri);
      field();

	}glPopMatrix();

    glPushMatrix();
    {

      glTranslated(0,-300,-25-incri);
      field1();

	}glPopMatrix();
	    glPushMatrix();
    {

      glTranslated(-300,0,-25-incri);
      field1();

	}glPopMatrix();
	    glPushMatrix();
    {

      glTranslated(-300,-300,-25-incri);
      field1();

	}glPopMatrix();
	glPushMatrix();
    {

      glTranslated(0,300,-25-incri);
      field1();

	}glPopMatrix();
		glPushMatrix();
    {

      glTranslated(-300,300,-25-incri);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,0,-25-incri);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,300,-25-incri);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,-300,-25-incri);
      field1();

	}glPopMatrix();


}


void play(){
 glPushMatrix();
    {
        glTranslated(xx,yy--,100);
        glRotated(20,1,0,0);

        helicopter();
    }glPopMatrix();

}



void pakcamp(){


 glPushMatrix();
			{
    glRotated(180,1,0,0);
     glBindTexture(GL_TEXTURE_2D, brek);
       GLUquadricObj *obj = gluNewQuadric();
        gluQuadricTexture(obj, GL_TRUE);
        gluCylinder(obj,60,60,50,50,50);
        gluSphere(obj,60,50, 50);


}
 glPopMatrix();


 }


 void tree_leaf(){


glPushMatrix();
{       glBindTexture(GL_TEXTURE_2D, tree_l);

       GLUquadricObj *obj = gluNewQuadric();
        gluQuadricTexture(obj, GL_TRUE);
        glTranslated(10,0,60);
        gluSphere(obj,20,50, 50);
        }
 glPopMatrix();

          glPushMatrix();
{          glBindTexture(GL_TEXTURE_2D, tree_l);

       GLUquadricObj *obj = gluNewQuadric();
        gluQuadricTexture(obj, GL_TRUE);
        glTranslated(-10,0,60);
        gluSphere(obj,20,50, 50);
        }
 glPopMatrix();

          glPushMatrix();
{
        glBindTexture(GL_TEXTURE_2D, tree_l);

       GLUquadricObj *obj = gluNewQuadric();
        gluQuadricTexture(obj, GL_TRUE);
        glTranslated(0,0,70);
        gluSphere(obj,20,50, 50);
        }
 glPopMatrix();

}
 void tree(){


  glPushMatrix();
{
    //glRotated(90,1,0,0);
       glBindTexture(GL_TEXTURE_2D, tree_w);

       GLUquadricObj *obj = gluNewQuadric();
        gluQuadricTexture(obj, GL_TRUE);
        gluCylinder(obj,15,10,50,50,50);

}
 glPopMatrix();

tree_leaf();
}


//+++++++++++DISPLY+++++++++++//
void display()
{

	glClearColor(0, 0, 0, 0);    //color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(look==1){
    gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);}
    else{
	//gluLookAt(cameraX, cameraY, cameraHeight, cameraLookingX, cameraLookingY, cameraLookingZ, 0, 0, 1);
	gluLookAt(cameraRadius * sin(cameraAngle), (-cameraRadius * cos(cameraAngle))+yy-100, 300, cameraLookingX, yy-100, cameraLookingZ, 0, 0, 1);
    }
    glMatrixMode(GL_MODELVIEW);


drawAxes();

						/****************************
						/ Add your objects from here
						****************************/


   if(mn1==1)
   {

        glPushMatrix();{

         glRotated(-14,0,1,0);
        glRotated(-90,0,0,1);
        glRotated(90,1,0,0);
    // glScaled(.1,.1,.1);

     welcome();

   }glPopMatrix();
    glPushMatrix();{
       glColor3f(1,0,1);
       //glScaled(.9,.9,.9);
        gameStartFunc();
        }glPopMatrix();

   }
   else if(mn2==1)
    {

        glPushMatrix();{
        glRotated(-14,0,1,0);
        glRotated(-90,0,0,1);
        glRotated(90,1,0,0);

     menuBG();


   }glPopMatrix();
    glPushMatrix();{
       glColor3f(0,1,.1);
        menuList();
        }glPopMatrix();

   }


 else if(initial==1){

   if(flag==1){
       cameraAngle=-100;
       cameraHeight=250;;
       flag=0;
   }
   glPushMatrix();
    {
        drawBitmapText("PRESS 'q' for start copter then press 'r' for run",14,-18,100);

    }glPopMatrix();





    glPushMatrix();
    {
        glRotated(90,0,0,1);
        helicopter();
	}glPopMatrix();



glPushMatrix();
    {

      glTranslated(0,-0,-25);

      field();

	}glPopMatrix();

    glPushMatrix();
    {

      glTranslated(0,-300,-25);
      field1();

	}glPopMatrix();
	    glPushMatrix();
    {

      glTranslated(-300,0,-25);
      field1();

	}glPopMatrix();
	    glPushMatrix();
    {

      glTranslated(-300,-300,-25);
      field1();

	}glPopMatrix();
	glPushMatrix();
    {

      glTranslated(0,300,-25);
      field1();

	}glPopMatrix();
		glPushMatrix();
    {

      glTranslated(-300,300,-25);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,0,-25);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,300,-25);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,-300,-25);
      field1();

	}glPopMatrix();

    }


else if(flg_fan_ang==1&&startFly==1)

    {
cameraHeight=incri;
   if(flag==1){
    cameraAngle=-100;
    cameraHeight=250;
   flag=0;
   }

    glPushMatrix();
    {
    glTranslated(0,0,-15);
    glRotated(45,0,0,1);
	helicopter();
	}glPopMatrix();



glPushMatrix();
    {

      glTranslated(0,-0,-25-incri);
      field();

	}glPopMatrix();

    glPushMatrix();
    {

      glTranslated(0,-300,-25-incri);
      field1();

	}glPopMatrix();
	    glPushMatrix();
    {

      glTranslated(-300,0,-25-incri);
      field1();

	}glPopMatrix();
	    glPushMatrix();
    {

      glTranslated(-300,-300,-25-incri);
      field1();

	}glPopMatrix();
	glPushMatrix();
    {

      glTranslated(0,300,-25-incri);
      field1();

	}glPopMatrix();
		glPushMatrix();
    {

      glTranslated(-300,300,-25-incri);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,0,-25-incri);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,300,-25-incri);
      field1();

	}glPopMatrix();
    glPushMatrix();
    {

      glTranslated(300,-300,-25-incri);
      field1();

	}glPopMatrix();



    }
else if(run==1)
{
if(yy>-500){
    glPushMatrix();{

       glTranslated(0,-500,-100);
        pakcamp();
    } glPopMatrix();
}
    glPushMatrix();{

       glTranslated(30,-700,-100);
        pakcamp();
    } glPopMatrix();



int o=0;
glPushMatrix();{
        play();
    }glPopMatrix();

if(b==1&& fb <130){
    glPushMatrix();{
       if(fb%3==0)
       {
           o+=2;
       }
        glTranslated(0,by-=10,bz-=o);
        bulet();
   }glPopMatrix();
        if(fb==129)
        {
          b=0;
          fb=0;
          by=0;
          bz=0;
          score++;
        }
      fb++;
      }

      glPushMatrix();
       {
         glTranslated(0,0,-100);
         ground();

        glTranslated(-600,0,0);
        ground1();
        glTranslated(-600,0,0);
        ground1();
        glTranslated(-600,0,0);
        ground1();
        glTranslated(-600,0,0);
        ground1();

    }glPopMatrix();
   glPushMatrix();
    {
	drawBitmapText("Score: ",-340,yy,62);
    itoa(score, score_value, 10);
	drawBitmapText(score_value,-298,yy,73);
    }glPopMatrix();

          glPushMatrix();
       {
         glTranslated(100,0,-100);
         tree();

    }glPopMatrix();
             glPushMatrix();
       {
         glTranslated(-90,0,-100);
         tree();

    }glPopMatrix();
             glPushMatrix();
       {
         glTranslated(70,0,-100);
         tree();

    }glPopMatrix();
             glPushMatrix();
       {
         glTranslated(-200,0,-100);
         tree();

    }glPopMatrix();
             glPushMatrix();
       {
         glTranslated(-300,100,-100);
         tree();

    }glPopMatrix();
             glPushMatrix();
       {
         glTranslated(40,-200,-100);
         tree();

    }glPopMatrix();

}
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glFlush();
	glutSwapBuffers();
}

void animate()
{



if(flg_fan_ang==1)
   {
       fan_ang+=7;

   }

  if(startFly==1&&incri<700)

      {
        incri+=1;
      }


	glutPostRedisplay();    //this will call the display AGAI


  if(cameraUp==1)
    {
       cameraHeight+=3;
    }
  if(cameraDown==1)
    {
       cameraHeight-=3;
    }
	glutPostRedisplay();    //this will call the display AGAI
  if(rxx==1&&xx<100)
    {
       xx++;
      rxx=0;
    }
 if(ryy==1&&xx>-100)
    {
       xx--;
     ryy=0;
    }

}


void init()
{

mn1=1;
mn2=0;
ncameraAngle=cameraAngle;
	cameraAngle = 0;	//angle in radian

ncameraAngleDelta=cameraAngleDelta;
    cameraAngleDelta = .001;
    ncameraRadius=cameraRadius;
    cameraRadius = 150;
    ncameraHeight=cameraHeight;
	cameraHeight = 50;


	glClearColor(0, 0, 0, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	/*
	gluPerspective() � set up a perspective projection matrix

	fovy -         Specifies the field of view angle, in degrees, in the y direction.
	aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
	zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
	*/

	gluPerspective(70, 1, 0.1, 10000.0);

}

void keyboardListener(unsigned char key, int x, int y)
{
	switch (key)
	{

	case '\015': //ENTER
	     mn1=0;
		    mn2=1;
		break;

	case '\033': //ESC
	    glutEnterGameMode();
		break;

	case 'p':
        mn2=0;
        flag+=1;
        initial=1;
        break;

	case 'r':
	    run=1;
	    flag+=1;
        initial=0;
        look=0;
        break;

	case 'q':
	    flg_fan_ang=1;
    break;


    case 'f':
	          rxx=1;
		break;
    case 'j':
            ryy=1;
		break;

        case 'a':
            b=1;
            bx=xx;
            by=yy;
		break;


	default:
		break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			cameraUp=1;
             break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			cameraDown=1;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:

			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y)
{    //x, y is the x-y of the screen (2D)
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			// 2 times?? in ONE click? -- solution is checking DOWN or UP
		}
		break;

	case GLUT_RIGHT_BUTTON:
		//........
		break;

	case GLUT_MIDDLE_BUTTON:
		//........
		break;

	default:
		break;
	}
}

int main(int argc, char **argv)
{







	glutInit(&argc, argv);                            //initialize the GLUT library

	glutInitWindowSize(1350, 700);
	glutInitWindowPosition(0, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Some Title");

	printf("Camera Controls\n\n");
	printf("Roll: UP and DOWN arrow\n");
	printf("Pitch: Q and E\n");
	printf("Yaw: LEFT and RIGHT arrow\n");
	printf("Up-Down: PAGEUP and PAGEDOWN\n");
	printf("Left-Right: L and R\n");
	printf("Zoom in-out: + and -\n");
	printf("Reset Camera: HOME\n");

	init();                        //codes for initialization

	loadAllImages();

	glEnable(GL_DEPTH_TEST);    //enable Depth Testing

								//loadAllImages();

	glutDisplayFunc(display);    //display callback function
	glutIdleFunc(animate);        //what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	glutMouseFunc(mouseListener);

	glutMainLoop();        //The main loop of OpenGL

	return 0;
}

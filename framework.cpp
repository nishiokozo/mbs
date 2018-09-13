#define APIENTRY
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

//#include <stdio.h>
#include <GL/glut.h>
//#include <math.h>
#include "framework.h"
#include "vector.h"
#include "matrix.h"
#include "math.h"
#include "font.h"
#include "key.h"
#include "mouse.h"
#include "camera.h"

//------------------------------------------------------------------------------
double	GetSecond()
//------------------------------------------------------------------------------
{
	LARGE_INTEGER frequency; 
	QueryPerformanceFrequency(&frequency);
	double f = frequency.QuadPart;
//	double f = 2741201;
//printf( "%d\n", frequency.QuadPart ) ;
	LARGE_INTEGER tm;
	QueryPerformanceCounter(&tm);

	return (double)(tm.QuadPart) / f;

}

static	float	g_x;
static	float	g_y;
static	float	g_w;
static	float	g_h;

static	int	g_flgExit;
static	int	g_valExit;

static	int	g_cntUpdate;
static	int	g_cntDraw;
static	int	g_cntKeyinput;
static	int	g_cntInit;
static	int	g_cntViewport;

static	int	(*g_viewport[100])(int,int);
static	int	(*g_update[100])();
static	int	(*g_draw[100])();
static	int	(*g_keyinput[100])(int);
static	int	(*g_init[100])(int argc, char *argv[]);

static	int	(*g_font)();
static	int	(*g_keyupdate)();
static	int	(*g_mouse)(int button, int state, int w, int h );

FRAMEWORK_INF	framework;

static	int	g_flgPlay = true;
static	int	g_flgPause = false;

//-----------------------------------------------------------------------------
static	void display(void)
//-----------------------------------------------------------------------------
{
	g_flgPlay = true;

	if ( g_keyupdate )	g_keyupdate();

	if ( key.hi.alt_l )	g_flgPause = false;

	if ( key.hi.space ) g_flgPause = true;

	if ( g_flgPause )	g_flgPlay = false;

	if ( g_flgPlay || key.rep.space )
	{
		int	i;
		for ( i = 0 ; i < g_cntUpdate ; i++ )
		{
			g_update[i]();
		}
	}

	//-----------------------------------------
	//	3D
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);	//	裏面を表示しない
	glCullFace(GL_FRONT);

	glClearColor(0.7,0.7,0.7,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

		glMatrixMode(GL_PROJECTION);
		gluPerspective(60.0, (double)g_w / (double)g_h, 1.0, 10000.0);

		glMatrixMode(GL_MODELVIEW);
		matrix	mat = minv(camera_getCamera());

		glLoadMatrixf( (float*)&mat.m );
		{
			int	i;
			for ( i = 0 ; i < g_cntDraw	 ; i++ )
			{
				g_draw[i]();
			}
		}

	glPopMatrix();

	//-----------------------------------------
	//	2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glDisable(GL_LIGHTING);

	if ( g_font ) g_font();

	//-----------------------------------------
	glutSwapBuffers();
#if 0
static	double	a0 = GetSecond();
static	double	a1 = GetSecond();
a1 = GetSecond();
printf("in %f\n", a1-a0);
a0 = GetSecond();
#endif

	if ( g_flgExit ) exit(g_valExit);
	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
static	void resize(int w, int h)
//-----------------------------------------------------------------------------
{
	framework.w = w;
	framework.h = h;

	int	i;
	for ( i = 0 ; i <g_cntViewport ;  i++ )
	{
		g_viewport[i](w,h);
	}

	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
static	void keyboard(unsigned char key, int x, int y)
//-----------------------------------------------------------------------------
{
	int	i;
	for ( i = 0 ; i <g_cntKeyinput ;  i++ )
	{
		g_keyinput[i](key);
	}
}

//-----------------------------------------------------------------------------
static void mousebutton( int button, int state, int x, int y)
//-----------------------------------------------------------------------------
{
	if ( g_mouse ) g_mouse( button, state, x, y );
}
//-----------------------------------------------------------------------------
static	void mousemotion( int x, int y)
//-----------------------------------------------------------------------------
{
	if ( g_mouse ) g_mouse( 0xffff, 0, x, y );
}


//-----------------------------------------------------------------------------
float		framework_getX()
//-----------------------------------------------------------------------------
{
	return	g_x;
}
//-----------------------------------------------------------------------------
float		framework_getY()
//-----------------------------------------------------------------------------
{
	return	g_y;
}
//-----------------------------------------------------------------------------
float		framework_getW()
//-----------------------------------------------------------------------------
{
	return	g_w;
}
//-----------------------------------------------------------------------------
float		framework_getH()
//-----------------------------------------------------------------------------
{
	return	g_h;
}
//-----------------------------------------------------------------------------
void	framework_run( int argc, char *argv[], int x, int y, int w, int h  )
//-----------------------------------------------------------------------------
{
	glutInit(&argc, argv);

	g_x = (float)x;
	g_y = (float)y;
	g_w = (float)w;
	g_h = (float)h;

	framework.w = w;
	framework.h = h;

	glutInitWindowPosition(x, y);
	glutInitWindowSize(w, h);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);

	glutMouseFunc(mousebutton);
	glutMotionFunc(mousemotion);

	{
		int	i;
		for ( i = 0 ; i < g_cntInit ; i++ )
		{
			g_init[i]( argc, argv );
		}
	}
printf("a\n");
	glutMainLoop();

}

//-----------------------------------------------------------------------------
void	framework_exit( int val )
//-----------------------------------------------------------------------------
{
	g_valExit = val;
	g_flgExit = true;

}

//-----------------------------------------------------------------------------
int		framework_entryKeyInput( int(*func)(int) )
//-----------------------------------------------------------------------------
{
	g_keyinput[ g_cntKeyinput ]  = func;
	g_cntKeyinput++;
	return	true;
}
//-----------------------------------------------------------------------------
int		framework_entryUpdate( int(*func)() )
//-----------------------------------------------------------------------------
{
	g_update[g_cntUpdate]  = func;
	g_cntUpdate++;

	return	true;
}
//-----------------------------------------------------------------------------
int		framework_entryDraw( int(*func)() )
//-----------------------------------------------------------------------------
{
	g_draw[g_cntDraw]  = func;
	g_cntDraw++;

	return	true;
}
//-----------------------------------------------------------------------------
int		framework_entryDrawFont( int(*func)() )
//-----------------------------------------------------------------------------
{
	g_font = func;

	return	true;
}
//-----------------------------------------------------------------------------
int		framework_entryKeyupdate( int(*func)() )
//-----------------------------------------------------------------------------
{
	g_keyupdate = func;

	return	true;
}
//-----------------------------------------------------------------------------
int		framework_entryInit( int(*func)(int argc, char *argv[]) )
//-----------------------------------------------------------------------------
{
	g_init[g_cntInit]  = func;
	g_cntInit++;
	return	true;
}
//-----------------------------------------------------------------------------
int		framework_entryViewport( int(*func)(int w, int h ) )
//-----------------------------------------------------------------------------
{
	g_viewport[g_cntViewport]  = func;
	g_cntViewport++;
	return	true;
}
//-----------------------------------------------------------------------------
int		framework_entryMouse( int(*func)(int button, int state, int w, int h ) )
//-----------------------------------------------------------------------------
{
	g_mouse  = func;
	return	true;
}
/*
//-----------------------------------------------------------------------------
int		framework_entryMotion( int(*func)(int w, int h ) )
//-----------------------------------------------------------------------------
{
	g_motion  = func;
	return	true;
}
*/

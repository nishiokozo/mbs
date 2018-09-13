#define APIENTRY
#include <stdio.h>
#include <GL/gl.h>
#include "vector.h"
#include "matrix.h"
#include "light.h"



//-----------------------------------------------------------------------------
int	light_draw()
//-----------------------------------------------------------------------------
{
	glEnable(GL_LIGHTING);

#if 0
	{
		static	float pos[] = { -00.0, -100.0,  00.0, 1.0 };
		static	float def[] = { 0.4, 0.4, 0.4, 1.0 };
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, def);
	}

	{
		static	float pos[] = {  00.0,  100.0, -00.0, 1.0 };
		static	float def[] = { 0.4, 0.4, 0.4, 1.0 };
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_POSITION, pos);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, def);
	}

	{
		static	float pos[] = { 100.0,    0.0, 100.0, 1.0 };
		static	float def[] = { 0.4, 0.4, 0.4, 1.0 };
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_POSITION, pos);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, def);
	}

	{
		static	float pos[] = {-100.0,    0.0,-100.0, 1.0 };
		static	float def[] = { 0.4, 0.4, 0.4, 1.0 };
		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT3, GL_POSITION, pos);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, def);
	}
#else
/*
	{
		static	float pos[] = { -00.0, -100.0,  00.0, 1.0 };
		static	float def[] = { 0.4, 0.4, 0.4, 1.0 };
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, def);
	}

	{
		static	float pos[] = {  00.0,  100.0, -00.0, 1.0 };
		static	float def[] = { 0.4, 0.4, 0.4, 1.0 };
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_POSITION, pos);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, def);
	}
*/
	{
		static	float pos[] = { -00.0, -100.0,  00.0, 1.0 };
		static	float def[] = { 0.8, 0.8, 0.8, 1.0 };
		static	float amb[]={2.0f,2.0f,2.0f,1.0f};
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, def);
		glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
	}
#endif




	return	true;
}

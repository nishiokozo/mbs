#define APIENTRY
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "vector.h"
#include "matrix.h"
#include "enemy.h"
#include "math.h"
#include "floor.h"

static	matrix	mf;

//----------------------------------------------------------
void drawFloor( matrix m, double sx, double sz, double size )
//----------------------------------------------------------
{
	glPushMatrix();

		glMultMatrixf( (float*)m.m );

		glDisable(GL_LIGHTING);

		GLfloat vertex[4][3];

		glBegin(GL_QUADS);
//		glBegin(GL_LINE_LOOP);
		{
			int	x = 0;
			int	z = 0;
			for( z = 0 ; z < sz ; z++ )
			{
				for( x = 0 ; x < sx ; x++ )
				{
/*
					if ((x+z)&0x01)
					{
						glColor3f(0.5,0.5,0.5);
					}
					else
					{
						glColor3f(0.4,0.4,0.4);
					}
*/

					double	fy = (double)0;
					double	fx = (double)x - (double)sx/2;
					double	fz = (double)z - (double)sz/2;
					vertex[0][0] = fx+( 0.0);
					vertex[0][1] = fy+( 0.0);
					vertex[0][2] = fz+( 0.0);
					vertex[1][0] = fx+( size);
					vertex[1][1] = fy+( 0.0);
					vertex[1][2] = fz+( 0.0);
					vertex[2][0] = fx+( size);
					vertex[2][1] = fy+( 0.0);
					vertex[2][2] = fz+( size);
					vertex[3][0] = fx+( 0.0);
					vertex[3][1] = fy+( 0.0);
					vertex[3][2] = fz+( size);
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);
					glVertex3fv(vertex[2]);
					glVertex3fv(vertex[3]);
				}
			}
		}
		glEnd();

		glEnable(GL_LIGHTING);

	glPopMatrix();

}
//----------------------------------------------------------
void drawRoom( matrix m, double sx, double sy, double sz, double size )
//----------------------------------------------------------
{
	GLfloat vertex[2][3];

	glPushMatrix();

		glMultMatrixf( (float*)m.m );

		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
//		glColor3f(0.55, 0.55, 0.55);
		glColor3f(0.65, 0.65, 0.65);

#if 1
		glEnable(GL_LINE_SMOOTH);
		glLineWidth(3);
		glHint( GL_LINE_SMOOTH_HINT, GL_NICEST);
#endif

		glBegin(GL_LINES);
		{
			float	i = 0;

			//°
			for ( i = 0 ; i < sx ; i+=size)
			{
					vertex[0][0] = -sx/2+i;
					vertex[0][1] = -sy/2;
					vertex[0][2] = -sz/2;
					vertex[1][0] = -sx/2+i;
					vertex[1][1] = -sy/2;
					vertex[1][2] =  sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

					vertex[0][0] = -sx/2;
					vertex[0][1] = -sy/2;
					vertex[0][2] = -sz/2+i;
					vertex[1][0] =  sx/2;
					vertex[1][1] = -sy/2;
					vertex[1][2] = -sz/2+i;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

					vertex[0][0] = -sx/2+i;
					vertex[0][1] =  sy/2;
					vertex[0][2] = -sz/2;
					vertex[1][0] = -sx/2+i;
					vertex[1][1] =  sy/2;
					vertex[1][2] =  sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

					vertex[0][0] = -sx/2;
					vertex[0][1] =  sy/2;
					vertex[0][2] = -sz/2+i;
					vertex[1][0] =  sx/2;
					vertex[1][1] =  sy/2;
					vertex[1][2] = -sz/2+i;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

			}

			for ( i = 0 ; i <= sx ; i+=size)
			{
				//	cü
					vertex[0][0] = -sx/2+i;
					vertex[0][1] = -sy/2;
					vertex[0][2] = -sz/2;
					vertex[1][0] = -sx/2+i;
					vertex[1][1] =  sy/2;
					vertex[1][2] = -sz/2;
				//	glColor3f(0.4,0.4,0.4);
					glVertex3fv(vertex[0]);
				//	glColor3f(0.3,0.6,0.7);
					glVertex3fv(vertex[1]);

					vertex[0][0] = -sx/2+i;
					vertex[0][1] = -sy/2;
					vertex[0][2] =  sz/2;
					vertex[1][0] = -sx/2+i;
					vertex[1][1] =  sy/2;
					vertex[1][2] =  sz/2;
				//	glColor3f(0.4,0.4,0.4);
					glVertex3fv(vertex[0]);
				//	glColor3f(0.3,0.6,0.7);
					glVertex3fv(vertex[1]);

			}

			for ( i = 0 ; i < sz ; i+=size)
			{
				//	cü
					vertex[0][0] = -sx/2;
					vertex[0][1] = -sy/2;
					vertex[0][2] = -sz/2+i;
					vertex[1][0] = -sx/2;
					vertex[1][1] =  sy/2;
					vertex[1][2] = -sz/2+i;
				//	glColor3f(0.4,0.4,0.4);
					glVertex3fv(vertex[0]);
				//	glColor3f(0.3,0.6,0.7);
					glVertex3fv(vertex[1]);

					vertex[0][0] =  sx/2;
					vertex[0][1] = -sy/2;
					vertex[0][2] = -sz/2+i;
					vertex[1][0] =  sx/2;
					vertex[1][1] =  sy/2;
					vertex[1][2] = -sz/2+i;
				//	glColor3f(0.4,0.4,0.4);
					glVertex3fv(vertex[0]);
				//	glColor3f(0.3,0.6,0.7);
					glVertex3fv(vertex[1]);
			}

				//	glColor3f(0.3,0.5,0.6);
			for ( i = 0 ; i < sy ; i+=size)
			{
				//	‰¡ü
					vertex[0][0] = -sx/2;
					vertex[0][1] = -sy/2+i;
					vertex[0][2] = -sz/2;
					vertex[1][0] =  sx/2;
					vertex[1][1] = -sy/2+i;
					vertex[1][2] = -sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

					vertex[0][0] = -sx/2;
					vertex[0][1] = -sy/2+i;
					vertex[0][2] =  sz/2;
					vertex[1][0] =  sx/2;
					vertex[1][1] = -sy/2+i;
					vertex[1][2] =  sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

					vertex[0][0] = -sx/2;
					vertex[0][1] = -sy/2+i;
					vertex[0][2] = -sz/2;
					vertex[1][0] = -sx/2;
					vertex[1][1] = -sy/2+i;
					vertex[1][2] =  sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

					vertex[0][0] =  sx/2;
					vertex[0][1] = -sy/2+i;
					vertex[0][2] = -sz/2;
					vertex[1][0] =  sx/2;
					vertex[1][1] = -sy/2+i;
					vertex[1][2] =  sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

			}


				//---

					vertex[0][0] = -sx/2;
					vertex[0][1] =  sy/2;
					vertex[0][2] = -sz/2;
					vertex[1][0] =  sx/2;
					vertex[1][1] =  sy/2;
					vertex[1][2] = -sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

					vertex[0][0] = -sx/2;
					vertex[0][1] =  sy/2;
					vertex[0][2] =  sz/2;
					vertex[1][0] =  sx/2;
					vertex[1][1] =  sy/2;
					vertex[1][2] =  sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);


					vertex[0][0] = -sx/2;
					vertex[0][1] =  sy/2;
					vertex[0][2] = -sz/2;
					vertex[1][0] = -sx/2;
					vertex[1][1] =  sy/2;
					vertex[1][2] =  sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);

					vertex[0][0] =  sx/2;
					vertex[0][1] =  sy/2;
					vertex[0][2] = -sz/2;
					vertex[1][0] =  sx/2;
					vertex[1][1] =  sy/2;
					vertex[1][2] =  sz/2;
					glVertex3fv(vertex[0]);
					glVertex3fv(vertex[1]);
			}

		glEnd();

		glEnable(GL_LIGHTING);

	glPopMatrix();

}
//-----------------------------------------------------------------------------
int	floor_draw()
//-----------------------------------------------------------------------------
{
#if 0
	drawFloor( mf, 50, 50, 0.5f );
#else
	drawRoom( mf, 300, 300, 300, 30.0f );
#endif

	return	true;
}

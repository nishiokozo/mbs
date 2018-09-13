#define APIENTRY
#include <stdio.h>
#include <GL/gl.h>
#include "l.h"

#include "camera.h"
#include "fighter.h"
#include "missile.h"
#include "enemy.h"
#include "bomb.h"

#define	MISSILE_MAX	1000

typedef struct
{
	int		flgActive;
	int		type;
	vector	vspeed;
	matrix	mat;
} MISSILE_INF;

static	MISSILE_INF	missile_inf[MISSILE_MAX];

static	int	missile_wr;
static	int	missile_rd;

static	float vertex[][3] = 
{
#if 0

	{ -0.045,  0.045, 2.0 },
	{  0.045,  0.045, 2.0 },
	{  0.045, -0.045, 2.0 },
	{ -0.045, -0.045, 2.0 },

	{ -0.045,  0.045, -1.5 },
	{  0.045,  0.045, -1.5 },
	{  0.045, -0.045, -1.5 },
	{ -0.045, -0.045, -1.5 }
#else
	{ -0.125,  0.125, 2.0 },
	{  0.125,  0.125, 2.0 },
	{  0.125, -0.125, 2.0 },
	{ -0.125, -0.125, 2.0 },

	{ -0.125,  0.125, -0.2 },
	{  0.125,  0.125, -0.2 },
	{  0.125, -0.125, -0.2 },
	{ -0.125, -0.125, -0.2 }
#endif
};

static	int face[][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};
/*
static	int edge[][2] = {
	{ 0, 6 },
	{ 0, 4 },
	{ 0, 7 },
	{ 4, 6 },
	{ 6, 7 },
	{ 7, 4 }
};
*/
static	float normal[][3] = {
	{ 0.0, 0.0,-1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{-1.0, 0.0, 0.0 },
	{ 0.0,-1.0, 0.0 },
	{ 0.0, 1.0, 0.0 }
};

static int g_body1;
static int g_body2;

//-----------------------------------------------------------------------------
static	void drawBody( matrix m, float size, int num )
//-----------------------------------------------------------------------------
{

	glPushMatrix();

		glMultMatrixf( (float*)m.m );

		glCallList(num);

	glPopMatrix();
}

//-----------------------------------------------------------------------------
int	missile_init( int argc, char *argv[] )
//-----------------------------------------------------------------------------
{
	//	ÉÇÉfÉãçÏê¨
#if 1
	g_body1 = glGenLists(1);
	glNewList(g_body1, GL_COMPILE);
	{
	#if 1
		static	float g_def[] = { 0.2, 0.2, 0.2, 1.0 };
		static	float g_amb[] = { 0.3, 0.4, 0.5, 1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, g_def);
		glMaterialfv(GL_FRONT, GL_AMBIENT, g_amb);
		glEnable(GL_LIGHTING);
	#else
		glDisable(GL_LIGHTING);
glColor4f(0.7, 0.8, 0.9, 1.0);
glColor4f(0.8, 0.9, 0.9, 1.0);
	#endif
		glBegin(GL_QUADS);
		{
			int i;
			int j;
			float	size = 1.0f;
			for (j = 0; j < 6; ++j) 
			{
				glNormal3fv(normal[j]);
				for (i = 0; i < 4; ++i) 
				{
					float	v[3];
					v[0] = vertex[face[j][i]][0] * size;
					v[1] = vertex[face[j][i]][1] * size;
					v[2] = vertex[face[j][i]][2] * size;
					glVertex3fv( v );
				}
			}
		}
		glEnd();
	}
	glEndList();
#endif
#if 1
	g_body2 = glGenLists(1);
	glNewList(g_body2, GL_COMPILE);
	{
		static	float g_def[] = { 0.4, 0.4, 0.4, 1.0 };
		static	float g_amb[] = { 0.4, 0.4, 0.4, 1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, g_def);
		glMaterialfv(GL_FRONT, GL_AMBIENT, g_amb);
		glEnable(GL_LIGHTING);
		glBegin(GL_QUADS);
		{
			int i;
			int j;
			float	size = 3.0f;
			for (j = 0; j < 6; ++j) 
			{
				glNormal3fv(normal[j]);
				for (i = 0; i < 4; ++i) 
				{
					float	v[3];
					v[0] = vertex[face[j][i]][0] * size;
					v[1] = vertex[face[j][i]][1] * size;
					v[2] = vertex[face[j][i]][2] * size;
					glVertex3fv( v );
				}
			}
		}
		glEnd();
	}
	glEndList();
#endif

	int	i;
	for ( i = 0 ; i < MISSILE_MAX ; i++ )
	{
		//	èâä˙à íu
		missile_inf[i].mat = mtrans( 0,10,0 );

	}	
	missile_wr = 0;
	missile_rd = 0;

	return	true;
}
//-----------------------------------------------------------------------------
void	missile_request( matrix m1, int type, float speed )
//-----------------------------------------------------------------------------
{

	missile_inf[missile_wr].mat = m1;
	missile_inf[missile_wr].flgActive = true;
	missile_inf[missile_wr].type = type;
	missile_inf[missile_wr].vspeed = vector(0,0,speed);
	missile_wr++;
	if ( missile_wr >= MISSILE_MAX-1 )	missile_wr = 0;

}
//-----------------------------------------------------------------------------
int	missile_update()
//-----------------------------------------------------------------------------
{
	int	i;
	for ( i = 0 ; i < MISSILE_MAX ; i++ )
	{
		MISSILE_INF*	pMissile = &missile_inf[i];

		if ( pMissile->flgActive )
		{
			vector p = pMissile->mat.vpos() +  pMissile->mat.mrot() * pMissile->vspeed; ;

			pMissile->mat.m[3][0] = p.x;
			pMissile->mat.m[3][1] = p.y;
			pMissile->mat.m[3][2] = p.z;

			if ( 
				p.x < -150 || p.x > 150 
			||	p.y < -150 || p.y > 150 
			||	p.z < -150 || p.z > 150 
			)
			{
				pMissile->flgActive = false;
			}

			//	è’ìÀîªíË
if(1)
			if ( pMissile->type == MISSLE_TYPE_FIGHTER )
			{
				vector	p1 = pMissile->mat.vpos();
				ENEMY_INF*	pEnemy = enemy_getPtr();
				int	j;
				for ( j = 0 ; j < enemy_getCnt() && j < 10000; j++ )
				{
					ENEMY_INF*	pe = &pEnemy[j];

					if ( pe->stat == ENEMY_STAT_ACTIVE )
					{
						vector	p2 = pe->mat.vpos();

						vector v = (p1-p2);
						if ( v.flen() < 2.0f )
						{
							pe->stat = ENEMY_STAT_DOWN;
							pMissile->flgActive = false;
							bomb_request( pe->mat, 1.0f );
						}

					}		
				}
			}

		}

	}
	return	true;
}

//-----------------------------------------------------------------------------
int	missile_draw()
//-----------------------------------------------------------------------------
{


	{
		int	i;
		for ( i = 0 ; i < MISSILE_MAX ; i++ )
		{
			MISSILE_INF* pMissile = &missile_inf[i];
			
			if ( pMissile->flgActive )
			{
				if ( pMissile->type == MISSLE_TYPE_FIGHTER )
				{
					drawBody( missile_inf[i].mat, 1.0f, g_body2 );
				}
				else
				{
					drawBody( missile_inf[i].mat, 1.0f, g_body1 );
				}
		
			}
		}
	}

	return	true;
}

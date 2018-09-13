#define APIENTRY
#include <stdio.h>
#include <GL/gl.h>
#include "l.h"

#include "camera.h"
#include "fighter.h"
#include "bomb.h"
#include "enemy.h"

#define	BOMB_MAX	1000

enum
{
	BOMB_STAT_NONE,
	BOMB_STAT_ACTIVE,
	BOMB_STAT_DOWN,
};
typedef struct
{
	int		stat;
	float	size;
	int		lim;
	matrix	mat;
} BOMB_INF;

static	BOMB_INF	bomb_inf[BOMB_MAX];

static	int	bomb_wr;
static	int	bomb_rd;

static	float vertex[][3] = 
{
	{ -0.5, -0.5, -0.5 },
	{  0.5, -0.5, -0.5 },
	{  0.5,  0.5, -0.5 },
	{ -0.5,  0.5, -0.5 },
	{ -0.5, -0.5,  0.5 },
	{  0.5, -0.5,  0.5 },
	{  0.5,  0.5,  0.5 },
	{ -0.5,  0.5,  0.5 }
};

static	int face[][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};
static	float normal[][3] = {
	{ 0.0, 0.0,-1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{-1.0, 0.0, 0.0 },
	{ 0.0,-1.0, 0.0 },
	{ 0.0, 1.0, 0.0 }
};

static int g_body;

//-----------------------------------------------------------------------------
static	void drawBody( matrix m, float size, int num, float alpha )
//-----------------------------------------------------------------------------
{

	glPushMatrix();

		glMultMatrixf( (float*)m.m );

//		glColor4f(1.0,1.0,1.0, alpha);
//		glColor4f(0.0,0.0,0.0, alpha);
		glColor4f(0.8,0.5,0.0, alpha);
		glCallList(num);

	glPopMatrix();
}

//-----------------------------------------------------------------------------
int	bomb_init( int argc, char *argv[] )
//-----------------------------------------------------------------------------
{
	//	ÉÇÉfÉãçÏê¨
#if 1
	g_body = glGenLists(1);
	glNewList(g_body, GL_COMPILE);
	{
		glDisable(GL_LIGHTING);
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

	int	i;
	for ( i = 0 ; i < BOMB_MAX ; i++ )
	{
		//	èâä˙à íu
		bomb_inf[i].mat = mtrans( 0,10,0 );

	}	
	bomb_wr = 0;
	bomb_rd = 0;

	return	true;
}
//-----------------------------------------------------------------------------
void	bomb_request( matrix m1, float size )
//-----------------------------------------------------------------------------
{

	bomb_inf[bomb_wr].mat = m1;
	bomb_inf[bomb_wr].stat = BOMB_STAT_ACTIVE;
	bomb_inf[bomb_wr].size = size;
	bomb_inf[bomb_wr].lim = 100;
	bomb_wr++;
	if ( bomb_wr >= BOMB_MAX-1 )	bomb_wr = 0;

}
//-----------------------------------------------------------------------------
int	bomb_update()
//-----------------------------------------------------------------------------
{
	int	i;
	for ( i = 0 ; i < BOMB_MAX ; i++ )
	{
		BOMB_INF*	pBomb = &bomb_inf[i];

		if ( pBomb->stat == BOMB_STAT_ACTIVE )
		{
			pBomb->mat = mscale(1.010f) * pBomb->mat; 

			if ( pBomb->lim > 0 )
			{
				pBomb->lim--;
				if ( pBomb->lim == 0 )
				{
					pBomb->stat = BOMB_STAT_NONE;
				}
			}
		}
	}
	return	true;
}

//-----------------------------------------------------------------------------
int	bomb_draw()
//-----------------------------------------------------------------------------
{

	{
		int	i;
		for ( i = 0 ; i < BOMB_MAX ; i++ )
		{
			BOMB_INF* pBomb = &bomb_inf[i];
			
			if ( pBomb->stat == BOMB_STAT_ACTIVE )
			{
				float	a = (float)pBomb->lim/100.0f;
				drawBody( bomb_inf[i].mat, 1.0f, g_body, a );
		
			}
		}
	}

	return	true;
}

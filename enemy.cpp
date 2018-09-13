#define APIENTRY
#include <stdio.h>
#include <GL/gl.h>
#include "l.h"
/*
#include "vector.h"
#include "matrix.h"
#include "math.h"
#include "font.h"
*/
#include "enemy.h"
#include "fighter.h"
#include "core.h"
#include "missile.h"


static	int	g_prev_lvl = 0;
static	int	g_lvl = 6;
static	int	g_x[10] = {1,2,4,6,8,10,14,18,20,50};
static	int	g_y[10] = {1,2,4,6,8,10,14,18,20,50};
static	int	g_z[10] = {1,2,4,6,8,10,14,18,20,40};

#define	ENEMY_CNT	100000
static	ENEMY_INF	enemy_inf[ENEMY_CNT];

static	float vertex[][3] = {
  #if 0
	{ -0.5, -0.5, -0.5 },
	{  0.0, -0.5, -0.5 },
	{  0.0, -0.5, -0.5 },
	{ -0.5, -0.5, -0.5 },

	{ -0.5, -0.5,  0.5 },
	{  0.0, -0.5,  0.5 },
	{  0.0,  0.5,  0.5 },
	{ -0.5,  0.5,  0.5 }
  #endif
  #if 0
	{ -0.00, -0.3, 1.5 },
	{  0.00, -0.3, 1.5 },
	{  0.00, -0.3, 1.5 },
	{ -0.00, -0.3, 1.5 },

	{ -0.00,  0.3, -0.5 },
	{  0.00,  0.3, -0.5 },
	{  0.7, -0.3, -0.5 },
	{ -0.7, -0.3, -0.5 }
  #endif
  #if 1
	{ -0.0, -0.0, 1.5 },	//	0
	{  0.0, -0.0, 1.5 },	//	1
	{  0.0, -0.0, 1.5 },	//	2
	{ -0.0, -0.0, 1.5 },	//	3	

	{ -0.0,  0.6, -0.5 },	//	4
	{  0.0,  0.6, -0.5 },	//	5
	{  0.7, -0.0, -0.5 },	//	6
	{ -0.7, -0.0, -0.5 }	//	7
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

static	int edge[][2] = {
	{ 0, 6 },
	{ 0, 4 },
	{ 0, 7 },
	{ 4, 6 },
	{ 6, 7 },
	{ 7, 4 }
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

//static	float g_black[] = { 0.0, 0.0, 0.0, 1.0 };
//static	float g_def[] = { 0.2, 0.2, 0.2, 1.0 };
static	float g_def[] = { 0.2, 0.2, 0.2, 1.0 };
static	float g_amb[] = { 0.2, 0.2, 0.2, 1.0 };
//static	float g_col2[] = { 1.0, 0.1, 0.1, 1.0 };
//static	float g_def[] = { 0.4, 0.4, 0.4, 1.0 };
//static	float g_def[] = { 0.6, 0.6, 0.6, 1.0 };
//static	float g_def[] = { 0.7, 0.7, 0.7, 1.0 };
//static	float g_def[] = { 0.8, 0.8, 0.8, 1.0 };

//-----------------------------------------------------------------------------
ENEMY_INF*	enemy_getPtr()
//-----------------------------------------------------------------------------
{
	return	&enemy_inf[0];
}
//-----------------------------------------------------------------------------
int	enemy_getCnt()
//-----------------------------------------------------------------------------
{
	return	g_x[g_lvl]*g_y[g_lvl]*g_z[g_lvl];
//	return	ENEMY_CNT;
}

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
int	enemy_init( int argc, char *argv[] )
//-----------------------------------------------------------------------------
{
	//	ÉÇÉfÉãçÏê¨
	g_body = glGenLists(1);
	glNewList(g_body, GL_COMPILE);
#if 0
		glDisable(GL_LIGHTING);
//		glEnable(GL_DEPTH_TEST);
//		glDepthFunc(GL_ALWAYS);
		glColor3f(0.0,0.0,0.0);
		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1);
		glBegin(GL_LINES);
		{
			int	j;
			for ( j = 0; j < 6 ; j++ )
			{
				int	i;
				for ( i = 0; i < 2 ; i++ )
				{
					float	v[3];
					v[0] = vertex[edge[j][i]][0]*1.0; 
					v[1] = vertex[edge[j][i]][1]*1.0; 
					v[2] = vertex[edge[j][i]][2]*1.0; 
					glVertex3fv( v );
				}
			}
		}
		glEnd();
#endif
#if 1

		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, g_def);
		glMaterialfv(GL_FRONT, GL_AMBIENT, g_amb);
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
#endif
#if 1
		glDisable(GL_LIGHTING);
//		glEnable(GL_DEPTH_TEST);
//		glDepthFunc(GL_ALWAYS);
		glColor3f(0.3,0.3,0.3);
		glDisable(GL_LINE_SMOOTH);
		glLineWidth(1);
		glBegin(GL_LINES);
		{
			int	j;
			for ( j = 0; j < 6 ; j++ )
			{
				int	i;
				for ( i = 0; i < 2 ; i++ )
				{
					float	v[3];
					v[0] = vertex[edge[j][i]][0]*1.0; 
					v[1] = vertex[edge[j][i]][1]*1.0; 
					v[2] = vertex[edge[j][i]][2]*1.0; 
					glVertex3fv( v );
				}
			}
		}
		glEnd();
#endif

	glEndList();


	//	èâä˙à íu
	{
		int	n = 0;
		int	i;
		for ( i = 0 ; i < 100 ; i++ )
		{
			int	j;
			for ( j = 0 ; j < 100 ; j++ )
			{
				int	k;
				for ( k = 0 ; k < 10 ; k++ )
				{
				  #if 0
					enemy_inf[n].mat = mtrans( 
						(i-50/2)*1.3f, 
						(k     )*1.3f+1, 
						(j-50/2)*1.3f
					);
				  #else
					enemy_inf[n].mat = mtrans( 
						((float)rand())/32768.0f*300-150,
						((float)rand())/32768.0f*300-150,
						((float)rand())/32768.0f*300-150
					);
				  #endif
		
					n++;
				}
			}
		}
	}
	g_prev_lvl	= -1;

	return	true;
}
//-----------------------------------------------------------------------------
static	void updateBody( ENEMY_INF* pInf, vector v1, vector pt, vector vs, vector pa, int stat )
//-----------------------------------------------------------------------------
{
//	vector vx = pInf->mat.vx();
//	vector vy = pInf->mat.vy();
	vector vz = pInf->mat.vz();
	vector vc = vnormal(vcross(  vz, v1 ));

	float	f = fdot( vz, v1 );
	float	rc = acos(f) / 70.0f;

	if ( key.hi.v ) 
	{
		missile_request( pInf->mat, MISSLE_TYPE_ENEMY, 1.0f );
	}


//vs.z = vs.z * f*2 ;
//if( vs.z < 0.1f) vs.z = 0.1f;

//if ( rc < rad(1) ) rc = rad(1);

	matrix	mr = mrotv( vc, rc );

	vector p = pInf->mat.vpos() +  pInf->mat.mrot() * vs ;

	//	çUåÇ
	if ( stat == ENEMY_STAT_ACTIVE )
	{
		vector	p0 = pInf->mat.vpos();

		vector	vt = vnormal(pa-p0);

		float	rz = acos(fdot( vz, vt ));

		if ( pInf->limAttack == 0 )
		{
			if ( rz < rad(30) )
			{
				missile_request( pInf->mat, MISSLE_TYPE_ENEMY, 1.0f );
			}
			pInf->limAttack = 200;
		}

		if ( pInf->limAttack > 0 )
		{
			pInf->limAttack--;
		}
	}

#if 0
//	épê®êßå‰
	vector	p0 = pInf->mat.vpos();

	vector	vt = vnormal(pt-p0);

	float	rz = acos(fdot( vy, vt ));


	
	if ( rz > rad(10) )
	{

	  #if 0
		line_request( p0, pt, vector(1,1,0));
		line_request( p0, p0+vy, vector(1,0,0));
	  #endif

		if ( fdot( vx, vt ) > 0.0f ) rz = -rz;

		pInf->mat = mrotz(rz/20) * pInf->mat * mr ;
	}
	else
	{
		pInf->mat = pInf->mat * mr ;
	}
#else
		pInf->mat = pInf->mat * mr ;

#endif

	pInf->mat.m[3][0] = p.x;
	pInf->mat.m[3][1] = p.y;
	pInf->mat.m[3][2] = p.z;

}
//-----------------------------------------------------------------------------
int	enemy_update()
//-----------------------------------------------------------------------------
{
	if ( key.hi._1 ) g_lvl = 0;
	if ( key.hi._2 ) g_lvl = 1;
	if ( key.hi._3 ) g_lvl = 2;
	if ( key.hi._4 ) g_lvl = 3;
	if ( key.hi._5 ) g_lvl = 4;
	if ( key.hi._6 ) g_lvl = 5;
	if ( key.hi._7 ) g_lvl = 6;
	if ( key.hi._8 ) g_lvl = 7;
	if ( key.hi._9 ) g_lvl = 8;
	if ( key.hi._0 ) g_lvl = 9;

	if ( g_lvl != g_prev_lvl )
	{
		int	cnt = g_x[g_lvl]*g_y[g_lvl]*g_z[g_lvl];
		int	i;
		for ( i = 0 ; i < ENEMY_CNT ; i++ )
		{
			if ( i < cnt )
			{
				enemy_inf[i].stat = ENEMY_STAT_ACTIVE;
			}
			else
			{
				enemy_inf[i].stat = ENEMY_STAT_NONE;
			}
		}

		g_prev_lvl = g_lvl;
	}


	static	int	flgPause = true;
	static	int	flgAsu = false;
//	static	int	flgRot = true;

//	if ( key.hi.r ) flgRot = !flgRot;
	if ( key.hi.p ) flgPause = !flgPause;
	if ( key.hi.y ) flgAsu = !flgAsu;

//	font_printf( "r=%d\n", flgRot );
//	font_printf( "p=%d\n", flgPause );
	font_printf( "y=%d\n", flgAsu );

//	int	flg = false;


	if ( flgPause ) 
	{
		vector pt = core_getMatrix().vpos();
		vector at = fighter_getMatrix().vpos();

		int	cnt = g_x[g_lvl]*g_y[g_lvl]*g_z[g_lvl];
		int	i;
		for ( i = 0 ; i < cnt ; i++ )
		{
			vector p0 = enemy_inf[i].mat.vpos();

			vector vm = vnormal( pt - p0 );

			{
				vector va = vector(0,0,0);

				//---------------------------------
				if( flgAsu)
				{
					int	j;
					for ( j = i+1 ; j < cnt ; j++ )
					{
							
						vector v = enemy_inf[j].mat.vpos() - p0;	

						float	len = v.flen();

						#define	DIST	2.0f

						if ( len < DIST )
						{
							va -= v * (1.0f-len/DIST)/2;	
						}
						
					}
				}
				vm += va;

				vm = vnormal( vm );
			}
			
			//---------------------------------

			{
				vector vs = vector( 0, 0, 0.4f );

				updateBody( &enemy_inf[i], vm, pt, vs, at, enemy_inf[i].stat );

			}

		}
	}

	return	true;
}

//-----------------------------------------------------------------------------
int	enemy_draw()
//-----------------------------------------------------------------------------
{
	int	cnt = g_x[g_lvl]*g_y[g_lvl]*g_z[g_lvl];

	font_printf("e=%d", cnt );

	int	i;
	for ( i = 0 ; i < cnt ; i++ )
	{
		{

			enemy_inf[i].mat	= mnormal( enemy_inf[i].mat );

			if ( enemy_inf[i].stat == ENEMY_STAT_NONE )
			{
			}
			else
			if ( enemy_inf[i].stat == ENEMY_STAT_DOWN )
			{
			}
			else
			{
				drawBody( enemy_inf[i].mat, 1.0f, g_body );
			}

		}
	}

	//	èâä˙à íu
	if ( key.hi.r )
	{
		int	n = 0;
		int	i;
		for ( i = 0 ; i < 100 ; i++ )
		{
			int	j;
			for ( j = 0 ; j < 100 ; j++ )
			{
				int	k;
				for ( k = 0 ; k < 10 ; k++ )
				{
				  #if 0
					enemy_inf[n].mat = mtrans( 
						(i-50/2)*1.3f, 
						(k     )*1.3f+1, 
						(j-50/2)*1.3f
					);
				  #else
					enemy_inf[n].mat = mtrans( 
						((float)rand())/32768.0f*300-150,
						((float)rand())/32768.0f*300-150,
						((float)rand())/32768.0f*300-150
					);
				  #endif
		
					n++;
				}
			}
		}
	}
	return	true;
}

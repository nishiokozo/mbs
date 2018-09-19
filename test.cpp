#define APIENTRY
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/gl.h>
#include "framework.h"
#include "vector.h"
#include "matrix.h"
#include "font.h"
#include "key.h"
#include "mouse.h"
#include "line.h"


/* 表示図形のディスプレイリスト番号 */
static GLuint cube;

/* 物体の色 */
static GLfloat red[] = { 0.8, 0.8, 0.8, 1.0 };

/* ドラッグ開始位置 */
//static float cx, cy;

/* マウスの絶対位置→ウィンドウ内での相対位置の換算係数 */
//static float sx, sy;

/* 回転の初期値 (クォータニオン) */
static quat qa;
static quat	qt1;
static quat	qt2;

matrix mt1;
matrix mt2;

static loc	la;
static loc	l1;
static loc	l2;
static vector	va = vector(cosf(rad(90)),sin(rad(90)),0);
static vector	vb = vector(cosf(rad( 45)),	0,		    sinf(rad(45)));
static vector	vc;
static vector	v1;
static vector	v2;


matrix	mf;
#define RADIAN( n ) ( ( n ) * ( 3.1415926535897932384626 / 180.0 ) )

//-----------------------------------------------------------------------------
int test_update()
//-----------------------------------------------------------------------------
{
#if 0
	{
		static	float	rz;

		if ( key.q ) rz += 1*M_PI/180.0f;
		if ( key.e ) rz -= 1*M_PI/180.0f;
		if ( rz > M_PI*2 ) rz -= M_PI*2; 
		if ( rz < 0 ) rz += M_PI*2; 

		static	float	rx;

		if ( key.r ) rx += 1*M_PI/180.0f;
		if ( key.f ) rx -= 1*M_PI/180.0f;
		if ( rx > M_PI*2 ) rx -= M_PI*2; 
		if ( rx < 0 ) rx += M_PI*2; 

		vector	v;
		v.x = cosf( rz );
		v.y = sinf( rz );

		va.x =  v.x;
		va.y =             v.y*cos( rx ) + v.z*sin( rx );
		va.z =            -v.y*sin( rx ) + v.z*cos( rx );

	}
#endif
#if 1
	{
		matrix	m;
		if ( key.on.q ) m = mrotz(rad( 2));
		if ( key.on.e ) m = mrotz(rad(-2));

		static	float	rx;

		if ( key.on.r ) rx += 1*M_PI/180.0f;
		if ( key.on.v ) rx -= 1*M_PI/180.0f;
		if ( rx > M_PI*2 ) rx -= M_PI*2; 
		if ( rx < 0 ) rx += M_PI*2; 

	}

	vc = vnormal(vcross(  va, vb ));



//font_printf( "va=%4.2f %4.2f %4.2f\n", (va.x), (va.y), (va.z) );
//font_printf( "vb=%4.2f %4.2f %4.2f\n", (vb.x), (vb.y), (vb.z) );
//font_printf( "deg=%4.2f\n", deg(acos(fdot(va,vb))));


	{
		static	int	flg = false;
		static	int	cnt = 0;

		if ( key.on.r )
		{
			flg  = false;
			cnt= 0;
		}
		if ( key.hi.space )
		{
			flg  = true;
			v1 = va;
			cnt= 0;
			mf = mrotv( vnormal(vcross(  va, vb )), rad(1) );

		}
		if ( flg )
		{
			cnt++;
			//if ( cnt >  180 ) 
			if ( cnt > deg(acos(fdot(va,vb))) )
			{
				flg = false ;
			}
		}

		{


//			font_printf("tflg=%d %d\n", flg, cnt );
		}

		v1 = v1 * mf;

		mt1 = mt1 * mf;
	}

#endif

#if 0
	if ( mouse.hi.l )
	{
		qa.x = qt1.x;
		qa.y = qt1.y;
		qa.z = qt1.z;
		qa.w = qt1.w;
	}

	if ( mouse.on.l )
	{
		
		float dx, dy, s;

		dx = mouse.dx;
		dy = mouse.dy;

		/* マウスポインタの位置のドラッグ開始位置からの距離 */
		s = sqrtf(dx * dx + dy * dy);
		dx /= s;
		dy /= s;

		if (s != 0.0) 
		{
			float	o = s*2;
			quat	qd( cosf(o), dy * sinf(o), dx * sinf(o), 0.0 );

			qt1 =  qd * qa;

		}
	}

			font_printf("mouse.l=%d \n", mouse.on.l );

	{
		static quat	qs;
		static quat	qe;
		static	int	flg = false;
		static	int	cnt = 0;
		if ( key.space )
		{
			if ( flg == false )
			{
				qs = qt2;
				qe = qt1;
				flg  = true;
				cnt= 0;
			}
		}
		if ( flg )
		{
			cnt++;
			if ( cnt >  60 ) 
			{
				flg = false ;
			}
		}
/*
		if ( flg )
		{
			font_printf("tflg=%d %d\n", flg, cnt );
			qt2 = qslerp( qs, qe, 1.0/60*cnt );
		}
*/
	}
#endif


	return	true;
}

//-----------------------------------------------------------------------------
int test_draw(void)
//-----------------------------------------------------------------------------
{
	glPushMatrix();

#if 0
		glPushMatrix();
			/* 回転 */

			/* クォータニオンから回転の変換行列を求める */
			mt1 = mq(qt1);

			glMultMatrixf((float*)&mt1.m[0][0]);

			/* 描画 */
			glCallList(cube);

		glPopMatrix();

		glPushMatrix();

			/* クォータニオンから回転の変換行列を求める */
			mt2 = mq(qt2);

			/* 回転 */
			glMultMatrixf((float*)&mt2.m[0][0]);

			/* 描画 */
			glCallList(cube);

		glPopMatrix();
#endif
#if 0

		static	float	rz;

		if ( key.q ) rz += rad(1);
		if ( key.e ) rz -= rad(1);
		if ( rz > M_PI*2 ) rz -= pi*2; 
		if ( rz < 0 ) rz += pi*2; 

		va.x = cosf( rz );
		va.y = sinf( rz );

		vector v0;
		line_request( v0, v0+va, vector( 0,0,1));

#endif

#if 1
		glPushMatrix();

			glMultMatrixf((float*)&mt1.m[0][0]);

			/* 描画 */
			glCallList(cube);

		glPopMatrix();

		{
			vector v0;
			line_request( v0, v0+mt1.vx(), vector( 1,0,0));
			line_request( v0, v0+mt1.vy(), vector( 0,1,0));
			line_request( v0, v0+mt1.vz(), vector( 0,0,1));
		}
#endif

#if 1

		vector v0;
		line_request( v0, v0+v1, vector( 1,1,1));
		line_request( v0, v0+va, vector( 0,1,1));
		line_request( v0, v0+vb, vector( 1,1,0));
		line_request( v0, v0+vc, vector( 1,0,1));

//		line_request( v0, v0+mf.vy(), vector( 1,0,0));
//		line_request( v0, v0+mf.vx(), vector( 0,1,0));
//		line_request( v0, v0+mf.vz(), vector( 0,0,1));



#endif
/*	
		{
			vector	v1 = mt2.vy();
			vector	v0 = mt2.vp();

			vector	v2 = vnormal(vcross(  mt1.vy(), mt2.vy() ));

			line_request( v0, v1+v0, vector( 1,1,0));
			line_request( v0, v2+v0, vector( 1,1,0));
		}
*/

	glPopMatrix();

	return	true;
}

static	float vertex[][3] = {
	{ -0.06, -0.1, -0.1 },
	{  0.06, -0.1, -0.1 },
	{  0.06,  1.2, -0.1 },
	{ -0.06,  1.2, -0.1 },
	{ -0.06, -0.1,  0.1 },
	{  0.06, -0.1,  0.1 },
	{  0.06,  1.2,  0.1 },
	{ -0.06,  1.2,  0.1 },

	{ -0.0,  1.2, -0.3 },
	{  0.0,  1.2, -0.3 },
	{  0.0,  1.3, -0.3 },
	{ -0.0,  1.3, -0.3 },
	{ -0.2,  1.2,  0.2 },
	{  0.2,  1.2,  0.2 },
	{  0.2,  1.3,  0.2 },
	{ -0.2,  1.3,  0.2 },
};

static	int face[][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 },

	{ 8+0, 8+1, 8+2, 8+3 },
	{ 8+1, 8+5, 8+6, 8+2 },
	{ 8+5, 8+4, 8+7, 8+6 },
	{ 8+4, 8+0, 8+3, 8+7 },
	{ 8+4, 8+5, 8+1, 8+0 },
	{ 8+3, 8+2, 8+6, 8+7 },

};

static	float normal[][3] = {
	{ 0.0, 0.0,-1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{-1.0, 0.0, 0.0 },
	{ 0.0,-1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },

	{ 0.0, 0.0,-1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{-1.0, 0.0, 0.0 },
	{ 0.0,-1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },

};

//-----------------------------------------------------------------------------
int test_init( int argc, char *argv[] )
//-----------------------------------------------------------------------------
{

	/* 表示図形をディスプレイリストに登録 */
	cube = glGenLists(1);

	/* 立方体 */
	glNewList(cube, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	{
		float	size = 1.0f;

		glBegin(GL_QUADS);
		int j;
		for (j = 0; j < 6*2; ++j) {
			glNormal3fv(normal[j]);
			int i;
			for (i = 0; i < 4; ++i) {
				float	v[3];
				v[0] = vertex[face[j][i]][0] * size;
				v[1] = vertex[face[j][i]][1] * size;
				v[2] = vertex[face[j][i]][2] * size;
				glVertex3fv( v );
			}
		}
		glEnd();
	}
	glEndList();

	return true;
}

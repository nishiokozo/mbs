#define APIENTRY
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include "l.h"
#include "camera.h"
#include "ctrl.h"
#include "core.h"
#include "missile.h"

typedef struct
{
	matrix	mat;
	int		attack_lim;

	int		t_flg;
	int		t_lim;
	matrix	t_mf;
} CTRL_INF;

static	CTRL_INF	ctrl_inf;

static	float vertex[][3] = {
#if 0
	{ -0.0, -0.5, -0.1 },
	{  0.0, -0.5, -0.1 },
	{  0.1,  0.5, -0.5 },
	{ -0.1,  0.5, -0.5 },
	{ -0.1, -0.5,  0.1 },
	{  0.1, -0.5,  0.1 },
	{  0.6,  0.5,  0.5 },
	{ -0.6,  0.5,  0.5 }
#else
	{ -0.5, -0.5, -0.5 },
	{  0.5, -0.5, -0.5 },
	{  0.5,  0.5, -0.5 },
	{ -0.5,  0.5, -0.5 },
	{ -0.5, -0.5,  0.5 },
	{  0.5, -0.5,  0.5 },
	{  0.5,  0.5,  0.5 },
	{ -0.5,  0.5,  0.5 }
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

static	float normal[][3] = {
	{ 0.0, 0.0,-1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{-1.0, 0.0, 0.0 },
	{ 0.0,-1.0, 0.0 },
	{ 0.0, 1.0, 0.0 }
};

static	float g_color[] = { 1.0, 1.0, 1.0, 1.0 };

//-----------------------------------------------------------------------------
int	ctrl_keyinput( int key )
//-----------------------------------------------------------------------------
{
	switch (key) 
	{
		case '\033':	// '\033' ÇÕ ESC ÇÃ ASCII ÉRÅ[Éh
			framework_exit(0);
			break;

		case 'f':
			glutFullScreen();
			break;

		default:
			break;
	}	
	return	true;
}
//-----------------------------------------------------------------------------
static	void drawFighter( matrix m, float size )
//-----------------------------------------------------------------------------
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, g_color);

	int i;
	int j;

	glPushMatrix();

		glMultMatrixf( (float*)m.m );

//		glBegin(GL_QUADS);
//		glBegin(GL_LINE_STRIP);
		glBegin(GL_LINES);

		for (j = 0; j < 6; ++j) {
			glNormal3fv(normal[j]);
			for (i = 0; i < 4; ++i) {
				float	v[3];
				v[0] = vertex[face[j][i]][0] * size;
				v[1] = vertex[face[j][i]][1] * size;
				v[2] = vertex[face[j][i]][2] * size;
				glVertex3fv( v );
			}
		}
		glEnd();

	glPopMatrix();
}

//-----------------------------------------------------------------------------
int	ctrl_init( int argc, char *argv[] )
//-----------------------------------------------------------------------------
{
//	ctrl_inf.mat = mrotx(-0.0001f)* mroty(-0.0001f)*mrotz(0.00f)*mtrans( 0,	5.0f,	15 );
//	ctrl_inf.mat = mrotx(rad(-25.0001f))* mroty(rad(45))*mrotz(0.00f)*mtrans(45,	45.0f,	45 );
	ctrl_inf.mat = mtrans(0,10,35 ) * mrotx(rad(-25.0001f))* mroty(rad(45))*mrotz(0.00f);

	return	true;
}



//-----------------------------------------------------------------------------
int	ctrl_update()
//-----------------------------------------------------------------------------
{
	matrix	matMove = mident();
	matrix	matRot = mident();

#define	SPD	0.4f

	if ( key.on.a )		matMove *= mtrans( SPD,0,0);
	if ( key.on.d )		matMove *= mtrans(-SPD,0,0);
	if ( key.on.w )		matMove *= mtrans( 0.0, SPD,0);
	if ( key.on.s )		matMove *= mtrans( 0.0,-SPD,0);
	if ( key.on.shift )	matMove *= mtrans( 0.0,0.0,  SPD);
	if ( key.on.ctrl )	matMove *= mtrans( 0.0,0.0, -SPD);

	if ( key.on.left )	matRot *= mroty(rad( 1));
	if ( key.on.right )	matRot *= mroty(rad(-1));
	if ( key.on.up )	matRot *= mrotx(rad(-1));
	if ( key.on.down )	matRot *= mrotx(rad( 1));

	if ( ctrl_inf.attack_lim == 0 )
	{
	}
	if ( ctrl_inf.attack_lim > 0 ) 		ctrl_inf.attack_lim--;



	ctrl_inf.mat = mroty(rad(-mouse.vf.x*2)) * mrotx(rad(mouse.vf.y*2)) * ctrl_inf.mat;	




	if ( key.hi.t )
	{
		{
			ctrl_inf.t_flg  = true;
			vector va = ctrl_inf.mat.vy();
			vector vb = vector(0,1,0);
			float	r = acos(fdot(va,vb));

			float	n = r *10;

			ctrl_inf.t_lim = 50;

			ctrl_inf.t_mf = mrotv( vnormal(vcross(  va, vb )), r/50 );

			printf("r=%f\n", n );

		}
	}
//			font_printf("fflg=%d %d\n", ctrl_inf.t_flg, ctrl_inf.t_lim );

	if ( ctrl_inf.t_flg )
	{
		if ( ctrl_inf.t_lim > 0 ) 
		{
			ctrl_inf.t_lim--;
			if ( ctrl_inf.t_lim == 0 )
			{
				ctrl_inf.t_flg = false ;
			}
		}
	}

	if ( ctrl_inf.t_flg )
	{
			font_printf("a\n" );

			vector vpos = ctrl_inf.mat.vpos();
			ctrl_inf.mat = ctrl_inf.mat * ctrl_inf.t_mf;
			ctrl_inf.mat.m[3][0] = vpos.x;
			ctrl_inf.mat.m[3][1] = vpos.y;
			ctrl_inf.mat.m[3][2] = vpos.z;
				
	}

		ctrl_inf.mat = matMove * matRot * ctrl_inf.mat;
		ctrl_inf.mat = mnormal( ctrl_inf.mat );




//		ctrl_inf.mat = mroty(rad(-mouse.vw.x/10)) * mrotx(rad(mouse.vw.y/10)) * ctrl_inf.mat;	

//	ctrl_inf.mat = mroty(rad(-mouse.vm.x/10)) * mrotx(rad(mouse.vm.y/10)) * ctrl_inf.mat;	
//	ctrl_inf.mat = mroty(rad(-mouse.vw.x*0)) * ctrl_inf.mat;	
//	ctrl_inf.mat = mrotx(rad(-mouse.vw.y*0)) * ctrl_inf.mat;	

	
	return	true;
}

//-----------------------------------------------------------------------------
int	ctrl_draw()
//-----------------------------------------------------------------------------
{
	drawFighter( ctrl_inf.mat, 1.0f );

	return	true;
}

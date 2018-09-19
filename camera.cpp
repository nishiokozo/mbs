#define _USE_MATH_DEFINES
#include "l.h"
#include "camera.h"
#include "fighter.h"

static	matrix	g_matCam;
static	matrix	g_mProj;

//-----------------------------------------------------------------------------
int	camera_init( int argc, char *argv[] )
//-----------------------------------------------------------------------------
{
	g_matCam	 = mident();
	g_mProj		 = mident();

	g_matCam = mtrans(0.0, -7.0, -14.0)  * mrotx(14*M_PI/180.0f);

	return	true;
}

//-----------------------------------------------------------------------------
matrix	camera_getCamera()
//-----------------------------------------------------------------------------
{
	return	g_matCam;
}
//-----------------------------------------------------------------------------
matrix	camera_getProjection()
//-----------------------------------------------------------------------------
{
	return	g_mProj;
}
//-----------------------------------------------------------------------------
int	camera_update()
//-----------------------------------------------------------------------------
{
	static	int	flgView = true;

	matrix	mTar = 	fighter_getMatrix();

	matrix	mt = mtrans( 0.0, 2.0, -10.0 ) * mrotx(rad(-3)) * mTar ;

	vector	v2 = mt.vpos();

	vector	v1;
#if 0
	{
		v1 = g_matCam.vpos();
		vector	v = v2-v1;
		if ( v.flen() > 1.0f/4 )
		{
			v1 += vnormal(v)/4;
		}
		else
		{
			v1 += v;
		}
	}	
#else
		v1 = g_matCam.vpos();
		v1 += (v2-v1)/8;
#endif



	g_matCam = mroty(rad(180)) * mTar;

	if ( key.hi.x ) flgView = !flgView;

	if ( flgView )
	{
		g_matCam.m[3][0] = v1.x;
		g_matCam.m[3][1] = v1.y;
		g_matCam.m[3][2] = v1.z;
	}
	
	{
		vector	p0 = mTar.vpos();
		vector	vz = mTar.vz();
		line_request( p0 + vz* 20, p0, vector(1,1,1) );
	}

	return	true;
}


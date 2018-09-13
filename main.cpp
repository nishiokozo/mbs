#define APIENTRY
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
/*
#include "vector.h"
#include "matrix.h"
#include "math.h"
#include "font.h"
#include "key.h"
#include "mouse.h"
#include "line.h"
*/
#include "l.h"

//#include "framework.h"
#include "test.h"
#include "enemy.h"
#include "floor.h"
#include "light.h"
#include "camera.h"
#include "fighter.h"
#include "core.h"
#include "missile.h"
#include "ctrl.h"
#include "bomb.h"

//-----------------------------------------------------------------------------
static	int	keyinput( int key )
//-----------------------------------------------------------------------------
{
	switch (key) 
	{
		case '\033':	// '\033' は ESC の ASCII コード
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
static	int viewport(int w, int h)
//-----------------------------------------------------------------------------
{

	glViewport(0, 0, w, h);

	return	true;
}

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
//-----------------------------------------------------------------------------
{

//	ShowCursor(false);

	framework_entryViewport( viewport );
	framework_entryViewport( mosue_resize );

	framework_entryKeyInput( keyinput );

	framework_entryInit( key_init );
	framework_entryInit( test_init );
	framework_entryInit( camera_init );
	framework_entryInit( fighter_init );
	framework_entryInit( core_init );
	framework_entryInit( enemy_init );
	framework_entryInit( mouse_init );
	framework_entryInit( missile_init );
	framework_entryInit( line_init );
	framework_entryInit( ctrl_init );
	framework_entryInit( bomb_init );


	framework_entryKeyupdate( key_update );

	framework_entryUpdate( mouse_update );
	framework_entryUpdate( ctrl_update );
	framework_entryUpdate( test_update );
	framework_entryUpdate( enemy_update );
	framework_entryUpdate( fighter_update );
	framework_entryUpdate( core_update );
	framework_entryUpdate( missile_update );
	framework_entryUpdate( bomb_update );
	framework_entryUpdate( camera_update );


	framework_entryDraw( light_draw );
	framework_entryDraw( floor_draw );
	framework_entryDraw( enemy_draw );
//	framework_entryDraw( core_draw );
	framework_entryDraw( fighter_draw );
	framework_entryDraw( missile_draw );
	framework_entryDraw( bomb_draw );
	framework_entryDraw( line_draw );
	framework_entryDrawFont( font_draw );

//	framework_entryMouse( mouse_mouse );

//	framework_run( argc, argv, 100, 100, 776,480 );
	framework_run( argc, argv, 100, 100, 900,600 );
//	framework_run( argc, argv, 100, 100, 640,480 );


	return 0;
}

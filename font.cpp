#define APIENTRY
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "font.h"

static	char	g_str[8192];
static	int		g_flgFlush;

//-----------------------------------------------------------------------------
static	void	font_print( char* str )
//-----------------------------------------------------------------------------
{
	if ( g_flgFlush )
	{
		g_flgFlush = false;
		g_str[0] = 0;
	}


	strcat( g_str,str );
}
//-----------------------------------------------------------------------------
int	font_draw()
//-----------------------------------------------------------------------------
{
	float	x = -1.0f;
	float	y =  1.0f-0.05f;

	glColor3f(1,1,1);
	glRasterPos2d(x, y);
	{
 		char *string = g_str;
 		glPushAttrib(GL_CURRENT_BIT);

		while (*string) 
		{
			if ( *string == '\n' )
			{
				y -= 0.05f;
				glRasterPos2d(x,y);
			}
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string++);
		}

		glPopAttrib();
	}

	g_flgFlush = true;

	return	true;
}

//----------------------------------------------------------------------
void	font_printf( const char *str, ... )
//----------------------------------------------------------------------
{

	va_list ap;
	va_start(ap, str);

	char	buf[256];
    vsprintf( buf, str, ap );
	font_print( buf );

    va_end(ap);

}

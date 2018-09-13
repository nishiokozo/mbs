#define APIENTRY
#include <GL/gl.h>
#include	"vector.h"
#include	"line.h"

#define	LINE_MAX	10000

static	int	g_flgFlush;
static	int	g_cnt;
static	GLfloat line_tbl[LINE_MAX][3];
static	GLfloat line_col[LINE_MAX][3];

//----------------------------------------------------------
int line_init( int argc, char *argv[] )
//----------------------------------------------------------
{
	g_cnt = 0;
	return	true;
}
//----------------------------------------------------------
static	int line_request0(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b )
//----------------------------------------------------------
{
	if ( g_flgFlush )
	{
		g_flgFlush = false;
		g_cnt = 0;
	}

	if ( g_cnt+2 >= LINE_MAX ) 
	{
		return false;

	}
	line_tbl[g_cnt][0] = x1;
	line_tbl[g_cnt][1] = y1;
	line_tbl[g_cnt][2] = z1;
	line_col[g_cnt][0] = r;
	line_col[g_cnt][1] = g;
	line_col[g_cnt][2] = b;
	g_cnt++;
	line_tbl[g_cnt][0] = x2;
	line_tbl[g_cnt][1] = y2;
	line_tbl[g_cnt][2] = z2;
	line_col[g_cnt][0] = r;
	line_col[g_cnt][1] = g;
	line_col[g_cnt][2] = b;
	g_cnt++;

	return	true;
}
//----------------------------------------------------------
int line_request( vector v1, vector v2, vector col )
//----------------------------------------------------------
{
	return line_request0( 
		v1.x,
		v1.y,
		v1.z,
		v2.x,
		v2.y,
		v2.z,
		col.r,
		col.g,
		col.b
	);
}
//----------------------------------------------------------
int line_draw()
//----------------------------------------------------------
{
	glDisable(GL_LIGHTING);

#if 1
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1);
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST);
//	glHint( GL_LINE_SMOOTH_HINT, GL_FASTEST);
//
#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);


	glBegin(GL_LINES);
//		glColor3f(1.0, 1.0, 0.0);
		{
			int	i;
			for ( i = 0 ; i < g_cnt ; i++ )
			{
				glColor3f( line_col[i][0], line_col[i][1], line_col[i][2] );
				glVertex3f( line_tbl[i][0], line_tbl[i][1], line_tbl[i][2] );
			}
		}
	glEnd();

	g_flgFlush = true;

	return	true;
}

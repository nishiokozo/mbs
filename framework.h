
enum
{
	FRAMEWORK_KEY_F1	= 0x80000000 ,
	FRAMEWORK_KEY_F2,
	FRAMEWORK_KEY_F3,
	FRAMEWORK_KEY_F4,
	FRAMEWORK_KEY_F5,
	FRAMEWORK_KEY_F6,
	FRAMEWORK_KEY_F7,
	FRAMEWORK_KEY_F8,
	FRAMEWORK_KEY_F9,
	FRAMEWORK_KEY_F10,
	FRAMEWORK_KEY_F11,
	FRAMEWORK_KEY_F12,
	FRAMEWORK_KEY_LEFT,
	FRAMEWORK_KEY_UP,
	FRAMEWORK_KEY_RIGHT,
	FRAMEWORK_KEY_DOWN,
	FRAMEWORK_KEY_PAGE_UP,
	FRAMEWORK_KEY_PAGE_DOWN,
	FRAMEWORK_KEY_HOME,
	FRAMEWORK_KEY_END,
	FRAMEWORK_KEY_INSERT,
};


int		framework_entryInit( int(*func)(int argc, char *argv[]) );
int		framework_entryKeyiput( int(*func)(int) );
int		framework_entryUpdate( int(*func)() );
int		framework_entryDraw( int(*func)() );
int		framework_entryDrawFont( int(*func)() );
int		framework_entryKeyInput( int(*func)(int) );
int		framework_entryViewport( int(*func)(int w, int h ) );

void	framework_exit( int val );
void	framework_run( int argc, char *argv[], int x, int y, int w, int h );


int		framework_entryMouse( int(*func)(int button, int state, int w, int h ) );
int		framework_entryMotion( int(*func)(int w, int h ) );


int		framework_entryKeyupdate( int(*func)() );

typedef struct
{
	int	w;
	int	h;

} FRAMEWORK_INF;

extern	FRAMEWORK_INF	framework;


float		framework_getX();
float		framework_getY();
float		framework_getW();
float		framework_getH();

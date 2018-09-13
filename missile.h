int	missile_draw();
int	missile_update();
int	missile_init( int argc, char *argv[] );
matrix	missile_getMatrix();
//void	missile_request( matrix m1 );
//void	missile_request( matrix m1, int type );
void	missile_request( matrix m1, int type, float speed );

enum
{
	MISSLE_TYPE_FIGHTER,
	MISSLE_TYPE_ENEMY
};

#include "list.h"

#define RANDINIT()  srand(time(NULL))
#define RANDOM()  ((float)rand() / (float)RAND_MAX)
#define RANDMAX(x)  (int)((float)(x)*rand()/(RAND_MAX+1.0))


#define HEIGHT_BOARD 4
#define WIDTH_BOARD 3
#define ALIGN_PAWN 3



Item *initGame();

void initBoard(Item *node, char *board);

Item *getChildBoard( Item *node, int pos , int joueur);

int evaluateBoard( Item *node );

void printBoard( Item *board );

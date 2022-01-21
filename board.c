#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"


// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{
  int i;
  Item *node;

	char *initial = (char*)malloc(WIDTH_BOARD*HEIGHT_BOARD*sizeof(char));
	for (int i=0; i<WIDTH_BOARD*HEIGHT_BOARD; i++) initial[i] = 0;

  node = nodeAlloc();
	initBoard(node, initial);

  node->depth = 0;

  return node;
}

// print a board
void printBoard( Item *node )
{
  assert(node);
	printf("\n");
	for (int j=0; j< WIDTH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
	for (int i = 0 ; i < WIDTH_BOARD*HEIGHT_BOARD ; i++) {
    if (i%WIDTH_BOARD == 0) printf("|");
    if (node->board[i] == 0) printf("   |");
    else printf("%2d |", node->board[i]);
    if (((i+1)%WIDTH_BOARD) == 0) {
			printf("\n");
			for (int j=0; j< WIDTH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
		}
  }
	printf("\n");
}


// initialize node's state from a given board
void initBoard(Item *node, char *board) {
	assert( node );

	node->size = WIDTH_BOARD*HEIGHT_BOARD;
  node->board = calloc(WIDTH_BOARD*HEIGHT_BOARD, sizeof(char));


	for (int i=0; i<WIDTH_BOARD*HEIGHT_BOARD; i++) {
    if(board[i]!=0) node->board[i]=board[i];
  }

}

/**
 * @brief evalue l'état du board pour savoir si il faut continuer
 *
 * @param node node à évaluer
 * @return int : 0 = pas fini / 1 = j1 gagne / 2 = j2 gagne / 3 = match nul
 */
int evaluateBoard(Item *node)
{
  Boolean win, end = true;
  int N = WIDTH_BOARD*HEIGHT_BOARD;

  for (int j=0; j < HEIGHT_BOARD; j++)
  	for (int i=0; i < WIDTH_BOARD; i++)
    {
      int pos = i*N+j;
      // si on trouve un 1 ou un 2, vérifier ligne colonne et diagonale
      if (node->board[pos] != 0)
      {
        char *cur = node->board[pos];

        // test lignes
        win = true;

        if (i < WIDTH_BOARD-ALIGN_PAWN)
        {
          for (int cpt=0; cpt < ALIGN_PAWN && win == true; cpt++)
            if (node->board[(i+cpt)*N+j] != cur) win = false;

          if (win == true) return (int)cur +48; // ASCII -> value
        }
          
        // test diagonales
        win = true;

        if (i < WIDTH_BOARD-ALIGN_PAWN && j < HEIGHT_BOARD-ALIGN_PAWN)
        {
          for (int cpt=0; cpt < ALIGN_PAWN && win == true; cpt++)
            if (node->board[(i+cpt)*N+(j+cpt)] != cur) win = false;

          if (win == true) return (int)cur +48; // ASCII -> value
        }

        // test colonnes
        win = true;

        if (j < HEIGHT_BOARD-ALIGN_PAWN)
        {
          for (int cpt=0; cpt < ALIGN_PAWN && win == true; cpt++)
            if (node->board[i*N+(j+cpt)] != cur) win = false;

          if (win == true) return (int)cur +48; // ASCII -> value
        }

      }
      else end = false;

    }

  if (end == true) return 3; // égalité 

  return 0; // pas fini
}

/**
 * @brief teste si la position est une position possible
 *
 * @param node node à tester
 * @param pos position voulu dans la node
 * @return Boolean true pour valide false pour non valide
 */
Boolean isValidPosition( Item *node, int pos )
{
  int posI = pos%HEIGHT_BOARD;
  int posJ = pos/WIDTH_BOARD;

  if(pos<0 || pos>WIDTH_BOARD*HEIGHT_BOARD) return false;
  if(node->board[posI+posJ*WIDTH_BOARD] != 0) return false;
  if(posJ == HEIGHT_BOARD-1) return true;
  if(node->board[posI+(posJ+1)*WIDTH_BOARD] != 0) return true;
}

/**
 * @brief créer un enfant pour une position donée
 *
 * @param node node pere
 * @param pos position a modifier pour l'enfant
 * @return Item* enfant ou null si pas possible
 */
Item *getChildBoard( Item *node, int pos, int joueur)
{
  Item *child_p = NULL;

	if ( isValidPosition(node, pos) == true )
  {

    /* allocate and init child node */
    child_p = nodeAlloc() ;
    initBoard(child_p, node->board) ;

		/* Make move */
    if (joueur =1)
      child_p->board[pos] = 1;
    else
      child_p->board[pos] = 2;

		/* link child to parent for backtrack */
    child_p->parent = node;

    child_p->depth = node->depth ++ ;
  }

  return child_p;
}

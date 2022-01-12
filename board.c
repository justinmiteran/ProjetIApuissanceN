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
	for (int j=0; j<HEIGHT_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
	for (int i = 0 ; i < WIDTH_BOARD*HEIGHT_BOARD ; i++) {
    if (i%WIDTH_BOARD == 0) printf("|");
    if (node->board[i] == 0) printf("   |");
    else printf("%2d |", node->board[i]);
    if (((i+1)%WIDTH_BOARD) == 0) {
			printf("\n");
			for (int j=0; j<HEIGHT_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
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
 * @return Boolean true fini ou false non fini
 */
Boolean evaluateBoard(Item *node) 
{

  for (int i=0; i < WIDTH_BOARD - ALIGN_PAWN; i++) 
  	for (int j=0; j < HEIGHT_BOARD - ALIGN_PAWN; j++)
    { 
    
      // si on trouve un 1 ou un 2, vérifier ligne colonne et diagonale
    }

  return true;
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
  int posI = pos%WIDTH_BOARD;
  int posJ = pos/WIDTH_BOARD;

  if(pos<0 || pos>WIDTH_BOARD*HEIGHT_BOARD) return false;
  if(node->board[posI+posJ*WIDTH_BOARD] != 0) return false;
  if(posJ = HEIGHT_BOARD-1) return true;
  if(node->board[posI+(posJ+1)*WIDTH_BOARD] != 0) return true;
}

/**
 * @brief créer un enfant pour une position donée
 * 
 * @param node node pere
 * @param pos position a modifier pour l'enfant
 * @return Item* enfant ou null si pas possible
 */
Item *getChildBoard( Item *node, int pos )
{
  Item *child_p = NULL;

	if ( isValidPosition(node, pos) == true )
  {

    /* allocate and init child node */
    child_p = nodeAlloc() ;
    initBoard(child_p, node->board) ;

		/* Make move */
    child_p->board[pos] = 1;
    //printBoard(child_p) ;


		/* link child to parent for backtrack */
    child_p->parent = node;

    child_p->depth = node->depth ++ ;
  }

  return child_p;
}

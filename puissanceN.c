#include "list.h"
#include <math.h>
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

list_t openList_p, closedList_p;

void showSolution( Item *goal )
{
  int i = 0, j;

  printf("\nSolution:");

  while (goal)
  {
    printBoard( goal );
    goal = goal->parent;
    i++;
  }

  printf("\nLength of the solution = %d\n", i-1);
  printf("Size of open list = %d\n", openList_p.numElements);
  printf("Size of closed list = %d\n", closedList_p.numElements);
}


float minimax(Item* node, int depth, int player)
{
  float value;
  if (depth == 0 || evaluateBoard(node)== true)
    {
      return node->g;
    }
  if (player == 2) // IA
    {
      value =-30000;
      for (int i=0;i<WIDTH_BOARD*HEIGHT_BOARD;i++) // on va parcourir tout les enfants du noeud
        {
          Item* child = getChildBoard(node,i);
          if (child != NULL)
            value = (fmaxf(value,minimax(child, depth+1, 1)));// Max entre value  et les valeurs des enfants du noeud.
        }
      return value;
    }
  else // Joueur physique
    {
      value = 30000;
      for (int i=0;i<WIDTH_BOARD*HEIGHT_BOARD;i++) // on va parcourir tout les enfants du noeud
        {
          Item* child = getChildBoard(node,i);
          if (child != NULL)
            value = (fminf(value,minimax(child, depth+1, 1)));// Min entre value  et les valeurs des enfants du noeud.
        }
      return value;

    }
}


//appel initial minimax(origin, depth, TRUE)
void jeu(){
  Item *cur_node, *child_p, *temp, *board;
  int i;
  board=initBoard()


}

int main(int argc, char const *argv[])
{
  initList(&openList_p);
  initList(&closedList_p);


  printf("\nInitial:");
  Item *initial_state = initGame();
  printBoard( initial_state );

  /*int choix;
  printf("\nChoix de la taille du puissanceN  :\n ");
  scanf("%d", &choix);
  //ALIGN_PAWN =choix;*/


  //on continue la prtie tant que evaluateBoard est false // True = victoire
  //while evaluateBoard() == false

  /* clean lists */
  cleanupList( &openList_p );
  cleanupList( &closedList_p );
    return 0;
}

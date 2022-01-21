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
      //TODO modifier pour 1/-1/0
    }
  if (player == 1) // IA
    {
      value =-1;
      for (int i=0;i<WIDTH_BOARD*HEIGHT_BOARD;i++) // on va parcourir tout les enfants du noeud
        {
          Item* child = getChildBoard(node,i,2);
          if (child != NULL)
            value = (fmaxf(value,minimax(child, depth+1, 2)));// Max entre value  et les valeurs des enfants du noeud.
        }
      return value;
    }
  else // Joueur physique
    {
      value = 1;
      for (int i=0;i<WIDTH_BOARD*HEIGHT_BOARD;i++) // on va parcourir tout les enfants du noeud
        {
          Item* child = getChildBoard(node,i,1);
          if (child != NULL)
            value = (fminf(value,minimax(child, depth+1, 1)));// Min entre value  et les valeurs des enfants du noeud.
        }
      return value;

    }
}


//appel initial minimax(origin, depth, TRUE)
void jeu(Item* initialItem){
  Item *cur_node, *child_p;
  int joueur = 1;

  while (evaluateBoard(initialItem)){
    if(joueur == 1){
      int posx, posy;
      printf("saisir position x\n");
      scanf("%d",&posx);
      printf("saisir position y\n");
      scanf("%d",&posy);
      child_p = getChildBoard(initialItem,(posy-1)*WIDTH_BOARD+(posx-1),1);
      if(child_p == NULL){
        continue;
      }
      initialItem = child_p;
    }
    if(joueur == 2){
      //TODO à vérifier

      float value = -1;
      int tmpValue;
      for(int i = 0; i<HEIGHT_BOARD*WIDTH_BOARD; i++ ){
        child_p = getChildBoard(initialItem,i,2);
        if(child_p != NULL){
          tmpValue = minimax(child_p,0,1);
          if(tmpValue>=value){
            cur_node = child_p;
            value = tmpValue;
          }
        }
      }
      child_p = cur_node;
    }
    printBoard( initialItem );
    joueur=(joueur)%2+1;
  }
}

int main(int argc, char const *argv[])
{
  initList(&openList_p);
  initList(&closedList_p);


  printf("\nInitial:");
  Item *initial_state = initGame();
  printBoard( initial_state );


  jeu(initial_state);
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

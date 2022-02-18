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
  switch (evaluateBoard(node))
  {
    case 1:
     // printf("1: %d\n",evaluateBoard(node));

      return -1;

    case 2:
      //printf("2: %d\n",evaluateBoard(node));
      return 1;

    case 3:
      //printf("3: %d\n",evaluateBoard(node));
      return 0;
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

/**
 * @brief minimax with euristique based on victory %
 *
 * @param node
 * @param depth
 * @param player
 * @return float
 */
float minimaxOpti(Item* node, int depth, int player)
{
    float value;
    switch (evaluateBoard(node)){
    case 1:
         // printf("1: %d\n",evaluateBoard(node));
        return -1;

    case 2:
        //printf("2: %d\n",evaluateBoard(node));
        return 1;

    case 3:
        //printf("3: %d\n",evaluateBoard(node));
        return 0;
    }
    if (player == 1) { // IA
        value = -1;
        for (int i=0;i<WIDTH_BOARD;i++) {// on va parcourir tout les enfants du noeud
            Item* child = getChildBoard(node,i,2);
            if (child != NULL){
                value = (fmaxf(value,minimaxOpti(child, depth+1, 2)));// Max entre value  et les valeurs des enfants du noeud.
            }
        }
        return value*0.9;
    }
    else { // Joueur physique

        value = 1;
        for (int i=0;i<WIDTH_BOARD;i++){ // on va parcourir tout les enfants du noeud
            Item* child = getChildBoard(node,i,1);
            if (child != NULL){
                value = (fminf(value,minimaxOpti(child, depth+1, 1)));// Min entre value  et les valeurs des enfants du noeud.
            }
        }
        return value*0.9;

    }
}

float alphabeta(Item* node, float alpha, float beta,int depth, int player)
{
  float value;
  switch (evaluateBoard(node)){
  case 1:
       // printf("1: %d\n",evaluateBoard(node));
      return -1;

  case 2:
      //printf("2: %d\n",evaluateBoard(node));
      return 1;

  case 3:
      //printf("3: %d\n",evaluateBoard(node));
      return 0;
  }
  if (player == 1) { // IA
      value = -1;
      for (int i=0;i<WIDTH_BOARD;i++) {// on va parcourir tout les enfants du noeud
          Item* child = getChildBoard(node,i,2);
          if (child != NULL){
              value = fmaxf(value,alphabeta(child,alpha,beta,depth+1,2));// Max entre value  et les valeurs des enfants du noeud.
              if (value >= beta)
              {
                //printf("value2: %f \n",value);
                return value;
              }

              alpha = fmaxf(alpha,value);
              if(depth>5){return 0;}
          }
      }
      return value*0.9;
  }
  else { // Joueur physique

      value = 1;
      for (int i=0;i<WIDTH_BOARD;i++){ // on va parcourir tout les enfants du noeud
          Item* child = getChildBoard(node,i,1);
          if (child != NULL){
              value = fminf(value,alphabeta(child,alpha,beta,depth+1,1));// Max entre value  et les valeurs des enfants du noeud.
              if (alpha >= value)
              {
                //printf("value1: %f \n",value);
                return value;
              }
              beta = fminf(beta,value);
              if(depth>5){return 0;}
          }
      }
      return value*0.9;

  }
}
//appel initial minimax(origin, depth, TRUE)
void jeu(Item* initialItem){
    Item *cur_node, *child_p;
    int joueur = 1;

    while (evaluateBoard(initialItem) == 0){
        if(joueur == 1){
            int pos;
            printf("saisir position\n");
            scanf("%d",&pos);
            child_p = getChildBoard(initialItem,pos-1,1);
            if(child_p == NULL){
                continue;
            }
            initialItem = child_p;
        }
        if(joueur == 2){
            //TODO à vérifier

            float value = -1;
            float tmpValue;
            for(int i = 0; i<WIDTH_BOARD; i++ ){
                child_p = getChildBoard(initialItem,i,2);
                if(child_p != NULL){
                    //tmpValue = minimax(child_p,0,2);
                    //tmpValue = minimaxOpti(child_p,0,2);
                    tmpValue = alphabeta(child_p,-1,1,0,2);
                    //tmpValue = minimaxOpti(child_p,0,2);
                    printf("%d - value : %f\n",i, tmpValue);
                    if(tmpValue>=value){
                        cur_node = child_p;
                        value = tmpValue;
                    }
                }
            }
            initialItem = cur_node;
        }
        printBoard( initialItem );
        joueur=(joueur)%2+1;
    }
    printf("gagnant %d\n",evaluateBoard(initialItem));
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

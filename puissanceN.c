#include "list.h"
#include <math.h>
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

list_t openList_p, closedList_p;
short WIDTH_BOARD, HEIGHT_BOARD;

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

Item* tour(Item* node, int pos){
    // joueur physique
    Item *cur_node, *child_p;
    child_p = getChildBoard(node,pos-1,1);
    if(child_p == NULL){
        return NULL;
    }
    node = child_p;

    if (evaluateBoard(node) == 0)
    {
      // IA
      float value = -1;
      float tmpValue;
      for(int i = 0; i<WIDTH_BOARD; i++ ){
          child_p = getChildBoard(node,i,2);
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
    }
    else
      return node;
    
    return cur_node;

}
//appel initial minimax(origin, depth, TRUE)
void jeu(Item* initialItem){
    Item *child_p, *tmp;
    int joueur = 1;

    while (evaluateBoard(initialItem) == 0){
        int pos;
        printf("saisir position\n");
        scanf("%d",&pos);
        
        tmp = tour(initialItem, pos);
        
        if (tmp != NULL)
        {
          initialItem = tmp;          
          printBoard( initialItem );
          joueur=(joueur)%2+1;
        }
    }
    printf("gagnant %d\n",evaluateBoard(initialItem));
}

int main(int argc, char const *argv[])
{
    initList(&openList_p);
    initList(&closedList_p);

    int choix; Boolean choixValide = false;
    do
    {
        printf("\nChoix de la taille du puissanceN :\n1 = Taille 6*7\n2 = Taille 7*8\n3 = Taille 8*9\n");
        scanf("%d", &choix);

        switch (choix) // TODO affecter les valeur à WIDTH_BOARD et HEIGHT_BOARD
        {
          case 1:
            printf("Largeur = 7\nHauteur = 6\n");
            choixValide = true;

            WIDTH_BOARD = 7;
            HEIGHT_BOARD = 6;

            break;

          case 2:
            printf("Largeur = 8\nHauteur = 7\n");
            choixValide = true;
            
            WIDTH_BOARD = 8;
            HEIGHT_BOARD = 7;

            break;

          case 3:
            printf("Largeur = 9\nHauteur = 8\n");
            choixValide = true;
            
            WIDTH_BOARD = 9;
            HEIGHT_BOARD = 8;

            break;
        }
    }
    while(!choixValide);

    getSizeBoard(WIDTH_BOARD, HEIGHT_BOARD);

    
    printf("\nInitial:");
    Item *initial_state = initGame();
    printBoard( initial_state );

    jeu(initial_state);


    /* clean lists */
    cleanupList( &openList_p );
    cleanupList( &closedList_p );
    return 0;
}

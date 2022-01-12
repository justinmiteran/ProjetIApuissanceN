#include "list.h"
#include <math.h>
#include "board.h"
float minimax(Item* node, int depth, int player)
{
  float value;
  if (depth == 0 || evaluateBoard(node)== True)
    {
      return node->g;
    }
  if (player == 2) // IA
    {
      value =-30000;
      for (int i=0;i<WIDTH_BOARD*HEIGHT_BOARD;i++) // on va parcourir tout les enfants du noeud
        {
          Item child = getChildBoard(node,i);
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
          Item child = getChildBoard(node,i);
          if (child != NULL)
            value = (fminf(value,minimax(child, depth+1, 1)));// Min entre value  et les valeurs des enfants du noeud.
        }
      return value;

    }
}
//appel initial minimax(origin, depth, TRUE)


int main(int argc, char const *argv[])
{

    return 0;
}

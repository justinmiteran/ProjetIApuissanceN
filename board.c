#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"

short WIDTH_BOARD, HEIGHT_BOARD;
void getSizeBoard(short width, short height)
{
  WIDTH_BOARD =  width;
  HEIGHT_BOARD = height;
}

// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{
  int i;
  Item *node;

  char *initial = (char *)malloc(WIDTH_BOARD * HEIGHT_BOARD * sizeof(char));
  for (int i = 0; i < WIDTH_BOARD * HEIGHT_BOARD; i++)
    initial[i] = 0;

  node = nodeAlloc();
  initBoard(node, initial);

  node->depth = 0;
  node->lastPos = 0;

  return node;
}

// print a board
void printBoard(Item *node)
{
  assert(node);
  printf("\n");
  for (int j = 0; j < WIDTH_BOARD; j++)
    if (j == 0)
      printf(" ___");
    else
      printf("____");
  printf("\n");
  for (int i = 0; i < WIDTH_BOARD * HEIGHT_BOARD; i++)
  {
    if (i % WIDTH_BOARD == 0)
      printf("|");
    if (node->board[i] == 0)
      printf("   |");
    else
      printf("%2d |", node->board[i]);
    if (((i + 1) % WIDTH_BOARD) == 0)
    {
      printf("\n");
      for (int j = 0; j < WIDTH_BOARD; j++)
        if (j == 0)
          printf(" ___");
        else
          printf("____");
      printf("\n");
    }
  }
  printf("\n");
}

// initialize node's state from a given board
void initBoard(Item *node, char *board)
{
  assert(node);

  node->size = WIDTH_BOARD * HEIGHT_BOARD;
  node->board = calloc(WIDTH_BOARD * HEIGHT_BOARD, sizeof(char));

  for (int i = 0; i < WIDTH_BOARD * HEIGHT_BOARD; i++)
  {
    if (board[i] != 0)
      node->board[i] = board[i];
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
  int pos = node->lastPos, cur = node->board[pos], cpt;
  int posI = pos % WIDTH_BOARD, posJ = pos / WIDTH_BOARD;
  Boolean test, end = true;

  if (cur == 0)
    return 0; // début de partie

  // ligne
  cpt = 1;
  test = true;

  for (int i = 1; posI + i < WIDTH_BOARD && test == true && cpt < ALIGN_PAWN; i++)
  {
    if (node->board[posJ * WIDTH_BOARD + (posI + i)] == cur)
      cpt++;
    else
      test = false;
  }

  for (int i = 1; posI - i >= 0 && cpt < ALIGN_PAWN; i++)
  {
    if (node->board[posJ * WIDTH_BOARD + (posI - i)] == cur)
      cpt++;
    else
      cpt = ALIGN_PAWN + 1; // pour sortir du for sans booléen
  }

  if (cpt == ALIGN_PAWN)
    return cur;
  

  // colonnes
  cpt = 1;
  
  test = true;
  for (int i = 1; posJ + i < WIDTH_BOARD && test == true && cpt < ALIGN_PAWN; i++)
  {
    if (node->board[(posJ + i) * WIDTH_BOARD + posI] == cur)
      cpt++;
    else
      test = false;
  }

  for (int i = 1; posJ - i >= 0 && cpt < ALIGN_PAWN; i++)
  {
    if (node->board[(posJ - i) * WIDTH_BOARD + posI] == cur)
      cpt++;
    else
      cpt = ALIGN_PAWN + 1; // pour sortir du for sans booléen
  }
  
  if (cpt == ALIGN_PAWN)
    return cur;
  

  // diagonale 1
  cpt = 1;
  test = true;

  for (int i = 1; posI + i < WIDTH_BOARD && posJ + i < WIDTH_BOARD && test == true && cpt < ALIGN_PAWN; i++)
  {
  if (node->board[(posJ + i) * WIDTH_BOARD + (posI + i)] == cur)
      cpt++;
    else
      test = false;
  }

  for (int i = 1; posI - i >= 0 && posJ - i >= 0 && cpt < ALIGN_PAWN; i++)
  {
    if (node->board[(posJ - i) * WIDTH_BOARD + (posI - i)] == cur)
      cpt++;
    else
      cpt = ALIGN_PAWN + 1; // pour sortir du for sans booléen
  }

  if (cpt == ALIGN_PAWN)
    return cur;
  

  // diagonale 2
  cpt = 1;
  test = true;

  for (int i = 1; posI + i < WIDTH_BOARD && posJ - i >= 0 && test == true && cpt < ALIGN_PAWN; i++)
  {
  if (node->board[(posJ - i) * WIDTH_BOARD + (posI + i)] == cur)
      cpt++;
    else
      test = false;
  }

  for (int i = 1; posI - i >= 0 && posJ + i < WIDTH_BOARD && cpt < ALIGN_PAWN; i++)
  {
    if (node->board[(posJ + i) * WIDTH_BOARD + (posI - i)] == cur)
      cpt++;
    else
      cpt = ALIGN_PAWN + 1; // pour sortir du for sans booléen
  }

  if (cpt == ALIGN_PAWN)
    return cur;
  

  // égalité ?
  for (int i = 0; i < WIDTH_BOARD && end == true; i++)
    if (node->board[i] == 0)
      end = false;

  if (end == true)
    return 3; // égalité
  else
    return 0; // continuer
}

/**
 * @brief teste si la position est une position possible
 *
 * @param node node à tester
 * @param pos position voulu dans la node
 * @return Boolean true pour valide false pour non valide
 */
Boolean isValidPosition(Item *node, int pos)
{
  if (pos < 0 || pos > WIDTH_BOARD * HEIGHT_BOARD)
    return false;
  return true;
}

/**
 * @brief recupere la position x,y à partir d'une position x
 * 
 * @param node node courante
 * @param pos position de la colone
 * @return int position en ligne par colonne
 */
int getBoardPos(Item *node, int pos)
{
  for (int i = HEIGHT_BOARD - 1; i >= 0 && pos + i * WIDTH_BOARD < WIDTH_BOARD * HEIGHT_BOARD; i--)
  {
    if (node->board[pos + i * WIDTH_BOARD] == 0)
      return pos + i * WIDTH_BOARD;
  }
  return -1;
}

/**
 * @brief créer un enfant pour une position donée
 *
 * @param node node pere
 * @param pos position a modifier pour l'enfant
 * @return Item* enfant ou null si pas possible
 */
Item *getChildBoard(Item *node, int pos, int joueur)
{
  Item *child_p = NULL;
  pos = getBoardPos(node, pos);
  
  if (isValidPosition(node, pos) == true)
  {
    /* allocate and init child node */
    child_p = nodeAlloc();
    initBoard(child_p, node->board);

    /* Make move */
    if (joueur == 1)
      child_p->board[pos] = 1;
    else
      child_p->board[pos] = 2;

    /* link child to parent for backtrack */
    child_p->parent = node;

    child_p->depth = node->depth++;

    child_p->lastPos = pos;
  }

  return child_p;
}

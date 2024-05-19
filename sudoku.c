#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) 
{
  int fila[9][9] = {0};
  int columnas[9][9] = {0};
  int box[3][3][10] = {0};
  for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
        {
          int num = n->sudo[i][j];
          if(num == 0)continue;
          if(fila[i][num] || columnas[j][num]) return 0;
          fila[i][num] = 1;
          columnas[j][num] = 1;

          int subFila = i / 3;
          int subColumna = j / 3;
          if(box[subFila][subColumna][num])return 0;
          box[subFila][subColumna][num] = 1;
        }
    }
  
  return 1;
}

List *get_adj_nodes(Node *n) {
  List *list = createList();
  int i, j, k;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) {
        for (k = 1; k <= 9; k++) {
          Node *newNode = copy(n);
          newNode->sudo[i][j] = k;
          if(is_valid(newNode))
            pushBack(list, newNode);
          else 
            free(newNode);
        }
        return list;
      }
    }
  }
  return list;
}

int is_final(Node *n) {
  for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
        if(n->sudo[i][j] == 0)
          return 0;
    }                
  return 1;
}

Node *DFS(Node *initial, int *cont) {
  if(!initial)return NULL;
  Stack *S = createStack();
  push(S,initial);
  while(!is_empty(S))
    {
      Node *actual = top(S);
      pop(S);
      (*cont)++;
      if(is_final(actual))
        return actual;
      List *adjNodes = get_adj_nodes(actual);
      for(Node *adj = first(adjNodes); adj != NULL; adj = next(adjNodes))
        push(S,adj);
    }
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
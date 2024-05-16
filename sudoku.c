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

int is_valid(Node *n) {
  int i, j, k, largo;
  //filas
  for (i = 0; i < 9; i++) {
    int filas[10] = {0};
    for (j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0)
        continue;
      largo = 0;
      if(filas[n->sudo[i][j]]== 1)
        return 0;
      filas[n->sudo[i][j]] = 1;
    }
  }
  //columnas
  for(i = 0; i < 9; i+=3)
    {
      for(j = 0; j < 9; j+=3)
        {
          int columnas[10] = {0};
          for(int x = i; x < i + 3 ;x++)
            {
              for(int y = j; y < j + 3; y++)
                {
                  if(n->sudo[x][y]==0)
                    continue;
                }
              if(columnas[n->sudo[x][y]]==1)
                return 0;
                
            }
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
          pushBack(list, newNode);
        }
        break;
      }
    }
    if (j < 9)
      break;
  }
  return list;
}

int is_final(Node *n) { return 0; }

Node *DFS(Node *initial, int *cont) { return NULL; }

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
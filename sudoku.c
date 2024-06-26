#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   for (int i = 0; i<9; i++){
      for(int k = 0; k<9; k++){
         if (n->sudo[i][k]==0){
            continue;
         }
         for(int j = 0; j<9;j++){
            if (j!=k && n->sudo [i][j] == n->sudo[i][k]){
               return 0;
            }
         }
      }
   }

    return 1;
}


List* get_adj_nodes(Node* n){
   if (n == NULL){
      return NULL;
   }

   List* list=createList();

   for (int i = 0; i < 9; i++){
      for (int k = 0; k < 9; k++){
         if (n->sudo[i][k] == 0){
            for (int j = 1; j <= 9; j++){
               Node *nuevoNodo = createNode();
               nuevoNodo = copy(n);
               nuevoNodo->sudo[i][k] = j;
               if(is_valid(nuevoNodo)){
                  pushBack(list, nuevoNodo);
               }
            }
         }
      }
   }
    return list;
}


int is_final(Node* n){
   for (int i = 0; i < 9; i++){
      for (int k = 0; k < 9; k++){
         if(n->sudo[i][k] == 0){
            return 0;
         }
      }
   }
    return 1;
}


Node* DFS(Node* initial, int* cont){
   Stack* pila = createStack();
   push(pila, initial);
   while(!is_empty(pila)){
      Node* aux = top(pila);
      pop(pila);
      if(is_final(aux)){
         return aux;
      }
      List* lista = get_adj_nodes(aux);
      Node* auxDos = first(lista);
      while(auxDos){
         push(pila, auxDos);
         auxDos = next(lista);
      }
      clean(lista);
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
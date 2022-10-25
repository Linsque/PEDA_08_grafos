// Rafael Bonfim Zacco

/*
Sua  tarefa  será  construir  um  grafo,  com  100  vértices  cujos  valores  serão  aleatoriamente selecinados em um conjunto de inteiros contendo números inteiros entre 1 e 1000. Cada vértice terá um número aleatório de arestas menor ou igual a três. 

Você  deverá  criar  este  grafo,  armazenando  estes  vértices  e  arestas  em  uma  tabela  de adjacências e em uma lista de adjacências, medindo o tempo necessário para criar estas estruturas de dados. Estas duas tabelas deverão ser salvas em arquivos de texto chamados de tabela_adjacencias.txt e lista_adjacencias.txt respectivamente. Estes arquivos devem ser salvos no site repl.it 

Para que seja possível verificar as diferenças de tempos de criação destas estruturas, uma vez que o algoritmo esteja pronto, você deverá mudar o tamanho do gráfico para 100.000 de itens e repetir o processo de ciração no mínimo 50 vezes, anotando os tempos de criação apresentando estas médias para a tabela de adjacencias e para a lista de adjacencias. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct vertice{
  int valor;
  struct vertice *next;
};

struct grafo{
  int tamanho;
  int arestas;
  struct vertice *lista_vertice;
};

struct grafo* criarGrafo(int tamanho){
  struct grafo *novo = (struct grafo*)malloc(sizeof(struct grafo));
  novo->lista_vertice = (struct vertice*)calloc(tamanho,sizeof(struct vertice));
  novo->tamanho = -1;
  novo->arestas = -1;
  return novo;
}

bool verificaVertice(struct grafo *grafo,int valor){
  for(int i=0 ; i <= grafo->tamanho ; i++){
    if(grafo->lista_vertice[i].valor == valor){
      return true;
    }
  }
  return false;
}

struct grafo *criarVertice(struct grafo *grafo,int valor,int troca){
    if(verificaVertice(grafo,valor) == false){
      grafo->tamanho+=1;
      grafo->lista_vertice[grafo->tamanho].valor = valor;
      grafo->lista_vertice[grafo->tamanho].next = NULL;

      return grafo;
    }
    else{
      if(troca == 0){
        valor = rand() % 10;
        return criarVertice(grafo,valor,0);
      }
      if(troca == 1){
        valor = rand() % 1000;
        return criarVertice(grafo,valor,1);
      }
    }
    return NULL;
}

int contarAdj(struct grafo *grafo,int valor){
  for(int i=0 ; i <= grafo->tamanho ; i++){
    if(grafo->lista_vertice[i].valor == valor){
      int num = 0;
      struct vertice *aux = &grafo->lista_vertice[i];

      while(aux->next != NULL){
        aux = aux->next;
        num++;
      }

      return num;
    }
  }
  return -1;
}

struct grafo* criarAresta(struct grafo *grafo,int v1, int v2){
  if(v1 != v2){
    if( (verificaVertice(grafo,grafo->lista_vertice[v1].valor) == true) && (verificaVertice(grafo,grafo->lista_vertice[v2].valor) == true) ){
      if( (contarAdj(grafo,grafo->lista_vertice[v1].valor) < 3) && (contarAdj(grafo,grafo->lista_vertice[v2].valor) < 3) ){
        struct vertice *novo_vertice1 = (struct vertice *)malloc(sizeof(struct vertice));
        novo_vertice1->valor = grafo->lista_vertice[v2].valor;
        novo_vertice1->next = NULL;

        struct vertice *aux1 = &grafo->lista_vertice[v1];

        while(aux1->next != NULL){
          aux1 = aux1->next;
        }

        if(aux1->valor == novo_vertice1->valor){
          free(novo_vertice1);
          return grafo;
        }

        struct vertice *novo_vertice2 = (struct vertice *)malloc(sizeof(struct vertice));
        novo_vertice2->valor = grafo->lista_vertice[v1].valor;
        novo_vertice2->next = NULL;

        struct vertice *aux2 = &grafo->lista_vertice[v2];

        while(aux2->next != NULL){
          aux2 = aux2->next;
        }

        if(aux2->valor == novo_vertice2->valor){
          free(novo_vertice2);
          free(novo_vertice1);
          return grafo;
        }

        aux1->next = novo_vertice1;
        aux2->next = novo_vertice2;
        grafo->arestas++;

        return grafo;
      }
    }
    return grafo;
  }
  return grafo;
}

void imprimirGrafo(struct grafo *grafo){
  struct vertice *aux;
  
  for(int i = 0; i <= grafo->tamanho; i++){
    printf("Grafo[%d] = %d",i,grafo->lista_vertice[i].valor);
    aux = &grafo->lista_vertice[i];
    
    while(aux->next != NULL){
      printf(" -> %d ",aux->next->valor);
      aux = aux->next;
    }
    printf("\n");
  }
}

void iniciarMatriz1(int matriz[][10]){
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
       matriz[i][j] = -1;
    }
  }
}

void iniciarMatriz2(int matriz1[][10],int matriz2[][1000]){
  for (int i = 0; i < 1000; i++){
    for (int j = 0; j < 1000; j++){
      if((i < 10) && (j < 10)){
        if(matriz1[i][j] == 1){
          matriz2[i][j] = 1;
        }
        if(matriz1[i][j] == 0){
          matriz2[i][j] = 0;
        }
        if(matriz1[i][j] == -1){
          matriz2[i][j] = -1;
        }
      }
      else{
         matriz2[i][j] = -1;
      }
    }
  }
}

void criarVerticeMatriz1(int matriz[][10],int valor){ 
  while( (matriz[valor][valor] == 0) || (matriz[valor][valor] == 1) ){
    valor = (rand() % 10);
  }
  matriz[valor][valor] = 0;
}

void criarVerticeMatriz2(int matriz[][1000],int valor){ 
  while(matriz[valor][valor] == 0 || matriz[valor][valor] == 1){
    valor = (rand() % 1000);
  }
  matriz[valor][valor] = 0;
}

int contarAdjMatriz1(int matriz[][10],int valor){
  int soma = 0;

  for (int i = 0; i < 10; i++){
    if(matriz[valor][i] == 1){
      soma += 1;
    }
  }
  return soma;
}

int contarAdjMatriz2(int matriz[][1000],int valor){
  int soma = 0;

  for (int i = 0; i < 1000; i++){
    if(matriz[valor][i] == 1){
      soma += 1;
    }
  }
  return soma;
}

bool verificaVerticeMatriz1(int matriz[][10],int valor){
  if( (matriz[valor][valor] == 1) || (matriz[valor][valor] == 0) ){
    return true;
  }
  return false;
}

bool verificaVerticeMatriz2(int matriz[][1000],int valor){
  if( (matriz[valor][valor] == 1) || (matriz[valor][valor] == 0) ){
    return true;
  }
  return false;
}

void criarArestaMatriz1(int matriz[][10],int vertice1,int vertice2){
  if(vertice1 != vertice2){
    if( (verificaVerticeMatriz1(matriz,vertice1) == true) && (verificaVerticeMatriz1(matriz,vertice2) == true) ){
      if( (contarAdjMatriz1(matriz,vertice1) < 3) && (contarAdjMatriz1(matriz,vertice2) < 3) ){
        matriz[vertice1][vertice2] = 1;
        matriz[vertice2][vertice1] = 1;  
      }  
    }      
  }
}

void criarArestaMatriz2(int matriz[][1000],int vertice1,int vertice2){
  if(vertice1 != vertice2){
    if(verificaVerticeMatriz2(matriz,vertice1) == true && verificaVerticeMatriz2(matriz,vertice2) == true){
      if(contarAdjMatriz2(matriz,vertice1) < 3 && contarAdjMatriz2(matriz,vertice2) < 3){
        matriz[vertice1][vertice2] = 1;
        matriz[vertice2][vertice1] = 1;
      }    
    }        
  }   
}

void imprimirMatriz1(int matriz[][10]){
  for (int i = 0 ; i < 10 ; i++){
    if( (matriz[i][i] == 1) || (matriz[i][i] == 0) ){
      printf("Matriz[%d]",i);
      for(int j = 0 ; j<10 ; j++){
        if(matriz[i][j] == 1){
          printf(" -> Matriz[%d]",j);
        }
      }
    printf("\n");
    }
  }
}

void imprimirMatriz2(int matriz[][1000]){
  for (int i = 0 ; i<1000 ; i++){
    if( (matriz[i][i] == 1) || (matriz[i][i] == 0) ){
      printf("Matriz[%d]",i);
      for(int j = 0 ; j<1000 ; j++){
        if(matriz[i][j] == 1){
          printf(" -> Matriz[%d]",j);
        }
      }
    printf("\n");
    }
  }
}

int main() {

  clock_t tempo;
  double soma = 0;
  srand(time(NULL));

  struct grafo *grafo1;
  int matriz1[10][10];
  
  grafo1 = criarGrafo(10);
  iniciarMatriz1(matriz1);

  int valor_aleatorio1;
  int valor_aleatorio2;
  
  for(int i = 0; i< 10; i++){
    valor_aleatorio1 = (rand() % 10);
    grafo1 = criarVertice(grafo1,valor_aleatorio1,0);
    criarVerticeMatriz1(matriz1,valor_aleatorio1);
  }

  for(int i = 0; i< 10; i++){
    valor_aleatorio1 = rand() % 4;
    for(int j = 0; j< valor_aleatorio1;j++){
      valor_aleatorio2 = rand() % 10;
      criarAresta(grafo1,i,valor_aleatorio2);
      criarArestaMatriz1(matriz1,grafo1->lista_vertice[i].valor,grafo1->lista_vertice[valor_aleatorio2].valor);
    }
  }

  FILE *file;
  file = fopen("lista_adjacencias.txt","w");
  struct vertice *aux;
  for(int i = 0; i<= grafo1->tamanho; i++){
    fprintf(file,"Grafo[%d] = %d",i,grafo1->lista_vertice[i].valor);
    aux = &grafo1->lista_vertice[i];
    while(aux->next != NULL){
      fprintf(file," -> %d ",aux->next->valor);
      aux = aux->next;
    }
    fprintf(file,"\n");
  }
  fclose(file);

  file = fopen("tabela_adjacencias.txt","w");
  for (int i = 0; i < 10; i++){
    if(matriz1[i][i] == 1 || matriz1[i][i] == 0){
      fprintf(file,"Matriz[%d]",i);
      for(int j = 0; j < 10; j++){
        if(matriz1[i][j] == 1){
          fprintf(file," -> Matriz[%d]",j);
        }
      }
    fprintf(file,"\n");
    }
  }
  fclose(file);

  grafo1->lista_vertice = realloc(grafo1->lista_vertice,1000*(sizeof(struct vertice)));
  
  int matriz2[1000][1000];
  iniciarMatriz2(matriz1,matriz2);

  //Armazenando vértices na lista de adjacências:

  int n_insercao = 99;
  int laco = 0;
  int limite = 20;
  int comeco = 10;

  tempo = clock();

  while(laco < n_insercao){
    for(int i = comeco; i< limite; i++){
      valor_aleatorio1 = (rand() % 1000);
      criarVertice(grafo1,valor_aleatorio1,1);
    }
    limite += 10; 
    comeco += 10; 
    laco++;
  }

  tempo = clock() - tempo;

  printf("\nTempo total para armazenamento dos vértices na lista de adjacências: %fs\n",((double)tempo)/CLOCKS_PER_SEC);
  printf("Tempo médio de armazenamento dos vértices na lista de adjacências: %fs\n\n",(((double)tempo)/CLOCKS_PER_SEC)/n_insercao);

  //Armazenando arestas na lista de adjacências:

  n_insercao = 99;
  laco = 0;
  limite = 20; 
  comeco = 10;

  tempo = clock();

  while(laco < n_insercao){
    for(int i = comeco; i< limite; i++){ 
      valor_aleatorio1 = rand() % 4;
      for(int j = 0; j< valor_aleatorio1;j++){
        valor_aleatorio2 = (rand() % 1000);
        criarAresta(grafo1,i,valor_aleatorio2);
      }
    }
    limite += 10; 
    comeco += 10; 
    laco++;
  } 

  tempo = clock() - tempo;

  printf("\nTempo total para armazenamento das arestas na lista de adjacências: %fs\n",((double)tempo)/CLOCKS_PER_SEC);
  printf("Tempo médio de armazenamento das arestas na lista de adjacências: %fs\n\n",(((double)tempo)/CLOCKS_PER_SEC)/n_insercao);

  //Armazenando vértices na tabela de adjacências:
   
  
  n_insercao = 99;
  laco = 0;
  limite = 20;
  comeco = 10;

  tempo = clock();
  
  while(laco < n_insercao){
    for(int i = comeco; i< limite; i++){ 
      valor_aleatorio1 = (rand() % 1000);
      criarVerticeMatriz2(matriz2,valor_aleatorio1);
    }
    limite += 10; 
    comeco += 10; 
    laco++;
  }

  tempo = clock() - tempo;

  printf("\nTempo total para armazenamento dos vértices na tabela de adjacências: %fs\n",((double)tempo)/CLOCKS_PER_SEC);
  printf("Tempo médio de armazenamento dos vértices na tabela de adjacências: %fs\n\n",(((double)tempo)/CLOCKS_PER_SEC)/n_insercao);

  //Armazenando arestas na tabela de adjacencias:

  n_insercao = 99;
  laco = 0;
  limite = 20; 
  comeco = 10;

  tempo = clock();

  while(laco < n_insercao){
    for(int i = comeco; i< limite; i++){ 
      valor_aleatorio1 = rand() % 4;
      for(int j = 0; j< valor_aleatorio1;j++){
        valor_aleatorio2 = (rand() % 1000);
        criarArestaMatriz2(matriz2,i,valor_aleatorio2);
      }
    }
    limite += 10; 
    comeco += 10; 
    laco++;
  }

  tempo = clock() - tempo;

  printf("\nTempo total para armazenamento das arestas na tabela de adjacências: %fs\n",((double)tempo)/CLOCKS_PER_SEC);
  printf("Tempo médio de armazenamento das arestas na tabela de adjacências: %fs\n\n",(((double)tempo)/CLOCKS_PER_SEC)/n_insercao);
  
  return 0;
}
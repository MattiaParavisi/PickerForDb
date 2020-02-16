/*
Copyright 2019 Mattia Paravisi
This is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This material is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this file.  If not, see <https://www.gnu.org/licenses/>.
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define STNDRD_LEN_ARR 5

struct coppia{
  int supermercato;
  int prodotto;
  struct coppia *next;
};

typedef struct coppia *Coppia_Lista;

int *leggi_da_file_prodotti(int *numret){
  FILE *ptr = fopen("input2", "r");
  int *return_array = malloc(STNDRD_LEN_ARR * sizeof(int));
  int inseriti = 0, check, inserito_attuale, len = STNDRD_LEN_ARR;
  for(;;){
    if(fscanf(ptr, "%d \n", &inserito_attuale)==EOF){
      fclose(ptr);
      *numret = inseriti;
      return return_array;
    }
    if(inseriti >= len){
      len += len;
      return_array = realloc(return_array, len * sizeof(int));
    }
    *(return_array+inseriti) = inserito_attuale;
    inseriti++;
  }
  fclose(ptr);
  return return_array;
}

int *leggi_da_file_supermercati(int *numret){
  FILE *ptr = fopen("input1", "r");
  int *return_array = malloc(STNDRD_LEN_ARR * sizeof(int));
  int inseriti = 0, check, inserito_attuale, len = STNDRD_LEN_ARR;
  for(;;){
    if(fscanf(ptr, "%d \n", &inserito_attuale)==EOF){
      fclose(ptr);
      *numret = inseriti;
      return return_array;
    }
    if(inseriti >= len){
      len += len;
      return_array = realloc(return_array, len * sizeof(int));
    }
    *(return_array+inseriti) = inserito_attuale;
    inseriti++;
  }
}

Coppia_Lista creacoppialista(){
  Coppia_Lista return_coppia_lista = malloc(sizeof(struct coppia));
  return_coppia_lista = NULL;
  return return_coppia_lista;
}

Coppia_Lista insert(Coppia_Lista testa, int supermarket_id, int product_id){
  Coppia_Lista nuovo_nodo = malloc(sizeof(struct coppia));
  nuovo_nodo -> supermercato = supermarket_id;
  nuovo_nodo -> prodotto = product_id;
  nuovo_nodo -> next = testa;
  testa = nuovo_nodo;
  return testa;
}

//1 se non c'e' -1 se c'e', RICORDATI DI PASSARE UNA COPIA DELLA TESTA
int check(Coppia_Lista testa, int supermercato, int prodotto){
  if(testa == NULL){
    return 1;
  }
  while(testa != NULL){
    if(testa -> supermercato == supermercato && testa -> prodotto == prodotto){
      return -1;
    }
    testa = testa -> next;
  }
  return 1;
}

void stampalistaformattata(Coppia_Lista lista){
  printf("INSERT INTO has_product VALUES \n");
  while(lista != NULL){
    if(lista->next == NULL){
      printf("('000%d','%d')", lista -> supermercato, lista -> prodotto);
      return;
    }
    printf("('000%d','%d'),", lista -> supermercato, lista -> prodotto);
    printf("\n"),
    lista =lista -> next;
  }
}

int main(void){
  int prodotto, supermercato, flag, num_associazioni, num_super, num_prod;
  srand(time(NULL));
  int *id_supermecati;
  int *id_prodotti;
  id_supermecati = leggi_da_file_supermercati(&num_super);
  id_prodotti = leggi_da_file_prodotti(&num_prod);
  Coppia_Lista mia_lista = creacoppialista();
  Coppia_Lista backup_mia_lista = mia_lista;
  printf("quante associazioni vuoi avere ? \n");
  scanf("%d", &num_associazioni);
  if(num_associazioni==0){
    return 0;
  }
  if(num_associazioni <= num_super*num_prod){
    for(int i = 0; i < num_associazioni; i++){
      prodotto = id_prodotti[(rand() % 16)];
      supermercato = id_supermecati[(rand() % 10)];
      backup_mia_lista = mia_lista;
      flag = check(backup_mia_lista,supermercato,prodotto);
      if(flag==1){
        mia_lista = insert(mia_lista, supermercato, prodotto);
      }else{
        i--;
        continue;
      }
    }
  }
  stampalistaformattata(mia_lista);
  printf("\n");
}

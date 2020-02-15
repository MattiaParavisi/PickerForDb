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

struct coppia{
  int supermercato;
  int prodotto;
  struct coppia *next;
};

typedef struct coppia *Coppia_Lista;

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
  int prodotto, supermercato, flag;
  srand(time(NULL));
  int id_supermecati[10] = {1, 2, 9, 5, 0, 7, 4, 3, 8, 6};
  int id_prodotti[16] = {123456789, 123456788, 354321563, 123456787, 354321553, 123555555, 556789432, 345321456, 256273890, 123456767, 354301553,  123555455, 550789432, 345341456, 256263890, 230818567};
  Coppia_Lista mia_lista = creacoppialista();
  Coppia_Lista backup_mia_lista = mia_lista;
  for(int i = 0; i < 30; i++){
    prodotto = id_prodotti[(rand() % 16)];
    supermercato = id_supermecati[(rand() % 10)];
    backup_mia_lista = mia_lista;
    flag = check(backup_mia_lista,supermercato,prodotto);
    if(flag==1){
      mia_lista = insert(mia_lista, supermercato, prodotto);
    }else{
      i++;
      continue;
    }
  }
  stampalistaformattata(mia_lista);
  printf("\n");
}

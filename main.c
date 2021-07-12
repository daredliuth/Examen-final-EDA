/**
 * \ Examen Final
 * \author Eliuth Montiel Navarrete
 * \date 07 de junio de 2019
 */

#include <stdio.h>
#include "Queue.h"
#include "Stack.h"

/** \fn void Imprime(Object objeto)
 * \brief Imprime un objeto.
 * \param objeto Es un object el cual se va a imprimir. */
void Imprime(Object objeto){
  printf("[peso:%d,valor:%d]\n",Object_GetWeight(&objeto),Object_GetValue(&objeto));
}
/** \fn Stack MochilaBTFacil(Objectptr n, int peso_max,int acum_peso, Queue objetos, Stack mochila)
 * \param n Un apuntador a objetos.
 * \param peso_max El peso máximo.
 * \param acum_peso El peso acumulado.
 * \param objetos Una cola de candidatos.
 * \param mochila una pila con el conjunto solución.
 * \return Una pila con la solución.*/
Stack MochilaBTFacil(Objectptr n, int peso_max,int acum_peso, Queue objetos, Stack mochila){
  static int contador = 0;
  static Stack posible_solucion;

  while(!Queue_IsEmpty(&objetos)){
    *n = Queue_Peek(&objetos);

    if(Object_GetWeight(n) + acum_peso <= peso_max){
      printf("Registrando al candidato [%d,%d]\n",Object_GetWeight(n),Object_GetValue(n));
      Stack_Push(&mochila,Queue_Peek(&objetos));
      acum_peso += Object_GetWeight(n);

      if(acum_peso < peso_max){
        ++contador;
        printf("Entrando al nivel %d\n",contador);
        posible_solucion = MochilaBTFacil(n,peso_max,acum_peso,objetos,mochila);


        if(Stack_IsEmpty(&posible_solucion)){
          printf("Cancelando el registro del candidato [%d,%d]\n",Object_GetWeight(n),Object_GetValue(n));
          acum_peso -= Object_GetWeight(n);
          Stack_Pop(&mochila,n);
          printf("saliendo del nivel %d\n",contador);
          --contador;
        }

      }
    }
    else{
      Queue_Remove(&objetos,n);
      return mochila;
    }
  }
  return mochila;
}


int main(){
  int peso;
  Objectptr obj1 = Object_New(10,15);
  Objectptr obj2 = Object_New(7,12);
  Objectptr obj3 = Object_New(1,11);
  Objectptr auxiliar = Object_New(0,0);
  Queue* cola = Queue_New();
  Stack* solucion = Stack_New();
  Stack* mochila = Stack_New();

  printf("Introduzca el peso maximo por favor: -> ");
  scanf("%d",&peso);

  Queue_Insert(cola,*obj1);
  Queue_Insert(cola,*obj2);
  Queue_Insert(cola,*obj3);

  *solucion = MochilaBTFacil(auxiliar,peso,0,*cola,*mochila);

  if(solucion){
    printf("Se encontró una solución\n");
    List_ForEach(solucion->stack,Imprime);
  }else{
    printf("No se encontró ninguna solución");
  }

  Object_Delete(obj1);
  Object_Delete(obj2);
  Object_Delete(obj3);
  Object_Delete(auxiliar);
  Stack_Delete(solucion);
  Stack_Delete(mochila);
  Queue_Delete(cola);
}

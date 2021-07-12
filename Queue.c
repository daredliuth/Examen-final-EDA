#include "Queue.h"

/** \fn Queue* Queue_New()
 * \brief Crea una nueva cola. 
 * \return Un apuntador a la cola creada. */
Queue* Queue_New(){
  Queue * q = (Queue*) malloc(sizeof(Queue));

  if(NULL!=q){
      q->queue = List_New();

      if (NULL == q->queue){
          free(q);
          q = NULL;
      }
      else{
          q->front = 0;
          q->back = 0;
          q->len = 0;
      }
  }
  return q;
}

/** \fn void Queue_Delete(Queue* this)
 * \brief Elimina una cola.
 * \param this Es un apuntador a la cola en la que se realizará la operación. */
void Queue_Delete(Queue* this){
  assert(this);

  List_Delete(this->queue);
  free(this);
}

/** \fn bool Queue_Is_Empty(Queue* this)
 * \brief Verifica si la cola está vacía.
 * \param this Es un apuntador a la cola en la que se realizará la operación. 
 * \return Un true si la cola está vacía. */
bool Queue_IsEmpty(Queue* this){
  return(this->len == 0);
}

/** \fn void Queue_Insert(Queue* this, Object _data)
 * \brief Inserta un objeto en la cola.
 * \param this Es un apuntador a la cola en la que se realizará la operación. */
void Queue_Insert(Queue* this, Object _data){
  assert(this);

  List_InsertBack(this->queue, _data);
  this->queue->cursor = this->queue->first;
  ++this->back;
  ++this->len;
}

/** \fn void Queue_Remove(Queue* this, Objectptr _data_back)
 * \brief Extrae un objeto de la cola.
 * \param this Es un apuntador a la cola en la que se realizará la operación.
 * \param _data_back Es un apuntador en el cual se guardará el valor removido */
void Queue_Remove(Queue* this,Objectptr _data_back){
  assert( !Queue_IsEmpty(this) );

  List_RemoveFront(this->queue, _data_back);
  this->queue->cursor = this->queue->first;
  ++this->front;
  --this->len;
}

/** \fn Object Queue_Peek(Queue* this,)
 * \brief Devuelve una copia del elemento en el front de la cola.
 * \param this Es un apuntador a la cola en la que se realizará la operación.
 * \return Devuelve el objeto que se copió.*/
Object Queue_Peek(Queue* this){
  assert( !Queue_IsEmpty(this) );
  this->queue->cursor = this->queue->first;
  Object copia;
  copia = List_Get(this->queue);
  return copia;
}

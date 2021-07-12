#include "Stack.h"

/** \fn Stack* Stack_New()
 * \brief Crea una nueva pila. 
 * \return Un apuntador a la pila creada. */
Stack*  Stack_New(){
  Stack* s = (Stack*) malloc( sizeof(Stack) );

  if (NULL != s){
    s->stack = List_New();

    if(NULL == s->stack){
      free(s);
      s = NULL;
    }else{
      s->top = 0;
    }
  }
  return s;
}

/** \fn void Stack_Delete( Stack* this)
 * \brief Elimina una pila.
 * \param this Es un apuntador a la pila en la cual se realizará la operación. */
void    Stack_Delete( Stack* this ){
  assert(this);

  free(this->stack);
  free(this);
}

/** \fn bool Stack_IsEmpty( Stack* this )
 * \brief Verifica si la pila está vacía.
 * \param this Es un apuntador a la pila en la que se realizará la operación.
 * \return Un apuntador a la pila creada. */
bool    Stack_IsEmpty( Stack* this ){
  return(this->top == 0);
}

/** \fn void Stack_Push(Stack* this, Object _data)
 * \brief Inserta un objeto en la pila. 
 * \param this Es un apuntador a la pila en la que se realizará la operación.
 * \param _data Es el objeto que se insertará en la pila. */
void    Stack_Push( Stack* this, Object _data ){
  assert(this);

  if(Stack_IsEmpty(this)){
    List_InsertBack(this->stack, _data);
    List_CursorFirst(this->stack);
    ++this->top;
  }else{
    List_InsertBack(this->stack, _data);
    this->stack->cursor = this->stack->last;
    ++this->top;
  }
}

/** \fn void Stack_Pop(Stack* this, Objectptr _data_back)
 * \brief Extrae un objeto de la pila. 
 * \param this Es un apuntador a la pila en la que se realizará la operación.
 * \param _data_back Es un apuntador que guardará el valor retirado de la pila. */
void     Stack_Pop( Stack* this, Objectptr _data_back ){
  assert(this->top > 0);
  List_RemoveBack(this->stack, _data_back);
  List_CursorLast(this->stack);
  --this->top;
}

/** \fn void Stack_Peek(Stack* this, Objectptr _data_back)
 * \brief Crea una copia del elemento en el top de la pila. 
 * \param this Es un apuntador a la pila en la que se realizará la operación.
 * \param _data_back Es un apuntador que guardará el valor copiado de la pila. */
void     Stack_Peek( Stack* this, Objectptr _data_back ){
  assert(this->top > 0);
  *_data_back = List_Get(this->stack);
}

/** \fn Stack Stack_Dup(Stack* this)
 * \brief Copia una pila. 
 * \param this Es un apuntador a la pila en la que se realizará la operación.
 * \return Devuelve una copia de la pila*/
Stack Stack_Dup(Stack* this){
  assert(this);
  Stack* it = Stack_New();
  Objectptr copia = Object_New(0,0);
  this->stack->cursor = this->stack->first;

  for(size_t i = 0;i < this->stack->len;++i){
    Stack_Peek(this, copia);
    Stack_Push(it,*copia);
    List_CursorNext(this->stack);
  }
  Object_Delete(copia);
  it->stack->cursor = it->stack->last;
  this->stack->cursor = this->stack->last;
  return *it;
}

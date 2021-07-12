#include "List.h"

/** \fn Static NodePtr newNode(Item _data)
 * \brief Crea un un nodo.
 * \param _data El Item que se insertara en el nodo.
 * \return Devuelve el pointer al nodo que se creó. */
static NodePtr newNode(Object _data){
  NodePtr n = (NodePtr) malloc ( sizeof(Node) );
  if (n){
    n->data = _data;
    n->next = NULL;
    n->prev = NULL;
  }
  return n;
}

/** \fn Static void reset(CDLL* this)
 * \brief Resetea la lista.
 * \param this El apuntador a la CDLL que se reseteará. */
static void reset (List* this){
  this->first = this->last = this->cursor = NULL;
  this->len = 0;
}

/** \fn List* List_New()
 * \brief Crea una nueva List.
 * \return Devuelve el pointer a la lista que se creó. */
List* List_New(){
  List* lista = (List*) malloc( sizeof(List) );
  if (lista){
    reset (lista);
  }
  return lista;
}

/** \fn void List_Delete(List* this)
 * \brief Borra una List.
 * \param this El apuntador a la lista que se borrará. */
void List_Delete(List* this){
  assert(this);
  while(this->len != 0){
    if(this->len == 1){
      free(this->first);
    }else{
      NodePtr tmp = this->first->next;
      free( this->first );
      this->first = tmp;
      this->last->next = this->first;
      this->first->prev = this->last;
    }
    --this->len;
  }
  reset(this);
}

/** \fn bool List_InsertBack(List* this,Object _data)
 * \brief Inserta un elemento en el "Back" de la List.
 * \param this El apuntador a la List en la que se va a realizar la operación.
 * \param _data El Object que se insertará en la List.
 * \return Devuelve true si se logró la inserción. */
bool List_InsertBack(List* this, Object _data){
  assert( this );

	bool done = false;

  NodePtr n = newNode( _data );
	if( n ){
    done = true;

		if( List_IsEmpty( this ) ){
      this->first = this->last = n;
			this->len = 1;
		} else {
			this->last->next = n;
			n->prev = this->last;

      n->next = this->first;
      this->first->prev = n;

      this->last = n;
			++this->len;
		}
	}
	return done;
}

/** \fn bool List_InsertFront(List* this,Object _data)
 * \brief Inserta un elemento en el "Front" de la List.
 * \param this El apuntador a la List en la que se va a realizar la operación.
 * \param _data El Object que se insertará en la List.
 * \return Devuelve true si se logró la inserción. */
bool List_InsertFront(List* this, Object _data){
  assert( this );

	bool done = false;

	NodePtr n = newNode( _data );
	if( n ){
		done = true;

		if( List_IsEmpty( this ) ){
			this->first = this->last = n;
      n->next = n->prev = n;
			this->len = 1;
		} else {
			n->next = this->first;
			this->first->prev = n;

      n->prev = this->last;
      this->last->next = n;

			this->first = n;
			++this->len;
		}
	}
	return done;
}

/** \fn bool List_RemoveBack(List* this,Object* _data_back)
 * \brief Remueve un elemento en el "Back" de la List.
 * \param this El apuntador a la List en la que se va a realizar la operación.
 * \param _data_back El apuntador en el cual se guardará el objeto retirado.
 * \return Devuelve true si se logró la extracción. */
bool List_RemoveBack(List* this, Object* _data_back){
  assert( this );

bool done = false;

if( !List_IsEmpty( this ) ){
  done = true;
  *_data_back = this->last->data;
  NodePtr tmp = this->last->prev;
  free( this->last );
  this->last = tmp;

  if( this->first != this->last || this->len == 2 ){
    this->last->next = this->first;
    this->first->prev = this->last;
    --this->len;
  } else {
    reset( this );
  }
}
return done;
}

/** \fn bool List_RemoveFront(List* this,Object* _data_back)
 * \brief Remueve un elemento en el "Front" de la List.
 * \param this El apuntador a la List en la que se va a realizar la operación.
 * \param _data_back El apuntador en el cual se guardará el objeto retirado..
 * \return Devuelve true si se logró la extracción. */
bool List_RemoveFront(List* this, Object* _data_back){
  assert( this );

	bool done = false;

	if( !List_IsEmpty( this ) ){
		done = true;
		*_data_back = this->first->data;
		NodePtr tmp = this->first->next;
		free( this->first );
		this->first = tmp;

		if( this->last != this->first || this->len == 2 ){
			this->first->prev = this->last;
      this->last->next = this->first;
			--this->len;
		}
    else {
      reset(this);
    }
	}
	return done;
}

/** \fn bool List_IsEmpty(List* this)
 * \brief Verifica si la List está vacía.
 * \param this El apuntador a la List en la que se va a realizar la operación.
 * \return Devuelve true si la List está vacía.*/
bool List_IsEmpty(List* this){
  assert(this);
  return this->first == NULL;
}

Object List_Get(List* this){
  assert(this->cursor);
  Object copia;
  if(this->cursor != NULL){
    (&copia)->valor = Object_GetValue(&this->cursor->data);
    (&copia)->peso = Object_GetWeight(&this->cursor->data);
  }
  return copia;
}

/** \fn void List_ForEach(List* this, void(*impfun)(Object))
 * \brief Verifica si la List está vacía.
 * \param this El apuntador a la List en la que se va a realizar la operación. 
 * \param void(*impfun)(object) Una funcion que requiere un Object*/
void List_ForEach(List* this, void(*impfun)(Object) ){
  assert( this );
  size_t i=0;
  for( NodePtr it = this->first; i<this->len ; it = it->next ){
    impfun( it->data );
    ++i;
  }
}

/** \fn void List_CursorNext(List* this)
 * \brief Mueve el cursor al siguiente elemento de la List.
 * \param this El apuntador a la List en la que se va a realizar la operación.
 *
 *Para romper la circularidad de la CDLL si el cursor se encuentra en el último nodo este no se moverá*/
void List_CursorNext(List* this){
  assert( this );
	if( this->cursor != this->last ){
		this->cursor = this->cursor->next;
	}
}

/** \fn void List_CursorLast(List* this)
 * \brief Mueve el cursor al último elemento de la List.
 * \param this El apuntador a la List en la que se va a realizar la operación. */
void List_CursorLast(List* this){
  assert( this );
	if( this->cursor != NULL ){
		this->cursor = this->last;
	}
}

/** \fn void List_CursorFirst(List* this)
 * \brief Mueve el cursor al primer elemento de la List.
 * \param this El apuntador a la List en la que se va a realizar la operación. */
void List_CursorFirst(List* this){
  assert( this );
  if( this->cursor != NULL ){
    this->cursor = this->first;
  }
}

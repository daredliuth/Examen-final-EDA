#include "CDLL.h"

/** \fn Static NodePtr newNode(Item _data)
 * \brief Crea un un nodo.
 * \param _data El Item que se insertara en el nodo.
 * \return Devuelve el pointer al nodo que se creó. */
static NodePtr newNode( Item _data )
{
	NodePtr n = (NodePtr) malloc( sizeof( Node ) );
	if( n ){
		n->data = _data;
		n->next = NULL;
		n->prev = NULL;
	}
	return n;
}

/** \fn Static void reset(CDLL* this)
 * \brief Resetea la lista.
 * \param this El apuntador a la CDLL que se reseteará. */
static void reset( CDLL* this )
{
	this->first = this->last = this->cursor = NULL;
  this->len = 0;
}

/** \fn CDLL* CDLL_New()
 * \brief Crea una nueva CDLL.
 * \return Devuelve el pointer a la CDLL que se creó. */
CDLL* CDLL_New()
{
	CDLL* list = (CDLL*) malloc( sizeof( CDLL ) );
	if( list ){
		reset( list );
	}
	return list;
}

/** \fn void CDLL_Delete(CDLL* this)
 * \brief Borra una CDLL.
 * \param this El apuntador a la CDLL que se borrará. */
void CDLL_Delete( CDLL* this )
{
	if( this ){
		CDLL_MakeEmpty( this );
		free( this );
	}
}

/** \fn bool CDLL_InsertBack(CDLL* this,Item _data)
 * \brief Inserta un elemento en el "Back" de la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data El Item que se insertará en la CDLL.
 * \return Devuelve true si se logró la inserción.*/
bool CDLL_InsertBack( CDLL* this, Item _data )
{
	assert( this );

	bool done = false;

	NodePtr n = newNode( _data );
	if( n ){
		done = true;

		if( CDLL_IsEmpty( this ) ){
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

/** \fn bool CDLL_InsertFront(CDLL* this,Item _data)
 * \brief Inserta un elemento en el "Front" de la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data El Item que se insertará en la CDLL.
 * \return Devuelve true si se logró la inserción.*/
bool CDLL_InsertFront( CDLL* this, Item _data )
{
	assert( this );

	bool done = false;

	NodePtr n = newNode( _data );
	if( n ){
		done = true;

		if( CDLL_IsEmpty( this ) ){
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

/** \fn bool CDLL_InsertAfter(CDLL* this,Item _data)
 * \brief Inserta un elemento a la derecha del cursor.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data El Item que se insertará en la CDLL.
 * \return Devuelve true si se logró la inserción.*/
bool CDLL_InsertAfter( CDLL* this, Item _data )
{
	assert( this );

	bool done = false;

	if( CDLL_IsEmpty( this ) || this->cursor == this->last ){
		done = CDLL_InsertBack( this, _data );
	} else {
		NodePtr n = newNode( _data );
		if( n ){
			done = true;

			n->next = this->cursor->next;
			this->cursor->next->prev = n;
			this->cursor->next = n;
			n->prev = this->cursor;
			++this->len;
		}
	}
	return done;
}

/** \fn bool CDLL_InsertBefore(CDLL* this,Item _data)
 * \brief Inserta un elemento a la izquierda del cursor.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data El Item que se insertará en la CDLL.
 * \return Devuelve true si se logró la inserción.*/
bool CDLL_InsertBefore( CDLL* this, Item _data ){
  assert( this );

	bool done = false;

	if( CDLL_IsEmpty( this ) || this->cursor == this->first ){
		done = CDLL_InsertFront( this, _data );
	} else {
		NodePtr n = newNode( _data );
		if( n ){
			done = true;

			n->prev = this->cursor->prev;
      this->cursor->prev->next = n;
			this->cursor->prev = n;

			n->next = this->cursor;
			++this->len;
		}
	}
	return done;
}

/** \fn bool CDLL_Remove(CDLL* this,ItemPtr _data_back)
 * \brief Remueve el elemento al que apunta el cursor.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data_back El apuntador a Item que se guardará el Item removido.
 * \return Devuelve true si se logró la extracción.*/
bool CDLL_Remove( CDLL* this, ItemPtr _data_back )
{
	assert( this );

	bool done = false;

	if( !CDLL_IsEmpty( this ) && NULL != this->cursor ){
		done = true;

		*_data_back = this->cursor->data;

		NodePtr left = this->cursor->prev;
		NodePtr right = this->cursor->next;
		free( this->cursor );

		if( left == right ){
			reset( this );
		}
    else if(this->cursor == this->first){
      this->cursor = left;
      this->first = right;
      this->cursor->next = right;
      right->prev = this->cursor;
      --this->len;

    }
    else if(this->cursor == this->last){
      this->cursor = left;
      this->last = left;
			this->cursor->next = right;
			right->prev = this->cursor;
			--this->len;
    }
    else {
			this->cursor = left;
			this->cursor->next = right;
			right->prev = this->cursor;
			--this->len;
		}
	}
	return done;
}

/** \fn bool CDLL_RemoveFront(CDLL* this,ItemPtr _data_back)
 * \brief Remueve el elemento del "Front" de la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data_back El apuntador a Item que se guardará el Item removido.
 * \return Devuelve true si se logró la extracción.*/
bool CDLL_RemoveFront( CDLL* this, ItemPtr _data_back )
{
	assert( this );

	bool done = false;

	if( !CDLL_IsEmpty( this ) ){
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

/** \fn bool CDLL_RemoveBack(CDLL* this,ItemPtr _data_back)
 * \brief Remueve el elemento del "Back" de la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data_back El apuntador a Item que se guardará el Item removido.
 * \return Devuelve true si se logró la extracción.*/
bool CDLL_RemoveBack( CDLL* this, ItemPtr _data_back ){
    assert( this );

	bool done = false;

	if( !CDLL_IsEmpty( this ) ){
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

/** \fn bool CDLL_Remove(CDLL* this,ItemPtr _data_back)
 * \brief Remueve el elemento a la derecha del cursor.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data_back El apuntador a Item que se guardará el Item removido.
 * \return Devuelve true si se logró la extracción.*/
bool CDLL_RemoveAfter( CDLL* this, ItemPtr _data_back ){
  assert( this );
  bool done = false;

  if(!CDLL_IsEmpty(this)){
    done = true;
    *_data_back = this->cursor->next->data;
    NodePtr tmp = this->cursor->next->next;

    if(tmp == this->first && tmp != this->cursor){
      this->cursor->next = tmp;
      tmp->prev = this->cursor;
      free(this->last);
      this->last = this->cursor;
      -- this->len;
    }else if(tmp == this->first->next && tmp != this->cursor){
      this->cursor->next = tmp;
      tmp->prev = this->cursor;
      free(this->first);
      this->first = tmp;
      --this->len;
    }else if(tmp == this->cursor){
      free(this->cursor->next);
      this->last = this->first = this->cursor->next = this->cursor->prev = this->cursor;
      --this->len;
    }else if(this->last == this->first){
      reset(this);
    }else{
      free(this->cursor->next);
      this->cursor->next = tmp;
      tmp->prev = this->cursor;
      --this->len;
    }
  }
  return done;
}

/** \fn bool CDLL_RemoveBefore(CDLL* this,ItemPtr _data_back)
 * \brief Remueve el elemento a la izquierda del cursor.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data_back El apuntador a Item que se guardará el Item removido.
 * \return Devuelve true si se logró la extracción.*/
bool CDLL_RemoveBefore( CDLL* this, ItemPtr _data_back ){
    assert( this );

	bool done = false;

	if( !CDLL_IsEmpty( this ) ){
		done = true;
		*_data_back = this->cursor->next->data;
		NodePtr tmp = this->cursor->prev->prev;

    if(tmp == this->last && tmp != this->cursor ){
      this->cursor->prev = tmp;
      tmp->next = this->cursor;
      free(this->first);
      this->first = this->cursor;
      --this->len;
    }else if(tmp == this->last->prev && tmp != this->cursor){
      this->cursor->prev = tmp;
      tmp->next = this->cursor;
      free(this->last);
      this->last = this->cursor->prev;
      --this->len;
    }else if(tmp == this->cursor){
      free(this->cursor->prev);
      this->last = this->first = this->cursor->next = this->cursor->prev = this->cursor;
      --this->len;
    }else if(this->first == this->last){
      reset(this);
    }else{
      free(this->cursor->prev);
      this->cursor->prev = tmp;
      tmp->next = this->cursor;
      --this->len;
    }
  }
  return done;
}

/** \fn size_t CDLL_Len(CDLL* this)
 * \brief Obtiene la longitud de la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \return Devuelve un entero que es la longitud de la CDLL.*/
size_t CDLL_Len( CDLL* this )
{
	assert( this );
	return this->len;
}

/** \fn bool CDLL_IsEmpty(CDLL* this)
 * \brief Verifica si la CDLL esta vacía.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \return Devuelve true si la CDLL está vacía.*/
bool CDLL_IsEmpty( CDLL* this )
{
	assert( this );
	return this->first == NULL;
}

/** \fn void CDLL_MakeEmpty(CDLL* this)
 * \brief Vacía la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación. */
void CDLL_MakeEmpty( CDLL* this )
{
	assert( this );
	while( this->len != 0){
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
	reset( this );
}

/** \fn bool CDLL_Peek(CDLL* this, ItemPtr _data_back)
 * \brief Guarda el Item al que apunta el cursor sin removerlo.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _data_back El apuntador a Item en el cual se guardara el Item.
 * \return Devuelve true si se realizó la operación.*/
bool CDLL_Peek( CDLL* this, ItemPtr _data_back )
{
    assert(this);
    if(NULL!=this->cursor){
        *_data_back=this->cursor->data;
        return true;
    }
    else{
        return false;
    }
}

/** \fn void CDLL_CursorFirst(CDLL* this)
 * \brief Mueve el cursor al primer elemento de la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación. */
void CDLL_CursorFirst( CDLL* this )
{
	assert( this );
	if( this->cursor != NULL ){
		this->cursor = this->first;
	}
}

/** \fn void CDLL_CursorLast(CDLL* this)
 * \brief Mueve el cursor al último elemento de la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación. */
void CDLL_CursorLast( CDLL* this )
{
	assert( this );
	if( this->cursor != NULL ){
		this->cursor = this->last;
	}
}

/** \fn void CDLL_CursorNext(CDLL* this)
 * \brief Mueve el cursor al siguiente elemento de la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación. */
void CDLL_CursorNext( CDLL* this )
{
	assert( this );
	if( this->cursor != NULL ){
		this->cursor = this->cursor->next;
	}
}

/** \fn void CDLL_CursorPrev(CDLL* this)
 * \brief Mueve el cursor al elemento anterior de la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación. */
void CDLL_CursorPrev( CDLL* this )
{
	assert( this );
	if( this->cursor != NULL ){
		this->cursor = this->cursor->prev;
	}
}

/** \fn bool CDLL_FindIf(CDLL* this, Item _key, bool (*cmp) (Item,Item))
 * \brief Verifica si un Item se encuentra en la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _key El Item que se busca.
 * \param bool (*cmp) (Item,Item) Una función que requiere dos Items y devuelve un bool.
 * \return Devuelve true si se encontró el Item.*/
bool CDLL_FindIf( CDLL* this, Item _key, bool (*cmp) (Item,Item) )
{
	assert( this );

	bool found = false;

	for( NodePtr it = this->first; it != it->next; it = it->next ){
		if( cmp(_key, it->data) ){
			found = true;
			break;
		}
	}
	return found;
}

/** \fn bool CDLL_Search(CDLL* this, Item _key)
 * \brief Verifica si un Item se encuentra en la CDLL si está coloca el cursor en el.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param _key El Item que se busca.
 * \return Devuelve true si se encontró el Item.*/
bool CDLL_Search( CDLL* this, Item _key )
{
  assert(this);
  bool found = false;

  if(!CDLL_IsEmpty(this)){
    Node* it = this->first;
    for (size_t i = 0;i<this->len;++i){
      if(Object_GetWeight(&_key) == Object_GetWeight(&it->data) || Object_GetValue(&_key) == Object_GetValue( &it->data) ){
        found=true;
        this->cursor = it;
        break;
      }
      it = it->next;
    }
  }
  return found;
}


/** \fn void CDLL_Traverse(CDLL* this, void (*pfun) (Item))
 * \brief Imprime toda la CDLL.
 * \param this El apuntador a la CDLL en la que se va a realizar la operación.
 * \param void (*pfun) (Item) Una función que requiere un Item. */
void CDLL_Traverse( CDLL* this, void (*pfun)(Item) )
{
  assert( this );
  size_t i=0;
  for( NodePtr it = this->first; i<this->len ; it = it->next ){
		pfun( it->data );
    ++i;
	}
}

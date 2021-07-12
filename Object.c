#include "Object.h"

/** \fn Objectptr Object_New(int weight, int value)
 * \brief Crea un objeto.
 * \param weight El peso del objeto.
 * \param value El valor del objeto.
 * \return Devuelve un apuntador al objeto creado.*/
Objectptr Object_New( int weight, int value ){
  Objectptr p = (Objectptr) malloc(sizeof(Object));
  assert(p);

  p->peso = weight;
  p->valor = value;

  return p;
}

/** \fn void Object_Delete(Objectptr p)
 * \brief Elimina un objeto.
 * \param p El apuntador al objeto que se eliminará. */
void Object_Delete(Objectptr p){
  free(p);
}

/** \fn void Object_SetWeight( int weight, Objectptr p)
 * \brief Establece el peso de un objeto.
 * \param weight El peso que se le establecera al objeto
 * \param p El apuntador al objeto. */
void Object_SetWeight( int weight, Objectptr p){
  p->peso = weight;
}

/** \fn int Object_GetWeight(Objectptr p)
 * \brief obtiene el peso de un objeto.
 * \param p El apuntador al objeto. 
 * \return El peso del objeto */
int Object_GetWeight(Objectptr p){
  return p->peso;
}

/** \fn void Object_SetValue( int value, Objectptr p)
 * \brief Establece el valor de un objeto.
 * \param value El valor que se le establecera al objeto
 * \param p El apuntador al objeto. */
void Object_SetValue( int value, Objectptr p ){
  p->valor = value;
}

/** \fn int Object_GetValue(Objectptr p)
 * \brief obtiene el peso de un objeto.
 * \param p El apuntador al objeto. 
 * \return El valor del objeto */
int Object_GetValue(Objectptr p){
  return p->valor;
}

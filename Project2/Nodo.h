#pragma once
#ifndef Nodo_H
#define Nodo_H
#include "contenedor.h"
class Nodo {
   friend class Lista;
public:
   Nodo( Contenedor &info ) : data( info ), sigPtr( NULL ) { }
   Contenedor getData() { 
   return data; }
private:
   Contenedor data;
   Nodo *sigPtr;
}; 
#endif
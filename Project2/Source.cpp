#pragma once
#ifndef Source_CPP
#define Source_CPP
#include "Header.h"
void main(){
	Lista Bodega;
	for(int i=0; i<5; i++){
		string tipo="def";
		float temp=0-i;
		Bodega.nuevoContenedor(3000, tipo, temp);
	}
	Bodega.mostrarInventario();
	Bodega.sacarDeBodega(5000, "def");
	Bodega.mostrarInventario();
	for(int i=0; i<5; i++){
		string tipo="def";
		float temp=0-i;
		Bodega.nuevoContenedor(3000, tipo, temp);
	}
	Bodega.mostrarInventario();
	Bodega.sacarDeBodega(5000, "def");
	Bodega.mostrarInventario();
	system("pause");
}
#endif
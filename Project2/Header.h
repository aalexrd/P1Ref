#pragma once
#ifndef Header_H
#define Header_H
#include "Nodo.h"
#include <iostream>
using namespace std;
class Lista{
private:
	Nodo *primerPtr;
	Nodo *ultimoPtr;
	Nodo *obtNuevoNodo(Contenedor &valor ){
	   return new Nodo( valor ); }
	int contenedores;
	string tipos[10];
	int cantidades[10];
public:
	Lista() : primerPtr( 0 ), ultimoPtr( 0 ), contenedores(0){}
   ~Lista(){
	   if ( !primerPtr==0 ){    //si no esta vacio
			cout << "Destruyendo nodos ...\n";
			Nodo *actualPtr = primerPtr;
			Nodo *tempPtr;
			while ( actualPtr != 0 ){  
				tempPtr = actualPtr;
				cout<<"Se elimino un contenedor "<<actualPtr->data.getTipo()<<endl;
				actualPtr = actualPtr->sigPtr;
				delete tempPtr;
			}
		}
		cout << "Todos los nodos destruidos\n\n";
   }
   void mostrarInventario(){
	   string tipo[10]; //vector para guardar los tipos de cada contenedor en la bodega
	   int cant[10]; //vector para guardar cantidad de los refrescos de cada tipo en la bodega
	   int i=0;
	   if (primerPtr == 0){
		   cout << "La bodega esta vacia\n\n";
		   return; }
	   Nodo *actualPtr = primerPtr;
	   cout << "Inventario: \n";
	   for(actualPtr = primerPtr; actualPtr!=0; actualPtr=actualPtr->sigPtr){ //pasar datos a vectores
		   tipo[i]=actualPtr->data.getTipo();
		   cant[i]=actualPtr->data.getCant();
		   i++;
	   }
	   for(i=0; i<10; i++){ //sumar todos los contenedores de igual tipo
		   for(int j=i+1; j<10; j++){
			   if(tipo[i]==tipo[j]&&(cant[i]!=NULL&&tipo[j]!="")){
				   cant[i]+=cant[j];
				   tipo[j]="";
				   cant[j]=NULL;
			   }
		   }
	   }
	   for(i=0; i<10; i++){ //imprime valores finales
		   if(tipo[i]!=""&&cant[i]!=NULL){
			   cout<<"Hay "<<cant[i]<<" de "<<tipo[i]<<"."<<endl;
			   tipos[i]=tipo[i]; //para usarse en otro metodo
			   cantidades[i]=cant[i]; //para usarse en otro metodo
		   }
	   }
   }
   void sacarDeBodega(int cant, string tipo){
	   int i=0;
	   Nodo *vector[10]; //vector de nodos(contenedores)
	   Nodo *actualPtr = primerPtr;
	   for(i=0; i<10; i++){ //se asegura de que en la bodega haiga la cantidad pedida
		   if(tipo==tipos[i])
			   if(cant>cantidades[i]){
				   cout<<"No hay suficientes refrescos"<<endl;
				   return; }
	   }
	   i=0;
	   for(actualPtr = primerPtr; actualPtr!=0; actualPtr=actualPtr->sigPtr){ //pasar contenedor(nodo) a vector
		   vector[i]=actualPtr;
		   i++;
	   }
	   int min;
	   for(i=0; i<contenedores&&vector[i]!=NULL; i++){ //ordenar vector por temperatura
		   min=i;
		   for(int j=i+1; j<contenedores&&vector[j]!=NULL; j++){
			   if(vector[j]->data.getTemp()<vector[i]->data.getTemp())
				   min=j;
		   }
		   Contenedor aux=vector[i]->data;
		   vector[i]->data=vector[min]->data;
		   vector[min]->data=aux;
	   }
	   for(i=0; i<contenedores&&vector[i]!=NULL; i++){
		   if(tipo==vector[i]->data.getTipo()){ //si encuentra un nodo con el contenedor del tipo que queremos....
			   if(cant==0)
				   return;
			   if(cant<=vector[i]->data.getCant()){ //si la cantidad que sacamos es igual o menor a la que hay en el contenedor
				   vector[i]->data.setCant(vector[i]->data.getCant()-cant); //reste la cantidad al contenedor
				   cout<<"Tiene que sacar "<<cant<<" refrescos del contenedor de "<<tipo<<" que esta a unos "
					   <<vector[i]->data.getTemp()<<" grados."<<endl;
				   if(vector[i]->data.getCant()==0){ //si queda vacio el contenedor se elimina
					   if(vector[i]==primerPtr){ //si es el primer
						   Nodo *aux=vector[i];
						   this->primerPtr=vector[i]->sigPtr;
						   delete aux; }
					   if (vector[i]==ultimoPtr){ //si es el ultimo
						   Nodo *aux=vector[i];
						   vector[i-1]->sigPtr=0;
						   ultimoPtr=vector[i-1];
						   delete aux; }
					   else { //esta en el medio
						   Nodo *aux=vector[i];
						   vector[i-1]->sigPtr=vector[i+1];
						   delete aux;
					   }
				   }
				   return; // como ya encontro la cantidad que necesita sacar se sale del metodo
			   }
			   else{ //si la cantidad necesaria es mayor que la que tiene ese contenedor....
				   cant-=vector[i]->data.getCant();//lo que aun me falta de sacar
				   cout<<"Tiene que sacar "<<vector[i]->data.getCant()<<" refrescos del contenedor de "<<tipo<<" que esta a unos "
					   <<vector[i]->data.getTemp()<<" grados."<<endl;
				   if(vector[i]==primerPtr){ //si es el primer
					   Nodo *aux=vector[i];
					   this->primerPtr=vector[i]->sigPtr;
					   delete aux; }
				   if (vector[i]==ultimoPtr){ //si es el ultimo
					   Nodo *aux=vector[i];
					   vector[i-1]->sigPtr=0;
					   ultimoPtr=vector[i-1];
					   delete aux; }
				   else { //esta en el medio
					   if(i!=0){
					   Nodo *aux=vector[i];
					   vector[i-1]->sigPtr=vector[i+1];
					   delete aux; }
				   }
			   }
		   }
	   }
   }
   void nuevoContenedor(int cantidad, string tipo , int temp){
	   if (primerPtr == 0){ //si no hay nada en bodega
		   Nodo *newPtr = new Nodo(Contenedor(tipo, cantidad, temp));
		   primerPtr=ultimoPtr=newPtr;
		   contenedores=1;
		   return;
	   }
	   int i=0;
	   Nodo *vector[10]; //vector de nodos(contenedores)
	   Nodo *actualPtr = primerPtr;
	   for(actualPtr = primerPtr; actualPtr!=0; actualPtr=actualPtr->sigPtr){ //pasar contenedor(nodo) a vector
		   vector[i]=actualPtr;
		   i++;
		   contenedores=i;
	   }
	   if(contenedores==10){//pues si ya hay 10 contenedores no hay espacio para 3000 o sea otro contenedor mas(siempre vienen llenos)
		   cout<<"No hay espacio en bodega"<<endl;
		   return; }
	   if(primerPtr->sigPtr!=NULL){//si hay mas de uno
		   int min;
	   bool vacio=false;
	   while(vacio!=false){ //asegurarme de que no queden vacios
		   vacio=false;
		   for(int i=0; i<10; i++){
			   if(vector[i]==NULL){
				   vector[i]=vector[i+1];
				   vector[i+1]=NULL;
			   }
		   }
		   for(int i=0; i<10; i++)
			   if (vector[i]==NULL)
				   for(int j=i+1; j<10; j++)
					   if(vector[j]!=NULL)
						   vacio=true;
	   }
	   for(i=0; i<contenedores; i++){ //ordenar vector por temperatura
		   min=i;
		   for(int j=i+1; j<contenedores; j++){
			   if(vector[j]->data.getTemp()<vector[i]->data.getTemp())
				   min=j;
		   }
		   Contenedor aux=vector[i]->data;
		   vector[i]->data=vector[min]->data;
		   vector[min]->data=aux;
	   }
	   
		   int restante=0;
		   for(i=0; i<10&&vector[i]->sigPtr!=NULL; i++){ //este for hace que los contenedores mas frios queden llenos al maximo posible
			   if(vector[i]->data.getCant()!=3000) //si no esta llena
				   for(int j=i+1; j<10&&vector[i]->sigPtr!=NULL; j++)
					   if(vector[i]->data.getCant()!=3000){ //verificar que no esta llena despues de ir recorriendo el vector
						   restante=3000-vector[i]->data.getCant(); //averiguar cuanto falta para llenar
						   if(vector[i]->data.getTipo()==vector[j]->data.getTipo()){ //sean del mismo tipo
							   if(vector[j]->data.getCant()<restante){ //si la cantidad del otro contenedor es menor a la que se necesita para llenar al otro
								   vector[i]->data.setCant(vector[i]->data.getCant()+vector[j]->data.getCant()); //se le suma el siguiente
								   //se elimina el que quedaria vacio
								   if (vector[j]==ultimoPtr){ //si es el ultimo
									   Nodo *aux=vector[j];
									   ultimoPtr=vector[j-1];
									   vector[j-1]->sigPtr=0;
									   delete aux; }
								   else { //esta en el medio
									   Nodo *aux=vector[j];
									   vector[j-1]->sigPtr=vector[j+1];
									   delete aux;
								   }
							   }
							   else {
								   vector[i]->data.setCant(vector[i]->data.getCant()+restante); //se le suma el siguiente
								   vector[j]->data.setCant(vector[j]->data.getCant()-restante);//se le resta lo que se le paso al anterior
							   }
						   }
					   }
		   }
	   }
	   
	   Nodo *newPtr = new Nodo(Contenedor(tipo, cantidad, temp)); //creo el contenedor y lo meto en un nodo
	   ultimoPtr->sigPtr=newPtr;
	   ultimoPtr=newPtr;
	}
   };
#endif
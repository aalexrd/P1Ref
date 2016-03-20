#pragma once
#ifndef contenedor_H
#define contenedor_H
#include <iostream>
#include <string>
using namespace std;
class Contenedor{
private:
	string refresco;
	int cantidad;
	float temperatura;
public:
	Contenedor(){}
	Contenedor(string tipo, int cant, float temp): refresco(tipo),cantidad(cant), temperatura(temp){}
	void setTipo(string tipo){
		refresco = tipo; }
	void setCant(int cant){
		cantidad=cant; }
	void setTemp(float temp){
		temperatura=temp; }
	string getTipo(){
		return refresco; }
	int getCant(){
		return cantidad; }
	float getTemp(){
		return temperatura; }
};
#endif
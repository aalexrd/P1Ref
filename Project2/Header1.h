   void mostrarInventario(){
	   if(primerPtr==0){
		   cout<< "vacia";
		   return;
	   }
	   int suma=0;
	   Nodo *v[10];
	   Nodo *actual=primerPtr;
	   int i=0;
	   int conte=0;
	   for(actual = primerPtr; actual!=0; actual=actual->sigPtr){
		   v[i]=actual;
		   i++;
		   conte++;
	   }
	   int min=0;
	   for(i=0; i<conte; i++){ //ordenar vector alfabeticamente
			   min=i;
		   for(int j=i+1; j<conte; j++){
			   if(v[j]->data.getTipo()<v[i]->data.getTipo())
				   min=j;
		   }
		   Contenedor aux=v[i]->data;
		   v[i]->data=v[min]->data;
		   v[min]->data=aux;
	   }
	   for(i=0; i<conte; i++){
		   if(v[i]!=NULL){
		   suma=v[i]->data.getCant();
		   for(int j=i+1; j<conte; j++){
			   if(v[i]->data.getTipo()==v[j]->data.getTipo()&&(v[j]!=NULL)){
				   suma+=v[j]->data.getCant();
				   v[j]=NULL; }
		   }
		   cout<<"Existen "<<suma<<" de "<<v[i]->data.getTipo()<<endl;
		   }
	   }
   }
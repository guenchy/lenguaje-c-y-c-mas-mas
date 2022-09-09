// Cabeceras de librerias
#include <stdio.H>
#include <string.H>
#include <stdlib.H>

// Constantes a ser utilizadas
#define ARCHIVOCLIENTES  "clientes.txt"
#define ARCHIVOENTREGAS  "entregas.txt"
#define LONGITUD         1000
#define TAM              20
#define TAMVEC           5

// Funcion principal
int main(){
	FILE *clientes, *entregas;   // Descriptores de archivos
	char  linea[LONGITUD];       // Lineas de lectura en archivo clientes
	char  lineaP[LONGITUD];      // Lineas de lectura en archivo productos 	 
	int   renglon = 0;           // Posicion de registro leido
	int   posicion;              // Posicion en el registro leido
	int   codigoCliente;         // Contiene el codigo del cliente
	char  nombreCliente[TAM];    // Nombre del cliente
	int   codigoProducto;        // Contiene el codigo del producto
	char  nombreProducto[TAM];   // Nombre del producto
	float kilos;                 // Cantidad de kilos transportados
	float distancia;             // Cantidad la distancia recorrida
	int   productos;             // Conteo de lineas en el archivo de productos
	float cantidadKilos;         // Kilos por cliente
	int   controlcaso1;          // Control la inexistencia de casos 1

	char  nombresP[][TAM] = {"Pasta", "Azucar", "Aceite", "Arroz", "Queso"}; // Vector de cadenas, contiene los nombres de los productos
	float kilosP[TAMVEC];        // Vector de kilos para casos de mas de 13000 kilos
	float distanciaP[TAMVEC];    // Vector de distancia para casos de mas de 13000 kilos
	
	float menor;                 // Valor menor
	float mayor;                 // Valor menor 
	int   imprimir;              // Control sobre el vector
	int posicionM;               // Posicion del menor 
	int posicionMay;             // Posicion de mayor
	int totalEntregasMay;        // Total entregas del mayor
	 				 
	clientes = fopen(ARCHIVOCLIENTES, "r");
	
	// Si se produce un error al leer el archivo de clientes
	if (clientes == NULL){		
		printf("Archivo de clientes no se pudo abrir");
		exit(1);
	}
	
	controlcaso1 = 0;
	// Se leyo el archivo de clientes
	while (fgets(linea, LONGITUD, clientes)){
		
		// Removemos el \n de cada linea
		strtok(linea, "\n");
		
		// Descomponemos la cadenas por el tabulador que separa los elementos
		char delimitador[] = "\t";
		
		char *token = strtok(linea, delimitador);
		
		// Si la linea no esta vacia, obtenemos los datos
		if (token != NULL){
			// Extraemos los elementos de cada linea segun su posicion
			posicion = 1;
			strcpy(nombreCliente, "");
			strcpy(nombreProducto, "");
			while(token != NULL){
				switch(posicion){
					case 1: // Nombre Cliente
							strcpy(nombreCliente, token);	
							break;
					case 2: // Nombre Producto
							strcpy(nombreProducto, token);	
							break;
				}
					
				token = strtok(NULL, delimitador);  // Leemos el siguiente elemento en la linea
				
				posicion++;
			} // Fin WHILE
		} // Fin IF
		
			entregas = fopen(ARCHIVOENTREGAS, "r");
	
			// Si se produce un error al leer el archivo de productos
			if (entregas == NULL){		
				printf("Archivo de productos no se pudo abrir");
				exit(1);
			}
			
			// Se pudo abrir el archivo de productos, continuamos ...
			
			// Casos
			// ************************************************************************************
			productos = 0;
			// Inicializamos los vectores
			for(int i = 0; i < TAMVEC; i++)	{
				kilosP[i] = 0.0;     
	 			distanciaP[i] = 0.0;
			}
			while(productos <= 4){ // Recorrido para los 5 productos
				
				cantidadKilos = 0;			
				rewind(entregas);
				while (fgets(lineaP, LONGITUD, entregas)){
					
					// Removemos el \n de cada linea
					strtok(lineaP, "\n");
					
					// Descomponemos la cadenas por el tabulador que separa los elementos
					char delimitador[] = "\t";
					
					char *token = strtok(lineaP, delimitador);
					
					// Si la linea no esta vacia, obtenemos los datos
					if (token != NULL){
						// Extraemos los elementos de cada linea segun su posicion
						posicion = 1;
						codigoCliente = -1;          
						codigoProducto = -1;         
						kilos = 0;                
						distancia = 0;            
						while(token != NULL){
							switch(posicion){
								case 1: // Codigo Cliente
										codigoCliente = atoi(token);	
										break;
								case 2: // Codigo Producto
										codigoProducto = atoi(token);	
										break;
								case 3: // Kilos
										kilos = atof(token);	
										break;
								case 4: // Distancia
										distancia = atof(token);	
										break;									
							}
								
							token = strtok(NULL, delimitador);  // Leemos el siguiente elemento en la linea
							
							posicion++;
						} // Fin WHILE
					} // Fin IF
					
					// Si coincide el cliente y el producto
					if (codigoCliente == renglon){
						kilosP[codigoProducto] = kilos;     
	 					distanciaP[codigoProducto] = distancia;  

						cantidadKilos += kilos;
					}
				}			
			
				productos++;
			}
			// ************************************************************************************
			if (cantidadKilos > 13000.0000){
				
				// Caso 1
				printf("\nEl Cliente: %s, tiene mas de 13000 kilos de entregas, en los siguientes productos:", nombreCliente);
				
				for(int i = 0; i < TAMVEC; i++){
					if (distanciaP[i] != 0.0){
						printf("\n%s, Cantidad: %.2f",nombresP[i], kilosP[i]);
					}
				}	
				
				// Caso 2
				printf("\n\nDesgloce de distancias recorridas por producto:");
				
				// Obtenemos el mayor valor
				mayor = 0.0;
				for(int i = 0; i < TAMVEC; i++){
					if ( distanciaP[i] >= mayor ){
						mayor = distanciaP[i];
						posicionMay = i;
					}
				}					

				// En cada pase encontramos el menor y lo imprimimos
				imprimir = 0;
				while (imprimir < TAMVEC){
					menor = 1000000.0;
					posicionM = -1;
					for(int i = 0; i < TAMVEC; i++){
						if ( (distanciaP[i] != 0.0) && (distanciaP[i] <= menor) ){
							menor = distanciaP[i];
							posicionM = i;
						}					
						
						if (  ( i == (TAMVEC - 1)) && (posicionM != -1)  ){
							printf("\n%s, Distancia: %.2f",nombresP[posicionM], distanciaP[posicionM]);
							distanciaP[posicionM] = 0.0;	
						}
					}
					imprimir++;
				}
				
				// Caso 3
				//****************************************************************************************
				totalEntregasMay = 0;
				rewind(entregas);
				while (fgets(lineaP, LONGITUD, entregas)){
					
					// Removemos el \n de cada linea
					strtok(lineaP, "\n");
					
					// Descomponemos la cadenas por el tabulador que separa los elementos
					char delimitador[] = "\t";
					
					char *token = strtok(lineaP, delimitador);
					
					// Si la linea no esta vacia, obtenemos los datos
					if (token != NULL){
						// Extraemos los elementos de cada linea segun su posicion
						posicion = 1;
						codigoCliente = -1;          
						codigoProducto = -1;         
						while(token != NULL){
							switch(posicion){
								case 1: // Codigo Cliente
										codigoCliente = atoi(token);	
										break;
								case 2: // Codigo Producto
										codigoProducto = atoi(token);	
										break;
							}
								
							token = strtok(NULL, delimitador);  // Leemos el siguiente elemento en la linea
							
							posicion++;
						} // Fin WHILE
					} // Fin IF
					
					// Si coincide el cliente y el producto
					if (codigoProducto == posicionMay ){
						totalEntregasMay++;
					}
				}			
				printf("\n\nEl producto: %s, con mayor recorrido de: %.2f Km, se hicieron: %i entregas", nombresP[posicionMay], mayor, totalEntregasMay);
				//****************************************************************************************				
				controlcaso1 = 1;			
			}

		renglon++; 
	} // Fin del WHILE de lectura de clientes
	
	if (!controlcaso1)
		printf("\nNo existen clientes con mas de 13000 kilos despachados");
	fclose(clientes);   // Cerramos el archivo de clientes
	fclose(entregas);  // Por 
	
	return 0;	
}
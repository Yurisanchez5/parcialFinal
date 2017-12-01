#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define reservar_memoria (Nodo *)malloc(sizeof(Nodo))
#include <iomanip>

using namespace std;

struct Pagina{
	char titulo[40];
	char url[40];
	char categoria[40];
	int cantImagenes;
	int cantVideos;
	int cantImagenesXxx;
	int cantVideosXxx;
	double puntaje;
};


struct Nodo{
	Pagina pagina;
	Nodo *der;
	Nodo *izq;    
};


Nodo * crearNodo(Pagina pagina){
	Nodo *nuevo_nodo = reservar_memoria;
	
	nuevo_nodo->pagina = pagina;
	nuevo_nodo->der = NULL;
	nuevo_nodo->izq = NULL;
	
	return nuevo_nodo;
}

void insertarPorPuntaje(Nodo *&arbol, Pagina pagina){
	
	//El arbol puede estar vacio
	if(arbol == NULL){
		Nodo *nuevo_nodo = crearNodo(pagina);
		arbol = nuevo_nodo;
		
	}else{
		// Si el puntaje es menor entonces se inserta a la izq
		if(pagina.puntaje < arbol->pagina.puntaje){
			insertarPorPuntaje(arbol->izq, pagina);
		}else{
			insertarPorPuntaje(arbol->der, pagina);
		}
	}
}

void insertarPorUrl(Nodo *&arbol, Pagina pagina){
	
	//El arbol puede estar vacio
	if(arbol == NULL){
		Nodo *nuevo_nodo = crearNodo(pagina);
		arbol = nuevo_nodo;

	}else{
		
		if(strcmp(pagina.url, arbol->pagina.url) < 0){
			insertarPorUrl(arbol->izq, pagina);
		}else{
			insertarPorUrl(arbol->der, pagina);
		}
	}
}

void insertar(Nodo *&arbol, Pagina pagina){	
	insertarPorUrl(arbol, pagina);
}

double calcularPuntaje(Pagina pagina){
	
	double acum = 0;
	
	double cantImagenes = (double)(0.2 * pagina.cantImagenes);
	double cantVideos = (double)(0.5 * pagina.cantVideos);
	double cantImagenesXxx = (double)(-0.5 * pagina.cantImagenesXxx);
	double cantVideosXxx = (double)(-1 * pagina.cantVideosXxx);
	
	acum = cantImagenes + cantVideos + cantImagenesXxx + cantVideosXxx;;
	
	return acum;
	
}

void editarPagina(Pagina *pagina)
{
	system("CLS");
	
	fflush(stdin);
	printf("Ingrese el titulo de la pagina:  ");
	fgets(pagina->titulo,40,stdin);	
	
	fflush(stdin);
	printf("Ingrese su categoria:  ");
	fgets(pagina->categoria,40,stdin);
	
	printf("Ingrese Cantidad de Imagenes:  ");
	scanf("%d", &pagina->cantImagenes);
	
	printf("Ingrese Cantidad de Videos:  ");
	scanf("%d", &pagina->cantVideos);
	
	printf("Ingrese cantidad de imagenes para adultos:  ");
	scanf("%d", &pagina->cantImagenesXxx);
	
	printf("Ingrese cantidad de videos para adultos:  ");
	scanf("%d", &pagina->cantVideosXxx);
	
	pagina->puntaje = calcularPuntaje(*pagina);
	
}

void editarPorUrl(Nodo *&arbol, char url[]){
	
	//El arbol puede estar vacio
	if(arbol == NULL){
		printf("arbol vacio\n");	
		getch();
	}else{
		if(strcmp(url, arbol->pagina.url) == 0){
			editarPagina(&arbol->pagina);
		}else if(strcmp(url, arbol->pagina.url) < 0){
			editarPorUrl(arbol->izq, url);
		}else{
			editarPorUrl(arbol->der, url);
		}
	}
}

void editar(Nodo *&arbol)
{	
	
	char url[40];
	printf("Ingrese el url de la pagina:\n");
	fflush(stdin);
	scanf("%s", url);		
	
	editarPorUrl(arbol, url);
}

Nodo * nodoMasALaIzquierda(Nodo* nodo)
{
	Nodo* actual = nodo;
	
	while (actual->izq != NULL){
		actual = actual->izq;
	}
	
	return actual;
}

Nodo* eliminarPorUrl(Nodo* arbol, char url[])
{
	if(arbol == NULL){
		printf("arbol vacio\n");	
	}else{

		if(strcmp(url, arbol->pagina.url) < 0){
			arbol->izq = eliminarPorUrl(arbol->izq, url);
		}
		else if(strcmp(url, arbol->pagina.url) > 0){
			arbol->der = eliminarPorUrl(arbol->der, url);
		}
		else
		{
			if (arbol->izq == NULL)
			{
				Nodo *temp = arbol->der;
				free(arbol);
				arbol = NULL;
				
				return temp;
			}
			else if (arbol->der == NULL)
			{
				Nodo *temp = arbol->izq;
				free(arbol);
				arbol = NULL;
				
				return temp;
			}

			Nodo* temp = nodoMasALaIzquierda(arbol->der);
			
			strcpy(arbol->pagina.url, temp->pagina.url);
			
			arbol->der = eliminarPorUrl(arbol->der, temp->pagina.url);
			
			printf("La pagina web fue borrada\n");
		}
	}
	return arbol;
}
	
void eliminar(Nodo *&arbol)
{
	system("CLS");
	
	char url[40];
	printf("Ingrese el url de la pagina:\n");
	fflush(stdin);
	scanf("%s", url);	
	
	arbol = eliminarPorUrl(arbol, url);
	getch();
}

void imprimirPagina(Pagina pagina, int contador)
{

	for(int i=0;i<contador;i++){
		printf("     ");
	}
		
	printf("URL: %s\n", pagina.url);
	
	for(int i=0;i<contador;i++){
		printf("     ");
	}
	
	printf("Titulo: %s\n", pagina.titulo);
	
	for(int i=0;i<contador;i++){
		printf("     ");
	}
	
	printf("Categoria: %s\n", pagina.categoria);
	
	for(int i=0;i<contador;i++){
		printf("     ");
	}
	printf("Puntaje: %.2f \n\n", pagina.puntaje);
}

void mostrarArbol(Nodo *arbol, int contador){
	//Verficando si arbol esta vacio
	if(arbol == NULL){
		return;
	}
	else{
		mostrarArbol(arbol->der,contador+1);
		
		imprimirPagina(arbol->pagina, contador);		
		
		mostrarArbol(arbol->izq,contador+1);
	}
}

void buscarPaginaPorCategoria(Nodo *arbol, char categoria[]){
	
	if(arbol == NULL){
		return;
	}
	else{
		buscarPaginaPorCategoria(arbol->izq, categoria);
		
		if(strcmp(arbol->pagina.categoria, categoria) == 0){
			printf("URL: %s\n", arbol->pagina.url);
			printf("Titulo: %s\n", arbol->pagina.titulo);
			printf("Categoria: %s\n", arbol->pagina.categoria);
			printf("Puntaje: %.2f \n\n", arbol->pagina.puntaje);
		}
		
		buscarPaginaPorCategoria(arbol->der, categoria);
	}	
}

void InOrden(Nodo *arbol, int contador){
	if(arbol == NULL){
		return;
	}
	else{
		InOrden(arbol->izq, contador);
		
		for(int i=0;i< contador;i++){
			printf("     ");
		}
		printf("%s", arbol->pagina.url);
		
		for(int i=0;i<contador;i++){
			printf("     ");
		}
		printf("Puntaje:  %.2f \n\n", arbol->pagina.puntaje);
		
		InOrden(arbol->der, contador);
	}
}

void postOrden(Nodo *arbol, int contador){
	if(arbol == NULL){
		return;
	}
	else{
		postOrden(arbol->izq, contador);
		postOrden(arbol->der, contador);
		
		for(int i=0;i<contador;i++){
			printf("     ");
		}
		printf("%s", arbol->pagina.url);
		
		for(int i=0;i<contador;i++){
			printf("     ");
		}
		printf("Puntaje:  %.2f \n\n", arbol->pagina.puntaje);
		
	}
}

void preOrden(Nodo *arbol, int contador){
	if(arbol == NULL){
		return;
	}
	else{
		
		for(int i=0;i<contador;i++){
			printf("     ");
		}
		printf("%s", arbol->pagina.url);
		
		for(int i=0;i<contador;i++){
			printf("     ");
		}
		printf("Puntaje:  %.2f \n\n", arbol->pagina.puntaje);
		
		preOrden(arbol->izq, contador);
		preOrden(arbol->der, contador);
		
	}
}

Pagina crearPagina(){
	
	system("CLS");
		
	Pagina pagina;
	
	printf("Ingrese el titulo de la pagina:  ");
	scanf("%s", pagina.titulo);
		
	printf("Ingrese la URL: ");
	scanf("%s", pagina.url);
	
	printf("Ingrese su categoria:  ");
	scanf("%s", pagina.categoria);
	
	printf("Ingrese Cantidad de Imagenes:  ");
	scanf("%d", &pagina.cantImagenes);
	
	printf("Ingrese Cantidad de Videos:  ");
	scanf("%d", &pagina.cantVideos);
	
	printf("Ingrese cantidad de imagenes para adultos:  ");
	scanf("%d", &pagina.cantImagenesXxx);
	
	printf("Ingrese cantidad de videos para adultos:  ");
	scanf("%d", &pagina.cantVideosXxx);
	
	
	pagina.puntaje = calcularPuntaje(pagina);
	
	return pagina;
}

void mostrarPaginas(Nodo *&arbol){
	system("CLS");
	
	mostrarArbol(arbol, 1);
	
	getch ();
}
 
void buscarPorCategoria (Nodo *&arbol){
	
	system("CLS");
	
	char categoria[40];
	
	printf("Escriba la categoria de la pagina web:\n");
	scanf("%s",categoria);
		
	if(arbol == NULL){
		printf("arbol vacio\n");
	}
	else {	
		buscarPaginaPorCategoria(arbol, categoria);
	}
		
	getch ();
}

void buscarPaginaPorTitulo(Nodo *arbol, char titulo[]){
	
	if(arbol == NULL){
		return;
	}
	else{
		buscarPaginaPorTitulo(arbol->izq, titulo);
		
		if(strcmp(arbol->pagina.titulo, titulo) == 0){
			printf("URL: %s\n", arbol->pagina.url);
			printf("Titulo: %s\n", arbol->pagina.titulo);
			printf("Categoria: %s\n", arbol->pagina.categoria);
			printf("Puntaje: %.2f \n\n", arbol->pagina.puntaje);
		}
		
		buscarPaginaPorTitulo(arbol->der, titulo);
	}	
}

void buscarPorTitulo(Nodo *&arbol)
{
	system("CLS");
	
	char titulo[40];
	
	printf("Escriba el titulo de la pagina web:\n");
	scanf("%s",titulo);
	
	if(arbol == NULL){
		printf("arbol vacio\n");
	}
	else {	
		buscarPaginaPorTitulo(arbol, titulo);
	}
	
	getch ();
	
}

void editarPagina(){
	
	char titulo[40];
	
	fflush(stdin);
	printf("Ingrese el titulo de la pagina a editar:  ");
	fgets(titulo,40,stdin);
}
	
void listarPorPuntaje(Nodo *&arbol)
{
	if(arbol == NULL){
		return;
	}
	else{
		listarPorPuntaje(arbol->der);

		printf("URL: %s\n", arbol->pagina.url);
		printf("Titulo: %s\n", arbol->pagina.titulo);
		printf("Categoria: %s\n", arbol->pagina.categoria);
		printf("Puntaje: %.2f \n\n", arbol->pagina.puntaje);
		
		listarPorPuntaje(arbol->izq);
	}
}

void copiarArbolANuevoArbolPuntaje(Nodo *&arbolActual, Nodo *&nuevoArbolPuntaje){
	
	if (arbolActual == NULL){
		return;
	}
	else{
		// se va recorriendo el arbol actual y se va insertando en el nuevo
		// arbol que esta ordenado segun el puntaje
		copiarArbolANuevoArbolPuntaje(arbolActual->izq, nuevoArbolPuntaje);
		insertarPorPuntaje(nuevoArbolPuntaje, arbolActual->pagina);
		copiarArbolANuevoArbolPuntaje(arbolActual->der, nuevoArbolPuntaje);
	}
}


void mostrarPuntaje(Nodo *&arbol)
{
	system("CLS");
	// Utilizando un arbol nuevo y vacio
	// se insertan todos los nodos del arbol actual a otro arbol que está
	// ordenado por puntaje y luego simplemente se imprime de mayor puntaje
	// a menor puntaje
	Nodo * arbolPorPuntaje = NULL;
	
	copiarArbolANuevoArbolPuntaje(arbol, arbolPorPuntaje);	
	listarPorPuntaje(arbolPorPuntaje);
	
	getch();
}

void escribirArbolAArchivo(Nodo *&arbol, FILE *archivo){
	if(arbol == NULL){
		return;
	}
	else{
		escribirArbolAArchivo(arbol->izq, archivo);
		fwrite(&arbol->pagina, sizeof(Pagina), 1, archivo);
		escribirArbolAArchivo(arbol->der, archivo);
	}
}

void guardarArchivo(Nodo *&arbol)
{
	FILE *archivo;
	
	archivo = fopen("arbol.txt", "wb"); //proceso para escribir byte por byte
	rewind(archivo);
	
	escribirArbolAArchivo(arbol, archivo);
	
	fclose(archivo);
}

void cargarArchivo(Nodo *&arbol)
{
	FILE *archivo;
	Pagina pagina;
	
	archivo = fopen("arbol.txt", "rb"); //proceso para leer byte por byte
	rewind(archivo);
	
	// Leyendo
	while (1 == fread(&pagina, sizeof(Pagina), 1, archivo))
	{
		insertar(arbol, pagina);
	}
	
	fclose(archivo);
}
	
int main (int argc, char *argv[]) {
	
	int opcion=1;
	
	Nodo * arbol = NULL;
	
	while(opcion!=0)
	{
		system("CLS");
		
		printf("----M E N U----\n");
		printf("1.Crear Pagina Web: \n");
		printf("2.Mostrar Paginas Web: \n");
		printf("3.Mostrar Paginas Web según puntaje: \n");
		printf("4.Editar Paginas Web: \n");
		printf("5.Eliminar Paginas Web: \n");
		printf("6.Buscar Paginas Web por categoria: \n");
		printf("7.Buscar Paginas Web por titulo: \n");
		printf("8.Cargar el archivo \"arbol.txt\": \n");
		printf("9.Guardar el archivo \"arbol.txt\": \n");
		printf("0.Salir \n");
		printf("Seleccione Opcion: "); 
		scanf("%d",&opcion);
		
		switch(opcion)
		{
			case 1: 
			{
				Pagina pagina;	
				pagina = crearPagina();
				insertar(arbol, pagina);				
				break;
			}          
			case 2: 
			{
				mostrarPaginas(arbol);				
				break;
			}        
			
			case 3: 
			{ 
				mostrarPuntaje(arbol);
				break;
			}
			
			case 4: 
			{
				editar(arbol);
				break;
			}  
			
			case 5: 
			{
				eliminar(arbol);
				break;
			}  
			
			case 6: 
			{ 
				buscarPorCategoria(arbol);
				break;
			}  
			
			case 7: 
			{ 
				buscarPorTitulo(arbol);
				break;
			} 
			
			case 8: 
			{ 
				cargarArchivo(arbol);
				break;
			}
			
			case 9: 
			{ 
				guardarArchivo(arbol);
				break;
			}
			
			default:{
				system("CLS");
				
				break;
			}          
		}
	}
	
	
	return 0;
}


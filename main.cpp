/**
 * Programa para resolver sistemas de ecuaciones lineales de 3x3.
 * 1. Se deben de introducir las ecuaciones y el programa debe extraer los coeficientes,
 *    generar la matriz de coeficientes y resolver el sistema.
 * 2. No se deben usar variables globales.
 * 3. Se debe usar el método de Gauss-Jordan.
 */
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string>
#include<string.h>
#include<cctype>
#include<math.h>
#include <regex>

using namespace std;
/**
 * Funciones necesarias para el programa.
 * º Función para la captura de las ecuaciones.
 * º Función para la extracción de los coeficientes.
 * º Función principal.
 * Se irán agregando más funciones conforme se vayan necesitando.
 */

//Declaramos las funciones

bool capturaEcuaciones(float *matriz, string *literales);//Se encarga de capturar las ecuaciones, regresa si se pudieron capturar o no
void sacarCoeficientes(string *ecuacion,float *matriz, int *currentElement);//Se encarga de sacar los coeficientes de las ecuaciones
bool hasNumbers(string *str);//Se encarga de checar si el substring tiene numeros
bool hasSign(string *str);//Se encarga de checar si el substring tiene signo



int main(){

    //Declaración de las variables

	//Variables para el Gauss-Jordan
	float auxiliar,factorUnitarinador=0, factorCeroinador[10];
	int mFilas=0, nColumnas=0, nmDiagonal=0, exchangeRowPosition=0, puntos=0;
	bool hasSolution=true;
    float matriz[3][4];

	//Variables para confirmaciones del usuario
	char salir;

	//Variables para trabajar con las ecuaciones
    string literales[4];
    char literals[3]={'x','y','z'};

	//Configuraciones de la consola
	setlocale(LC_CTYPE,"spanish");
	
	//Opciones básicas para el funcionaiento del programa
	inicio:fflush(stdin);
	hasSolution=true;
	system("cls");

	//Se imprime la bienvenida al programa
    cout<<"PROGRAMA GAUSS-JORDAN"<<endl<<endl;
    cout<<"Ingrese las ecuaciones separadas por un salto de linea:"<<endl;
    cout<<"\tEjemplo: 2x+3y-4z=5"<<endl;
    cout<<"\t           -2y+5z=6"<<endl;
    
    if(!capturaEcuaciones((float *)matriz, literales))//Se reciben los datos
	{ 	//Si se introducen ecuaciones inválidas, se pregunta si se desea volver a empezar o salir del programa
		cout<<"Desea volver a empezar? (S/N): ";
		cin>>salir;
		if(salir=='s'||salir=='S'){
			goto inicio;
		}else{
			system("pause");
			return 0;
		}
	}

	//Cantidad de columnas y filas de la matriz
    nColumnas=3;
	mFilas=3;

	//Checar que el usuario haya introducido lo que quería introducir
	for(int i=0;i<mFilas;i++){
		cout<<"\t\t";
		for(int j=0;j<nColumnas;j++){
			printf("%+5.2f%c ",matriz[i][j],literals[j]);
		}
		printf("= %5.2f\n",matriz[i][nColumnas]);
	}

	//Permitir al usuario confirmar que los datos introducidos son correctos
	cout<<"\t¿Es correcto? (S/N): ";
	cin>>salir;
	if(salir!='s'&&salir!='S'){
		goto inicio;
	}
	
	system("pause");
	system("cls");
	
	//Se empieza el Gauss-Jordan
	
	//Se define una "diagonal" sobre la cual operar
	nmDiagonal=(mFilas<=nColumnas)?mFilas:nColumnas;
	
	for(int i=0;i<nmDiagonal;i++){//Nos recorre la diagonal
		if(matriz[i][i]==0){//Si el elemento actual de la diagonal es 0, hacer intercambio con otra fila
			bool breakIt=false;
			if(i+1==nmDiagonal){
				break;
			}
			for(int j=i;;j++){//Recorre filas
				if(matriz[j][i]!=0){
					exchangeRowPosition=j;//Encontramos la fila por la que intercambiaremos
					break;
				}
				if(j>=mFilas){
					breakIt=true;
					break;
				}
			}
			if(breakIt){
				break;
			}
			for(int j=0;j<nColumnas;j++){//Recorre columnas
				//Intercambiamos filas
				auxiliar=matriz[i][j];
				matriz[i][j]=matriz[exchangeRowPosition][j];
				matriz[exchangeRowPosition][j]=auxiliar;
			}
			
			//Imprimir paso a paso
			{
				cout<<"Intercambiar R"<<i+1<<" <=> R"<<exchangeRowPosition+1<<":"<<endl;
				for(int k=0;k<mFilas;k++){
					cout<<"\t\t";
					for(int l=0;l<nColumnas;l++){
						printf("+%5.2f%c ",matriz[k][l],literals[l]);
					}
					printf("= %5.2f \n",matriz[k][nColumnas]);
				}
				cout<<endl<<endl;
			}
			
		}
		factorUnitarinador=1/matriz[i][i];
		{
			cout<<"Multiplicar R"<<i+1<<"*"<<factorUnitarinador<<":"<<endl;
			for(int k=0;k<mFilas;k++){
				cout<<"\t\t";
				for(int l=0;l<nColumnas;l++){
					if(k==i){
						printf("%+5.2f%c ",(matriz[k][l]*factorUnitarinador),literals[l]);
					}else{
						printf("%+5.2f%c ",matriz[k][l],literals[l]);
					}
					
				}
				if(k==i){
					printf("= %5.2f \n",(matriz[k][nColumnas]*factorUnitarinador));
				}else{
					printf("= %5.2f \n",matriz[k][nColumnas]);
				}
			}
			cout<<endl<<endl;
		}
		for(int j=i;j<=nColumnas;j++){//Nos recorre la fila a partir de el elemento actual en la diagonal
			matriz[i][j]*=factorUnitarinador;
			for(int k=0;k<mFilas;k++){//Nos recorre la columna del elemento actual de la fila desde arriba hasta abajo
				if(k==i){
					continue;
				}
				if(j==i){
					factorCeroinador[k]=matriz[k][j];
				}
				matriz[k][j]-=(factorCeroinador[k]*matriz[i][j]);
			}
		}
		
		{
			cout<<"Sumar";
			for(int k=0;k<mFilas;k++){
				if(k!=i){
					cout<<" | R"<<k+1<<" = R"<<k+1<<" + ("<<(-1*factorCeroinador[k])<<"*R"<<i+1<<")";
				}
			}
			cout<<":"<<endl;
			for(int k=0;k<mFilas;k++){
				cout<<"\t\t";
				for(int l=0;l<nColumnas;l++){
					printf("%+5.2f%c ",matriz[k][l],literals[l]);
				}
				printf("= %5.2f \n",matriz[k][nColumnas]);
			}
			cout<<endl<<endl;
		}
	}
	
	//Verificando que tenga una posible solucion
	{
		int cantidadCerosFila=0;
		for(int i=0;i<mFilas;i++){
			cantidadCerosFila=0;
			for(int j=0;j<nColumnas;j++){
				if(matriz[i][j]==0){
					cantidadCerosFila++;
				}
			}
			if(cantidadCerosFila==nColumnas&&matriz[i][nColumnas]!=0){
				cout<<"El sistema no tiene solución"<<endl;
				hasSolution=false;
			}
		}
	}

	//Si tiene solución, se imprime la solución
	if(hasSolution){
		cout<<"RESULTADOS"<<endl;
		for(int i=0;i<mFilas;i++){
			for(int j=0;j<nColumnas;j++){
				printf("%+5.2f%c ",matriz[i][j],literals[j]);
			}
			printf("= %5.2f \n",matriz[i][nColumnas]);
		}
	}
	cout<<"Desea volver a empezar? (S/N): ";
	cin>>salir;
	if(salir=='s'||salir=='S'){
		goto inicio;
	}
	system("pause");
	return 0;
}

//Definimos las funciones

//Función encargada de capturar las ecuaciones
bool capturaEcuaciones(float *matriz, string *literales){
    string ecuacion;//La ecuación que se va a capturar
	regex patron(R"([-+]?\d*(\.\d+)?[xyz]?([-+]?\d*(\.\d+)?[xyz]?([-+]?\d*(\.\d+)?[xyz]?)?)?\s*=\s*[-+]?\d*(\.\d+)?)");//Regex para comprobar que la ecuación sea válida
	//Un regex es como una especie de patrón que se usa para comprobar que una cadena de texto cumpla con ciertas características
	//En este caso, el regex que se usa es para comprobar que la ecuación sea válida

    int currentElement=0;//Elemento actual de la matriz
    for(int i=0;i<3;i++){//Se capturan las 3 ecuaciones
        getline(cin,ecuacion,'\n');//Se captura la ecuación
		if(!regex_match(ecuacion,patron)){//Se comprueba que la ecuación sea válida
			cout<<endl<<"\t\tEcuacion invalida, vuelva a intentarlo"<<endl;
			return false;
		}
        sacarCoeficientes(&ecuacion,matriz,&currentElement);//Se sacan los coeficientes de la ecuación
    }
	return true;
}

//Función encargada de sacar los coeficientes de las ecuaciones
void sacarCoeficientes(string *ecuacion,float *matriz, int *currentElement){
    int divisores[4];//Divisores de la ecuación
	//Sacaremos los coeficientes de la ecuación por medio de substrings
	//Se usan las literales para partir la ecuación en 4 partes
	//Luego, se sacan los coeficientes de cada parte

    string coeficiente;//Coeficiente actual
    for (auto& x : *ecuacion) {//for-range loop (para cada elemento x en la ecuacion) 
        x = tolower(x);//pasar a minusculas toda la ecuacion
    }

	//Se encuentran los divisores
    divisores[0]=(*ecuacion).find("x");
    divisores[1]=(*ecuacion).find("y");
    divisores[2]=(*ecuacion).find("z");
    divisores[3]=(*ecuacion).find("=");

	//Se sacan los coeficientes
	int n= *currentElement;//Últino elemento de la matriz de coeficientes

	bool hasStarted=false;//Revisa si ya se empezó a sacar coeficientes distintos de 0

    for(;*currentElement<(n+3);(*currentElement)++){//Se recorren las 3 literales


    	if(divisores[((*currentElement)%4)]>=0&&hasStarted){//Checamos si ya se empezó a sacar coeficientes distintos de 0 y si el término existe. Ej. evitamos buscar "y" en 2x+3z=11


    		coeficiente=(*ecuacion).substr((((*currentElement)%4==0&&true)?0:(divisores[((*currentElement)%4)-1]+1)),(((*currentElement)%4==0)?divisores[((*currentElement)%4)]:((divisores[((*currentElement)%4)]-1)-divisores[((*currentElement)%4)-1])));
			
			if(!coeficiente.empty()&&coeficiente!="+"&&coeficiente!="-"){//Ej. sirve para buscar "y" en 2x+3y=11
				int plusPosition=coeficiente.find("+");//Checamos si el coeficiente tiene un signo de suma
				if(plusPosition>=0){//Si tiene un signo de suma, lo quitamos
					coeficiente.erase(plusPosition,1);
					if(coeficiente.empty()){//Ej. sirve para buscar "y" en 2x+y=11
						*(matriz+(*currentElement))=1.0;//Si el coeficiente es vacío, el coeficiente es 1 
					}else{
						*(matriz+(*currentElement))=stof(coeficiente);//Si el coeficiente no es vacío, lo convertimos a float y lo guardamos
					}
					
				}else{
					*(matriz+(*currentElement))=stof(coeficiente);//Si el coeficiente no tiene signo de suma, lo convertimos a float y lo guardamos (negativos)
				}
				
			}else if(!coeficiente.empty()&&(coeficiente=="+"||coeficiente=="-")){//Ej. sirve para buscar "y" en 2x-3y=11
				int plusPosition=coeficiente.find("+");//Checamos si el coeficiente tiene un signo de suma
				
				if(plusPosition>=0){//Si tiene un signo de suma, lo quitamos
					coeficiente.erase(plusPosition,1);
					if(coeficiente==""){
						*(matriz+(*currentElement))=1.0;//Si el coeficiente es vacío, el coeficiente es 1
					}else{
						*(matriz+(*currentElement))=stof(coeficiente);//Si el coeficiente no es vacío, lo convertimos a float y lo guardamos
					}
					
				}else{
					*(matriz+(*currentElement))=-1.0;//Si el coeficiente no tiene signo de suma, el coeficiente es -1
				}
			}else{
				*(matriz+(*currentElement))=1.0;//Si el coeficiente es vacío, el coeficiente es 1
			}
		}else if(hasStarted&&divisores[((*currentElement)%4)]<0){//Ej. sirve para buscar "y" en 2x+3z=11

			*(matriz+(*currentElement))=0.0;
			divisores[((*currentElement)%4)]=divisores[((*currentElement)%4)-1];//Cambia esto para que cuando saquemos la "z", no busque a partir de la "y", sino de la "x"


		}else if(!hasStarted&&divisores[((*currentElement)%4)]>=0){//Encargado de sacar el primer coeficiente de la ecuación

			coeficiente=(*ecuacion).substr(0,divisores[((*currentElement)%4)]);//Sacamos el substring que contiene el coeficiente del primer término

			bool hasNoNumbersInIt=!hasNumbers(&coeficiente);//Checa si el substring tiene numeros, Ej. 4x en 4x+3y=11

			bool hasSignInIt=hasSign(&coeficiente);//Checa si el substring tiene signo, Ej. -4x en -4x+3y=11

			if(coeficiente.empty()){//Ej. sirve para buscar "x" en x+3y=11
				*(matriz+(*currentElement))=1.0;
				
			}else if(hasNoNumbersInIt){//Ej. sirve para buscar "x" en -x+3y=11
				float valor=((hasSignInIt)?(-1.0):(1.0));
				*(matriz+(*currentElement))=valor;

			}else{//Ej. sirve para buscar "4x" en 4x+3y=11
				*(matriz+(*currentElement))=stof(coeficiente);
			}
			
			hasStarted=true;

		}else{//Encargado de poner 0 en los coeficientes que no existen en la ecuación, Ej. 2y+3z=11, el coeficiente de la "x" es 0
			//Solo cuando aún no ha empezado a sacar coeficientes distintos de 0
			*(matriz+(*currentElement))=0.0;
			divisores[((*currentElement)%4)]=0;
		}
    }

	//Encargado de sacar los resultados de las ecuaciones
    if(((*ecuacion).substr(divisores[((*currentElement)%4)]+1,(*ecuacion).size()))=="0"||(*ecuacion).substr(divisores[((*currentElement)%4)]+1,(*ecuacion).size()).empty()){
    	*(matriz+(*currentElement))=0;//Si el resultado es 0, el resultado es 0
	}else{
		*(matriz+(*currentElement))=stof((*ecuacion).substr(divisores[((*currentElement)%4)]+1,(*ecuacion).size()));//Si el resultado no es 0, lo convertimos a float y lo guardamos
	}
    
    (*currentElement)++;
}

//Función encargada de checar si el substring tiene numeros
bool hasNumbers(string *str){
    for(int i=0;i<(*str).length();i++){
        if(isdigit((*str)[i])&&(*str)[i]>='0'&&((*str)[i])<='9'){
            return true;
        }
    }
    return false;
}

//Función encargada de checar si el substring tiene signo
bool hasSign(string *str){
    return (int((*str).find("-"))>=0);
}
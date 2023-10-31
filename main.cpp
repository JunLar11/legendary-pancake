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

bool capturaEcuaciones(float *matriz, string *literales);//Se encarga de capturar las ecuaciones
void sacarCoeficientes(string *ecuacion,float *matriz, int *currentElement);//Se encarga de sacar los coeficientes de las ecuaciones
bool hasNumbers(string *str);//Se encarga de checar si el substring tiene numeros
bool hasSign(string *str);//Se encarga de checar si el substring tiene signo



int main(){
    
    
    //Declaración de las variables
	float auxiliar,factorUnitarinador=0, factorCeroinador[10];
	int mFilas=0, nColumnas=0, nmDiagonal=0, exchangeRowPosition=0, puntos=0;
	char salir;
	bool hasSolution=true;
    float matriz[3][4];
    string literales[4];
    char literals[3]={'x','y','z'};
	
	//Recibimos las dimensiones de la matriz por parte del usuario
	inicio:fflush(stdin);
	hasSolution=true;
	system("cls");

    cout<<"PROGRAMA GAUSS-JORDAN"<<endl<<endl;
    cout<<"Ingrese las ecuaciones separadas por un salto de linea:"<<endl;
    cout<<"\tEjemplo: 2x+3y-4z=5"<<endl;
    cout<<"\t           -2y+5z=6"<<endl;
    setlocale(LC_CTYPE,"spanish");
    if(!capturaEcuaciones((float *)matriz, literales))//Se reciben los datos
	{
		cout<<"Desea volver a empezar? (S/N): ";
		cin>>salir;
		if(salir=='s'||salir=='S'){
			goto inicio;
		}else{
			system("pause");
			return 0;
		}
	}
    nColumnas=3;
	mFilas=3;

	for(int i=0;i<mFilas;i++){
		cout<<"\t\t";
		for(int j=0;j<nColumnas;j++){
			printf("%+5.2f%c ",matriz[i][j],literals[j]);
		}
		printf("= %5.2f\n",matriz[i][nColumnas]);
	}
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

bool capturaEcuaciones(float *matriz, string *literales){
    string ecuacion;
	regex patron(R"([-+]?\d*(\.\d+)?[xyz]?([-+]?\d*(\.\d+)?[xyz]?([-+]?\d*(\.\d+)?[xyz]?)?)?\s*=\s*[-+]?\d*(\.\d+)?)");
    int currentElement=0;
    for(int i=0;i<3;i++){
        getline(cin,ecuacion,'\n');
		if(!regex_match(ecuacion,patron)){
			cout<<endl<<"\t\tEcuacion invalida, vuelva a intentarlo"<<endl;
			return false;
		}
        sacarCoeficientes(&ecuacion,matriz,&currentElement);
    }
	return true;
}

void sacarCoeficientes(string *ecuacion,float *matriz, int *currentElement){
    int divisores[4];
    string coeficiente;
    for (auto& x : *ecuacion) { 
        x = tolower(x);
    }
    divisores[0]=(*ecuacion).find("x");
    divisores[1]=(*ecuacion).find("y");
    divisores[2]=(*ecuacion).find("z");
    divisores[3]=(*ecuacion).find("=");
	int n= *currentElement;
	bool hasStarted=false;
    for(;*currentElement<(n+3);(*currentElement)++){
    	if(divisores[((*currentElement)%4)]>=0&&hasStarted){
    		coeficiente=(*ecuacion).substr((((*currentElement)%4==0&&true)?0:(divisores[((*currentElement)%4)-1]+1)),(((*currentElement)%4==0)?divisores[((*currentElement)%4)]:((divisores[((*currentElement)%4)]-1)-divisores[((*currentElement)%4)-1])));
			
			if(!coeficiente.empty()&&coeficiente!="+"&&coeficiente!="-"){
				int plusPosition=coeficiente.find("+");
				if(plusPosition>=0){
					coeficiente.erase(plusPosition,1);
					if(coeficiente.empty()){
						*(matriz+(*currentElement))=1.0;
					}else{
						*(matriz+(*currentElement))=stof(coeficiente);
					}
					
				}else{
					*(matriz+(*currentElement))=stof(coeficiente);
				}
				
			}else if(!coeficiente.empty()&&(coeficiente=="+"||coeficiente=="-")){
				int plusPosition=coeficiente.find("+");
				
				if(plusPosition>=0){
					coeficiente.erase(plusPosition,1);
					if(coeficiente==""){
						*(matriz+(*currentElement))=1.0;
					}else{
						*(matriz+(*currentElement))=stof(coeficiente);
					}
					
				}else{
					*(matriz+(*currentElement))=-1.0;
				}
			}else{
				*(matriz+(*currentElement))=1.0;
			}
		}else if(hasStarted&&divisores[((*currentElement)%4)]<0){
			*(matriz+(*currentElement))=0.0;
			divisores[((*currentElement)%4)]=divisores[((*currentElement)%4)-1];
		}else if(!hasStarted&&divisores[((*currentElement)%4)]>=0){
			coeficiente=(*ecuacion).substr(0,divisores[((*currentElement)%4)]);
			bool hasNoNumbersInIt=!hasNumbers(&coeficiente);
			bool hasSignInIt=hasSign(&coeficiente);
			if(coeficiente.empty()){
				*(matriz+(*currentElement))=1.0;
			}else if(hasNoNumbersInIt){
				float valor=((hasSignInIt)?(-1.0):(1.0));
				*(matriz+(*currentElement))=valor;
			}else{
				
				*(matriz+(*currentElement))=stof(coeficiente);
			}
			
			hasStarted=true;
		}else{
			*(matriz+(*currentElement))=0.0;
			divisores[((*currentElement)%4)]=0;
		}
    }
    if(((*ecuacion).substr(divisores[((*currentElement)%4)]+1,(*ecuacion).size()))=="0"||(*ecuacion).substr(divisores[((*currentElement)%4)]+1,(*ecuacion).size()).empty()){
    	*(matriz+(*currentElement))=0;
	}else{
		*(matriz+(*currentElement))=stof((*ecuacion).substr(divisores[((*currentElement)%4)]+1,(*ecuacion).size()));
	}
    
    (*currentElement)++;
}

bool hasNumbers(string *str){
    for(int i=0;i<(*str).length();i++){
        if(isdigit((*str)[i])&&(*str)[i]>='0'&&((*str)[i])<='9'){
            return true;
        }
    }
    return false;
}

bool hasSign(string *str){
    return (int((*str).find("-"))>=0);
}
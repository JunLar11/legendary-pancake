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

using namespace std;
/**
 * Funciones necesarias para el programa.
 * º Función para la captura de las ecuaciones.
 * º Función para la extracción de los coeficientes.
 * º Función principal.
 * Se irán agregando más funciones conforme se vayan necesitando.
 */

//Declaramos las funciones

void capturaEcuaciones(int *matriz, string *literales);//Se encarga de capturar las ecuaciones
void sacarCoeficientes(string *ecuacion,int *matriz);//Se encarga de sacar los coeficientes de las ecuaciones



int main(){
    fflush(stdin);
    system("cls");
    float matriz[3][4];
    string literales[4];
    capturaEcuaciones((int *)matriz, literales);
    return 0;
}

void capturaEcuaciones(int *matriz, string *literales){
    string ecuacion;
    for(int i=0;i<3;i++){
        getline(cin,ecuacion,'\n');
        sacarCoeficientes(&ecuacion,matriz);
        cout<<"XD";
    }
}

void sacarCoeficientes(string *ecuacion,int *matriz){
    cout<<"x "<<(*ecuacion).find("x")<<endl;
    cout<<"y "<<(*ecuacion).find("y")<<endl;
    cout<<"z "<<(*ecuacion).find("z")<<endl;
}
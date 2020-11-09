#include<iostream>
#include "rls.h"
#include "rls_potencia.h"
#include "rls_exponencial.h"
#include "rc.h"

using std::cout;
using std::endl;
using std::vector;

void caso();
void imprimir_tabla_datos(vector<double>, vector<double>);
void imprimir_potencia(vector<double>, vector<double>, regresion_potencia);
void imprimir_exponencial(vector<double>, vector<double>, regresion_exponencial);
void imprimir_cuadratica(vector<double>, vector<double>, regresion_rc);

int main (int argc, char *argv[]) {
	
	caso();
	return 0;
}

void caso(){
	vector<double> x {1100, 1200, 1250, 1300, 1600, 1800, 1850, 1950, 2000, 2025, 2200, 2500, 2600};
	vector<double> y {112.5, 114, 115.5, 117, 126.5, 135, 142, 146, 147.5, 151, 161, 190, 210};
	
	//Regresion Potencial
	rls_potencia r_p;
	regresion_potencia resultado_p = r_p.calcular(x, y);
	
	//Regresion Exponencial
	rls_exponencial r_ex;
	regresion_exponencial resultado_ex = r_ex.calcular(x, y);
	
	//Regresion Cuadratica
	rc r_cua;
	regresion_rc resultado_cu = r_cua.calcular(x, y);
	
	imprimir_potencia(x, y, resultado_p);
	imprimir_exponencial(x, y, resultado_ex);
	imprimir_cuadratica(x, y, resultado_cu);
}

void imprimir_tabla_datos(vector<double> x, vector<double> y){
	cout << endl << "TABLA DE DATOS" << endl;
	cout << "x\t\ty" << endl;
	for(unsigned int i =0; i < x.size(); i++){
		cout << x[i] << "\t\t" << y[i] << endl;
	}
	cout << endl;
}
void imprimir_potencia(vector<double> x, vector<double> y, regresion_potencia r_p){
	imprimir_tabla_datos(x,y);
	cout << " POTENCIAL" << endl;
	cout << "St\t= " << r_p.st<< endl;
	cout << "Sr\t= " << r_p.sr<< endl;
	cout << "Sy\t= " << r_p.sy << endl;
	cout << "Sy/x\t= " << r_p.syx << endl;
	cout << "r2\t= " << r_p.r2 << endl;
	cout << "FORMULA: Y = " << r_p.c << " * X^(" << r_p.a << ")" << endl;
	system("pause");
}
void imprimir_exponencial(vector<double> x, vector<double> y, regresion_exponencial r_e){
	imprimir_tabla_datos(x,y);
	cout << " EXPONENCIAL" << endl;
	cout << "St\t= " << r_e.st<< endl;
	cout << "Sr\t= " << r_e.sr<< endl;
	cout << "Sy\t= " << r_e.sy << endl;
	cout << "Sy/x\t= " << r_e.syx << endl;
	cout << "r2\t= " << r_e.r2 << endl;
	cout<<"FORMULA: Y = " << r_e.c << " * e^( " << r_e.a << "X )" << endl;
	system("pause");
}
void imprimir_cuadratica(vector<double> x, vector<double> y, regresion_rc resultado){
	imprimir_tabla_datos(x,y);
	cout << " CUADRATICA" << endl;
	cout << "St\t= " << resultado.st<< endl;
	cout << "Sr\t= " << resultado.sr<< endl;
	cout << "Sy\t= " << resultado.sy << endl;
	cout << "Sy/x\t= " << resultado.syx << endl;
	cout << "r2\t= " << resultado.r2 << endl;
	cout << "FORMULA: Y = " << resultado.a2 << "X^2";
	if(resultado.a1 > 0){
		cout << " +"; 
	}
	cout << " " << resultado.a1 << "X + " << resultado.a0 << endl;
	system("pause");
}

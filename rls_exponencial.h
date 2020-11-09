#ifndef RLS_EXPONENCIAL_H
#define RLS_EXPONENCIAL_H
#include "rls.h"
#include <vector>
#include <cmath>

using std::vector;

struct regresion_exponencial{
	double c;
	double a;
	double sy;
	double syx;
	double r2;
	double st;
	double sr;
};

class rls_exponencial{
public:
	regresion_exponencial calcular(vector<double>x, vector<double> y){
		vector<double> lny(y);
		
		for (unsigned int i = 0; i < lny.size(); i++){
			lny[i] = log(lny[i]);
		}
		
		rls r;
		regresion reg = r.calcular(x, lny);
		
		regresion_exponencial resultado;
		resultado.a = reg.b1;
		resultado.c = pow(2.718281828 , reg.b0);
		resultado.sy = reg.sy;
		resultado.syx = reg.syx;
		resultado.r2 = reg.r2;
		resultado.st = reg.st;
		resultado.sr = reg.sr;
		
		return resultado;
	}
};
#endif

#ifndef RLS_POTENCIA_H
#define RLS_POTENCIA_H
#include "rls.h"
#include <vector>
#include <cmath>

using std::vector;

struct regresion_potencia{
	double c;
	double a;
	double sy;
	double syx;
	double r2;
	double st;
	double sr;
};

class rls_potencia{
public:
	regresion_potencia calcular(vector<double>x, vector<double> y){
		vector<double> logx(x);
		vector<double> logy(y);
		
		for (unsigned int i = 0; i < logx.size(); i++){
			logx[i] = log10(logx[i]);
			logy[i] = log10(logy[i]);
		}
		
		rls r;
		regresion reg = r.calcular(logx, logy);
		
		regresion_potencia resultado;
		resultado.a = reg.b1;
		resultado.c = pow(10 , reg.b0);
		resultado.sy = reg.sy;
		resultado.syx = reg.syx;
		resultado.r2 = reg.r2;
		resultado.st = reg.st;
		resultado.sr = reg.sr;
		
		return resultado;
	}
};
#endif

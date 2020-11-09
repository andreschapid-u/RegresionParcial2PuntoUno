#ifndef RC_H
#define RC_H
#include <cmath>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

struct regresion_rc{
	double a0;
	double a1;
	double a2;
	double syx;
	double sy;
	double r2;
	double st;
	double sr;
};

class rc{
public:
	regresion_rc calcular(vector<double> x,
					  vector<double> y){
		
		int i;
		vector<vector<double>> m = matriz_regresion(x, y);
		
		vector<double> coeficientes = gauss(m);
		regresion_rc resultado;
		
		resultado.a0 = coeficientes[0];
		resultado.a1 = coeficientes[1];
		resultado.a2 = coeficientes[2];
		
		int n = x.size();
		double sx = 0.0;
		double sy = 0.0;
		double sxy = 0.0;
		double sx2 = 0.0;
		
		for (i = 0; i < n; i++){
			sx += x[i];
			sxy += x[i] * y[i];
			sx2 += x[i] * x[i];
			sy += y[i];
		}
		
		double ym = sy / (double)n;
		
		resultado.st = 0.0;
		resultado.sr = 0.0;
		for(i = 0; i < n; i++){
			resultado.st += pow(y[i] - ym, 2);
			resultado.sr += pow( y[i] - (resultado.a0 + resultado.a1 * x[i] + (resultado.a2 * x[i]*x[i])), 2);
		}
		
		//Calcular la desviacion estandar
		resultado.sy = sqrt(resultado.st / (double)(n - 1));
		
		//Calcular el error estandar de aproximacion
		resultado.syx = sqrt(resultado.sr / (double)(n - 3));
		
		//Calcular el coeficiente de determinacion
		resultado.r2 = (resultado.st - resultado.sr) / resultado.st;
		return resultado;
	}
private:
			vector<vector<double>> matriz_regresion(vector<double> x,
											vector<double> y){
				int n = x.size();
				
				double sx {0};
				double sx2 {0};
				double sx3 {0};
				double sx4 {0};
				double sy {0};
				double sxy {0};
				double sx2y {0};
				//Calcularlos valores que se almacenan en la matriz
				for(unsigned int i = 0; i < x.size(); i++){
					double x2 = x[i] * x[i];
					double x3 = x2 * x[i];
					double x4 = x3 * x[i];
					
					sx += x[i];
					sx2 += x2;
					sx3 += x3;
					sx4 += x4;
					
					sy += y[i];
					sxy += x[i]*y[i];
					sx2y += x2*y[i];
				}
				//Construir la matriz para la regresion
				vector<vector<double>> resultado {
					{(double)n, sx, sx2, sy}, //Primera fila
				{sx, sx2, sx3, sxy}, //Segunda fila
					{sx2, sx3, sx4, sx2y} //Tercera fila	
				};
				
				return resultado;
			}
				
				vector<double> gauss(vector<vector<double>> m){
					int i, j, k;
					int n = m.size();
					
					vector<double> resultado(n);
					
					//Eliminacion Gaussiana
					for(i = 0; i < n; i++){
						for(j = i+1; j < n; j++){
							//Valor que anula el elemento en la columna
							double v = m[j][i] / m[i][i];
							//Hacer la operacion fila[j] = fila[j] - v * fila[i]
							for (k=0; k <=n; k++){
								m[j][k] -= v* m[i][k];
							}
						}
					}
					
//					imprimir(m);
					
					//Despejar las variables
					for(i=n - 1; i >=0; i--){
						resultado[i] = m[i][n];
						//TODO reemplazar las varibles ya halladas
						for(j = i +1; j < n; j++){
							if(i != j){ //reemplazar las variables, menos el coeficiente
								resultado[i] = resultado[i] - m[i][j] * resultado[j];
							}
						}
						resultado[i] = resultado[i] / m[i][i];
					}
					
					return resultado;
				}
					
					void imprimir(vector<vector<double>> m){
						cout << "[" << endl;
						for(unsigned int i = 0; i < m.size(); i++){
							cout << "[ ";
							for(unsigned int j = 0; j < m[i].size(); j++){
								cout << m[i][j] << " ";
							}
							cout << "]" << endl;
						}
						cout << "]" << endl;
					}
};
#endif

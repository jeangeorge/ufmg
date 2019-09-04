#include "Ponto2D.hpp"
#include "Retangulo.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

Retangulo::Retangulo(Ponto2D superiorEsq,Ponto2D inferiorDir){
	this->superiorEsq.x = superiorEsq.x;
	this->superiorEsq.y = superiorEsq.y;

	this->inferiorDir.x = inferiorDir.x;
	this->inferiorDir.y = inferiorDir.y;
}


double Retangulo::calcularArea(){
	double area = fabs(this->superiorEsq.x - this->inferiorDir.x) * fabs(this->superiorEsq.y - this->inferiorDir.y);

	cout << fixed <<  setprecision(2) << area << endl;
	return area;
}

double Retangulo::calcularIntersecao(Retangulo r){
	bool intersecaoSuperiorSuperior, intersecaoSuperiorInferior;
	bool intersecaoInferiorSuperior, intersecaoInferiorInferior;

    // Abaixo faço as quatro condições lógicas para interseçao.
	intersecaoSuperiorSuperior = (this->superiorEsq.x >= r.superiorEsq.x && this->superiorEsq.y <= r.superiorEsq.y);
	intersecaoSuperiorInferior = (this->superiorEsq.x >= r.inferiorDir.x && this->superiorEsq.y <= r.inferiorDir.y);
	intersecaoInferiorSuperior = (this->inferiorDir.x >= r.superiorEsq.x && this->inferiorDir.y <= r.superiorEsq.y);
	intersecaoInferiorInferior = (this->inferiorDir.x >= r.inferiorDir.x && this->inferiorDir.y <= r.inferiorDir.y);

    // Basta que uma das condições seja satisfeita para que haja interseção
	if (intersecaoSuperiorSuperior || intersecaoSuperiorInferior || intersecaoInferiorSuperior || intersecaoInferiorInferior){
		double largura = fabs(this->superiorEsq.x - r.superiorEsq.x) - fabs(this->inferiorDir.x - r.inferiorDir.x);
		double altura = fabs(this->superiorEsq.y - r.superiorEsq.y) - fabs(this->inferiorDir.y - r.inferiorDir.y);
        double areaIntersecao = largura * altura;
        cout << fixed <<  setprecision(2) << largura << endl;
		cout << intersecaoSuperiorSuperior << endl;
		cout << intersecaoSuperiorInferior << endl;
		cout << intersecaoInferiorSuperior << endl;
		cout << intersecaoInferiorInferior << endl;
        return areaIntersecao;
	}else{
	    cout << fixed << setprecision(2) << 0 << endl;
		return 0.0;
	}
}

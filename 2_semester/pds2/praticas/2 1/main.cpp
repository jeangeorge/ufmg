#include <iostream>
#include "Ponto2D.hpp"
#include "Retangulo.hpp"

using namespace std;

int main(){
  double r1_se_x;
  double r1_se_y;
  double r1_id_x;
  double r1_id_y;

  cin >> r1_se_x >> r1_se_y >> r1_id_x >> r1_id_y;

  Ponto2D p1(r1_se_x, r1_se_y);
  Ponto2D p2(r1_id_x, r1_id_y);
  Retangulo ret1(p1,p2);
  ret1.calcularArea();


  double r2_se_x;
  double r2_se_y;
  double r2_id_x;
  double r2_id_y;

  cin >> r2_se_x >> r2_se_y >> r2_id_x >> r2_id_y;

  Ponto2D p3(r2_se_x, r2_se_y);
  Ponto2D p4(r2_id_x, r2_id_y);
  Retangulo ret2(p3,p4);
  ret2.calcularArea();
  ret1.calcularIntersecao(ret2);

  return 0;
}

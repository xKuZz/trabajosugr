#include <algorithm>
#include <iostream>
#include <functional>
#include <random>
#include <vector>
#include <tuple>

#define ID 0
#define KB 1
#define FREC 2

using namespace std;
using programa = tuple<int, long, double>;
vector<programa> generador(int N) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<> dist_kb(0,40000);
    uniform_int_distribution<> dist_prob(1,100);

  vector<programa> salida;
  vector<int> kb;
  vector<double> prob;

  kb.reserve(N);
  prob.reserve(N);
  salida.reserve(N);

  for (int i = 0; i < N; ++i) {
    kb.push_back(dist_kb(mt));
    prob.push_back(dist_prob(mt));
  }

  double total = accumulate(prob.begin(),prob.end(), 0, plus<double>());

  for (auto& d: prob)
    d /= total;

  for (int i = 0; i < N; ++i) {
     salida.emplace_back(i, kb[i], prob[i]);
     cout << get<ID>(salida[i]) << '\t' << get<KB>(salida[i]) << '\t' << get<FREC>(salida[i]) << endl;
  }

  return salida;

}

double tiempo_medio (const vector<programa> &v) {
  double tiempo = 0;
  double c = 0.000004;

  for (int i = 0; i < v.size(); ++i) {
    double sumalocal = 0;
    for (int j = 0; j <= i; ++j)
      sumalocal += get<KB>(v[j]);
    tiempo += get<FREC>(v[i]) * sumalocal;
  }

  return c * tiempo;
}

int main(int argc, char *argv[])
{
   if (argc != 2) {
     cerr << "Introducir N como argumento";
     return -1;
   }

   int N = atoi(argv[1]);
   vector<programa> inicial = generador(N);

   vector<programa> decreciente_frec(inicial);
   sort(decreciente_frec.begin(),decreciente_frec.end(), [](const programa& p1,
                                                            const programa& p2){
     return get<FREC>(p1) > get<FREC>(p2);
   });

   cout << N << " " << tiempo_medio(decreciente_frec) << endl;


}

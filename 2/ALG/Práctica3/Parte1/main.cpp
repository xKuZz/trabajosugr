#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <random>
#include <vector>
#include <tuple>

#define ID 0
#define KB 1
#define FREC 2

//Para deshabilitar comentar el define
#define MOSTRARPANTALLA 1
#define ESCRIBIRARCHIVOS 1
// Solo activar un contraejemplo a la vez
//#define CONTRAEJEMPLOTAM 1
#define CONTRAEJEMPLOFREC 1
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

  for (int i = 0; i < N; ++i)
     salida.emplace_back(i, kb[i], prob[i]);


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

#if !defined(CONTRAEJEMPLOTAM) && !defined(CONTRAEJEMPLOFREC)
   vector<programa> inicial=generador(N);
#else
   vector<programa> inicial;
   N=4;
#endif


#ifdef CONTRAEJEMPLOTAM
   inicial.emplace_back(0,10000,0.5);
   inicial.emplace_back(1,3999,0.3);
   inicial.emplace_back(2,7000,0.2);
   inicial.emplace_back(3,3000,0.1);
#endif

#ifdef CONTRAEJEMPLOFREC
   inicial.emplace_back(0,1500000,0.9);
   inicial.emplace_back(1,10000,0.03);
   inicial.emplace_back(2,100000,0.05);
   inicial.emplace_back(3,14000,0.02);
#endif

   vector<programa> creciente_tam(inicial);
   sort(creciente_tam.begin(),creciente_tam.end(), [](const programa& p1,
                                                      const programa& p2){
     return get<KB>(p1) < get<KB>(p2);
   });

   vector<programa> decreciente_frec(inicial);
   sort(decreciente_frec.begin(),decreciente_frec.end(), [](const programa& p1,
                                                            const programa& p2){
     return get<FREC>(p1) > get<FREC>(p2);
   });

   vector<programa> decreciente_div(inicial);
   sort(decreciente_div.begin(),decreciente_div.end(), [](const programa& p1,
                                                      const programa& p2){
     return (get<FREC>(p1)/get<KB>(p1)) > (get<FREC>(p2) /get<KB>(p2));
   });

#ifdef MOSTRARPANTALLA
   cout << "Para " << N << " programas."                          << endl;
   cout << "Aleatorio: "        << tiempo_medio(inicial)          << endl;
   cout << "Creciente tam: "    << tiempo_medio(creciente_tam)    << endl;
   cout << "Decreciente frec: " << tiempo_medio(decreciente_frec) << endl;
   cout << "Decreciente div: "  << tiempo_medio(decreciente_div)  << endl;
#endif

#ifdef ESCRIBIRARCHIVOS
   ofstream random ("aleatorio.dat",       ofstream::app);
   ofstream crectam("crecientetam.dat",    ofstream::app);
   ofstream decfrec("decrecientefrec.dat", ofstream::app);
   ofstream decdiv ("decrecientediv.dat",  ofstream::app);

   random  << N << " " << tiempo_medio(inicial)          << endl;
   crectam << N << " " << tiempo_medio(creciente_tam)    << endl;
   decfrec << N << " " << tiempo_medio(decreciente_frec) << endl;
   decdiv  << N << " " << tiempo_medio(decreciente_div)  << endl;
#endif

#if defined(CONTRAEJEMPLOTAM) || defined(CONTRAEJEMPLOFREC)
  cout << "INICIAL " << '\t';
  for (auto t : inicial)
    cout << get<ID>(t) << '\t';
  cout << endl << "CRECIENTE TAM" << '\t';
  for (auto t : creciente_tam)
    cout << get<ID>(t) << '\t';
  cout << endl << "DECRECIENTE FRE" << '\t';
  for (auto t : decreciente_frec)
    cout << get<ID>(t) << '\t';
  cout << endl << "DECRECIENTE DIV" << '\t';
  for (auto t : decreciente_div)
    cout << get<ID>(t) << '\t';
  cout << endl << endl << "MUESTRA" << endl;
  for (auto t: inicial)
    cout << get<ID>(t) << '\t' << get<KB>(t) << '\t' << get<FREC>(t) << endl;
#endif






}

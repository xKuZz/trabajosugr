#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <random>
#include "avl.h"
using namespace std;

void probar_orden (){
  AVL<int> arbolito;
  random_device rd;
  mt19937 generador(rd());
  uniform_int_distribution<int> entero(0, 1000);
  vector<int> copia;
  copia.reserve(1000);
  for (int i = 0; i< 2000; ++i) {
    int numero = entero(generador);
    arbolito.insert(numero);
    if (i < 30)
      copia.push_back(numero);
  }

  for (auto d: copia)
    arbolito.erase(d);
  for (auto it = arbolito.rbegin(); it != arbolito.rend(); ++it)
      cout << *it << endl;
  for (auto d: arbolito)
    cout << d << endl;
  cout << arbolito.size() << endl;

}

void rotar_simple_izquierda() {
  AVL<int> arbolito{9,5,12,10,13,14};
  for (auto d: arbolito)
    cout << d << endl;
  cout << arbolito.size() << endl;
}

void rotar_simple_derecha() {
  AVL<int> arbolito{9, 5, 10, 4, 6 , 1};
  for (auto d: arbolito)
    cout << d << endl;
  cout << arbolito.size() << endl;
}

void rotar_doble_izquierda() {
  AVL<int> arbolito{9,5,12,10,13,11};
  for (auto d: arbolito)
    cout << d << endl;
  cout << arbolito.size() << endl;
}

void rotar_doble_derecha() {
  AVL<int> arbolito{9,5,10,1,7,6};
  for (auto d: arbolito)
    cout << d << endl;
  cout << arbolito.size() << endl;
}

void check_erase(){
  AVL<int> arbolito{9,5,12,11,13};
  arbolito.erase(13);
  arbolito.erase(11);

  for (auto d: arbolito)
    cout << d << endl;
  cout << arbolito.size() << endl;
}


string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

void check()  {
    set<string, greater<string>> conjunto;
    AVL<string, greater<string>> arbol;
    set<string, greater<string>> eliminar;
    random_device rd;
    mt19937 generador(rd());
    uniform_int_distribution<int> entero(0, 1000);
    for (int i = 0; i< 1000; ++i) {
      string numero = random_string(10);
      arbol.insert(numero);
      conjunto.insert(numero);
      if (numero[0]=='z')
        eliminar.insert(numero);
    }

    for (auto d : eliminar) {
      arbol.erase(d);
      conjunto.erase(d);
    }

    auto it_a = arbol.begin();
    for (auto it_c = conjunto.begin();
              it_a != arbol.end();
              ++it_a, ++it_c)
        assert(*it_c == *it_a);


    for (auto d: eliminar) {
      auto it_l = arbol.lower_bound(d);
      auto it_f = arbol.find(d);
      auto it_fs = conjunto.find(d);
      auto it_u = arbol.upper_bound(d);
      auto it_us = conjunto.upper_bound(d);
      auto it_ls = conjunto.lower_bound(d);
      if (it_l != arbol.end())
        assert(*it_l == *it_ls);
      else
        assert(it_ls == conjunto.end());
      if (it_f != arbol.end())
          assert(*it_f == *it_fs);
      else
          assert(it_fs == conjunto.end());
      if (it_u != arbol.end())
        assert(*it_u == *it_us);
      else
        assert(it_us == conjunto.end());
    }
    auto it1 = arbol.rbegin();
    auto it2 = conjunto.rbegin();
    for (;it2 != conjunto.rend(); ++it1, ++ it2)
      assert (*it1 == *it2);
    cout << "Bien" << endl;
}

void prueba_find_bounds() {
  AVL<int> arbolito{1,3,5,6};
  auto it = arbolito.find(3);
  cout << "BUSCANDO 3 - FIND |LOWER BOUND | UPPER BOUND " << endl;
  cout << *it << endl;
  it = arbolito.lower_bound(3);
  cout << *it << endl;
  it = arbolito.upper_bound(3);
  cout << *it << endl;
  it = arbolito.find(0);
  cout << "BUSCANDO 0 (NO ESTA) - LOWER BOUND | UPPER BOUND |FIND" << endl;
  if (it == arbolito.end())
    cout << "NO ESTA" << endl;
  it = arbolito.lower_bound(0);
  cout << *it << endl;
  it = arbolito.upper_bound(0);
  cout << *it << endl;
}


int main() {
  check();
}

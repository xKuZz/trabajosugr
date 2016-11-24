#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include "css.h"
using namespace std;

template<class Iterator>
void iterar(Iterator begin, Iterator end){
    for (auto it=begin;it!=end; ++it)
        cout << it->second << endl;
}

template<class Iterator>
void iterar_hacia_atras(Iterator begin, Iterator end){
    assert(begin != end);
    auto it=--end;
    for (;it!=begin;--it)
        cout << it->second << endl;
    cout << it->second << endl;
}

int main(){
  CSS test;
  test.load("crimenes.csv");
  vector<int> ids;
  list <string> queryWords { "BATTERY", "RETAIL", "WEAPON" };

  auto v =test.Query(queryWords,30);
  for (auto p: v)
      cout << p.first << " | " << p.second << " | "
           << test.find_ID(p.first)->second.getDESCR() << endl;
  for (auto &p : test)
      ids.push_back(p.first);

  for (auto id: ids)
      test.erase(id);

  test.load("crimenes.csv");
  auto it=test.find_ID(10233462);
  cout << "ID" << endl << endl;
  iterar(it,test.end());
  cout << "ID hacia atras" << endl << endl;
  iterar_hacia_atras(test.begin(),it);
  cout << "Fecha" << endl << endl;
  iterar(test.dbegin(),test.dend());
  cout << "IUCR hacia atrás" << endl << endl;
  iterar_hacia_atras(test.ibegin(),test.iend());
}

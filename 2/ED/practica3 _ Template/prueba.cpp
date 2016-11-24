
#include "fecha.h"
#include "crimen.h"
#include "conjunto.h"
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <chrono>

using namespace std;
using namespace std::chrono;

	/** @brief lee un fichero de delitos, linea a linea
	@param[in] s nombre del fichero
        @param[in,out] C conjunto sobre el que se lee
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

template<class CMP>
bool load(conjunto<CMP> &C, const string &s) {
 ifstream fe;
 string cadena;
 crimen aux;

 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);
 if (fe.fail())
 {
   cerr << "Error al abrir el fichero " << s << endl;
 } else {
   getline(fe,cadena,'\n'); //leo la cabecera del fichero
   cout << cadena << endl;
    while ( !fe.eof())
      { getline(fe,cadena,'\n');
       	if (!fe.eof()) {
           cout << "leo:: "<< cadena << endl;
           aux=cadena;
           C.insert(aux);
        }
     }
    fe.close();
    return true;
    } // else
  fe.close();
  return false;
 }

constexpr int lecturas=40; // Nº de lecturas para el test
template<class CMP>
bool cargatest(conjunto<CMP> &C,crimen &guardar) {
 ifstream fe;
 string cadena;
 crimen aux;
 int i=0;

 cout << "Abrimos " << endl;
 fe.open("/home/david/Escritorio/ED/Prácticas/crimenes.csv", ifstream::in);
 if (fe.fail())
 {
   cerr << "Error al abrir el fichero " << endl;
 } else {
   getline(fe,cadena,'\n'); //leo la cabecera del fichero
   cout << cadena << endl;
    while ( !fe.eof() && i<lecturas)
      { getline(fe,cadena,'\n');
        if (!fe.eof()) {
           cout << "leo:: "<< cadena << endl;
           aux=cadena;
           C.insert(aux);
           i++;
        }
     }
    fe.close();
    guardar=aux;
    return true;
    } // else
  fe.close();
  return false;
 }
class crecienteID{
  public:
    bool operator()(const crimen &a, const crimen &b) const {
        return a.getID()>b.getID();
    }
};

class decrecienteID{
  public:
    bool operator()(const crimen &a, const crimen &b) const {
        return a.getID()>b.getID();
    }
};

class crecienteFecha{
    public:
        bool operator()(const crimen &a, const crimen &b) const {
            return a.getDate()<b.getDate();
    }
};

class decrecienteFecha{
    public:
        bool operator()(const crimen &a, const crimen &b) const {
             return a.getDate()>b.getDate();
    }
};

class crecienteIUCR{
    public:
        bool operator()(const crimen &a, const crimen &b) const {
                return a.getIUCR()<b.getIUCR();
    }
};


int main()
{
    conjunto<decrecienteFecha> A;
    crimen C;
    load(A,"/home/david/Escritorio/ED/Prácticas/crimenes.csv");
    conjunto<crecienteFecha> B(A.begin(),A.end());

    auto it=B.find(C);
    if (it!=B.end())
        cout << "ENCONTRADO:" << endl << *it << endl;
    else cout << "NO ENCONTRADO.\n";
    B.erase(C);
    it=B.find(C);
    if (it!=B.end())
        cout << "ENCONTRADO:" << endl << *it << endl;
    else cout << "NO ENCONTRADO.\n";
    for (auto &it2 : B){
        cout << it2 << endl;
    }
    cout << B << endl;

}


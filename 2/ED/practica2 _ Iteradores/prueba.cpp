
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


bool load(conjunto &  C, const string & s) {
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

int main()
{
  conjunto DatosChicago, agresion;
  load(DatosChicago,"crimenes.csv");
  conjunto::const_iterator encontrar;
  auto cdit=DatosChicago.aend();
  cdit--;
  for (auto cit=DatosChicago.abegin(); cit!=DatosChicago.aend();++cit)
      cout << *cit << endl;
  for (auto dit=DatosChicago.cdbegin("BATTERY"); dit!=DatosChicago.cdend();++dit)
      cout << *dit << endl;

  encontrar=DatosChicago.find(10229167);

  if (encontrar!=DatosChicago.cend())
      cout << "ENCONTRADO: " << *encontrar << endl;
  else
      cout << "NO HAY CRIMEN CON DICHA ID." << endl;
}

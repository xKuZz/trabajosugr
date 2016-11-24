
#include "fecha.h"
#include "crimen.h"
#include "conjunto.h"
#include <iostream>
#include <string>
#include <fstream>
#include <utility>

using namespace std;

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
    while ( !fe.eof() )
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
  pair<crimen,bool> encontrar;
  load(DatosChicago,"/home/david/Dropbox/Yoquesé/practica2/crimenes.csv");

  encontrar=DatosChicago.find(10230953);
  if (encontrar.second)
      DatosChicago.erase(10230953);

  encontrar=DatosChicago.find(10230953);
  if (encontrar.second)
      cout << "Erase no funciona.\n";
  else
      cout << "Erase sí funciona.\n";

  agresion = DatosChicago.findDESCR("BATTERY");
  if (!agresion.empty()){
   cout << agresion << endl;
   cout <<"Tenemos "<< agresion.size() << " agresiones" << endl;
  } else
   cout << "No hay agresiones en el conjunto" << endl;
}

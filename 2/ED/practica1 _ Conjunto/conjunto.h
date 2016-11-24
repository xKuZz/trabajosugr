/**
  * @file conjunto.h
  * @brief Declaración de la clase conjunto.
  * @author Alejandro Campoy Nieves
  * @author David Criado Ramón
  */

#ifndef __CONJUTO_H
#define __CONJUTO_H
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

#include "crimen.h"

using namespace std;


//! Clase conjunto
/*! Métodos--> conjunto:: conjunto(), insert(), find(),  findIUCR(), findDESCR(), erase(), size(), empty()

 * Tipos--> conjunto::entrada, conjunto::size_type

 * Descripción

* Un conjunto es un contenedor que permite almacenar en orden creciente un conjunto de elementos no repetidos.  En nuestro caso el conjunto va a tener un subconjunto restringido de métodos (inserción de elementos, consulta de un elemento, etc). Este conjunto "simulará" un conjunto de la stl, con algunas claras diferencias pues, entre otros,  no estará dotado de la capacidad de iterar (recorrer) a través de sus elementos.

* Asociado al conjunto, tendremos el tipo  \code conjunto::entrada \endcode que permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto, en nuestro caso delitos (crimenes). Para esta entrada el requisito es que tenga definidos el operador< y operator=

* Además encontraremos el tipo \code conjunto::size_type \endcode que permite hacer referencia al número de elementos en el conjunto.

* El número de elementos en el conjunto puede variar dinámicamente; la gestión de la memoria es automática.

 Ejemplo de su uso:
\code
...
conjunto DatosChicago, agresion;
crimen cr;

conjunto.insert(cr);
...
agresion = conjunto.findDESCR("BATTERY");

if (!agresion.empty()){
 cout <<"Tenemos "<< agresion.size() << " agresiones" << endl;
 cout << agresion << endl;
} else "No hay agresiones en el conjunto" << endl;
...
\endcode
 */





class conjunto
{
public:
    /** @brief entrada permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto
    */
	typedef crimen entrada;
	/** @brief size_type numero de elementos en el conjunto
         */
	typedef unsigned int size_type;
    /**
     @brief Constructor por defecto de la clase conjunto (Conjunto vacio).
    */
	conjunto( );


    /**
     * @brief Constructor de copia.
     * @d Conjunto a copiar.
     */
    conjunto (const conjunto &d);

    /**
     * @brief Busca una entrada dada su id en el conjunto.
     * @param id ID del crimen a buscar.
     * @return Par (crimen,verdadero) si se encuentra o (--,falso) si no se encuentra.
     \verbatim Uso
     if (C.find(12345).second ==true) cout << "Esta" ;
     else cout << "No esta";
     \endverbatim
     */
	pair<conjunto::entrada,bool>  find( const long int & id) const;

    /**
     * @brief Devuelve un conjunto con todos los crímenes con el mismo IUCR.
     * @param iucr IUCR a buscar.
     * @return Conjunto con crímenes con el IUCR proporcionado.
     \verbatim Uso
        conjunto C, A;
        ....
        A = C.findIUCR("0460");
     \endverbatim
     */

    conjunto findIUCR(const string &iucr) const;

    /**
     * @brief Devuelve un conjunto con todos los crímenes con la misma descripción
     * @param descr Descripción a buscar
     * @return Conjunto con todos los crímenes con la descripción proporcionada.
     \verbatim Uso
        conjunto C, A;
        ....
        A = C.findDESCR("BATTERY");
     \endverbatim
     */
    conjunto findDESCR(const string &descr) const;

    /**
     * @brief Inserta una entrada en la posición apropiada del conjunto.
     * @param e Crimen a introducir.
     * @return Si se ha insertado correctamente o no (ya existía un crimen con dicha ID).
     */
    bool insert(const conjunto::entrada &e);



    /**
     * @brief Elimina un elemento del conjunto dado su identificador.
     * @param id ID de la entrada a eliminar del conjunto.
     * @return True si se ha podido eliminar, false en caso contrario (no se encontró un crimen con esa id).
     */

    bool erase(const long int &id);

    /**
     * @brief Elimina un elemento del conjunto dado un crimen.
     * @param e Crimen a eliminar en el conjunto.
     * @return True si se ha podido eliminar, false en caso contrario (no se encontró el crimen).
     */

    bool erase(const conjunto::entrada &e);


    /**
     * @brief Sobrecarga del operador de asignación.
     * @param org Conjunto a asignar.
     * @return Referencia al objeto de la clase (this).
     */
    conjunto & operator=(const conjunto &org);

    /**
     * @brief Devuelve el tamaño del conjunto
     * @return Tamaño del conjunto
     */
	size_type size() const ;


    /**
     * @brief Comprueba si el conjunto está vacío.
     * @return True si el conjunto está vacío, false en caso contrario.
     */
	bool empty() const;

   
private:
 vector<crimen> vc; // vector ORDENADO por crimen.id que almacena los elementos del conjunto
 /** \invariant

 IR: rep ==> bool

\li Para todo i, 0 <= i < vc.size() se cumple
	vc[i].ID > 0;
\li Para todo i, 0 <= i <= D.dic.size()-1 se cumple
	vc[i].ID< vc[i+1].ID

*/


  /**
   * @brief Comprueba el invariante de la representación de la clase conjunto.
   * @return True si se cumple el invariante, false en caso contrario.
   */
  bool cheq_rep( ) const;

//  declaracion del operator<< como metodo amigo
  friend ostream &  operator << ( ostream & sal, const conjunto & D);
  // Clases amigas  ....


};


/**
 * @brief Sobrecarga del operador de extracción de flujos para la clase conjunto.
 * @param sal Flujo de salida.
 * @param D Conjunto a mostrar.
 * @return Referencia al flujo de salida.
 */
ostream &  operator << ( ostream & sal, const conjunto & D);

#include "conjunto.hxx"

#endif

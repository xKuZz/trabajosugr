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
#include <iterator>
#include <cassert>

#include "crimen.h"

using namespace std;

/** @brief Clase Conjunto.
 *  @tparam CMP Relación de orden a ser utilizada.
 *
 *  Conjunto es una clase que permite almacenar múltiples crímenes utilizando
 *  la relación de orden proporcionada por CMP
 */
template <class CMP>
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
    conjunto<CMP>( );


    /**
     * @brief Constructor de copia.
     * @d Conjunto a copiar.
     */
    conjunto<CMP> (const conjunto<CMP> &d);



    /** @brief Construye un %conjunto con los elementos definidos en [ini,fin)
      * @param ini Iterador inicial del conjunto a copiar
      * @param fin Iterador final (posición siguiente a final) del conjunto a copiar
      *
      * Construye un %conjunto, cogiendo los crímenes definidos en el rango [int,fin)
      * y aplicándoles el nuevo criterio de comparación CMP.
      */
    template <class InputIterator>
    conjunto<CMP> (const InputIterator &ini, const InputIterator &fin);
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

    conjunto<CMP> findIUCR(const string &iucr) const;

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
    conjunto<CMP> findDESCR(const string &descr) const;

    /**
     * @brief Inserta una entrada en la posición apropiada del conjunto.
     * @param e Crimen a introducir.
     * @return Si se ha insertado correctamente o no (ya existía un crimen con dicha ID).
     */
    void insert(const crimen &e);



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

    bool erase(const crimen &e);


    /**
     * @brief Sobrecarga del operador de asignación.
     * @param org Conjunto a asignar.
     * @return Referencia al objeto de la clase (this).
     */
    conjunto<CMP>& operator=(const conjunto<CMP> &org);

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

    // ================================= ITERADORES ========================================/


    /** @brief class iterator
         * Iterador bidireccional sobre el conjunto (SOLO LECTURA)
         * */
        class iterator {
          public:
           /** @brief Constructor por defecto.
             */
           iterator();
           /** @brief Constructor de copia.
            *  @param[in] it Conjunto::iterator a copiar
            */
           iterator (const iterator & it);

           /** @brief Operador de dereferencia.
            *  @return Devuelve el crimen al que apuntaba el iterador.
            */
           const conjunto<CMP>::entrada& operator*();

           /** @brief Operador de postincremento. Avanza al siguiente elemento del conjunto.
            *  @return Devuelve una copia del iterador antes del incremento.
            */
           iterator operator++(int);
           /** @brief Operador de preincremento. Avanza al siguiente elemento del conjunto.
            *  @return Devuelve una copia del iterador a despues del incremento.
            */
           iterator& operator++();
           /** @brief Operador de postdecremento. Retrocede al elemento anterior del conjunto.
            *  @return Devuelve una copia del iterador antes del decremento.
            */
           iterator operator--(int);
           /** @brief Operador de predecremento. Retrocede al elemento anterior del conjunto.
            *  @return Devuelve una copia del iterador despues del decremento.
            */
           iterator& operator--();
           /** @brief Operador de igualdad. Comprueba que dos iteradores apuntan al mismo elemento.
            *  @return True si son iguales, false si son distintos.
            */
           bool operator==(const iterator &it);
           /** @brief Operador de desigualdad. Comprueba que dos iteradores no apuntan al mismo elemento.
            *  @return True si son distintos, false si son iguales.
            */
           bool operator!=(const iterator &it);

           private:
               friend class conjunto;
               vector<entrada>::iterator itv;
    };
        /** @brief Devuelve iterador al inicio del conjunto.
        */
        iterator begin();

        /** @brief Devuelve iterador al final (posición siguiente al último del conjunto).
        */
        iterator end();

        /** @brief
             @return Devuelve el const_iterator a la primera posición del conjunto.
        @post no modifica el diccionario
            */

        /** @brief class const_iterator
         *  Iterador bidireccional sobre el conjunto. SOLO LECTURA
         * */
        class const_iterator {
        public:
          /** @brief Constructor por defecto.
           */
          const_iterator();
          /** @brief Constructor de copia.
           *  @param[in] it const_iterator a copiar.
           */
          const_iterator(const const_iterator &it);
          /** @brief Convierte iterator en const_iterator
           *  @param[in] it iterator a copiar
           */
          const_iterator(const iterator &it);
          /** @brief Operador de dereferencia
           *  @return Devuelve el crimen al que apunta el iterador
           */
          const conjunto<CMP>::entrada& operator*() const;

          /** @brief Operador de postincremento. Avanza al siguiente crimen del conjuto.
           *  @return Devuelve copia del const_iterator antes del incremento.
           */
          const_iterator operator++( int );
          /** @brief Operador de preincremento. Avanza al siguiente crimen del conjuto.
           *  @return Devuelve copia del const_iterator despues del incremento.
           */
          const_iterator& operator++();
          /** @brief Operador de postdecremento. Retrocede al crimen anteriordel conjuto.
           *  @return Devuelve copia del const_iterator antes del decremento.
           */
          const_iterator operator--(int);
          /** @brief Operador de predecremento. Retrocede al crimen anterior del conjuto.
           *  @return Devuelve copia del const_iterator despues del decremento.
           */
          const_iterator& operator--();

          /** @brief Operador de igualdad. Compara si ambos const_iterator apuntan al mismo dato.
           *  @return True si es el mismo, false en caso contrario.
           */
          bool operator==(const const_iterator &it);
          /** @brief Operador de desigualdad. Compara si ambos const_iterator apuntan al mismo dato.
           *  @return True si es distinto, false si son iguales.
           */
          bool operator!=(const const_iterator &it);
        private:

          vector<entrada>::const_iterator c_itv;
          friend class conjunto;

        };
        /** @brief Iterador constante al inicio.
         *  @return Devuelve el iterador constante a la posición inicial del conjunto.
         *  @post No modifica el conjunto.
        */
        const_iterator cbegin() const;
        /** @brief Iterador constante al final
         *  @return Devuelve el iterador constante a la posición final del conjunto.
         *  @post No modifica el conjunto.
         */
        const_iterator cend() const;
        /** @brief Busca el crimen con dicha ID en el conjunto.
         *  @return Iterador costante al crimen si se encuentra, cend si no.
         *  @post No modifica el conjunto.
         *
         *  Este método utiliza la búsqueda secuencial para buscar el elemento x
         *  tal que x.ID=id, depediendo del éxito de su búsqueda se devolverá iterador
         *  a dicho crimen o el iterador cend(), es decir la posición siguiente a la
         *  final del conjunto
         */
        const_iterator find(const long int &id) const;

        /** @brief Busca el crimen dado en el conjunto
         *  @return Iterador al crimen si se encuentra, end si no.
         */
        iterator find(const crimen &c);
        /** @brief Busca la posicion donde esta o deberia insertarse el crimen.
         *  @return Iterador al posicion donde estaria el crimen.
         */
        iterator lower_bound(const crimen &c);
        /** @brief Busca la posicion siguiente a donde deberia encontrarse el crimen
         *  @return Iterador a la supuesta posicion siguiente a la del crimen.
         */
        iterator upper_bound(const crimen &c);
        /** @brief Busca el crimen dado en el conjunto
         *  @return Iterador al crimen si se encuentra, end si no.
         *  @post No modifica el conjunto.
         */
        const_iterator find (const crimen &c) const;
        /** @brief Busca la posicion donde deberia estar el crimen.
         *  @return Iterador al posicion donde estaria el crimen.
         *  @post No modifica el conjunto.
         */
        const_iterator lower_bound(const crimen &c) const;
        /** @brief Busca la posicion siguiente a donde deberia encontrarse el crimen
         *  @return Iterador a la supuesta posicion siguiente a la del crimen.
         *  @post No modifica el conjunto.
         */
        const_iterator upper_bound(const crimen &c) const;




private:
 CMP comp;
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
  template <class CMP1>
  friend ostream &  operator << ( ostream & sal, const conjunto<CMP1> & D);
  // Clases amigas  ....
      friend class iterator;
      friend class const_iterator;


};


/**
 * @brief Sobrecarga del operador de extracción de flujos para la clase conjunto.
 * @param sal Flujo de salida.
 * @param D Conjunto a mostrar.
 * @return Referencia al flujo de salida.
 */
template<class CMP>
ostream &  operator << (ostream & sal, const conjunto<CMP> & D);

#include "conjunto.hxx"

#endif

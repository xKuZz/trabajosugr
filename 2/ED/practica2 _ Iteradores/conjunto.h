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


    //pair<conjunto::entrada,bool>  find( const long int & id) const;
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
           const conjunto::entrada& operator*();

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
          const conjunto::entrada& operator*() const;

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
         *  @return Devuelve el iterador constante a la  posición inicial del conjunto.
         *  @post No modifica el conjunto.
        */
        const_iterator cbegin() const;
        /** @brief Iterador constante al final
         *  @return Devuelve el iterador constante a la  posición final del conjunto.
         *  @post No modifica el conjunto.
         */
        const_iterator cend() const;
            // ============================== arrest iterator ===============================
        /** @brief Iterador bidireccional que se mueve entre crimenes que implican arresto. SÓLO LECTURA
         */
        class arrest_iterator {
        public:
            /** @brief Constructor por defecto.
             */
            arrest_iterator();
            /** @brief Constructor de copia.
             *  @param[in] it Iterador a copiar.
             */
            arrest_iterator(const arrest_iterator &it);
            /** @brief Dereferencia el iterador.
             */
            const conjunto::entrada& operator*();
            /** @brief Operador de postincremento. Avanza al siguiente crimen con arresto
             *  @return Devuelve copia del iterador antes del incremento.
             */
            arrest_iterator operator++(int);
            /** @brief Operador de preincremento. Avanza al siguiente crimen con arresto
             *  @return Iterador después del incremento.
             */
            arrest_iterator& operator++();
            /** @brief Operador de postdecremento. Retrocede al crimen con arresto anterior.
             *  @pre El iterador no debe estar en conjunto::begin()
             *  @return Devuelve copia del iterador antes del incremento.
             */
            arrest_iterator operator--(int);
            /** @brief Operador de predecremento. Retrocede al crimen con arresto anterior.
             *  @pre El iterador no debe estar en conjunto::begin()
             *  @return Iterador antes del incremento.
             */
            arrest_iterator& operator--();

            /** @brief Operador de igualdad. Compara si ambos const_iterator apuntan al mismo dato.
             *  @return True si es el mismo, false en caso contrario.
             */
            bool operator==(const arrest_iterator &it);
            /** @brief Operador de desigualdad. Compara si ambos const_iterator apuntan al mismo dato.
             *  @return True si es distinto, false si son iguales.
             */
            bool operator!=(const arrest_iterator &it);
        private:
            vector<entrada>::iterator itv;
            conjunto *ptr;
            friend class conjunto;
        };
        /** @brief Devuelve el arrest_iterator al primer arresto del conjunto
         *  @return arrest_iterator al primer arresto del conjunto, aend() en caso de no haber ningún arresto.
         */
        arrest_iterator abegin();

        /** @brief Devuelve el arrest_iterator a la posición siguiente a la final del conjunto
         *  @return arrest_iterator a la posición siguiente a la final del conjunto
         */
        arrest_iterator aend();
        // ============================== const arrest iterator ===============================
    /** @brief Iterador constante bidireccional que se mueve entre los crimenes con arresto.
     */

    class const_arrest_iterator {
    public:
        /** @brief Constructor por defecto.
         */
        const_arrest_iterator();
        /** @brief Constructor de copia.
         *  @param[in] it const_arrest_iterator a copiar
         */
        const_arrest_iterator(const const_arrest_iterator &it);
        /** @brief Operador de dereferencia. Accede al crimen al que apunta el iterador.
         *  @post No modifica el conjunto.
         *  @return Crimen al que apunta el conjunto.
         */
        const conjunto::entrada& operator*() const;
        /** @brief Operador de postincremento. Avanza al siguiente crimen con arresto
         *  @return Devuelve copia del iterador antes del incremento.
         */
        const_arrest_iterator operator++(int);
        /** @brief Operador de preincremento. Avanza al siguiente crimen con arresto
         *  @return Iterador después del incremento.
         */
        const_arrest_iterator& operator++();
        /** @brief Operador de postdecremento. Retrocede al crimen con arresto anterior.
         *  @pre El iterador no debe estar en conjunto::begin()
         *  @return Devuelve copia del iterador antes del incremento.
         */
        const_arrest_iterator operator--(int);
        /** @brief Operador de predecremento. Retrocede al crimen con arresto anterior.
         *  @pre El iterador no debe estar en conjunto::begin()
         *  @return Iteradordespues antes del incremento.
         */
        const_arrest_iterator& operator--();

        /** @brief Operador de igualdad. Compara si ambos const_iterator apuntan al mismo dato.
         *  @return True si es el mismo, false en caso contrario.
         */
        bool operator==(const const_arrest_iterator &it);
        /** @brief Operador de desigualdad. Compara si ambos const_iterator apuntan al mismo dato.
         *  @return True si es distinto, false si son iguales.
         */
        bool operator!=(const const_arrest_iterator &it);
    private:
        vector<entrada>::const_iterator c_itv;
        const conjunto *ptr;
        friend class conjunto;
    };
    /** @brief const_arrest_iterator al primer arresto del conjunto.
     *  @post No modifica el conjunto.
     *  @return Iterador constante al primer arresto del conjunto. conjunto::caend() en caso de no haber arrestos.
     */
    const_arrest_iterator cabegin() const;
    /** @brief const_arrest_iterator al final del conjunto
     *  @post No modifica el conjunto.
     *  @return Iterador constante a la posición siguiente a la última del conjunto.
     */
    const_arrest_iterator caend() const;

            // ============================== description iterator ===============================

        /** @brief Iterador que se mueve sobre los crimenes cuya descripcion contiene la cadena dada
         *  al iterador al ser creado con dbegin. SOLO LECTURA
         */
        class description_iterator {
        public:
          /** @brief Constructor por defecto.
           */
          description_iterator();
          /** @brief Constructor de copia.
           *  @param[in] it description_iterator a copiar
           */
          description_iterator(const description_iterator &it);
          /** @brief Operador de dereferencia. Accede al crimen al que apunta el iterador
           *  @return Crimen constante al que apunta el iterador
           */
          const conjunto::entrada& operator*();
          /** @brief Operador de postincremento. Avanza al siguiente crimen que contiene la descripcion.
           *  @return Copia del iterador antes de avanzar.
           */
          description_iterator operator++( int );
          /** @brief Operador de preincremento. Avanza al siguiente crimen que contiene la descripcion.
           *  @return Iterador despues de avanzar.
           */
          description_iterator& operator++();
          /** @brief Operador de postdecremento. Retrocede al crimen anterior que contiene la descripcion.
           *  @pre El iterador debe ser disinto de conjunto::dbegin()
           *  @return Copia del iterador antes de retroceder.
           */
          description_iterator operator--(int);
          /** @brief Operador de predecremento. Retrocede al crimen anterior que contiene la descripcion.
           *  @pre El iterador debe ser disinto de conjunto::dbegin()
           *  @return Iterador despues de retroceder.
           */
          description_iterator& operator--();

          /** @brief Operador de igualdad. Compara si ambos const_iterator apuntan al mismo dato.
           *  @return True si es el mismo, false en caso contrario.
           */
          bool operator==(const description_iterator &it);
          /** @brief Operador de desigualdad. Compara si ambos const_iterator apuntan al mismo dato.
           *  @return True si es distinto, false si son iguales.
           */
          bool operator!=(const description_iterator &it);
        private:
          string descr;  // la descripcion se asigna en con el metodo dbegin
          vector<entrada>::iterator itv;
          friend class conjunto;
          conjunto *ptr;

        };


        /**   @brief devolver primera posicion del elemento que empareja con la descripcion descr
        @param[in] descr descripcion de buscamos
        @return un iterador que apunta a la primera posicion, el emparejamiento se hace teniendo en cuenta que descr debe ser una subcadena de la descripción del delito.
        */
        description_iterator  dbegin(const string &descr);

         /**   @brief devolver fin del conjunto

        @return un iterador que apunta a la posicion final
        */
        description_iterator  dend();



        // ============================== description iterator ===============================

    class const_description_iterator {
        typedef ptrdiff_t  difference_type;
    public:
      /** @brief Constructor por defecto.
       */
      const_description_iterator();
      /** @brief Constructor de copia.
       *  @param[in] it const_description_iterator a copiar
       */
      const_description_iterator(const const_description_iterator &it);
      /** @brief Operador de dereferencia. Accede al crimen al que apunta el iterador
       *  @post No modifica el conjunto.
       *  @return Crimen constante al que apunta el iterador.
       */
      const conjunto::entrada& operator*() const;
      /** @brief Operador de postincremento. Avanza al siguiente crimen que contiene la descripcion.
       *  @return Copia del iterador antes de avanzar.
       */
      const_description_iterator operator++( int );
      /** @brief Operador de preincremento. Avanza al siguiente crimen que contiene la descripcion.
       *  @return Iterador despues de avanzar.
       */
      const_description_iterator& operator++();
      /** @brief Operador de postdecremento. Retrocede al crimen anterior que contiene la descripcion.
       *  @return Copia del iterador antes de retroceder.
       */
      const_description_iterator operator--(int);
      /** @brief Operador de predecremento. Retrocede al crimen anterior que contiene la descripcion.
       *  @pre El iterador debe ser disinto de conjunto::cdbegin()
       *  @return Iterador despues de retroceder.
       */
      const_description_iterator& operator--();

      /** @brief Operador de igualdad. Compara si ambos const_iterator apuntan al mismo dato.
       *  @pre El iterador debe ser disinto de conjunto::cdbegin()
       *  @return True si es el mismo, false en caso contrario.
       */
      bool operator==(const const_description_iterator &it);
      /** @brief Operador de desigualdad. Compara si ambos const_iterator apuntan al mismo dato.
       *  @return True si es distinto, false si son iguales.
       */
      bool operator!=(const const_description_iterator &it);
    private:
      string descr;  // la descripcion se asigna en con el metodo dbegin
      vector<entrada>::const_iterator c_itv;
      friend class conjunto;
      const conjunto *ptr;
    };

    /**   @brief devolver primera posicion del elemento que empareja con la descripcion descr
    @param[in] descr descripcion de buscamos
    @post No modifica el conjunto.
    @return un iterador que apunta a la primera posicion, el emparejamiento se hace teniendo en cuenta que descr debe ser una subcadena de la descripción del delito.
    */
    const_description_iterator cdbegin(const string &descr) const;
    /**   @brief devolver fin del conjunto
          @post No modifica el conjunto.
          @return un iterador que apunta a la posicion final
   */
    const_description_iterator cdend() const;
    /**
     * @brief Busca una entrada dada su id en el conjunto.
     * @param id ID del crimen a buscar.
     * @return Iterador al crimen con dicha id o conjunto::cend() si no esta.
     \verbatim Uso
     if (C.find(12345)!=C.cend()) cout << "Esta" ;
     else cout << "No esta";
     \endverbatim
     */
     const_iterator find(const long int &id) const;
private:
 const_iterator binarysearch(const long int &id) const;
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
      friend class iterator;
      friend class const_iterator;
      friend class description_iterator;
      friend class arrest_iterator;
      friend class const_description_iterator;
      friend class const_arrest_iterator;


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

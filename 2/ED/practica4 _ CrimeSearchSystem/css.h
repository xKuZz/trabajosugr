#ifndef CSS_H
#define CSS_H

#include "fecha.h"
#include "crimen.h"
#include <fstream>
#include <iterator>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

using Longitud = float;
using Latitud  = float;
using Termino  = string;
using IUCR     = string;
using ID       = unsigned;

class CSS {
  map<ID, crimen> baseDatos;
  multimap<fecha, map<ID, crimen>::iterator> DateAccess;
  map<IUCR, set<ID>> IUCRAccess;
  unordered_map<Termino, set<ID>> index;
  map<Longitud, multimap<Latitud, ID>> posicionGeo;


  /** @brief Método auxiliar que comprueba si al borrar un multicontenedor, el contenedor
   *  interno queda vacio.
   *  @tparam Map Tipo contenedor externo (Map/Unordered Map).
   *  @tparam Key Tipo clave del map.
   *  @tparam Remove Tipo a eliminar del contenedor interno del map.
   *  @param mapContainer Contenedor externo del que eliminar.
   *  @param key Clave correspondiente al contenedor interno.
   *  @param toErase Dato a eliminar del contenedor interno.
   */
  template<class Map, class Key, class Remove>
  void erase_empty_descr(Map &mapContainer, Key &key, Remove &toErase);

  /** @brief Método auxiliar para pasar a un vector el contenido de una cola que es vaciada
   *  @tparam Queue Tipo de la cola a eliminar (Queue/Priority Queue).
   *  @param q Instancia de la cola a vaciar.
   *  @return Vector que contiene pares ID peso con el peso ordenado descendentemente.
   */
  template <class Queue>
  vector<pair<ID,float>> pop_to_vector(Queue &q);

  /** @brief Añade al map los pesos específicados por el set.
   *  @param t1 Map que contiene los ID y sus pesos correspondientes.
   *  @param t2 Set que contiene un nuevo conjunto de ID a ser añadidos al map.
   */
  void unionPeso(map<ID, float> &t1, const set<ID> &t2);




public:
  /** @brief Iterador sobre la base de datos en orden creciente de ID.
   */
  class iterator;
  /** @brief Itera en la base de datos en orden creciente de fecha.
   */
  class Date_iterator;
  class IUCR_iterator;
  friend class IUCR_iterator;

  /** @brief Carga la base de datos.
   *  @param nombreDB Ruta donde se encuentra la base de datos.
   */
  void load(const string &nombreDB);
  /** @brief Inserta un crimen en la base de datos
   *  @pre El crimen debe tener ID mayor que 0 y no encontrarse en la base de
   * datos.
   *  @param x Crimen a insertar.
   */
  void insert(const crimen &x);
  /** @brief Borra un crimen de la base de datos.
   *  @param ID ID del crimen a borrar.
   *  @return true si existia y se ha borrado, false en caso contrario.
   */
  bool erase(ID id);
  /** @brief Busca el crimen con dicho ID
   *  @param ID ID del crimen a encontrar.
   *  @return Iterador al crimen buscado. Si no se encuentra devuelve end()
   */
  iterator find_ID(unsigned int ID);
  /** @brief Modifica el campo arresto del crimen
   *  @pre El crimen debe existir en la base de datos.
   *  @param ID ID del crimen a modificar.
   *  @param value Valor del campo arresto.
   */
  void setArrest(unsigned int ID, bool value);
  /** @brief Dada una consulta devuelve los k elementos mas apropiados.
   *  @param q Consulta.
   *  @param k Numero de elementos a devolver.
   */
  vector<pair<ID, float>> Query(list<string> &q, const unsigned &k);
  /** @brief Devuelve una lista con los crimenes que se produjeron en dicho
   * area.
   *  @pre Se presupone que x1 < x2 y y1 > y2
   *  @param x1 Longitud de la coordenada inicial
   *  @param y1 Latitud de la coordenada inicial.
   *  @param x2 Longitud de la coordenada final.
   *  @param y2 Latitud de la coordenada final.
   */
  list<ID> inArea(const Longitud &x1, const Latitud &y1, const Longitud &x2,
                  const Latitud &y2);

  /** @brief Inicio de base de datos ordenada por ID.
   *  @return Devuelve un iterator al inicio de baseDatos.
   */
  iterator begin();
  /** @brief Inicio de base de datos ordenada por IUCR.
   *  @return Devuelve un iterator al inicio de IUCRAccess.
   */
  IUCR_iterator ibegin();
  /** @brief Inicio de base de datos ordenada por fecha.
   *  @return Devuelve un iterator al inicio DateAccess.
   */
  Date_iterator dbegin();
  /** @brief Fin de base de datos ordenada por ID.
   *  @return Devuelve un iterator al final de baseDatos.
   */
  iterator end();
  /** @brief Fin de base de datos ordenada por IUCR.
   *  @return Devuelve un iterator al final de IUCRAccess.
   */
  IUCR_iterator iend();
  /** @brief Fin de base de datos ordenada por fecha.
   *  @return Devuelve un iterator al final de DateAccess.
   */
  Date_iterator dend();

  /** @brief Iterador al primer elemento que contiene dicha id.
   *  @param id ID a buscar.
   *  @return Devuelve el iterador al primer elemento que contiene dicha id.
   */
  iterator lower_bound(const ID &id);
  /** @brief Iterador al primer elemento que contiene dicha IUCR.
   *  @param iucr IUCR a buscar.
   *  @return Devuelve el IUCR_iterador al primer elemento que contiene dicha IUCR.
   */
  IUCR_iterator lower_bound(const IUCR &iucr);
  /** @brief Iterador al primer elemento que contiene dicha fecha.
   *  @param f Fecha a buscar.
   *  @return Devuelve el IUCR_iterador al primer elemento que contiene dicha fecha.
   */
  Date_iterator lower_bound(const fecha &f);

  /** @brief Iterador al elemento siguiente al último que contiene dicha id.
   *  @param id ID a buscar.
   *  @return Devuelve el iterador al siguiente al último elemento que contiene dicha id.
   */
  iterator upper_bound(const ID &id);
  /** @brief Iterador al elemento siguiente al último que contiene dicha iucr.
   *  @param iucr IUCR a buscar.
   *  @return Devuelve el iterador al siguiente al último elemento que contiene dicha iucr.
   */
  IUCR_iterator upper_bound(const IUCR &iucr);
  /** @brief Iterador al elemento siguiente al último que contiene dicha fecha.
   *  @param f Fecha a buscar.
   *  @return Devuelve el iterador al siguiente al último elemento que contiene dicha fecha.
   */
  Date_iterator upper_bound(const fecha &f);

  /** @brief Iterador que itera en orden creciente de ID.
   */
  class iterator : public std::iterator<bidirectional_iterator_tag,
                                        pair<const ID, crimen>> {
    /** @brief Itera sobre baseDatos ,
     */
    map<ID,crimen>::iterator it;
    friend class CSS;
  public:
    /** @brief Constructor por defecto.
     */
    iterator();
    /** @brief Constructor de copia.
     *  @param it2 Iterador a copiar.
     */
    iterator(const iterator &it2);
    /** @brief Dereferencia el iterador.
     *  @return Referencia al par <const ID, crimen> al que apunta el iterador.
     */
    reference operator*();
    /** @brief Operador de acceso por dereferencia.
     *  @return Puntero a un par<const ID, crimen>
     */
    pointer operator->();
    /** @brief Operador de postincremento. Avanza en orden ascendente de ID.
     *  @return Copia del iterador antes de avanzar.
     */
    iterator operator++(int);
    /** @brief Operador de preincremento. Avanza en orden ascendente de ID.
     *  @return Referencia al iterador tras avanzar.
     */
    iterator& operator++();
    /** @brief Operador de postdecremento. Retrocede al ID anterior.
     *  @return Copia del iterador antes de retroceder.
     */
    iterator operator--(int);
    /** @brief Operador de predecremento. Retrocede al ID anterior.
     *  @return Referencia al iterador tras retroceder.
     */
    iterator& operator--();
    /** @brief Operador de igualdad.
     *  @param it2 iterator con el que comparar.
     *  @return true si ambos iteradores apuntan al mismo crimen, falso en caso contrario.
     */
    bool operator==(const iterator &it2);
    /** @brief Operador de desigualdad.
     *  @param it2 iterator con el que comparar.
     *  @return true si ambos iteradores no apuntan al mismo crimen, falso en caso contrario.
     */
    bool operator!=(const iterator &it2);
  };

  /** @brief Iterador que itera en orden ascendente de fecha
   */
  class Date_iterator : public std::iterator<bidirectional_iterator_tag,
                                             pair<const ID, crimen>> {
    multimap<fecha, map<ID,crimen>::iterator>::iterator it;
    friend class CSS;
  public:
    /** @brief Constructor por defecto.
     */
    Date_iterator();
    /** @brief Constructor de copia.
     *  @param it2 Iterador a copiar.
     */
    Date_iterator(const Date_iterator &it2);
    /** @brief Dereferencia el iterador.
     *  @return Referencia al par <const ID, crimen> al que apunta el iterador.
     */
    reference operator*();
    /** @brief Operador de acceso por dereferencia.
     *  @return Puntero a un par<const ID, crimen>
     */
    pointer operator->();
    /** @brief Operador de postincremento. Avanza en orden ascendente de fecha.
     *  @return Copia del iterador antes de avanzar.
     */
    Date_iterator operator++(int);
    /** @brief Operador de preincremento. Avanza en orden ascendente de fecha.
     *  @return Referencia al iterador tras avanzar.
     */
    Date_iterator& operator++();
    /** @brief Operador de postdecremento. Retrocede a la fecha anterior.
     *  @return Copia del iterador antes de retroceder.
     */
    Date_iterator operator--(int);
    /** @brief Operador de predecremento. Retrocede a la fecha anterior.
     *  @return Referencia al iterador tras retroceder.
     */
    Date_iterator& operator--();
    /** @brief Operador de igualdad.
     *  @param it2 Date_iterator con el que comparar.
     *  @return true si ambos iteradores apuntan al mismo crimen, false en caso contrario.
     */
    bool operator==(const Date_iterator &it2);
    /** @brief Operador de desigualdad.
     *  @param it2 Date_iterator con el que comparar.
     *  @return true si ambos iteradores no apuntan al mismo crimen, false en caso contrario.
     */
    bool operator!=(const Date_iterator &it2);
  };

  /** @brief Iterador que itera en orden ascendente de IUCR, y dentro de cada IUCR en orden ascendente
   *  de ID.
   */
  class IUCR_iterator : public std::iterator<bidirectional_iterator_tag,
                                             pair<const ID, crimen>> {
    /** @brief Itera sobre IUCRAccess.
     */
    map<IUCR, set<ID>>::iterator it_m;
    /** @brief Itera sobre el conjunto de crimenes de cada IUCR
     */
    set<ID>::iterator it_s;
    CSS *css;
    friend class CSS;

  public:
    /** @brief Constructor por defecto.
     */
    IUCR_iterator();
    /** @brief Constructor de copia.
     *  @param it2 Iterador a copiar.
     */
    IUCR_iterator(const IUCR_iterator &it2);
    /** @brief Dereferencia el iterador.
     *  @return Referencia al par <const ID, crimen> al que apunta el iterador.
     */
    reference operator*();
    /** @brief Operador de acceso por dereferencia.
     *  @return Puntero a un par<const ID, crimen>
     */
    pointer operator->();
    /** @brief Operador de postincremento. Avanza en orden ascendente de IUCR(ID para mismo IUCR).
     *  @return Copia del iterador antes de avanzar.
     */
    IUCR_iterator operator++(int);
    /** @brief Operador de preincremento. Avanza en orden ascendente de IUCR(ID para mismo IUCR).
     *  @return Referencia al iterador tras avanzar.
     */
    IUCR_iterator& operator++();
    /** @brief Operador de postdecremento. Retrocede al crimen con IUCR(ID para mismo IUCR) anterior.
     *  @return Copia del iterador antes de retroceder.
     */
    IUCR_iterator operator--(int);
    /** @brief Operador de predecremento. Retrocede al crimen con IUCR(ID para mismo IUCR) anterior.
     *  @return Referencia al iterador tras retroceder.
     */
    IUCR_iterator& operator--();
    /** @brief Operador de igualdad.
     *  @param it2 IUCR_iterator con el que comparar.
     *  @return true si ambos iteradores apuntan al mismo crimen, false en caso contrario.
     */
    bool operator==(const IUCR_iterator &it2);
    /** @brief Operador de desigualdad.
     *  @param it2 IUCR_iterator con el que comparar.
     *  @return true si ambos iteradores no apuntan al mismo crimen, false en caso contrario.
     */
    bool operator!=(const IUCR_iterator &it2);
  };
};

#include "css.hxx"
#endif // CSS_H

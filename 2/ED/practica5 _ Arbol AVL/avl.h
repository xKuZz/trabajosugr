#ifndef __AVL_H
#define __AVL_H
#include "bintree.h"
#include <utility>
#include <initializer_list>
#include <iterator>
#include <algorithm>
using namespace std;

template<typename T, class comparar=less<T> >
class AVL {
  public:
#define AVL_Dato      0
#define AVL_Altura    1
    using altura = int;
    using key_type = T;
    using value_type = T;
    using key_compare = comparar;
    using value_compare = comparar;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using difference_type = ptrdiff_t;
    using size_type = size_t;
    using avl_tree_t = bintree<pair<T,altura>>;
    using avl_node_t = typename avl_tree_t::node;

    // Constructores
    /** @brief Constructor por defecto.
     */
    AVL() = default;

    /** @brief Constructor de rango.
     *  @tparam InputIterator Tipo de dato de un iterador.
     *  @param first Posición inicial para copiar.
     *  @param last Posición final para copiar.
     */
    template<typename InputIterator>
    AVL(InputIterator first, InputIterator last);

    /** @brief Constructor de copia.
     *  @param x AVL a copiar.
     */
    AVL(const AVL& x) = default;

    /** @brief Constructor con lista de inicialización.
     *  @param il Lista de inicialización para el AVL.
     */
    AVL(initializer_list<T> il);

    /** @brief Operador de asignación.
     *  @param x AVL a copiar.
     *  @return Referencia al AVL.
     */
    AVL& operator=(const AVL& x) = default;

    /** ITERADORES -> MÉTODOS **/
    class iterator;
    class const_iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /** @brief Devuelve un iterador al inicio del AVL.
     *  @return Iterador al inicio.
     */
    iterator begin();

    /** @brief Devuelve un iterador al final del AVL.
     *  @return Iterador al final.
     */
    iterator end();

    /** @brief Devuelve un iterador constante al inicio del AVL.
     *  @post No modifica el AVL.
     *  @return Iterador constante al inicio.
     */
    const_iterator cbegin();

    /** @brief Devuelve un iterador constante al final del AVL.
     *  @post No modifica el AVL.
     *  @return Iterador constante al final.
     */
    const_iterator cend();

    /** @brief Devuelve un iterador reverso al inicio reverso del AVL.
     *  @return Iterador reverso al inicio reverso del AVL.
     */
    reverse_iterator rbegin();

    /** @brief Devuelve un iterador reverso al final reverso del AVL.
     *  @return Iterador reverso al final reverso del AVL.
     */
    reverse_iterator rend();

    /** @brief Devuelve un iterador reverso constante al inicio reverso del AVL.
     *  @post No modifica el AVL.
     *  @return Iterador reverso constante al inicio reverso del AVL.
     */
    const_reverse_iterator crbegin();

    /** @brief Devuelve un iterador reverso constante al final reverso del AVL.
     *  @post No modifica el AVL.
     *  @return Iterador reverso constante al final reverso del AVL.
     */
    const_reverse_iterator crend();

    // Capacidad:
    /** @brief Comprueba si el AVL está vacío.
     *  @post No modifica el AVL.
     *  @return true si está vacío, false si hay algún elemento.
     */
    bool empty() const;

    /** @brief Devuelve el número de elementos en el AVL.
     *  @post No modifica el AVL.
     *  @return Número de elementos en el AVL.
     */
    size_type size() const;

    // Modificadores:
    /** @brief Inserta un valor en el AVL si no fue insertado previamente.
     *  @param val Valor a insertar.
     *  @return Par que tiene como primer elemento el iterador a la posición y
     *  como segundo el valor true si el dato no había sido insertado previamente.
     */
    pair<iterator,bool> insert(const value_type& val);

    /** @brief Inserta un rango de valores en el AVL.
     *  @tparam InputIterator Tipo de dato de un iterador.
     *  @param first Posición del primer valor a insertar.
     *  @param last Posición del último valor a insertar.
     */
    template<class InputIterator>
    void insert(InputIterator first, InputIterator last);

    /** @brief Inserta una lista de inicialización en el AVL.
     *  @param il Lista de inicialización.
     */
    void insert(initializer_list<value_type> il);

    /** @brief Borra la posición del iterador del AVL.
     *  @param position Posición a eliminar del AVL.
     *  @return Iterador a la posición siguiente a la eliminada.
     */
    iterator erase(const_iterator position);

    /** @brief Borra un valor del AVL.
     *  @param val Valor a eliminar del AVL.
     *  @return Número de elementos eliminados (máx 1 al ser conjunto).
     */
    size_type erase(const value_type& val);

    /** @brief Borra un rango de valores del AVL.
     *  @param first Posición del primer elemento a borrar.
     *  @param last Posición del último elemento a borrar.
     *  @return iterador a la posición siguiente a la última eliminada.
     */
    iterator erase(const_iterator first, const_iterator last);

    /** @brief Intercambia dos AVL.
     *  @param x AVL a intercambiar.
     */
    void swap(AVL& x);

    /** @brief Vacía el contenido del AVL.
     */
    void clear() noexcept;

    // Operaciones:
    /** @brief Busca un valor en el AVL.
     *  @param val Valor a buscar.
     *  @post No modifica el AVL.
     *  @return Iterador constante al valor si se encuentra, a cend() si no se encuentra.
     */
    const_iterator find(const value_type& val) const;

    /** @brief Busca un valor en el AVL.
     *  @param val Valor a buscar.
     *  @return Iterador al valor si se encuentra, a end() si no se encuentra.
     */
    iterator find(const value_type& val);

    /** @brief Devuelve un iterador a la primera posición que no va antes que la supuesta posición del valor.
     *  @param val Valor a tener en cuenta.
     *  @return Iterador para el primer valor para el que cmp(elemento,val) es falso.
     */
    iterator lower_bound(const value_type& val);

    /** @brief Devuelve un iterador constante a la primera posición que no va antes que la supuesta posición del valor.
     *  @param val Valor a tener en cuenta.
     *  @post No modifica el conjunto.
     *  @return Iterador constante al primer valor para el que cmp(elemento,val) es false.
     */
    const_iterator lower_bound(const value_type& val) const;

    /** @brief Devuelve un iterador a la primera posición que va tras la supuesta posición del valor.
     *  @param val Valor a tener en cuenta.
     *  @return Iterador al primer elemento para el que cmp(val,elemento) es true.
     */
    iterator upper_bound(const value_type& val);

    /** @brief Devuelve un iterador constante a la primera posición que va tras la supuesta posición del valor.
     *  @param val Valor a tener en cuenta.
     *  @post No modifica el conjunto.
     *  @return Iterador al primer elemento constantepara el que cmp(val,elemento) es true.
     */
    const_iterator upper_bound(const value_type& val) const;

    class iterator: public std::iterator<bidirectional_iterator_tag, T> {
    public:
        /** @brief Constructor por defecto.
         */
        iterator() = default;

        /** @brief Constructor de copia
         *  @param it Iterador a copiar.
         */
        iterator(const iterator& it) = default;

        /** @brief Operador de asignación para iterador.
         *  @param it Iterador a asignar.
         *  @return Referencia al iterador tras ser asignado.
         */
        iterator& operator=(const iterator& it) = default;

        /** @brief Avanza a la siguiente posición en el AVL.
         *  @pre El iterador no debe encontrarse en la posición end().
         *  @return Copia del iterador antes de avanzar.
         */
        iterator operator++(int);

        /** @brief Retrocede a la posición anterior en el AVL.
         *  @pre El iterador no debe encontrarse en la posición begin().
         *  @return Copia del iterador antes de retroceder.
         */
        iterator operator--(int);

        /** @brief Avanza a la siguiente posición en el AVL.
         *  @pre El iterador no debe encontrarse en la posición end().
         *  @return Referencia al iterador tras avanzar.
         */
        iterator& operator++();

        /** @brief Retrocede a la posición anterior en el AVL.
         *  @pre El iterador no debe encontrarse en la posición begin().
         *  @return Referencia al iterador tras retroceder.
         */
        iterator& operator--();

        /** @brief Dereferencia el iterador.
         *  @pre El iterador debe encontrarse en el rango [begin(), end()).
         *  @return Referencia al valor apuntado por el iterador.
         */
        T& operator*();

        /** @brief Operador de acceso a miembros.
         *  @pre El iterador debe encontrarse en el rango [begin(), end()).
         *  @return Puntero al elemento apuntado por el iterador.
         */
        T* operator->();

        /** @brief Operador de igualdad.
         *  @param it Iterador a comparar.
         *  @return true si son iguales, false en caso contrario.
         */
        bool operator==(const iterator& it) const;

        /** @brief Operador de desigualdad.
         *  @param it Iterador a comparar.
         *  @return true si no son iguales, false si son iguales.
         */
        bool operator!=(const iterator& it) const;
      private:
        iterator(avl_node_t& n);
        typename avl_tree_t::inorder_iterator iter;
        friend class AVL;
    };

    class const_iterator: public std::iterator<bidirectional_iterator_tag, const T,
                          ptrdiff_t, const T*, const T&> {
      public:
        /** @brief Constructor por defecto.
         */
        const_iterator() = default;

        /** @brief Constructor a partir de iterador normal.
         *  @param it Iterador a partir del que construir.
         */
        const_iterator(const iterator& it);

        /** @brief Constructor de copia.
         *  @param it Iterador constante a copiar.
         */
        const_iterator(const const_iterator& it) = default;

        /** @brief Operador de asignación.
         *  @param it Iterador constante a asignar.
         *  @return Referencia al iterador constante.
         */
        const_iterator& operator=(const const_iterator& it) = default;

        /** @brief Avanza a la siguiente posición del AVL.
         *  @pre El iterador constante no debe estar en la posición cend().
         *  @return Copia del iterador constante antes de avanzar.
         */
        const_iterator operator++(int);

        /** @brief Retrocede a la posición anterior del AVL.
         *  @pre El iterador constante no debe estar en la posición cbegin().
         *  @return Copia del iterador constante antes de retroceder.
         */
        const_iterator operator--(int);

        /** @brief Avanza a la siguiente posición del AVL.
         *  @pre El iterador constante no debe estar en la posición cend().
         *  @return Referencia al iterador constante tras avanzar.
         */
        const_iterator& operator++();

        /** @brief Retrocede a la siguiente posición del AVL.
         *  @pre El iterador constante no debe estar en la posición cbegin().
         *  @return Referencia al iterador constante tras retroceder.
         */
        const_iterator& operator--();

        /** @brief Dereferencia el elemento apuntado por el iterador.
         *  @pre El valor se encuentra en el rango [cbegin(), cend()).
         *  @post No modifica el AVL.
         *  @return Referencia al valor constante al que apunta el iterador.
         */
        const T& operator*() const;

        /** @brief Accede al elemento apuntado por el iterador.
         *  @pre El valor se encuentra en el rango [cbegin(), cend()).
         *  @post No modifica el AVL.
         *  @return Puntero al elemento apuntado por el iterador.
         */
        const T* operator->() const;

        /** @brief Operador de igualdad.
         *  @param it Iterador constante a comparar.
         *  @return true si son iguales, false en caso contrario.
         */
        bool operator==(const const_iterator& it) const;

        /** @brief Operador de desigualdad.
         *  @param it Iterador constante a comparar.
         *  @return true si no son iguales, false si son iguales.
         */
        bool operator!=(const const_iterator& it) const;
      private:
        const_iterator(avl_node_t& n);
        typename avl_tree_t::inorder_iterator iter;
        friend class AVL;
    };


  private:
    // Métodos privados
    enum class ROTAR { IZQUIERDA, DERECHA, DERECHA_IZQUIERDA, IZQUIERDA_DERECHA};
    bool balancear(avl_node_t);
    void rotacion(avl_node_t n, ROTAR r);
    void ajustar_altura(avl_node_t n);
    altura h(avl_node_t n);

    // Representación
    avl_tree_t el_avl;
    comparar cmp;
    int tama=0;
};

#include "avl.hxx"
#endif // __AVL_H

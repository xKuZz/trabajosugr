#include "avl.h" // AUTOCOMPLETAR
#define AVL_TEMPLATE template <typename T, class comparar>

/** @file   avl.hxx
 *  @brief  Implementación del Árbol AVL a partir de bintree.
 *  @author David Criado Ramón.
 */
/*----------------------- CONSIDERACIONES INICIALES -------------------------*/
/**  Modificaciones a bintree proporcionado
 *  A la estructura de datos proporcionada se le han hecho las siguientes
 *  modificaciones:
 *
 *  bintree::inorder_iterator
 *   -He añadido el operador de predecremento (--it).
 *   -He añadido un puntero a un bintree para poder hacer el decremento.
 *   -inorder_iterator ahora es amigo de AVL.
 *   -El constructor de copia que estaba declarado pero no implementado ahora
 *    es implementado por el compilador.
 *
 *  bintree::node
 *   -node es ahora amigo de AVL
 *
 *  bintree
 *   -bintree es ahora amigo de AVL.
 *   -swap: Añadido método swap.
 *   -begin_inoder: modificado para poner el puntero a bintree (necesario --).
 *   -end_inorder:  modificado para poner el puntero a bintree (necesario --).
 *
 *  bintreeNode.hxx:
 *   -Eliminados multiples ; después de implementaciones de métodos que no
 *    permitián compilar.
 */

/**  Algunas abreviaciones utilizadas
 *  Con la idea de facilitar la lectura del código se utilizan la siguientes
 *  abreviaciones basadas en macro y alias frecuentemente:
 *  Basados en macros:
 *   AVL_TEMPLATE equivale a template <typename T, class comparar>
 *   get<AVL_Dato>(*n) Devuelve referencia al valor de la etiqueta del nodo.
 *   get<AVL_Altura(*n) Devuelve referencia a la altura de la etiqueta del nodo.
 *  Basados en alias:
 *   avl_tree_t equivale a bintree<pair<T, altura>>
 *   avl_node_t equivale a typename avl_tree_t::node
 */
/*----------------------- CONSTRUCTORES-ASIGNACIÓN --------------------------*/
/**  Métodos para la construcción y asignación de AVL
 *  Los constructores por defecto y de copia y el operador de asignación
 *  son creados automáticamente por el compilador
 *
 *  Los constructores de rango y lista de inicialización son los aquí creados
 *  y llaman a sus correspondientes versiones de insert
 */

AVL_TEMPLATE
template <typename InputIterator>
AVL<T, comparar>::AVL(InputIterator first, InputIterator last) {
  insert(first,last);
}

AVL_TEMPLATE
AVL<T, comparar>::AVL(initializer_list<T> il) {
 for (auto valor : il)
    insert(valor);
}

/*-------------------------------- ALTURA -----------------------------------*/
/**  Métodos privados relacionados con el tratamiento de la altura
 *  Existen 3 métodos
 *   Un método h que devuelve la altura del nodo o -1 si el nodo es nulo.
 *   Un método que actualiza la altura tras insertar mientras sea pertinente.
 *   Un método que actualiza la altura tras borrar mientras sea pertinente.
 *   El método utilizado tras borrar es también se usa para las rotaciones.
 */

AVL_TEMPLATE
typename AVL<T,comparar>::altura AVL<T,comparar>::h(avl_node_t n) {
  if (n.elnodo == nullptr)
    return -1;
  else
    return get<AVL_Altura>(*n);
}

AVL_TEMPLATE
void AVL<T, comparar>::ajustar_altura(avl_node_t n) {
  for (avl_node_t nodo = n; !nodo.null(); nodo = nodo.parent()) {
    auto altura_correcta = max(h(nodo.elnodo->izda),
                               h(nodo.elnodo->dcha)) + 1;
    if (get<AVL_Altura>(*nodo) == altura_correcta)
      break;
    else
        get<AVL_Altura>(*nodo) =  altura_correcta;
  }
}
/*--------------------------ROTACIONES AVL ----------------------------------*/
/**  Métodos privados para comprobar y realizar rotaciones AVL.
 *  El método balancear recibe la raíz de un subárbol y comprueba si es
 *  necesario balancear. En caso de que no sea necesario devuelve false.
 *
 *  El método rotar realiza las rotaciones dependiendo del tipo.
 *
 *  Las rotaciones ajustan todos los punteros implicados de padres e hijos.
 *
 *  Las rotaciones dobles están implementadas en función de las simples.
 */

AVL_TEMPLATE
bool AVL<T, comparar>::balancear(avl_node_t n) {
  // Caso A: La parte izquierda es más alta que la derecha
  if   (h(n.elnodo->izda) - h(n.elnodo->dcha) >= 2)
    // Caso A1: Rotación normal
    if (h(n.elnodo->izda.elnodo->izda) >= h(n.elnodo->izda.elnodo->dcha))
      rotacion(n, ROTAR::DERECHA);
    // Caso A2: Rotación zig-zag
    else
      rotacion(n, ROTAR::IZQUIERDA_DERECHA);
  // Caso B: La parte derecha es más alta que la izquierda
  else if (h(n.elnodo->dcha) - h(n.elnodo->izda) >= 2) {
    // Caso B1: Rotación normal
    if    (h(n.elnodo->dcha.elnodo->dcha) >= h(n.elnodo->dcha.elnodo->izda))
      rotacion(n, ROTAR::IZQUIERDA);
    // Caso B2: Rotación zig-zag
    else
      rotacion(n, ROTAR::DERECHA_IZQUIERDA);
  }
  else if (!n.parent().null())
    return false;

  return true;
}

AVL_TEMPLATE
void AVL<T, comparar>::rotacion(avl_node_t n, ROTAR r) {
  avl_node_t aux;
  switch (r) {
    case ROTAR::IZQUIERDA:
      // Guardo el hijo izquierda del hijo derecha (si existe)
      if (!n.right().null()) {
        aux = n.elnodo->dcha.elnodo->izda;
        if (!aux.null())
          aux.elnodo->pad = n;
      }

      // Preparo al hijo derecha para ser la raíz
      n.elnodo->dcha.elnodo->pad = n.elnodo->pad;
      n.elnodo->dcha.elnodo->izda = n;
      // Rotamos
      n = n.elnodo->dcha;

      // Fijo los datos del padre de la raíz para la rotación
      if (n.parent().null())
        el_avl.laraiz = n;
      else if (n.elnodo->pad.elnodo->izda == n.elnodo->izda &&
              !n.elnodo->izda.null())
        n.elnodo->pad.elnodo->izda = n;
      else if (n.elnodo->pad.elnodo->dcha == n.elnodo->izda &&
              !n.elnodo->dcha.null())
        n.elnodo->pad.elnodo->dcha = n;

      // Reajusto los datos de la antigua raíz (añadiendo el dato guardado)
      n.elnodo->izda.elnodo->pad = n;
      n.elnodo->izda.elnodo->dcha = aux;

      get<AVL_Altura>(*n.left()) = max(h(n.left().left()),
                                       h(n.left().right())) + 1;
      get<AVL_Altura>(*n) = max(h(n.left()),
                                h(n.right())) + 1;
      ajustar_altura(n.elnodo->pad);
      break;

    case ROTAR::DERECHA:
      // Guardo el hijo derecha del hijo izquierda (si existe)
      if (!n.left().null()) {
        aux = n.elnodo->izda.elnodo->dcha;
        if (!aux.null())
          aux.elnodo->pad = n;
      }

      // Preparo al hijo izquierda para ser la raíz
      n.elnodo->izda.elnodo->pad = n.elnodo->pad;
      n.elnodo->izda.elnodo->dcha = n;
      // Rotamos
      n = n.elnodo->izda;

      // Fijo los datos del padre de la raíz para la rotación
      if (n.parent().null())
        el_avl.laraiz = n;
      else if (n.elnodo->pad.elnodo->izda == n.elnodo->dcha &&
              !n.elnodo->izda.null())
        n.elnodo->pad.elnodo->izda = n;
      else if (n.elnodo->pad.elnodo->dcha == n.elnodo->dcha &&
              !n.elnodo->dcha.null())
        n.elnodo->pad.elnodo->dcha = n;

      // Reajusto los datos de la antigua raíz (añadiendo el dato guardado)
      n.elnodo->dcha.elnodo->pad = n;
      n.elnodo->dcha.elnodo->izda = aux;

      // Reajusto las alturas

      get<AVL_Altura>(*n.right()) = max(h(n.right().left()),
                                        h(n.right().right())) + 1;
      get<AVL_Altura>(*n) = max(h(n.left()),
                                h(n.right())) + 1;
      ajustar_altura(n.elnodo->pad);

      break;
    case ROTAR::DERECHA_IZQUIERDA:
      rotacion(n.elnodo->dcha, ROTAR::DERECHA);
      rotacion(n             , ROTAR::IZQUIERDA);

      break;
    case ROTAR::IZQUIERDA_DERECHA:
      rotacion(n.elnodo->izda, ROTAR::IZQUIERDA);
      rotacion(n             , ROTAR::DERECHA);
      break;
  }
}

/*------------------------- AVL: INSERTAR DATOS -----------------------------*/
/**  Métodos para la inserción de datos en el árbol.
 *  La lógica requerida para la implementación es manejada en la versión que
 *  recibe un valor como parámetro, el resto de implementaciones se basan en
 *  la primera.
 *
 *  El algoritmo implementado baraja los siguientes casos:
 *    1- El árbol está vacío.
 *    2- El dato no se encuentra en el árbol.
 *    3- El árbol se encuentra en el árbol.
 *  Si un dato ha sido insertado se reajusta su altura y se comprueba el
 *  equilibrio de la estructura parando o bien cuándo se produce una rotación
 *  o bien si se llega a la raíz sin rotar.
 */

AVL_TEMPLATE
pair<typename AVL<T, comparar>::iterator, bool> AVL<T, comparar>::insert
                                                        (const T& val) {
  auto nodo = el_avl.laraiz;
  bool insertado = false;
  if (nodo.null()) { // Árbol vacío -> Inserto como raíz
    el_avl = avl_tree_t({val, 0});
    return { iterator(el_avl.laraiz), true};
  }
  else
    while (!insertado) {
      if (cmp(val, get<AVL_Dato>(*nodo))) {       // CMP: MENOR -> IZQUIERDA
        if (nodo.left().null()) {
          el_avl.insert_left (nodo, {val, 0});
          insertado = true;
        }
        nodo = nodo.left();
      }
      else if (cmp(get<AVL_Dato>(*nodo), val)) {  // CMP: MAYOR -> DERECHA
        if (nodo.right().null()) {
          el_avl.insert_right(nodo, {val,0});
          insertado = true;
        }
        nodo = nodo.right();
      }
      else                                        // CMP: IGUAL
        return { iterator(nodo), false };
    }
  ++tama;
  ajustar_altura(nodo.parent());
  for (auto aux = nodo; !balancear(aux) ;aux = aux.parent()) {}
  return       { iterator(nodo), true  };
  }

AVL_TEMPLATE
template <typename InputIterator>
void AVL<T, comparar>::insert(InputIterator first, InputIterator last) {
  for_each(first, last, [this](InputIterator it) { insert(*it); });
}

AVL_TEMPLATE
void AVL<T, comparar>::insert(initializer_list<T> il) {
  for (auto valor : il)
    insert(valor);
}
/*------------------------- AVL: BORRAR DATOS -------------------------------*/
/**  Métodos para la eliminación de elementos del árbol
 *  La lógica es manejada en la versión 1 que recibe un iterador costante y
 *  devuelve un iterador.
 *  El resto de métodos dependen del primero.
 *  Además existen un método privado en la sección del calculo de alturas
 *  que permite actualizar las alturas tras la eliminación de un dato.
 *  El algoritmo se divide en 4 casos:
 *    Caso 1: Iterador inválido
 *    Caso 2: El elemento a borrar es una hoja (Raíz | No Raíz)
 *    Caso 3: El elemento a borrar tiene sólo un hijo
 *    Caso 4: El elemento a borrar tiene dos hijos. (Llamada recursiva).
 *  Una vez el algoritmo borra el elemento se actualizan las alturas y se
 *  comprueba la condición de equilibrio subiendo hasta la raíz.
 */
AVL_TEMPLATE
typename AVL<T, comparar>::iterator AVL<T, comparar>::erase(
                                    const_iterator position) {
  if (position == cend()) return end(); // CASO 1: ITERADOR INVÁLIDO
  else {
    avl_node_t nodo_padre = position.iter.elnodo.elnodo->pad;
    avl_node_t nodo       = position.iter.elnodo;
    avl_node_t aux;
    avl_tree_t tree_aux;
    iterator salida;
    salida.iter = ++position.iter;
    if (nodo.left().null() && nodo.right().null()) { // CASO 2: HOJA
      if (nodo_padre.null()) // Padre: Raíz
        el_avl.clear();
      else {                 // Padre: No raíz
        if (nodo_padre.left() == nodo)  // Soy hijo izquierda
          el_avl.prune_left (nodo_padre, tree_aux);
        else                           // Soy hijo derecha
          el_avl.prune_right(nodo_padre, tree_aux);
        tree_aux.clear();              // Libero memoria
      }
      // Ajusto alturas y compruebo rotaciones
      --tama;
      aux = nodo_padre;
    }
    else if (!nodo.left().null() != !nodo.right().null()) { // CASO 3: HIJO ÚNICO
      if (!nodo.left().null())        // Sólo hay hijo izquierda
        el_avl.prune_left (nodo, tree_aux);
      else                            // Sólo hay hijo derecha
        el_avl.prune_right(nodo, tree_aux);

      if (nodo_padre.null()) {         // Padre: Raíz
        el_avl.swap(tree_aux);
        tree_aux.clear();
        aux = el_avl.laraiz;
      }                                // Padre: No raíz
      else if (nodo_padre.left() == nodo) { // Soy hijo izquierda
        el_avl.insert_left (nodo_padre, tree_aux);
        aux = nodo_padre.left();
      }
      else {
        el_avl.insert_right(nodo_padre, tree_aux);
        aux = nodo_padre.right();
      }
      --tama;
      aux = nodo_padre;

    }
    else {                       // CASO 4: DOS HIJOS
      avl_node_t nodo_a_borrar;
      // Búsqueda del anterior: Nodo más a la derecha del hijo izquierda
      avl_node_t anterior = nodo.elnodo->izda;
      while (!anterior.right().null())
        anterior = anterior.elnodo->dcha;

      auto valor_anterior(*anterior);
      // Implementación recursiva
      nodo_a_borrar = nodo;
      erase(get<AVL_Dato>(*anterior));
      *nodo_a_borrar = valor_anterior;
      aux = nodo_a_borrar;
    }
    ajustar_altura(aux);
    for (; !aux.null(); aux = aux.parent())
      balancear(aux);
    return salida;
  }

}

AVL_TEMPLATE
typename AVL<T, comparar>::size_type AVL<T, comparar>::erase(
                                                const T& val) {
  const_iterator c_it = find(val);
  if (c_it != cend()) {
    erase(c_it);
    return 1;
  }
  return 0;
}

AVL_TEMPLATE
typename AVL<T, comparar>::iterator AVL<T, comparar>::erase(
                     const_iterator first, const_iterator last) {
  const_iterator it = first;
  while (it != last)
    it = erase(it);
  return it;
}

/*------------------------- CAPACIDAD, SWAP, CLEAR --------------------------*/
/**  Métodos para consultar capacidad, intercambio y limpieza del AVL.
 */
AVL_TEMPLATE
bool AVL<T, comparar>::empty() const {
  return tama == 0;
}

AVL_TEMPLATE
typename AVL<T, comparar>::size_type AVL<T, comparar>::size() const {
  return tama;
}

AVL_TEMPLATE
void AVL<T, comparar>::swap(AVL& x) {
  el_avl.swap(x.el_avl);
}

AVL_TEMPLATE
void AVL<T, comparar>::clear() noexcept {
  el_avl.clear();
}

/*--------------------- AVL: OPERACIONES DE BÚSQUEDA ------------------------*/
/**  Métodos para realización de búsquedas O (log n).
 *  Todos los métodos están implementados en función del functor de orden cmp
 *  Existen versiones para iterator y const_iterator
 */

AVL_TEMPLATE
typename AVL<T, comparar>::iterator
         AVL<T, comparar>::lower_bound(const T& val) {
  avl_node_t nodo_out,     nodo = el_avl.laraiz;
  while (!nodo.null())
    if (!cmp(get<AVL_Dato>(*nodo), val))
       nodo_out = nodo,    nodo = nodo.left();
    else
       nodo     = nodo.right();
  auto it = iterator(nodo_out);
  it.iter.ptr = &el_avl;
  return it;
}

AVL_TEMPLATE
typename AVL<T, comparar>::iterator
         AVL<T, comparar>::upper_bound(const T& val) {
  avl_node_t nodo_out,   nodo = el_avl.laraiz;
  while (!nodo.null())
    if (cmp(val, get<AVL_Dato>(*nodo)))
       nodo_out = nodo,  nodo = nodo.left();
    else
       nodo     = nodo.right();
  auto it = iterator(nodo_out);
  it.iter.ptr = &el_avl;
  return it;
}

AVL_TEMPLATE
typename AVL<T, comparar>::iterator
         AVL<T, comparar>::find(const T& val) {
  iterator it  =    lower_bound(val);
  return  (it == end() || cmp(val, *it)) ? end() : it;
}


AVL_TEMPLATE
typename AVL<T, comparar>::const_iterator
         AVL<T, comparar>::lower_bound(const T& val) const {
  avl_node_t nodo_out, nodo = el_avl.laraiz;
  while (!nodo.null())
    if (!cmp(get<AVL_Dato>(*nodo), val))
       nodo_out = nodo,    nodo = nodo.left();
    else
       nodo     = nodo.right();
  auto c_it = const_iterator(nodo_out);
  c_it.iter.ptr = &el_avl;
  return c_it;
}

AVL_TEMPLATE
typename AVL<T, comparar>::const_iterator
         AVL<T, comparar>::upper_bound(const T& val) const {
  avl_node_t nodo_out,   nodo = el_avl.laraiz;
  while (!nodo.null())
    if (cmp(val, get<AVL_Dato>(*nodo)))
       nodo_out = nodo,  nodo = nodo.left();
    else
       nodo     = nodo.right();
  auto c_it = const_iterator(nodo_out);
  c_it.iter.ptr = &el_avl;
  return c_it;

}
AVL_TEMPLATE
typename AVL<T, comparar>::const_iterator
         AVL<T, comparar>::find(const T& val) const {
  const_iterator c_it = lower_bound(val);
  return (c_it == cend() || cmp(val, *c_it)) ? cend() : c_it;

}

/*------------------------ AVL: MÉTODOS DE RANGO ----------------------------*/
/**  Métodos para el inicio y el final del rango del AVL.
 *  Se sigue la filosofía [begin(), end())
 *  Para los iteradores no reversos:
 *   begin(), cbegin() apunta al primer dato del árbol (si hay) o al nodo nulo
 *   end(), cend() apunta al nodo nulo
 *  Para los iteradores reversos:
 *  rbegin(), crbegin() equivale a --end(), --cend() respectivamente.
 *  rend(), crend() equivale a --begin(), --cbegin() respectivamente.
 */
AVL_TEMPLATE
typename AVL<T, comparar>::iterator AVL<T, comparar>::begin() {
  iterator it;
  it.iter = el_avl.begin_inorder();
  return it;
}

AVL_TEMPLATE
typename AVL<T, comparar>::iterator AVL<T, comparar>::end() {
  iterator it;
  it.iter = el_avl.end_inorder();
  return it;
}

AVL_TEMPLATE
typename AVL<T, comparar>::const_iterator AVL<T, comparar>::cbegin() {
  const_iterator it;
  it.iter = el_avl.begin_inorder();
  return it;
}

AVL_TEMPLATE
typename AVL<T, comparar>::const_iterator AVL<T, comparar>::cend() {
  const_iterator it;
  it.iter = el_avl.end_inorder();
  return it;
}

AVL_TEMPLATE
typename AVL<T, comparar>::reverse_iterator AVL<T, comparar>::rbegin() {
  return reverse_iterator(end());
}

AVL_TEMPLATE
typename AVL<T, comparar>::reverse_iterator AVL<T, comparar>::rend() {
  return reverse_iterator(begin());
}

AVL_TEMPLATE
typename AVL<T, comparar>::const_reverse_iterator AVL<T, comparar>::crbegin() {
  return const_reverse_iterator(cend());
}

AVL_TEMPLATE
typename AVL<T, comparar>::const_reverse_iterator AVL<T, comparar>::crend() {
  return const_reverse_iterator(cbegin());
}

/*----------------------------- AVL: ITERATOR -------------------------------*/
/**  Implementación del iterador estándar.
 *  El iterador se comporta como un iterador bidireccional.
 *  El iterador se basa en el funcionamiento del inorder_iterator de bintree.
 */
AVL_TEMPLATE
AVL<T, comparar>::iterator::iterator(avl_node_t& n) : iter(n) {}

AVL_TEMPLATE
typename AVL<T, comparar>::iterator
         AVL<T, comparar>::iterator::operator++(int) {
  auto copia(*this);
  ++iter;
  return copia;
}

AVL_TEMPLATE
typename AVL<T, comparar>::iterator&
         AVL<T, comparar>::iterator::operator++() {
  ++iter;
  return *this;
}


AVL_TEMPLATE
typename AVL<T, comparar>::iterator
         AVL<T, comparar>::iterator::operator--(int) {
  auto copia(*this);
  --iter;
  return copia;
}

AVL_TEMPLATE
typename AVL<T, comparar>::iterator&
         AVL<T, comparar>::iterator::operator--() {
  --iter;
  return *this;
}

AVL_TEMPLATE
T& AVL<T, comparar>::iterator::operator*() {
  return get<AVL_Dato>(*iter);
}

AVL_TEMPLATE
T* AVL<T, comparar>::iterator::operator->() {
  return addressof(get<AVL_Dato>(*iter));
}

AVL_TEMPLATE
bool AVL<T, comparar>::iterator::operator==(const iterator& it) const {
  return iter == it.iter;
}

AVL_TEMPLATE
bool AVL<T, comparar>::iterator::operator!=(const iterator& it) const {
  return iter != it.iter;
}

/*----------------------------- AVL: CONST_ITERATOR -------------------------*/
/**  Implementación del iterador constante.
 *  El iterador se comporta como un iterador bidireccional.
 *  El iterador se basa en el funcionamiento del inorder_iterator de bintree.
 */
AVL_TEMPLATE
AVL<T, comparar>::const_iterator::const_iterator(const iterator &it)
                                                     : iter(it.iter) {}
AVL_TEMPLATE
AVL<T, comparar>::const_iterator::const_iterator(avl_node_t &n) : iter(n) {}

AVL_TEMPLATE
typename AVL<T, comparar>::const_iterator
         AVL<T, comparar>::const_iterator::operator++(int) {
  auto copia(*this);
  ++iter;
  return copia;
}

AVL_TEMPLATE
typename AVL<T, comparar>::const_iterator&
         AVL<T, comparar>::const_iterator::operator++() {
  ++iter;
  return *this;
}

AVL_TEMPLATE
typename AVL<T, comparar>::const_iterator
         AVL<T, comparar>::const_iterator::operator--(int) {
  auto copia(*this);
  --iter;
  return copia;
}

AVL_TEMPLATE
typename AVL<T, comparar>::const_iterator&
         AVL<T, comparar>::const_iterator::operator--() {
  --iter;
  return *this;
}

AVL_TEMPLATE
const T& AVL<T, comparar>::const_iterator::operator*() const {
  auto it = const_cast<typename avl_tree_t::inorder_iterator&>(iter);
  return get<AVL_Dato>(*it);
}

AVL_TEMPLATE
const T* AVL<T, comparar>::const_iterator::operator->() const {
  auto it = const_cast<typename avl_tree_t::inorder_iterator&>(iter);
  return addressof(get<AVL_Dato>(*it));
}

AVL_TEMPLATE
bool AVL<T, comparar>::const_iterator::operator==(const const_iterator& it)
                                                                    const {
  return iter == it.iter;
}

AVL_TEMPLATE
bool AVL<T, comparar>::const_iterator::operator!=(const const_iterator& it)
                                                                    const {
  return iter != it.iter;
}

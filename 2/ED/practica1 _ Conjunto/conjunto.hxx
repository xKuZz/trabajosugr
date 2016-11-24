/**
  * @file conjunto.hxx
  * @brief Implementación de la clase conjunto
  * @author Alejandro Campoy Nieves
  * @author David Criado Ramón
  */

/**
 @brief Constructor por defecto de la clase conjunto (Conjunto vacio).
*/
conjunto::conjunto(){
}

/**
 * @brief Constructor de copia.
 * @d Conjunto a copiar.
 */
conjunto::conjunto(const conjunto &d){
    this->vc=d.vc;
}

/**
 * @brief Comprueba el invariante de la representación de la clase conjunto.
 * @return True si se cumple el invariante, false en caso contrario.
 */
bool conjunto::cheq_rep() const{
    for (conjunto::size_type i=0; i<vc.size(); ++i)
        if (vc[i].getID()<=0)
            return false;
    for (conjunto::size_type i=0; i<vc.size()-1; ++i)
        if(vc[i].getID()>=vc[i+1].getID())
            return false;
    return true;
}
/**
 * @brief Comprueba si el conjunto está vacío.
 * @return True si el conjunto está vacío, false en caso contrario.
 */
bool conjunto::empty() const{
    if (vc.size()==0)
        return true;
    return false;
}

/**
 * @brief Elimina un elemento del conjunto dado su identificador.
 * @param id ID de la entrada a eliminar del conjunto.
 * @return True si se ha podido eliminar, false en caso contrario (no se encontró un crimen con esa id).
 */
bool conjunto::erase(const long int &id){
    vector<conjunto::entrada>::const_iterator it;
    conjunto::entrada comparativo;
    comparativo.setID(id);
    it=lower_bound(vc.begin(),vc.end(),comparativo);
    if(it->getID()==id){
        vc.erase(it);
        return true;
      }
    else{
        return false;
    }
}

/**
 * @brief Elimina un elemento del conjunto dado un crimen.
 * @param e Crimen a eliminar en el conjunto.
 * @return True si se ha podido eliminar, false en caso contrario (no se encontró el crimen).
 */
bool conjunto::erase(const conjunto::entrada &e){
    return erase(e.getID());
}

/**
 * @brief Busca una entrada dada su id en el conjunto.
 * @param id ID del crimen a buscar.
 * @return Par (crimen,verdadero) si se encuentra o (--,falso) si no se encuentra.
 */
pair<conjunto::entrada,bool> conjunto::find(const long int &id) const{
    vector<conjunto::entrada>::const_iterator it;
    conjunto::entrada comparativo;
    comparativo.setID(id);
    pair<conjunto::entrada,bool> salida;
    it=lower_bound(vc.begin(),vc.end(),comparativo);
    if (it->getID()==id){
        salida.first=*it;
        salida.second=true;
    }
    else {
        salida.second=false;
    }

    return salida;
}

/**
 * @brief Inserta una entrada en la posición apropiada del conjunto.
 * @param e Crimen a introducir.
 * @return Si se ha insertado correctamente o no (ya existía un crimen con dicha ID).
 */
bool conjunto::insert(const conjunto::entrada &e){
    vector<conjunto::entrada>::const_iterator it;
    if (vc.size()==0){
        vc.push_back(e);
        return true;
     }
    else {
        it=lower_bound(vc.begin(),vc.end(),e);
        if (it->getID()!=e.getID()){

            vc.insert(it,e);
            return true;
    }
        else {
            return false;
        }
    }
}

/**
 * @brief Sobrecarga del operador de asignación.
 * @param org Conjunto a asignar.
 * @return Referencia al objeto de la clase (this).
 */
conjunto& conjunto::operator=(const conjunto &org){
    if (this!=&org){
        this->vc=org.vc;
    }
    return *this;
}

/**
 * @brief Devuelve el tamaño del conjunto
 * @return Tamaño del conjunto
 */
conjunto::size_type conjunto::size() const{
    return vc.size();
}

/**
 * @brief Sobrecarga del operador de extracción de flujos para la clase conjunto.
 * @param sal Flujo de salida.
 * @param D Conjunto a mostrar.
 * @return Referencia al flujo de salida.
 */

ostream& operator<<(ostream &sal, const conjunto &D){
    for(conjunto::size_type i=0; i<D.vc.size(); ++i)
        sal << D.vc[i] << endl;
    return sal;
}

/**
 * @brief Devuelve un conjunto con todos los crímenes con el mismo IUCR.
 * @param iucr IUCR a buscar.
 * @return Conjunto con crímenes con el IUCR proporcionado.
 */
conjunto conjunto::findIUCR (const string &iucr) const{
    conjunto salida;
    for_each(vc.begin(),vc.end(),[&iucr, &salida](const conjunto::entrada &e){
        if (e.getIUCR()==iucr)
            salida.insert(e);
    });
    return salida;
}
/**
 * @brief Devuelve un conjunto con todos los crímenes con la misma descripción.
 * @param descr Descripción a buscar.
 * @return Conjunto con todos los crímenes con la descripción proporcionada.
 */
conjunto conjunto::findDESCR(const string &descr) const {
    conjunto salida;
    for_each(vc.begin(),vc.end(),[&descr, &salida](const conjunto::entrada &e){
        if (e.getDESCR().rfind(descr)!=string::npos){
            salida.insert(e);
        }
    });
    return salida;
}

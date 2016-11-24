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
    for (size_type i=0; i<vc.size(); ++i)
        if (vc[i].getID()<=0)
            return false;
    for (size_type i=0; i<vc.size()-1; ++i)
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
    it=lower_bound(vc.begin(),vc.end(),id);
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
conjunto::const_iterator conjunto::find( const long int &id) const{
    const_iterator it;
    it.c_itv=lower_bound(vc.begin(),vc.end(),id);
    return it;
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
    for (const auto &e: vc){
        if(e.getIUCR()==iucr)
            salida.insert(e);
    }
    return salida;
}
/**
 * @brief Devuelve un conjunto con todos los crímenes con la misma descripción.
 * @param descr Descripción a buscar.
 * @return Conjunto con todos los crímenes con la descripción proporcionada.
 */
conjunto conjunto::findDESCR(const string &descr) const {
    conjunto salida;
    for (const auto &e: vc)
        if (e.getDESCR().rfind(descr)!=string::npos){
            salida.insert(e);
    }

    return salida;
}

/**         conjunto::iterator **/

conjunto::iterator conjunto::begin(){
    conjunto::iterator sal;
    sal.itv = vc.begin();
    return sal;
}


conjunto::iterator conjunto::end(){
    conjunto::iterator sal;
    sal.itv = vc.end();
    return sal;
}
/** @brief constructor defecto iterator
*/
conjunto::iterator::iterator(){

}

/** @brief constructor copia iterator
*/
conjunto::iterator::iterator(const conjunto::iterator & i){
    itv = i.itv;
}

const conjunto::entrada& conjunto::iterator::operator*(){
    return *itv;
}

conjunto::iterator conjunto::iterator::operator++(int){
    conjunto::iterator antiguo(*this);
    ++itv;
    return antiguo;
}

conjunto::iterator& conjunto::iterator::operator++(){
    ++itv;
    return *this;
}

conjunto::iterator conjunto::iterator::operator--(int){
    conjunto::iterator antiguo(*this);
    --itv;
    return antiguo;
}

conjunto::iterator& conjunto::iterator::operator--(){
    --itv;
    return *this;
}

bool conjunto::iterator::operator==(const iterator &it){
    return itv==it.itv;
}

bool conjunto::iterator::operator!=(const iterator &it){
    return itv!=it.itv;
}
/** conjunto::const_iterator **/
conjunto::const_iterator::const_iterator(){

}

conjunto::const_iterator::const_iterator(const conjunto::const_iterator &it){
    c_itv=it.c_itv;
}

conjunto::const_iterator::const_iterator(const conjunto::iterator &it){
    c_itv=it.itv;
}

const conjunto::entrada& conjunto::const_iterator::operator*() const{
    return *c_itv;
}

conjunto::const_iterator conjunto::const_iterator::operator++(int){
    conjunto::const_iterator antiguo(*this);
    ++c_itv;
    return antiguo;
}

conjunto::const_iterator& conjunto::const_iterator::operator++(){
    ++c_itv;
    return *this;
}

conjunto::const_iterator conjunto::const_iterator::operator--(int){
    conjunto::const_iterator antiguo(*this);
    --c_itv;
    return antiguo;
}

conjunto::const_iterator& conjunto::const_iterator::operator--(){
    --c_itv;
    return *this;
}

bool conjunto::const_iterator::operator==(const const_iterator &it){
    return c_itv==it.c_itv;
}

bool conjunto::const_iterator::operator!=(const const_iterator &it){
    return c_itv!=it.c_itv;
}

conjunto::const_iterator conjunto::cbegin() const{
    conjunto::const_iterator sal;
    sal.c_itv = vc.cbegin();
    return sal;
}

conjunto::const_iterator conjunto::cend() const{
    conjunto::const_iterator sal;
    sal.c_itv = vc.cend();
    return sal;
}

/** conjunto::arrest_iterator **/

conjunto::arrest_iterator::arrest_iterator(){

}

conjunto::arrest_iterator::arrest_iterator(const arrest_iterator &it){
    itv=it.itv;
    ptr=it.ptr;
}

const conjunto::entrada& conjunto::arrest_iterator::operator*(){
    return *itv;
}

conjunto::arrest_iterator conjunto::arrest_iterator::operator++(int){
    conjunto::arrest_iterator antiguo (*this);
    if (itv!=(*ptr).vc.end())
        itv++;

    while(itv!=(*ptr).vc.end() && !itv->getArrest())
        itv++;

    return antiguo;
}

conjunto::arrest_iterator conjunto::arrest_iterator::operator--(int){
    conjunto::arrest_iterator antiguo(*this);

    assert(itv!=(*ptr).vc.begin());
    do {
        itv--;
    } while (itv!=(*ptr).vc.begin() && !itv->getArrest());

    return antiguo;
}

conjunto::arrest_iterator& conjunto::arrest_iterator::operator++(){
    if (itv!=(*ptr).vc.end())
        itv++;

    while(itv!=(*ptr).vc.end() && !itv->getArrest())
        itv++;
    return *this;
}

conjunto::arrest_iterator& conjunto::arrest_iterator::operator--(){
    assert(itv!=(*ptr).vc.begin());
    do {
        itv--;
    } while (itv!=(*ptr).vc.begin() && !itv->getArrest());
    return *this;
}

bool conjunto::arrest_iterator::operator==(const arrest_iterator &it){
    return (itv==it.itv);
}

bool conjunto::arrest_iterator::operator!=(const arrest_iterator &it){
    return (itv!=it.itv);
}


conjunto::arrest_iterator conjunto::abegin(){
    conjunto::arrest_iterator it;
    it.itv=vc.begin();
    it.ptr=this;
    while (it.itv!=vc.end() && !it.itv->getArrest()){
        it.itv++;
    }
    return it;
}









conjunto::arrest_iterator conjunto::aend(){
    conjunto::arrest_iterator it;
    it.itv=vc.end();
    return it;
}

/** conjunto::const_arrest_iterator **/

conjunto::const_arrest_iterator::const_arrest_iterator(){

}

conjunto::const_arrest_iterator::const_arrest_iterator(const const_arrest_iterator &it){
    c_itv=it.c_itv;
    ptr=it.ptr;
}

const conjunto::entrada& conjunto::const_arrest_iterator::operator*() const{
    return *c_itv;
}

conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator++(int){
    conjunto::const_arrest_iterator antiguo(*this);
    if (c_itv!=(*ptr).vc.cend())
        c_itv++;

    while(c_itv!=(*ptr).vc.cend() && !c_itv->getArrest())
        c_itv++;

    return antiguo;
}

conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator--(int){
    conjunto::const_arrest_iterator antiguo(*this);

    assert(c_itv!=(*ptr).vc.cbegin());
    do {
        c_itv--;
    } while (c_itv!=(*ptr).vc.cbegin() && !c_itv->getArrest());

    return antiguo;
}

conjunto::const_arrest_iterator& conjunto::const_arrest_iterator::operator++(){
    if (c_itv!=(*ptr).vc.cend())
        c_itv++;

    while(c_itv!=(*ptr).vc.cend() && !c_itv->getArrest())
        c_itv++;
    return *this;
}

conjunto::const_arrest_iterator& conjunto::const_arrest_iterator::operator--(){
    assert(c_itv!=(*ptr).vc.cbegin());
    do {
        c_itv--;
    } while (c_itv!=(*ptr).vc.cbegin() && !c_itv->getArrest());
    return *this;
}


bool conjunto::const_arrest_iterator::operator==(const const_arrest_iterator &it){
    return (c_itv==it.c_itv);
}

bool conjunto::const_arrest_iterator::operator!=(const const_arrest_iterator &it){
    return (c_itv!=it.c_itv);
}

conjunto::const_arrest_iterator conjunto::cabegin() const{
    conjunto::const_arrest_iterator it;
    it.c_itv=vc.cbegin();
    while (it.c_itv!=vc.cend() && !it.c_itv->getArrest()){
        it.c_itv++;
    }
    return it;
}

conjunto::const_arrest_iterator conjunto::caend()const {
    conjunto::const_arrest_iterator it;
    it.c_itv=vc.cend();
    return it;
}
/** conjunto::description_iterator **/

conjunto::description_iterator::description_iterator(){

}

conjunto::description_iterator::description_iterator(const conjunto::description_iterator &it){
    itv=it.itv;
    ptr=it.ptr;
    descr=it.descr;
}

const conjunto::entrada& conjunto::description_iterator::operator*(){
    return *itv;
}


conjunto::description_iterator conjunto::description_iterator::operator++(int){
    conjunto::description_iterator antiguo(*this);
    do {
      itv++;
    } while (itv!=(*ptr).vc.end() && itv->getDESCR().rfind(descr)==string::npos);
    return antiguo;
}

conjunto::description_iterator& conjunto::description_iterator::operator++(){
    do {
      itv++;
    } while (itv!=(*ptr).vc.end() && itv->getDESCR().rfind(descr)==string::npos);
    return *this;
}

conjunto::description_iterator conjunto::description_iterator::operator--(int){
    conjunto::description_iterator antiguo(*this);
    assert(itv!=(*ptr).vc.begin());

    while (itv!=(*ptr).vc.begin() && itv->getDESCR().rfind(descr)==string::npos)
            itv--;

    return antiguo;
}

conjunto::description_iterator& conjunto::description_iterator::operator--(){
    assert(itv!=(*ptr).vc.begin());
    while (itv!=(*ptr).vc.begin() && itv->getDESCR().rfind(descr)==string::npos)
            itv--;

    return *this;
}

bool conjunto::description_iterator::operator==(const description_iterator &it){
    return (itv==it.itv);
}

bool conjunto::description_iterator::operator!=(const description_iterator &it){
    return (itv!=it.itv);
}

conjunto::description_iterator conjunto::dbegin(const string &descr) {
    conjunto::description_iterator it;
    it.itv=vc.begin();
    it.descr=descr;
    it.ptr=this;
    while (it.itv!=vc.end() && it.itv->getDESCR().rfind(descr)==string::npos){
        it.itv++;
    }

    return it;

}
conjunto::description_iterator conjunto::dend(){
    conjunto::description_iterator it;
    it.itv=vc.end();

    return it;
}

/** conjunto::const_description_iterator **/

conjunto::const_description_iterator::const_description_iterator(){

}

conjunto::const_description_iterator::const_description_iterator(const conjunto::const_description_iterator &it){
    c_itv=it.c_itv;
    ptr=it.ptr;
    descr=it.descr;
}

const conjunto::entrada& conjunto::const_description_iterator::operator*() const{
    return *c_itv;
}


conjunto::const_description_iterator conjunto::const_description_iterator::operator++(int){
    conjunto::const_description_iterator antiguo(*this);
    do {
      c_itv++;
    } while (c_itv!=(*ptr).vc.cend() && c_itv->getDESCR().rfind(descr)==string::npos);
    return antiguo;
}

conjunto::const_description_iterator& conjunto::const_description_iterator::operator++(){
    do {
      c_itv++;
    } while (c_itv!=(*ptr).vc.cend() && c_itv->getDESCR().rfind(descr)==string::npos);
    return *this;
}

conjunto::const_description_iterator conjunto::const_description_iterator::operator--(int){
    conjunto::const_description_iterator antiguo(*this);
    assert(c_itv!=(*ptr).vc.cbegin());

    while (c_itv!=(*ptr).vc.cbegin() && c_itv->getDESCR().rfind(descr)==string::npos)
            c_itv--;

    return antiguo;
}

conjunto::const_description_iterator& conjunto::const_description_iterator::operator--(){
    assert(c_itv!=(*ptr).vc.cbegin());
    while (c_itv!=(*ptr).vc.cbegin() && c_itv->getDESCR().rfind(descr)==string::npos)
            c_itv--;

    return *this;
}

bool conjunto::const_description_iterator::operator==(const const_description_iterator &it){
    return (c_itv==it.c_itv);
}

bool conjunto::const_description_iterator::operator!=(const const_description_iterator &it){
    return (c_itv!=it.c_itv);
}

conjunto::const_description_iterator conjunto::cdbegin(const string &descr) const {
    conjunto::const_description_iterator it;
    it.c_itv=vc.cbegin();
    it.descr=descr;
    it.ptr=this;
    while (it.c_itv!=vc.cend() && it.descr.rfind(descr)==string::npos){
        it.c_itv++;
    }

    return it;

}
conjunto::const_description_iterator conjunto::cdend() const{
    conjunto::const_description_iterator it;
    it.c_itv=vc.cend();

    return it;
}

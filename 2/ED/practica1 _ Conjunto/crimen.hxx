/**
  * @file crimen.hxx
  * @brief Implementación de la clase crimen.
  * @author Alejandro Campoy Nieves
  * @author David Criado Ramón
  */

/**
 * @brief Constructor por defecto. Id, longitud y latitud a 0, fecha nula, strings vacios.
 */
crimen::crimen(){
    ID=0;
    latitude=longitude=0.0;
  }
/**
 @brief Constructor de copia.
 @param x Objeto de tipo crimen a copiar.
 */
crimen::crimen(const crimen &x){
  if (this!=&x){
    this->ID=x.ID;
    this->case_number=x.case_number;
    this->date=x.date;
    this->IUCR=x.IUCR;
    this->primary_type=x.primary_type;
    this->location=x.location;
    this->arrest=x.arrest;
    this->domestic=x.domestic;
    this->latitude=x.latitude;
    this->longitude=x.longitude;
    this->description=x.description;
  }
}

/**
 * @brief Constructor a partir de string.
 * @param s Cadena a leer.
 */

crimen& crimen::operator=(const string &s){
    string::size_type inicio=0;
    string::size_type fin;
    string aux;

    fin=s.find_first_of(',');
    ID=stoi(s.substr(inicio,fin));

    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    case_number=s.substr(inicio,fin-inicio);

    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    date=s.substr(inicio,fin-inicio);

    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    // SALTO BLOCK

    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    IUCR=s.substr(inicio,fin-inicio);

    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    primary_type=s.substr(inicio,fin-inicio);

    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    description=s.substr(inicio,fin-inicio);

    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    location=s.substr(inicio,fin-inicio);

    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    arrest = (s.substr(inicio,fin-inicio)=="true") ? true : false;

    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    domestic = (s.substr(inicio,fin-inicio)=="true") ? true : false;


    for (int i=0; i<10; ++i){ // Salto hasta latitude
        inicio=fin+1;
        fin=s.find_first_of(',',inicio);
    }

    aux=s.substr(inicio,fin-inicio);
    if(aux.empty())
        latitude=0.0;
    else
        latitude=stod(aux);
    inicio=fin+1;
    fin=s.find_first_of(',',inicio);
    aux=s.substr(inicio,fin-inicio);
    if (aux.empty())
        longitude=0.0;
    else
        longitude=stod(s.substr(inicio,fin-inicio));
    return *this;
}

/**
 * @brief Modificador del atributo identificador.
 * @param id Valor a sobreescribir en el atributo ID.
 */
void crimen::setID(const long int &id){
    ID=id;
}

/**
 * @brief Modificador del atributo descripción.
 * @param s Valor a sobreescribir en el atributo description.
 */
void crimen::setDESCR(const string &s){
    description=s;
}


/**
 * @brief Modificador del atributo número de caso.
 * @param s Valor a sobreescribir en el atributo Case Number.
 */
void crimen::setCaseNumber(const string &s){
    case_number=s;
}
/**
 * @brief Modificador del atributo fecha.
 * @param d Valor a sobreescribir en el atributo Date.
 */
void crimen::setDate(const fecha &d){
    date=d;
}
/**
 * @brief Modificador del atributo arresto.
 * @param a Valor a sobreescribir en el atributo arrest.
 */
void crimen::setArrest(const bool &a){
    arrest=a;
}

/**
 * @brief Modificador del atributo doméstico.
 * @param d Valor a sobreescribir en el atributo domestic.
 */
void crimen::setDomestic(const bool &d){
    domestic=d;
}

/**
 * @brief Modificador del atributo IUCR.
 * @param iucr Valor a sobreescribir en el atributo iucr.
 */
void crimen::setIUCR(const string &iucr){
    IUCR=iucr;
}

/**
 * @brief Modificador del atributo tipo principal.
 * @param s valor a sobreescribir en el atributo Primary Type.
 */
void crimen::setPrimaryType(const string &s){
    primary_type=s;
}

/**
 * @brief Modificador del tipo de ubicación.
 * @param s Valor a sobreescribir en el atributo Location Description.
 */
void crimen::setLocation(const string &s){
    location=s;
}

/**
 * @brief Modificador del atributo latitud
 * @param d Valor a sobreescribir en el atributo latitude.
 */
void crimen::setLatitude(const double &d){
    latitude=d;
}

/**
 * @brief Modificador del atributo longitud.
 * @param d valor a sobreescribir en el atributo longitude.
 */
void crimen::setLongitude(const double &d){
    longitude=d;
}
/**
 * @brief Acceso al atributo ID
 * @return Atributo ID
 */
long int crimen::getID() const{
  return ID;
}

/**
 * @brief Accede al número de caso
 * @return Atributo CaseNumber
 */
string crimen::getCaseNumber() const{
  return case_number;
}

/**
 * @brief Accede a la fecha
 * @return Atributo Fecha
 */
fecha crimen::getDate() const{
  return date;
}

/**
 * @brief Accede a la descripción
 * @return Atributo description
 */
string crimen::getDESCR() const{
    return description;
}

/**
 * @brief Accede al IUCR
 * @return Atributo IUCR
 */
string crimen::getIUCR() const{
    return IUCR;
}

/**
 * @brief Accede al tipo primario.
 * @return Atributo Primary Type
 */
string crimen::getPrimaryType() const{
    return primary_type;
}

/**
 * @brief Accede al tipo de ubicación.
 * @return Atributo Location Description.
 */
string crimen::getLocation() const{
    return location;
}

/**
 * @brief Accede al atributo arresto.
 * @return Atributo Arrest.
 */
bool crimen::getArrest() const{
    return arrest;
}

/**
 * @brief Accede al atributo doméstico.
 * @return Atributo Domestic.
 */
bool crimen::getDomestic() const{
    return domestic;
}
/**
 * @brief Accede al atributo latitud.
 * @return Atributo Latitude.
 */
double crimen::getLatitude() const{
    return latitude;
}
/**
 * @brief Accede al atributo longitud
 * @return Atributo Longitude.
 */
double crimen::getLongitude() const{
    return longitude;
}
/**
 * @brief Sobrecarga del operador de extracción de flujo.
 * @param os Flujo de salida.
 * @param x Crimen a mostrar.
 * @return Referencia al flujo de salida.
 */
ostream& operator<<(ostream &os, const crimen &x){
  os << x.ID << "," << x.case_number << "," << x.date << "," << x.IUCR << ","
  << x.primary_type << "," << x.description << "," << x.location << ","
  << boolalpha << x.arrest << "," << x.domestic << "," << x.latitude << ","
  << x.longitude;
  return os;
}

/**
 * @brief Sobrecarga del operador de asignación.
 * @param x crimen a asignar.
 * @return devuelve referencia al objeto de la clase (this).
 */
crimen& crimen::operator=(const crimen &x){
 if (this!=&x){
    this->ID=x.ID;
    this->case_number=x.case_number;
    this->date=x.date;
    this->IUCR=x.IUCR;
    this->primary_type=x.primary_type;
    this->location=x.location;
    this->arrest=x.arrest;
    this->domestic=x.domestic;
    this->latitude=x.latitude;
    this->longitude=x.longitude;
    this->description=x.description;
  }
  return *this;
}

/**
 * @brief Sobrecarga del operador de igualdad.
 * @param x crimen a comparar.
 * @return True si son iguales, false en caso contrario.
 */
bool crimen::operator==(const crimen &x) const{
  return ID==x.ID;
}

/**
 * @brief Sobrecarga del operador menor.
 * @param x Crimen a comparar.
 * @return Devuelve si el crimen es menor.
 */
bool crimen::operator<(const crimen &x) const{
  return ID<x.ID;
}



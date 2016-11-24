#include "crimen.h"
/**
 * @brief Constructor por defecto. Id, longitud y latitud a 0, fecha nula, strings vacios.
 */
crimen::crimen(){}

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
    this->description=x.description;
    this->arrest=x.arrest;
    this->domestic=x.domestic;
    this->latitude=x.latitude;
    this->longitude=x.longitude;

  }
}


/**
 * @brief Constructor a partir de string.
 * @param s Cadena a leer.
 */

crimen& crimen::operator=(const string &s){
    istringstream aux(s);
    string split;

    getline(aux,split, ',');
    ID=stol(split);
    getline(aux,case_number, ',');
    getline(aux,split, ',');
    date=split;
    getline(aux,split, ','); // Salto BLOCK
    getline(aux,IUCR, ',');
    getline(aux,description, ',');
    getline(aux,split, ',');
    description += ' ' + split;
    getline(aux,split, ',');
    description += ' ' + split;
    getline(aux,split, ',');
    arrest = split== "true";
    getline(aux,split, ',');
    domestic = split == "true";
    for (int i=0; i<9; ++i)
        aux.ignore(numeric_limits<streamsize>::max(),',');
    getline(aux,split, ',');
    if (split=="")
        latitude=0;
    else
        latitude=stod(split);
    getline(aux,split, ',');
    if (split=="")
        longitude=0;
    else
        longitude=stod(split);

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
 * @param id Valor a sobreescribir en el atributo description.
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
  << x.description  << ","
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

bool crimen::operator>(const crimen &x) const{
  return ID>x.ID;
}
/**
 * @brief Sobrecarga del operador menor
 * @param id ID a comparar
 * @return Devuelve si el crimen tiene una ID menor que la proporcionada
 */
bool crimen::operator<(const long int &id) const{
    // Este método no ha sido solicitado pero facilita la legibilidad de código
    // posterior al no haber necesidad de crear ningún functor, lambda o crimen falso
    return ID<id;
}





/**
  * @file fecha.hxx
  * @brief Implementación de la clase fecha.
  * @author Alejandro Campoy Nieves
  * @author David Criado Ramón
  */
/**
 @brief Constructor por defecto de la clase fecha.
 Inicializa los datos a "00-00-0000 00:00:00 AM"
*/
fecha::fecha(){
	sec=0;
	min=0;
	hour=0;
	mday=0;
	mon=0;
	year=0;
}
/**
 @brief Constructor de copia.
 @param x Objeto de tipo fecha a copiar.
 */
fecha::fecha(const fecha & x){
    sec=x.sec;
    min=x.min;
    hour=x.hour;
    mday=x.mday;
    mon=x.mon;
    year=x.year;
}
 /**
  @brief Crea un objeto fecha a partir de un string
  @param s es un string con el formato "MM-DD-AAAA HH:MM:SS AM"
  */
  fecha::fecha (const string & s){
      this->mon=stoi(s.substr(0,2));
      this->mday=stoi(s.substr(3,2));
      this->year=stoi(s.substr(6,4));
      this->hour=stoi(s.substr(11,2));
      this->min=stoi(s.substr(14,2));
      this->sec=stoi(s.substr(17,2));
      if (s.substr(19,2)=="PM")
          hour+=12;
   }

/**
 @brief Operador de asignación para fecha.
 @param f objeto de tipo fecha.
 @return Referencia al objeto fecha (this).
 */
fecha & fecha::operator=(const fecha & f){
    if (this != &f){
      this->sec=f.sec;
      this->min=f.min;
      this->hour=f.hour;
      this->mday=f.mday;
      this->mon=f.mon;
      this->year=f.year;
    }
    return *this;
}
/**
 @brief Operador de asignación para la clase fecha con fechas en formato string.
 @param s como string fecha en formato "MM-DD-AAAA HH:MM:SS AM".
 @return Referencia al objeto fecha (this).
 */
fecha & fecha::operator=(const string & s){
    mon=stoi(s.substr(0,2));
    mday=stoi(s.substr(3,2));
    year=stoi(s.substr(6,4));
    hour=stoi(s.substr(11,2));
    min=stoi(s.substr(14,2));
    sec=stoi(s.substr(17,2));
    if (s.substr(19,2)=="PM")
        hour+=12;

    return *this;
}

/**
 @brief Da la verisón string de la clase fecha
 @return Devuelve el string de la fecha en formato "MM-DD-AAAA HH:MM:SS AM"
*/
string fecha::toString() const{
    int hora=(hour>=12) ? (hour-12) : hour;
    string a=(hour>=12) ? "PM" : "AM";


    string f(to_string(mon)+"/"+to_string(mday)+"/"+to_string(year)+" "  //to_string(int) tranformara dicho nombretipo en string.
    + to_string(hora) + ":" + to_string(min) + ":" + to_string(sec) + " " + a);
    return f;


}

 /**
  @brief Sobrecarga del operador << para los flujos de entrada de la clase.
  @param os como flujo de entrada dado por referencia para indicar las operaciones a realizar.
  @param f como fecha dado por referencia a partir de la cual se mete sus datos en el flujo.
  @return Nos devuelve dicho flujo pasado como primer parámetro.
*/
 ostream& operator<< ( ostream& os, const fecha & f){ //no aparece fecha::operator porque es un mtodo friend(no necesita ser de la clase).
    os << setfill('0') << setw(2) << f.mon;
    os << "/";
    os << setfill('0') << setw(2) << f.mday;
    os << "/";
    os << setfill('0') << setw(2) << f.year;
    os << " ";
    if(f.hour<=12)
        os << setfill('0') << setw(2) << f.hour;
    else
        os << setfill('0') << setw(2) << (f.hour-12);
    os << ":";
    os << setfill('0') << setw(2) << f.min;
    os << ":";
    os << setfill('0') << setw(2) << f.sec;
    os << " ";
    if(f.hour<=12)
        os << "AM";
    else
        os << "PM";
   return os;
 }
 /**
  @brief Sobrecarga del operador de igualdad para la clase fecha
  @param f como fecha a comparar
  @return True si son iguales y false en caso contrario
*/
bool fecha::operator==(const fecha & f) const{
    return (mon==f.mon && mday==f.mday && year==f.year &&
          hour==f.hour && min==f.min && sec==f.sec);
}

/**
 @brief Sobrecarga del operador de menor para la clase fecha
 @param f como fecha a comparar
 @return True si la clase es menor que f y false en caso contrario
*/
bool fecha::operator<(const fecha & f)const{
    if (year<f.year)
        return true;
    else if(year==year){
         if(mon<f.mon)
            return true;
         else if(mon==f.mon){
            if(mday<f.mday)
                 return true;
            else if(mday==f.mday){
                if(hour<f.hour)
                    return true;
                else if(hour==f.hour){
                     if(min<f.min)
                         return true;
                     else if(min==f.min){
                     if(sec<f.sec)
                        return true;
                     else
                        return false;
                     }
                 }
             }
         }
     }
    return false;
}

/**
 @brief Sobrecarga del operador de mayor para la clase fecha
 @param f como fecha a comparar
 @return True si la clase es mayor que f y false en caso contrario
*/
bool fecha::operator>(const fecha & f) const{
    if (year>f.year)
        return true;
    else if(year==year){
         if(mon>f.mon)
            return true;
         else if(mon==f.mon){
            if(mday>f.mday)
                 return true;
            else if(mday==f.mday){
                if(hour>f.hour)
                    return true;
                else if(hour==f.hour){
                     if(min>f.min)
                         return true;
                     else if(min==f.min){
                     if(sec>f.sec)
                        return true;
                     else
                        return false;
                     }
                 }
             }
         }
     }
    return false;
}

/**
 @brief Sobrecarga del operador de menor o igual para la clase fecha
 @param f como fecha a comparar
 @return True si la clase es menor o igual que f y false en caso contrario
*/
bool fecha::operator<=(const fecha &f) const{
  return (*this<f || *this==f);  //Utilizamos la sobrecarga de los dos operadores anteriores :D
}

/**
 @brief Sobrecarga del operador de mayor o igual para la clase fecha
 @param f como fecha a comparar
 @return True si la clase es mayor o igual que f y false en caso contrario
*/
bool fecha::operator>=(const fecha &f) const{
  return (*this>f || *this==f);   //Utilizamos la sobrecarga de los operadores anteriores y no tenemos que repetir código :D.
}

/**
 @brief Sobrecarga del operador de igualdad para la clase fecha
 @param f como fecha a comparar
 @return True si no son iguales y false si son iguales
*/

bool fecha::operator!=(const fecha &f) const{
  return (*this!=f);
}








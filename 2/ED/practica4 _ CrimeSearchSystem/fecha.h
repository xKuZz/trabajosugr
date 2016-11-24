/**
 * @file fecha.h
 * @brief Declaración de la clase fecha.
 * @author Alejandro Campoy Nieves
 * @author David Criado Ramón
 */
#ifndef __FECHA_H
#define __FECHA_H

#include <string>  // Necesario para usar los metodos de la clase string.
#include <iostream>
#include <iomanip>  //Necesario para asignar espacios vacios y de colocacion en los flujos de salida como setw o setfill
using namespace std;

//! Clase fecha,  contiene toda la información asociada a una fecha con el formato  mm/dd/aaaa hh:mm:ss AM/PM
/*! * Toda fecha debe cumplir que:
 * \invariant  0 \f$\leq\f$ hour(hora) \f$<\f$ 24
 * \invariant  0 \f$\leq\f$ min(minuto) \f$<\f$ 60
 * \invariant  0 \f$\leq\f$ sec(segundo) \f$<\f$ 60
 * \invariant  0 \f$\leq\f$ mday(día) \f$\leq\f$ 31
 * \invariant  0 \f$\leq\f$ mon(mes) \f$\leq\f$ 12
 */
/*! Además su función de abstracción es:\n
 *  AF: Representacion \f$\to\f$ Abstraccion\n
 * Dada la tupla \f$(anio,mes,dia,hora,minuto,segundo,am/pm) \f$   \f$\Rightarrow \f$ f\n
 * F es un objeto abstracto que se instacia como una tupla de año, mes, día, hora, minutos y segundos.
 *
*/

class fecha {

public:
 /**
  @brief Constructor por defecto de la clase fecha.
  Inicializa los datos a "00-00-0000 00:00:00 AM"
 */
 fecha ();
 /**
  @brief Constructor de copia.
  @param x Objeto de tipo fecha a copiar.
  */
 fecha(const fecha & F);
 fecha(fecha&& F);
 /**
  @brief Crea un objeto fecha a partir de un string.
  @param s es un string con el formato "MM-DD-AAAA HH:MM:SS AM".
  */
 fecha (const string & s);
 /**
  @brief Operador de asignación para fecha.
  @param f objeto de tipo fecha.
  @return Referencia al objeto fecha (this).
  */
 fecha & operator=(const fecha & f);
 /**
  @brief Operador de asignación para la clase fecha con fechas en formato string.
  @param s como string fecha en formato "MM-DD-AAAA HH:MM:SS AM".
  @return Referencia al objeto fecha (this).
  */
 fecha & operator=(const string & s);
 /**
  @brief Da la verisón string de la clase fecha
  @return Devuelve el string de la fecha en formato "MM-DD-AAAA HH:MM:SS AM"
 */
 string toString( ) const;

// Operadores relacionales
 /**
  @brief Sobrecarga del operador de igualdad para la clase fecha
  @param f como fecha a comparar
  @return True si son iguales y false en caso contrario
*/
 bool operator==(const fecha & f) const;
 /**
  @brief Sobrecarga del operador de menor para la clase fecha
  @param f como fecha a comparar
  @return True si la clase es menor que f y false en caso contrario
 */
 bool operator<(const fecha & f)const;
 /**
  @brief Sobrecarga del operador de mayor para la clase fecha
  @param f como fecha a comparar
  @return True si la clase es mayor que f y false en caso contrario
 */
 bool operator>(const fecha & f) const;
 /**
  @brief Sobrecarga del operador de menor o igual para la clase fecha
  @param f como fecha a comparar
  @return True si la clase es menor o igual que f y false en caso contrario
 */
 bool operator<=(const fecha & f)const;
 /**
  @brief Sobrecarga del operador de mayor o igual para la clase fecha
  @param f como fecha a comparar
  @return True si la clase es mayor o igual que f y false en caso contrario
 */
 bool operator>=(const fecha & f) const;
 /**
  @brief Sobrecarga del operador de igualdad para la clase fecha
  @param f como fecha a comparar
  @return True si no son iguales y false si son iguales
 */
 bool operator!=(const fecha & f)const;

private:
  int  sec;   // seconds of minutes from 0 to 59
  int  min;   // minutes of hour from 0 to 59
  int  hour;  // hours of day from 0 to 24
  int  mday;  // day of month from 1 to 31
  int  mon;   // month of year from 0 to 11
  int  year;  // year since 2000

friend  ostream& operator<< ( ostream& os, const fecha & f);
};

/**
 @brief Sobrecarga del operador << para los flujos de salida de la clase.
 @param os como flujo de entrada dado por referencia para indicar las operaciones a realizar.
 @param f como fecha dado por referencia a partir de la cual se mete sus datos en el flujo.
 @return Nos devuelve dicho flujo pasado como primer parámetro.
*/
 ostream& operator<< ( ostream& os, const fecha & f);


#include "fecha.hxx" // Incluimos la implementacion.


#endif

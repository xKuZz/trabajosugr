/**
  * @file crimen.h
  * @brief Declaración de la clase crimen.
  * @author Alejandro Campoy Nieves
  * @author David Criado Ramón
  */
#ifndef __CRIMEN_H
#define __CRIMEN_H

#include <string>
#include <iostream>

#include "fecha.h"

//! Clase crimen,  contiene toda la información asociada a un crimen
 /*! \invariant  ID \f$\>\f$ 0 \f$<\f$ */

/*! Además su función de abstracción es:\n
 *  AF: Representacion \f$\to\f$ Abstraccion\n
 * Dada la tupla \f$(ID,CaseNumber,Date,IUCR,Primary Type, Description, Location,
 * Arrest, Domestic, Latitude, Longitude) \f$   \f$\Rightarrow \f$ f\n
 * C es un objeto abstracto al que denominamos conjunto y que instanciamos como un
 * entero (ID), 1 fecha (fecha), 2 double (Latitud y Longitud),
 * 5 string (Número de caso, IUCR, Tipo Primario, Descripción y Localización)
 * y 2 valores booleanos (Arresto y Doméstico).
*/


class crimen {
 public:
  // CONSTRUCTORES
  /**
   * @brief Constructor por defecto. Id, longitud y latitud a 0, fecha nula, strings vacios.
   */
  crimen();

  /**
   @brief Constructor de copia.
   @param x Objeto de tipo crimen a copiar.
   */
  crimen(const crimen &x);


  /**
   * @brief Sobrecarga del operador de asignación a partir de string.
   * @param s Cadena a leer.
   */
  crimen& operator=(const string &s);

  /**
   * @brief Sobrecarga del operador de asignación.
   * @param c crimen a asignar.
   * @return devuelve referencia al objeto de la clase (this).
   */
  crimen& operator=(const crimen &c);

  // MODIFICADORES
  /**
   * @brief Modificador del atributo identificador.
   * @param id Valor a sobreescribir en el atributo ID.
   */
  void setID(const long int &id);

  /**
   * @brief Modificador del atributo número de caso.
   * @param s Valor a sobreescribir en el atributo Case Number.
   */
  void setCaseNumber(const string &s);

  /**
   * @brief Modificador del atributo fecha.
   * @param d Valor a sobreescribir en el atributo Date.
   */
  void setDate(const fecha &d);

  /**
   * @brief Modificador del atributo IUCR.
   * @param iucr Valor a sobreescribir en el atributo iucr.
   */
  void setIUCR(const string &iucr);

  /**
   * @brief Modificador del atributo arresto.
   * @param a Valor a sobreescribir en el atributo arrest.
   */
  void setArrest(const bool &a);

  /**
   * @brief Modificador del atributo doméstico.
   * @param d Valor a sobreescribir en el atributo domestic.
   */
  void setDomestic(const bool &d);

  /**
   * @brief Modificador del atributo descripción.
   * @param s Valor a sobreescribir en el atributo description.
   */
  void setDESCR(const string &s);

  /**
   * @brief Modificador del atributo tipo principal.
   * @param s valor a sobreescribir en el atributo Primary Type.
   */
  void setPrimaryType(const string &s);

  /**
   * @brief Modificador del tipo de ubicación.
   * @param s Valor a sobreescribir en el atributo Location Description.
   */
  void setLocation(const string &s);

  /**
   * @brief Modificador del atributo latitud
   * @param d Valor a sobreescribir en el atributo latitude.
   */
  void setLatitude(const double &d);

  /**
   * @brief Modificador del atributo longitud.
   * @param d valor a sobreescribir en el atributo longitude.
   */
  void setLongitude(const double &d);

  // ACCESORES
  
  /**
   * @brief Acceso al atributo ID
   * @return Atributo ID
   */
  long int getID() const;

  /**
   * @brief Accede al número de caso
   * @return Atributo CaseNumber
   */
  string getCaseNumber() const;

  /**
   * @brief Accede a la fecha
   * @return Atributo Fecha
   */
  fecha getDate() const;

  /**
   * @brief Accede a la descripción
   * @return Atributo description
   */
  string getDESCR() const;

  /**
   * @brief Accede al IUCR
   * @return Atributo IUCR
   */
  string getIUCR() const;

  /**
   * @brief Accede al tipo de ubicación.
   * @return Atributo Location Description.
   */
  string getLocation() const;

  /**
   * @brief Accede al tipo primario.
   * @return Atributo Primary Type
   */
  string getPrimaryType() const;

  /**
   * @brief Accede al atributo arresto.
   * @return Atributo Arrest.
   */
  bool getArrest() const;

  /**
   * @brief Accede al atributo doméstico.
   * @return Atributo Domestic.
   */
  bool getDomestic() const;

  /**
   * @brief Accede al atributo latitud.
   * @return Atributo Latitude.
   */
  double getLatitude() const;

  /**
   * @brief Accede al atributo longitud
   * @return Atributo Longitude.
   */
  double getLongitude() const;
  

   // OPERADORES RELACIONALES

   /**
    * @brief Sobrecarga del operador de igualdad.
    * @param x crimen a comparar.
    * @return True si son iguales, false en caso contrario.
    */
   bool operator==(const crimen &x) const;

   /**
    * @brief Sobrecarga del operador menor.
    * @param x Crimen a comparar.
    * @return Devuelve si el crimen es menor.
    */
   bool operator<(const crimen &x) const;
   bool operator<(const long int &id) const;

  private:
   friend ostream& operator<< ( ostream &os , const crimen &x );
   //Atributos 
   long int ID; 
   string case_number;
   fecha date;
   string IUCR;
   string primary_type;
   string description;
   string location;
   bool arrest;
   bool domestic;
   double latitude;
   double longitude;
};

 /**
  * @brief Sobrecarga del operador de extracción de flujo.
  * @param os Flujo de salida.
  * @param x Crimen a mostrar.
  * @return Referencia al flujo de salida.
  */
  ostream& operator<< ( ostream &os, const crimen &x);


#include "crimen.hxx"
#endif

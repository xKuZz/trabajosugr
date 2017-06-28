#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <iostream>
#include <fstream>
#include <vector>

/** @brief Esta clase se encargará de leer los datos del archivo y guardar las matrices en cuestión.
 */
class InputData
{
public:
    // Se considera que todos los datos leídos son enteros (si no fuese modificar aquí).
    using Type = int;
private:
    /** @brief Tamaño del problema.
     */
    int n;

    /** @brief Matriz de distancias.
     */
    std::vector<std::vector<Type>> distance;

    /** @brief Matriz de flujos.
     */
    std::vector<std::vector<Type>> stream;

    /** @brief Nombre del archivo elegido.
     */
    std::string fileName;
public:
    /** @brief Lee del archivo indicado los datos de entrada (se quitan datos anterirores si los hubiese)
     *  @param fileName Ruta en la que se encuentra el archivo de entrada.
     *  @pre Se supone que el archivo presenta un formato correcto
     */
    void read(const std::string& fileName);

    /** @brief Devuelve el flujo que va desde la primera localización pasada como parámetro hasta la segunda.
     *  @param origin Posición en la matriz (empezando por 0) del elemento desde que sale el flujo.
     *  @param destination Posición en la matriz (empezando por 0) del elemento al que llega el flujo.
     *  @return Flujo que va desde la primera localización pasada como parámetro hasta la segunda.
     */
    Type getStream(int origin, int destination) const;

    /** @brief Devuelve la distancia que hay desde la primera localización pasada como parámetro hasta la segunda.
     *  @param origin Posición en la matriz (empezando por 0) del elemento desde el que sale la ruta.
     *  @param destination Posición en la matriz (empezando por 0) del elemento al que llega la ruta.
     *  @return Distancia que hay desde la primera localización pasada como parámetro hasta la segunda.
     */
    Type getDistance(int origin, int destination) const;

    /** @brief Devuelve el tamaño del problema.
     *  @return Tamaño del problema.
     */
    int size() const;

    /** @brief Devuelve la ruta del archivo que ha sido leído.
     *  @return Ruta del archivo que ha sido leído.
     */
    std::string getFileName() const;

    friend std::ostream& operator<<(std::ostream& os, const InputData& input);
};

/** @brief Sobrecarga del operador de salida para flujos de los datos de entrada.
 *  @param os Flujo a utilizar.
 *  @param input Datos leídos.
 *  @return Referencia al flujo tras ser modificado.
 */
std::ostream& operator<<(std::ostream& os, const InputData& input);

#endif // INPUTDATA_H

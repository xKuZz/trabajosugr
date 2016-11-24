#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;
using namespace std::chrono;
using ConvenienciaGlobal = long int;
using Conveniencia = int;
using Persona = int;
using Mesa = vector<Persona>;
using MatrizConveniencia = vector<vector<Conveniencia>>;

// Muestra la matriz de conveniencias
#define MOSTRARMATRIZCONVENIENCIAS 0

// Activar para sacar datos para gráficas
#define ONLYPRINTTIME 0

// Activar para sólo sacar VUELTAATRAS (gráficas)
#define ONLYVUELTAATRAS 0



/** @brief Genera conveniencias aleatoriamente. La conveniencia con uno mismo
 * está iniciada a -1
 */
MatrizConveniencia generarConveniencia(int N) {
    MatrizConveniencia salida(N,Mesa(N, -1));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,100);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i != j)
            salida[i][j] = dis(gen);

    return salida;
}

ConvenienciaGlobal calcularConvenienciaGlobal(const Mesa& mesa,
                                  const MatrizConveniencia& v) {
    // Casos especiales

    if (mesa.size() == 0)
        return 0; // No hay nadie en la mesa
    else if (mesa.size() == 1)
        return 200; // Sólo hay uno en la mesa
    else if (mesa.size() == 2)
        return 2*v[mesa[0]][mesa[1]] + 2*v[mesa[1]][mesa[0]]; // Hay 2 en la mesa


    ConvenienciaGlobal salida = 0;
    // Como en el vector el 0 y el N - 1 no estan contiguos entre sí los
    // calculamos primero
    salida += v[mesa[0]][mesa[mesa.size()-1]] + v[mesa[0]][mesa[1]];
    salida += v[mesa[mesa.size()-1]][mesa[mesa.size()-2]]
           +  v[mesa[mesa.size()-1]][mesa[0]];

    // Calculamos el resto de la conveniencia
    for (unsigned i = 1; i < mesa.size() - 1; ++i)
        salida += v[mesa[i]][mesa[i-1]] + v[mesa[i]][mesa[i+1]];

    return salida;
}

ConvenienciaGlobal fuerzaBruta(const MatrizConveniencia& v,
                                     Mesa& mejorMesa) {
    // Creamos una mesa ordenada numéricamente
    Mesa mesa;
    for (unsigned i = 0; i < v.size(); ++i)
        mesa.push_back(i);

    // Calculamos la valoración de la mesa inicial
    auto valoracion = calcularConvenienciaGlobal(mesa,v);
    mejorMesa = mesa;

    // Realizamos todas las permutaciones y comprobamos si la nueva permutación
    // es mejor que el guardado como mejor
    while (next_permutation(mesa.begin(),mesa.end())) {
        auto valoracionLocal = calcularConvenienciaGlobal(mesa,v);
        if (valoracionLocal > valoracion) {
            mejorMesa = mesa;
            valoracion = valoracionLocal;
        }
    }

    return valoracion;
}

class Solucion {
    // Apunta a la matriz de conveniencias creada
    const MatrizConveniencia* conveniencias;
    Mesa mesaActual;
    Mesa mejorMesa;
    ConvenienciaGlobal mejor;

    int nComensalesTotales;

public:
    Solucion(const MatrizConveniencia* conveniencias) {
        nComensalesTotales = conveniencias->size();
        this->conveniencias = conveniencias;
        mejor = -1;
    }

    int size() const {
        return nComensalesTotales;
    }
    void iniciar() {

        mesaActual.push_back(-1);
    }

    void siguienteValor(int indice) {
        ++mesaActual[indice];
        while(count(mesaActual.begin(),mesaActual.end(), mesaActual[indice]) > 1)
            ++mesaActual[indice];
    }

    bool todosGenerados(int indice) {
        return mesaActual[indice] == nComensalesTotales;
    }

    bool esFactible() {
        auto convenienciaActual = calcularConvenienciaGlobal(mesaActual, *conveniencias);
        int personasRestantes = nComensalesTotales - mesaActual.size();

        ConvenienciaGlobal convenienciaMaxima = convenienciaActual + 200 * personasRestantes;

        return convenienciaMaxima > mejor;
    }

    void actualizarMejor() {
        auto convenienciaActual = calcularConvenienciaGlobal(mesaActual, *conveniencias);
        if (convenienciaActual > mejor) {
            mejor = convenienciaActual;
            mejorMesa = mesaActual;
        }
    }

    void eliminarUltimo() {
        mesaActual.erase(mesaActual.end()-1);
    }

    Mesa mesa() const {
        return mejorMesa;
    }
};

void vueltaAtrasRecursiva(Solucion& sol, int i) {
    sol.iniciar();
    sol.siguienteValor(i);
    while (!sol.todosGenerados(i)) {
        if (sol.esFactible())
            vueltaAtrasRecursiva(sol, i+1);
        if (i == sol.size()-1)
            sol.actualizarMejor();
        sol.siguienteValor(i);
    }



    sol.eliminarUltimo();
}

ConvenienciaGlobal vueltaAtras(const MatrizConveniencia& v,
                                     Mesa& mejorMesa) {
    Solucion miSolucion(&v);
    vueltaAtrasRecursiva(miSolucion,0);

    mejorMesa = miSolucion.mesa();
    auto VA = calcularConvenienciaGlobal(mejorMesa, v);
    return VA;
}




int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Introducir como argumento numero de comensales" << endl;
        return -1;
    }

    int N = atoi(argv[1]);
    auto conveniencias = generarConveniencia(N);

    Mesa mesaFB;
    Mesa mesaVA;
    high_resolution_clock::time_point tAntes, tDespues;

#if (MOSTRARMATRIZCONVENIENCIAS && !ONLYPRINTTIME)
    cout << "Matriz de conveniencias" << endl;
    for (auto fila : conveniencias) {
        for (auto d: fila)
            cout << d << '\t';
        cout << endl;
    }
#endif

#if !ONLYPRINTTIME
    tAntes = high_resolution_clock::now();
    auto FB = fuerzaBruta(conveniencias, mesaFB);
    tDespues = high_resolution_clock::now();
    duration<double> tiempoFB = duration_cast<duration<double>>(tDespues - tAntes);


    cout << endl << "FUERZA BRUTA" << endl << endl;
    for (auto persona : mesaFB)
        cout << persona << endl;

    cout << endl << "La conveniencia global de la mesa es de: " << FB << endl;
    cout << "El algoritmo de fuerza bruta ha tardado: " << tiempoFB.count() << endl;

    tAntes = high_resolution_clock::now();
    auto VA = vueltaAtras(conveniencias, mesaVA);
    tDespues = high_resolution_clock::now();
    duration<double> tiempoVA = duration_cast<duration<double>>(tDespues - tAntes);


    cout << endl << "VUELTA ATRAS" << endl << endl;

    for (auto persona : mesaVA)
        cout << persona << endl;

    cout << endl << "La conveniencia global de la mesa es de: " << VA << endl;
     cout << "El algoritmo de vuelta atras ha tardado: " << tiempoVA.count() << endl;
#else
 
    ofstream archivoVA("cenaGalaVA.dat",ofstream::app);
  #if !ONLYVUELTAATRAS
    ofstream archivoFB("cenaGalaFB.dat",ofstream::app);

    tAntes = high_resolution_clock::now();
    fuerzaBruta(conveniencias, mesaFB);
    tDespues = high_resolution_clock::now();
    duration<double> tiempoFB = duration_cast<duration<double>>(tDespues - tAntes);

    cout << "Fuerza bruta: " << N << " " << tiempoFB.count() << endl;
    archivoFB << N << " " << tiempoFB.count() << endl;
  #endif

    tAntes = high_resolution_clock::now();
    vueltaAtras(conveniencias, mesaVA);
    tDespues = high_resolution_clock::now();
    duration<double> tiempoVA = duration_cast<duration<double>>(tDespues - tAntes);

    cout << "Vuelta atras: " << N << " " << tiempoVA.count() << endl;
    archivoVA << N << " " << tiempoVA.count() << endl;


#endif
}

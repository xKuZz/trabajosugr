#include <algorithm>
#include <chrono>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;
using namespace std::chrono;
using Ciudad = int;
using Distancia = int;
using Coordenadas = pair<int, int>;
using MapaCiudades = vector<Coordenadas>;
using MatrizDistancias = vector<vector<Distancia>>;
using Trayectoria = vector<Ciudad>;

#define X 0
#define Y 1


MapaCiudades leerArchivo(char* nombre) {
    // Esta función sólo lee los datos del archivo de entrada.
    ifstream archivo(nombre);;
    archivo.ignore(10);

    int N = 0;
    archivo >> N;


    if (!archivo.is_open() || N == 0){
        cerr << "Error de lectura de archivo";
        exit (-1);
    }

    MapaCiudades salida;
    salida.reserve(N);
    double x, y;
    for (int i = 0; i < N; ++i) {
        archivo >> x;
        archivo >> x;
        archivo >> y;
        salida.emplace_back(x, y);
    }

    return salida;
}

Distancia distanciaCiudad(Ciudad c1, Ciudad c2, const MapaCiudades& v) { // Distancia Euclídea
    return round(sqrt(pow(get<X>(v[c1])-get<X>(v[c2]),2) +
                      pow(get<Y>(v[c1])-get<Y>(v[c2]),2)));
}


MatrizDistancias calcularMatrizDistancias(const MapaCiudades& v) {
    // Matriz con todas las distancias, distancias[i][j] == distancias[j][i]
    MatrizDistancias salida;
    vector<Distancia> fila;
    for (unsigned i = 0; i < v.size(); ++i) {
        fila.clear();
        for (unsigned j = 0; j < v.size(); ++j)
            if (i != j)
              fila.push_back(distanciaCiudad(i,j,v));
            else
              fila.push_back(-1);
        salida.push_back(fila);
    }
    return salida;
}
vector<Ciudad> seleccionarTriangulo(const MapaCiudades& loc) {
    // Buscamos la más al norte, la más al este y la mas al oste y devuelve un vector con las mismas;
    Coordenadas norte, este, oeste;
    Ciudad cnorte = 0, ceste = 0, coeste = 0;
    norte = este = oeste = loc.front();
    for (unsigned city = 0; city < loc.size(); ++city) {
        if (get<Y>(loc[city]) >= get<Y>(norte)) { norte = loc[city]; cnorte = city ;}
        if (get<X>(loc[city]) >= get<X>( este)) {  este = loc[city]; ceste  = city ;}
        if (get<X>(loc[city]) <= get<Y>(oeste)) { oeste = loc[city]; coeste = city ;}
    }
    Trayectoria salida;
    salida.push_back(cnorte);
    salida.push_back(ceste);
    salida.push_back(coeste);
    salida.push_back(cnorte);
    return salida;
}

Distancia agregarCiudad(Trayectoria trayectoria, Ciudad city, unsigned posicion,
                        const MatrizDistancias& distancias) {
    // Trayectoria se pasa por copia puesto que no se quiere modificar la trayectoria inicial,
    // sólo calcular la supuesta distancia del camino.
    Distancia dist = 0;
    trayectoria.insert(trayectoria.begin()+posicion,city);
    for (unsigned i = 1; i < trayectoria.size(); ++i)
        dist += distancias[trayectoria[i-1]][trayectoria[i]];
    return dist;
}

Distancia heuristicaInsercion(const MapaCiudades& ciudades,
                              const MatrizDistancias& distancias,
                              Trayectoria& trayectoria) {
    // Primero seleccionamos las ciudades más al norte, este y oeste
    trayectoria = seleccionarTriangulo(ciudades);

    // Recorremos las ciudades en orden numérico
    for (unsigned city = 0; city < ciudades.size(); ++city) {
        // Si no se encuentran en el camino todavía
        if (find(trayectoria.begin(),trayectoria.end(),city) == trayectoria.end()) {
            unsigned pos = 1;
            Distancia dist_min = agregarCiudad(trayectoria, city, pos, distancias);
            // Comprobamos que ocurriría si la metiésemos entre cada una de las aristas válidas
            for (unsigned j = 2; j < trayectoria.size(); ++j) {
                Distancia dist = agregarCiudad(trayectoria, city, j, distancias);
                if (dist < dist_min) { // Cogemos la de menor distancia
                    dist_min = dist;
                    pos = j;
                }
            }
            trayectoria.insert(trayectoria.begin()+pos,city); // y la añadimos
        }
    }

    Distancia dist = 0;
    for (unsigned i = 1; i < trayectoria.size(); ++i)
        dist += distancias[trayectoria[i-1]][trayectoria[i]];
    return dist;
}

void mostrarRecorrido(const MapaCiudades& mapa,
                      const vector<Ciudad>& trayectoria, Distancia d) {
    for (auto ciudad : trayectoria)
        cout << ciudad + 1 << " " << mapa[ciudad].first
                           << " " << mapa[ciudad].second << endl;

    cout << "La distancia es de " << d << endl;
}


/** HASTA AQUÍ TODO ERA DE LA PRÁCTICA 3 **/

Distancia calcularDistancia(const Trayectoria& trayectoria,
                            const MatrizDistancias& distancias) {
    Distancia dist = 0;
    for (unsigned i = 1; i < trayectoria.size(); ++i)
        dist += distancias[trayectoria[i-1]][trayectoria[i]];

    if (trayectoria.size() == distancias.size())
        dist += distancias[trayectoria[0]][trayectoria[trayectoria.size()-1]];
    return dist;
}

map<Ciudad, multimap<Distancia, Ciudad>> calcularArcos(const MatrizDistancias& distancias) {
    map<Ciudad, multimap<Distancia, Ciudad>> salida;
    for (size_t origen = 0; origen < distancias.size(); ++origen)
        for (size_t destino = 0; destino < distancias.size(); ++destino)
            if (origen != destino)
                salida[origen].insert( { distancias[origen][destino], destino});

    return salida;
}

class Solucion {
    vector<Ciudad> caminoRecorrido {0}; // Iniciamos el recorrido con la ciudad 0
    Distancia cotaInferior = 0; // Distancia óptima estimada
    Distancia distancia = 0;

public:

    /** Métodos consultores **/

    Distancia getCotaInferior() const {
        return cotaInferior;
    }

    bool esSolucion(size_t tam) const {
        return caminoRecorrido.size() == tam;
    }

    vector<int> getCaminoRecorrido() const {
        return caminoRecorrido;
    }

    vector<int> generarCiudadesRestantes(int n) const {
        vector<int> salida;
        for (int i{0}; i < n; ++i)
            if (find(caminoRecorrido.begin(), caminoRecorrido.end(), i) == caminoRecorrido.end())
                salida.push_back(i);
        return salida;
    }

    bool operator< (const Solucion& s) const {
        // Necesario para indicar quién es más importante en la priority queue.
        // Por tanto es menos importante el que más CI tenga porque es menos
        // probable que sea el óptimo.
        return cotaInferior > s.cotaInferior;
    }

    void mostrar(const MapaCiudades& mapa, ostream& os = cout) const {
        for (auto ciudad : caminoRecorrido)
            os << ciudad + 1          << " "
               << mapa[ciudad].first  << " "
               << mapa[ciudad].second << endl;

    }

    void mostrarPantalla(const MapaCiudades& mapa) const {
        mostrar(mapa);
        cout << "La distancia es de " << distancia << endl;
    }
    /** Métodos modificadores **/

    Distancia buscarAristaMenor(Ciudad ciudad, const map<Ciudad, multimap<Distancia, Ciudad>>& arcos) {
        auto it = arcos.find(ciudad)->second.begin();
        while (it != arcos.find(ciudad)->second.end() &&
           find(caminoRecorrido.begin(), caminoRecorrido.end() - 1, it->second)
                                      != caminoRecorrido.end() - 1)
           ++it;

        return it->first;
    }

    Distancia calcularCotaInferior(const map<Ciudad, multimap<Distancia, Ciudad>>& arcos) {
       // La cota inferior será la distancia
       cotaInferior = distancia;
       // más [para todo vértice no presente en el recorrido] su arista menor
       for (auto ciudad : generarCiudadesRestantes(arcos.size()))
           cotaInferior += buscarAristaMenor(ciudad, arcos);
       return cotaInferior += buscarAristaMenor(0, arcos);
    }

    void nuevaCiudad() {
        caminoRecorrido.push_back(-1);
    }

    void cambiarUltimaCiudad(Ciudad ciudad, const MatrizDistancias& distancias) {
        if (caminoRecorrido.back() != -1 && caminoRecorrido.size() > 1) {
            distancia -= distancias[caminoRecorrido.back()]
                         [caminoRecorrido [caminoRecorrido.size() - 2]];


            if (caminoRecorrido.size() == distancias.size())
                distancia -= distancias[caminoRecorrido.back()][0];
        }
        caminoRecorrido.back() = ciudad;
        if (caminoRecorrido.size() > 1)
        distancia += distancias[caminoRecorrido.back()]
                     [caminoRecorrido [caminoRecorrido.size() - 2]];
    }

    /** Métodos consultores / modificadores **/

    Distancia getDistanciaRecorridoCompleto(const MatrizDistancias& distancias) {
        // Añadimos el coste de volver a la ciudad inicial y lo devolvemos
        return distancia += distancias[caminoRecorrido.back()][0];

    }

};

void branchAndBound(const map<Ciudad, multimap<Distancia, Ciudad>>& arcos, const MatrizDistancias& distancias,
                          Trayectoria& mejorCamino, Distancia& mejorDistancia) {
    priority_queue<Solucion, vector<Solucion>> cola;
    size_t n = arcos.size();
    Solucion enodo;
    Distancia distanciaActual;
    vector<int> ciudadesRestantes;
    cola.push(enodo);
    // mejorDistancia actúa como cota superior
    while (!cola.empty() && (cola.top().getCotaInferior() < mejorDistancia)) {
        enodo = cola.top();
        cola.pop();
        ciudadesRestantes = enodo.generarCiudadesRestantes(n);
        enodo.nuevaCiudad();
        for (size_t i = 0; i < ciudadesRestantes.size(); ++i) {
            enodo.cambiarUltimaCiudad(ciudadesRestantes[i], distancias);
            if (enodo.esSolucion(n)) {
                distanciaActual = enodo.getDistanciaRecorridoCompleto(distancias);
                if (distanciaActual < mejorDistancia) { // Comprobamos si es la mejor solución
                    mejorDistancia = distanciaActual;
                    mejorCamino = enodo.getCaminoRecorrido();
                }
            }
            else if (enodo.calcularCotaInferior(arcos)< mejorDistancia)
                cola.push(enodo);
         }
    }


    mejorCamino.push_back(mejorCamino.front());
}


int main(int argc, char* argv[]) {
    // Leemos del archivo
    if (argc != 2) {
        cerr << "Debe indicar como único argumento el archivo" << endl;
        return -1;
    }

    MapaCiudades mapa = leerArchivo(argv[1]);
    auto distancias = calcularMatrizDistancias(mapa);
    vector<Ciudad> trayectoria;
    // Calculamos la cota superior inicial
    Distancia distancia = heuristicaInsercion(mapa, distancias, trayectoria);


    mostrarRecorrido(mapa, trayectoria, distancia);
    auto arcos = calcularArcos(distancias);

    auto tAntes = high_resolution_clock::now();
    branchAndBound(arcos, distancias, trayectoria, distancia);
    auto tDespues = high_resolution_clock::now();
    mostrarRecorrido(mapa, trayectoria, distancia);
    duration<double> tiempo = duration_cast<duration<double>>(tDespues - tAntes);
    cout << "El tiempo de ejecucion es de " << tiempo.count() << endl;

}

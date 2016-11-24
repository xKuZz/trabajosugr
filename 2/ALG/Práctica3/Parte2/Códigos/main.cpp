#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <utility>
#include <list>
#include <map>
#include <vector>

using namespace std;

using ciudad = int;
using distancia = unsigned;
using coordenadas = pair<int, int>;
#define X 0
#define Y 1

#define MOSTRARDISTANCIAS 0
#define HEURISTICA
#define SHOWLONGITUD 0
#define SHOWRECORRIDO 1



vector<coordenadas> leerArchivo(char* nombre) {
    // Esta función sólo lee los datos del archivo de entrada.
    ifstream archivo(nombre);
    archivo.ignore(10);

    int N = 0;
    archivo >> N;


    if (!archivo.is_open() || N == 0){
        cerr << "Error de lectura de archivo";
        exit (-1);
    }

    vector<coordenadas> salida;
    salida.reserve(N);
    double x, y;
    for (int i = 0; i < N; ++i) {
        archivo >> x;
        archivo >> x;
        archivo >> y;
        salida.emplace_back((int)x,(int)y);
    }

    return salida;
}

int distanciaCiudad(ciudad c1, ciudad c2, const vector<coordenadas>& v) { // Distancia Euclídea
    return round(sqrt(pow(get<X>(v[c1])-get<X>(v[c2]),2) +
                      pow(get<Y>(v[c1])-get<Y>(v[c2]),2)));
}

#if HEURISTICA == 1
map<ciudad, multimap<distancia, ciudad>> calcularDistancias(const vector<coordenadas>& v) {
    // La descripción del map es un multimap con clave distancia ya que así siempre tendremos en
    // el begin del multimap la distancia mas corta
    map<ciudad, multimap<distancia, ciudad>> salida;
    multimap<distancia, ciudad> aux;

    for (unsigned i = 0; i < v.size(); ++i) {
        aux.clear();
        for (unsigned j = 0; j < v.size(); ++j) {
            int dist = distanciaCiudad(i,j,v);
            aux.insert({dist, j});
        }
        salida[i] = aux;
    }

#if MOSTRARDISTANCIAS
    for (auto p : salida) {
        for (auto c : p.second)
            cout << p.first << '\t' << c.second  << '\t' << c.first << endl;
    }

#endif
    return salida;
}

#elif HEURISTICA == 2
vector<vector<distancia>> calcularDistancias(const vector<coordenadas> &v) {
    // Matriz con todas las distancias, distancias[i][j] == distancias[j][i]
    vector<vector<distancia>> salida;
    vector<distancia> fila;
    for (unsigned i = 0; i < v.size(); ++i) {
        fila.clear();
        for (unsigned j = 0; j < v.size(); ++j)
            fila.push_back(distanciaCiudad(i,j,v));
        salida.push_back(fila);
    }
    return salida;
}
#endif

// Heurística Propuesta 1
distancia seleccionarMasCercanas (unsigned N, vector<ciudad>& trayectoria,
                             map<ciudad, multimap<distancia, ciudad>>& distancias) {
    // Para trabajar trabajamos de 0 a N-1, los resultados se sacan de 1 a N con
    // las funciones creadas para ello
    unsigned long longitud = 0;

    // Empezamos en la ciudad 0
    int ciudad_actual = 0;
    trayectoria.reserve(N+1);
    trayectoria.push_back(ciudad_actual);

    while (trayectoria.size() < N) {
        // Miramos por orden creciente de distancia desde la ciudad actual
        auto it = distancias[ciudad_actual].begin();

        // Avanzamos en el caso de que ya hubiese sido introducida en trayectoria
        while (it != distancias[ciudad_actual].end() &&
               find(trayectoria.begin(), trayectoria.end(),
                    it->second) != trayectoria.end()
               ) ++it;
        // Introducimos la ciudad y añadimos la longitud del trayecto
        trayectoria.push_back(it->second);
        longitud += it->first;
        ciudad_actual = it->second;
    }

    // Añadimos la ciudad inicial para completar el ciclo
    trayectoria.push_back(0);
    return longitud;
}

// Heurística Propuesta 2
vector<ciudad> seleccionarTriangulo(const vector<coordenadas>& loc) {
    // Buscamos la más al norte, la más al este y la mas al oste y devuelve un vector con las mismas;
    coordenadas norte, este, oeste;
    ciudad cnorte, ceste, coeste;
    norte = este = oeste = loc.front();
    for (unsigned city = 0; city < loc.size(); ++city) {
        if (get<Y>(loc[city]) > get<Y>(norte)) { norte = loc[city]; cnorte = city ;}
        if (get<X>(loc[city]) > get<X>( este)) {  este = loc[city]; ceste  = city ;}
        if (get<X>(loc[city]) < get<Y>(oeste)) { oeste = loc[city]; coeste = city ;}
    }
    vector<ciudad> salida;
    salida.push_back(cnorte);
    salida.push_back(ceste);
    salida.push_back(coeste);
    salida.push_back(cnorte);
    return salida;
}

distancia agregarCiudad(vector<ciudad> trayectoria, ciudad city, unsigned posicion,
                        const vector<vector<distancia>>& distancias) {
    // Trayectoria se pasa por copia puesto que no se quiere modificar la trayectoria inicial,
    // sólo calcular la supuesta distancia del camino.
    distancia dist = 0;
    trayectoria.insert(trayectoria.begin()+posicion,city);
    for (unsigned i = 1; i < trayectoria.size(); ++i)
        dist += distancias[trayectoria[i-1]][trayectoria[i]];
    return dist;
}

distancia heuristicaInsercion(const vector<coordenadas>& ciudades,
                              const vector<vector<distancia>>& distancias,
                              vector<ciudad>& trayectoria) {
    // Primero seleccionamos las ciudades más al norte, este y oeste
    trayectoria = seleccionarTriangulo(ciudades);

    // Recorremos las ciudades en orden numérico
    for (unsigned city = 0; city < ciudades.size(); ++city) {
        // Si no se encuentran en el camino todavía
        if (find(trayectoria.begin(),trayectoria.end(),city) == trayectoria.end()) {
            unsigned pos = 1;
            distancia dist_min = agregarCiudad(trayectoria, city, pos, distancias);
            // Comprobamos que ocurriría si la metiésemos entre cada una de las aristas válidas
            for (unsigned j = 2; j < trayectoria.size(); ++j) {
                distancia dist = agregarCiudad(trayectoria, city, j, distancias);
                if (dist < dist_min) { // Cogemos la de menor distancia
                    dist_min = dist;
                    pos = j;
                }
            }
            trayectoria.insert(trayectoria.begin()+pos,city); // y la añadimos
        }
    }

    distancia dist = 0;
    for (unsigned i = 1; i < trayectoria.size(); ++i)
        dist += distancias[trayectoria[i-1]][trayectoria[i]];
    return dist;
}

// Heurística 3
multimap<distancia, pair<ciudad, ciudad>> crearAristas(const vector<coordenadas>& ciudades) {
    // Crea un multimap con clave la longitud de cada una de las posibles aristas
    multimap<distancia, pair<ciudad, ciudad>> salida;
    for (unsigned i = 0; i < ciudades.size(); ++i)
        for (unsigned j = 0; j < ciudades.size(); ++j)
        {
            if (j > i)
                salida.insert({distanciaCiudad(i,j,ciudades), {i,j}});
        }

//    for (auto c: salida) {
//        cout << c.first << '\t' << c.second.first+1 << '\t' << c.second.second+1 << endl;
//    }
    return salida;
}

bool esFactible(const list<pair<ciudad, ciudad>>& aristas,
             const pair<ciudad,ciudad>& arista) {
    // Devuelve que es factible si no hay dos aristas que llegan a involucran a un vértice
    int contador1 = 0, contador2 = 0;
    for (auto a : aristas) {
        if (a.first == arista.first || a.second == arista.first)
            ++contador1;
        if (a.first == arista.second || a.second == arista.second)
            ++contador2;
    }
    return contador1 <= 1 && contador2 <= 1;
}

// Devuelve iterador a un par del vector de aristas que contega como primero o segundo el dato d
// Colocando como de el dato de la otra punta de la arista neuva
list<pair<ciudad,ciudad>>::const_iterator buscar_par(const list<pair<ciudad, ciudad>>& a, ciudad& d) {

    return find_if(a.begin(),a.end(),[&](const pair<ciudad, ciudad>& p) {
        if (p.first == d) {
            d = p.second;
            return true;
        }
        else if (p.second == d){
            d = p.first;
            return true;
        }
        else
            return false;
    });

}
bool hayCiclos(list<pair<ciudad, ciudad>> aristas,
               const pair<ciudad,ciudad>& arista) {
    // Devuelve si se produciría algún ciclo al añadir la arista arista
    auto buscar = [&] (const ciudad& c) {
        return find_if(aristas.begin(),aristas.end(),[&](const pair<ciudad, ciudad>& p) {
            return p.first == c || p.second == c;
        });
    };

    ciudad res=arista.second;
    ciudad pos=arista.first;
    for (auto it=buscar(pos); it !=aristas.end(); it=buscar(pos)) {
        pos = (pos == it->first) ? it->second : it->first;
        aristas.erase(it);
    }
    return pos==res;

}

vector<ciudad> aristasATrayectoria(list<pair<ciudad, ciudad>>& aristas) {
    // Aunque aristas se borre se pasa por referencia por que no se va a usar más
    vector<ciudad> salida;

    auto c_it = aristas.cbegin();
    salida.push_back(aristas.begin()->first); // Introducimos la primera ciudad
    ciudad city = c_it->second; // Recordamos la segunda
    aristas.erase(c_it); // Eliminamos
    // Vaciamos el contenido de aristas repitiendo el proceso anterior
    while (!aristas.empty()) {
        salida.push_back(city);
        c_it = buscar_par(aristas, city);
        aristas.erase(c_it);
    }

    // Añadimos el ciudad inicial para cerrar el camino
    salida.push_back(salida.front());
    return salida;
}

void cerrarCiclo(list<pair<ciudad, ciudad>>& aristas,
                 const multimap<distancia, pair<ciudad, ciudad>>& dist_aristas,
                  distancia& longitud) {
    int queda_cerrar1 = 0, queda_cerrar2 = 0;
    // Buscamos aquellos vértices que tengan grado menor que 2
    for (auto p : aristas) {
        int contador1 = count_if(aristas.begin(), aristas.end(),
                                 [&](const pair<ciudad, ciudad>&c) {
            return p.first == c.first || p.first == c.second;
        });
        int contador2 = count_if(aristas.begin(), aristas.end(),
                                 [&](const pair<ciudad, ciudad>&c) {
            return p.second == c.first || p.second == c.second;
        });

        // Determinamos las puntas de arista sin cerrar
        if (contador1 < 2 && queda_cerrar1 == 0) queda_cerrar1 = p.first;
        else if (contador1 < 2 && queda_cerrar2 == 0) queda_cerrar2 = p.first;
        if (contador2 < 2 && queda_cerrar1 == 0) queda_cerrar1 = p.second;
        else if (contador2 < 2 && queda_cerrar2 == 0) queda_cerrar2 = p.second;
    }

    // Añadimos la nueva arista y la distancia correspondiente
    for (auto p: dist_aristas) {
        auto f = p.second.first;
        auto s = p.second.second;
        if ((queda_cerrar1 == f && queda_cerrar2 ==s) || (queda_cerrar1 == s && queda_cerrar2 == f)) {
            aristas.push_back(p.second);
            longitud += p.first;
            break;
        }
    }
}

distancia heuristica3(const multimap<distancia, pair<ciudad, ciudad>>& dist_aristas, vector<int>& trayectoria) {
    list<pair<ciudad, ciudad>> aristas;
    distancia longitud = 0;
    auto it = dist_aristas.begin();
    // Metemos la arista más corta
    aristas.push_back(it->second);
    longitud += it->first;
    it++;
    while (it!=dist_aristas.end()) { // Llendo de más corta a más larga comprobamos si podemos introducirla
        if (esFactible(aristas, it->second) && !hayCiclos(aristas, it->second)) {
            aristas.push_back(it->second);
            longitud += it->first;
        }
        it++;
    }
    cerrarCiclo(aristas,dist_aristas, longitud); // Cerramos el ciclo
    trayectoria = aristasATrayectoria(aristas); // Pasamos las aristas a un camino
    return longitud;
}

void mostrarRecorrido(const vector<ciudad>& trayectoria, const vector<coordenadas>& ciudades,
                      unsigned long longitud) {
#if SHOWRECORRIDO
    for (auto c : trayectoria)
        cout << c+1 << " " << get<X>(ciudades[c]) << " " << get<Y>(ciudades[c]) << endl;
#endif
#if SHOWLONGITUD
    cout << "Longitud del recorrido: " << longitud << endl;
#endif
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        cerr << "Poner como argumento nombre archivo";
        return -1;
    }
    auto   ciudades = leerArchivo(argv[1]);

    vector<ciudad> trayectoria;
#if HEURISTICA == 1
    auto distancias = calcularDistancias(ciudades);
    auto longitud = seleccionarMasCercanas(ciudades.size(), trayectoria,
                                           distancias);
#elif HEURISTICA == 2
    auto longitud = heuristicaInsercion(ciudades,calcularDistancias(ciudades),trayectoria);
#elif HEURISTICA == 3
    auto longitud = heuristica3(crearAristas(ciudades),trayectoria);
#endif

    mostrarRecorrido(trayectoria, ciudades, longitud);

}

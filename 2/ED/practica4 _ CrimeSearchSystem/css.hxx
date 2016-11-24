#include "css.h"
void CSS::load(const string &nombreDB) {
  ifstream archivo(nombreDB);

  if (archivo.is_open()) {
    auto linea   = string();
    auto entrada = crimen();

    getline(archivo, linea); // Ignoro primera línea (cabeceras)
    while (getline(archivo, linea))
           insert(entrada = linea);
  }
  else cout << "Error al abrir el fichero\n";
}

void CSS::insert(const crimen &x) {
  istringstream split(x.getDESCR());

  auto id   = x.getID();
  auto fec  = x.getDate();
  auto iucr = x.getIUCR();
  auto lat  = x.getLatitude();
  auto lon  = x.getLongitude();

  auto word = string();
  auto it   = map<ID, crimen>::iterator();

  tie(it, ignore) = baseDatos.insert({ id, x});
                   DateAccess.insert({fec, it});
             posicionGeo[lon].insert({lat, id});
             IUCRAccess[iucr].insert(id);

  while (split >> word)
                  index[word].insert(id);
}

template<class Map, class Key, class Remove>
void CSS::erase_empty_descr(Map &mapContainer, Key &key, Remove &toErase){
    mapContainer[key].erase(toErase);
    if (mapContainer[key].empty())
        mapContainer.erase(key);
}

bool CSS::erase(ID id) {
  auto it  = baseDatos.find(id);

  if  (it == baseDatos.end()) return false;
  else {
    auto lon      = it->second.getLongitude();
    auto lat      = it->second.getLatitude();
    auto fec      = it->second.getDate();
    auto iucr     = it->second.getIUCR();
    auto descr    = it->second.getDESCR();
    auto word     = string();

    auto latitud  = posicionGeo[lon].equal_range(lat);
    auto fecha    =       DateAccess.equal_range(fec);
    istringstream split(descr);

    for (auto it_lat = latitud.first; it_lat != latitud.second; ++it_lat)
      if (it_lat->second == id) {
        erase_empty_descr(posicionGeo,lon,it_lat);
        break;
      }

    erase_empty_descr(IUCRAccess,iucr,id);

    for (auto it_f = fecha.first; it_f != fecha.second; ++it_f)
      if (it_f->second->first == id) {
        DateAccess.erase(it_f);
        break;
      }

    while (split >> word)
      erase_empty_descr(index,word,id);
    baseDatos.erase(it);
    return true;
  }

}

CSS::iterator CSS::find_ID(unsigned int ID) {
  CSS::iterator it;
  it.it = baseDatos.find(ID);
  return it;
}

void CSS::setArrest(unsigned int ID, bool value) {
  auto it  = baseDatos.find(ID);
  if  (it != baseDatos.end())
       it->second.setArrest(value);
}

void CSS::unionPeso(map<ID, float> &t1, const set<ID> &t2) {
  for (auto id : t2)
       ++t1[id];
}

template <class Queue>
vector<pair<ID,float>> CSS::pop_to_vector(Queue &q){
vector<pair<ID,float>> output(q.size());

  while ( !q.empty() ) {
    output[q.size()-1]= q.top();
                        q.pop();
  }
  return output;
}

vector<pair<ID, float>> CSS::Query(list<string> &q, const unsigned int &k) {
  using par = pair<ID,float>;
  auto salida = vector<par>();
  salida.reserve(k);

  if (q.size() == 1){ // Si hay 1
    auto tam = min(k, (unsigned) index[q.front()].size());
    auto salida = vector<par>();
         salida.reserve(tam);

    for (auto &i : index[q.front()]) {
      salida.push_back({i, 1});
      if (salida.size() == tam)
          break;
    }

    return salida;
  }
  else {
    auto safe_find = [this] (const string &pal) {
                         auto it  = index.find(pal);
                         if  (it == index.end())
                             return set<ID>();
                         else
                             return it->second;
                   };
    auto prioridad = [](const par &a, const par &b) { // Functor
                        return a.second > b.second;
                   };
    auto cola  = priority_queue<par, vector<par>, decltype(prioridad)> (prioridad);
    auto pesos = map<ID,float>();

    for (auto &pal: q)      // Si hay 2 o mas
       unionPeso(pesos, safe_find(pal));

    for (auto &p : pesos)   // Seleccion de los k mejores
      if (cola.size() < k)
        cola.push(p);
      else {
        if (prioridad(p,cola.top())) {
          cola.pop();
          cola.push(p);
        }
      }

    return pop_to_vector(cola);
    }
}

list<ID> CSS::inArea(const Longitud &x1, const Latitud &y1, const Longitud &x2,
                     const Latitud &y2) {
  list<ID> salida;

  for (auto p = posicionGeo.lower_bound(x1); p!=posicionGeo.upper_bound(x2); ++p)
    for (auto pp = p->second.lower_bound(y2); pp!=p->second.upper_bound(y1); ++pp)
         salida.push_back(pp->second);

  return salida;
}

CSS::iterator CSS::begin() {
  CSS::iterator it;
  it.it = baseDatos.begin();
  return it;
}

CSS::Date_iterator CSS::dbegin() {
  CSS::Date_iterator it;
  it.it = DateAccess.begin();
  return it;
}

CSS::IUCR_iterator CSS::ibegin() {
  CSS::IUCR_iterator it;
  it.css = this;
  it.it_m = IUCRAccess.begin();
  if (!it.css->IUCRAccess.empty())
    it.it_s = it.it_m->second.begin();
  return it;
}

CSS::iterator CSS::end() {
  CSS::iterator it;
  it.it = baseDatos.end();
  return it;
}

CSS::Date_iterator CSS::dend() {
  CSS::Date_iterator it;
  it.it = DateAccess.end();
  return it;
}

CSS::IUCR_iterator CSS::iend() {
  CSS::IUCR_iterator it;
  it.css = this;
  it.it_m = IUCRAccess.end();
  if (!it.css->IUCRAccess.empty()){
    it.it_m--;
    it.it_s = it.it_m->second.end();
    it.it_s--;
  }
  return it;
}

CSS::iterator CSS::lower_bound(const ID &id) {
  CSS::iterator it;
  it.it = baseDatos.lower_bound(id);
  return it;
}

CSS::IUCR_iterator CSS::lower_bound(const IUCR &iucr) {
  CSS::IUCR_iterator it;
  it.css = this;
  it.it_m = IUCRAccess.lower_bound(iucr);
  it.it_s = it.it_m->second.begin();
  return it;
}

CSS::Date_iterator CSS::lower_bound(const fecha &f) {
  CSS::Date_iterator it;
  it.it = DateAccess.lower_bound(f);
  return it;
}

CSS::iterator CSS::upper_bound(const ID &id) {
  CSS::iterator it;
  it.it = baseDatos.upper_bound(id);
  return it;
}

CSS::IUCR_iterator CSS::upper_bound(const IUCR &iucr) {
  CSS::IUCR_iterator it;
  it.css  = this;
  it.it_m = IUCRAccess.upper_bound(iucr);
  it.it_s = it.it_m->second.begin();
  return it;
}

CSS::Date_iterator CSS::upper_bound(const fecha &f) {
  CSS::Date_iterator it;
  it.it = DateAccess.upper_bound(f);
  return it;
}

CSS::iterator::iterator() {}
CSS::iterator::iterator(const CSS::iterator &) = default;
CSS::iterator CSS::iterator::operator++(int) {
  auto copy(*this);
  ++it;
  return copy;
}

CSS::iterator CSS::iterator::operator--(int) {
  auto copy(*this);
  --it;
  return copy;
}
CSS::iterator& CSS::iterator::operator++() {
  ++it;
  return *this;
}

CSS::iterator& CSS::iterator::operator--() {
  --it;
  return *this;
}

bool CSS::iterator::operator==(const CSS::iterator &it2) {
  return it == it2.it;
}

bool CSS::iterator::operator!=(const CSS::iterator &it2) {
  return it != it2.it;
}

CSS::iterator::reference CSS::iterator::operator*() {
  return *it;
}

CSS::iterator::pointer CSS::iterator::operator->() {
  return &(*it);
}

CSS::Date_iterator::Date_iterator() {}
CSS::Date_iterator::Date_iterator(const Date_iterator &) = default;
CSS::Date_iterator CSS::Date_iterator::operator++(int) {
  auto copy(*this);
  ++it;
  return copy;
}

CSS::Date_iterator& CSS::Date_iterator::operator++() {
  ++it;
  return *this;
}

CSS::Date_iterator CSS::Date_iterator::operator--(int) {
  auto copy(*this);
  --it;
  return copy;
}

CSS::Date_iterator& CSS::Date_iterator::operator--() {
  --it;
  return *this;
}

CSS::Date_iterator::reference CSS::Date_iterator::operator*() {
  return *it->second;
}

CSS::Date_iterator::pointer CSS::Date_iterator::operator->() {
  return &(*it->second);
}

bool CSS::Date_iterator::operator==(const CSS::Date_iterator &it2){
  return it == it2.it;
}

bool CSS::Date_iterator::operator!=(const CSS::Date_iterator &it2){
  return it != it2.it;
}

CSS::IUCR_iterator::IUCR_iterator() {}
CSS::IUCR_iterator::IUCR_iterator(const IUCR_iterator &) = default;
CSS::IUCR_iterator::reference CSS::IUCR_iterator::operator*() {
  return *css->baseDatos.find(*it_s);
}

CSS::IUCR_iterator::pointer CSS::IUCR_iterator::operator->() {
  return &(*css->baseDatos.find(*it_s));
}

CSS::IUCR_iterator CSS::IUCR_iterator::operator++(int) {
  auto r(*this);
  if (++it_s == it_m->second.end()) {
    ++it_m;
    it_s = it_m->second.begin();
  }
  return r;
}

CSS::IUCR_iterator CSS::IUCR_iterator::operator--(int) {
  auto r(*this);
  if (it_s == it_m->second.begin()) {
    --it_m;
    it_s = it_m->second.end();
    --it_s;
  } else
    --it_s;
  return r;
}

CSS::IUCR_iterator& CSS::IUCR_iterator::operator++() {
  if (++it_s == it_m->second.end()) {
    ++it_m;
    it_s = it_m->second.begin();
  }
  return *this;
}

CSS::IUCR_iterator& CSS::IUCR_iterator::operator--() {
  if (it_s == it_m->second.begin()) {
    --it_m;
    it_s = it_m->second.end();
    --it_s;
  } else
    --it_s;
  return *this;
}

bool CSS::IUCR_iterator::operator==(const CSS::IUCR_iterator &it2) {
  return it_m == it2.it_m && it_s == it2.it_s;
}

bool CSS::IUCR_iterator::operator!=(const CSS::IUCR_iterator &it2) {
  return it_m != it2.it_m || it_s != it2.it_s;
}

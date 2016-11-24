
#include "fecha.h"
#include "crimen.h"
#include "conjunto.h"
#include <functional>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

template<class CMP>
conjunto<CMP>::conjunto(){

}

template<class CMP>
void conjunto<CMP>::insert(const crimen &e){
        if (vc.empty())
            vc.push_back(e);

        else
            vc.insert(std::lower_bound(vc.begin(),vc.end(),e,comp), e);
}

template<class CMP>
conjunto<CMP>::conjunto(const conjunto<CMP> &d){
    vc=d.vc;
}

template<class CMP>
conjunto<CMP> conjunto<CMP>::findIUCR (const string &iucr) const{
    conjunto<CMP> salida;
    for (const auto &e: vc){
        if(e.getIUCR()==iucr)
            salida.insert(e);
    }
    return salida;

}

template<class CMP>
bool conjunto<CMP>::erase(const long int &id) {
   for (auto it=vc.begin(); it!=vc.end(); ++it)
       if (it->getID()==id){
           vc.erase(it);
           return true;
       }
   return false;
}

template<class CMP>
bool conjunto<CMP>::erase(const crimen &e){
    vector<crimen>::iterator it;
    for(it=std::lower_bound(vc.begin(),vc.end(),e,comp);
            it==vc.end() && !comp(e,*it) && !(*it==e); ++it);

    if (!(*it==e))
        return false;
    else {
        vc.erase(it);
        return true;
    }
}

template<class CMP>
bool conjunto<CMP>::empty() const{
    return vc.empty();
}

template<class CMP>
typename conjunto<CMP>::size_type conjunto<CMP>::size() const{
    return vc.size();
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::begin(){
    typename conjunto<CMP>::iterator sal;
    sal.itv = vc.begin();
    return sal;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::end(){
    typename conjunto<CMP>::iterator sal;
    sal.itv = vc.end();
    return sal;
}

template<class CMP>
conjunto<CMP>::iterator::iterator(){

}

template<class CMP>
conjunto<CMP>::iterator::iterator(const conjunto<CMP>::iterator &i){
    itv = i.itv;
}

template<class CMP>
const typename conjunto<CMP>::entrada&  conjunto<CMP>::iterator::operator*(){
    return *itv;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::iterator::operator++(int){
    typename conjunto::iterator antiguo(*this);
    ++itv;
    return antiguo;
}
template<class CMP>
typename conjunto<CMP>::iterator& conjunto<CMP>::iterator::operator++(){
    ++itv;
    return *this;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::iterator::operator--(int){
    typename conjunto<CMP>::iterator antiguo(*this);
    --itv;
    return antiguo;
}

template<class CMP>
typename conjunto<CMP>::iterator& conjunto<CMP>::iterator::operator--(){
    --itv;
    return *this;
}

template<class CMP>
bool conjunto<CMP>::iterator::operator==(const iterator &it){
    return itv==it.itv;
}

template<class CMP>
bool conjunto<CMP>::iterator::operator!=(const iterator &it){
    return itv!=it.itv;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::find(const crimen &c){
    typename conjunto<CMP>::iterator it;
    for(it.itv=std::lower_bound(vc.begin(),vc.end(),c,comp);
            it.itv==vc.end() && !comp(c,*it) && !(*it.itv==c); ++it.itv);

    if (!(*it==c))
        it.itv=vc.end();

    return it;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::lower_bound(const crimen &c){
    typename conjunto<CMP>::iterator it;
    it.itv=std::lower_bound(vc.begin(),vc.end(),c,comp);
    return it;
}
template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::upper_bound(const crimen &c){
    typename conjunto<CMP>::iterator it;
    it.itv=std::upper_bound(vc.begin(),vc.end(),c,comp);
    return it;
}


template<class CMP>
template<class InputIterator>
conjunto<CMP>::conjunto(const InputIterator &ini, const InputIterator &fin){
    for_each(ini,fin,[this](const crimen &e){ insert(e);});
}

template<class CMP>
conjunto<CMP> conjunto<CMP>::findDESCR(const string &descr) const{
    conjunto<CMP> salida;
    for (const auto &e: vc)
        if (e.getDESCR().rfind(descr)!=string::npos){
             salida.insert(e);
    }
    return salida;
}

template<class CMP>
conjunto<CMP> & conjunto<CMP>::operator=(const conjunto<CMP> &org){
    if (this!=&org){
            this->vc=org.vc;
        }
        return *this;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::find(const crimen &e) const {
    typename conjunto<CMP>::const_iterator c_it;
    c_it.c_itv=std::lower_bound(vc.cbegin(),vc.cend(),e,comp);

    while(c_it.c_itv!=vc.cend() && !comp(e,*c_it)){
        if (!(*c_it==e))
            c_it++;
        else
            return c_it;
    }
    c_it.c_itv=vc.cend();
    return c_it;

}

template<class CMP>
bool conjunto<CMP>::cheq_rep() const{
    for (size_type i=0; i<vc.size(); ++i)
            if (vc[i].getID()<=0)
                return false;
        for (size_type i=0; i<vc.size()-1; ++i)
            if(comp(vc[i+1],vc[i]))
                return false;
        return true;
}

template<class CMP>
conjunto<CMP>::const_iterator::const_iterator(){

}

template<class CMP>
conjunto<CMP>::const_iterator::const_iterator(const conjunto<CMP>::const_iterator &it){
    c_itv=it.c_itv;
}

template<class CMP>
conjunto<CMP>::const_iterator::const_iterator(const conjunto<CMP>::iterator &it){
    c_itv=it.itv;
}

template<class CMP>
const crimen& conjunto<CMP>::const_iterator::operator*() const{
    return *c_itv;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::const_iterator::operator++(int){
    conjunto<CMP>::const_iterator antiguo(*this);
    ++c_itv;
    return antiguo;
}

template<class CMP>
typename conjunto<CMP>::const_iterator& conjunto<CMP>::const_iterator::operator++(){
    ++c_itv;
    return *this;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::const_iterator::operator--(int){
    conjunto<CMP>::const_iterator antiguo(*this);
    --c_itv;
    return antiguo;
}

template<class CMP>
typename conjunto<CMP>::const_iterator& conjunto<CMP>::const_iterator::operator--(){
    --c_itv;
    return *this;
}

template<class CMP>
bool conjunto<CMP>::const_iterator::operator==(const const_iterator &it){
    return c_itv==it.c_itv;
}

template<class CMP>
bool conjunto<CMP>::const_iterator::operator!=(const const_iterator &it){
    return c_itv!=it.c_itv;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::cbegin() const{
    conjunto<CMP>::const_iterator sal;
    sal.c_itv = vc.cbegin();
    return sal;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::cend() const{
    conjunto<CMP>::const_iterator sal;
    sal.c_itv = vc.cend();
    return sal;
}


template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::find(const long int &id) const{
    conjunto<CMP>::const_iterator c_it;
    for(c_it=cbegin();c_it!=cend();c_it++){
        if(*c_it.getID()==id)
            return c_it;
    }
    return c_it;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::lower_bound(const crimen &e) const{
    typename conjunto<CMP>::const_iterator c_it;
    c_it.c_itv=std::lower_bound(vc.cbegin(),vc.cend(),e,comp);
    return c_it;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::upper_bound(const crimen &e) const{
    typename conjunto<CMP>::const_iterator c_it;
    c_it.c_itv=std::upper_bound(vc.cbegin(),vc.cend(),e,comp);
    return c_it;
}

template<class CMP>
ostream &  operator << ( ostream & sal, const conjunto<CMP> & D){
    for(typename conjunto<CMP>::size_type i=0; i<D.vc.size(); ++i)
            sal << D.vc[i] << endl;
        return sal;
}


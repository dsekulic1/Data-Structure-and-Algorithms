#include <iostream>
#include <utility>
#include <vector>
#include <functional>

template <typename TipKljuca, typename TipVrijednosti>
class Mapa{
    public:
    Mapa(){};
    virtual TipVrijednosti &operator[](const TipKljuca kljuc)=0;
    virtual TipVrijednosti operator[](const TipKljuca &kljuc)const=0;
    virtual int brojElemenata()const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const TipKljuca &kljuc)=0;
    virtual ~Mapa(){};
};

template<typename TipKljuca,typename TipVrijednosti>
class HashMapa:public Mapa<TipKljuca,TipVrijednosti>{
    std::pair<TipKljuca,TipVrijednosti> *nizparova;
    std::vector<bool> obrisan;
    int brel, kapacitet;
    unsigned int (*pnf)(TipKljuca,unsigned int);
    public:
    HashMapa(){
        brel=0;
        kapacitet=5;
        nizparova=new std::pair<TipKljuca,TipVrijednosti>[5];
        pnf=nullptr;
    }
    HashMapa(const HashMapa<TipKljuca,TipVrijednosti> &mapa){
        pnf=mapa.pnf;
        brel=mapa.brel;
        kapacitet=mapa.kapacitet;
        nizparova=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
        obrisan.resize(mapa.obrisan.size());
        obrisan=mapa.obrisan;
        for(int i=0;i<brel;i++){
            nizparova[i]=mapa.nizparova[i];
        }
    }
    ~HashMapa(){
        delete []nizparova;
    }
    HashMapa &operator=(const HashMapa<TipKljuca,TipVrijednosti>&mapa){
    if(this==&mapa)return *this;
    brel=mapa.brel;
    kapacitet=mapa.kapacitet;
    delete []nizparova;
    nizparova=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
    for(int i(0);i<brel;i++) nizparova[i]=mapa.nizparova[i];
    obrisan.resize(mapa.obrisan.size());
    obrisan=mapa.obrisan;
    return *this;
    }
    HashMapa &operator =(HashMapa && mapa){
        brel=mapa.brel;
        kapacitet=mapa.kapacitet;
        delete[]nizparova;
        obrisan.resize(mapa.size());
        obrisan=mapa.obrisan;
        nizparova=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
        for(int i(0);i<brel;i++) nizparova[i]=mapa.nizparova[i];
        return *this;
    }
    int brojElemenata()const override{
        return brel;
    }
    void obrisi()override{
        brel=0;
    }
    void obrisi(const TipKljuca &kljuc)override{
        bool postoji=false;
        for(int i=0;i<brel;i++){
            if(nizparova[i].first==kljuc){
                postoji=true;
                for(int j=i;j<brel-1;j++) nizparova[j]=nizparova[j+1];
                brel--;
                break;
            }
        }
        if(!postoji)throw "Nema para koji sadrzi dati kljuc";
    }
    TipVrijednosti &operator[](const TipKljuca kljuc)override{
        if(!pnf) throw "";
        for(int i=0;i<brel;i++){
            if(nizparova[i].first==kljuc) return nizparova[i].second;
        }
        if(kapacitet>brel){
            nizparova[brel].first=kljuc;
            nizparova[brel++].second=TipVrijednosti();
            return nizparova[brel-1].second;
        }
        else {
            kapacitet*=2;
            std::pair<TipKljuca,TipVrijednosti>*tnizparova=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
            for(int i=0;i<brel;i++) tnizparova[i]=nizparova[i];
            
            delete[]nizparova;
            nizparova=tnizparova;
            tnizparova=nullptr;
            nizparova[brel].first=kljuc;
            nizparova[brel++].second=TipVrijednosti();
            return nizparova[brel-1].second;
        }
    }
    TipVrijednosti operator[](const TipKljuca &kljuc)const override{
        if(!pnf) throw "";
        int hashvr=pnf(kljuc,kapacitet);
        if(nizparova[hashvr].first==kljuc) return nizparova[hashvr].second;
        else{
            for(int i=hashvr+1;i<kapacitet;i++){
                if(nizparova[i].first==kljuc) return nizparova[i].second;
            }
            for(int i=0;i<hashvr;i++){
                if(nizparova[i].first==kljuc)return nizparova[i].second;
            }
        }
        return TipVrijednosti();
    }
    
    void definisiHashFunkciju(unsigned int (*pnf2)(TipKljuca,unsigned int)){
        pnf=pnf2;
    }
};








int main() {
    std::cout << "Pripremna Zadaca Za Vjezbu 9, Zadatak 1";
    return 0;
}

#include <iostream>
#include <utility>
using namespace std;

template <typename TipKljuca,typename TipVrijednosti>
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
template <typename TipKljuca,typename TipVrijednosti>
class NizMapa:public Mapa<TipKljuca,TipVrijednosti>{
    std::pair<TipKljuca,TipVrijednosti>*nizparova;
    int brel,kapacitet;
    public:
    NizMapa(){
        brel=0;
        kapacitet=5;
        nizparova=new std::pair<TipKljuca,TipVrijednosti>[5];
    }
    NizMapa(const NizMapa<TipKljuca,TipVrijednosti> &mapa){
        brel=mapa.brel;
        kapacitet=mapa.kapacitet;
        nizparova=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
        for(int i=0;i<brel;i++) nizparova[i]=mapa.nizparova[i];
    }
    NizMapa&operator=(const NizMapa<TipKljuca,TipVrijednosti> &mapa){
        if(this==&mapa)return *this;
        brel=mapa.brel;
        kapacitet=mapa.kapacitet;
        delete[]nizparova;
        nizparova=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
        for(int i=0;i<brel;i++) nizparova[i]=mapa.nizparova[i];
        return *this;
    }
    NizMapa &operator=( NizMapa&& mapa){
        brel=mapa.brel;
        kapacitet=mapa.kapacitet;
        delete[]nizparova;
        nizparova=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
        for(int i=0;i<brel;i++) nizparova[i]=mapa.nizparova[i];
        return *this;
    }
    int brojElemenata()const override{return brel;}
    void obrisi()override{brel=0;}
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
        if(!postoji) throw("Nema para koji sadrzi dati kljuc");
    }
    TipVrijednosti &operator[](const TipKljuca kljuc)override{
        for(int i=0;i<brel;i++){
            if(nizparova[i].first==kljuc){
                return nizparova[i].second;
            }
        }
        if(kapacitet>brel){
            nizparova[brel].first=kljuc;
            nizparova[brel++].second=TipVrijednosti();
            return nizparova[brel-1].second;
        }
        else{
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
        for(int i=0;i<brel;i++){
            if(nizparova[i].first==kljuc) return nizparova[i].second;
        }
        return TipVrijednosti();
    }
    ~NizMapa(){
        delete[]nizparova;
    }
};
template<typename TipKljuca,typename TipVrijednosti>
void test1(NizMapa<TipKljuca,TipVrijednosti>&nm){
    nm["Jedinica"]=1;
    nm["Dvica"]=2;
    std::cout<<nm.brojElemenata()<<std::endl;
    std::cout<<nm["Jedinica"];
}
template<typename TipKljuca,typename TipVrijednosti>
void test2(NizMapa<TipKljuca,TipVrijednosti>&nm){
    std::cout<<nm.brojElemenata()<<std::endl;
     nm[10]="Test2";
    std::cout<<nm.brojElemenata()<<" "<<nm[10];
}
template<typename TipKljuca,typename TipVrijednosti>
void test3(NizMapa<TipKljuca,TipVrijednosti>&nm){
    nm["a"]=1;
    nm["b"]=2;
    NizMapa<std::string,int>nm2(nm);
    std::cout<<nm2.brojElemenata()<<" "<<nm2["b"] <<std::endl;
}
template<typename TipKljuca,typename TipVrijednosti>
void test4(NizMapa<TipKljuca,TipVrijednosti>&nm){
    nm["a"]="j";
    nm["b"]="b";
    nm["c"]="c";
    NizMapa<std::string,std::string>nm2;
    std::cout<<"Broj elemenata: "<<(nm2=nm).brojElemenata()<<std::endl;
}
template<typename TipKljuca,typename TipVrijednosti>
void test5(NizMapa<TipKljuca,TipVrijednosti>&nm){
   for(int i=0;i<10;i++) nm[i]=i+10;
    std::cout<<nm.brojElemenata()<<" "<<nm[9]<<std::endl;
}
int main() {
   NizMapa<int,int>nm;
   test5(nm);
    return 0;
}

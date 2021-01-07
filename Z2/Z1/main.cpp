#include <iostream>
#include <utility>

template <typename tip>
struct cvor{
  tip vrijednost;
  cvor<tip> *sljedeci=nullptr,*prethodni=nullptr;
};
template <typename tip>
class DvostraniRed{
    cvor<tip>*tekuci=nullptr,*pocetak=nullptr,*kraj=nullptr;
    int duzina;
    
public:
    DvostraniRed(){
        pocetak=new cvor<tip>;
        kraj=new cvor<tip>;
        pocetak->sljedeci=kraj;
        kraj->prethodni=pocetak;
        kraj->sljedeci=nullptr;
        tekuci=nullptr;
        duzina=0;
    }
    DvostraniRed(const DvostraniRed &r){
        pocetak=new cvor<tip>;
        kraj=new cvor<tip>;
        
        kraj->prethodni=pocetak;
        pocetak->sljedeci=kraj;
        duzina=0;
        
        cvor<tip>*tmp;
        tmp=r.pocetak->sljedeci;
        int i=0;
        while(i<r.duzina){
            staviNaVrh(tmp->vrijednost);
            tmp=tmp->sljedeci;
            i++;
        }
    }
    DvostraniRed(DvostraniRed &&r){
        std::swap(pocetak,r.pocetak);
        std::swap(kraj,r.kraj);
        std::swap(duzina,r.duzina);
    }
    int brojElemenata(){return duzina;}
    void brisi(){
        while(pocetak->sljedeci!=kraj){
            cvor<tip>*tmp=pocetak->sljedeci;
            pocetak->sljedeci=tmp->sljedeci;
            delete tmp;
        }
        kraj->prethodni=pocetak;
        duzina=0;
    }
    ~DvostraniRed(){
        while(pocetak->sljedeci!=nullptr){
            cvor<tip>*tmp=pocetak->sljedeci;
            pocetak->sljedeci=tmp->sljedeci;
            delete tmp;
        }
        delete pocetak;
    }
    DvostraniRed &operator=(const DvostraniRed &r){
        if(this==&r) return *this;
        brisi();
        duzina=0;
        cvor<tip> *tmp;
        tmp=r.pocetak->sljedeci;
        int i=0;
        while(i<r.duzina){
            staviNaVrh(tmp->vrijednost);
            tmp=tmp->sljedeci;
            i++;
        }
        return *this;
    }
    DvostraniRed &operator=(DvostraniRed &&r){
        std::swap(pocetak,r.pocetak);
        std::swap(kraj,r.kraj);
        std::swap(duzina,r.duzina);
        return *this;
    }
    void staviNaVrh(const tip &el){
        cvor <tip> *tmp=new cvor<tip>;
        tmp->vrijednost=el;
        tmp->sljedeci=kraj;
        tmp->prethodni=kraj->prethodni;
        kraj->prethodni->sljedeci=tmp;
        kraj->prethodni=tmp;
        duzina++;
    }
    tip skiniSaVrha(){
        if(duzina==0) throw ("ERROR");
        cvor<tip>*tmp=kraj->prethodni;
        tmp->prethodni->sljedeci=kraj;
        kraj->prethodni=tmp->prethodni;
        duzina--;
        tip el=tmp->vrijednost;
        delete tmp;
        return el;
    }
    tip &vrh(){
        if(duzina==0) throw ("ERROR");
        return kraj->prethodni->vrijednost;
    }
    tip &celo(){
        if(duzina==0)throw ("ERROR");
        return pocetak->sljedeci->vrijednost;
    }
    void staviNaCelo(const tip &el){
        cvor<tip> *tmp=new cvor<tip>;
        tmp->vrijednost=el;
        tmp->prethodni=pocetak;
        tmp->sljedeci=pocetak->sljedeci;
        pocetak->sljedeci->prethodni=tmp;
        pocetak->sljedeci=tmp;
        duzina++;
    }
    tip skiniSaCela(){
        if(duzina==0) throw ("ERROR");
        cvor<tip> *tmp=pocetak->sljedeci;
        pocetak->sljedeci=tmp->sljedeci;
        tmp->sljedeci->prethodni=pocetak;
        duzina--;
        tip el=tmp->vrijednost;
        delete tmp;
        return el;
    }
    void ispisi(){
        cvor<tip>*tmp=pocetak->sljedeci;
        while (tmp!=kraj) {
            std::cout<<tmp->vrijednost<< " ";
            tmp=tmp->sljedeci;
            
        }
    }
 
};
int main() {
   
    return 0;
}

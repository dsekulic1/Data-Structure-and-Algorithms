#include <iostream>
template <typename tip>
struct cvor{
    tip vrijednost;
    cvor <tip>*sljedeci=nullptr;
};
template <typename tip>
class Stek{
    cvor<tip>*prepoc;
    int duzina;
    public:
    Stek(){
        prepoc=new cvor<tip>;
        duzina=0;
    }
    Stek(const Stek &s){
        prepoc=new cvor<tip>;
        prepoc->sljedeci=nullptr;
        duzina=s.duzina;
        cvor<tip>*tmp,*trenutni=prepoc;
        tmp=s.prepoc->sljedeci;
        while(tmp){
            cvor<tip>*novi=new cvor<tip>;
            novi->vrijednost=tmp->vrijednost;
            novi->sljedeci=nullptr;
            trenutni->sljedeci=novi;
            trenutni=trenutni->sljedeci;
            tmp=tmp->sljedeci;
        }
    }
    Stek(Stek &&s){
        std::swap(prepoc,s.prepoc);
        std::swap(duzina,s.duzina);
    }
    void brisi(){
        while(prepoc->sljedeci!=nullptr){
            cvor<tip>*tmp=prepoc->sljedeci;
            prepoc->sljedeci=tmp->sljedeci;
            delete tmp;
        }
        duzina=0;
    }
    void stavi(const tip &el){
        cvor<tip>*novi=new cvor<tip>;
        novi->vrijednost=el;
        novi->sljedeci=prepoc->sljedeci;
        prepoc->sljedeci=novi;
        duzina++;
    }
    tip skini(){
        if(duzina==0) throw "Erorcic!";
        cvor<tip>*tmp=prepoc->sljedeci;
        prepoc->sljedeci=tmp->sljedeci;
        auto a=tmp->vrijednost;
        delete tmp;
        duzina--;
        return a;
    }
    tip &vrh(){
        if(duzina==0) throw "Erorcic!";
        cvor<tip>*tmp=prepoc->sljedeci;
        return tmp->vrijednost;
    }
    int brojElemenata(){
        return duzina;
    }
    Stek &operator=(const Stek &s){
        if(this==&s) return *this;
        while(prepoc->sljedeci!=nullptr){
            cvor<tip>*tmp=prepoc->sljedeci;
            prepoc->sljedeci=tmp->sljedeci;
            delete tmp;
        }
        prepoc->sljedeci=nullptr;
        duzina=s.duzina;
        cvor<tip>*tmp,*trenutni=prepoc;
        tmp=s.prepoc->sljedeci;
        while(tmp){
            cvor<tip>*novi=new cvor<tip>;
            novi->vrijednost=tmp->vrijednost;
            novi->sljedeci=nullptr;
            trenutni->sljedeci=novi;
            trenutni=trenutni->sljedeci;
            tmp=tmp->sljedeci;
        }
        return *this;
    }
    Stek &operator =(Stek &&s){
        std::swap(prepoc,s.prepoc);
        std::swap(duzina,s.duzina);
        return *this;
    }
    ~Stek(){
        while(prepoc->sljedeci!=nullptr){
            cvor<tip>*tmp=prepoc->sljedeci;
            prepoc->sljedeci=tmp->sljedeci;
            delete tmp;
        }
        delete prepoc;
        duzina=0;
    }
};
template<typename tip>
void test1(Stek<tip>&n){
    std::cout<<n.brojElemenata()<<std::endl;
}
template<typename tip>
void test2(Stek<tip>&n){
    std::cout<<n.skini()<<std::endl;
}
template<typename tip>
void test3(Stek<tip>&n){
    n.brisi();
    std::cout<<n.brojElemenata()<<std::endl;
}
template<typename tip>
void test4(Stek<tip>&n,tip a){
    std::cout<<n.brojElemenata()<<std::endl;
    n.stavi(a);
    std::cout<<n.brojElemenata()<<std::endl;
}
int main() {
    std::cout << "Pripremna Zadaca Za Vjezbu 3, Zadatak 1";
    return 0;
}

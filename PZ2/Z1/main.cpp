#include <iostream>
#include <utility>
#include <exception>
using namespace std;
template <typename Tip> 
class Lista{
    public:
    Lista (){}
    virtual int brojElemenata() const=0;
    virtual const Tip trenutni() const=0;
    virtual Tip& trenutni() =0;
    virtual bool prethodni() =0;
    virtual bool sljedeci() =0;
    virtual void pocetak() =0;
    virtual void kraj() =0;
    virtual void obrisi()=0;
    virtual void dodajIspred(const Tip& el)=0;
    virtual void dodajIza(const Tip& el)=0;
    virtual const Tip operator[](const int &ix) const=0;
    virtual Tip &operator[](const int &ix)=0;
    virtual ~Lista(){}
};
template <typename Tip>
class NizLista: public Lista<Tip>{
    Tip *niz;
    int brojEl,kapacitet,indexTr;
    public:
    NizLista(){
        brojEl=0;
        kapacitet=0;
        indexTr=0;
        niz=nullptr;
    }
    NizLista(const NizLista &n){
        kapacitet=n.kapacitet;
        brojEl=n.brojEl;
        indexTr=n.indexTr;
        niz=new Tip [kapacitet];
        for(int i(0);i<brojEl;i++){
            niz[i]=n.niz[i];
        }
    }
 
    
    int brojElemenata() const override{return brojEl;}
    const Tip trenutni()const override{
        return niz[indexTr];
    }
    Tip &trenutni() override{
        return niz[indexTr];
    }
    bool prethodni() override{
        if(brojEl==0) throw std::logic_error("PRAZAN");
        if(indexTr==0) return false;
        indexTr--;
        return true;
    };
    bool sljedeci()override{
      if(brojEl==0) throw std::logic_error("PRAZAN");
      if(indexTr==brojEl-1)return false;
      indexTr++;
      return true;
    };
    void pocetak() override{
    if(brojEl==0) throw std::logic_error("PRAZAN");
    indexTr=0;
    }
    void kraj()override{
    if(brojEl==0) throw std::logic_error("PRAZAN");
    indexTr=brojEl-1;
    }
    void dodajIspred(const Tip&el){
        
       if(kapacitet==0){
           kapacitet++;
           niz=new Tip[kapacitet];
           //**niz=new Tip*[kapacitet];
           niz[0]=el;
           brojEl++;
       } 
       else if(brojEl<kapacitet){
           for(int i=brojEl;i>indexTr;i--){
               niz[i]=niz[i-1];
           }
           niz[indexTr]=el;
           indexTr++;
           brojEl++;
       }
       else{
           Tip *privremeni=new Tip[2*kapacitet];
           for(int i(0);i<indexTr;i++){
               privremeni[i]=niz[i];
           }
           privremeni[indexTr]=el;
           for(int i=indexTr;i<brojEl;i++) privremeni[i+1]=niz[i];
           indexTr++;
           kapacitet=2*kapacitet;
           brojEl++;
           delete [] niz;
           niz=privremeni;
       }
       
    }
    void dodajIza(const Tip &el){
        if(kapacitet==0){
            kapacitet++;
            niz=new Tip[kapacitet];
            niz[0]=el;
            brojEl++;
        }
        else if(brojEl<kapacitet && kapacitet!=1){
            for(int i=brojEl;i>indexTr;i--){
                niz[i]=niz[i-1];
            }
            niz[indexTr+1]=el;
            brojEl++;
        }
        else{
            Tip *niz2=new Tip[2*kapacitet];
            for(int i=0;i<=indexTr;i++){
                niz2[i]=niz[i];
            }
            niz2[indexTr+1]=el;
            for(int i=indexTr+1;i<brojEl;i++) niz2[i+1]=niz[i];
        kapacitet=2*kapacitet;
        brojEl++;
        delete []niz;
        niz=niz2;
        }
    }
    const Tip operator[](const int &ix)const override{
        if(ix>=brojEl || ix<0) throw ("Error!");
        return niz[ix];
    }
    Tip &operator[] (const int &ix) override{
        if(ix>=brojEl || ix<0) throw("Error!");
        return niz[ix];
    }
    void obrisi() override{
        if(brojEl==0) throw "prazan";
        
        if(brojEl==1) {
           brojEl--;
        }
        else if(indexTr==brojEl-1){
            brojEl--; indexTr--;
        }
        else{
            for(int i=indexTr;i<brojEl-1;i++) 
            niz[i]=niz[i+1];
            brojEl--;
        }
    }
    ~NizLista(){
        
        delete[]niz;
    }
    NizLista &operator=(const NizLista&n){
        if(this==&n) return *this;
        indexTr=n.indexTr;
        kapacitet=n.kapacitet;
        brojEl=n.brojEl;
        delete[]niz;
        niz=new Tip[kapacitet];
        for(int i=0;i<brojEl;i++){
            niz[i]=n.niz[i];
        }
        return *this;
    }
    NizLista &operator =(NizLista&n){
        indexTr=n.indexTr;
        kapacitet=n.kapacitet;
        brojEl=n.brojEl;
        delete[]niz;
        niz=n.niz;
        n.niz=nullptr;
        return *this;
    }
};
template <typename Tip> struct Cvor{
    Tip vr;
    Cvor<Tip> *sljedeci=nullptr;
};

template <typename Tip> 
class JednostrukaLista: public Lista<Tip>{
    Cvor<Tip> *Ta,*prepoc;
    int duzina;
    public:
    JednostrukaLista(){
        prepoc=new Cvor<Tip>;
        Ta=nullptr;
        duzina=0;
    }
    JednostrukaLista(const JednostrukaLista &n){
    
       prepoc=new Cvor<Tip>;
       // prepoc->sljedeci=nullptr;
        duzina=n.duzina;
        Ta=nullptr;
        Cvor<Tip> *tmp,*trenutni=prepoc;
        tmp=n.prepoc->sljedeci;
        while(tmp){
            Cvor<Tip> *novi=new Cvor<Tip>;
            if(tmp==n.Ta) Ta=novi;
            novi->vr=tmp->vr;
            novi->sljedeci=nullptr;
            trenutni->sljedeci=novi;
            trenutni=trenutni->sljedeci;
            tmp=tmp->sljedeci;
           // delete novi;
        }
        //delete novi;
         
      
    }
    JednostrukaLista( JednostrukaLista &&n){
        std::swap(prepoc,n.prepoc);
        std::swap(Ta,n.Ta);
        std::swap(duzina,n.duzina);
    }
    int brojElemenata()const override{return duzina;}
    const Tip trenutni()const override{
        return Ta->vr;
    }
    Tip &trenutni()override{
        return Ta->vr;
    }
    bool prethodni() override{
        if(duzina==0) throw("ERROR!");
        if(prepoc->sljedeci==Ta) return false;
        Cvor<Tip> *tmp=prepoc;
        while(tmp->sljedeci!=Ta) tmp=tmp->sljedeci;
        Ta=tmp;
        return true;
    };
    bool sljedeci()override{
        if(duzina==0) return false;
        if(Ta->sljedeci==nullptr)return false;
        Ta=Ta->sljedeci;
        return true;
    };
    void pocetak()override{
        if(duzina==0) throw("ERROR!");
        Ta=prepoc->sljedeci;
    }
    void kraj()override{
        if(duzina==0) throw ("ERROR!");
        while (Ta->sljedeci!=nullptr) {
            Ta=Ta->sljedeci;
        }
    }
    const Tip operator[](const int &ix) const override{
        if(ix>=duzina || ix<0) throw ("ERROR!");
        Cvor<Tip> *tmp=prepoc->sljedeci;
        for(int i=0;i<ix;i++) tmp=tmp->sljedeci;
        return tmp->vr;
    }
    Tip &operator[](const int &ix) override{
        if(ix>=duzina || ix<0) throw ("ERROR!");
        Cvor<Tip> *tmp=prepoc->sljedeci;
        for(int i=0;i<ix;i++) tmp=tmp->sljedeci;
        return tmp->vr;
    }
    void obrisi() override{
        if(duzina==0) throw ("NE MOZE!");
        Cvor<Tip>*tmp=prepoc;
        while(tmp->sljedeci!=Ta) tmp=tmp->sljedeci;
        tmp->sljedeci=Ta->sljedeci;
        delete Ta;
        if(tmp->sljedeci==nullptr) Ta=tmp;
        else Ta=tmp->sljedeci;
        duzina--;
    }
    void dodajIspred(const Tip&el){
        if(duzina==0){
            Cvor<Tip>*tmp=new Cvor<Tip>;
            tmp->vr=el;
            tmp->sljedeci=nullptr;
            prepoc->sljedeci=tmp;
            Ta=tmp;
            duzina++;
        }
        else if(duzina==1){
            Cvor<Tip>*novi=new Cvor<Tip>;
            novi->vr=el;
            novi->sljedeci=Ta;
            prepoc->sljedeci=novi;
            duzina++;
        }
        else{
            Cvor<Tip>*tmp=prepoc;
            while (tmp->sljedeci!=Ta) { 
                tmp=tmp->sljedeci;
            }
            Cvor<Tip>*pomocni=new Cvor<Tip>;
            pomocni->vr=el;
            pomocni->sljedeci=Ta;
            tmp->sljedeci=pomocni;
            duzina++;
        }
    }
    void dodajIza(const Tip&el){
        if(duzina==0){
            Cvor<Tip>*tmp=new Cvor<Tip>;
            tmp->vr=el;
            tmp->sljedeci=nullptr;
            prepoc->sljedeci=tmp;
            Ta=tmp;
            duzina++;
        }
        else{
            Cvor<Tip>*tmp=new Cvor<Tip>;
            tmp->vr=el;
            tmp->sljedeci=Ta->sljedeci;
            Ta->sljedeci=tmp;
            duzina++;
        }
    }
    ~JednostrukaLista(){
        while (prepoc->sljedeci!=nullptr) {
            Cvor<Tip> *tmp;
            tmp=prepoc->sljedeci;
            prepoc->sljedeci=tmp->sljedeci;
            delete tmp;
            
        }
        delete prepoc;
    }
    JednostrukaLista&operator =(const JednostrukaLista &n){
        if(this==&n) return *this;
        while(prepoc->sljedeci!= nullptr){
            Cvor<Tip> *tmp;
            tmp=prepoc->sljedeci;
            prepoc->sljedeci=tmp->sljedeci;
            delete tmp;
        }
        prepoc->sljedeci=nullptr;
        duzina=n.duzina;
        Ta=nullptr;
        Cvor<Tip>*tmp,*trenutni=prepoc;
        tmp=n.prepoc->sljedeci;
        while (tmp) {
            Cvor<Tip> *novi=new Cvor<Tip>;
            if(tmp==n.Ta) Ta=novi;
            novi->vr=tmp->vr;
            novi->sljedeci=nullptr;
            trenutni->sljedeci=novi;
            trenutni=trenutni->sljedeci;
            tmp=tmp->sljedeci;
            
        }
        return *this;
    }
    JednostrukaLista &operator =(JednostrukaLista &&n){
        std::swap(prepoc,n.prepoc);
        std::swap(Ta,n.Ta);
        std::swap(duzina,n.duzina);
        return *this;
    }

    
    //Funkcije za provjeru
    void ispis1(){
        Cvor<Tip>*pom=prepoc;
        std::cout <<duzina << std::endl;
        while(pom->sljedeci!=nullptr){
            pom=pom->sljedeci;
            std::cout <<  pom->vr<< std::endl;
        }
    }
    void t2(){
        std::cout << "Tek"<<Ta->vr << std::endl;
    }
};
template <typename Tip> 
void testNizListaDodajIspred(NizLista<Tip>&n1,int n){
    n1.dodajIspred(n);
}
template <typename Tip> 
void testNizListaDodajIza(NizLista<Tip>&n1,int n){
    n1.dodajIza(n);
}
template<typename Tip> 
void PrethodniTest(NizLista<Tip>&n1){
    try{
        n1.prethodni();
    }
    catch(...) {throw "IZZZZ";}
}
template<typename Tip> 
void SljedeciTest(NizLista<Tip>&n1){
    try{
        n1.sljedeci();
    }
    catch(...) {throw "IZZZZ";}
}
template<typename Tip>
void testObrisi(NizLista<Tip> &n1){
       try{
        n1.obrisi();
    }
    catch(...) {throw "IZZZZ";}
}
template<typename Tip>
Tip JednostrukaListaOperatorIndeks(JednostrukaLista<Tip> &l,int i){
    try {
       return l[i];
    }
    catch (...) {
        throw "izzzz";
    }
    
}

int main() { 
    NizLista<int>n1;
    for(int i=0;i<10;i++) testNizListaDodajIspred(n1,i+1);
     for(int i=0;i<10;i++) testNizListaDodajIza(n1,i+1);
    testObrisi(n1);
    JednostrukaLista<int> lista;
for (int i(1); i<=50; i++){
if(i%2==0)	lista.dodajIspred(i);
else lista.dodajIza(i);
}
std::cout << JednostrukaListaOperatorIndeks(lista, 5) << " " ;
    return 0;
}

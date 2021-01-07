#include <iostream>
#include<utility>

template <typename tip> 
class Iterator;

template<typename tip> 
class Lista{
    public:
    Lista(){}
    virtual int brojElemenata() const=0;
    virtual const tip trenutni() const=0;
    virtual tip& trenutni()=0;
    virtual bool prethodni()=0;
    virtual bool sljedeci()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual void obrisi()=0;
    virtual void dodajIspred(const tip &el)=0;
    virtual void dodajIza(const tip &el)=0;
    virtual const tip operator[](const int &ix) const=0;
    virtual tip & operator[](const int &ix)=0;
    virtual ~Lista(){}
};
template <typename tip>
struct cvor{
    tip vrijednost;
    cvor<tip>*sljedeci=nullptr,*prethodni=nullptr;
};
template<typename tip>
class DvostrukaLista: public Lista<tip>{
    //tekuci tj element na koji lista trenunto pokazuje
    //prepoc je pokazivac na prvi element lista
    //poskraja je pokazivac na kraj liste tj zadnji element
    cvor<tip>*tekuci,*prepoc=nullptr,*poskraja=nullptr;
    int duzina;
    public:
    //Konstruktor bez parametara , podesava sve na null vrijednosti odnosno default vrijednosti
    DvostrukaLista(){
        prepoc=new cvor<tip>;
        poskraja=new cvor<tip>;
        prepoc->sljedeci=poskraja;
        poskraja->prethodni=prepoc;
        poskraja->sljedeci=nullptr;
        tekuci=nullptr;
        duzina=0;
    }
    //Konstruktor s jednim parametrom koji prima constanu referencu na dvostruku listu
    //potrebno je elemente vec postoje liste postaviti na null vrijednosti a zatim iskopirati proslijedjnu listu u nasu
    DvostrukaLista(const DvostrukaLista &n){
        prepoc=new cvor<tip>;
        poskraja=new cvor<tip>;
        prepoc->prethodni=nullptr;
        poskraja->sljedeci=nullptr;
        prepoc->sljedeci=nullptr;
        duzina=n.duzina;
        
        tekuci=nullptr;
        cvor<tip>*tmp,*trenutni=prepoc;
        //pokazivac tmp sluzi za kretanje kroz datu listu kako ne bi doslo do gubitka podataka
        tmp=n.prepoc->sljedeci;
        while(tmp){
            cvor<tip>*novi=new cvor<tip>;
            if(tmp==n.tekuci) tekuci=novi;
            novi->vrijednost=tmp->vrijednost;
            //=nullptr ukoliko nema vise elemenata to bi bio zadnji koji bi pokazivao na nullptr 
            //kako pri kretenju ne bi pristupali nekom nedefinisanom elementu
            novi->sljedeci=nullptr;
            novi->prethodni=trenutni;
            //trenutni postavljamo na sljedeci kako bi na taj sljedeci mogli nadovezati novi (ukoliko ga ima)
            trenutni->sljedeci=novi;
            trenutni=trenutni->sljedeci;
            tmp=tmp->sljedeci;
        }
        //pocetne vrijednosti liste postavljamo na vrijednosti koje smo dobili u while petlji iznad
        trenutni->sljedeci=poskraja;
        poskraja->prethodni=trenutni;
    }
    //kopiraj i razmjeni
    DvostrukaLista( DvostrukaLista &&n){
        std::swap(prepoc,n.prepoc);
        std::swap(poskraja,n.poskraja);
        std::swap(tekuci,n.tekuci);
        std::swap(duzina,n.duzina);
    }
    int brojElemenata() const override{return duzina;}
    const tip trenutni() const override{return tekuci->vrijednost;}
    tip &trenutni() override{return tekuci->vrijednost;}
    bool prethodni() override{
        //ako je duzina =0 baci izuzetak da ne bi pokusavali pristupit necem nedefinisanom
        if(duzina==0) throw;
        // ako je trenutni prvi element liste 
        if(tekuci->prethodni==prepoc) return false;
        tekuci=tekuci->prethodni;
        return true;
    };
    bool sljedeci()override{
        // ista stvar kao i gore samo ako je sljedeci onaj zadnji element liste
        if(duzina==0) throw;
        if(tekuci->sljedeci==nullptr || tekuci->sljedeci==poskraja) 
        return false;
        tekuci=tekuci->sljedeci;
        return true;
    };
    // postavi trenutni da pokazuje na pocetak liste
    void pocetak()override{
        if(duzina==0) throw;
        tekuci=prepoc->sljedeci;
    }
    // postavi trenutni da pokazuje na kraj liste
    void kraj() override{
        if(duzina==0) throw;
        tekuci=poskraja->prethodni;
    }
    // preklopljeni operator uglastih zagrada
    const tip operator[](const int &ix)const override{
        if(ix>=duzina || ix<0) throw;
        cvor<tip>*tmp=prepoc->sljedeci;
        for(int i=0;i<ix;i++) tmp=tmp->sljedeci;
        return tmp->vrijednost;
    }
    tip& operator[]( const int &ix) override{
        if(ix>=duzina || ix<0) throw;
        cvor<tip>*tmp=prepoc->sljedeci;
        for(int i=0;i<ix;i++) tmp=tmp->sljedeci;
        return tmp->vrijednost;
    }
    
    void obrisi() override{
        if(duzina==0) throw;
        //tmp je privremeni pokazivac za kretanje kroz listu jer ukoliko obrisemo jedan element
        //izgubili bi podatke gdje se nalazi sljedeci element u listi te ih ne bi mogli obrisati i doslo bi do curenja memorije
        cvor<tip> *tmp=prepoc;
        while(tmp->sljedeci!=tekuci) tmp=tmp->sljedeci;
        tmp->sljedeci=tekuci->sljedeci;
        delete tekuci;
        if(tmp->sljedeci==nullptr) tekuci=tmp;
        else tekuci=tmp->sljedeci;
        duzina--;
    }
    //preklopljeni operator =
    DvostrukaLista &operator=(const DvostrukaLista &n){
        //izbjegavanje samododjele
        if(this==&n) return *this;
        //obrisi sve kroz listu
        while(prepoc->sljedeci!=nullptr){
            cvor<tip>*tmp;
            tmp=prepoc->sljedeci;
            prepoc->sljedeci=tmp->sljedeci;
            delete tmp;
        }
        //kao kod kodstruktora s jednim parametrom jednostavno sve iskopiramo
        prepoc->sljedeci=nullptr;
        duzina=n.duzina;
        tekuci=nullptr;
        cvor<tip>*tmp,*trenutni=prepoc;
        tmp=n.prepoc->sljedeci;
        while (tmp) {
            cvor<tip>*novi=new cvor<tip>;
            if(tmp==n.tekuci) tekuci=novi;
            novi->vrijednost=tmp->vrijednost;
            novi->sljedeci=nullptr;
            trenutni->sljedeci=novi;
            trenutni=trenutni->sljedeci;
            tmp=tmp->sljedeci;
        }
        return *this;
    }
    //dvostruka referena opet samo kopiraj i razmjeni
    DvostrukaLista &operator=(  DvostrukaLista &&n){
        std::swap(prepoc,n.prepoc);
        std::swap(poskraja,n.poskraja);
        std::swap(tekuci,n.tekuci);
        std::swap(duzina,n.duzina);
        return *this;
    }
    // destruktor, obrisemo sve elemente liste da ne dodje do curenja memorije
    ~DvostrukaLista(){
        while(prepoc->sljedeci!=nullptr){
            cvor<tip> *tmp;
            tmp=prepoc->sljedeci;
            prepoc->sljedeci=tmp->sljedeci;
            delete tmp;
        }
        delete prepoc;
    }
    void dodajIza(const tip &el){
        if(duzina==0){
            cvor<tip>*tmp=new cvor <tip>;
            tmp->vrijednost=el;
            tmp->sljedeci=poskraja;
            tmp->prethodni=prepoc;
            poskraja->prethodni=tmp;
            prepoc->sljedeci=tmp;
            tekuci=tmp;
            duzina++;
        }
        else{
            cvor<tip>*novi=new cvor<tip>,*tmp;
            novi->vrijednost=el;
            novi->sljedeci=tekuci->sljedeci;
            novi->prethodni=tekuci;
            
            tekuci->sljedeci=novi;
            tmp=novi->sljedeci;
            tmp->prethodni=novi;
            duzina++;
        }
    }
    void dodajIspred(const tip& el){
        if(duzina==0){
            cvor<tip>*novi=new cvor<tip>;
            novi->vrijednost=el;
            novi->sljedeci=poskraja;
            novi->prethodni=prepoc;
            prepoc->sljedeci=novi;
            poskraja->prethodni=novi;
            tekuci=novi;
            duzina++;
        }
        else if(duzina==1){
            cvor<tip>*novi=new cvor<tip>;
            novi->vrijednost=el;
            novi->sljedeci=poskraja;
            novi->prethodni=prepoc;
            prepoc->sljedeci=novi;
            tekuci->prethodni=novi;
            duzina++;
        }
        else{
            cvor<tip>*novi=new cvor<tip>,*tmp;
            novi->vrijednost=el;
            novi->sljedeci=tekuci;
            novi->prethodni=tekuci->prethodni;
            
            tekuci->prethodni=novi;
            tmp=novi->prethodni;
            tmp->sljedeci=novi;
            duzina++;
        }
    }
    friend class Iterator<tip>;
};

template <typename tip>
class Iterator{
    cvor<tip> *tekuci,*prepoc=nullptr,*poskraja=nullptr;
    int duzina;
    public:
    Iterator(const DvostrukaLista<tip> &dl){
        tekuci=dl.tekuci;
        prepoc=dl.prepoc;
        poskraja=dl.poskraja;
        duzina=dl.duzina;
    }
    tip trenutni(){
        return tekuci->vrijednost;
    }
    void pocetak(){
        if(duzina==0) throw;
        tekuci=prepoc->sljedeci;
    }
    bool sljedeci(){
        if (duzina==0) return false;
        if(tekuci->sljedeci==nullptr || tekuci->sljedeci==poskraja) return false;
        tekuci=tekuci->sljedeci;
        return true;
    }
};
template<typename tip>
tip dajMaksimum(const Lista<tip>&l){
    Iterator<tip> it=dynamic_cast<const DvostrukaLista<tip>&> (l);
    it.pocetak();
    tip max=it.trenutni();
    while(it.sljedeci()){
        if(it.trenutni()>max)
        max=it.trenutni();
    }
    return max;
}

int main() {
DvostrukaLista<int> lista;
for (int i(1); i<=50; i++){
if(i%2==0)	lista.dodajIspred(i);
else lista.dodajIza(i);
}

    return 0;
}

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

template <typename TipKljuca, typename TipVrijednosti>
class Mapa {
    public:
        Mapa() {}
        virtual ~Mapa() {}
        virtual int brojElemenata() const { return 0; }
        virtual TipVrijednosti &operator[] (TipKljuca kljuc) = 0;
        virtual TipVrijednosti operator [] (TipKljuca kljuc) const = 0;
        virtual void obrisi() {}
        virtual void obrisi(const TipKljuca &kljuc) {}
};



template <typename TipKljuca, typename TipVrijednosti>
struct Pair {
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
};

template <typename TipKljuca, typename TipVrijednosti>
class NizMapa : public Mapa<TipKljuca,TipVrijednosti> {
    private:
        Pair<TipKljuca,TipVrijednosti>* parovi;
        int broj=0;
        int kapacitet=500;
    public:
        NizMapa() : broj(0) { parovi=new Pair<TipKljuca,TipVrijednosti>[kapacitet]; }
        NizMapa(const NizMapa &nm);
        NizMapa(NizMapa &&nm) : kapacitet(nm.kapacitet), broj(nm.broj), parovi(nm.parovi) {}
        NizMapa &operator=(const NizMapa &nm);
        NizMapa &operator=(NizMapa &&nm);
        ~NizMapa() { delete[] parovi; }
        int brojElemenata() const { return broj; }
        TipVrijednosti &operator[] (TipKljuca kljuc);
        TipVrijednosti operator [] (TipKljuca kljuc) const;
        void obrisi() { delete[] parovi; broj=0; kapacitet=500; parovi=new Pair<TipKljuca,TipVrijednosti>[kapacitet]; }
        void obrisi(const TipKljuca &kljuc);
};

template <typename TipKljuca, typename TipVrijednosti>
NizMapa<TipKljuca,TipVrijednosti> &NizMapa<TipKljuca,TipVrijednosti>::operator= (NizMapa &&nm) {
    if(this==&nm) return *this;
    delete[] parovi;
    kapacitet=nm.kapacitet;
    broj=nm.broj;
    parovi=nm.parovi;
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
NizMapa<TipKljuca,TipVrijednosti> &NizMapa<TipKljuca,TipVrijednosti>::operator= (const NizMapa &nm) {
    if(this==&nm) return *this;
    delete[] parovi;
    kapacitet=nm.kapacitet;
    broj=nm.broj;
    parovi=new Pair<TipKljuca,TipVrijednosti>[kapacitet];
    for(int i(0);i<broj;i++)
        parovi[i]=nm.parovi[i];
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
NizMapa<TipKljuca,TipVrijednosti>::NizMapa(const NizMapa &nm) {
    kapacitet=nm.kapacitet;
    broj=nm.broj;
    parovi=new Pair<TipKljuca,TipVrijednosti>[kapacitet];
    for(int i(0);i<broj;i++)
        parovi[i]=nm.parovi[i];
}

template <typename TipKljuca, typename TipVrijednosti>
void NizMapa<TipKljuca,TipVrijednosti>::obrisi(const TipKljuca &kljuc) {
    for(int i(0);i<broj;i++)
        if(parovi[i].kljuc==kljuc) {
            for(int j(i);j<broj-1;j++)
                parovi[j]=parovi[j+1];
            broj--;
        }
}

template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti NizMapa<TipKljuca,TipVrijednosti>::operator[] (TipKljuca kljuc) const {
    for(int i(0);i<broj;i++)
        if(kljuc==parovi[i].kljuc) return parovi[i].vrijednost;
    return TipVrijednosti();
}

template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti &NizMapa<TipKljuca,TipVrijednosti>::operator[] (TipKljuca kljuc) {
    for(int i(0);i<broj;i++)
        if(kljuc==parovi[i].kljuc) return parovi[i].vrijednost;
    if(broj==kapacitet) {
        kapacitet*=2;
        Pair<TipKljuca,TipVrijednosti>* pomocni=new Pair<TipKljuca,TipVrijednosti>[kapacitet];
        for(int i(0);i<broj;i++)
            pomocni[i]=parovi[i];
        delete[] parovi;
        parovi=pomocni;
    }
    broj++;
    Pair<TipKljuca,TipVrijednosti> tempPar;
    tempPar.kljuc=kljuc;
    tempPar.vrijednost=TipVrijednosti();
    parovi[broj-1]=tempPar;
    return parovi[broj-1].vrijednost;
}

template <typename TipKljuca, typename TipVrijednosti>
struct BCvor {
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
    BCvor<TipKljuca,TipVrijednosti>* roditelj=nullptr;
    BCvor<TipKljuca,TipVrijednosti>* lijevi=nullptr;
    BCvor<TipKljuca,TipVrijednosti>* desni=nullptr;
};


template <typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa : public Mapa<TipKljuca,TipVrijednosti> {
    private:
        BCvor<TipKljuca,TipVrijednosti>* korijen;
        int broj;
        void preorderKopiraj(BCvor<TipKljuca,TipVrijednosti>* cvor1, BCvor<TipKljuca,TipVrijednosti>* &cvor2, BCvor<TipKljuca,TipVrijednosti>* prethodni=nullptr);
    public:
        BinStabloMapa() : korijen(nullptr), broj(0) {}
        ~BinStabloMapa() { this->obrisi(); }
        BinStabloMapa(const BinStabloMapa &bsm);
        BinStabloMapa(BinStabloMapa &&bsm) : korijen(bsm.korijen), broj(bsm.broj) {}
        BinStabloMapa &operator=(const BinStabloMapa &bsm);
        BinStabloMapa &operator=(BinStabloMapa &&bsm);
        int brojElemenata() const { return broj; }
        TipVrijednosti &operator[] (TipKljuca kljuc);
        TipVrijednosti operator [] (TipKljuca kljuc) const;
        void obrisi();
        void obrisi(const TipKljuca &kljuc);
};

template <typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca,TipVrijednosti> &BinStabloMapa<TipKljuca,TipVrijednosti>::operator=(BinStabloMapa &&bsm) {
    if(this==&bsm) return *this;
    this->obrisi();
    korijen=bsm.korijen;
    broj=bsm.broj;
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca,TipVrijednosti> &BinStabloMapa<TipKljuca,TipVrijednosti>::operator=(const BinStabloMapa &bsm) {
    if(this==&bsm) return *this;
    this->obrisi();
    preorderKopiraj(bsm.korijen, korijen);
    broj=bsm.broj;
    return *this;
}

template <typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca,TipVrijednosti>::preorderKopiraj(BCvor<TipKljuca,TipVrijednosti>* cvor1, BCvor<TipKljuca,TipVrijednosti>* &cvor2, BCvor<TipKljuca,TipVrijednosti>* prethodni) {
    if(cvor1!=nullptr) {
        cvor2=new BCvor<TipKljuca,TipVrijednosti>();
        cvor2->kljuc=cvor1->kljuc;
        cvor2->vrijednost=cvor1->vrijednost;
        cvor2->roditelj=prethodni;
        preorderKopiraj(cvor1->lijevi, cvor2->lijevi, cvor2);
        preorderKopiraj(cvor1->desni, cvor2->desni, cvor2);
    }
}

template <typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca,TipVrijednosti>::BinStabloMapa(const BinStabloMapa &bsm) : broj(bsm.broj) {
    preorderKopiraj(bsm.korijen, korijen);
}

template <typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca,TipVrijednosti>::obrisi(const TipKljuca &kljuc) {
    BCvor<TipKljuca,TipVrijednosti>* p=korijen, *roditelj=nullptr;
    while(p!=nullptr && kljuc!=p->kljuc) {
        roditelj=p;
        if(kljuc<p->kljuc) p=p->lijevi;
        else p=p->desni;
    }
    if(p==nullptr) return;
    BCvor<TipKljuca,TipVrijednosti>* m;
    if(p->lijevi==nullptr) m=p->desni;
    else {
        if(p->desni==nullptr) m=p->lijevi;
        else {
            BCvor<TipKljuca,TipVrijednosti>* pm=p, *tmp;
            m=p->lijevi;
            tmp=m->desni;
            while(tmp!=nullptr) {
                pm=m;
                m=tmp;
                tmp=m->desni;
            }
            if(pm!=p) {
                pm->desni=m->lijevi;
                m->lijevi=p->lijevi;
            }
            m->desni=p->desni;
        }
    }
    if(roditelj==nullptr) korijen=m;
    else {
        if(p==roditelj->lijevi) roditelj->lijevi=m;
        else roditelj->desni=m;
    }
    delete p;
    broj--;
}

template <typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca,TipVrijednosti>::obrisi() {
    while(korijen!=nullptr) obrisi(korijen->kljuc);
}

template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti BinStabloMapa<TipKljuca,TipVrijednosti>::operator[] (TipKljuca kljuc) const {
    BCvor<TipKljuca,TipVrijednosti>* temp=korijen;
    while(temp!=nullptr && kljuc!=temp->kljuc) {
        if(kljuc<temp->kljuc) temp=temp->lijevi;
        else temp=temp->desni;
    }
    if(temp==nullptr) return TipVrijednosti();
    return temp->vrijednost;
}

template <typename TipKljuca, typename TipVrijednosti>
TipVrijednosti &BinStabloMapa<TipKljuca,TipVrijednosti>::operator[] (TipKljuca kljuc) {
    BCvor<TipKljuca,TipVrijednosti>* temp=korijen;
    while(temp!=nullptr && kljuc!=temp->kljuc) {
        if(kljuc<temp->kljuc) temp=temp->lijevi;
        else temp=temp->desni;
    }
    
    if(temp==nullptr) {
        temp=new BCvor<TipKljuca,TipVrijednosti>();
        broj++;
        temp->kljuc=kljuc;
        temp->vrijednost=TipVrijednosti();
        BCvor<TipKljuca,TipVrijednosti>* x=korijen,*y=nullptr;
        while(x!=nullptr) {
            y=x;
            if(temp->kljuc<x->kljuc) x=x->lijevi;
            else x=x->desni;
        }
        if(y==nullptr) korijen=temp;
        else {
            if(temp->kljuc<y->kljuc) y->lijevi=temp;
            else y->desni=temp;
            temp->roditelj=y;
        }
    }
    return temp->vrijednost;
}


void generisi(Mapa<int,int> &m, int vel) {
    srand(time(NULL));
    for(int i(0);i<vel;i++)
        m[i]=rand();
}

void testNizBinStablo() {
    BinStabloMapa<int,int> bsm;
    NizMapa<int,int> nm;

    clock_t vrijeme1=clock();
    generisi(bsm,7500);
    clock_t vrijeme2=clock();
    double ukvrijeme1=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000);

    clock_t vrijeme3=clock();
    generisi(nm,7500);
    clock_t vrijeme4=clock();
    double ukvrijeme2=(vrijeme4-vrijeme3)/(CLOCKS_PER_SEC/1000);

    std::cout << "Binarno stablo dodavanje: " << ukvrijeme1/7500 << " ms " << std::endl << "Niz mapa dodavanje: " << ukvrijeme2/7500 << " ms " << std::endl;

    clock_t vrijeme5=clock();
    for(int i(0);i<7500;i++)
        bsm[i];
    clock_t vrijeme6=clock();
    double ukvrijeme3=(vrijeme6-vrijeme5)/(CLOCKS_PER_SEC/1000);

    clock_t vrijeme7=clock();
    for(int i(0);i<7500;i++)
        nm[i];
    clock_t vrijeme8=clock();
    double ukvrijeme4=(vrijeme8-vrijeme7)/(CLOCKS_PER_SEC/1000);

    std::cout << "Binarno stablo pristup: " << ukvrijeme3/7500 << " ms " << std::endl << "Niz mapa pristup: " << ukvrijeme4/7500 << " ms " << std::endl;

}

int main() {
    testNizBinStablo();
}

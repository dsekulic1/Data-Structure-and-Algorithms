#include <iostream>
using namespace std;
template<typename Tip>
struct cvor{
    Tip vrijednost;
    cvor<Tip> *sljedeci=nullptr;
};

template <typename Tip>
class Red{
  cvor<Tip> *pocetak,*kraj;
  int duzina;
  
  public:
  Red(){
      pocetak=new cvor<Tip>;
      duzina=0;
      kraj=pocetak;
  }
  Red(const Red &r){
      pocetak=new cvor<Tip>;
      pocetak->sljedeci=nullptr;
      duzina=r.duzina;
      cvor<Tip>*tmp,*trenutni=pocetak;
      tmp=r.pocetak->sljedeci;
      while(tmp){
          cvor<Tip>*novi=new cvor<Tip>;
          novi->vrijednost=tmp->vrijednost;
          novi->sljedeci=nullptr;
          trenutni->sljedeci=novi;
          trenutni=trenutni->sljedeci;
          tmp=tmp->sljedeci;
      }
      kraj=trenutni;
  }
  Red(Red &&r){
      std::swap(pocetak,r.pocetak);
      std::swap(duzina,r.duzina);
      std::swap(kraj,r.kraj);
  }
  void brisi(){
      while(pocetak->sljedeci!=nullptr){
          cvor<Tip>*tmp=pocetak->sljedeci;
          pocetak->sljedeci=tmp->sljedeci;
          delete tmp;
      }
      kraj=nullptr;
      duzina=0;
  }
  void stavi(const Tip &el){
      if(duzina==0)
                kraj=pocetak;
      cvor<Tip> *novi=new cvor<Tip>;
      novi->vrijednost=el;
      novi->sljedeci=nullptr;
      kraj->sljedeci=novi;
      kraj=kraj->sljedeci;
      
      duzina++;
  }
  Tip skini(){
      if(duzina==0) throw ("ERRR");
      
      cvor<Tip> *tmp=pocetak->sljedeci;
      pocetak->sljedeci=tmp->sljedeci;
      auto a=tmp->vrijednost;
      delete tmp;
      duzina--;
      return a;
  }
  Tip &celo(){
      if(duzina==0) throw;
      cvor<Tip> *tmp=pocetak->sljedeci;
      return tmp->vrijednost;
  }
  int brojElemenata(){return duzina;}
  Red &operator=(Red &&r){
      std::swap(pocetak,r.pocetak);
      std::swap(duzina,r.duzina);
      return *this;
  }
  Red &operator =(const Red &r){
      if(this==&r) return *this;
      while(pocetak->sljedeci!=nullptr){
          cvor<Tip>*tmp=pocetak->sljedeci;
          pocetak->sljedeci=tmp->sljedeci;
          delete tmp;
      }
      pocetak->sljedeci=nullptr;
      duzina=r.duzina;
      cvor<Tip> *tmp,*trenutni=pocetak;
      tmp=r.pocetak->sljedeci;
      while(tmp){
          cvor<Tip> *novi=new cvor<Tip>;
          novi->vrijednost=tmp->vrijednost;
          novi->sljedeci=nullptr;
          trenutni->sljedeci=novi;
          trenutni=trenutni->sljedeci;
          tmp=tmp->sljedeci;
      }
      return *this;
  }
  ~Red(){
      while(pocetak->sljedeci!=nullptr){
          cvor<Tip> *tmp=pocetak->sljedeci;
          pocetak->sljedeci=tmp->sljedeci;
          delete tmp;
      }
      delete pocetak;
      duzina= 0;
  }
};
template<typename Tip>
void TestNumero1(Red<Tip>&r){
    cout<<"Broj elemenata: "<<r.brojElemenata()<<endl;
}
template<typename Tip>
void TestNumero2(Red<Tip>r, Tip el){
    cout<<"Element na celu: "<<r.celo()<<endl;
    r.celo()=el;
        cout<<"Novi element na celu: "<<r.celo()<<endl;
}
template<typename Tip>
void TestNumero3(Red<Tip>&r){
    cout<<"Izbaceni element metodom skini: "<<r.skini()<<endl;
}
template<typename Tip>
void TestNumero4(Red<Tip>&r){
    r.brisi();
    cout<<"Broj elementa nakon brisanja: "<<r.brojElemenata()<<endl;
}
template<typename Tip>
void TestNumero5(Red<Tip>&r, Tip el){
    cout<<"Broj elementa prije dodavanja novog: "<<r.brojElemenata()<<endl;
    r.stavi(el);
    cout<<"Broj elementa poslije dodavanja novog: "<<r.brojElemenata()<<endl;
}
int main() {
Red<int> r;
for(int i(1);i<10;i++)r.stavi(i*2+1);
cout<< "Testna funkcija broj 1:"<<endl;
TestNumero1(r);
cout<< "Testna funkcija broj 2:"<<endl;
TestNumero2(r,15);
cout<< "Testna funkcija broj 3:"<<endl;
TestNumero3(r);
cout<< "Testna funkcija broj 4:"<<endl;
TestNumero4(r);
cout<< "Testna funkcija broj 5:"<<endl;
TestNumero5(r,81);

    return 0;
}

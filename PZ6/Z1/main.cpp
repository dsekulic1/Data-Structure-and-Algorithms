#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>
template<typename Tip>
void bubble_sort(Tip *niz, int vel){
    for(int i=vel-1;i>=1;i--){
        for(int j=1;j<=i;j++){
            if(niz[j-1]>niz[j])
                std::swap(niz[j-1],niz[j]);
        }
    }
}
template<typename Tip>
void selection_sort(Tip *niz, int vel){
    for(int i=0;i<=vel-2;i++){
        Tip min=niz[i];
        int pmin=i;
        for(int j=i+1;j<=vel-1;j++){
            if(niz[j]<min){
                min=niz[j];
                pmin=j;
            }
        }
        niz[pmin]=niz[i];
        niz[i]=min;
    }
}
template <typename Tip>
int particija(Tip *niz, int prvi, int zadnji){
    Tip pivot=niz[prvi];
    int p=prvi+1;
    while(p<=zadnji && niz[p]<pivot) p=p+1;
    for(int i=p+1;i<=zadnji;i++){
        if(niz[i]<pivot){
            std::swap(niz[i],niz[p]);
            p=p+1;
        }
    }
    std::swap(niz[prvi],niz[p-1]);
    return p-1;
}
template <typename Tip>
void quick_sortv2(Tip *niz, int prvi, int zadnji){
    
    if(prvi<zadnji){
        int j=particija(niz,prvi,zadnji);
        quick_sortv2(niz,prvi,j-1);
        quick_sortv2(niz,j+1,zadnji);
    }
}
template <typename Tip>
void quick_sort(Tip *niz, int vel){
    quick_sortv2(niz,0,vel-1);
}
template<typename Tip>
void merge(Tip *niz,int l, int p, int q, int u){
    int i=0;
    int j=q-l;
    int k=l;
    Tip *B=new Tip[u-l+1];
    for(int m=0;m<=u-l;m++) B[m]=niz[l+m];
    while(i<=p-l && j<=u-l){
        if(B[i]<B[j]) niz[k]=B[i++];
        else niz[k]=B[j++];
        k++;
    }
    while(i<=p-l) niz[k++]=B[i++];
    while(j<=u-l) niz[k++]=B[j++];
    delete [] B;
}
template<typename Tip>
void merge_sortv2(Tip* niz, int l,int u){
    if(u>l){
        int p=(l+u-1)/2;
        int q=p+1;
        merge_sortv2(niz,l,p);
        merge_sortv2(niz,q,u);
        merge(niz,l,p,q,u);
    }
    
}
template<typename Tip>
void merge_sort(Tip* niz, int vel){
    merge_sortv2(niz,0,vel-1);
}
void ucitaj(std::string filename, int *&niz, int &vel){
    std::fstream datoteka;
    int tmp=0;
    niz=new int[vel];
    datoteka.open(filename);
    while(tmp<vel){
        datoteka>> niz[tmp];
        tmp++;
    }
    datoteka.close();
}
void generisi(std::string filename, int vel){
    std::fstream datoteka;
    datoteka.open(filename,std::ios::out);
    for(int i=0;i<vel;i++){
        int ri=rand()%100+1;
        datoteka<<ri<< " ";
    }
    datoteka.close();
}
template<typename Tip>
void upisiudat(std::string filename, Tip*niz,int vel){
    std::fstream datoteka;
    datoteka.open(filename, std::ios::out);
    for(int i=0;i<vel;i++) datoteka<<niz[i]<<" ";
    datoteka.close();
}
int main() {
    int *niz,vel;
    std::cout<<"Unesite broj elemenata niza (velicina niza koji ce se generisati): ";
    std::cin>>vel;
    generisi("p1.txt",vel);
    ucitaj("p1.txt",niz,vel);
    
    std::cout<<"Generisani niz brojeva(nesoritran): "<<std::endl;
    for(int i=0;i<vel;i++) std::cout<< i+1<<". "<< niz[i]<<std::endl;
    
    int menu;
    std::cout<<"Odaberite jedan od algoritama za  sortiranje niza:\n1.Bubble sort\n2.Selection sort\n3.Quick sort\n4.Merge sort\n";
    std::cin>>menu;
    clock_t vrijeme,vrijeme2;
    if(menu==1){
        vrijeme=clock();
        bubble_sort(niz,vel);
    }
    else if(menu==2){
        vrijeme=clock();
        selection_sort(niz,vel);
    }
    else if(menu==3){
        vrijeme=clock();
        quick_sort(niz,vel);
    }
    else if(menu==4){
        vrijeme=clock();
        merge_sort(niz,vel);
    }
    vrijeme2=clock();
    int ukvrijeme=(vrijeme2-vrijeme)/(CLOCKS_PER_SEC/1000);
    for(int i=0;i<vel-1;i++) if(niz[i]>niz[i+1]){
        std::cout<<"Niz nije uspjesno sortiran";
        break;
    }
    std::cout<<"Niz uspjesno sortiran!\n";
    std::cout<<"Vrijeme sortiranja: "<<ukvrijeme<<" ms\n";
    upisiudat("pz6rezultat.txt",niz,vel);
    std::cout<<"Sortiran niz je upisan u datoteku: pz6rezultat.txt";
    return 0;
}

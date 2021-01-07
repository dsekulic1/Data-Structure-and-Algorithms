#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void radixSort(std::vector<int> &a){
    int maxbr=0;
    for(int i=0;i<a.size();i++){
        if(maxbr<a[i]) maxbr=a[i];
    }
    int bc=0;
    while (maxbr!=0) {
        maxbr/=10;
        bc++;
    }
    
    std::vector<std::vector<int>> m(10);
    for(int i=0;i<bc;i++){
        int s=pow(10,i);
        for(int k=0;k<m.size();k++) m[k].resize(0);
        
        for(int j=0;j<a.size();j++){
            m[(a[j]%(10*s))/(10*s/10)].push_back(a[j]);
        }
        a.clear();
        for(int l=0;l<m.size();l++)
            for(int l1=0;l1<m[l].size();l1++)
                a.push_back(m[l][l1]);
    }
}
bool list(std::vector<int>&a,int i){
    return(i>=a.size()/2 && i<a.size());
}
void stvoriGomilu(std::vector<int>&a){
    for(int i=a.size()/2;i>=0;i--){
        while(!list(a,i)){
        int veci=2*i+1;
        int dd=2*i+2;
        if(dd<a.size()and a[dd]>a[veci]) veci=dd;
        if(a[i]>a[veci]) break;
        swap(a[i],a[veci]);
        i=veci;
        }
    }
}
void pd(std::vector<int>&a,int i, int velicina){
    while(!(i>=velicina/2 && i<velicina)){
        int veci=2*i+1;
        int dd=2*i+2;
        if(dd<velicina and a[dd]>a[veci]) veci=dd;
        if(a[i]>a[veci]) return;
        swap(a[i],a[veci]);
        i=veci;
    }
}
void umetniUGomilu(std::vector<int>&a,int umetnuti,int &velicina){
    if(velicina>a.size()) throw ("Gomila je puna");
    a.push_back(umetnuti);
    velicina++;
    int i=velicina-1;
    while(i!=0 and a[i]>a[(i-1)/2]){
        swap(a[i],a[(i-1)/2]);
        i=(i-1)/2;
    }
}
int izbaciPrvi(std::vector<int>&a, int &velicina){
    if(a.size()==0) throw "ERRRR";
    swap(a[0],a[velicina-1]);
    velicina--;
    if(velicina!=0){
        pd(a,0,velicina);
    }
    return a[velicina];
}
void gomilaSort(std::vector<int>&a){
    stvoriGomilu(a);
    int velicina=a.size();
    for(int i=a.size()-1;i>0;i--){
        swap(a[i],a[0]);
        velicina--;
        pd(a,0,velicina);
    }
}
int main() {
    std::cout << "Zadaća 3, Zadatak 1";
    return 0;
}

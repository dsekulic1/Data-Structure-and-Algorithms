#include <iostream>
int nzd(int x,int y){
    if(y==0) return x;
    else return nzd(y,x%y);
}
int fib2_0(int n,int predzadnji=1, int zadnji=0){
    if(n==1) return predzadnji;
    return fib2_0(n-1,predzadnji+zadnji,predzadnji);
}
int main() {
    std::cout <<nzd(12,13)<<std::endl;
    std::cout<<fib2_0(50)<<std::endl;
    return 0;
}

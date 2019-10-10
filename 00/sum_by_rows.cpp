#include "timer.cpp"
#include <iostream>
using namespace std;

int main()
{
int a[1000][1000]={};
for (int i=0; i<1000; i++){
    for (int j=0; j<1000; j++){
        a[i][j]=i+j;
    }

}
long long int sum=0;
Timer t;
for(int n=0; n<1000; n++){
for (int i=0; i<1000; i++){
    for (int j=0; j<1000; j++){
        sum+=a[i][j];
    }
}
}

cout<<"Time for rows "<<endl;

return 0;

}



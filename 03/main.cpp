#include "matrix.hpp"
#include <cassert>



int main() {
    try {
        const size_t rows = 5;
        const size_t cols = 3;

        Matrix m(rows, cols);

        assert(m.getRows() == 5);
        assert(m.getColumns() == 3);
        for (size_t i=0;i<m.getRows(); i++){
            for (size_t j=0;j<m.getColumns(); j++){
                m[i][j]=i+j;
            }   
        }
        cout<<"m"<<endl <<m <<endl;
        m*=4;
        cout<<"m"<<endl<< m <<endl;
        Matrix m1(m);
        cout<<"m1"<<endl<< m1 <<endl;
        cout <<"m1==m = "<< (m1==m)<<endl;
        m1*=5;
        cout<<"m1"<<endl<<m1<<endl;
        cout<<"m1==m = "<< (m1==m)<<endl;
        cout<<"m1!=m = "<< (m1!=m)<<endl;
        Matrix m2(3, 5);
        cout<<"m2"<<endl<< m2 <<endl;
        cout<<"m2!=m = "<<(m2==m)<<endl;
        //пытаемся получить элемент, которого нет
        cout<< m1[6][6]<<endl;
    } 
    catch (out_of_range& e) {
        cout << e.what()<< endl;
        return 1;

    return 0;
    }
}
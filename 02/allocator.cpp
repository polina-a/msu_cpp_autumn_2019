/*Написать свой аллокатор со стратегией линейного выделения памяти
со следующим интерфейсом: Аллокатор при создании аллоцирует указанный размер, 
после чего при вызове alloc возвращает указатель на блок запрошенного размера или nullptr, 
если места недостаточно. 
После вызова reset аллокатор позволяет использовать свою память снова.*/
#include <cstdlib>
#include <iostream>

 using namespace std;

class LinearAllocator
{
    char* start;
    char* current;
    size_t MaxSize;
    size_t Size;

public:
    LinearAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();    
    size_t maxsize();
    size_t currentsize();
    void alloc_state(); // выодит масимальный размер, текущий размер и память, которая еще доступна для заполнения
    ~LinearAllocator(); 

};

LinearAllocator::LinearAllocator(size_t maxSize){
    MaxSize = maxSize;
    start = (char*) malloc(sizeof(char) * maxSize);
     if (start == nullptr) {
        throw runtime_error("start == nullprt!!!");
    }
    current = start;
    Size = 0;
}

char* LinearAllocator::alloc(size_t size){

        if (start == nullptr) {
        throw runtime_error("start == nullprt!!!");
        return nullptr;
    }

    if (size+Size>MaxSize){ 
    throw runtime_error("requested size is larger than MaxSize"); 
    return nullptr;
    }

    *current +=size;
    Size +=size;
    return current;

}
void LinearAllocator::reset(){
    Size = 0;
    current = start;
}

size_t LinearAllocator::maxsize(){
    return MaxSize;
}

size_t LinearAllocator::currentsize()
{
    return Size;
}


void LinearAllocator::alloc_state(){
    cout<< "MaxSize = "<<MaxSize<<"\t Current Size = "<<Size<<"\t Memory remaing = "<<(MaxSize-Size)<<endl;
}

LinearAllocator::~LinearAllocator(){
   
    free(start);
    MaxSize = 0;
    Size = 0;
}

int main(){
    try{
    LinearAllocator Allocator(15);
    Allocator.alloc_state();
    char* a  = Allocator.alloc(7) ;
    Allocator.alloc_state();
    a = Allocator.alloc(5);
    Allocator.alloc_state();
    for (int i = 0; i<int(Allocator.currentsize());i++)
    {
        *(a+i) = '0'+i;
        cout<<"for i  = "<<i<<" a = "<< *(a+i) << endl; 
    }
    Allocator.reset();
    cout<<endl<<endl<<endl<<"after reset "<<endl;
    Allocator.alloc_state();
    a = Allocator.alloc(3);
    for (int i = 0; i<int(Allocator.currentsize());i++)
    {
        *(a+i) = 'a'+i;
        cout<<"for i  = "<<i<<" a = "<< *(a+i) << endl; 
    }
    Allocator.alloc_state();
    a  = Allocator.alloc(7) ;
    Allocator.alloc_state();
    
    //попытаемся запросить больше памяти, чем осталось 
    a = Allocator.alloc(Allocator.maxsize()-Allocator.currentsize() +1);
    }
    catch(runtime_error& e ){
        cerr<<"ERROR: "<<e.what()<<endl;
        return 1;
    }
    return 0;

}
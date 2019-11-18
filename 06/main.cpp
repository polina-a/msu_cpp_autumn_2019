#include "format.h"
using namespace std;

int main(){
    auto text = format("{1}+{1} = {0}",  "forty", 20);
    cout<<text<<endl;
    assert(text == "20+20 = forty");

    text = format("1:{1}, 2:{0}",  "second string", "first string");
    cout<<text<<endl;
    assert(text == "1:first string, 2:second string");

    text = format("some text");
    cout<<text<<endl;
    assert(text == "some text");

    cout<<endl<<endl<<"Errors tests:"<<endl<<endl;

    try {
        text = format("some{}text");
    } catch (runtime_error& e) {
        cout<<e.what() <<endl;
    }
    try {
        text = format("{0}+{2}-{3} = -2", "seven", "one", "ten");
    } catch (runtime_error& e) {
        cout<< e.what()<<endl;
    }
    
    try {
        text = format("} - {0} +{1} = three", 1, "two");
    } catch (runtime_error& e) {
        cout<< e.what() <<endl;
    }
    try {
        text = format("some {0} text {{", "number", 0);
    } catch (runtime_error& e) {
        cout<< e.what()<<endl;
    }

     try {
        text = format("{0}+{1}-{2}+{3} = -2", "seven", "one", "ten");
    } catch (runtime_error& e) {
        cout<< e.what()<<endl;
    }
     return 0;
}
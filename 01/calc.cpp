
#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>

using namespace std;

//перечисление значений элементов
enum Token {
    Invalid,
    Minus = '-',
    Plus = '+',
    Mul = '*',
    Div = '/',
    Number,
    End
};

//лексема состоит из двух частей: значения, определяющего вид лексемы tok,
//и (если необходимо)  значения лексемы - number_value.
struct Symbol {
    Token tok;
    double number_value;
};


double Calc(const char*& text);
double MulDiv(const char*& text, Symbol& curr_Symbol);
double Init(const char*& text, Symbol& curr_Symbol);
Symbol getToken(const char*& text, Symbol& curr_Symbol);



//обрабатывает сложение и вычитание
double Calc(const char*& text) {
    Symbol curr_Symbol;
    getToken(text, curr_Symbol);
    double left = MulDiv(text, curr_Symbol);
    while (1) {
        switch (curr_Symbol.tok) {
            case Token::Plus:
                getToken(text, curr_Symbol);
                left += MulDiv(text, curr_Symbol);
                break;
            case Token::Minus:
                getToken(text, curr_Symbol);
                left -= MulDiv(text, curr_Symbol);
                break;
            default:
                return left;
        }
    }
    
}

//обрабатывает умножение и деление
double MulDiv(const char*& text, Symbol& curr_Symbol) {
    double left = Init(text, curr_Symbol);
    double d;
    while(1) {
        switch (curr_Symbol.tok) {
            case Token::Mul:
                getToken(text, curr_Symbol);
                
                left *= Init(text, curr_Symbol);
                break;
            case Token::Div:
                getToken(text, curr_Symbol);
                d = Init(text, curr_Symbol);
                if (d == 0) {
                    cerr << "zero division" << endl;
                    exit(1);
                }
                left /= d;
                break;
            default:
                return left;
        }
    }
}

// обрабатывает первичные элементы
double Init(const char*& text, Symbol& curr_Symbol) {
    switch (curr_Symbol.tok) {
        case Token::Number:
            getToken(text, curr_Symbol);
            return curr_Symbol.number_value;
        case Token::Minus: //унарный минус
            getToken(text, curr_Symbol);
            return -Init(text,curr_Symbol);
        case Token::End:
            return 1;
        default:
            cout << "Original needed" << endl;
            exit(1);
            break;
    }
    return 1;
}

//получениt очереного токена 
Symbol getToken(const char*& text, Symbol& curr_Symbol) {
    while (const auto c = *text++) {
        switch (c) {
            case ' ': continue;
            case '-':
            case '+':
            case '*':
            case '/':
                curr_Symbol.tok = Token(c);
                return curr_Symbol;
        }
        if (c >= '0' && c <= '9') {
            string tmp = "";
            tmp += c;
            while (isdigit(*text)) {
                tmp += *text;
                text++;
            }
            curr_Symbol.tok = Token::Number;
            curr_Symbol.number_value = atoi(tmp.c_str());
            return curr_Symbol;
            
        }
        cerr << "Invalid token" << endl;
        exit(1);
        //curr_Symbol.tok = Token::Invalid;
        return curr_Symbol;
    }
    curr_Symbol.tok = Token::End;
    return curr_Symbol;
}


int main(int argc, char* argv[]) {
    
    const char* text; // выражение считанное из командной строки

    
    //проверяем кол-во параметров командной строки
    switch(argc) {
        case 1:
            cerr << "Not enough paramenters" << endl;
            return(1);
            break;
        case 2:
            text = argv[1];
            break;
        default:
            cerr << "To many parameters" << endl;
            return(1);
            break;
    }
    //производим вычисление
    cout << Calc(text);
    
    return 0;
}
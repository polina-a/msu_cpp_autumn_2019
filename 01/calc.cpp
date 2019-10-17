
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
struct symbol {
    Token tok;
    double number_value;
};


double sumsub(char*& text);
double muldiv(char*& text, symbol& curr_symbol);
double init(char*& text, symbol& curr_symbol);
symbol getToken(char*& text, symbol& curr_symbol);



//обрабатывает сложение и вычитание
double sumsub(char*& text) {
    symbol curr_symbol;
    getToken(text, curr_symbol);
    double left = muldiv(text, curr_symbol);
    while (1) {
        switch (curr_symbol.tok) {
            case Token::Plus:
                getToken(text, curr_symbol);
                left += muldiv(text, curr_symbol);
                break;
            case Token::Minus:
                getToken(text, curr_symbol);
                left -= muldiv(text, curr_symbol);
                break;
            default:
                return left;
        }
    }
    
}

//обрабатывает умножение и деление
double muldiv(char*& text, symbol& curr_symbol) {
    double left = init(text, curr_symbol);
    double d;
    while(1) {
        switch (curr_symbol.tok) {
            case Token::Mul:
                getToken(text, curr_symbol);
                
                left *= init(text, curr_symbol);
                break;
            case Token::Div:
                getToken(text, curr_symbol);
                d = init(text, curr_symbol);
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
double init(char*& text, symbol& curr_symbol) {
    switch (curr_symbol.tok) {
        case Token::Number:
            getToken(text, curr_symbol);
            return curr_symbol.number_value;
        case Token::Minus: //унарный минус
            getToken(text, curr_symbol);
            return -init(text,curr_symbol);
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
symbol getToken(char*& text, symbol& curr_symbol) {
    while (const auto c = *text++) {
        switch (c) {
            case ' ': continue;
            case '-':
            case '+':
            case '*':
            case '/':
                curr_symbol.tok = Token(c);
                return curr_symbol;
        }
        if (c >= '0' && c <= '9') {
            string tmp = "";
            tmp += c;
            while (isdigit(*text)) {
                tmp += *text;
                text++;
            }
            curr_symbol.tok = Token::Number;
            curr_symbol.number_value = atoi(tmp.c_str());
            return curr_symbol;
            
        }
        cerr << "Invalid token" << endl;
        exit(1);
        //curr_symbol.tok = Token::Invalid;
        return curr_symbol;
    }
    curr_symbol.tok = Token::End;
    return curr_symbol;
}


int main(int argc, char* argv[]) {
    
    char* text; // выражение считанное из командной строки

    
    //проверяем кол-во параметров командной строки
    switch(argc) {
        case 1:
            cerr << "Not enough paramenters" << endl;
            exit(1);
            break;
        case 2:
            text = argv[1];
            break;
        default:
            cerr << "To many parameters" << endl;
            exit(1);
            break;
    }
    //производим вычисление
    cout << sumsub(text);
    
    return 0;
}

#include "bigint.h"
using namespace std;



BigInt::BigInt(const int n){
	if (n < 0)
		is_neg = true;
	else 
		is_neg = false;
	string s = to_string(n);
	if (is_neg){
		data = new char[s.length() - 1];
		size = s.length() - 1;
		for (int i = 0;i < s.length() - 1;i++)
		data[i] = s[i + 1];
	}
	else{
		data = new char[s.length()];
		size = s.length();
		for (int i = 0;i < s.length();i++)
		data[i]=s[i];
	}
}


BigInt::BigInt(const BigInt& n){
	data=new char[n.size];
	size = n.size;
	is_neg = n.is_neg;
	for (int i = 0;i < n.size;i++)
		data[i] = n.data[i];
}




BigInt& BigInt::operator=(const BigInt& n){
	if (this == &n)
		return *this;
	char* s = new char[n.size];
	delete[] data;
	data = s;
	size = n.size;
	is_neg=n.is_neg;
	copy(n.data, n.data + size, data);
	return *this;
}


BigInt::BigInt(BigInt&& moved){
	data = moved.data;
	size = moved.size;
	is_neg  =  moved.is_neg;
	moved.data = nullptr;
	moved.size = 0;
}

BigInt& BigInt::operator=(BigInt&& moved){
	if (this == &moved)
		return *this;
	delete[] data;
	data= moved.data;
	size = moved.size;
	is_neg = moved.is_neg;
	moved.data = nullptr;
	moved.size = 0;
	return *this;
}




BigInt BigInt::operator-()const{
	BigInt a = *this;
	if (is_neg)
		a.is_neg = false;
	else
		a.is_neg = true;
	return a;
}





BigInt operator+(const BigInt& a,const BigInt& b){
	bool flag = false;
	BigInt result(0);
	char *p, *first, *second;
	int f_s,s_s;
	int c;

	if (a.size > b.size){
		first = a.data;
		second = b.data;
		f_s = a.size;
		s_s = b.size;
	}
	else{
		first = b.data;
		second = a.data;
		f_s = b.size;
		s_s = a.size;
	}
	if (b.is_neg == a.is_neg){
		if (a.size == b.size){
			p=new char[a.size];
			for(int i = a.size - 1;i >= 0;i--){
				c = int(a.data[i] - '0') + int(b.data[i + b.size - a.size] - '0');
				if (flag) c++;
				if (c > 9) {
					flag = true;
					p[i] = char(c - 10 + '0');
					}
				else {
					flag = false;
					p[i] = char(c + int('0'));
					}
			}
		}
		else{
			p = new char[f_s];
			for(int i = f_s - 1;i >= f_s - s_s;i--){
				c = int(first[i] - '0') + int(second[i + s_s - f_s] - '0');
				if (flag) c++;
				if (c > 9) {
					flag = true; 
					p[i] = char(c - 10 + '0');
					}
				else {
					flag = false; 
					p[i] = char(c + int('0'));
					}
			}
			for(int i = f_s - s_s - 1;i >= 0;i--){
				if (flag){
					c = int(first[i] - '0');
					if (flag) c++;
					if (c > 9) {
						flag = true; 
						p[i] = char(c - 10 + '0');
						}
					else {
						flag = false; 
						p[i] = char(c + int('0'));
						}
				}
				else
					p[i] = first[i];
			}
		}
		if (flag) {
			delete[] result.data;
			result.data = new char[f_s + 1];
			result.size = f_s + 1;
			for (int i = 1;i <= f_s;i++) result.data[i] = p[i - 1];
			result.data[0] = '1';
			delete[] p;
		}
		else{
			delete[] result.data;
			result.data = p;
			result.size = f_s;
		}
		result.is_neg = a.is_neg;
		return result;
	}
	if(a == (-b))
		return 0;
	if(!a.is_neg)
		return a - (-b);
	else
		return b - (-a);
}

BigInt operator-(const BigInt& a,const BigInt& b){
	int c;
	bool flag = false;
	BigInt result(0);
	char* p,*first,*second;
	int f_s,s_s,first_sign,second_sign;

	if (((a >= b) && (!a.is_neg)) || ((a <= b) && a.is_neg)){
		first = a.data; 
		second = b.data; 
		f_s = a.size; s_s = b.size; 
		first_sign = b.is_neg; 
		second_sign = a.is_neg;
		}
	else{  
		first = b.data; 
		second = a.data; 
		f_s = b.size; 
		s_s = a.size; 
		first_sign = b.is_neg; 
		second_sign = a.is_neg;
		}

	if (b.is_neg == a.is_neg){
		if (f_s == s_s){
			p = new char[f_s];
			for(int i = f_s-1;i >= 0;i--){
				c = int(first[i] - '0') - int(second[i] - '0');
				if (flag) c--;
				if (c < 0) {
					flag = true;
					p[i] = char(c + 10 + '0');
					}
				else {
					flag = false; 
					p[i] = char(c + int('0'));
					}
			}
		}
		else{
			p = new char[f_s];
			for(int i = f_s - 1;i >= f_s - s_s;i--){
				c=int(first[i] - '0') - int(second[i + s_s - f_s] - '0');
				if (flag) c--;
				if (c < 0) {
					flag = true; 
					p[i] = char(c + 10 + '0');
					}
				else {
					flag = false;
					p[i] = char(c + int('0'));
					}
			}
			for(int i=f_s-s_s-1;i>=0;i--){
				if (flag){
					c=int(first[i]-'0');
					if (flag) c--;
					if (c < 0) {
						flag=true; 
						p[i] = char(c + 10 + '0');
						}
					else {
						flag = false; 
						p[i] = char(c + int('0'));
						}
				}
				else
					p[i] = first[i];
			}
		}

		int k = 0;
		for (k;(k < f_s) && (p[k] == '0');k++);
		if (k > 0){
			result.size = f_s - k;
			if (result.size == 0){
				result.size = 1;
				delete[] result.data;
				result.data = new char[1];
				result.data[0] = '0';
				delete[] p;
			}
			else{
				delete[] result.data;
				result.data = new char[result.size];
				for (int i = k;i < f_s;i++) result.data[i - k] = p[i];
				delete[] p;
			}
		} 
		else{
			delete[] result.data;
			result.data = p;
			result.size = f_s;
		}
		if(!a.is_neg)
			result.is_neg = (a<=b);
		else
			result.is_neg = (a<=b);

		return result;
	}
	if (a == b)
		return 0;
	if (!a.is_neg)
		return a + (-b);
	else
		return b + (-a);

}



bool operator==(const BigInt& a,const BigInt& b){
	if (&b == &a)
		return true;
	if((a.size != b.size) && (a.is_neg != b.is_neg))
		return false;
	for (int i = 0;i < a.size;i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}
bool operator!=(const BigInt& a,const BigInt& b){
	if(a == b)
		return false;
	return true;
}
bool operator>(const BigInt& a,const BigInt& b){
	if (a.is_neg != b.is_neg){
		return !a.is_neg;
	}
	if(a.size > b.size){
		return !a.is_neg;
	}
	if((a.size < b.size)){
		return a.is_neg;
	}
	if (!a.is_neg){
		for (int i = 0;i < a.size;i++)
			if(a.data[i] != b.data[i])
				return (a.data[i] > b.data[i]);
	}
	else{
		for (int i = 0;i < a.size;i++)
			if(a.data[i] != b.data[i])
				return (a.data[i] < b.data[i]);
	}
	return false;
}

bool operator<(const BigInt& a,const BigInt& b){
	return b > a;
}

bool operator>=(const BigInt& a,const BigInt& b){
	return (a > b) || (a == b);
}

bool operator<=(const BigInt& a,const BigInt& b){
	return b >= a;
}


ostream & operator<<(ostream & out, const BigInt & a){
	if (a.is_neg)
		out<<'-';
	for (int i = 0; i < a.size; i++)
		out << a.data[i] ;
	out << endl;
	return out;
}

BigInt::~BigInt(){
	delete[] data;
}
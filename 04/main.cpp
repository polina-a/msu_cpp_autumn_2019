#include "bigint.h"
using namespace std;

int main(){


		BigInt a(123456789);
		BigInt b(987654321);
		BigInt c(a+b);
		BigInt d = b-a;
		cout<<c<<d<<endl;

		assert(c-b ==a);

		assert(d == 864197532);
		assert(-d == -864197532);
		d = b;
		assert(d == b);
		assert(c-c==0);
		assert((c<b)==0);
		assert(c>a ==1);
		assert(b!=d ==0);
		assert(c<=d ==0);
		assert(d>=c==0);
		assert(c==d==0);
		c = -c;
		assert((c<b)==1);
		assert(c>a ==0);
		assert(c<=d ==1);
		assert(d>=c==1);
		assert(c==d==0);
		c = -124;
		assert(c+a == 123456665);
		assert(c-a == -123456913);
		assert(a-c == 123456913);
		assert(a-c+50 == 123456963);
		assert(a-c-50 == 123456863);


		cout<<"All tests successfully completed"<<endl;


}
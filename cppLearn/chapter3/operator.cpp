#include<iostream>
#include<cmath>

using namespace std;
	
/*
重载运算符
1 用户自定义的数据类型可以参与运算 
2 把运算符的调用看成是运算符函数的调用，这样运算符的重载就相当于函数的重载 
*/

/*
规则与限制
1 可以重载除 . .* :: ?: 外的所有运算符
2 只能重载已有的运算符，不能自己定一个符号作为运算符来重载
3 不改变原有的优先级和结合性
4 不改变原有的操作数个数
5 经过重载的运算符至少有一个与原来的操作数类型不一样 
*/ 

/*
重载形式
1 重载为类的成员函数
2 重载为类的友元函数 
*/ 

/*
单目运算符重载
1 不需要参数
2 函数的返回值应该视需要而定
  如果函数返回了一个对象需要作为左值，则返回生成对象的引用
  如果不改变产生的对象则返回对象即可 
*/ 

/*
重载前缀++与后缀++ 
1 前缀++使自身加并返回自身的引用
2 后缀++自身不变返回一个自身++后的临时对象
3 两者都为单目运算符，为了区分前缀与后缀，后缀重载函数中有一个整型参数作为占位符没有实际用处 
4 两者都重载为成员函数 
*/

/*
类型转换运算符
1 类类型向标量类型转换 称为拆箱 unboxing 
2 标量类型向类类型转换 称为装箱 boxing 
3 类类型向类类型转换 

要求限制
1 没有返回值类型，但函数体内部retur一个与运算符同名的实例 
2 函数没有参数，且重载为类的成员函数 
*/

/*
重载赋值运算符
1 =左边的对象必须存在，拷贝构造函数左边的对象不存在
2 实现类类型向类类型的转换
3 没有返回类型，没有参数其他同类型转换运算符 
*/
	
class complex{
private:
	double real;
	double imag;
public:
	complex(double r=0.0, double i=0.0);
	complex(const complex& a);
	friend void print(const complex& c);
	
	//operator 是定义运算符重载函数的关键字 
	complex operator+(const complex& b); 
	complex operator-(const complex& b);
	complex operator*(const complex& b);
	
	//单目运算符 
	complex operator-();
	complex& operator+(){return *this;}
	
	//重载前缀与后缀++
	complex& operator++();
	complex operator++(int i); 
	
	//重载关系运算符,可以为成员函数也可以为友元函数 
	bool operator<(const complex& b); 
	
	//重载<< >>
	ostream& operator<<(const ostream& os);
	istream& operator>>(const istream& is);
	
	//类型转换
	operator double(); 
	
	//重载为友元函数,友元函数不属于任何一个对象所以没有this指针 
	friend complex operator/(const complex& b, const complex& a); 
};

complex::complex(double r, double i):real(r), imag(i){
	std::cout<<"构造函数"<<std::endl;
}
complex::complex(const complex& a):real(a.real), imag(a.imag){
	std::cout<<"拷贝构造函数"<<std::endl;
}
complex complex::operator+(const complex& b){
	std::cout<<"重载+"<<std::endl;
	return complex(real+b.real, imag+b.imag);
}
complex complex::operator-(const complex& b){
	std::cout<<"重载-"<<std::endl;
	return complex(real-b.real, imag-b.imag);
}
complex complex::operator*(const complex& b){
	std::cout<<"重载*"<<std::endl;
	return complex(real*b.real, imag*b.imag);
}
complex complex::operator-(){
	return complex(0-this->real,0-this->imag);
}
complex& complex::operator++(){
	this->real++;
	this->imag++;
	return *this;
}
complex complex::operator++(int i){
	return complex(this->real++, this->imag++);
}
bool complex::operator<(const complex& b){
	double an=((this->real)*(this->real)+(this->imag)*(this->imag));
	double bn=((b.real)*(b.real)+(b.imag)*(b.imag));
	bool flag= an<bn;
	std::cout<<flag<<std::endl;
	return an<bn;
}
ostream& complex::operator<<(const ostream& os){
	os<<"real: "<<this->real<<" imag: "<<this->imag;
	return os;
}
complex::operator double(){
	return sqrt((this->real)*(this->real)+(this->imag)*(this->imag));
}
complex operator/(const complex& a, const complex& b){
	std::cout<<"重载/"<<std::endl;
	return complex(a.real/b.real, a.imag/b.imag);
}
void print(const complex& c){
	std::cout<<"real:"<<c.real<<" imag: "<<c.imag<<std::endl;
}
int main(){
	complex c1(1.0, 1.0);
	complex c2(2.0, 2.0);
	
	print(-c1);
	print(c1+c2);
	//重载为友元函数的运算符仍然是这样使用 
	print(c2/c1);
	c1<c2;
}

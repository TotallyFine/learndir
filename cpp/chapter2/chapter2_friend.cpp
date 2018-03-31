#include<iostream>
using namespace std;

/*
为了在外部频繁访问对象的priavte成员
实现方式：友元 可以访问对象的所有成员，可以为函数可以为类 
一定程度违反了封装原则 
*/ 
class R{
private:
	int a;
	int b;	
public:
	//声明这个函数为友元，但是这个函数不属于这个类 
	friend void friendFun1(const R& r);
	friend void friendFun3(const R& r);
	class C{
		private:
			int c;
		public:
			//在内部类中声明的友元函数只能访问这个内部类的成员
			//不能访问外部类的成员 
			friend void friendFun2(const C& c); 
	}
};

/*
1 友元函数是全局的不属于任何一个类一个对象，因此没有this指针
2 一个类的成员函数也可以声明为其他类的友元 
*/
class D{
private:
	int a;
	int b;
public:
	void friendFun3(const R& r);
	friend class E; 
};

/*
D的友元类 
友元类中的普通函数即可访问D中的成员 
*/
class E{
private:
	int a;
public:
	void friendFun4(const D& d);
}

void friendFun1(const R& r){
	std::cout<<"全局的 R的友元函数"<<std::endl;
}
void friendFun2(const C& c){
	std::cout<<"全局的 R的内部类C的友元函数"<<std::endl; 
}
void D::friendFun3(const R& r){
	std::cout<<"类D中的成员作为R的友元函数"<<std::endl; 
} 
void E::friendFun4(const D& d){
	std::cin<<"类E作为D的友元类，E中普通函数可以访问D中成员"<<std::endl; 
}

/*
友元关系的重要性 
1 某个函数可以是多个类的友元这样可以很高效简洁 
2 提供了不同类之间的对象之间的合作方式 
 
 
 友元关系的特性
 1 非传递性 A为B的友元 B为C的友元 A不为C的友元
 2 非对称性 A为B的友元 B可以不为A的友元 
*/ 

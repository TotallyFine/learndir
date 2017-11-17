#include<iostream>

using namespace std;

/*
多态的实现
1 函数重载 体现为静态的多态，编译时实现 
2 运算符重载 体现为静态的多态 编译时实现 
3 虚函数 体现为动态的多态  运行时实现 
  常采用指针 父类指针指向派生类对象 
*/

/*
注意事项
1 虚函数不能为全局的
2 虚函数不能为静态成员函数
3 不能在声明友元时说明其为虚函数
4 虚函数可以是另一个类的友元 
*/

/*
虚析构函数
1 通过基类指针删除派生类对象
2 基类的析构函数不是虚函数则执行delete的结果是不确定的 
*/

/*
抽象类 
1 抽象类只能作为基类使用
2 不能声明抽象类的对象
3 构造函数不能是虚函数，析构函数可以是虚函数 
*/

class Quadrangle{
public:
	string name;
	Quadrangle(string n):name(n){}
	virtual double area()const{return -1.0;}
	virtual string what()const{return name;}	
};

class Parallelogram:public Quadrangle{
protected:
	int width,height;
public:
	Parallelogram(string n="Parallelogram",int w=5, int h=5)
	:Quadrangle(n),width(w),height(5){}
	double area()const{return width*height;}
};
class Trapezoid : public Quadrangle {   
protected:  
	int edge1, edge2, height;  
public:  
	Trapezoid(string n = "Trapezoid", int e1 = 3, int e2 = 4, int h = 5) 
	: Quadrangle(n),edge1(e1),edge2(e2),height(h){}  
	double area() const { return (edge1 + edge2) * height / 2.0; }
}; 

class Abstract{
public:
	virtual double area()=0;	
};

int main(){
	Quadrangle *pQuad; 
	Parallelogram para;
	                 
	pQuad=&para;                  
	cout << para.what () << ": area = " << pQuad->area () << endl;
	 
	Trapezoid trap;                
	pQuad=&trap;                
	cout << trap.what () << ": area = " << pQuad->area () << endl; 
		
}


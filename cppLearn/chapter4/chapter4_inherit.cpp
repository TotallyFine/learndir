#include<iostream>

using namespace std;

/*
继承的意义
1 实现代码的复用
2 面向对象特点 模拟现实 
*/

/*
继承方式
1 公有继承
2 保护继承
3 私有继承

体现
1 派生类对基类的访问权限
2 通过派生类对基类的访问权限 
*/ 

/*
基类静态成员的派生
1 整个继承树上的所有类共享祖先的静态成员
2 严格遵循静态成员是属于类而不属于对象的思想
3 访问统一为 基类名::静态成员名 
*/

/*
不能被继承的成员
1 构造函数
2 析构函数
3 重载的operator=
4 基类授权的友元函数 
*/ 

/*
基类对象的初始化
1 派生过程中首先继承基类成员再加上自己的成员
2 派生过程中先调用构造函数来构造基类成员
3 如果使用基类的缺省的构造函数或者不带参数的构造函数
  派生类构造函数中初始化列表中可以省去基类的相关初始化 
  但其仍隐式的调用了缺省的构造函数
4 基类声明了带参数的构造函数的时候派生类也应该声明
  带形参的构构造函数，并将参数传递给基类的构造函数 
*/ 

/*
派生类对象对基类赋值
1 派生类对象可以复制给基类对象
2 派生类对象可以初始化基类的引用
3 派生类对象的地址可以复制给指向基类的指针
4 替代后派生类只能发挥基类对象的作用 
*/

/*
名字查找 
1 首先在自己的作用域中查找指定的名字
2 其次在外围基类中查找
3 派生类中的数据成员会屏蔽或者叫隐藏基类中的同名数据成员
4 通过基类的名字限定可以访问 基类::同名成员 
5 成员函数重载的时候即使参数不一样仍然会屏蔽 
*/

class Quadrangle{
public:
	string name;
	static int counter;	
	Quadrangle(string n):name(n){std::cout<<"Quadrangle()"<<std::endl;}
	~Quadrangle(){std::cout<<"~Quadrangle()"<<std::endl;}
};
//必须被初始化，否则有错 
int Quadrangle::counter=0;

class Parallelogram:public Quadrangle{
protected:
	int width,height;
public:
	double area() const{return width+height;}
	Parallelogram(string n="Parallelogram", int w=5, int h=5)
	:Quadrangle(n),width(w),height(h){std::cout<<"Parallelogram()"<<std::endl;}
	~Parallelogram(){std::cout<<"Parallelogram"<<std::endl;}
};

class Rectangle:public Parallelogram{
public:
	/*
	Rectangle(int w,int h):width(w), height(h){} error
	初始化列表不能这样初始化基类对象 
	*/
	Rectangle(int w=5, int h=5):Parallelogram("Rectangle",w,h)
	{std::cout<<"Rectangle()"<<std::endl;}
	~Rectangle(){std::cout<<"~Rectangle()"<<std::endl;}
};

/*
私有继承恢复原有访问控制，不能改变只能恢复 
*/
class Rectangle1:private Parallelogram{
protected:
	Parallelogram::width;
	Parallelogram::height;
public:
	Parallelogram::area;
};


int main(){
	Rectangle r(2,3);
	std::cout<<r.area()<<Rectangle::counter; 
	/*
	std::cout<<r.counter; error 只能通过类名来访问
	Quadrangle::counter 或者 Rectangle::counter 都可以 
	*/
	Parallelogram para("para",5,8);
	Quadrangle& quadRef=para;//合法 但是quadRef只能看到属于Parallelogram的成员 
	
}

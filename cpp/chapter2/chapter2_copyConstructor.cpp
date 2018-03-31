#include<iostream>

using namespace std;

/*
实现两个类之间的复制
1.通过赋值
2.在创建对象的时候通过一个对象产生另一个对象即拷贝构造函数 
*/
class Rectangle{
private :
	int width;
	int height;
	static int counter;
	/*
	实现禁止复制对象,在private段声明拷贝构造函数但不给出定义
	Rectangle(const Rectangle& r); 
	*/ 
public :
	//如此定义拷贝构造函数 
	Rectangle(){Rectangle::counter++;std::cout<<"构造函数 "<<Rectangle::counter<<endl;}
	Rectangle(const Rectangle& r);	
	Rectangle(int width, int height);
	~Rectangle();
};

int Rectangle::counter=0; 

Rectangle::Rectangle(int width, int height):width(width), height(height){
	Rectangle::counter++;
	std::cout<<"构造函数 "<<Rectangle::counter<<endl;
}


//如此定义拷贝构造函数
/*
如果没有定义拷贝构造函数，编译器会自动合成一个，但是对静态成员变量不起作用
且自动合成的是浅复制 ，当有指针的时候只是把指针的地址改了，没有重新开辟堆栈 
只有构造函数和拷贝构造函数可以使用初始化列表 
*/
Rectangle::Rectangle(const Rectangle& r):width(r.width), height(r.height) {
	Rectangle::counter++;
	std::cout<<"拷贝构造函数 "<<Rectangle::counter<<std::endl; 
}	
Rectangle::~Rectangle(){
	Rectangle::counter--;
	std::cout<<"析构函数 "<<Rectangle::counter<<std::endl;
}

/*
在参数传递、返回对象时会调用拷贝构造函数 
*/
Rectangle f(Rectangle r){
	return r;
}

int main(){
	Rectangle r1;
	Rectangle r2(2, 3);
	Rectangle r3=r1;
	Rectangle r4(r2);
	/*
	动态对象通过new关键字来产生，实际还是调用构造函数或者是拷贝构造函数 
	*/
	Rectangle r5=new Rectangle(r1);
	f(r1);
	/*
	当使用隐式拷贝构造函数的时候只实现浅复制
	如果有堆栈指针则释放时会导致多次释放同一块内存，发生问题 
	Rectangle r5=new Rectangle();
	Rectangle r6=r5;
	delete r5;
	delete r6; 
	*/
}

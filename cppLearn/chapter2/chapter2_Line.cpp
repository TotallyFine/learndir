#include<iostream>
using namespace std;

class Circle{
private:
	double xx;
	double yy;
	double radius;
public:
	int const constMenber;
	void showConst() const{
		std::cout<<"常成员为 "<<constMenber<<std::endl; 
	}
	void show(){
		std::cout<<"非常成员为"<<xx<<std::endl;
	}
	Circle(int cm):constMenber(cm){
		this->xx=1;
		this->yy=1;
		this->radius=1;
	}	
}; 

class Line{
private:
	int length;
public:
	//如果将常对象作为数据成员，那么在构造函数中就必须进行初始化 
	Circle const constCircle;
	void setLength(int len);
	int getLength();
	//构造函数不能为虚函数 
	Line(int len,Circle c);
	//析构函数可以为虚函数，不能有参数 ，显示调用无效 
	~Line();		
};

void Line::setLength(int len){
	this->length = len; 
}
int Line::getLength(){
	return this->length;
}
/*
默认参数
在赋值时右边的参数必须也使用了默认参数否则将使用默认参数的放到最右边、初始化列表 
函数原型中可使用默认参数，在定义函数的时候不能写上默认函数 
*/
Line::Line(int len,Circle c):length(len), constCircle(c){
	std::cout<<"构造函数"<<std::endl; 
}
Line::~Line(){
	std::cout<<"析构函数"<<std::endl;
}

/*
函数返回对象时产生临时对象
函数返回指向对象的指针，如果该对象的作用域不再更大的范围的话无法使用
函数返回对象的引用，同样该对象的作用域需要在更大的范围内 
*/
Line objectReturn(Line l){
	return l;
}
Line* pointerReturn(Line* pl){
	return pl;
}
Line& refReturn(Line& rl){
	return rl;
}


int main(){
	Circle c(2);
	Line l(1,c);
	Line& ly = l;
	std::cout<<ly.getLength()<<std::endl;
	ly.constCircle.showConst();
	//ly.constCircle.show(); error 
	return 0;
}

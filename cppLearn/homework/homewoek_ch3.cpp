#include<iostream>

using namespace std;

class Rectangle{
private:
	double length;
	double width;
	
public:
	//构造函数 
	Rectangle(double length, double width);
	//拷贝构造函数 
	Rectangle(const Rectangle& r):length(r.length), width(r.width){}
	
	//传入的const Rectangle 使用时需要其为常成员函数 
	double getLength() const;
	double getWidth() const;
	
	//类成员函数重载各种操作符 
	void operator=(const Rectangle& r);
	double operator+(const Rectangle& r);
	double operator-(const Rectangle& r);
	//重载后缀单目运算符有一个int占位符 返回的是一个副本，前缀返回的是一个本身的引用 
	Rectangle operator++(int);
	Rectangle operator--(int);
	Rectangle& operator++();
	Rectangle& operator--();
	Rectangle& operator+=(const Rectangle& r);
	Rectangle& operator-=(const Rectangle& r);	
	bool operator==(const Rectangle& r);
	bool operator<(const Rectangle& r);
	bool operator>(const Rectangle& r);
	
	//友元函数重载各类操作符
	friend double operator+(const Rectangle& r, const Rectangle& r2);
	friend double operator-(const Rectangle& r, const Rectangle& r2);
	friend Rectangle operator++(Rectangle& r,int);
	friend Rectangle operator--(Rectangle& r,int);
	friend Rectangle& operator++(Rectangle& r);
	friend Rectangle& operator--(Rectangle& r);
	friend Rectangle& operator+=(Rectangle& r, const Rectangle& r2);
	friend Rectangle& operator-=(Rectangle& r, const Rectangle& r2);	
	friend bool operator==(const Rectangle& r, const Rectangle& r2);
	friend bool operator<(const Rectangle& r, const Rectangle& r2);
	friend bool operator>(const Rectangle& r, const Rectangle& r2);
	
	//显示length width 
	void show();
};

Rectangle::Rectangle(double length, double width){
	if(length<=0 || width<=0){
		std::cout<<"边长不合法，将初始化为length：1，width：1"<<std::endl;
	}else{
		this->length=length;
		this->width=width;
	}
}

double Rectangle::getLength() const{
	return this->length;
}

double Rectangle::getWidth() const{
	return this->width;
}
//以下为类成员函数重载操作符的各种实现  
//类成员函数重载= 
void Rectangle::operator=(const Rectangle& r){
	this->length = r.getLength();
	this->width = r.getWidth();
}

//面积相加 类成员函数重载+ 
double Rectangle::operator+(const Rectangle& r){
	return (length*width)+(r.getLength()*r.getWidth());
}

//面积的差 类成员函数重载- 
double Rectangle::operator-(const Rectangle& r){
	return (length*width)-(r.getLength()*r.getWidth());
}
//类成员函数重载后缀++ 
Rectangle Rectangle::operator++(int){
	return Rectangle(this->length++, this->width++);
}
//类成员函数重载后缀-- 
Rectangle Rectangle::operator--(int){
	if(this->length-1<=0 || this->width-1<=0){
		std::cout<<"after reduction the length or width is illeagle"<<std::endl;
		return *this;
	}else return Rectangle(--this->length,--this->width);
}
//类成员函数重载前缀++ 
Rectangle& Rectangle::operator++(){
	this->length++;
	this->width++;
	return *this;
}
//类成员函数重载前缀-- 
Rectangle& Rectangle::operator--(){
	if(this->length-1<=0 || this->width-1<=0){
		std::cout<<"after reduction the length or width is illeagle"<<std::endl;
		return *this;
	}else{
		this->length--;
		this->width--;
		return *this;
	}
}
//类成员函数重载+= 
Rectangle& Rectangle::operator+=(const Rectangle& r){
	this->length+=r.getLength();
	this->width+=r.getWidth();
	return *this;
}
//类成员函数重载-= 
Rectangle& Rectangle::operator-=(const Rectangle& r){
	if(this->length-r.getLength()<=0 || this->width-r.getWidth()<=0){
		std::cout<<"after reduction the length or width is illeagle"<<std::endl;
	}else{
		this->length-=r.getLength();
		this->width-=r.getWidth();
		return *this;
	}
}

//以下都为比较面积 类成员函数重载== 
bool Rectangle::operator==(const Rectangle& r){
	if((this->length*this->width)==(r.getLength()*r.getWidth())) return true;
	else return false;
}
//类成员函数重载< 
bool Rectangle::operator<(const Rectangle& r){
	if((this->length*this->width)<(r.getLength()*r.getWidth())) return true;
	else return false;
}
//类成员函数重载>
bool Rectangle::operator>(const Rectangle& r){
	if((this->length*this->width)>(r.getLength()*r.getWidth())) return true;
	else return false;
}

//以下为友元函数重载操作符的各种实现
//友元函数重载+ 
double operator+(const Rectangle& r1, const Rectangle& r2){
	return (r1.getLength()*r1.getWidth())+(r2.getLength()*r2.getWidth());
}
//友元函数重载- 
double operator-(const Rectangle& r1, const Rectangle& r2){
	return (r1.getLength()*r1.getWidth())-(r2.getLength()*r2.getWidth());
}
//友元函数重载后缀++
Rectangle operator++(Rectangle& r,int){
	Rectangle r1(++r.length, ++r.width);
	return r1;
}
//友元函数重载后缀--
Rectangle operator--(Rectangle& r,int){
	if(r.getLength()-1<=0 || r.getWidth()-1<=0){
		std::cout<<"after reduction the length or width is illeagle"<<std::endl;
		return r;
	}
	Rectangle r1(--r.length, --r.width);
	return r1;
}
//友元函数重载前缀++ 
Rectangle& operator++(Rectangle& r){
	r.length++;
	r.width++;
	return r;
}
//友元函数重载前缀-- 
Rectangle& operator--(Rectangle& r){
	if(r.length-1<=0 || r.width-1<=0){
		std::cout<<"after reduction the length or width is illeagle"<<std::endl;
		return r;
	}else{
		r.length--;
		r.width--;
		return r;
	}
}
//友元函数重载+= 
Rectangle& operator+=(Rectangle& r1, const Rectangle& r2){
	r1.length+=r2.getLength();
	r1.width+=r2.getWidth();
	return r1;
}
//友元函数重载-= 
Rectangle& operator-=(Rectangle& r1, const Rectangle& r2){
	if(r1.length-r2.getLength()<=0 || r1.width-r2.getWidth()<=0){
		std::cout<<"after reduction the length or width is illeagle"<<std::endl;
	}else{
		r1.length-=r2.getLength();
		r1.width-=r2.getWidth();
		return r1;
	}
}
//友元函数重载== 
bool operator==(const Rectangle& r1, const Rectangle& r2){
	if((r1.length*r1.width)==(r2.getLength()*r2.getWidth())) return true;
	else return false;
}
//友元函数重载< 
bool operator<(const Rectangle& r1, const Rectangle& r2){
	if((r1.length*r1.width)<(r2.getLength()*r2.getWidth())) return true;
	else return false;
}
//友元函数重载>
bool operator>(const Rectangle& r1, const Rectangle& r2){
	if((r1.length*r2.width)>(r2.getLength()*r2.getWidth())) return true;
	else return false;
}

void Rectangle::show(){
	std::cout<<"length:"<<this->length<<" width:"<<this->width<<std::endl;
}


int main(){
	
	/*
	拷贝构造函数和重载运算符的区别
	拷贝构造函数是以一个对象为模板生成新的对象
	重载= 是左边的对象已经存在的情况下，把右边的对象复制到左边去 
	*/
	
	Rectangle r1(1,2);
	Rectangle r2(r1);//拷贝构造函数生成新的对象 
	r2.show();
	Rectangle r3(2,3);
	r3.show();
	r3=r2;//重载= 将r2的值复制过去 
	r3.show();
	
	
	std::cout<<r1+r2<<std::endl;
	std::cout<<r1-r2<<std::endl;
	(r1++).show();
	r1.show();
	std::cout<<(r1>r2)<<std::endl;	
}


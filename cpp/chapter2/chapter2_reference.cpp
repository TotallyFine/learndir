//引用和const 
#include <iostream>
using namespace std;
double vals[] = {10.1, 12.6, 33.1, 24.1};

//引用更接近 const 指针，一旦被初始化则不能更改 
//初始化特指在构造函数或者类定义时第一次的赋值
//static类型的成员在类外第一次赋值也叫做初始化

 
//引用作为函数返回值的例子
//函数返回一个引用，实际上是返回一个指向返回值的隐式指针，所以函数就可以作为左值 
double& setValues(int x){
	return vals[x];
} 
void arrayRef(){
	int a[10];
	//对数组进行引用时要注意 
	int(&ra)[10]=a;
} 
//将常指针赋值给非常指针 
//使用const_cast来去除const限定 
void constCast(const char* str){
	char* p=const_cast<char*>(str);
	
} 
int main(){
	/*int i;
	int& ri = i;
	i = 5;
	cout<<"i 的值为"<<i<<endl;
	cout<<"ri 的值为"<<ri<<endl;
	*/
	int i;
	/*
	非常量引用不能指向常量值,常指针不能赋给非常量指针 
	const int j=10;
	int& rj=j; error
	const int& rj=j; right
	*/
	cout<<"改变前的值"<<endl;
	for (i=0;i<4;i++){
		cout<<"vals["<<i<<"]=";
		cout<<vals[i]<<endl;
	} 
	
	setValues(1)=20.23;
	setValues(3)=70.8;
	
	cout<<"改变后的值"<<endl;
	for (i=0;i<4;i++){
		cout<<"vals["<<i<<"]=";
		cout<<vals[i]<<endl;
	} 
} 
/*
const 指针 的各种用法
const int* p --- p是变量但是指向的需要为常量 
int* const p --- p是常量指针，初始化后不能改变 
const int* const p --- p是常量指针， 初始化后不能改变，且指向的必须为常量值 
*/ 

/*
在函数调用的时候编译器无法区分修饰符
void k(int){...}
void k(const int){...}
后者相当于重新定义了k(int)因此不算做重载 
*/ 

/*
常对象
常对象不常见，一般是对象作为返回值的时候创建一个常对象，因此只能作为右值
另一个用处是作为函数的参数，如拷贝构造函数
 
*/


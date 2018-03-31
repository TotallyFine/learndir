//指针

/*
c++中为每个非静态成员函数生成了一个指向对象数据首地址
自动隐藏无法被显示声明，每个对象仅有唯一的this指针
指针类似于const指针
this->data;
const Type* pt=&t; pt->data; 
*/ 

 /*
 静态成员函数没有this指针
 this指针是属于每个对象的，指向每个对象的头地址
 静态成员函数是属于类的，其无法拥有this指针 
 */
 
class X{
 private:
 	int a;
public:
	int b;
	int f();
 };
 
 /*
 指向类成员的指针定义在类的外面
 ptr只能指向public段的成员 
 */
 int X::*ptr;
 int (X::*fptr)(); 
 
 void pointerFun(){
 	X obj;
 	X* pObj=&Obj;
 	//将指针与具体对象绑定 
	ptr=&X::b;
	fptr=&X::f();
	//通过对象或者指针或者引用来使用 
	Obj.*ptr=2;
	++(pObj->*ptr); 
	/*
	Obj.*fptr();是错误的
	这样编译器会认为是Obj.*(fptr());
	这意味着fptr是一个函数并且其返回值是类对象的指针
	并通过Obj使用 
	*/
	(Obj.*fptr)();
	(pObj->a*fptr)();
	 
 } 
 
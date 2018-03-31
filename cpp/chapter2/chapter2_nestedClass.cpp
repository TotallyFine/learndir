#include<iostream>
using namespace std;
/*
嵌套类
如果类 G只为类F提供服务那么G最好成为F的内部类 F是G的包围类 
*/ 
class F{
private:
	int fa;
	class G{
	private:
		int ga;	
	};
public:
	//如果类的定义很长可以放在外面 
	class H;	
};

class F::H{
	private:
		int ha;
	public:
		//内部类同样可以有友元到但是友元不能访问包围类 
		friend void ffun(); 
		void show();
} 

void ffun(){
	std::cout<<"H的全局友元"<<std::endl; 
}

void nestedFun(){
	H h;//error
	F::H h1;//ok
	G g;//error
	F::G g1;//error G定义在private段无法访问 
}

void F::H::show(){
	//error 内部类不能访问包围类的成员 
	std::cout<<fa<<std::endl;
}

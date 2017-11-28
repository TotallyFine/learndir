/*
实现一个日期类，包括增加日期减少日期，考虑闰年的情况。 
*/

#include<iostream>

using namespace std;
	
		
class Date{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	
public :
	Date(int year=2000, int month=1, int day=1, int hour=0, int minute=0, int second=0);
	Date(const Date& d);
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMintue();
	int getSecond();
	bool IsLeap(int year);
	
	void addYear(int add);
	void addMonth(int add);
	void addDay(int add);
	void addHour(int add);
	void addMinute(int add);
	void addSecond(int add);
	
	void reduceYear(int rdu);
	void reduceMonth(int rdu);
	void reduceDay(int rdu);
	void reduceHour(int rdu);
	void reduceMinute(int rdu);
	void reduceSecond(int rdu);
	
	void show();	
};

Date::Date(int year, int month, int day, int hour, int minute, int second){
	
	//检查日期是否合法 
	if(year<0) {std::cout<<"错误的年份，程序将初始化为1970年"<<std::endl; this->year=1970;}
	else {this->year=year;}
	
	if(month<1||month>12) {std::cout<<"错误的月份，程序将初始化为1月"<<std::endl; this->month=1;}
	else {this->month=month;}
	
	//有一种情况，即当年份不合法小于零的时候，将其看为2000 
	if(day<0||day>31){std::cout<<"错误的天数，程序将初始化为1日"<<std::endl; this->day=1;}
	//判断月份 是不是小于31天的 
	else if(this->month==2 || this->month==4 || this->month==9 ||this->month== 11){
		//如果是闰年且是二月且天数不合法 
		if(IsLeap(this->year) && day>29 && month==2){std::cout<<"错误的天数，程序将初始化为1日"<<std::endl; this->day=1;}
		//如果不是闰年且是二月但是天数不合法
	 	else if(!IsLeap(this->year) && day>28 && month==2){std::cout<<"错误的天数，程序将初始化为1日"<<std::endl; this->day=1;}
		//如果不是二月且天数不合法 
		else if(day == 31) {std::cout<<"错误的天数，程序将初始化为1日"<<std::endl; this->day=1;}
	}
	this->day=day;
	
	if(hour<0||hour>23) {std::cout<<"错误的小时，程序将初始化为0时"<<std::endl; this->hour=1;}
	else{this->hour=hour;}
	
	if(minute<0||minute>59){std::cout<<"错误的分钟，程序将初始化为0分"<<std::endl; this->minute=1;}
	else{this->minute=minute;}
	
	if(second<0||second>59){std::cout<<"错误的秒数，程序将初始化为0秒"<<std::endl; this->second=1;}
	else {this->second=second;}	
}

Date::Date(const Date& d):year(d.year), month(d.month), day(d.day), hour(d.hour), minute(d.minute), second(d.second){}

int Date::getYear(){
	return this->year;
}
int Date::getMonth(){
	return this->month;
}
int Date::getDay(){
	return this->day;
}
int Date::getHour(){
	return this->hour;
}
int Date::getMintue(){
	return this->minute;
}
int Date::getSecond(){
	return this->second;
}

//判断是否是闰年 
bool Date::IsLeap(int year){
	if( (year%4==0 && year%100 != 0)  || (year%400 == 0) )
		return true;
	return false;
}

void Date::addYear(int add){
	if(add<0){std::cout<<"年份增加的数目需大于零"<<std::endl;}
	else{this->year+=add;}
}

/*
因为月份和天数是从1开始的所以有 add=this->month+add-13 而不是 减12，小时分钟和秒数没有这样的问题 
*/
void Date::addMonth(int add){
	if(add<0){std::cout<<"月份增加的数目需大于零"<<std::endl;}
	else{
		while(add+month>12){
			add=this->month+add-13;
			this->month=1;
			this->addYear(1);
		}
		this->month+=add;
	}
}

//使用递归的形式 
void Date::addDay(int add){
	if(add<0){return;}
	else{
		//一个月有31天 
		if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
			//增加的日期超过一个月 
			if(day+add>31){this->addMonth(1); this->day=1; this->addDay(add+day-32);}
			//增加的日期没超过一个月 
			else{this->day+=add; return;}
		}else if(month==4||month==6||month==9||month==11){
			//一个月30天
	 		//增加的日期超过一个月 
			if(day+add>30){this->addMonth(1); this->day=1; this->addDay(add+day-31);}
			//增加的日期没超过一个月 
			else{this->day+=add; return;}
		}else if(IsLeap(this->year)){
			//二月是闰年的情况
		 	//增加的日期超过一个月 
			if(day+add>29){this->addMonth(1); this->day=1; this->addDay(add+day-30);}
			//增加的日期没超过一个月 
			else{this->day+=add; return;}
		}else{
			//二月不是闰年
			//增加的日期超过一个月 
			if(day+add>28){this->addMonth(1); this->day=1; this->addDay(add+day-29);}
			//增加的日期没超过一个月 
			else{this->day+=add; return;} 
		}
	}
}

void Date::addHour(int add){
	if(add<0){std::cout<<"小时增加的数目需大于零"<<std::endl;}
	else{
		while(add+hour>=24){
			add=this->hour+add-24;
			this->hour=0;
			this->addDay(1);
		}
		this->hour+=add;
	}
}

void Date::addMinute(int add){
	if(add<0){std::cout<<"分钟增加的数目需大于零"<<std::endl;}
	else{
		while(add+minute>=60){
			add=this->minute+add-60;
			this->minute=0;
			this->addHour(1);
		}
		this->minute+=add;
	}
}

void Date::addSecond(int add){
	if(add<0){std::cout<<"秒数增加的数目需大于零"<<std::endl;}
	else{
		while(add+second>=60){
			add=this->second+add-60;
			this->second=0;
			this->addMinute(1);
		}
		this->second+=add;
	}
}

void Date::reduceYear(int rdu){
	if(this->year-rdu<0){std::cout<<"减少后的年份不合法"<<std::endl;}
	else{this->year-=rdu;}
}

void Date::reduceMonth(int rdu){
	if(rdu<=0){std::cout<<"减少的数目需大于零"<<std::endl;}
	else{
		while(this->month-rdu<=0){
			rdu-=month;
			this->month=12;
			this->reduceYear(1);
		}
		this->month-=rdu;
	}
}

//递归的形式 
void Date::reduceDay(int rdu){
	if(rdu<0){std::cout<<"减少的数目需大于零"<<std::endl; return;}
	else{
		//够减的情况 
		if(day>rdu){this->year-=rdu; return;}
		//不够减的情况
		else{
			//前一个月是31天
			if(month==1||month==2||month==4||month==6||month==8||month==9||month==11){
				rdu-=day;
				this->day=31;
				this->reduceMonth(1);
				this->reduceDay(rdu);
			//前一个月是30天 
			}else if(month==5||month==7){
				rdu-=day;
				this->day=30;
				this->reduceMonth(1);
				this->reduceDay(rdu);
			//前一天是29天 
			}else if(IsLeap(this->year)){
				rdu-=day;
				this->day=29;
				this->reduceMonth(1);
				this->reduceDay(rdu);
			//前一天是28天 
			}else{
				rdu-=day;
				this->day=28;
				this->reduceMonth(1);
				this->reduceDay(rdu);
			}
		} 
	}
}

//因为小时最高是23 分钟最高是59 所以有 rdu-=(hour+1);
void Date::reduceHour(int rdu){
	if(rdu<=0){std::cout<<"减少的数目需大于零"<<std::endl; return;}
	else{
		while(hour-rdu<=0){
			rdu-=(hour+1);
			this->hour=23;
			this->reduceDay(1);
		}
		this->hour-=rdu;
	}
}

void Date::reduceMinute(int rdu){
	if(rdu<=0){std::cout<<"减少的数目需大于零"<<std::endl; return;}
	else{
		while(minute-rdu<=0){
			rdu-=(minute+1);
			this->minute=59;
			this->reduceHour(1);
		}
		this->minute-=rdu;
	}
}

void Date::reduceSecond(int rdu){
	if(rdu<=0){std::cout<<"减少的数目需大于零"<<std::endl; return;}
	else{
		while(second-rdu<=0){
			rdu-=(second+1);
			this->second=59;
			this->reduceMinute(1);
		}
		this->second-=rdu;
	}
}


void Date::show(){
	std::cout<<this->year<<'-' <<this->month<<'-'<<this->day<<' ';
	std::cout<<this->hour<<':'<<this->minute<<':'<<this->second<<std::endl;
}

int main(){
	Date d(2000, 1, 1, 0, 0, 0);
	d.show();
	d.reduceSecond(1);
	d.show();
	d.addSecond(1);
	d.show();
}


#include<iostream>

using namespace std;


/*
在类List类内部建立一个内部类Node，有成员数据 int data，成员数据 Node *next和Node* pre 指针。
List类具有成员变量Node * first和 Node * last，List类具有成员函数插入、删除结点、查找结点；
两个链表的连接、结点数据的排序、两个有序链表的合并成有序链表等成员方法；构造函数、深复制构造函数、析构函数、链表的置空等。
*/
class List{

public:
	class Node{
	public:
		int data;
		Node* next;
		Node* pre;
	};
	Node* first;
	Node* last;	
	
public:
	List();
	//深度复制构造函数 
	List(const List& l);
	~List();
	//链表置空 
	void Clean();

	//将data插入到链表的最后 
	void Insert(int data);
	//删除对应下标的节点 没有找到就返回false，这里的index是从0开始且头结点不计入，即头结点对用户是隐藏的。 
	bool Delete(int index);
	//返回与data匹配的节点的下标，没有找到就返回-1，
	int Search(int data);
	//将两个链表简单的连接 
	void Concat(const List& l);
	//对链表中的数据进行排序 
	void Sort();
	//对有序的链表进行有序合并 
	void Join(const List& l);
	//显示List中的元素
	void Show(); 
	
};

List::List(){
	//这里必须使用new创建头结点，不然函数结束的时候就会释放资源 
	List::Node* n = new List::Node();
	n->next=NULL;
	n->pre=NULL;
	this->first= n;
	this->last= n; 
}

List::List(const List& l){
	/*
	p用于指向已有的链表中的节点
	pN用于指向刚分配的节点 
	pre用于指向pN的前一个节点 
	*/
	List::Node* p= l.first->next;
	List::Node* pN = new List::Node();
	List::Node* pre;
	this->first= pN;
	this->last= pN;
	pN->next=NULL;
	pN->pre=NULL; 
	
	while(p!=NULL){
		pre = pN;
		pN = new List::Node();
	 	pre->next=pN;
	 	pN->pre=pre;
	 	pN->next=NULL;
	 	pN->data=p->data;
	 	p=p->next;
	}
}

List::~List(){
	this->Clean();
	delete this->first; 
}

void List::Clean(){
	/*
	虽然不知道这样写到底是好还是坏， 多次通过指针访问内存是否会很大程度上增大开销？ 
	*/
	while(this->last!=this->first){
		this->last=this->last->pre;
		delete this->last->next;
	}
}

void List::Insert(int data){
	List::Node* p= new List::Node();
	p->data = data;
	p->pre = this->last;
	this->last->next = p;
	this->last = p;
	p->next = NULL;
}

bool List::Delete(int index){
	int count;
	List::Node* p = this->first->next;
	
	//检查下标是否合法 
	if(index<0) return false;
	
	for(count = 0;p!=NULL&&count<=index;p=p->next, count++){
		if(count==index){
			//考虑要删除的是最后一个的情况 
			if(p->next==NULL){
				this->last=p->pre;
				p->pre->next=NULL;
				delete p; 
			}else{
				p->next->pre=p->pre;
				p->pre->next=p->next;
				delete p;
				return true;
			}
		}
	}
	//没有找到下标 
	return false;
}

int List::Search(int data){
	int count;
	List::Node* p = this->first->next;
	
	for(count = 0;p!=NULL;p=p->next, count++){
		if(p->data==data) return count;
	}
	return -1;
}

void List::Concat(const List& l){
	/*
	如果是简单的合并的话，只是连接起来而且const List& l不再被使用，否则会造成混乱
	但是简单的合并就很难受，所以还是写成了深度的合并 
	*/
	
	//这个if语句是为了防止l是空的，最后delete l1->first，导致this->last指向不确定的地方 
	if(l.first==l.last) return;
	
	List* l1 = new List(l);
	this->last->next=l1->first;
	this->last=l1->last;
	delete l1->first; 
}

void List::Sort(){
	List::Node* i=this->first->next;
	List::Node* j;
	
	for(; i!=NULL; i=i->next){
		for(j=i->next; j!=NULL; j=j->next){
			if(i->data > j->data){
				i->data=i->data+j->data;
				j->data=i->data-j->data;
				i->data=i->data-j->data;
			}
		}
	}
	
}

/*
假设两个List已经是有序的然后进行排序 
将const List 插入 this中 
*/
void List::Join(const List& l){
	//指向this中的Node的指针 
	List::Node* i=this->first->next;
	//指向const List中的指针
	List::Node* j=l.first->next;
	
	//特殊情况，可以直接拼接在一起 
	if(this->last->data<=j->data){
		while(j!=NULL){
			List::Node* n1 = new List::Node();
			n1->data=j->data;
	 		n1->pre=this->last;
	 		this->last->next=n1;
			n1->next=NULL;
			this->last=n1; 
			j=j->next;
		} 
		return ;
	}
	
	while(i!=NULL){
		//找到可以插进去的地方，j->data刚刚大于等于i->data
		//当i=NULL的时候 试图使用i->data显然是错误的操作
		//所以需要把i!=NULL写在前面 
		while(i!=NULL&&i->data<j->data) i = i->next;
		if(i!=NULL){
			List::Node* n =new List::Node();
			n->data= j->data;
			n->next=i;
			n->pre=i->pre;
			n->pre->next=n;
			n->next->pre=n; 
			j=j->next;
		}
	}//从这个循环中退出并且全部插完或者没有插完之后 this->last没有变化 
	
	//当this已经到末尾了但是const List仍然没有到末尾 
	//此时j指向的node还未被插入 
	while(j!=NULL){
		List::Node* n1 = new List::Node();
		n1->data=j->data;
	 	n1->pre=this->last;
	 	this->last->next=n1;
		n1->next=NULL;
		this->last=n1; 
		j=j->next;
	}
}

void List::Show(){
	List::Node*p=this->first->next;
	if(this->first==this->last){
		std::cout<<"over"<<std::endl;
		return ;
	}
	while(p!=NULL){
		std::cout<<p->data<<std::endl;
		p=p->next;
	}
	std::cout<<"over"<<std::endl;
}

int main(){
	List l1;
	l1.Insert(1);
	l1.Insert(2);
	l1.Insert(5);
	l1.Insert(3);
	l1.Insert(7);
	l1.Insert(4);
	l1.Sort();
	l1.Show();
} 


#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED

class illegalSize{};
class outOfBound{};

template <class elemType>
class seqStack
{
    private:
    	elemType *array;    //栈存储数组，存放实际的数据元素。
        int Top;            //栈顶下标。
        int maxSize;	    //栈中最多能存放的元素个数。
        void doubleSpace();
    public:
        seqStack(int initSize = 100); //初始化顺序栈
        int isEmpty () { return ( Top == -1 ); } ; //栈为空返回1,否则返回0。
        int isFull () { return (Top == maxSize-1); };//栈满返回1，否则返回0。
        elemType top ();// 返回栈顶元素的值，不改变栈顶
        void push (const elemType &e );//将元素e压入栈顶，使其成为新的栈顶。
        void pop (); //将栈顶元素弹栈。
        void clear() { Top=-1; }; //清除栈中所有元素
        ~seqStack(){ delete []array;}; //释放栈占用的动态数组
};

template <class elemType>
seqStack<elemType>::seqStack(int initSize)//初始化顺序栈
{
	array = new elemType[initSize];
	if (!array) throw illegalSize();
	Top=-1;
    maxSize=initSize;
}

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType *tmp;
    int i;

    tmp = new elemType[maxSize*2];
    if (!tmp) throw illegalSize();

    for(i= 0; i<=Top; i++ ) tmp[i] = array[i]; 	// 逐个复制结点。
    delete []array;
    array = tmp;
    maxSize = 2*maxSize;
}

template <class elemType>
elemType seqStack<elemType>::top ()// 返回栈顶元素的值，不改变栈顶
{
    if (isEmpty()) throw outOfBound();
    return array[Top];
}

template <class elemType>
void seqStack<elemType>::push(const elemType &e )//将元素e压入栈顶，使其成为新的栈顶。
{
     if  (isFull()) doubleSpace();//栈满时从新分配2倍的空间，并将原空间内容拷入
     array[++Top] = e;      	// 新结点放入新的栈顶位置。
}

template <class elemType>
void seqStack<elemType>::pop()//将栈顶元素弹栈。
{
    if (Top==-1) throw outOfBound();
    Top--;
}

#endif //SEQSTACK_H_INCLUDED

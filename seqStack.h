#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED

class illegalSize{};
class outOfBound{};

template <class elemType>
class seqStack
{
    private:
    	elemType *array;    //ջ�洢���飬���ʵ�ʵ�����Ԫ�ء�
        int Top;            //ջ���±ꡣ
        int maxSize;	    //ջ������ܴ�ŵ�Ԫ�ظ�����
        void doubleSpace();
    public:
        seqStack(int initSize = 100); //��ʼ��˳��ջ
        int isEmpty () { return ( Top == -1 ); } ; //ջΪ�շ���1,���򷵻�0��
        int isFull () { return (Top == maxSize-1); };//ջ������1�����򷵻�0��
        elemType top ();// ����ջ��Ԫ�ص�ֵ�����ı�ջ��
        void push (const elemType &e );//��Ԫ��eѹ��ջ����ʹ���Ϊ�µ�ջ����
        void pop (); //��ջ��Ԫ�ص�ջ��
        void clear() { Top=-1; }; //���ջ������Ԫ��
        ~seqStack(){ delete []array;}; //�ͷ�ջռ�õĶ�̬����
};

template <class elemType>
seqStack<elemType>::seqStack(int initSize)//��ʼ��˳��ջ
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

    for(i= 0; i<=Top; i++ ) tmp[i] = array[i]; 	// ������ƽ�㡣
    delete []array;
    array = tmp;
    maxSize = 2*maxSize;
}

template <class elemType>
elemType seqStack<elemType>::top ()// ����ջ��Ԫ�ص�ֵ�����ı�ջ��
{
    if (isEmpty()) throw outOfBound();
    return array[Top];
}

template <class elemType>
void seqStack<elemType>::push(const elemType &e )//��Ԫ��eѹ��ջ����ʹ���Ϊ�µ�ջ����
{
     if  (isFull()) doubleSpace();//ջ��ʱ���·���2���Ŀռ䣬����ԭ�ռ����ݿ���
     array[++Top] = e;      	// �½������µ�ջ��λ�á�
}

template <class elemType>
void seqStack<elemType>::pop()//��ջ��Ԫ�ص�ջ��
{
    if (Top==-1) throw outOfBound();
    Top--;
}

#endif //SEQSTACK_H_INCLUDED

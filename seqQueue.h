#ifndef SEQQUEUE_H_INCLUDED
#define SEQQUEUE_H_INCLUDED

class illegalSize{};
class outOfBound{};

template <class elemType>
class seqQueue
{
    private:
        elemType *array;
        int maxSize;
        int Front, Rear;
        void doubleSpace(); //��չ�Ӷ���Ԫ�صĴ洢�ռ�Ϊԭ����2��
    public:
        seqQueue(int size=10); //��ʼ������Ԫ�صĴ洢�ռ�
        bool isEmpty(); //�ж϶ӿշ񣬿շ���true������Ϊfalse
        bool isFull();  //�ж϶�����������true������Ϊfalse
        elemType front(); //��ȡ����Ԫ�ص�ֵ�����ײ���
        void enQueue(const elemType &x); //��x���ӣ���Ϊ�µĶ�β
        void deQueue(); //������Ԫ�س���
        ~seqQueue(); //�ͷŶ���Ԫ����ռ�ݵĶ�̬����
};

template <class elemType>
seqQueue<elemType>::seqQueue(int size) //��ʼ������Ԫ�صĴ洢�ռ�
{
    array = new elemType[size]; //����ʵ�ʵĶ��д洢�ռ�
    if (!array) throw illegalSize();
    maxSize = size;
    Front = Rear = 0;
}

template <class elemType>
bool seqQueue<elemType>::isEmpty()  //�ж϶ӿշ񣬿շ���true������Ϊfalse
{return Front == Rear;}

template <class elemType>
bool seqQueue<elemType>::isFull() //�ж϶�����������true������Ϊfalse
{return (Rear+1)%maxSize == Front;}

template <class elemType>
elemType seqQueue<elemType>::front() //��ȡ����Ԫ�ص�ֵ�����ײ���
{
    if (isEmpty()) throw outOfBound();
    return array[Front];
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)  //��x���ӣ���Ϊ�µĶ�β
{
    if (isFull())  doubleSpace();
    array[Rear]=x;
    Rear = (Rear+1)%maxSize;
}

template <class elemType>
void seqQueue<elemType>::deQueue() //������Ԫ�س���
{
    if (isEmpty()) throw outOfBound();
    Front = (Front+1)%maxSize;
}

template <class elemType>
seqQueue<elemType>::~seqQueue()  //�ͷŶ���Ԫ����ռ�ݵĶ�̬����
{  delete []array;}

template <class elemType>
void seqQueue<elemType>::doubleSpace() //��չ�Ӷ���Ԫ�صĴ洢�ռ�Ϊԭ����2��
{
    elemType * newArray;
    int i,j;

    newArray = new elemType[2*maxSize];
    if (!newArray) throw illegalSize();

    for (i=0, j=Front; j!=Rear; i++,j=(j+1)%maxSize)
        newArray[i]=array[j];

    delete []array; //�ͷ�ԭ����С�ռ�
    array = newArray;
    Front = 0;
    Rear = j;
    maxSize = 2*maxSize;
}

#endif //SEQQUEUE_H_INCLUDED

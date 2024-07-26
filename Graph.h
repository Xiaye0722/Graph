#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
//#include "seqStack.h"
#include "seqQueue.h"
using namespace std;

#define DefaultNumVertex 20
//class outOfBound{};

template <class edgeType>
struct edgeNode
{
    int dest;
    edgeType weight;
    edgeNode *link;
};

template <class verType, class edgeType>
struct verNode
{
    verType data;
    edgeNode<edgeType> *adj;
};

template <class verType, class edgeType>
class Graph
{
    private:
        bool directed;      //����ͼΪ1������ͼΪ0
        int verts, edges;   //ͼ��ʵ�ʶ�������ʵ�ʱ���
        int maxVertex;      //ͼ���������������
        verNode<verType,edgeType> *verList;   // ���涥�����ݵ�һά����

        void DFS(int start, bool visited[])const;//������ȱ���
    public:
        //��ʼ��ͼ�ṹg��directΪ�Ƿ�����ͼ��־��eΪ�ޱ�����
        Graph(bool direct);
        ~Graph();

        int numberOfVertex()const{ return verts; }; // ����ͼ��ǰ������
        int numberOfEdge()const{ return edges; }; // ����ͼ��ǰ����
        //���ض���Ϊvertexֵ��Ԫ���ڶ�����е��±�
        int getVertex(verType vertex)const;
        bool existEdge(verType vertex1,verType vertex2)const; //�ж�ĳ����������Ƿ��б�
        void insertVertex(verType vertex ); //���붥��
        void insertEdge(verType vertex1, verType vertex2, edgeType edge); //�����
        void removeVertex(verType vertex);  //ɾ������
        void removeEdge(verType vertex1, verType vertex2); //ɾ����
        //���ض���vertex�ĵ�һ���ڽӵ�,������ڽӵ㷵��-1
        int getFirstNeighbor(verType vertex ) const;
        //���ض���vertex1�����vertex2����һ���ڽӵ㣬�������һ���ڽӵ㷵��-1
        int getNextNeighbor(verType vertex1, verType vertex2)const;
        void disp()const; //��ʾ�ڽӾ����ֵ
        //void DFS(verType start)const;//������ȱ���
        void DFS()const;//������ȱ���
        void BFS()const;//������ȱ���
        void Prim()const;
        void Kruscal()const;
};

//-----------------------------����ʵ��-----------------------------
//��ʼ��ͼ�ṹg��directΪ�Ƿ�����ͼ��־
template <class verType, class edgeType>
Graph<verType, edgeType>::Graph(bool direct)
{
    //��ʼ������
    directed = direct;
    verts = 0;
    edges = 0;
    maxVertex = DefaultNumVertex;

    //Ϊ�涥���һά���鴴���ռ�
    verList = new verNode<verType,edgeType> [maxVertex];
}

template <class verType, class edgeType>
Graph<verType, edgeType>::~Graph()
{
    int i;
    edgeNode<edgeType> *p;

    for (i=0; i<verts; i++) //�ͷ����б߱��еĽ��
    {
        while (verList[i].adj)
        {
            p = verList[i].adj;
            verList[i].adj = p->link;
            delete p;
        }
    }

    delete []verList;
}

//���ض���Ϊvertexֵ��Ԫ���ڶ�����е��±�
template <class verType, class edgeType>
int Graph<verType, edgeType>::getVertex(verType vertex) const
{
    int i;
    for (i=0; i<verts; i++)
        if (verList[i].data==vertex)
            return i;
    return -1;
}

//�ж�ĳ���������Ƿ��б�
template <class verType, class edgeType>
bool Graph<verType, edgeType>::existEdge(verType vertex1,verType vertex2)const
{
    int i, j;
    edgeNode<edgeType> *p;

    //�ҵ�vertex1��vertex2���±�
    for (i=0; i<verts; i++)
        if (verList[i].data==vertex1)
            break;
    for (j=0; j<verts; j++)
        if (verList[j].data==vertex2)
            break;

    //�޴˶���
    if (i==verts && j==verts) return false;
    p = verList[i].adj;
    while (p)
    {
        if (p->dest==j) return true;
        p = p->link;
    }
    return false;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::insertVertex (verType vertex ) //���붥��
{
    if (verts == maxVertex ) throw outOfBound();
    verts++;
    verList[verts-1].data = vertex;
    verList[verts-1].adj = NULL;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::insertEdge(verType vertex1, verType vertex2, edgeType edge) //�����
{
    int i, j;
    edgeNode<edgeType> *tmp;

    //�ҵ�vertex1��vertex2���±�
    for (i=0; i<verts; i++)
        if (verList[i].data==vertex1)
            break;
    for (j=0; j<verts; j++)
        if (verList[j].data==vertex2)
            break;

    //�޴˶���
    if ((i==verts)||(j==verts))
        return;

    //��i�±������ĵ������в���һ���߽��
    tmp = new edgeNode<edgeType>;
    tmp->dest = j;
    tmp->weight = edge;
    tmp->link = verList[i].adj;
    verList[i].adj = tmp;

    edges++;

    if (!directed) //���������ͼ�������й������Խ��ߵĶԳƵ�ҲҪ����
    {
        tmp = new edgeNode<edgeType>;
        tmp->dest = i;
        tmp->weight = edge;
        tmp->link = verList[j].adj;
        verList[j].adj = tmp;
    }
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::removeEdge (verType vertex1, verType vertex2)//ɾ����
{
    int i, j;
    edgeNode<edgeType> *p, *q;

    for (i=0; i<verts; i++)
        if (verList[i].data==vertex1)
            break;
    for (j=0; j<verts; j++)
        if (verList[j].data==vertex2)
            break;
    if ((i==verts)||(j==verts)) return;

    p = verList[i].adj;
    q = NULL;
    while (p)
    {   if (p->dest==j) break;
        q = p;
        p = p->link;
    }
    if (!p) return;
    if (!q)//ɾ���׽��
       verList[i].adj = p->link;
    else
        q->link = p->link;
    delete p;
    edges--;

    if (directed) return;
    //����ͼ��Ҫɾ���±�j�����ĵ������е�һ��dest=i�Ľ��
    p = verList[j].adj;
    q = NULL;
    while (p)
    {   if (p->dest==i) break;
        q = p;
        p = p->link;
    }
    if (!p) return;
    if (!q)//ɾ���׽��
       verList[j].adj = p->link;
    else
        q->link = p->link;
    delete p;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::removeVertex(verType vertex)  //ɾ������
{
    int i, j;
    int count=0;
    edgeNode<edgeType> *p, *q;

    //�ҵ��ö����ڶ�����е��±�
    for (i=0; i<verts; i++)
        if (verList[i].data==vertex)
            break;

    if (i==verts) return; //�ö��㲻�ڶ������

    //ɾ���±�Ϊi�Ķ��������ĵ����������н�㲢����ɾ���ı�
    p = verList[i].adj;
    while (p)
    {
        count++;
        verList[i].adj = p->link;
        delete p;
        p = verList[i].adj;
    }
    cout<<"count= "<<count<<endl;

    //������е���������dest��i�Ķ�ɾ��
    for (j=0; j<verts; j++)
    {
        p = verList[j].adj; q = NULL;
        while (p)
        {
            if (p->dest == i) break;
            q = p;
            p = p->link;
        }
        if (!p) continue;
        if (!q)
            verList[j].adj = p->link;
        else
            q->link = p->link;
        delete p;
        count++;
    }

    //������е���������dest>i�Ķ�ɾ��һ
    for (j=0; j<verts; j++)
    {
        p = verList[j].adj;
        while (p)
        {
            if (p->dest > i)
                p->dest--;
            p = p->link;
        }
    }

    if (directed)
        edges-=count;
    else
        edges-=count/2; //����ͼ������count��һ��

    //�ڶ������ɾ������
    for (j=i; j<verts-1; j++)
        verList[j] = verList[j+1];
    verts--;
}

//���ض���vertex�ĵ�һ���ڽӵ㣬������ڽӵ㷵��-1
template <class verType, class edgeType>
int Graph<verType, edgeType>::getFirstNeighbor(verType vertex )const
{
    int i, j;
    edgeNode<edgeType> *p;

    for (i=0; i<verts; i++)
        if (verList[i].data==vertex)
            break;
    if (i==verts) return -1;

    p = verList[i].adj;
    if (!p) return -1;
    return p->dest;
}

//���ض���vertex1�����vertex2����һ���ڽӵ㣬�������һ���ڽӵ㷵��-1
template <class verType, class edgeType>
int Graph<verType, edgeType>::getNextNeighbor(verType vertex1, verType vertex2)const
{
    int i,j,k;
    edgeNode<edgeType> *p;

    for (i=0; i<verts; i++)
        if (verList[i]==vertex1)
            break;
    for (j=0; j<verts; j++)
        if (verList[j]==vertex2)
            break;
    if ((i==verts)||(j==verts)) return -1;

    p = verList[i].adj;
    while (p)
    {
        if (p->dest==j) break;
        p = p->link;
    }
    if (!p ||!p->link) return -1;
    return p->link->dest;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::disp() const//��ʾ�ڽӾ����ֵ
{
    int i;
    edgeNode<edgeType> *p;


    for (i=0; i<verts; i++)
    {
        p = verList[i].adj;
        cout << verList[i].data <<": ";
        while (p)
        {
            cout<<p->dest<<", "<<"("<<p->weight<<") ";
            p = p->link;
        }
        cout<<endl;
    }
}

/*
//DFS�ǵݹ��㷨ʵ��
template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS()const
{
	seqStack<int> s;
	edgeNode<edgeType> *p;
	bool *visited;
    int i, start;

    //Ϊvisited������̬����ռ䣬���ó�ʼ���ʱ�־Ϊfalse��
    visited = new bool[verts];
    if (!visited) throw illegalSize();
    for (i=0; i<verts; i++) visited[i]=false;

    //��һ�ҵ�δ�����ʹ����㣬��������ȱ���
	for (i=0; i<verts; i++)
	{
	    if (visited[i]) continue;
	    s.push(i);

	    while (!s.isEmpty())
	    {
	        start = s.top(); s.pop();
	        if (visited[start]) continue;

	        cout<<verList[start].data<<'\t';
	        visited[start] = true;

	        p = verList[start].adj;
	        while (p)
	        {
	            if (!visited[p->dest])
                    s.push(p->dest);
                p = p->link;
	        }
        }
        cout<<'\n';
    }
}

//DFS�ݹ��㷨
template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS()const
{
	bool *visited;
	int i;

	//Ϊvisited������̬����ռ䣬���ó�ʼ���ʱ�־Ϊfalse��
    visited = new bool[verts];
    if (!visited) throw illegalSize();
    for (i=0; i<verts; i++) visited[i]=false;

    for (i=0; i<verts; i++)
    {
        if (!visited[i]) DFS(i, visited);
        cout<<endl;
    }
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS(int start, bool visited[])const
{
    edgeNode<edgeType> *p;

    cout<<verList[start].data<<'\t';
    visited[start] = true;

    p = verList[start].adj;
    while (p)
    {
        if (!visited[p->dest]) DFS(p->dest, visited);
        p = p->link;
    }
}
*/

template <class verType, class edgeType>
void Graph<verType, edgeType>::BFS()const//������ȱ���
{
	seqQueue<int> q;
	edgeNode<edgeType> *p;
	bool *visited;
	int i, start;

    //Ϊvisited������̬����ռ䣬���ó�ʼ���ʱ�־Ϊfalse��
    visited = new bool[verts];
    if (!visited) throw illegalSize();
    for (i=0; i<verts; i++) visited[i]=false;

    //��һ�ҵ�δ�����ʹ����㣬��������ȱ���
	for (i=0; i<verts; i++)
	{
	    if (visited[i]) continue;
	    q.enQueue(i);

	    while (!q.isEmpty())
	    {
	        start = q.front(); q.deQueue();
	        if (visited[start]) continue;

	        cout<<verList[start].data<<'\t';
	        visited[start] = true;

	        p = verList[start].adj;
	        while (p)
	        {
	            if (!visited[p->dest])
                    q.enQueue(p->dest);
                p = p->link;
	        }
	    }
	    cout<<'\n';
	}
}

/*
//prim�㷨
template <class edgeType>
struct primNode
{
    int from; //�ߵ�һ���ڽӵ�
    int to;   //�ߵ�����һ���ڽӵ�
    edgeType weight; //�ߵ�Ȩֵ
};

template <class verType, class edgeType>
void Graph<verType, edgeType>::Prim()const
{
    int *source;  //��¼Դ����
    edgeType *dist; //��¼���㵽U�����еľ���
    bool *selected; //��¼�����Ƿ��Ѿ���U��
    primNode<edgeType> *treeEdges; //��С�������еı�

    edgeType sum; //��С��������Ȩֵ��
    int cnt; //��¼����U�ж���ĸ���
    int min; //ѡ����ǰW���뼯��U��̵Ķ����±�
    int i, j, selVert;

    edgeNode<edgeType> *p;


    //������̬�ռ�
    source = new int[verts];
    dist   = new edgeType[verts];
    selected = new bool[verts];
    treeEdges = new primNode<edgeType>[verts-1];

    //��ʼ��
    for (i=0; i<verts; i++)
    {
        source[i]=-1;
        dist[i]= 9999; //��һ���ܴ��ֵ��ʾ�����
        selected[i] = false;
    }

    //ѡ��һ������
    selVert = 0;
    source[0]=0;
    dist[0] = 0;
    selected[0]=true;
    cnt=1;

    while (cnt<verts)
    {
        //���selVert����������W�е��ڽӵ㣬������Ҫ����������Ϣ
        p = verList[selVert].adj;
        while (p)
        {
            if (!selected[p->dest]&&(dist[p->dest]>p->weight))
            {
                source[p->dest] = selVert;
                dist[p->dest]   = p->weight;
            }
            p = p->link;
        }

        //ѡ��W����U����Ķ��㣬��dist��С��ֵ
        for (i=0; i<verts; i++)
            if (!selected[i]) break;
        min = i;

        for (j=i+1; j<verts; j++)
            if (!selected[j] && dist[j]<dist[min]) min = j;

        //������Ķ��㲢��U,������Ӧ�ı߲�����С������
        selVert = min;
        selected[min] = true;
        treeEdges[cnt-1].from = source[min];
        treeEdges[cnt-1].to = min;
        treeEdges[cnt-1].weight = dist[min];
        cnt++;
    }

    //-------------��������-----------------
    //�����С�������и����߼�Ȩֵ��
    sum = 0;
    for (i=0; i<cnt-1; i++)
    {
        sum += treeEdges[i].weight;
        cout<<treeEdges[i].from<<" ->  "<<treeEdges[i].to<<"  "<<treeEdges[i].weight<<endl;
    }
    cout<<"The total weight is: "<<sum<<endl;
}
*/

#endif //GRAPH_H_INCLUDED

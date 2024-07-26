#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    int i, vCount, eCount;
    char v1, v2;
    int value;

    //Graph<char, int> g(true,0);
    Graph<char,int> g(false);

    cout<<"Input the number of verts and edges: ";
    cin >> vCount >> eCount;
    cin.get();

    for (i=0; i<vCount; i++) //插入所有顶点
        g.insertVertex('A'+i);

    cout<<"Input the edge, for example: AB 5 "<<endl;
    for (i=0; i<eCount; i++) //插入所有边,以回车分割各条边
    {
        v1 = cin.get();
        v2 = cin.get();
        cin >> value;
        cin.get();//读入回车

        g.insertEdge(v1,v2,value); //插入边

    }

    g.disp();
    //cout<<"-----------------------"<<endl;
    //g.DFS();
    g.BFS();
    //g.Prim();
    //g.Dijkstra('E');
    //g.Floyd();
    //g.topoSort();
    //g.keyActivity('C','H');

/*
    cout<<"The numbers of verts and edges are: ";
    cout<<g.numberOfVertex()<<", "<<g.numberOfEdge()<<endl;

    cout<<"The index of C is: "<<g.getVertex('C')<<endl;
    if (g.existEdge('A','C'))
        cout<<"From A to C: no edge!"<<endl;
    else
        cout<<"From A to C: has an edge!"<<endl;

    g.insertVertex('E');
    cout<<"After insert the vertex E, The numbers of verts and edges are:  ";
    cout<<g.numberOfVertex()<<", "<<g.numberOfEdge()<<endl;

    g.insertEdge('E','C',1);
    cout<<"After insert the edge EC, The numbers of verts and edges are:  ";
    cout<<g.numberOfVertex()<<", "<<g.numberOfEdge()<<endl;

    g.disp();

    g.removeEdge('A','B');
    cout<<"After remove the edge AB, The numbers of verts and edges are:  ";
    cout<<g.numberOfVertex()<<", "<<g.numberOfEdge()<<endl;
    g.disp();

    g.removeVertex('A');
    cout<<"After remove the vertex A, The numbers of verts and edges are:  ";
    cout<<g.numberOfVertex()<<", "<<g.numberOfEdge()<<endl;
    g.disp();
*/
    return 0;
}

//input AB AD BC CA DC

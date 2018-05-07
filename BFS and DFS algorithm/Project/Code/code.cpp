/*Analysis and Algorithms
 Homework 1
 Harun Çatal
 150130034
 */
#include<iostream>
#include <list>
#include <ctime>// to calculate execution time
using namespace std;
class node{//to define stages
public:
    void initiateStages();//to initiate stages for graph
    int id;//to keep stage name
    int i1,i2,i3,i4;//to keep indexes
    void print(int);//to print stages with id asinteger
    node(){};//consturctors
    node(int a,int b ,int c,int d,int e)
    {
        id=a;
        i1=b;
        i2=c;
        i3=d;
        i4=e;
    }
    void operator = (node s ) {//assigment operand overloading
        id=s.id;
        i1=s.i1;
        i2=s.i2;
        i3=s.i3;
        i4=s.i4;
    }
};
node states[15];//to keep states in an array
void node:: initiateStages()//first define as a node then initialize to an array
{
    node s0(0,1,1,1,1);
    node s1(1,0,1,1,1);
    node s2(2,0,0,1,1);
    node s3(3,0,1,0,1);
    node s4(4,0,1,1,0);
    node s5(5,1,0,1,1);
    node s6(6,1,1,0,1);
    node s7(7,1,1,1,0);
    node s8(8,0,0,0,1);
    node s9(9,0,1,0,0);
    node s10(10,0,0,1,0);
    node s11(11,1,0,0,1);
    node s12(12,1,1,0,0);
    node s13(13,1,0,1,0);
    node s14(14,0,0,0,0);
    node s15(15,1,0,0,0);
    
    states[0]=s0;
    states[1]=s1;
    states[2]=s2;
    states[3]=s3;
    states[4]=s4;
    states[5]=s5;
    states[6]=s6;
    states[7]=s7;
    states[8]=s8;
    states[9]=s9;
    states[10]=s10;
    states[11]=s11;
    states[12]=s12;
    states[13]=s13;
    states[14]=s14;
}
int visitedNodeNumber=0;//to keep visited node number
unsigned long maxNodeInMemory=0;//to keep max node in memory
unsigned long solNumberBFS=0;
unsigned long solNumberDFS=0;
list<int> way;//to keep true way
list<int> wayTemp; // temp list for keep path
int arr[15][15];//an array to keep edges with 1 and 0
void fillArr(){//filling array with 0's
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
            arr[i][j]=0;
    }
}
class Graph
{
public:
    int N;//number of nodes
    list<int> *adjacency;//adjacency list
    void DFSUtil(int N, bool visited[]);
    Graph(int V)
    {
        this->N = V;
        adjacency = new list<int>[V];
    }
    void BFS(int);//bfs function
    void DFS(int);//dfs function
    void addEdge(int v, int w)//function to add edge
    {
        adjacency[v].push_back(w); // Add w to v’s list.
        adjacency[w].push_back(v); // Add w to v’s list.
        arr[v][w]=1;
        arr[w][v]=1;
    }
};
void Graph::BFS(int a)
{
    
    bool *visited = new bool[N];//All point is not visited firstly
    for(int i = 0; i < N; i++)
        visited[i] = false;
    visited[1]=true;// then dead stages 1 2 4 12 and 13 are should be visited
    visited[2]=true;
    visited[4]=true;
    visited[11]=true;
    visited[12]=true;
    list<int> queue; //queue for bfs
    
    
    visited[a] = true;//if visited -> true
    queue.push_back(a); //push in queue
    maxNodeInMemory=queue.size(); //update max node
    
    list<int>::iterator i;//iterator enable traversing
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        a= queue.front();//dequeue from begining and keep it in another temporary list
        wayTemp.push_back(a);
        unsigned long temp=queue.size();
        if(temp>maxNodeInMemory)
            maxNodeInMemory=temp;//update max node in memory
        queue.pop_front();
        
        for (i = adjacency[a].begin(); i != adjacency[a].end(); ++i)//getting all adjacent nodes and make visited and enqueue
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    
    for (int m=0; m<N; m++) {//calculate visited node number
        if(visited[m]==true)
            visitedNodeNumber++;
    }
    //calculating true way from queue
    // starting from end of the queue to begin and control nodes with previous node is it an edge or not keep them in another list(way)
    solNumberBFS=wayTemp.size();//size of wayTemp is equal to number of step for solution
    int keep;
    keep=wayTemp.back();
    while(!wayTemp.empty())//Take solution array. Starting from last to begin. Control with before elements is there an edge or not. If there is an edge it is our true path.
    {
        if(arr[wayTemp.back()][keep]==1)
        {
            way.push_front(keep);
            keep=wayTemp.back();
        }
        else
            wayTemp.pop_back();
    }
    
    
    
}
int c=0;
void node::print(int n)
{
    if(c==0)
    {
        cout<<"Farmer Rabbit Carrot Fox ||"<<endl;//stage 0
        c++;
    }
    
    if(states[n].i1==1)
        cout<<" Farmer ";
    if(states[n].i2==1)
        cout<<" Carrot ";
    if(states[n].i3==1)
        cout<<" Rabbit ";
    if(states[n].i4==1)
        cout<<" Fox ";
    cout<<"|| ";
    if(states[n].i1==0)
        cout<<" Farmer ";
    if(states[n].i2==0)
        cout<<" Carrot ";
    if(states[n].i3==0)
        cout<<" Rabbit ";
    if(states[n].i4==0)
        cout<<" Fox ";
    cout<<endl;
}

void Graph::DFS(int v)
{
    bool *visited = new bool[N];//All nodes unvisited
    for (int i = 0; i < N; i++)
        visited[i] = false;
    visited[1]=true;//dead stages visited
    visited[2]=true;
    visited[4]=true;
    visited[11]=true;
    visited[12]=true;
    list<int> stack; //queue for bfs
    visited[v] = true;//if visited -> true
    stack.push_front(v); //push in queue
    maxNodeInMemory=stack.size(); //update max node
    list<int>::iterator j;//iterator enable traversing
    while(!stack.empty())
    {
        // Dequeue a vertex from queue and print it
        v= stack.front();//dequeue from begining and keep it in another temporary list
        wayTemp.push_back(v);
        unsigned long temp=stack.size();
        if(temp>maxNodeInMemory)
            maxNodeInMemory=temp;//update max node in memory
        stack.pop_back();
        
        for (j = adjacency[v].begin(); j!= adjacency[v].end(); ++j)//getting all adjacent nodes and make visited and enqueue
        {
            if (!visited[*j])
            {
                visited[*j] = true;
                stack.push_front(*j);
            }
        }
    }
    for (int m=0; m<N; m++) {//calculate visited node number
        if(visited[m]==true)
            visitedNodeNumber++;
    }
    solNumberDFS=wayTemp.size();//size of wayTemp is equal to number of step for solution
    //calculating true way from queue
    // starting from end of the queue to begin and control nodes with previous node is it an edge or not keep them in another list(way)
    solNumberBFS=wayTemp.size();//size of wayTemp is equal to number of step for solution
    int keep;
    keep=wayTemp.back();
    while(!wayTemp.empty())
    {
        if(arr[wayTemp.back()][keep]==1)
        {
            way.push_front(keep);
            keep=wayTemp.back();
        }
        else
            wayTemp.pop_back();
    }
    
}
void printSteps()
{
    node n;
    n.initiateStages();//initiate stages
    while(!way.empty())
    {
        n.print(way.front());//print with stage number
        way.pop_front();
    }
}
int main(int argc,char *argv[])
{
    Graph g(16);//our graph consist of 16 nodes
    g.addEdge(0,1);//initial edge for graph
    g.addEdge(0,2 );
    g.addEdge(0,3 );
    g.addEdge(0, 4);
    g.addEdge(2,5);
    g.addEdge(3,6 );
    g.addEdge(4,7);
    g.addEdge(5, 8);
    g.addEdge(5,10);
    g.addEdge(6,8 );
    g.addEdge(6,9 );
    g.addEdge(7, 9);
    g.addEdge(7, 10);
    g.addEdge(8,11);
    g.addEdge(9,12 );
    g.addEdge(10,13 );
    g.addEdge(11, 14);
    g.addEdge(12,14);
    g.addEdge(13,14 );
    if(argc!=2)//more than one operation
        cout<<"Please enter just 1 operation name"<<endl;
    else if(argc==2)//1 operation
    {
        string operation=argv[1];
        
        if(operation=="bfs")
        {
            unsigned long start_s=clock();
            g.BFS(0);
            unsigned long stop_s=clock();
            cout<<"Algorithm : BFS"<<endl;
            cout<<"Number of visited nodes : "<<visitedNodeNumber<<endl;
            cout<<"Maximum number kept in memory "<<maxNodeInMemory<<endl;
            cout <<"Running time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 <<"second"<< endl;
            cout<<"Solution move count : "<<solNumberBFS<<endl;
            printSteps();
        }
        else if(operation=="dfs")
        {
            unsigned long start_s=clock();
            g.DFS(0);
            unsigned long stop_s=clock();
            cout<<"Algorithm : DFS"<<endl;
            cout<<"Number of visited nodes : "<<visitedNodeNumber<<endl;
            cout<<"Maximum number kept in memory "<<maxNodeInMemory<<endl;
            cout <<"Running time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 <<"second"<< endl;
            cout<<"Solution move count : "<<solNumberDFS<<endl;
            printSteps();
        }
        else
            cout<<"Invalid operation name"<<endl;
    }
    return 0;
    
}


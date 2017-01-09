
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stack>
#define INFINITY 9999


using namespace std;



struct info
{
    string ip;
    int num;
};

class router
{
private:
    int table[20][20];
    int size;//the number of roots(it changes with the using of function delet and add)
    info router_info[20];//the information of routers
public:
    router();
    void deleteVertex(router &G);
    void deleteEdge(router &G);
    void addVertex(router &G);
    void addEdge(router &G);
    void calculate(router &G);
    void createVertices();
    void createEdges();
    void createGraph();
    void save();
    int getVertexPos(int v)
    {
        for(int i=0; i<size; i++)
            if(router_info[i].num==v)return i;
        return -1;
    }
};

void menu(router &G);

router::router()
{
    int i,j;
    for(i=0; i<20; i++)
        for(j=0; j<20; j++)
        {
            if(i==j)table[i][j]=0;
            else table[i][j]=INFINITY;
        }
    for(i=0; i<20; i++)
        router_info[i].num=0;
    size=0;
}

void router::calculate(router &G)
{
    int s;
    int v0=0;
    cout<<"\t\t-->Here is the information of all routers:"<<endl;
    cout<<"\t\t-------------------------------------------"<<endl;
    for(int i=0;i<size;++i)
    {
        cout<<"\t\t   router_number : "<<router_info[i].num<<endl;
        cout<<"\t\t   IP_address    : "<<router_info[i].ip<<endl;
        cout<<"\t\t-------------------------------------------"<<endl;
    }
    cout<<"\t\t-->Please enter the number of router:";
    cin>>s;
    for(int i=0;i<size;++i)
    {
        if(router_info[i].num==s)
        {
            v0=i;
            break;
        }
    }
    //start to calculate
    bool flag[20];//pending if this node has been calculated
    int dist[20];//distance
    int pre[20];//the number of parent
    //initialization
    for(int i=0;i<size;++i)
    {
        dist[i]=table[v0][i];
        flag[i]=false;
        if(dist[i]==INFINITY)
            pre[i]=-1;
        else
            pre[i]=v0;
    }
    dist[v0]=0;
    flag[v0]=true;//v0 has been calculated
    for(int i=1;i<size;++i)
    {
        int temp=INFINITY;
        int node=v0;//NOTICE:the number of v0 is node+1
        for(int j=0;j<size;++j)//to find the shortest node
        {
            if(flag[j]==false&&dist[j]<temp)
            {
                node=j;
                temp=dist[j];
            }
        }
        flag[node]=true;
        for(int k=0;k<size;++k)
        {
            if(flag[k]==false&&table[node][k]!=INFINITY)
            {
                if(table[node][k]+dist[node]<dist[k])
                {
                    dist[k]=table[node][k]+dist[node];
                    pre[k]=node;
                }
            }
        }
    }
    //dijkstra ends
    cout<<"\t\t-------------------------------------------"<<endl;
    int temp_num;
    
    for(int i=0;i<size;++i)
    {
        stack<int> s1;
        temp_num=i;
        if(i==v0)
            continue;
        int count=0;
        while(count<size)
        {
            int c=temp_num;
            temp_num=pre[temp_num];
            s1.push(c);
            if(temp_num==v0)
            {
                cout<<"\t\t   The destination IP is : "<<router_info[i].ip<<endl;
                cout<<"\t\t   The next jump is  : "<<router_info[c].num<<endl;
                cout<<"\t\t   path : ";
                cout<<router_info[v0].num;
                while(1)
                {
                    cout<<"->";
                    cout<<router_info[s1.top()].num;
                    s1.pop();
                    if(s1.empty())
                        break;
                }
                cout<<endl;
                cout<<"\t\t-------------------------------------------"<<endl;
                break;
            }
            count++;
            
        }
    }
    menu(G);
}


void router::deleteVertex(router &G)
{
    int i,v;
    cout<<"\t\t-->Please enter the number of router :";
    cin>>i;
    v=getVertexPos(i);
    if(v==-1)
    {
        cout<<"\t\t-->E N T E R__E R R O R !"<<endl;
        return;
    }
    router_info[v]=router_info[size-1];
    for(i=0; i<size; i++)
    {
        table[i][v]=table[i][size-1];
        //if(table[v][i]>0&&table[v][i]<MaxValue)
    }
    size--;
    for(i=0; i<size; i++)
    {
        table[v][i]=table[size][i];
    }
    save();
    menu(G);
}

void router::deleteEdge(router &G)
{
    int a,b;
    cout<<"\t\t-->Please enter the information of edge: "<<endl;
    cout<<"\t\t-->Please enter the source IP :";
    cin>>a;
    cout<<endl<<"\t\t-->Please enter the  destination IP: ";
    cin>>b;
    int v,t;
    v=getVertexPos(a);
    t=getVertexPos(b);
    if(v==-1)
    {
        cout<<"\t\t-->E N T E R__E R R O R !"<<endl;
        return;
    }
    else if(t==-1)
    {
        cout<<"\t\t--> E N T E R__E R R O R !"<<endl;
        return;
    }
    else if(table[v][t]>0&&table[v][t]<INFINITY)table[v][t]=table[t][v]=INFINITY;
    save();
    menu(G);
}

void router::addVertex(router &G)
{
    int i;
    if(size>20)
    {
        cout<<"\t\t-->Table Full!"<<endl;
        return;
    }
    cout<<"\t\t-->Please enter the routing information :"<<endl;
    cout<<"\t\t-->IP: ";
    cin>>router_info[size].ip;
    cout<<"\t\t-->Number: ";
    cin>>router_info[size].num;
    for(i=0; i<size; i++)
    {
        table[size][i]=table[i][size]=INFINITY;
    }
    table[size][i]=0;
    size++;
    save();
    menu(G);
}

void router::addEdge(router &G)
{
    int a,b,c;
    cout<<"\t\t-->Please enter the information of edge : "<<endl;
    cout<<"\t\t-->Please enter the source IP :";
    cin>>a;
    cout<<endl<<"\t\t-->Please enter destination IP :";
    cin>>b;
    cout<<endl<<"\t\t-->Please enter the cost of the edge :"<<endl;
    cin>>c;
    int v,t;
    v=getVertexPos(a);
    t=getVertexPos(b);
    if(v==-1)
    {
        cout<<"\t\t-->Wrong information of source IP!"<<endl;
        return;
    }
    else if(t==-1)
    {
        cout<<"\t\t-->Wrong information of source IP!"<<endl;
        return;
    }
    else if(table[v][t]!=0&&table[v][t]<INFINITY)table[v][t]=table[t][v]=c;
    save();
    menu(G);
}


void router::createVertices()
{
    int i=0,j,tag=1;
    cout<<"\t\t-->Please enter routing information :"<<endl;
    while(tag)
    {
        cout<<"\t\t-->IP: "<<endl;
        cin>>router_info[i++].ip;
        cout<<"\t\t-->Number: "<<endl;
        cin>>router_info[i++].num;
        cout<<"\t\t-->enter '0' to exit"<<endl;
        cin>>tag;
        size++;
    }
    ofstream out("/Users/tadakanade/desktop/cage/root_table/root_table/rout_info.txt");
    if(out.is_open())
    {
        for(j=0; j<i; j++)
            out<<router_info[j].ip<<" "<<router_info[j].num<<endl;;
    }
    out.close();
}

void router::createEdges()
{
    int i,j,count=0,tag=1;
    int a,b,c;
    int v,t;
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            if(i==j)table[i][j]=0;
            else table[i][j]=INFINITY;
        }
    cout<<"\t\t-->Please enter the path information :";
    while(tag)
    {
        cout<<endl<<"\t\t-->Please enter the source IP : ";
        cin>>a;
        cout<<endl<<"\t\t-->Please enter the destination IP : ";
        cin>>b;
        cout<<endl<<"\t\t-->Please enter the cost: ";
        cin>>c;
        cout<<endl<<"\t\t-->enter '0' to exit!  ";
        cin>>tag;
        v=getVertexPos(a);
        t=getVertexPos(b);
        if(v!=-1&&t!=-1)
        {
            table[v][t]=c;
            table[t][v]=c;
        }
    }
    ofstream out("/Users/tadakanade/desktop/cage/root_table/root_table/rout_path.txt");
    if(out.is_open())
    {
        for(i=0; i<size; i++)
            for(j=0; j<size; j++)
            {
                out<<table[i][j]<<" ";
                count++;
                if(count%size==0)out<<endl;
            }
    }
    out.close();
}

void router::createGraph()
{
    int i=0,j;
    char buff[255];
    int number;
    size=0;
    ifstream in("/Users/tadakanade/desktop/cage/root_table/root_table/rout_info.txt");
    if(!in)
    {
        cout<<"\t\t-->O P E N__E R R O R !"<<endl;
        exit(1);
    }
    while(!in.eof()&&size<=20)
    {
        in>>buff>>number;
        router_info[i].ip=buff;
        router_info[i].num=number;
        i++;
        size++;
    }
    size=size-1;
    in.close();
    ifstream fin("/Users/tadakanade/desktop/cage/root_table/root_table/rout_path.txt");
    if(!fin)
    {
        cout<<"\t\t-->O P E N__E R R O R !"<<endl;
        exit(1);
    }
    while(!fin.eof())
    {
        for(i=0; i<size; i++)
            for(j=0; j<size; j++)
            {
                fin>>table[i][j];
            }
    }
}

void router::save()
{
    int i,j,count=0;
    ofstream out("/Users/tadakanade/desktop/cage/root_table/root_table/rout_info.txt");
    if(out.is_open())
    {
        for(i=0; i<size; i++)
            out<<router_info[i].ip<<" "<<router_info[i].num<<endl;
    }
    out.close();
    ofstream fout("/Users/tadakanade/desktop/cage/root_table/root_table/rout_path.txt");
    if(fout.is_open())
    {
        for(i=0; i<size; i++)
            for(j=0; j<size; j++)
            {
                fout<<table[i][j]<<"\t";
                count++;
                if(count%size==0)fout<<endl;
            }
    }
    fout.close();
}
void menu(router &G)
{
    system("cls");
    int i=0,n=0,m=0;
    int p=1;
    cout <<"\t\t|-------------W E L C O M E !-------------|"<<endl;
    cout <<"\t\t|>>>>>This is an initialization page<<<<<<|"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|Initialization from:                     |"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|  1: Keyboard                            |"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|  2: File                                |"<<endl;
    cout <<"\t\t|------------Thanks for using!------------|"<<endl;
    cout <<"\t\t-->Your choice is :";
    while(m!=1||m!=2)
    {
    cin>>m;
    switch(m)
    {
    case 1:
        G.createVertices();
        G.createEdges();
        break;
    case 2:
        G.createGraph();
        cout <<"\t\t-->Initialization success !"<<endl;
        break;
    default:
        cout<<"\t\tW R O N G__E N T E R !"<<endl;
        cout <<"\t\t--> Please enter the correct number"<<endl;
        cout <<"\t\t-->Your choice is :";
    }
    if(m==1||m==2)break;
    }
    cout <<"\t\t|-------------W E L C O M E !-------------|"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|  Function choices:                      |"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|  1.Print the routing information base   |"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|  2.Add a router                         |"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|  3.Delete a router                      |"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|  Please enter the number your choose:   |"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|  4.Exit the program                     |"<<endl;
    cout <<"\t\t|                                         |"<<endl;
    cout <<"\t\t|  Please enter the number your choose:   |"<<endl;
    cout <<"\t\t|------------Thanks for using!------------|"<<endl;
    cout <<"\t\t                                           "<<endl;
    //cout <<"\t\t--> Your choice is :";

    while(p)
    {
    cout <<"\t\t--> Your choice is :";
    cin >>i;
    if(i<1||i>4)
    {
        p=1;
        cout <<"\t\t--> Please enter the correct number"<<endl;
    }
    else p=0;
    }
    switch(i)
    {
        case 1:
            G.calculate(G);
            break;
        case 2:
            cout <<"\t\t-->Please choose the function you want:"<<endl;
            cout <<"\t\t-->1.Add router"<<endl<<"\t\t-->2.Add edge"<<endl;
            cout <<"\t\t-->Your choice is :";
            cin >>n;
            if(n==1)G.addVertex(G);
            else if(n==2)G.addEdge(G);
            else cout <<"\t\tW R O N G__E N T E R !"<<endl;
            break;
        case 3:
            cout <<"\t\t-->Please choose the function you want:"<<endl;
            cout <<"\t\t-->1.Delete router"<<endl<<"\t\t-->2.Delete edge"<<endl;
            cout <<"\t\t-->Your choice is :";
            cin >>n;
            if(n==1)G.deleteVertex(G);
            else if(n==2)G.deleteEdge(G);
            else cout <<"\t\tW R O N G__E N T E R !"<<endl;
            break;
        case 4:
            return;
        default:
        cout<<"\t\tW R O N G__E N T E R !"<<endl;
        cout <<"\t\t--> Please enter the correct number"<<endl;
        cout <<"\t\t-->Your choice is :";
    }
}

int main()
{
    router G;
    menu(G);
    return 0;
}

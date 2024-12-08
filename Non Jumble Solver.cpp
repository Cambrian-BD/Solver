#include<set>
#include<cmath>
#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int BLOCKNUMBER=100;
const int OPERATION=10;
const int MAXSTEP=18;
const int MAXANS=1000;
const int MAXSIZE=1000;
const int MAXLENGTH=260;
const int MAXMULTIPLE=5;
int n,m;
int numberOfSolutions=0;
int opMem[MAXSTEP+5];
string opMap[OPERATION];
struct Loop{
    int size=0;
    int num[BLOCKNUMBER];
};
class Solution{
    public:
    int parity=1,multiplied=1;
    int numberOfLoops=0,numberOfSteps=0;
    int steps[MAXLENGTH];
    int mapOfBlocks[BLOCKNUMBER];
    Loop loops[BLOCKNUMBER>>1];
    bool operator<(const Solution &x)const{
        if(numberOfLoops==0)return 0;
        if(numberOfLoops<x.numberOfLoops)return 1;
        if(numberOfLoops==x.numberOfLoops&&loops[0].size<x.loops[0].size)return 1;
        if(numberOfLoops==x.numberOfLoops&&loops[0].size==x.loops[0].size&&numberOfSteps<x.numberOfSteps)return 1;
        if(numberOfLoops==x.numberOfLoops&&loops[0].size==x.loops[0].size&&numberOfSteps==x.numberOfSteps&&loops[0].num[0]<x.loops[0].num[0])return 1;
        return 0;
    }
    bool operator>(const Solution &x)const{
        if(numberOfLoops==0)return 1;
        if(numberOfLoops>x.numberOfLoops)return 1;
        if(numberOfLoops==x.numberOfLoops&&loops[0].size>x.loops[0].size)return 1;
        if(numberOfLoops==x.numberOfLoops&&loops[0].size==x.loops[0].size&&numberOfSteps>x.numberOfSteps)return 1;
        if(numberOfLoops==x.numberOfLoops&&loops[0].size==x.loops[0].size&&numberOfSteps==x.numberOfSteps&&loops[0].num[0]>x.loops[0].num[0])return 1;
        return 0;
    }
    Solution(){
        for(int i=0;i<n;++i)
            mapOfBlocks[i]=i;
    }
}start,starttemp;
Solution baseSolutions[MAXANS*MAXMULTIPLE];
Solution Operations[OPERATION];
priority_queue<Solution,vector<Solution>> solution;
//priority_queue<Solution,vector<Solution>,greater<Solution>> Recycle;
class Puzzles{
    public:
    int numberOfBlocks;
    int operationName[OPERATION];
    string name;
}puzzles[20];
void FindLoops(Solution &ret);
bool compLoop(const Loop &a,const Loop &b){
    return a.size>b.size;
}
void Init(int x=0){
    if(x==0){
        cin>>n;
    }
    else if(x==1){
        n=55;
        cout<<"Eliac"<<endl;
    }
    else if(x==2){
        n=33;
        cout<<"Trapentrix"<<endl;
    }
    else if(x==3){
        n=26;
        cout<<"Bauhinium"<<endl;
    }
    else if(x==4){
        n=30;
        cout<<"Bygride 3-4"<<endl;
    }
    else if(x==5){
        n=47;
        cout<<"BiAxe"<<endl;
    }
    else if(x==6){
        n=25;
        cout<<"Moonshine"<<endl;
    }
    else if(x==7){
        n=67;
        cout<<"Trientalis"<<endl;
    }
    else if(x==8){
        n=33;
        cout<<"Eight"<<endl;
    }
    else if(x==9){
        n=69;
        cout<<"Arecibo"<<endl;
    }
    else if(x==10){
        n=9;
        cout<<"Subgraph"<<endl;
    }
    else if(x==11){
        n=29;
        cout<<"Cohan Circle"<<endl;
    }
    else if(x==12){
        n=30;
        cout<<"Jugo Flower"<<endl;
    }
    else if(x==13){
        n=71;
        cout<<"Mimosa"<<endl;
    }
    else if(x==14){
        n=15;
        cout<<"BiRex"<<endl;
    }
    else if(x==15){
        n=14;
        cout<<"Looper"<<endl;
    }
    else if(x==16){
        n=9;
        cout<<"Trilotica v1"<<endl;
    }
    else if(x==17){
        n=14;
        cout<<"Trilotica v2"<<endl;
    }
    else if(x==18){
        n=32;
        cout<<"Trilotica v3"<<endl;
    }
    else if(x==19){
        n=40;
        cout<<"Trilotica v4"<<endl;
    }
    else if(x==1000){
        n=14;
        cout<<"Test"<<endl;
    }
    for(int i=0;i<n;++i){
        start.mapOfBlocks[i]=i;
    }
}
void opInit(int x=0){
    if(x==0){
        cin>>m;
        for(int i=0;i<m;++i)
            opMap[i]='A'+i;
    }
    else if(x==1){
        m=4;
        opMap[0]="A1";
        opMap[1]="A2";
        opMap[2]="A3";
        opMap[3]="B";
    }
    else if(x==2){
        m=4;
        opMap[0]='L';
        opMap[1]="L'";
        opMap[2]="R";
        opMap[3]="R'";
    }
    else if(x==3){
        m=5;
        opMap[0]="A1";
        opMap[1]="A2";
        opMap[2]="A3";
        opMap[3]="A4";
        opMap[4]="B";
    }
    else if(x==4){
        m=5;
        opMap[0]="L";
        opMap[1]="L2";
        opMap[2]="L'";
        opMap[3]="R";
        opMap[4]="R'";
    }
    else if(x==5){
        m=6;
        opMap[0]="L";
        opMap[1]="L2";
        opMap[2]="L'";
        opMap[3]="R";
        opMap[4]="R2";
        opMap[5]="R'";
    }
    else if(x==6){
        m=5;
        opMap[0]="A1";
        opMap[1]="A2";
        opMap[2]="A3";
        opMap[3]="A4";
        opMap[4]="B";
    }
    else if(x==7){
        m=4;
        opMap[0]='L';
        opMap[1]="L'";
        opMap[2]="R";
        opMap[3]="R'";
    }
    else if(x==8){
        m=4;
        opMap[0]="L";
        opMap[1]="L2";
        opMap[2]="L'";
        opMap[3]="R2";
    }
    else if(x==9){
        m=4;
        opMap[0]='L';
        opMap[1]="L'";
        opMap[2]="R";
        opMap[3]="R'";
    }
    else if(x==10){
        m=4;
        opMap[0]='L';
        opMap[1]="L'";
        opMap[2]="R";
        opMap[3]="R'";
    }
    else if(x==11){
        m=10;
        opMap[0]="L";
        opMap[1]="L2";
        opMap[2]="L3";
        opMap[3]="L2'";
        opMap[4]="L'";
        opMap[5]="R";
        opMap[6]="R2";
        opMap[7]="R3";
        opMap[8]="R2'";
        opMap[9]="R'";
    }
    else if(x==12){
        m=15;
        opMap[0]="R";
        opMap[1]="R2";
        opMap[2]="R3";
        opMap[3]="R4";
        opMap[4]="R5";
        opMap[5]="R6";
        opMap[6]="R7";
        opMap[7]="R8";
        opMap[8]="R9";
        opMap[9]="R10";
        opMap[10]="R11";
        opMap[11]="R12";
        opMap[12]="R13";
        opMap[13]="R14";
        opMap[14]="R15";
    }
    else if(x==13){
        m=5;
        opMap[0]="L";
        opMap[1]="L2";
        opMap[2]="L2'";
        opMap[3]="L'";
        opMap[4]="R";
    }
    else if(x==14){
        m=4;
        opMap[0]="L";
        opMap[1]="L2";
        opMap[2]="L'";
        opMap[3]="R";
    }
    else if(x==15){
        m=3;
        opMap[0]="L";
        opMap[1]="U";
        opMap[2]="R";
    }
    else if(x>=16&&x<=19){
        m=3;
        opMap[0]="L";
        opMap[1]="L'";
        opMap[2]="R";
    }
    else if(x==1000){
        m=4;
        opMap[3]="X";
        opMap[0]="L";
        opMap[1]="L'";
        opMap[2]="R";
    }
    for(int i=0;i<m;++i){
        Operations[i].numberOfSteps=1;
        Operations[i].steps[0]=i;
        for(int j=0;j<n;++j){
            cin>>Operations[i].mapOfBlocks[j];
        }
        FindLoops(Operations[i]);
    }
}
void doOperation(Solution x,Solution &s){
    int buf[BLOCKNUMBER];
    for(int i=0;i<n;++i)
        buf[i]=s.mapOfBlocks[x.mapOfBlocks[i]];
    for(int i=0;i<n;++i)
        s.mapOfBlocks[i]=buf[i];
}
void reverseOp(Solution x,Solution &s){
    int buf[BLOCKNUMBER];
    for(int i=0;i<n;++i)
        buf[x.mapOfBlocks[i]]=s.mapOfBlocks[i];
    for(int i=0;i<n;++i)
        s.mapOfBlocks[i]=buf[i];
}
int ReverseMap(int x){
    return x^1;
    if(x<=1)return 1-x;
    return x;
}
void FindLoops(Solution &ret){
    ret.numberOfLoops=0;
    for(int i=0;i<BLOCKNUMBER>>1;++i){
        ret.loops[i].size=0;
    }
    bool visited[BLOCKNUMBER];
    for(int i=0;i<n;++i)visited[i]=0;
    for(int i=0;i<n;++i){
        if(!visited[ret.mapOfBlocks[i]]){
            if(ret.mapOfBlocks[i]==i){
                visited[ret.mapOfBlocks[i]]=1;
                continue;
            }
            int now=ret.mapOfBlocks[i];
            while (!visited[now]){
                ret.loops[ret.numberOfLoops].num[ret.loops[ret.numberOfLoops].size++]=now;
                visited[now]=1;
                now=ret.mapOfBlocks[now];
            }
            ret.numberOfLoops++;
        }
    }
    sort(ret.loops,ret.loops+ret.numberOfLoops,compLoop);
}
Solution ConvertToSolution(int steps,Solution &x){
    x.numberOfSteps=steps;
    for(int i=0;i<steps;++i){
        x.steps[i]=opMem[i];
    }
    FindLoops(x);
    return x;
}
bool Check(Solution x,int Round){
    if(x.numberOfLoops==0)return 0;
    //return 1;
    if(Round==0)return 1;
    bool flag=0;
    for(int i=0;i<x.numberOfLoops;++i){
        if(x.loops[i].num[0]>=15&&x.loops[i].num[0]<=32&&x.loops[i].size<7){
            flag=1;
            break;
        }
    }
    return flag;
}
bool CheckParity(int step,Solution &x){
    if(x.parity==0&&step<=1)return 0;
    if(x.parity==1&&step>1)return 0;
    return 1;
}
void Mask(Solution &x){
    //return;
    for(int i=0;i<n;++i){
        if((i>=6&&i<=14)){
            x.mapOfBlocks[i]=i;
        }
    }
}
void dfs(int step,int depth){
    while(!solution.empty()&&(solution.size()>MAXSIZE||solution.top().numberOfLoops==0)){
        /*if(solution.top().numberOfLoops&&RecycleCheck(solution.top())){
            Recycle.push(solution.top());
        }
        if(Recycle.size()>MAXSIZE)Recycle.pop();*/
        solution.pop();
    }
    starttemp=start;
    Mask(starttemp);
    FindLoops(starttemp);
    if(Check(starttemp,0))
        solution.push(ConvertToSolution(step,starttemp));
    if(step>=depth)return;
    for(int i=0;i<m;++i){
        if(step&&!CheckParity(i,start))continue;
        if(step==0){
            start.parity=i<=1;//
        }
        opMem[step]=i;
        doOperation(Operations[i],start);
        start.parity^=1;
        dfs(step+1,depth);
        reverseOp(Operations[i],start);
        start.parity^=1;
    }
}
Solution Compose(Solution &a,Solution &b,bool add){
    Solution ret;
    if(add){
        for(int i=0;i<n;++i)
            ret.mapOfBlocks[i]=a.mapOfBlocks[b.mapOfBlocks[i]];
    }
    else{
        for(int i=0;i<n;++i)
            ret.mapOfBlocks[b.mapOfBlocks[i]]=a.mapOfBlocks[i];
    }
    ret.numberOfSteps=a.numberOfSteps+b.numberOfSteps;
    for(int i=0;i<ret.numberOfSteps;++i){
        if(add)
            ret.steps[i]=(i<a.numberOfSteps)?a.steps[i]:b.steps[i-a.numberOfSteps];
        else ret.steps[i]=(i<a.numberOfSteps)?a.steps[i]:ReverseMap(b.steps[b.numberOfSteps-i+a.numberOfSteps-1]);
    }
    FindLoops(ret);
    return ret;
}
Solution Commutator(Solution &a,Solution &b){
    Solution ret,temp1,temp2;
    for(int i=0;i<n;++i)
        temp1.mapOfBlocks[i]=a.mapOfBlocks[b.mapOfBlocks[i]];
    for(int i=0;i<n;++i)
        temp2.mapOfBlocks[a.mapOfBlocks[i]]=temp1.mapOfBlocks[i];
    for(int i=0;i<n;++i)
        ret.mapOfBlocks[b.mapOfBlocks[i]]=temp2.mapOfBlocks[i];
    ret.numberOfSteps=a.numberOfSteps*2+b.numberOfSteps*2;
    for(int i=0;i<ret.numberOfSteps&&i<MAXLENGTH;++i){
        if(i<a.numberOfSteps){
            ret.steps[i]=a.steps[i];
        }
        else if(i-a.numberOfSteps<b.numberOfSteps){
            ret.steps[i]=b.steps[i-a.numberOfSteps];
        }
        else if(i-a.numberOfSteps-b.numberOfSteps<a.numberOfSteps){
            ret.steps[i]=ReverseMap(a.steps[a.numberOfSteps*2+b.numberOfSteps-1-i]);
        }
        else{
            ret.steps[i]=ReverseMap(b.steps[a.numberOfSteps*2+b.numberOfSteps*2-1-i]);
        }
    }
    FindLoops(ret);
    return ret;
}
Solution Conjugate(Solution &a,Solution &b){
    Solution ret,temp;
    for(int i=0;i<n;++i)
        temp.mapOfBlocks[i]=a.mapOfBlocks[b.mapOfBlocks[i]];
    for(int i=0;i<n;++i)
        ret.mapOfBlocks[a.mapOfBlocks[i]]=temp.mapOfBlocks[i];
    ret.numberOfSteps=a.numberOfSteps*2+b.numberOfSteps;
    for(int i=0;i<ret.numberOfSteps&&i<MAXLENGTH;++i){
        if(i<a.numberOfSteps){
            ret.steps[i]=a.steps[i];
        }
        else if(i-a.numberOfSteps<b.numberOfSteps){
            ret.steps[i]=b.steps[i-a.numberOfSteps];
        }
        else{
            ret.steps[i]=ReverseMap(a.steps[a.numberOfSteps*2+b.numberOfSteps-1-i]);
        }
    }
    FindLoops(ret);
    return ret;
}
void ShowAnswer(int Round){
    cout<<"Find "<<solution.size()<<" perms."<<endl;
    priority_queue<Solution,vector<Solution>,greater<Solution>> _rev;
    while (!solution.empty()){
        if(Check(solution.top(),Round))_rev.push(solution.top());
        solution.pop();
    }
    for(int i=0;i<MAXANS;++i){
        if(_rev.empty())break;
        cout<<"#"<<i+1<<endl;
        Solution temp=_rev.top();
        _rev.pop();
        baseSolutions[numberOfSolutions++]=temp;
        for(int j=0;j<temp.numberOfSteps*temp.multiplied;++j){
            cout<<opMap[temp.steps[j%temp.numberOfSteps]]<<' ';
        }
        cout<<endl;
        cout<<"length: "<<temp.numberOfSteps*temp.multiplied<<endl;
        cout<<"code: ";
        for(int j=0;j<temp.numberOfSteps*temp.multiplied;++j)
            cout<<temp.steps[j%temp.numberOfSteps]<<' ';
        cout<<endl;
        for(int i=0;i<n;++i)cout<<temp.mapOfBlocks[i]<<' ';
        cout<<endl;
        for(int j=0;j<temp.numberOfLoops;++j){
            cout<<"  Loop "<<j+1<<": ";
            for(int k=0;k<temp.loops[j].size;++k){
                cout<<temp.loops[j].num[k];
                if(k!=temp.loops[j].size-1)cout<<" <- ";
            }
            cout<<"   size: "<<temp.loops[j].size;
            cout<<endl;
        }
        cout<<endl;
    }
    for(int i=0;i<m;++i){
        Mask(Operations[i]);
        baseSolutions[numberOfSolutions++]=Operations[i];
    }
        
}
void GenerateNewSolution(){
    while(!solution.empty())solution.pop();
    //Multiply();
    for(int i=0;i<numberOfSolutions;++i){
        while(solution.size()>MAXSIZE)solution.pop();
        for(int j=i+1;j<numberOfSolutions;++j){
            Solution temp=Compose(baseSolutions[i],baseSolutions[j],0);
            if(temp<baseSolutions[i]&&temp<baseSolutions[j]){
                solution.push(temp);
            }
            /*temp=Compose(baseSolutions[j],baseSolutions[i],0);
            if(temp<baseSolutions[i]&&temp<baseSolutions[j]){
                solution.push(temp);
            }*/
            temp=Compose(baseSolutions[i],baseSolutions[j],1);
            if(temp<baseSolutions[i]&&temp<baseSolutions[j]){
                solution.push(temp);
            }
            temp=Commutator(baseSolutions[i],baseSolutions[j]);
            if(temp<baseSolutions[i]&&temp<baseSolutions[j]){
                solution.push(temp);
            }
            temp=Conjugate(baseSolutions[i],baseSolutions[j]);
            if(temp<baseSolutions[i]&&temp<baseSolutions[j]){
                solution.push(temp);
            }
            temp=Conjugate(baseSolutions[j],baseSolutions[i]);
            if(temp<baseSolutions[i]&&temp<baseSolutions[j]){
                solution.push(temp);
            }
        }
    }
    numberOfSolutions=0;
}
void Simulate(){
    int num;
    Solution a;
    for(int i=0;i<n;++i)a.mapOfBlocks[i]=i;
    cin>>num;
    for(int i=0;i<num;++i){
        int OP;
        cin>>OP;
        cout<<opMap[OP]<<' ';
        doOperation(Operations[OP],a);
    }
    cout<<endl;
    for(int i=0;i<n;++i)cout<<a.mapOfBlocks[i]<<' ';
    cout<<endl;
    FindLoops(a);
    for(int i=0;i<a.numberOfLoops;++i){
        for(int j=0;j<a.loops[i].size;++j){
            cout<<a.loops[i].num[j];
            if(j!=a.loops[i].size-1)cout<<" <- ";
        }
        cout<<endl;
    }
    cout<<endl;
}
int main(){
    freopen("Results.txt","w",stdout);
    cout<<"Start"<<endl;
    Init(2);
    opInit(2);
    //Simulate();
    //return 0;
    dfs(0,MAXSTEP);
    ShowAnswer(0);
    for(int i=1;i<=2;++i){
        cout<<"-------------"<<i<<"-------------"<<endl;
        GenerateNewSolution();
        ShowAnswer(i);
    }
    cout<<"End"<<endl;
    fclose(stdout);
    return 0;
}
/*
Eliac

0 1 4 2 5 3 6 7 9 11 8 10 12 13 14 17 18 22 21 16 15 19 20 23 24 33 29 34 30 39 37 27 25 40 38 28 26 35 31 36 32 41 42 47 45 49 43 50 44 48 46 51 52 53 54
0 1 5 4 3 2 6 7 11 10 9 8 12 13 14 22 21 20 19 18 17 16 15 23 24 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 41 42 50 49 48 47 46 45 44 43 51 52 53 54
0 1 3 5 2 4 6 7 10 8 11 9 12 13 14 20 19 15 16 21 22 18 17 23 24 32 36 31 35 26 28 38 40 25 27 37 39 30 34 29 33 41 42 46 48 44 50 43 49 45 47 51 52 53 54
1 0 2 3 7 6 5 4 8 14 13 12 11 10 9 15 16 17 24 23 20 22 21 19 18 25 26 27 28 29 30 31 32 33 42 41 36 40 39 38 37 35 34 43 44 45 46 52 51 50 49 48 47 54 53
*/
/*
Trapentrix

2 0 1 3 4 5 8 6 7 9 12 10 11 13 14 19 20 15 16 17 18 21 30 32 24 25 26 23 22 29 28 31 27
1 2 0 3 4 5 7 8 6 9 11 12 10 13 14 17 18 19 20 15 16 21 28 27 24 25 26 32 30 29 22 31 23
0 1 2 5 3 4 7 9 8 6 13 11 12 14 10 15 27 29 18 19 20 25 26 21 22 23 24 31 28 30 17 16 32
0 1 2 4 5 3 9 6 8 7 14 11 12 10 13 15 31 30 18 19 20 23 24 25 26 21 22 16 28 17 29 27 32
*/
/*
Test

4
3
1 0 2 3
0 2 1 3
0 1 3 2

*/
/*
Bauhinium

0 1 6 2 3 4 5 7 8 9 10 15 11 12 13 14 16 17 18 23 19 20 21 22 24 25
0 1 5 6 2 3 4 7 8 9 10 14 15 11 12 13 16 17 18 22 23 19 20 21 24 25
0 1 4 5 6 2 3 7 8 9 10 13 14 15 11 12 16 17 18 21 22 23 19 20 24 25
0 1 3 4 5 6 2 7 8 9 10 12 13 14 15 11 16 17 18 20 21 22 23 19 24 25
1 0 2 9 10 7 8 5 6 3 4 11 16 17 18 15 12 13 14 19 20 25 24 23 22 21
*/

/*
Bygride 3-4

3 0 1 2 4 5 9 6 7 8 10 11 12 13 20 21 14 15 16 17 18 19 22 23 24 25 26 27 28 29
2 3 0 1 4 5 8 9 6 7 10 11 12 13 18 19 20 21 14 15 16 17 22 23 24 25 26 27 28 29
1 2 3 0 4 5 7 8 9 6 10 11 12 13 16 17 18 19 20 21 14 15 22 23 24 25 26 27 28 29
5 1 2 3 0 4 13 12 8 9 7 6 10 11 25 24 26 17 18 19 20 16 15 14 22 23 21 29 27 28
4 1 2 3 5 0 11 10 8 9 12 13 7 6 23 22 21 17 18 19 20 26 24 25 15 14 16 28 29 27
*/

/*
BiAxe

3 0 1 2 4 5 6 7 11 8 9 10 12 13 17 14 15 16 18 19 20 27 28 21 22 23 24 25 26 29 44 43 32 33 34 35 36 37 38 31 30 39 40 41 42 45 46
2 3 0 1 4 5 6 7 10 11 8 9 12 13 16 17 14 15 18 19 20 25 26 27 28 21 22 23 24 29 42 41 32 33 34 35 36 37 38 43 44 31 30 39 40 45 46
1 2 3 0 4 5 6 7 9 10 11 8 12 13 15 16 17 14 18 19 20 23 24 25 26 27 28 21 22 29 40 39 32 33 34 35 36 37 38 41 42 43 44 31 30 45 46
0 1 2 3 7 4 5 6 9 13 10 11 8 12 20 15 16 17 14 18 19 21 39 38 24 25 26 27 28 35 36 29 30 31 32 33 34 45 46 37 40 41 42 43 23 22 44
0 1 2 3 6 7 4 5 13 12 10 11 9 8 19 15 16 17 20 14 18 21 37 46 24 25 26 27 28 33 34 35 36 29 30 31 32 22 44 45 40 41 42 43 38 39 23
0 1 2 3 5 6 7 4 12 8 10 11 13 9 18 15 16 17 19 20 14 21 45 44 24 25 26 27 28 31 32 33 34 35 36 29 30 39 23 22 40 41 42 43 46 37 38
 */

/*
Moonshine
0 2 3 4 5 1 6 7 9 10 11 12 8 13 14 17 18 19 20 21 22 23 24 15 16
0 3 4 5 1 2 6 7 10 11 12 8 9 13 14 19 20 21 22 23 24 15 16 17 18
0 4 5 1 2 3 6 7 11 12 8 9 10 13 14 21 22 23 24 15 16 17 18 19 20
0 5 1 2 3 4 6 7 12 8 9 10 11 13 14 23 24 15 16 17 18 19 20 21 22
1 0 2 3 4 5 8 9 6 7 10 11 12 16 17 18 13 14 15 19 20 21 22 23 24
*/

/*
Trientalis
2 1 3 0 4 7 5 6 8 16 13 11 15 19 14 17 18 12 9 10 20 21 22 32 33 34 26 36 30 31 42 37 38 39 40 35 41 29 23 24 25 27 28 43 44 45 46 47 48 50 51 49 64 65 66 54 52 53 58 59 60 61 62 63 56 57 55
3 1 0 2 4 6 7 5 8 18 19 11 17 10 14 12 9 15 16 13 20 21 22 38 39 40 26 41 42 37 28 29 23 24 25 35 27 31 32 33 34 36 30 43 44 45 46 47 48 51 49 50 56 57 55 66 64 65 58 59 60 61 62 63 52 53 54
1 2 0 3 8 4 6 7 5 22 10 20 21 12 9 15 11 17 18 19 16 13 14 48 43 44 45 46 28 47 25 26 27 33 29 23 24 37 38 39 40 41 42 36 30 31 32 34 35 60 58 59 53 54 52 55 56 57 62 63 61 49 50 51 64 65 66
2 0 1 3 5 8 6 7 4 14 10 16 13 21 22 15 20 17 18 19 11 12 9 35 36 30 31 32 28 34 44 45 46 33 47 48 43 37 38 39 40 41 42 24 25 26 27 29 23 61 62 63 54 52 53 55 56 57 50 51 49 60 58 59 64 65 66
*/

/*
Eight
1 2 3 0 4 5 7 8 9 6 10 13 14 15 16 17 18 11 12 21 22 23 24 25 26 19 20 27 28 30 31 32 29
2 3 0 1 4 5 8 9 6 7 10 15 16 17 18 11 12 13 14 23 24 25 26 19 20 21 22 27 28 31 32 29 30
3 0 1 2 4 5 9 6 7 8 10 17 18 11 12 13 14 15 16 25 26 19 20 21 22 23 24 27 28 32 29 30 31
0 1 4 5 2 3 6 7 10 9 8 11 12 13 14 15 25 24 18 19 20 21 22 27 17 16 28 23 26 29 30 31 32
*/

/*
Arecibo
1 2 0 3 4 5 7 8 6 9 12 13 14 15 10 11 22 16 18 19 20 21 17 23 26 27 28 29 24 25 32 33 34 35 30 31 36 37 38 39 40 41 43 44 42 45 46 49 50 51 52 47 48 55 56 57 58 53 54 60 61 59 62 63 64 65 66 67 68
2 0 1 3 4 5 8 6 7 9 14 15 10 11 12 13 17 22 18 19 20 21 16 23 28 29 24 25 26 27 34 35 30 31 32 33 36 37 38 39 40 41 44 42 43 45 46 51 52 47 48 49 50 57 58 53 54 55 56 61 59 60 62 63 64 65 66 67 68
0 1 2 4 5 3 6 9 7 8 10 11 12 13 23 14 18 19 20 21 16 17 22 15 24 25 26 41 33 29 30 31 37 40 27 36 38 39 35 32 28 34 42 43 45 46 44 47 48 49 67 60 52 53 54 63 68 56 62 59 66 50 64 65 58 55 51 61 57
0 1 2 5 3 4 6 8 9 7 10 11 12 13 15 23 20 21 16 17 18 19 22 14 24 25 26 34 40 29 30 31 39 28 41 38 35 32 36 37 33 27 42 43 46 44 45 47 48 49 61 66 52 53 54 65 57 68 64 59 51 67 58 55 62 63 60 50 56 
*/

/*
Subgraph
1 2 0 3 6 4 5 7 8
2 0 1 3 5 6 4 7 8 
0 8 4 2 3 5 6 1 7
0 7 3 4 2 5 6 8 1 
*/

/*
Cohan Circle
1 2 3 4 5 0 6 7 8 9 11 12 13 14 15 10 17 18 19 20 21 16 22 23 24 25 26 27 28
2 3 4 5 0 1 6 7 8 9 12 13 14 15 10 11 18 19 20 21 16 17 22 23 24 25 26 27 28
3 4 5 0 1 2 6 7 8 9 13 14 15 10 11 12 19 20 21 16 17 18 22 23 24 25 26 27 28 
4 5 0 1 2 3 6 7 8 9 14 15 10 11 12 13 20 21 16 17 18 19 22 23 24 25 26 27 28 
5 0 1 2 3 4 6 7 8 9 15 10 11 12 13 14 21 16 17 18 19 20 22 23 24 25 26 27 28
0 1 2 3 9 4 5 6 7 8 10 11 12 13 26 21 20 17 18 19 25 14 16 22 23 24 27 28 15
0 1 2 3 8 9 4 5 6 7 10 11 12 13 27 14 25 17 18 19 24 26 20 16 22 23 28 15 21 
0 1 2 3 7 8 9 4 5 6 10 11 12 13 28 26 24 17 18 19 23 27 25 20 16 22 15 21 14 
0 1 2 3 6 7 8 9 4 5 10 11 12 13 15 27 23 17 18 19 22 28 24 25 20 16 21 14 26 
0 1 2 3 5 6 7 8 9 4 10 11 12 13 21 28 22 17 18 19 16 15 23 24 25 20 14 26 27 
*/

/*
Jugo Flower
15 1 2 18 4 5 6 7 23 9 10 26 12 13 14 0 16 17 3 19 20 21 22 8 24 25 11 27 28 29
0 1 17 3 4 5 6 22 8 9 25 11 12 13 29 15 16 2 18 19 20 21 7 23 24 10 26 27 28 14
0 16 2 3 4 5 21 7 8 24 10 11 12 28 14 15 1 17 18 19 20 6 22 23 9 25 26 27 13 29
15 1 2 3 4 20 6 7 23 9 10 11 27 13 14 0 16 17 18 19 5 21 22 8 24 25 26 12 28 29
0 1 2 3 19 5 6 22 8 9 10 26 12 13 29 15 16 17 18 4 20 21 7 23 24 25 11 27 28 14
0 1 2 18 4 5 21 7 8 9 25 11 12 28 14 15 16 17 3 19 20 6 22 23 24 10 26 27 13 29
0 1 17 3 4 20 6 7 8 24 10 11 27 13 14 15 16 2 18 19 5 21 22 23 9 25 26 12 28 29
0 16 2 3 19 5 6 7 23 9 10 26 12 13 14 15 1 17 18 4 20 21 22 8 24 25 11 27 28 29
15 1 2 18 4 5 6 22 8 9 25 11 12 13 14 0 16 17 3 19 20 21 7 23 24 10 26 27 28 29
0 1 17 3 4 5 21 7 8 24 10 11 12 13 29 15 16 2 18 19 20 6 22 23 9 25 26 27 28 14
0 16 2 3 4 20 6 7 23 9 10 11 12 28 14 15 1 17 18 19 5 21 22 8 24 25 26 27 13 29
15 1 2 3 19 5 6 22 8 9 10 11 27 13 14 0 16 17 18 4 20 21 7 23 24 25 26 12 28 29
0 1 2 18 4 5 21 7 8 9 10 26 12 13 29 15 16 17 3 19 20 6 22 23 24 25 11 27 28 14
0 1 17 3 4 20 6 7 8 9 25 11 12 28 14 15 16 2 18 19 5 21 22 23 24 10 26 27 13 29
0 16 2 3 19 5 6 7 8 24 10 11 27 13 14 15 1 17 18 4 20 21 22 23 9 25 26 12 28 29
*/

/*
Mimosa
1 2 3 4 0 5 6 7 8 10 11 12 13 9 14 15 17 18 19 20 16 21 22 23 25 26 27 28 24 30 31 32 33 29 34 35 37 38 39 40 36 41 42 44 45 46 47 43 49 50 51 52 48 54 55 56 57 53 59 60 61 62 58 63 64 65 66 67 68 69 70
2 3 4 0 1 5 6 7 8 11 12 13 9 10 14 15 18 19 20 16 17 21 22 23 26 27 28 24 25 31 32 33 29 30 34 35 38 39 40 36 37 41 42 45 46 47 43 44 50 51 52 48 49 55 56 57 53 54 60 61 62 58 59 63 64 65 66 67 68 69 70
3 4 0 1 2 5 6 7 8 12 13 9 10 11 14 15 19 20 16 17 18 21 22 23 27 28 24 25 26 32 33 29 30 31 34 35 39 40 36 37 38 41 42 46 47 43 44 45 51 52 48 49 50 56 57 53 54 55 61 62 58 59 60 63 64 65 66 67 68 69 70
4 0 1 2 3 5 6 7 8 13 9 10 11 12 14 15 20 16 17 18 19 21 22 23 28 24 25 26 27 33 29 30 31 32 34 35 40 36 37 38 39 41 42 47 43 44 45 46 52 48 49 50 51 57 53 54 55 56 62 58 59 60 61 63 64 65 66 67 68 69 70
8 1 5 6 7 2 3 4 0 9 10 11 14 15 12 13 16 17 21 22 23 18 19 20 24 25 26 33 35 29 30 31 34 27 32 28 36 37 41 39 42 38 40 43 44 45 53 64 48 49 50 63 58 46 68 55 56 67 52 66 60 61 65 51 47 62 59 57 54 70 69
*/

/*
BiRex
0 1 3 4 5 2 6 7 8 10 11 12 9 13 14
0 1 4 5 2 3 6 7 8 11 12 9 10 13 14
0 1 5 2 3 4 6 7 8 12 9 10 11 13 14
1 0 2 6 7 8 3 4 5 9 10 13 14 11 12
*/

/*
Looper

*/

/*
Trilotica v1
1 2 0 3 5 6 4 7 8
2 0 1 3 6 4 5 7 8
0 1 3 2 4 7 8 5 6
*/

/*
Trilotica v2
0 1 3 4 2 5 7 8 6 9 10 12 13 11
0 1 4 2 3 5 8 6 7 9 10 13 11 12
1 0 2 3 5 4 6 9 10 7 8 11 12 13
*/

/*
Trilotica v3
0 1 3 4 2 5 6 8 9 7 11 12 10 14 15 13 17 18 16 20 21 19 22 23 25 26 24 28 29 27 30 31
0 1 4 2 3 5 6 9 7 8 12 10 11 15 13 14 18 16 17 21 19 20 22 23 26 24 25 29 27 28 30 31
1 0 2 5 6 3 4 7 8 9 10 11 20 16 14 15 13 22 18 23 12 21 17 19 24 25 27 26 31 30 29 28
*/

/*
Trilotica v4
0 1 3 4 2 5 6 8 9 7 11 12 10 14 15 13 17 18 16 20 21 19 22 23 25 26 24 28 29 27 30 31 33 34 32 36 37 35 38 39
0 1 4 2 3 5 6 9 7 8 12 10 11 15 13 14 18 16 17 21 19 20 22 23 26 24 25 29 27 28 30 31 34 32 33 37 35 36 38 39
1 0 2 5 6 3 4 7 8 9 10 11 20 16 14 15 13 22 18 23 12 21 17 19 24 25 27 26 31 30 29 28 39 33 35 34 36 38 37 32
*/
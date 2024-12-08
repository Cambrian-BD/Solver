#include<cmath>
#include<cstdio>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
const int NUM=100;
const double EPSILON=1e-5;

int n;

class Vector{
    public:
        double x,y,z;
        Vector(void){x=0,y=0,z=0;};
        Vector(double x_,double y_,double z_):x(x_),y(y_),z(z_){};
        double norm();
        void get();
};
double Vector::norm(){return sqrt(this->x*this->x+this->y*this->y+this->z*this->z);}
void Vector::get(){cin>>this->x>>this->y>>this->z;}
double dotProduct(Vector a,Vector b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
Vector crossProduct(Vector a,Vector b){
    Vector ret;
    ret.x=a.y*b.z-a.z*b.y;
    ret.y=a.z*b.x-a.x*b.z;
    ret.z=a.x*b.y-a.y*b.x;
    return ret;
}
double angleCos(Vector a,Vector b){
    return dotProduct(a,b)/(a.norm()*b.norm());
}

bool overlap(Vector axis,Vector a,Vector b){
    return abs(angleCos(axis,a)-angleCos(axis,b))<EPSILON;
}

class Block
{
    public:
        int size;
        Vector vertices[NUM];
        bool isIntersect(Vector normal);
};
bool Block::isIntersect(Vector normal){
    bool flag=dotProduct(normal,this->vertices[0])>0?1:0;
    for (int i = 1; i < this->size; i++){
        if (flag!=dotProduct(normal,this->vertices[i])>0?1:0)return 1;
    }
    return 0;
}

void Search(){

}

void Init(){
    cin>>n;
    Block *blocks=new Block[n];
    for (int i = 0; i < n; i++){
        cin>>blocks[i].size;
        for (int j = 0; j < blocks[i].size; j++){
            blocks[i].vertices[j].get();
        }
    }
}

int main(){
    cout<<"start"<<endl;
    Init();
    return 0;
}
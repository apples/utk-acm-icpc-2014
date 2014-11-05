#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;
int main(){
ifstream in;
in.open("fun.in");
int W,L;
int num=0;
while(in>>W)
{
num++;
in>>L;
if(W==0&&L==0) break;
vector<string> house;
string str;
for(int i=0;i<L;i++)
{
in>>str;
house.push_back(str);
}
int x,y;
bool up=false;
bool down=false;
bool left=false;
bool right=false;
for(int i=0;i<W;i++){
if(house[0][i]=='*'){
y=0;
x=i;
down=true;
}
if(house[L-1][i]=='*'){
y=L-1;
up=true;
x=i;
}
}
for(int i=0;i<L;i++)
{
if(house[i][0]=='*'){
x=0;
right=true;
y=i;
}
if(house[i][W-1]=='*'){
x=W-1;
y=i;
left=true;
}
}
while(1){
if(down)y++;
if(up)y--;
if(right)x++;
if(left)x--;
if(house[y][x]=='x'){
house[y][x]='&';
break;

}
if(house[y][x]=='/'&&right){
right=false;
up=true;
}
else if(house[y][x]=='/'&&left){
left=false;
down=true;
}
else if(house[y][x]=='/'&&up){
right=true;
up=false;
}
else if(house[y][x]=='/'&&down){
down=false;
left=true;
}
else if(house[y][x]=='\\'&&right){
right=false;
down=true;
}
else if(house[y][x]=='\\'&&down){
down=false;
right=true;
}
else if(house[y][x]=='\\'&&left){
left=false;
up=true;
}
else if(house[y][x]=='\\'&&up){
up=false;
left=true;
}
}
cout<<"HOUSE "<<num<<"\n";
for(int i=0;i<L;i++)
{
cout<<house[i]<<"\n";
}
}
}
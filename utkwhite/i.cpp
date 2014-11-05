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
in.open("wet.in");
int X,Y,T,L,W;
while(in>>X){
vector<vector<int> > room;
if(X==-1)break;
in>>Y>>T>>L>>W;
room.clear();
room.resize(X);
for(int i=0;i<X;i++)
{
room[i].resize(Y);
}
for(int i=0;i<L;i++)
	{
	int x,y;
	in>>x>>y;
	x--;
	y--;
	room[x][y]=-2;
	}
	
for(int i=0;i<W;i++)
{
int x1,x2,y1,y2;
in>>x1>>y1>>x2>>y2;
x1--;
y1--;
y2--;
x2--;
room[x1][y1]=-1;
room[x2][y2]=-1;
bool dif= (abs(x1-x2)==abs(y2-y1));
if(x1==x2&&y1==y2){
int cant_think_ont=0;
}
else if(!dif){ 
	if(x1==x2){
	
	for(int y=min(y1,y2);y<max(y1,y2);y++)
		room[x1][y]=-1;	
		}
	if(y1==y2){
	
	for(int x=min(x1,x2);x<max(x1,x2);x++)
		room[x][y1]=-1;	
		}

}
else{
int x_dir=(x1-x2)/abs(x1-x2);
int y_dir=(y1-y2)/abs(y1-y2);
int lenj=abs(x1-x2);
for(int q=0;q<lenj;q++)
	{
	room[x1-x_dir*q][y1-y_dir*q]=-1;
	}

}

}
vector<pair<int,int> > visisted;
int wet_spots=L;
for(int x=0;x<X;x++)
	for(int y=0;y<Y;y++)
	{	
	if(room[x][y]==-2 &&x!=X-1&&room[x+1][y]==0)
	{
	room[x+1][y1]=1;
	visisted.push_back(pair<int,int>{x+1,y});
	wet_spots++;
	}
	
	if(room[x][y]==-2 &&x!=0&&room[x-1][y]==0)
	{
	
	room[x-1][y1]=1;
	visisted.push_back(pair<int,int>{x-1,y});
	wet_spots++;
	}
	if(room[x][y]==-2 &&y!=0&&room[x][y-1]==0)
	{
	
	room[x][y-1]=1;
	visisted.push_back(pair<int,int>{x,y-1});
	wet_spots++;
	}
	if(room[x][y]==-2 &&y!=Y-1&&room[x][y+1]==0)
	{
	room[x][y+1]=1;
	visisted.push_back(pair<int,int>{x,y-1});
	wet_spots++;
	}
	

	}

while(!visisted.empty())
{
int x=visisted[0].first;
int y=visisted[0].second;
visisted.erase(visisted.begin());
	if(x!=X-1&&room[x+1][y]==0)
	{
	room[x+1][y]=1;
	visisted.push_back(pair<int,int>{x+1,y});
	wet_spots++;
	}
	
	if(x!=0&&room[x-1][y]==0)
	{
	
	room[x-1][y]=1;
	visisted.push_back(pair<int,int>{x-1,y});
	wet_spots++;
	}
	if(y!=0&&room[x][y-1]==0)
	{
	
	room[x][y-1]=1;
	visisted.push_back(pair<int,int>{x,y-1});
	wet_spots++;
	}
	if(y!=Y-1&&room[x][y+1]==0)
	{
	room[x][y+1]=1;
	visisted.push_back(pair<int,int>{x,y-1});
	wet_spots++;
	}
}	
cout<<wet_spots<<endl;
}
}



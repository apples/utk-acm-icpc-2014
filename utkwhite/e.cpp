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
in.open("cloud.in");
int cl_num=0;
int W,N;
while(in>>W)
{
cl_num++;
in>>N;
vector<string> words;
vector<int> freq;
vector<int> width;
freq.resize(N);
words.resize(N);
width.resize(N);
if(W==0&&N==0)break;
string str;
int num;
for(int i=0;i<N;i++)
{
in>>str;
words[i]=str;
in>>num;
freq[i]=num;
}
int c_max=0;
for(int i=0;i<N;i++)
if(freq[i]>c_max)c_max=freq[i];

for(int i=0;i<N;i++)
{
 double poop=(40*(freq[i]-4));
 double but=(c_max-4);
int P=8+ceil(poop/but);
double asdf=16;
double asdff=(9*words[i].size()*P);
width[i]=ceil(asdff/asdf);
}
int w_counter=0;
int height_total=0;
int max_height=0;
for(int i=0;i<N;i++)
{
if(W<(w_counter+width[i])){
height_total+=max_height;
max_height=0;
w_counter=0;
}
 double poop=(40*(freq[i]-4));
 double but=(c_max-4);
int P=8+ceil(poop/but);
if(P>max_height){
max_height=P;
}
w_counter+=width[i]+10;


}
height_total+=max_height;
cout<<"CLOUD "<<cl_num<<": "<<height_total<<"\n";
}


}
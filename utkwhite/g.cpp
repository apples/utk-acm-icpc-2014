#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
int main(){
ifstream in;
in.open("rot.in");
int r;
string str;
vector<char> alph;
alph.resize(28);
for(int i=0;i<26;i++)alph[i]='A'+i;
alph[26]='_';
alph[27]='.';
while(in>>r)
{
if(r==0)break;
in>>str;
string new_str=str;
for(int i=0;i<str.size();i++)
{
int index =str[i]-'A'+r;
if(str[i]=='_')index=26+r;
if(str[i]=='.')index=27+r;

index=index%28;
new_str[new_str.size()-i-1]=alph[index];
}
cout<<new_str<<"\n";

}

}
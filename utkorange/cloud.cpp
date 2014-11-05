#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

struct Word {
	string letters;
	int numletters;
	int count;
	int height;
	int width;
	
	void setwidth() {
		double temp = (9.0/16.0)*numletters*height;
		width = ceil(temp);
	}
	
	void setheight(vector<Word>& vec, int maxcount) {
		double temp = 8 + (double(40*(count-4))/double(maxcount-4));
		height = ceil(temp);
	}
};

int main() {
	int W;
	int N;
	
	ifstream in ("cloud.in");
	
	vector<Word> vec;
	vector<int> count;
	vector<int> lineheight;
	vector<vector<Word>> lines;
	
	int cloud = 0;
	
	while ((in >> W >> N) && (W!=0 && N!=0)) {
	
		++cloud;
		
		vec.clear();
		vec.resize(N);
		
		count.clear();
		count.resize(N);
		
		for (int i=0; i<N; ++i) {
			in >> vec[i].letters >> vec[i].count;
			
			vec[i].numletters = vec[i].letters.size();
			count[i] = vec[i].count;
		}
		
		int maxcount = *max_element(begin(count),end(count));
		
		for (int i=0; i<N; ++i) {
			vec[i].setheight(vec,maxcount);
			vec[i].setwidth();
		}
		
		int maxheight = 0;
		int runwidth = 0;
		
		lineheight.clear();
		
		lines.clear();
		lines.resize(1);
		
		for (Word& w : vec) {
			if (runwidth > 0) {
				runwidth += 10;
			}
			runwidth += w.width;
			if (runwidth > W) {
				lines.push_back(vector<Word>{});
				runwidth = w.width;
			}
			lines.back().push_back(w);
		}
		
		for (auto& line : lines) {
			int mx = 0;
			for (auto& w : line) {
				mx = max(mx,w.height);
			}
			lineheight.push_back(mx);
		}
		
		#if 0
		
		for (int i=1; i<N; ++i) {
			if (((runwidth+10+vec[i].width) > W)) {
				cout << endl;
				lineheight.push_back(maxheight);
				runwidth = vec[i].width;
				maxheight = vec[i].height;
				cout << vec[i].letters << " " << vec[i].height;
			} else {
				runwidth += (10 + vec[i].width);
				if (vec[i].height > maxheight) {
					maxheight = vec[i].height;
				}
				cout << " " << vec[i].letters << " " << vec[i].height;
			}
			if (i==N-1 && runwidth == vec[i].width) {
				cout << vec[i].letters << " " << vec[i].height;
				lineheight.push_back(maxheight);
			}
		}
		cout << endl;
		
		#endif
		
		int sum = accumulate(begin(lineheight),end(lineheight),0);
		
		cout << "CLOUD " << cloud << ": " << sum << endl;
	}
}

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

enum Cardinal : unsigned {
	WEST,
	SOUTH,
	EAST,
	NORTH,
};

Cardinal flip(Cardinal c) {
	switch (c) {
		case WEST: return EAST;
		case EAST: return WEST;
		case NORTH: return SOUTH;
		case SOUTH: return NORTH;
	}
}

struct Cell {
	int r = -1;
	int c = -1;
	char ch = 'X';
	
	vector<Cell*> neighbors;
	bool visited = false;
	bool outside = false;
	
	Cell() {
		neighbors.reserve(4);
	}
};

struct Results {
	bool path_found = false;
	bool loop_found = false;
};

Results operator||(Results r1, Results const& r2) {
	r1.path_found = (r1.path_found || r2.path_found);
	r1.loop_found = (r1.loop_found || r2.loop_found);
	return r1;
}

Results explore(Cell* cell, Cell* from) {
	Results res;
	
	if (cell->visited) {
		if (!from->outside) {
			if (!cell->outside) {
				res.loop_found = true;
				#ifdef PRINT_JUNK
				cout << "Loop found at " << cell->r << "," << cell->c << endl;
				cout << "    From " << from->r << "," << from->c << endl;
				#endif
			} else {
				res.path_found = true;
				#ifdef PRINT_JUNK
				cout << "Path found from " << from->r << "," << from->c << endl;
				#endif
			}
		}
		return res;
	}
	
	#ifdef PRINT_JUNK
	cout << "Visiting " << cell->r << "," << cell->c << endl;
	#endif
	
	cell->visited = true;
	
	for (auto nbor : cell->neighbors) {
		if (nbor != from) {
			auto r = explore(nbor, cell);
			res = (res || r);
		}
	}
	
	return res;
}

int main() {
	int H;
	int W;
	
	string str;
	
	Cell outside;
	outside.outside = true;
	vector<Cell> cells;
	
	ifstream in ("maze.in");
	
	auto cellat = [&](int r, int c) -> Cell& {
		if (r<0 || r>=H || c<0 || c>=W) {
			return outside;
		}
		return cells[r*W+c];
	};
	
	auto char2int = [](char c){
		unsigned rv = 0;
		if (c >= '0' && c <= '9') {
			rv = c-'0';
		} else {
			rv = (c-'A')+10;
		}
		return rv;
	};
	
	auto modr = [](int r, int dir) {
		switch (dir) {
			case 0: return r;
			case 2: return r;
			case 3: return r-1;
			case 1: return r+1;
		}
	};
	
	auto modc = [](int c, int dir) {
		switch (dir) {
			case 0: return c-1;
			case 2: return c+1;
			case 3: return c;
			case 1: return c;
		}
	};
	
	while ((in >> H >> W) && W!=0) {
		cells.clear();
		cells.resize(W*H);
		outside.neighbors.clear();
		outside.visited = false;
		
		for (int r=0; r<H; ++r) {
			in >> str;
			for (int c=0; c<W; ++c) {
				unsigned x = char2int(str[c]);
				auto& c1 = cellat(r,c);
				c1.r = r;
				c1.c = c;
				c1.ch = str[c];
				for (unsigned i=0; i<4; ++i) {
					if (((x >> i) & 1u) == 0u) {
						auto& c2 = cellat(modr(r,i),modc(c,i));
						c1.neighbors.push_back(&c2);
						if (c2.outside) {
							c2.neighbors.push_back(&c1);
						}
					}
				}
			}
		}
		
		
	#ifdef PRINT_JUNK
		for (auto& c : cells) {
			cout << "Cell " << c.ch << " " << c.r << "," << c.c << ":" << endl;
			for (auto cp : c.neighbors) {
				cout << "    " << cp->r << "," << cp->c << endl;
			}
		}
	#endif
	
		auto res = explore(&outside, nullptr);
		
		auto iter = find_if(begin(cells),end(cells),[](Cell const& cell){
			return !cell.visited;
		});
		
		bool unreachables = (iter != end(cells));
		
		if (!res.path_found) {
			cout << "NO SOLUTION" << endl;
		} else if (unreachables) {
			cout << "UNREACHABLE CELL" << endl;
		} else if (res.loop_found) {
			cout << "MULTIPLE PATHS" << endl;
		} else {
			cout << "MAZE OK" << endl;
		}
	}
}

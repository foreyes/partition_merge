#ifndef MERGE_HPP_
#define MERGE_HPP_

#include <queue>
#include "partition.hpp"
using namespace std;

class LoserTree{
public:
	LoserTree(vector<Partition*> parts, int result_block_size = 128):
		parts(parts), 
		result_block_size(result_block_size){
		for(int i = 0;i < parts.size();i++){
			int x;
			if(parts[i]->get_next(x)){
				q.push(make_pair(-x, i));
			}
		}
		result = new Partition();
	}
	bool get_loser(int &x){
		if(q.empty()) return false;
		pair<int, int> result = q.top();q.pop();
		x = result.first * -1;
		int p = result.second, tmp;
		if(parts[p]->get_next(tmp)){
			q.push(make_pair(-tmp, p));
		}
		return true;
	}
	Partition* merge(){
		int x;
		while(get_loser(x)){
			result->add_number(x, result_block_size);
		}
		return result;
	}
private:
	int result_block_size;
	vector<Partition*> parts;
	Partition *result;
	priority_queue<pair<int, int> > q;
};

#endif
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "partition.hpp"
#include "merge.hpp"

using namespace std;

void test(){
	srand(2140506);
	Partition p[5];
	vector<Partition*> data;
	vector<int> nums;
	for(int i = 0;i < 200;i++) nums.push_back(rand()%100);
	sort(nums.begin(),nums.end());
	int cnt = 0;

	for(int i = 0;i < 20;i++){
		for(int j = 0;j < 5;j++){
			p[j].add_number(nums[cnt++], 5);
		}
	}
	for(int i = 0;i < 5;i++){
		data.push_back(&p[i]);
		p[i].output();
	}
	LoserTree test(data);
	test.merge()->output();
}

int main(){
	test();
	return 0;
}
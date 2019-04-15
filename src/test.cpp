#include <iostream>
#include <vector>
#include "partition.h"

using namespace std;

int main(){
	vector<DataBlock*> nums;
	vector<int> a = {1, 2, 3, 4};
	DataBlock *tmp = new DataBlock(a);
	DataBlock *tmp2 = new DataBlock(a);
	nums.push_back(tmp);
	nums.push_back(tmp2);
	Partition test(nums);
	test.output();
	return 0;
}
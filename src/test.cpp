#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "partition.hpp"
#include "merge.hpp"

using namespace std;

void test(){
	//test data generat
	srand(41241);
	Partition p[5];
	vector<Partition*> data;
	vector<int> nums;
	for(int i = 0;i < 200;i++) nums.push_back(rand()%10000);
	sort(nums.begin(),nums.end());
	int cnt = 0;

	for(int i = 0;i < 20;i++){
		for(int j = 0;j < 5;j++){
			p[j].add_number(nums[cnt++], 5);
		}
	}

	//Output and merge test
	for(int i = 0;i < 5;i++){
		data.push_back(&p[i]);
		cout<<"Partition "<<i<<": ";
		p[i].output();
	}
	cout<<endl;
	cout<<"After merge:"<<endl;
	LoserTree test(data);//data is a vector of Partition pointers
	test.merge()->output();
}

int main(){
	test();
	return 0;
}
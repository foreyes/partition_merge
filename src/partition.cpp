#include <iostream>
#include <vector>
#include "partition.h"

DataBlock::DataBlock(std::vector<int> &data){
	num_size = data.size();
	nums = data;
}

void DataBlock::output(){
	for(auto x: nums){
		std::cout<<x<<" ";
	}
}

Partition::Partition(std::vector<DataBlock*> &blocks){
	num_size = 0;
	head = blocks[0];
	DataBlock *previous = nullptr;
	for(DataBlock* item: blocks){
		num_size += item->num_size;
		if(previous != nullptr){
			previous->next = item;
		}
		previous = item;
	}
	previous->next = nullptr;
}

void Partition::output(){
	DataBlock *cur = head;
	while(cur != nullptr){
		cur->output();
		cur = cur->next;
	}
	std::cout<<std::endl;
}
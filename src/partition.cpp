#include <iostream>
#include <vector>
#include "partition.h"

DataBlock::DataBlock(std::vector<int> data){
	nums = data;
}

int DataBlock::get_size(){
	return nums.size();
}

void DataBlock::output(){
	for(auto x: nums){
		std::cout<<x<<" ";
	}
}

Partition::Partition(std::vector<DataBlock*> blocks){
	num_size = 0;
	head = blocks[0];
	DataBlock *previous = nullptr;
	for(DataBlock* item: blocks){
		num_size += item->get_size();
		if(previous != nullptr){
			previous->next = item;
		}
		previous = item;
	}
	previous->next = nullptr;
	cur_pos = 0;
	cur_block = head;
}

int Partition::get_size(){
	return num_size;
}

bool Partition::get_next(int &x){
	while(cur_pos >= cur_block->get_size()){
		if(cur_block == tail) return false;
		cur_block = cur_block->next;
		cur_pos = 0;
	}
	x = cur_block->nums[cur_pos];
	cur_pos++;
	return true;
}

void Partition::reset(){
	cur_block = head;
	cur_pos = 0;
}

void Partition::add_number(int x, int block_size = 128){
	if(tail->get_size() >= block_size){
		tail->next = new DataBlock(std::vector<int>());
		tail = tail->next;
	}
	tail->nums.push_back(x);
	num_size++;
}

void Partition::output(){
	DataBlock *cur = head;
	while(cur != nullptr){
		cur->output();
		cur = cur->next;
	}
	std::cout<<std::endl;
}
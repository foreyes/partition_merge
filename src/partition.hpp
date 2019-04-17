#ifndef PARTITION_HPP_
#define PARTITION_HPP_

#include <iostream>
#include <vector>

struct DataBlock{
	std::vector<int> nums;
	DataBlock *next;

	DataBlock(std::vector<int> data){
		nums = data;
		next = nullptr;
	}
	int get_size(){
		return nums.size();
	}
	void output(){
		for(auto x: nums){
			std::cout<<x<<" ";
		}
	}
};

class Partition{
public:
	//Construct a empty Partition
	Partition(){
		head = tail = cur_block = nullptr;
		num_size = cur_pos = 0;
	}

	//Construct a Partition from some data blocks
	Partition(std::vector<DataBlock*> blocks){
		head = cur_block = blocks[0];
		tail = blocks[blocks.size()-1];
		num_size = cur_pos = 0;
		DataBlock *previous = nullptr;
		for(DataBlock* item: blocks){
			num_size += item->get_size();
			if(previous != nullptr){
				previous->next = item;
			}
			previous = item;
		}
		previous->next = nullptr;
	}

	int get_size(){
		return num_size;
	}

	//Get next value, and move forward
	bool get_next(int &x){
		if(cur_block == nullptr) return false;
		while(cur_pos >= cur_block->get_size()){
			if(cur_block == tail) return false;
			cur_block = cur_block->next;
			cur_pos = 0;
		}
		x = cur_block->nums[cur_pos];
		cur_pos++;
		return true;
	}

	//Reset the current point to the front
	void reset(){
		cur_block = head;
		cur_pos = 0;
	}

	//Add a number to the end of this Partition, with the given max data block size
	void add_number(int x, int block_size = 128){
		if(tail == nullptr){
			cur_block = head = tail = new DataBlock(std::vector<int>());
		} else if(tail->get_size() >= block_size){
			tail->next = new DataBlock(std::vector<int>());
			tail = tail->next;
		}
		tail->nums.push_back(x);
		num_size++;
	}

	//Output the whole Partition, blocks are separated by ' | '
	void output(){
		DataBlock *cur = head;
		while(cur != nullptr){
			cur->output();
			std::cout<<" | ";
			cur = cur->next;
		}
		std::cout<<std::endl;
	}
	
private:
	int num_size, cur_pos;
	DataBlock *head;
	DataBlock *tail;
	DataBlock *cur_block;
};

#endif
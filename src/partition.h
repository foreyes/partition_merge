#ifndef PARTITION_H
#define PARTITION_H

#include <vector>

struct DataBlock{
	std::vector<int> nums;
	DataBlock *next;

	DataBlock(std::vector<int> data);
	int get_size();
	void output();
};

class Partition{
public:
	Partition(std::vector<DataBlock*> blocks);
	int get_size();
	bool get_next(int &x);
	void reset();
	void add_number(int x, int block_size);
	void output();
private:
	int num_size, cur_pos;
	DataBlock *head;
	DataBlock *tail;
	DataBlock *cur_block;
};

#endif
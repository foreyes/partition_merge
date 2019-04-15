#ifndef PARTITION_H
#define PARTITION_H

#include <vector>

struct DataBlock{
	int num_size;
	std::vector<int> nums;
	DataBlock *next;

	DataBlock(std::vector<int> &data);
	void output();
};

class Partition{
public:
	int num_size;
	DataBlock *head;

	Partition(std::vector<DataBlock*> &blocks);
	void output();
};

#endif
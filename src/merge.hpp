#ifndef MERGE_HPP_
#define MERGE_HPP_

#include <queue>
#include <cassert>
#include "partition.hpp"
using namespace std;

struct LoserNode{
	bool available;
	pair<int, int> loser;
	pair<int, int> winner;
	LoserNode *left;
	LoserNode *right;
	LoserNode *parent;

	//Constructor of Loser Node
	LoserNode(LoserNode *left = nullptr, LoserNode *right = nullptr): 
		left(left), right(right){
		if(left != nullptr) left->parent = this;
		if(right != nullptr) right->parent = this;
		available = false;
		parent = nullptr;
	}
};

class LoserTree{
public:
	//Constructor, takes vector of Partition pointers and default data block size as arguments.
	LoserTree(vector<Partition*> parts, int result_block_size = 128):
		parts(parts), 
		result_block_size(result_block_size){
		assert(parts.size() > 1);

		fetch = vector<LoserNode*>(parts.size(), nullptr);
		queue<LoserNode*> q;
		for(int i = 0;i < parts.size();i++){
			int x;
			if(!parts[i]->get_next(x)) continue;
			LoserNode *cur = new LoserNode();
			cur->available = true;
			cur->winner = make_pair(x, i);
			fetch[i] = cur;
			q.push(cur);
		}
		while(!q.empty()){
			LoserNode *left = q.front();q.pop();
			if(q.empty()){
				root = left;
				break;
			}
			LoserNode *right = q.front();q.pop();
			LoserNode *cur = new LoserNode(left, right);
			q.push(cur);
		}
		build(root);
		result = new Partition();
	}

	//Build up the whole Loser Tree
	void build(LoserNode *cur){
		if(cur->available) return;
		build(cur->left);
		build(cur->right);
		cur->available = true;
		cur->winner = cur->left->winner;
		cur->loser = cur->right->winner;
		if(cur->winner.first > cur->loser.first){
			swap(cur->winner, cur->loser);
		}
	}

	//Update competition informations after get_loser()
	void update(LoserNode *cur){
		if(cur->parent == nullptr) return;
		if(cur->winner.first > cur->parent->loser.first){
			cur->parent->winner = cur->parent->loser;
			cur->parent->loser = cur->winner;
		} else {
			cur->parent->winner = cur->winner;
		}
		update(cur->parent);
	}

	//Erase a leaf node from the tree
	void erase(LoserNode *cur){
		if(cur->parent == nullptr){
			cur->available = false;
			return;
		}
		LoserNode *brother;
		if(cur == cur->parent->left){
			brother = cur->parent->right;
		} else {
			brother = cur->parent->left;
		}
		brother->parent = cur->parent->parent;
		if(brother->parent == nullptr){
			root = brother;
		} else {
			if(brother->parent->left == cur->parent){
				brother->parent->left = brother;
			} else{
				brother->parent->right = brother;
			}
		}
		update(brother);
	}

	//Get the loser value, and updata competition
	bool get_loser(int &x){
		if(!root->available) return false;
		x = root->winner.first;
		int idx = root->winner.second;
		int next_number;
		if(parts[idx]->get_next(next_number)){
			fetch[idx]->winner = make_pair(next_number, idx);
			update(fetch[idx]);
		} else {
			//delete
			erase(fetch[idx]);
		}
		return true;
	}

	//The merge sorting function
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
	vector<LoserNode*> fetch;
	Partition *result;
	LoserNode *root;
};


#endif
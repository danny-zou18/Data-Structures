/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <fstream>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template <class T>
class BPlusTree {
public:
	//Constructors
	BPlusTree(int s) : root(NULL), size(s) {};
	BPlusTree(const BPlusTree<T>& old);
	~BPlusTree(); //Deconstructors

	//Accessors
	BPlusTreeNode<T>* find(const T& value) const;
	void print_sideways(std::ostream out) const;
	void print_BFS(std::ostream out) const;
	int get_size() const {return size;}

	//Modifiers
	void insert(const T& key);
	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* new_root) ;
	void destroy_tree(BPlusTreeNode<T>* root);
	void sort_keys(BPlusTreeNode<T>*& pos);
	void split(const T& value, BPlusTreeNode<T>* pos);

private:
	BPlusTreeNode<T>* root;
	unsigned int size;
};
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& old){
	size = old.get_size();
	root = copy_tree(old.root,nullptr);
}
template <class T>
BPlusTree<T>::~BPlusTree(){
	destroy_tree(root);
	root = nullptr;
}
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& value) const {
	if (root == nullptr){
		return nullptr;
	}
	BPlusTreeNode<T>* temp = root;
	while (!temp->is_leaf()){
		for (unsigned int i = 0; i < temp->keys.size(); i++){
			if (value < (temp->keys)[i]){
				return (temp->children)[i];
			}
		}
		unsigned int next_index = temp->keys.size() - 1;
		if (value > temp->keys[next_index]){
			temp = temp->children[temp->keys.size()];
		}
	}
	return temp;
}
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* parentNode){
	if (old_root == nullptr){
		return nullptr;
	}
	BPlusTreeNode<T>* tempNode = new BPlusTreeNode<T>();
	tempNode->keys = old_root->keys;
	tempNode->parent = parentNode;

	for (unsigned int i = 0; i < (old_root->children).size(); i++){
		BPlusTreeNode<T>* new_child = copy_tree((old_root->children)[i], tempNode);
		tempNode->children.push_back(new_child);
	}
	return tempNode;
}
template <class T>
void BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* root){
	if (root == nullptr){
		return;
	}
	for (unsigned int i = 0; i < (root->children).size(); i++){
		destroy_tree(root->children[i]);
	}
	delete root;
}

template <class T>
void BPlusTree<T>::sort_keys(BPlusTreeNode<T>*& pos) {
	unsigned int key_size = pos->keys.size();
	for (unsigned int i; i < key_size - 1; i++){
		for (unsigned int j = i + 1; j < key_size; j++){
			if (pos->keys[j] < pos->keys[i]){
				if (j != i){
					T temp = pos->keys[i];
					pos->keys[i] = pos->keys[j];
					pos->keys[j] = temp;
					break;
				}
			}
		}
	}
}
template <class T>
void BPlusTree<T>::split(const T& value, BPlusTreeNode<T>* pos){
	BPlusTreeNode<T>* new_node1 = new BPlusTreeNode<T>();
	BPlusTreeNode<T>* new_node2 = new BPlusTreeNode<T>();
	
	for (unsigned int i = 0; i < size; i++){
		new_node1->children.push_back(nullptr);
		new_node2->children.push_back(nullptr);
		if (i < size/2){
			new_node1->keys.push_back(pos->keys[i]);
		} else {
			new_node2->keys.push_back(pos->keys[i]);
		}
	}
	if (pos->children[0] == nullptr && pos->children[1] == nullptr 
		&& pos->children[2] == nullptr && pos->parent == nullptr){
			BPlusTreeNode<T>* top_node = new BPlusTreeNode<T>;
			top_node->children.push_back(nullptr);
			top_node->children.push_back(nullptr);
			top_node->keys.push_back(pos->keys[size/2]);
			top_node->children[0] = new_node1;
			top_node->children[1] = new_node2;
			new_node1->parent = top_node;
			new_node2->parent = top_node;
			pos->keys = top_node->keys;
			pos->children = top_node->children;
	} else if (pos->parent == nullptr){
			BPlusTreeNode<T>* top_node = new BPlusTreeNode<T>;
			top_node->children.push_back(nullptr);
			top_node->children.push_back(nullptr);
			top_node->keys.push_back(pos->keys[size-1]);
			BPlusTreeNode<T>* temp = new BPlusTreeNode<T>;
			temp->keys.push_back(new_node1->keys[0]);
			temp->parent = new_node1;
			new_node1->children[0] = pos->children[0];
			new_node1->children[1] = temp;
			new_node2->children[0] = pos->children[1];
			new_node2->children[1] = pos->children[2];
			top_node->children[0] = new_node1;
			top_node->children[1] = new_node2;
			pos->keys = top_node->keys;
			pos->children = top_node->children;
			new_node1->parent = top_node;
			new_node2->parent = top_node;
	} else {
		pos->parent->keys.push_back(pos->keys[size/2]);
		new_node1->parent = pos->parent;
		new_node2->parent = pos->parent;
		pos->keys = pos->parent->keys;
		pos->parent->children[1] = new_node1;
		pos->parent->children[2] = new_node2;
	}
}
template <class T>
void BPlusTree<T>::insert(const T& value) {
	if (root != nullptr){
		BPlusTreeNode<T>* pos = find(value);
		pos->keys.push_back(value);
		sort_keys(pos);
		if (pos->keys.size() >= size){
			split(value, pos);
		}
	} else {
		root = new BPlusTreeNode<T>;
		for (unsigned int i = 0; i < size; i++){
			root->children.push_back(nullptr);
		}
		root->keys.push_back(value);
	}
}
#endif

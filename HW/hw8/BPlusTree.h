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
	void print_sideways(std::ostream& out) const;
	void print_BFS(std::ostream& out) const;
	int get_size() const {return size;}

	//Modifiers
	void insert(const T& key);
	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* new_root) ;
	void destroy_tree(BPlusTreeNode<T>* root);
	void sort_keys(BPlusTreeNode<T>*& pos);
private:
	BPlusTreeNode<T>* root;
	unsigned int size;
	void print_sideways(std::ostream& out, BPlusTreeNode<T>* p, unsigned int level) const;
	void seperate(BPlusTreeNode<T>*& split_node);
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
	BPlusTreeNode<T>* pos = root;
	while (!pos->is_leaf()){
		for (unsigned int i = 0; i < pos->keys.size();i++){
			if (value < pos->keys[i]){
				BPlusTreeNode<T>* temp = pos->children[i];
				if (temp->is_leaf()){
					return temp;
				}
			}
		}
		if (value > pos->keys[size-2]){
			pos = pos->children[size-1];
		}
	}
	return pos;
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
	for (unsigned int i = 0; i < key_size - 1; i++){
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
void BPlusTree<T>::insert(const T& value) {
	if (root != nullptr){
		BPlusTreeNode<T>* insert_node = find(value);
		if (insert_node->keys.size() >= size){
			seperate(insert_node);
		} else {
			insert_node->keys.push_back(value);
			sort_keys(insert_node);
		}
	} else {
		root = new BPlusTreeNode<T>;
		for (unsigned int i = 0;i < size; i++){
			root->children.push_back(nullptr);
		}
		root->keys.push_back(value);
		return;
	}
}
template <class T>
void BPlusTree<T>::print_sideways(std::ostream& out, BPlusTreeNode<T>* pos, unsigned int level) const {
	 if (root == NULL) {
        out << "Tree is empty." << std::endl;
        return;
    }
    unsigned int left = pos->children.size() / 2;
    unsigned int right = pos->children.size() - left;
    
    for (unsigned int i = 0; i < left; ++i){
        print_sideways(out, pos->children[i], level + 1);
	}
    for (unsigned int i = 0; i < level; ++i) {
		out << '\t';
	}
    out << pos->keys[0];
    for (unsigned int i = 1; i < pos->keys.size(); ++i) {
		out << ',' << pos->keys[i];
	}
    out << std::endl;
    for (unsigned int i = left; i < left + right; ++i){
        print_sideways(out, pos->children[i], level + 1);
	}
}
template <class T>
void BPlusTree<T>::print_sideways(std::ostream& out) const {
	print_sideways(out, root, 0);
}
template <class T>
void BPlusTree<T>::print_BFS(std::ostream& out) const {
    // Check: If tree is empty
    if (root == NULL) {
        out << "Tree is empty." << std::endl;
        return;
    }
    
    // Initialize a FIFO queue
    std::vector<BPlusTreeNode<T>*> queue;
    queue.push_back(root);
    std::vector<int> levels;
    levels.push_back(0);
    
    int last_level = 0;
    while (queue.size() != 0) {
        // get and remove the first element from queue
        BPlusTreeNode<T>* current(queue.front());
        queue.erase(queue.begin());
        int level(levels.front());
        levels.erase(levels.begin());
        
        //spacing
        if (level == last_level && level > 0) out << '\t';
        else if (level != last_level) out << std::endl;
        
        // print key vector
        out << current->keys[0];
        for (unsigned int i = 1; i < current->keys.size(); ++i)
            out << ',' << current->keys[i];
        
        // append current node's children to queue
        for (unsigned int i = 0; i < current->children.size(); ++i) {
            queue.push_back(current->children[i]);
            levels.push_back(level + 1);
        }
        
        last_level = level;
    }
    out << std::endl;
}
template <class T>
void BPlusTree<T>::seperate(BPlusTreeNode<T>*& split_node) {
	if (split_node->parent == nullptr && split_node->children[0] == nullptr){
		BPlusTreeNode<T>* node1 = new BPlusTreeNode<T>;
		BPlusTreeNode<T>* node2 = new BPlusTreeNode<T>;
		BPlusTreeNode<T>* new_root = new BPlusTreeNode<T>;
		node1->parent = new_root;
		node2->parent = new_root;
		new_root->keys.push_back(split_node->keys[size/2]);
		new_root->children[0] = node1;
		new_root->children[1] = node2;
		split_node = new_root;
	} else if (split_node->is_leaf()){
		unsigned int split_index = split_node->keys.size() / 2;
		std::vector<T> to_be_moved;
		for (unsigned int i = 0; i < split_index; i++){
			to_be_moved.push_back(split_node->keys[i]);
		}
		BPlusTreeNode<T>* new_node = new BPlusTreeNode<T>;
		BPlusTreeNode<T>* temp_node = new BPlusTreeNode<T>;
		for (unsigned int i = 0; i < to_be_moved.size(); i++){
			new_node->keys.push_back(to_be_moved[i]);
		}
		split_node->parent->keys.push_back(split_node->keys[split_index]);
		for (unsigned int i = to_be_moved.size(); i < split_node->keys.size(); i++){
			temp_node->keys.push_back(split_node->keys[i]);
		}
		unsigned int insert_index = split_node->parent->children.size();
		
		split_node->parent->children[insert_index-2] = new_node;
		split_node->parent->children[insert_index-1] = temp_node;
		if (split_node->parent->keys.size() >= size){
			seperate(split_node->parent);
		}
		if (split_node->parent->children[insert_index-2]->keys.size() >= size){
			seperate(split_node->parent->children[insert_index-2]);
		}
	} else if (split_node->parent == nullptr){
		BPlusTreeNode<T>* node1 = new BPlusTreeNode<T>;
		BPlusTreeNode<T>* node2 = new BPlusTreeNode<T>;
		BPlusTreeNode<T>* new_root = new BPlusTreeNode<T>;
		node1->keys.push_back(split_node->keys.front());
		node2->keys.push_back(split_node->keys.back());
		unsigned int split_children = split_node->children.size() / 2;
		unsigned int split_children2 = split_node->children.size() - split_children;
		for (unsigned int i = 0; i < split_children; i++){
			node1->children[i] = split_node->children[i];
			split_node->children[i]->parent = node1;
		}
		for (unsigned int i = 0; i < split_children2; i++){
			unsigned int temp = split_children + i;
			node2->children[i] = split_node->children[temp];
			split_node->children[temp]->parent = node2;
		}
		new_root->children[0] = node1;
		new_root->children[1] = node2;
		node1->parent = new_root;
		node2->parent = new_root;
		split_node = new_root;
	}
}
#endif

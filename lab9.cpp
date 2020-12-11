#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
struct data
{
	T value;
};

template <typename T>
struct AVL_tree_node
{
	T value ;
	unsigned short int height = 0;
	AVL_tree_node* right;
	AVL_tree_node* left;
};

template <typename T>
struct Print_it
{
	T value;
	int level;
};

template <typename T>
void constructor_tree(AVL_tree_node<T>* p, data<T> n)
{
	p->left = nullptr;
	p->right = nullptr;
	p->height = 1;
	p->value = n.value;
}

template <typename T>
unsigned short int height_of(AVL_tree_node<T>* p)
{
	if (p == nullptr)
	{
		return 0;
	}
	else
	{
		return p->height;
	}
}

template <typename T>
int branch_dif(AVL_tree_node<T>* p)
{
	return height_of(p->right) - height_of(p->left);
}

template <typename T>
void set_height(AVL_tree_node<T>* p)
{
	if (height_of(p->left) > height_of(p->right))
	{
		p->height = height_of(p->left) + 1;
	}
	else
	{
		p->height = height_of(p->right) + 1;
	}
}

template <typename T>
AVL_tree_node<T>* rotate_right(AVL_tree_node<T>* p)
{
	AVL_tree_node<T>* q = p->left;
	p->left = q->right;
	q->right = p;
	set_height(p);
	set_height(q);
	return q;
}

template <typename T>
AVL_tree_node<T>* rotate_left(AVL_tree_node<T>* q)
{
	AVL_tree_node<T>* p = q->right;
	q->right = p->left;
	p->left = q;
	set_height(p);
	set_height(q);
	return p;
}

template <typename T>
AVL_tree_node<T>* balance(AVL_tree_node<T>* p)
{
	set_height(p);
	if (branch_dif(p) == 2)
	{
		if (branch_dif(p->right) < 0)
		{
			p->right = rotate_right(p->right);
		}
		return rotate_left(p);
	}
	if (branch_dif(p) == -2)
	{
		if (branch_dif(p->left) > 0)
		{
			p->left = rotate_left(p->left);
		}
		return rotate_right(p);
	}
	return p;
}

template <typename T>
AVL_tree_node<T>* insert(AVL_tree_node<T>* p, data<T> n)
{
	if (p == nullptr)
	{
		AVL_tree_node<T>* rez = new AVL_tree_node<T>;
		constructor_tree(rez, n);
		return rez;
	}
	if (n.value < p->value)
	{
		p->left = insert(p->left, n);
	}
	else
	{
		p->right = insert(p->right, n);
	}
	return balance(p);
}

template <typename T>
AVL_tree_node<T>* find_min_val(AVL_tree_node<T>* p)
{
	if (p->left == nullptr)
	{
		return p;
	}
	else
	{
		return find_min_val(p->left);
	}
}

template <typename T>
AVL_tree_node<T>* delete_min(AVL_tree_node<T>* p)
{
	if (p->left == nullptr)
	{
		return p->right;
	}
	p->left = delete_min(p->left);
	return balance(p);
}

template <typename T>
AVL_tree_node<T>* delete_node(AVL_tree_node<T>* p, data<T> n)
{
	if (p->height == 0)
	{
		std::cout << "Tree is empty" << std::endl;
		return 0;
	}
	if (n.value < p->value)
	{
		p->left = delete_node(p->left, n);
	}
	else if (n.value > p->value)
	{
		p->right = delete_node(p->right, n);
	}
	else
	{
		AVL_tree_node<T>* cur_left = p->left;
		AVL_tree_node<T>* cur_right = p->right;
		delete p;
		if (cur_right == nullptr)
		{
			return cur_left;
		}
		AVL_tree_node<T>* cur_min = find_min_val(cur_right);
		cur_min->right = delete_min(cur_right);
		cur_min->left = cur_left;
		return balance(cur_min);
	}
	return balance(p);
}

template <typename T>
void show_tree(AVL_tree_node<T>* p)
{
	if (p != nullptr)
	{
		std::vector<Print_it<T>> prints;
		show(p, 200, prints, 4);
		Print_it<T> line;
		line.value = -1;
		int lvl = height_of(p);
		int spaces = static_cast<int>(pow(2, (lvl - 1)));
		for (int i = lvl; i > 0; --i)
		{
			for (int j = 0; j < prints.size(); ++j)
			{
				if (prints[j].level == i)
				{
					for (int k = 0; k < spaces; ++k)
					{
						std::cout << " ";
					}
					if (prints[j].value == -1)
					{
						std::cout << "-";
					}
					else
					{
						std::cout << prints[j].value;
					}
					for (int k = 0; k < spaces - 1; ++k)
					{
						std::cout << " ";
					}
				}
			}
			spaces /= 2;
			std::cout << std::endl;
		}
	}
}

template <typename T>
void show(AVL_tree_node<T>* p, int k, std::vector<Print_it<T>>& prints, int cur_h)
{
	if (p != nullptr)
	{
		Print_it<T> n;
		if (k == 200)
		{
			n.level = height_of(p);
			n.value = p->value;
			prints.push_back(n);
			n.level = height_of(p) - 1;
			if (p->left != nullptr)
			{
				n.value = p->left->value;
			}
			else
			{
				n.value = -1;//заглушка
			}
			prints.push_back(n);
			if (p->right != nullptr)
			{
				n.value = p->right->value;
			}
			else
			{
				n.value = -1;//заглушка
			}
			prints.push_back(n);
			cur_h = height_of(p) - 1;
			show(p->left, 100, prints, cur_h - 1);
			show(p->right, 100, prints, cur_h - 1);
		}
		if (k == 100)
		{
			if ((p->left != nullptr) || (p->right != nullptr))
			{
				n.level = cur_h;
				if (p->left != nullptr)
				{
					n.value = p->left->value;
				}
				else
				{
					n.value = -1;//заглушка
				}
				prints.push_back(n);
				if (p->right != nullptr)
				{
					n.value = p->right->value;
				}
				else
				{
					n.value = -1;
				}
				prints.push_back(n);
				show(p->left, 100, prints, cur_h - 1);
				show(p->right, 100, prints, cur_h - 1);
			}
			else
			{
				n.level = cur_h;
				n.value = -1;
				prints.push_back(n);
				prints.push_back(n);
				show(p->left, 101, prints, cur_h - 1);
				show(p->right, 101, prints, cur_h - 1);
			}
		}
		
	}

}

template <typename T>
void destructor_tree(AVL_tree_node<T>* p)
{
	if (p != nullptr)
	{
		destructor_tree(p->left);
		destructor_tree(p->right);
		delete p;
	}
}

int main()
{
	//std::vector<Print_it<int>> prints;

	AVL_tree_node<int>* tree0 = new AVL_tree_node<int>;
	tree0 = nullptr;
	data<int> tmp;
	//constructor_tree(tree0);
	for (int i = 0; i < 10; ++i)
	{
		tmp.value = i;
		tree0 = insert(tree0, tmp);
	}
	show_tree(tree0);
	std::cout << std::endl << "-----------------" << std::endl;
	tmp.value = 3;
	tree0 = delete_node(tree0, tmp);
	tmp.value = 7;
	tree0 = delete_node(tree0, tmp);
	show_tree(tree0);
	destructor_tree(tree0);
	return 0;
}



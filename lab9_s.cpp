﻿#include <iostream>
#include <vector>
#define temp template <typename T>

temp
struct AVL_p
{
    AVL_p* left;
    AVL_p* right;
    unsigned short int height;
    T value;
};

temp
struct data
{
	T value;
};

temp
struct Print_it
{
    T value;
    int level;
};

temp
AVL_p<T>* construct(AVL_p<T>* p, T n)
{
    p->left = nullptr;
    p->right = nullptr;
    p->value = n;
    p->height = 1;
	return p;
}

temp
unsigned short int height_of(AVL_p<T>* p)
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

temp
int branch_dif(AVL_p<T>* p)
{
    return height_of(p->right) - height_of(p->left);
}

temp
AVL_p<T>* set_height(AVL_p<T>* p)
{
    if (branch_dif(p) < 0)
    {
        p->height = height_of(p->left) + 1;
    }
    else
    {
        p->height = height_of(p->right) + 1;
    }
	return p;
}

temp
AVL_p<T>* rotate_right_small(AVL_p<T>* p)
{
    AVL_p<T>* tmp = p->left;
    p->left = tmp->right;
    tmp->right = p;
    p = set_height(p);
    tmp = set_height(tmp);
    return tmp;
}

temp
AVL_p<T>* rotate_left_small(AVL_p<T>* p)
{
    AVL_p<T>* tmp = p->right;
    p->right = tmp->left;
    tmp->left = p;
    p = set_height(p);
    tmp = set_height(tmp);
    return tmp;
}

temp
AVL_p<T>* rotate_left_big(AVL_p<T>* p)
{
    AVL_p<T>* tmp_y = p->right;
    AVL_p<T>* tmp_z = tmp_y->left;
    p->right = tmp_z->left;
    tmp_y->left = tmp_z->right;
    tmp_z->left = p;
    tmp_z->right = tmp_y;
    p = set_height(p);
    tmp_y = set_height(tmp_y);
    tmp_z = set_height(tmp_z);
    return tmp_z;
}

temp
AVL_p<T>* rotate_right_big(AVL_p<T>* p)
{
    AVL_p<T>* tmp_y = p->left;
    AVL_p<T>* tmp_z = tmp_y->right;
    p->left = tmp_z->right;
    tmp_y->right = tmp_z->left;
    tmp_z->left = tmp_y;
    tmp_z->right = p;
    p = set_height(p);
    tmp_y = set_height(tmp_y);
    tmp_z = set_height(tmp_z);
    return tmp_z;
}

temp
AVL_p<T>* balance(AVL_p<T>* p)
{
    set_height(p);
    if (branch_dif(p) == 2)
    {
        if (branch_dif(p->right) < 0)
        {
            return rotate_left_big(p);
        }
        else
        {
            return rotate_left_small(p);
        }
    }
    if (branch_dif(p) == -2)
    {
        if (branch_dif(p->left) > 0)
        {
            return rotate_right_big(p);
        }
        else
        {
            return rotate_right_small(p);
        }
    }
	return p;
}

temp
AVL_p<T>* insert(AVL_p<T>* p, T n)
{
    if (p == nullptr)
    {
		AVL_p<T>* leaf = new AVL_p<T>;
		leaf = construct(leaf, n);
		return leaf;
    }
    if (p->value > n)
    {
        p->left = insert(p->left, n);
    }
	if (p->value < n)
	{
		p->right = insert(p->right, n);
	}
    return balance(p);
}

temp
void show_tree(AVL_p<T>* p)
{
	if (p != nullptr)
	{
		std::vector<Print_it<T>> prints;
		int lvl = height_of(p);
		show(p, 200, prints, lvl);
		Print_it<T> line;
		line.value = -1;

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

temp
AVL_p<T> find_max(AVL_p<T>* p)
{
	;
}

temp
void show(AVL_p<T>* p, int k, std::vector<Print_it<T>>& prints, int cur_h)
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

temp
void delete_tree(AVL_p<T>* p)
{
	if (p != nullptr)
	{
		delete_tree(p->left);
		delete_tree(p->right);
		delete p;
	}
}

int main()
{
	AVL_p<int>* tree0 = new AVL_p<int>;
	tree0 = nullptr;
	data<int> tmp;
	//constructor_tree(tree0);
	for (int i = 0; i < 10; ++i)
	{
		tmp.value = i;
		tree0 = insert(tree0, tmp.value);
	}
	show_tree(tree0);
	delete_tree(tree0);
}
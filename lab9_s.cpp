#include <iostream>
#include <vector>
#include <cmath>
#define temp template <typename T>

struct pair_temp
{
	int key;
	std::string value;
};

bool operator>(const pair_temp& left, const pair_temp& right)
{
	return left.key > right.key;
}

bool operator<(const pair_temp& left, const pair_temp& right)
{
	return left.key < right.key;
}

bool operator==(const pair_temp& left, const pair_temp& right)
{
	return left.key == right.key;
}

std::ostream& operator<<(std::ostream& out, const pair_temp& p)
{
	out << p.key;
	return out;
}

temp
struct AVL_p
{
    AVL_p* left;
    AVL_p* right;
    unsigned short int height;
    T value;
};

temp 
struct AVL_tree
{
	AVL_p<T>* root;
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
void consrtuct_tree(AVL_tree<T>& p)
{
	p.root = nullptr;
}

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
AVL_p<T>* balance(AVL_p<T>* p) // проверка на баланс и обновление высоты
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
void insert_tree(AVL_tree<T>& p, T value)
{
	p.root = insert(p.root, value);
}

temp
AVL_p<T>* find_max(AVL_p<T>* p)
{
	if (p->right != nullptr)
	{
		return find_max(p->right);
	}
	else
	{
		return p;
	}
}

temp
AVL_p<T>* find_prev_max(AVL_p<T>* p, AVL_p<T>* max)
{
	if (p == max)
	{
		return p;
	}
	if (p->right == max)
	{
		return p;
	}
	else
	{
		return find_prev_max(p->right, max);
	}
}

temp
AVL_p<T>* delete_node(AVL_p<T>* p, T n)
{
	if (height_of(p) == 0)
	{
		std::cout << "Tree is empty" << std::endl;
		return 0;
	}
	if (p->value > n)
	{
		p->left = delete_node(p->left, n);
	}
	else if (p->value < n)
	{
		p->right = delete_node(p->right, n);
	}
	else
	{
		AVL_p<T>* cur_left = p->left;
		AVL_p<T>* cur_right = p->right;
		delete p;
		if (cur_left == nullptr && cur_right == nullptr) // p - leaf
		{
			return nullptr;
		}
		else
		{
			AVL_p<T>* max = find_max(cur_left);
			
				AVL_p<T>* prev_max = find_prev_max(cur_left, max);
				if (prev_max == max)  //ситуация, что самый близкий к р это его левый элемент
				{
					max->right = cur_right;
					return (balance(max));
				}
				else
				{
					prev_max->right = max->left;
					prev_max = balance(prev_max);
					max->left = cur_left;
					max->right = cur_right;
					return balance(max);
				}
			
		}
	}
	return balance(p);
}

temp
void remove_from_tree(AVL_tree<T>& p, T value)
{
	p.root = delete_node(p.root, value);
}

void plug(int& n)
{
	n = -1;
}

void plug(pair_temp& p)
{
	p.key = -1;
	p.value = "-";
}

temp
void show_tree(AVL_tree<T>& p)
{
	if (p.root != nullptr)
	{
		//нужно создать массив из элементов принтс, у которых есть значение и уровень
		std::vector<Print_it<T>> prints;
		int lvl = height_of(p.root);
		show(p.root, 200, prints, lvl);
		Print_it<T> line;
		plug(line.value);
		//вывод сначала тех принтсов, у которых уровень выше
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
					if (prints[j].value == line.value)
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
void show(AVL_p<T>* p, int k, std::vector<Print_it<T>>& prints, int cur_h)
{
	// 200 - корень, 100 - узел или лист, 101 - выход
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
				plug(n.value);//заглушка
			}
			prints.push_back(n);
			if (p->right != nullptr)
			{
				n.value = p->right->value;
			}
			else
			{
				plug(n.value);//заглушка
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
					plug(n.value);//заглушка
				}
				prints.push_back(n);
				if (p->right != nullptr)
				{
					n.value = p->right->value;
				}
				else
				{
					plug(n.value);//заглушка
				}
				prints.push_back(n);
				show(p->left, 100, prints, cur_h - 1);
				show(p->right, 100, prints, cur_h - 1);
			}
			else
			{
				n.level = cur_h;
				plug(n.value);//заглушка
				prints.push_back(n);
				prints.push_back(n);
				show(p->left, 101, prints, cur_h - 1);
				show(p->right, 101, prints, cur_h - 1);
			}
		}

	}

}

temp
void delete_p(AVL_p<T>* p)
{
	if (p != nullptr)
	{
		delete_p(p->left);
		delete_p(p->right);
		delete p;
	}
}

temp
void delete_tree(AVL_tree<T>& p)
{
	delete_p(p.root);
}

int main()
{
	AVL_tree<int> tree0;
	data<int> tmp;
	consrtuct_tree(tree0);
	for (int i = 0; i <= 12; ++i)
	{
		tmp.value = i;
		insert_tree(tree0, tmp.value);
	}
	show_tree(tree0);
	tmp.value = 7;
	remove_from_tree(tree0, tmp.value);
	std::cout << "----------------------\n";
	show_tree(tree0);
    tmp.value = 1;
	remove_from_tree(tree0, tmp.value);
	std::cout << "----------------------\n";
	show_tree(tree0);
	tmp.value = 3;
	remove_from_tree(tree0, tmp.value);
	std::cout << "----------------------\n";
	show_tree(tree0);
	delete_tree(tree0);
	std::cout << "----------------------\n";
	AVL_tree<pair_temp> tree1;
	consrtuct_tree(tree1);
	pair_temp p0 = { 1, "abc" };
	pair_temp p1 = { 2, "def" };
	pair_temp p2 = { 5, "ghi" };
	pair_temp p3 = { 7, "jkl" };
	pair_temp p4 = { 3, "mno" };
	pair_temp p5 = { 9, "pqr" };
	pair_temp p6 = { 6, "stu" };
	pair_temp p7 = { 4, "vwx" };
	insert_tree(tree1, p0);
	insert_tree(tree1, p1);
	insert_tree(tree1, p2);
	insert_tree(tree1, p3);
	insert_tree(tree1, p4);
	insert_tree(tree1, p5);
	insert_tree(tree1, p6);
	insert_tree(tree1, p7);
	show_tree(tree1);
	delete_tree(tree1);
	return 0;
}

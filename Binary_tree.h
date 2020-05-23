#ifndef UNTITLED4_BINARY_TREE_H
#define UNTITLED4_BINARY_TREE_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <cmath>

using namespace std;
template<typename T>
class Binary_tree{
private:

    struct tNode{
    public:
        tNode* pRight;
        tNode* pLeft;
        T data;
        tNode(T number) {
            pLeft = nullptr;
            pRight = nullptr;
            data = number;
        }
    };
    tNode* root;

    tNode* adding_tree_iterator(T number, tNode* current)
    {
        if ((current->pLeft == nullptr) && (number < current->data)){return current;}
        if ((current->pRight == nullptr) && (number >= current->data)){return current;}
        if (number < current->data)
        {
            current = current->pLeft;
            return adding_tree_iterator(number, current);
        }
        else
        {
            current = current->pRight;
            return adding_tree_iterator(number, current);
        }
    }



public:
    Binary_tree() {
        root = nullptr;
    }


    ~Binary_tree(){
        clear();
    }

    void add_elem(T number)
    {
        function<tNode*(T, tNode*)> adding_iterator = [&adding_iterator](T number, tNode* current)
        {
            if ((current->pLeft == nullptr) && (number < current->data)){return current;}
            if ((current->pRight == nullptr) && (number >= current->data)){return current;}
            if (number < current->data)
            {
                current = current->pLeft;
                return adding_iterator(number, current);
            }
            else
            {
                current = current->pRight;
                return adding_iterator(number, current);
            }
        };
        if (root==nullptr)
        {
            root = new tNode(number);
            root->data = number;
        }
        else
        {
            tNode* current = adding_tree_iterator(number, root);
            if (number < current->data)
            {
                current->pLeft = new tNode(number);
            }
            else
            {
                current->pRight = new tNode(number);
            }
        }
    }

    void delete_elem(T number)
    {
        function<tNode*(T, tNode*)> deleting_iterator = [&deleting_iterator](T number, tNode* current)
        {
            if (current->pLeft != nullptr)
                if (number == current->pLeft->data){return current;}
            if (current->pRight != nullptr)
                if (number == current->pRight->data){return current;}

            if (number < current->data)
                return deleting_iterator(number, current->pLeft);
            else
                return deleting_iterator(number, current->pRight);
        };
        if (root==nullptr)
        {
            cout << "The tree is empty!";
        }
        else
        {
            if (number == root->data)
            {
                tNode * root_to_delete = root;
                tNode * root_left = root->pLeft;
                root = root->pRight;
                tNode * current = root;
                while(current->pLeft)
                    current = current->pLeft;
                current->pLeft = root_left;
                delete root_to_delete;
            } else{
                tNode* prev_deleting_elem = deleting_iterator(number, root); // Мы находимся над нужным элементом (он или справа, или слева)
                tNode *deleting_elem = nullptr;
                tNode* left;
                tNode* right;

                // назначаем удаляемый элемент
                if ((prev_deleting_elem->pLeft) && (number == prev_deleting_elem->pLeft->data)) // удаляемый элемент слева
                {
                    deleting_elem = prev_deleting_elem->pLeft;
                }
                if ((prev_deleting_elem->pRight) && (number == prev_deleting_elem->pRight->data)) // удаляемый элемент справа
                {
                    deleting_elem = prev_deleting_elem->pRight;
                }

                // если удаляем последние элементы в дереве
                if (!(deleting_elem->pLeft) && !(deleting_elem->pRight))
                {
                    if (number == prev_deleting_elem->pLeft->data)
                    {
                        prev_deleting_elem->pLeft = nullptr;
                        delete deleting_elem;
                    } else{
                        prev_deleting_elem->pRight = nullptr;
                        delete deleting_elem;
                    }
                }

                    // удаляем не последний элемент в дереве
                else{
                    left = deleting_elem->pLeft; // левый от удаляемого
                    right = deleting_elem->pRight; // правый от удаляемого
                    if (!right)
                    {
                        if(deleting_elem == prev_deleting_elem->pLeft)
                            prev_deleting_elem->pLeft = left;
                        if(deleting_elem == prev_deleting_elem->pRight)
                            prev_deleting_elem->pRight = left;
                    } else{
                        if(deleting_elem == prev_deleting_elem->pLeft)
                            prev_deleting_elem->pLeft = right; // переназначаем левый указатель предыдущего элемента перед удаляемым
                        else
                            prev_deleting_elem->pRight = right; // переназначаем правый указатель предыдущего элемента перед удаляемым

                        while ((right) && (right->pLeft)) // переходим на самый малый элемент в правой ветке от удаляемого
                        {
                            right = right->pLeft;
                        }
                        if (right)
                            right->pLeft = left;
                        else
                        {
                            if ((prev_deleting_elem->pLeft) && (number == prev_deleting_elem->pLeft->data))
                                prev_deleting_elem->pLeft = nullptr;
                            else
                                prev_deleting_elem->pRight = nullptr;
                        }
                    }

                    delete deleting_elem;
                }
            }

        }
    }


    void printTree()
    {

        // Инициализация квадратного массива с размерами 2^(глубина-1)
        int size = pow(2,getDepth());
        vector<vector<string>> tree_mass (getDepth()+1, vector<string>(size, " "));
        //Заполнение всех ячеек пробелами

        int current_depth = 1;

        function<void(int, int, tNode*)> mass_fill = [&mass_fill, &tree_mass, size](int current_depth, int position, tNode * current)
        {
            tree_mass[current_depth][position] = to_string(current->data);
            if (current->pLeft)
                mass_fill(current_depth + 1, position - size/pow(2, current_depth+1), current->pLeft);
            if (current->pRight)
                mass_fill(current_depth + 1, position + size/pow(2, current_depth+1), current->pRight);
        };

        mass_fill(current_depth, size/2, root);
        for (int i = 0; i<getDepth()+1; i++)
        {
            for (int j = 0; j<size; j++)
                cout << tree_mass[i][j];
            cout << endl << endl;
        }
    }

    tNode * getRoot()
    {
        return root;
    }

    int getDepth()
    {
        int maxDepth = 1;
        function<int(tNode*, int, int&)> tree_iterator = [&tree_iterator](tNode* current, int current_depth, int& maxDepth)
        {
            if (current)
            {
                tree_iterator(current->pLeft, current_depth + 1, maxDepth);
                tree_iterator(current->pRight, current_depth + 1, maxDepth);
                if (current_depth > maxDepth)
                    maxDepth = current_depth;
            }
            return maxDepth;
        };
        return tree_iterator(root, 1, maxDepth);
    }

    void clear()
    {
        function<void(tNode*)> deleting_tree_iterator = [&deleting_tree_iterator](tNode* current)
        {
            if (current)
            {
                deleting_tree_iterator(current->pLeft);
                deleting_tree_iterator(current->pRight);
                delete current;
            }
        };
        deleting_tree_iterator(root);
    }
};
#endif //UNTITLED4_BINARY_TREE_H

#include "Node.h"

#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <utility>

template <typename T>
class BinaryTree
{
public:
	BinaryTree(Node<T>* root = nullptr);
	~BinaryTree();

	void insertR(const T& data);
	void insertI(const T& data);

	void eraseR(const T& data);
    void eraseI(const T& data);

	bool findR(const T& data) const;
	bool findI(const T& data) const;
    T findMinR() const;
    T findMinI() const;
    T findMaxR() const;
    T findMaxI() const;

	void inorderR() const;
	void preorderR() const;
	void postorderR() const;

	void preorderI() const;
	void inorderI() const;
	void postorderI() const;
	void levelorder() const;

	int countOfNodesR() const;
    int countOfNodesI() const;
	int countOfLeavesR() const;
    int countOfLeavesI() const;

	int heightR() const;
	int heightI() const;

	int widthI() const;
	int widthR() const;

	void clearR();

private:
	Node<T>* insertHelper(Node<T>* ptr, const  T& data);

	Node<T>* eraseHelper(Node<T>* ptr, const T& data);

	Node<T>* findHelper(Node<T>* ptr, const T& data) const;
	Node<T>* findMinHelper(Node<T>* ptr) const;
	Node<T>* findMaxHelper(Node<T>* ptr) const;

	void inorderHelper(Node<T>* ptr) const;
	void preorderHelper(Node<T>* ptr) const;
	void postorderHelper(Node<T>* ptr) const;

	int countOfNodesHelper(Node<T>* ptr) const;
	int countOfLeavesHelper(Node<T>* ptr) const;

	int heightHelper(Node<T>* ptr) const;
	int widthHelper(Node<T>* ptr, int i) const;

	void clearHelper(Node<T>* ptr);

private:
	Node<T>* m_root;
};




template <typename T>
BinaryTree<T>::BinaryTree(Node<T>* root)
{
    m_root = root;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    clearR();
}

template <typename T>
void BinaryTree<T>::insertI(const T& data)
{
    if (m_root == nullptr) {
        m_root = new Node<T>(data);
        return;
    }

    Node<T>* ptr = m_root;
    while (true) {
        if (data > ptr->data) {
            if (ptr->right == nullptr) {
                ptr->right = new Node<T>(data);
                return;
            } else {
                ptr = ptr->right;
            }
        } else if (data < ptr->data) {
            if (ptr->left == nullptr) {
                ptr->left = new Node<T>(data);
                return;
            } else {
                ptr = ptr->left;
            }
        } else {
            std::cout << "Skipping data: " << data << std::endl;
            return;
        }
    }
}

template <typename T>
void BinaryTree<T>::insertR(const T& data)
{
    m_root = insertHelper(m_root, data);
}

template <typename T>
Node<T>* BinaryTree<T>::insertHelper(Node<T>* ptr, const T& data)
{
    if (ptr == nullptr) {
        ptr = new Node<T>(data);
        return ptr;
    }

    if (data > ptr->data) {
        ptr->right = insertHelper(ptr->right, data);
    } else if (data < ptr->data) {
        ptr->left = insertHelper(ptr->left, data);
    } else {
        std::cout << "Skipping data: " << data << std::endl;
    }
    return ptr;
}


template <typename T>
void BinaryTree<T>::eraseI(const T& data)
{
    if (m_root == nullptr) {
        return;
    }

    Node<T>* ptr = m_root;
    Node<T>* parent = nullptr;

    while (ptr != nullptr) {
        if (data > ptr->data) {
            parent = ptr;
            ptr = ptr->right;
        } else if (data < ptr->data) {
            parent = ptr;
            ptr = ptr->left;
        } else {
            if (ptr->left == nullptr && ptr->right == nullptr) {
                std::cout << "Deleting leaf" << std::endl;
                delete ptr;
                if (ptr == m_root) {
                    m_root = nullptr;
                }
                if (ptr == parent->left) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
                ptr = nullptr;
                return;
            }

            if (ptr->right == nullptr) {
                std::cout << "Deleting node with left child" << std::endl;
                parent->left = ptr->left;
                delete ptr;
                return;
            }
            if (ptr->left == nullptr) {
                std::cout << "Deleting node with right child" << std::endl;
                parent->right = ptr->right;
                delete ptr;
                return;
            }

            std::cout << "Deleting node with two child" << std::endl;
            Node<T>* max = findMaxHelper(ptr->left);
            std::swap(ptr->data, max->data);
            parent = ptr;
            ptr = ptr->left;
        }
    }
    return;
}


template <typename T>
void BinaryTree<T>::eraseR(const T& data)
{
    m_root = eraseHelper(m_root, data);
}


template <typename T>
Node<T>* BinaryTree<T>::eraseHelper(Node<T>* ptr, const T& data)
{
    if (ptr == nullptr) {
        return nullptr;
    }
    
    if (data > ptr->data) {
        ptr->right = eraseHelper(ptr->right, data);
    } else if (data < ptr->data) {
        ptr->left = eraseHelper(ptr->left, data);
    } else {
        if (ptr->left == nullptr && ptr->right == nullptr) {
            std::cout << "Deleting leaf " << std::endl;
            delete ptr;
            return nullptr;
        } 
        if (ptr->left == nullptr) {
            std::cout << "Deleting node with right child" << std::endl;
            Node<T>* tmp = ptr->right;
            delete ptr;
            return tmp;
        } 
        if (ptr->right == nullptr) {
            std::cout << "Deleting node with left child" << std::endl;
            Node<T>* tmp = ptr->left;
            delete ptr;
            return tmp;
        }

        std::cout << "Deleting node with two child" << std::endl;
        Node<T>* max = findMaxHelper(ptr->left);
        ptr->data = max->data;
        ptr->left = eraseHelper(ptr->left, max->data);
    }
    return ptr;
}


template <typename T>
T BinaryTree<T>::findMaxI() const
{
    if (m_root == nullptr) {
        std::cout << "Root is nullptr" << std::endl;
        return T{};
    }
    Node<T>* ptr = m_root;

    while (ptr->right != nullptr) {
        ptr = ptr->right;
    }
    return ptr->data;
}

template <typename T>
T BinaryTree<T>::findMinI() const
{
    if (m_root ==  nullptr) {
        std::cout << "Root is nullptr" << std::endl;
        return T{};
    }

    Node<T>* ptr = m_root;
    while (ptr->left != nullptr) {
        ptr = ptr->left;
    }

    return ptr->data;
}


template <typename T>
T BinaryTree<T>::findMaxR() const
{
    if (m_root == nullptr) {
        std::cout << "Root is nullptr" << std::endl;
        return T{};
    }

    return findMaxHelper(m_root)->data;
}


template <typename T>
Node<T>* BinaryTree<T>::findMaxHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return nullptr;
    }

    if (ptr->right != nullptr) {
        return findMaxHelper(ptr->right);
    }
    return ptr;
}

template <typename T>
T BinaryTree<T>::findMinR() const
{
    if (m_root == nullptr) {
        std::cout << "Root is nullptr" << std::endl;
        return T{};
    }
    return findMinHelper(m_root)->data;
}

template <typename T>
Node<T>* BinaryTree<T>::findMinHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return nullptr;
    }

    if (ptr->left != nullptr) {
        return findMinHelper(ptr->left);
    }
    return ptr;
}


template <typename T>
bool BinaryTree<T>::findI(const T& data) const
{
    Node<T>* ptr = m_root;
    while (ptr) {
        if (data > ptr->data) {
            ptr = ptr->right;
        } else if (data < ptr->data) {
            ptr = ptr->left;
        } else {
            return true;
        }
    }
    return false;
}


template <typename T>
bool BinaryTree<T>::findR(const T& data) const
{
    return findHelper(m_root, data) != nullptr;
}

template <typename T>
Node<T>* BinaryTree<T>::findHelper(Node<T>* ptr, const T& data) const
{
    if (ptr == nullptr) {
        return nullptr;
    } 
    if (data > ptr->data) {
        return findHelper(ptr->right, data);
    }
    if (data < ptr->data) {
        return findHelper(ptr->left, data);
    }
    return ptr;

}


template <typename T>
void BinaryTree<T>::inorderI() const
{
	std::stack<Node<T>*> stk;
	Node<T>* ptr = m_root;

	while (true) {
		while (ptr != nullptr) {
			stk.push(ptr);
			ptr = ptr->left;
		}

		if (stk.empty()) { 
			return;
        }

		ptr = stk.top();
		stk.pop();
		std::cout << ptr->data << ' ';

		ptr = ptr->right;
	}
}


template <typename T>
void BinaryTree<T>::postorderI() const
{
	std::stack<Node<T>*> stk;
	Node<T>* ptr = m_root;
	
	while (true) {
		while (ptr != nullptr) {
			if (ptr->right) {
				stk.push(ptr->right);
			}
			stk.push(ptr);
			ptr = ptr->left;
		}

		if (stk.empty()) {
			return;
		}

		ptr = stk.top();
		stk.pop();
		if (ptr->right && !stk.empty() && stk.top() == ptr->right) {
			stk.pop();
			stk.push(ptr);
			ptr = ptr->right;
		} else {
			std::cout << ptr->data << ' '; 
			ptr = nullptr;
		}
	}
}


template <typename T>
void BinaryTree<T>::preorderI() const
{
    std::stack<Node<T>*> stk;
	Node<T>* ptr = m_root;

	while (true) {
		while (ptr != nullptr) {
			std::cout << ptr->data << " ";
			
			if (ptr->right) {
				stk.push(ptr->right);
			}

			ptr = ptr->left;
		}

		if (stk.empty()) {
			return;
		}
		
		ptr = stk.top();
		stk.pop();
	}
}


template <typename T>
void BinaryTree<T>::levelorder() const
{
	std::queue <Node<T>*> q;
	q.push(m_root);
	while (!q.empty()) {
		Node<T>* ptr = q.front();
		q.pop();

		std::cout << ptr->data << ' ';

		if (ptr->left) {
			q.push(ptr->left);
		}
		if (ptr->right) {
			q.push(ptr->right);
		}
	}
}


template <typename T>
void BinaryTree<T>::inorderR() const
{
    inorderHelper(m_root);
}

template <typename T>
void BinaryTree<T>::inorderHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return;
    }

    inorderHelper(ptr->left);
    std::cout << ptr->data << " ";
    inorderHelper(ptr->right);
}


template <typename T>
void BinaryTree<T>::postorderR() const
{
    postorderHelper(m_root);
}

template <typename T>
void BinaryTree<T>::postorderHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return;
    }

    postorderHelper(ptr->left);
    postorderHelper(ptr->right);
    std::cout << ptr->data << " ";
}


template <typename T>
void BinaryTree<T>::preorderR() const
{
    preorderHelper(m_root);
}

template <typename T>
void BinaryTree<T>::preorderHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return;
    }
    
    std::cout << ptr->data << " ";
    preorderHelper(ptr->left);
    preorderHelper(ptr->right);
}


template <typename T>
int BinaryTree<T>::countOfNodesI() const
{
	std::stack<Node<T>*> stk;
	Node<T>* ptr = m_root;
    int count = 0;

	while (true) {
		while (ptr != nullptr) {
			stk.push(ptr);
			ptr = ptr->left;
		}

		if (stk.empty()) {
			return count;
        }

		ptr = stk.top();
		stk.pop();
		++count;

		ptr = ptr->right;
	}
}


template <typename T>
int BinaryTree<T>::countOfNodesR() const
{
    return countOfNodesHelper(m_root);
}

template <typename T>
int BinaryTree<T>::countOfNodesHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return 0;
    }

    return countOfNodesHelper(ptr->left) + countOfNodesHelper(ptr->right) + 1;
}


template <typename T>
int BinaryTree<T>::countOfLeavesI() const
{
    std::stack<Node<T>*> stk;
	Node<T>* ptr = m_root;
    int count = 0;

	while (true) {
		while (ptr != nullptr) {
			stk.push(ptr);
			ptr = ptr->left;
		}

		if (stk.empty()) {
			return count;
        }

		ptr = stk.top();
		stk.pop();
        if (ptr->left == nullptr && ptr->right == nullptr) {
		    ++count;
        }

		ptr = ptr->right;
	}
}


template <typename T>
int BinaryTree<T>::countOfLeavesR() const
{
    return countOfLeavesHelper(m_root);
}

template <typename T>
int BinaryTree<T>::countOfLeavesHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return 0;
    }
    if (ptr->left == nullptr && ptr->right == nullptr) {
        return 1;
    }

    return countOfLeavesHelper(ptr->left) + countOfLeavesHelper(ptr->right);
}


template <typename T>
int BinaryTree<T>::heightI() const
{
    std::queue<Node<T>*> q;
	q.push(m_root);

	int height = 0;

	while (!q.empty()) {
		const int size = q.size();
		for (int i = 0; i < size; i++) {
			Node<T>* ptr = q.front();
			q.pop();

			if (ptr->left) {
				q.push(ptr->left);
			}

			if (ptr->right) {
				q.push(ptr->right);
			}
		}
		++height;
	}
	return height;
}


template <typename T>
int BinaryTree<T>::heightR() const
{
    return heightHelper(m_root);
}

template <typename T>
int BinaryTree<T>::heightHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return 0;
    }

    if (ptr->left == nullptr && ptr->right == nullptr) {
        return 1;
    }

    return 1 + std::max(heightHelper(ptr->left), heightHelper(ptr->right));
}


template <typename T>
int BinaryTree<T>::widthI() const
{
	std::queue<Node<T>*> q;
	q.push(m_root);
	int width = 0;

	while (!q.empty()) {
		const int size = q.size();
		width = std::max(size, width); 
		for (int i = 0; i < size; i++) {
			Node<T>* ptr = q.front();
			q.pop();

			if (ptr->left) {
				q.push(ptr->left);
			}

			if (ptr->right) {
				q.push(ptr->right);
			}
		}
	}
	return width;
}


template <typename T>
int BinaryTree<T>::widthR() const
{
    int width = 0;
    int height = heightR();

    for (int i = 0; i <= height; ++i) {
        int currentWidth = widthHelper(m_root, i);
        if (currentWidth > width) {
            width = currentWidth;
        }
    }
    return width;
}

template <typename T>
int BinaryTree<T>::widthHelper(Node<T>* ptr, int level) const
{
    if (ptr == nullptr) {
        return 0;
    }

    if (level == 0) {
        return 1;
    }

    return widthHelper(ptr->left, level - 1) + widthHelper(ptr->right, level - 1);
}


template <typename T>
void BinaryTree<T>::clearR() 
{
    clearHelper(m_root);
    m_root = nullptr;
}

template <typename T>
void BinaryTree<T>::clearHelper(Node<T>* ptr)
{
    if (ptr == nullptr) {
        return;
    }

    clearHelper(ptr->left);
    clearHelper(ptr->right);
    delete ptr;
    ptr = nullptr;
}

#pragma once

template<typename T>
struct Node
{
    Node(int d, Node* l = nullptr, Node* r = nullptr)
        :data{d}
        ,left{l}
        ,right{r}
    {}
    
    T data;
    Node<T>* left;
    Node<T>* right;
};

template <typename T>
BST<T>::BST(const std::initializer_list<T>& l) : BST<T>()
{
    for(const auto& v : l)
    {
        insertNode(v);
    }
}

template <typename T>
void BST<T>::insertNode(const T& value)
{
    m_nodes.clear();
    insertNode(value, m_root);
}

template <typename T>
void BST<T>::insertNode(const T& value, Node*& root)
{
    if(root == nullptr)
    {
        root = new Node { value, nullptr, nullptr, std::to_string(value) };
        return;
    }

    Node* currentNode {root};
    while(true)
    {
        if(value < currentNode->data)
        {
            if(currentNode->left != nullptr)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode->left = new Node { value, nullptr, nullptr, std::to_string(value) };
                break;
            }
        }
        else if(value > currentNode->data)
        {
            if(currentNode->right != nullptr)
            {
                currentNode = currentNode->right;
            }
            else
            {
                currentNode->right = new Node { value, nullptr, nullptr, std::to_string(value) };
                break;
            }
        }
        else
        {
            break;
        }
    }
}

template <typename T>
void BST<T>::deleteNode(const T& value)
{
    m_nodes.clear();
    deleteNode(value, m_root);
}

template <typename T>
void BST<T>::deleteNode(const T& value, Node*& root)
{
    if(root == nullptr)
    {
        return;
    }

    Node* currentNode = find(value, root);
    if(currentNode->left != nullptr && currentNode->right != nullptr)
    {
        Node* successiveNode = findMinNode(currentNode->right);
        if(successiveNode->right != nullptr)
        {
            currentNode->data = successiveNode->data;
            successiveNode->data = successiveNode->right->data;
            delete successiveNode->right;
            successiveNode->right = nullptr;
        }
        else
        {
            currentNode->data = successiveNode->data;
            if(m_nodes.top() != currentNode)
            {
                m_nodes.top()->left = nullptr;
            }
            else
            {
                m_nodes.top()->right = nullptr;
            }

            delete successiveNode;
        }
    }
    else
    {
        if(m_nodes.empty())
        {
            root = (currentNode->left != nullptr) ? currentNode->left : currentNode->right;
        }
        else if(currentNode == m_nodes.top()->left)
        {
            m_nodes.top()->left  = (currentNode->left != nullptr) ? currentNode->left : currentNode->right;
        }
        else if(currentNode == m_nodes.top()->right)
        {
            m_nodes.top()->right = (currentNode->left != nullptr) ? currentNode->left : currentNode->right;
        }

        delete currentNode;
    }
}

template <typename T>
void BST<T>::labelNode(Node* node)
{
    node->label = std::to_string(node->data);
}

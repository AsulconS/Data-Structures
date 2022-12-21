template <typename T>
SplayTree<T>::SplayTree(const std::vector<T>& data) : SplayTree<T>()
{
    for(const auto& v : data)
    {
        insertNode(v);
    }
}

template <typename T>
SplayTree<T>::SplayTree(const std::initializer_list<T>& l) : SplayTree<T>()
{
    for(const auto& v : l)
    {
        insertNode(v);
    }
}

template <typename T>
GenericNode<T>* SplayTree<T>::find(const T& value)
{
    m_nodes.clear();
    Node* node = find(value, m_root);
    splay(m_root, (node != nullptr) ? node : m_nodes.top());
    return node;
}

template <typename T>
void SplayTree<T>::insertNode(const T& value)
{
    m_nodes.clear();
    insertNode(value, m_root);
}

template <typename T>
void SplayTree<T>::insertNode(const T& value, Node*& root)
{
    if(root == nullptr)
    {
        root = new Node { value, nullptr, nullptr };
        labelNode(root);
        if(debugMode)
        {
            this->exportToFile("Root Insertion");
        }
        return;
    }

    Node* currentNode {root};
    while(true)
    {
        if(value < currentNode->data)
        {
            m_nodes.push(currentNode);
            if(currentNode->left != nullptr)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode->left = new Node { value, nullptr, nullptr };
                labelNode(currentNode->left);
                if(debugMode)
                {
                    this->exportToFile("Insertion");
                }
                splay(root, currentNode->left);
                break;
            }
        }
        else if(value > currentNode->data)
        {
            m_nodes.push(currentNode);
            if(currentNode->right != nullptr)
            {
                currentNode = currentNode->right;
            }
            else
            {
                currentNode->right = new Node { value, nullptr, nullptr };
                labelNode(currentNode->right);
                if(debugMode)
                {
                    this->exportToFile("Insertion");
                }
                splay(root, currentNode->right);
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
void SplayTree<T>::deleteNode(const T& value)
{
    m_nodes.clear();
    deleteNode(value, m_root);
}

template <typename T>
void SplayTree<T>::deleteNode(const T& value, Node*& root)
{
    if(root == nullptr)
    {
        return;
    }

    /* First build the path from root to the node to be deleted by finding it */
    Node* currentNode = find(value, root);
    if(currentNode == nullptr)
    {
        currentNode = m_nodes.pop();
        splay(root, currentNode);
        return;
    }
    if(currentNode->left == nullptr && currentNode->right == nullptr)
    {
        splay(root, currentNode);
    }

    Node* successive {currentNode};
    m_predecessors.clear();
    while(successive->left != nullptr || successive->right != nullptr)
    {
        m_nodes.push(successive);
        m_predecessors.push(successive);
        if(successive->left != nullptr)
        {
            successive = findMaxNode(successive->left);
        }
        else if(successive->right != nullptr)
        {
            successive = findMinNode(successive->right);
        }
        std::cout << m_predecessors.getStrN() << std::endl;
    }

    T oldData {};
    while(!m_predecessors.empty())
    {
        oldData = m_predecessors.top()->data;
        m_predecessors.top()->data = successive->data;
        labelNode(m_predecessors.pop());
        successive->data = oldData;
    }

    std::cout << m_nodes.top()->data << std::endl;
    std::cout << successive->data << std::endl;
    if(successive == m_nodes.top()->left)
    {
        m_nodes.top()->left = nullptr;
    }
    else
    {
        m_nodes.top()->right = nullptr;
    }

    while(m_nodes.pop() != currentNode);

    delete successive;

    splay(root, currentNode);
}

template <typename T>
void SplayTree<T>::labelNode(Node* node)
{
    if(node != nullptr)
    {
        std::string label { "label = \"" + std::to_string(node->data) + '\"' };
        node->label = label;
    }
}

template <typename T>
void SplayTree<T>::splay(Node*& root, Node* leaf)
{
    Node* currentNode {leaf};
    while(m_nodes.getSize() > 1)
    {
        Node* parent = m_nodes.pop();
        Node* grandParent = m_nodes.pop();
        Node*& pivot = (!m_nodes.empty()) ? ((grandParent == m_nodes.top()->left) ? m_nodes.top()->left : m_nodes.top()->right) : root;

        if(parent == grandParent->left && currentNode == parent->left)
        {
            rotateZigZig(pivot);
        }
        else if(parent == grandParent->left && currentNode == parent->right)
        {
            rotateZagZig(pivot);
        }
        else if(parent == grandParent->right && currentNode == parent->right)
        {
            rotateZagZag(pivot);
        }
        else
        {
            rotateZigZag(pivot);
        }
    }

    if(!m_nodes.empty())
    {
        if(currentNode == root->left)
        {
            rotateZig(root);
        }
        else
        {
            rotateZag(root);
        }
    }
}

template <typename T>
void SplayTree<T>::rotateZig(Node*& root)
{
    Node* oldRoot {root};
    root = root->left;
    oldRoot->left = root->right;
    root->right = oldRoot;
    if(debugMode)
    {
        this->exportToFile("Rotate: Zig. Pivot: " + std::to_string(oldRoot->data));
    }
}

template <typename T>
void SplayTree<T>::rotateZag(Node*& root)
{
    Node* oldRoot {root};
    root = root->right;
    oldRoot->right = root->left;
    root->left = oldRoot;
    if(debugMode)
    {
        this->exportToFile("Rotate: Zag. Pivot: " + std::to_string(oldRoot->data));
    }
}

template <typename T>
void SplayTree<T>::rotateZigZig(Node*& root)
{
    if(debugMode)
    {
        this->exportToFile("Rotate: Zig-Zig. Pivot: " + std::to_string(root->data));
    }
    rotateZig(root);
    rotateZig(root);
}

template <typename T>
void SplayTree<T>::rotateZagZag(Node*& root)
{
    if(debugMode)
    {
        this->exportToFile("Rotate: Zag-Zag. Pivot: " + std::to_string(root->data));
    }
    rotateZag(root);
    rotateZag(root);
}

template <typename T>
void SplayTree<T>::rotateZigZag(Node*& root)
{
    if(debugMode)
    {
        this->exportToFile("Rotate: Zig-Zag. Pivot: " + std::to_string(root->data));
    }
    rotateZig(root->right);
    rotateZag(root);
}

template <typename T>
void SplayTree<T>::rotateZagZig(Node*& root)
{
    if(debugMode)
    {
        this->exportToFile("Rotate: Zag-Zig. Pivot: " + std::to_string(root->data));
    }
    rotateZag(root->left);
    rotateZig(root);
}

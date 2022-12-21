template <typename T>
AVL<T>::AVL(const std::vector<T>& data) : AVL<T>()
{
    for(const auto& v : data)
    {
        insertNode(v);
    }
}

template <typename T>
AVL<T>::AVL(const std::initializer_list<T>& l) : AVL<T>()
{
    for(const auto& v : l)
    {
        insertNode(v);
    }
}

template <typename T>
void AVL<T>::insertNode(const T& value)
{
    m_nodes.clear();
    insertNode(value, m_root);
}

template <typename T>
void AVL<T>::insertNode(const T& value, Node*& root)
{
    if(root == nullptr)
    {
        root = new Node { value, 0, nullptr, nullptr };
        labelNode(root);
        if(debugMode)
        {
            this->exportToFile("Root Insertion");
        }
        return;
    }

    /* Clears the stacks to store the node's path */
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
                currentNode->left = new Node { value, 0, nullptr, nullptr };
                labelNode(currentNode->left);
                if(debugMode)
                {
                    this->exportToFile("Insertion");
                }
                balance(root, currentNode->left);
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
                currentNode->right = new Node { value, 0, nullptr, nullptr };
                labelNode(currentNode->right);
                if(debugMode)
                {
                    this->exportToFile("Insertion");
                }
                balance(root, currentNode->right);
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
void AVL<T>::deleteNode(const T& value)
{
    m_nodes.clear();
    deleteNode(value, m_root);
}

template <typename T>
void AVL<T>::deleteNode(const T& value, Node*& root)
{
    if(root == nullptr)
    {
        return;
    }

    /* First build the path from root to the node to be deleted by finding it */
    Node* currentNode = find(value, root);
    if(currentNode->left != nullptr && currentNode->right != nullptr)
    {
        Node* successiveNode;
        m_nodes.push(currentNode);
        if(height(currentNode->left) > height(currentNode->right))
        {
            successiveNode = findMaxNode(currentNode->left);
            /* Only has one left child */
            if(successiveNode->left != nullptr)
            {
                currentNode->data = successiveNode->data;
                successiveNode->data = successiveNode->left->data;
                successiveNode->height = 0;
                delete successiveNode->left;
                successiveNode->left = nullptr;
            }
            else
            {
                currentNode->data = successiveNode->data;
                if(m_nodes.top() != currentNode)
                {
                    m_nodes.top()->right = nullptr;
                }
                else
                {
                    m_nodes.top()->left = nullptr;
                }

                delete successiveNode;
            }
        }
        else
        {
            successiveNode = findMinNode(currentNode->right);
            /* Only has one right child */
            if(successiveNode->right != nullptr)
            {
                currentNode->data = successiveNode->data;
                successiveNode->data = successiveNode->right->data;
                successiveNode->height = 0;
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

        labelNode(currentNode);
        labelNode(successiveNode);
        balance(root, successiveNode);
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
            balance(root, m_nodes.top()->left);
        }
        else if(currentNode == m_nodes.top()->right)
        {
            m_nodes.top()->right = (currentNode->left != nullptr) ? currentNode->left : currentNode->right;
            balance(root, m_nodes.top()->right);
        }
        
        delete currentNode;
    }
}

template <typename T>
void AVL<T>::labelNode(Node* node)
{
    if(node != nullptr)
    {
        std::string label {"label = \"" + std::to_string(node->data) + " : " + std::to_string(node->height) + '\"'};
        node->label = label;
    }
}

template <typename T>
int8 AVL<T>::height(Node* node)
{
    return (node != nullptr) ? node->height : -1;
}

template <typename T>
void AVL<T>::balance(Node*& root, Node* leaf)
{
    Node* currentNode {leaf};
    while(!m_nodes.empty())
    {
        Node* parent = m_nodes.pop();
        Node*& pivot = (!m_nodes.empty()) ? ((parent == m_nodes.top()->left) ? m_nodes.top()->left : m_nodes.top()->right) : root;

        Node* left  = (currentNode == parent->left ) ? currentNode : parent->left;
        Node* right = (currentNode == parent->right) ? currentNode : parent->right;
        if(height(left) - height(right) > IMBALANCE_CONSTANT)
        {
            if(height(left->left) >= height(left->right))
            {
                rotateRight(pivot);

                m_nodes.push(left);
                m_nodes.push(parent);
            }
            else
            {
                Node* aux = left->right;

                rotateLeftRight(pivot);

                m_nodes.push(aux);
                m_nodes.push(parent);
                m_nodes.push(left);
            }
        }
        else if(height(right) - height(left) > IMBALANCE_CONSTANT)
        {
            if(height(right->left) >= height(right->right))
            {
                Node* aux = right->left;

                rotateRightLeft(pivot);

                m_nodes.push(aux);
                m_nodes.push(parent);
                m_nodes.push(right);
            }
            else
            {
                rotateLeft(pivot);

                m_nodes.push(right);
                m_nodes.push(parent);
            }
        }
        else
        {
            m_nodes.push(parent);
        }

        currentNode = m_nodes.pop();
        currentNode->height = std::max(height(currentNode->left), height(currentNode->right)) + 1;
        labelNode(currentNode);
    }   
}

template <typename T>
void AVL<T>::rotateLeft(Node*& root)
{
    Node* oldRoot {root};
    root = root->right;
    oldRoot->right = root->left;
    root->left = oldRoot;
    if(debugMode)
    {
        this->exportToFile("Rotate: Left. Pivot: " + std::to_string(oldRoot->data));
    }
}

template <typename T>
void AVL<T>::rotateRight(Node*& root)
{
    Node* oldRoot {root};
    root = root->left;
    oldRoot->left = root->right;
    root->right = oldRoot;
    if(debugMode)
    {
        this->exportToFile("Rotate: Right. Pivot: " + std::to_string(oldRoot->data));
    }
}

template <typename T>
void AVL<T>::rotateRightLeft(Node*& root)
{
    if(debugMode)
    {
        this->exportToFile("Rotate: Right-Left. Pivot: " + std::to_string(root->data));
    }
    rotateRight(root->right);
    rotateLeft(root);
}

template <typename T>
void AVL<T>::rotateLeftRight(Node*& root)
{
    if(debugMode)
    {
        this->exportToFile("Rotate: Left-Right. Pivot: " + std::to_string(root->data));
    }
    rotateLeft(root->left);
    rotateRight(root);
}

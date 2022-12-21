template <typename T>
RedBlack<T>::RedBlack(const std::vector<T>& data) : RedBlack<T>()
{
    for(const auto& v : data)
    {
        insertNode(v);
    }
}

template <typename T>
RedBlack<T>::RedBlack(const std::initializer_list<T>& l) : RedBlack<T>()
{
    for(const auto& v : l)
    {
        insertNode(v);
    }
}

template <typename T>
void RedBlack<T>::insertNode(const T& value)
{
    m_nodes.clear();
    insertNode(value, m_root);
}

template <typename T>
void RedBlack<T>::insertNode(const T& value, Node*& root)
{
    if(root == nullptr)
    {
        root = new Node { value, c_black, nullptr, nullptr };
        labelNode(root);
        if(debugMode)
        {
            this->exportToFile("Root Insertion");
        }
        return;
    }

    /* Clears the stacks to store the m_nodes' path */
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
                currentNode->left = new Node { value, c_red, nullptr, nullptr };
                labelNode(currentNode->left);
                if(debugMode)
                {
                    this->exportToFile("Insertion");
                }
                // If the parent of the new node is red, we start balancing
                if(color(currentNode))
                {
                    balance(root, currentNode->left);
                }
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
                currentNode->right = new Node { value, c_red, nullptr, nullptr };
                labelNode(currentNode->right);
                if(debugMode)
                {
                    this->exportToFile("Insertion");
                }
                // If the parent of the new node is red, we start balancing
                if(color(currentNode))
                {
                    balance(root, currentNode->right);
                }
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
void RedBlack<T>::deleteNode(const T& value)
{
    m_nodes.clear();
    deleteNode(value, m_root);
}

template <typename T>
void RedBlack<T>::deleteNode(const T& value, Node*& root)
{
    if(root == nullptr)
    {
        return;
    }
}

template <typename T>
bool RedBlack<T>::color(Node* node)
{
    return (node != nullptr) ? node->color : c_black;
}

template <typename T>
void RedBlack<T>::swapColor(Node* lNode, Node* rNode)
{
    bool color = lNode->color;
    lNode->color = rNode->color;
    rNode->color = color;
    labelNode(lNode);
    labelNode(rNode);
}

template <typename T>
void RedBlack<T>::balance(Node*& root, Node* leaf)
{
    Node* currentNode {leaf};
    while((m_nodes.getSize() > 1) && color(m_nodes.top()))
    {
        Node* parent = m_nodes.pop();
        Node* grandParent = m_nodes.pop();
        Node*& pivot = (!m_nodes.empty()) ? ((grandParent == m_nodes.top()->left) ? m_nodes.top()->left : m_nodes.top()->right) : root;

        Node* uncle = (parent == grandParent->left) ? grandParent->right : grandParent->left;
        if(color(uncle))
        {
            recolorPU(grandParent);
        }
        else
        {
            if(parent == grandParent->left && currentNode == parent->left)
            {
                rotateRight(pivot);
                swapColor(parent, grandParent);
            }
            else if(parent == grandParent->left && currentNode == parent->right)
            {
                rotateLeftRight(pivot);
                swapColor(currentNode, grandParent);
            }
            else if(parent == grandParent->right && currentNode == parent->right)
            {
                rotateLeft(pivot);
                swapColor(parent, grandParent);
            }
            else
            {
                rotateRightLeft(pivot);
                swapColor(currentNode, grandParent);
            }
            if(debugMode)
            {
                this->exportToFile("Swap colors");
            }
            
            root->color = c_black;
            labelNode(root);
            if(debugMode)
            {
                this->exportToFile("Root must be black");
            }
            return;
        }        

        currentNode = grandParent;
    }
    root->color = c_black;
    labelNode(root);
    if(debugMode)
    {
        this->exportToFile("Root must be black");
    }
}

template <typename T>
void RedBlack<T>::recolorPU(Node* grandParent)
{
    grandParent->left->color  = c_black;
    grandParent->right->color = c_black;
    grandParent->color = c_red;

    labelNode(grandParent->left);
    labelNode(grandParent->right);
    labelNode(grandParent);

    if(debugMode)
    {
        this->exportToFile("Recoloring");
    }
}

template <typename T>
void RedBlack<T>::labelNode(Node* node)
{
    if(node != nullptr)
    {
        std::string label {"label = \"" + std::to_string(node->data) + "\", fillcolor = "};
        label += (node->color) ? "red2, fontcolor = white" : "gray16, fontcolor = white";
        node->label = label;
    }
}

template <typename T>
void RedBlack<T>::rotateLeft(Node*& root)
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
void RedBlack<T>::rotateRight(Node*& root)
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
void RedBlack<T>::rotateRightLeft(Node*& root)
{
    if(debugMode)
    {
        this->exportToFile("Rotate: Right-Left. Pivot: " + std::to_string(root->data));
    }
    rotateRight(root->right);
    rotateLeft(root);
}

template <typename T>
void RedBlack<T>::rotateLeftRight(Node*& root)
{
    if(debugMode)
    {
        this->exportToFile("Rotate: Left-Right. Pivot: " + std::to_string(root->data));
    }
    rotateLeft(root->left);
    rotateRight(root);
}

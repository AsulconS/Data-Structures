namespace std
{
template <typename T>
inline string to_string(AVLNode<T>*& val)
{
    return to_string(val->idata);
}

template <typename T>
inline string to_string(AVLNode<T>*&& val)
{
    return to_string(val->idata);
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
    if(m_root == nullptr)
    {
        m_root = new Node { std::move(value) * 100, std::move(value), 0, nullptr, nullptr };
        this->exportToFile("Root Insertion");
        return;
    }

    insertNode(value, m_root);
}

template <typename T>
void AVL<T>::insertNode(const T& value, Node* root)
{
    while(true)
    {
        if(value < root->idata)
        {
            if(root->left != nullptr)
            {
                root = root->left;
            }
            else
            {
                root->left = new Node { std::move(value) * 100, std::move(value), 0, nullptr, nullptr };
                this->exportToFile("Insertion");
                balance(m_root, root->left);
                break;
            }
        }
        else
        {
            if(root->right != nullptr)
            {
                root = root->right;
            }
            else
            {
                root->right = new Node { std::move(value) * 100, std::move(value), 0, nullptr, nullptr };
                this->exportToFile("Insertion");
                balance(m_root, root->right);
                break;
            }
        }
    }
}

template <typename T>
void AVL<T>::deleteNode(const T& value)
{
    deleteNode(value, m_root);
}

template <typename T>
void AVL<T>::deleteNode(const T& value, Node* root)
{
    //
}

template <typename T>
int8 AVL<T>::height(Node* node)
{
    return (node != nullptr) ? node->height : -1;
}

template <typename T>
void AVL<T>::balance(Node*& root, Node* leaf)
{
    if(leaf == nullptr)
    {
        return;
    }

    Stack<int8>  heights;
    Stack<Node*> nodes;
    Node* currentNode {root};
    while(currentNode != leaf)
    {
        nodes.push(currentNode);
        if(leaf->idata < currentNode->idata)
        {
            heights.push(height(currentNode->right));
            currentNode = currentNode->left;
        }
        else
        {
            heights.push(height(currentNode->left));
            currentNode = currentNode->right;
        }
    }

    while(!(nodes.empty() & heights.empty()))
    {
        std::string text
        {
            "Let's Balance!\r\n Current Pivot -> " +
            std::to_string(nodes.top()->idata) +
            "\r\nCurrent Node (child) -> "+
            std::to_string(currentNode->idata) +
            "\r\nCurrent Node height: " +
            std::to_string(currentNode->height) +
            "\r\n" +
            "\r\nNodes: " +
            nodes.getStr() +
            "\r\nHeights: " +
            heights.getStr()
        };
        this->exportToFile(text);

        /* If the difference is greater than 1, it does rotations */
        if(abs(currentNode->height - heights.top()) > IMBALANCE_CONSTANT)
        {
            Node* parent  = nodes.pop();
            int8  parentH = heights.pop();

            /* If current node is the left child of its parent */
            if(currentNode == parent->left)
            {
                if(height(currentNode->left) <= height(currentNode->right))
                {
                    Node* aux = currentNode->right;
                    if(nodes.getSize() == 0)
                    {
                        rotateLeftRight(root);
                    }
                    else
                    {
                        rotateLeftRight((parent == nodes.top()->left) ? nodes.top()->left : nodes.top()->right);
                    }

                    nodes.push(aux);
                    heights.push(parentH);

                    nodes.push(parent);
                    heights.push(std::max(height(currentNode->left), height(currentNode->right)) + 1);

                    nodes.push(currentNode);
                    heights.push(height(currentNode->left));
                }
                else
                {
                    if(nodes.getSize() == 0)
                    {
                        rotateRight(root);
                    }
                    else
                    {
                        rotateRight((parent == nodes.top()->left) ? nodes.top()->left : nodes.top()->right);
                    }

                    nodes.push(currentNode);
                    heights.push(height(currentNode->left));

                    nodes.push(parent);
                    heights.push(parentH);
                }
            }
            /* If current node is the right child of its parent */
            else
            {
                if(height(currentNode->left) <= height(currentNode->right))
                {
                    if(nodes.getSize() == 0)
                    {
                        rotateLeft(root);
                    }
                    else
                    {
                        rotateLeft((parent == nodes.top()->left) ? nodes.top()->left : nodes.top()->right);
                    }

                    nodes.push(currentNode);
                    heights.push(height(currentNode->right));

                    nodes.push(parent);
                    heights.push(parentH);
                }
                else
                {
                    Node* aux = currentNode->left;
                    if(nodes.getSize() == 0)
                    {
                        rotateRightLeft(root);
                    }
                    else
                    {
                        rotateRightLeft((parent == nodes.top()->left) ? nodes.top()->left : nodes.top()->right);
                    }

                    nodes.push(aux);
                    heights.push(parentH);

                    nodes.push(parent);
                    heights.push(std::max(height(currentNode->left), height(currentNode->right)) + 1);

                    nodes.push(currentNode);
                    heights.push(height(currentNode->right));
                }
            }
        }

        currentNode = nodes.pop();
        heights.pop();
        currentNode->height = std::max(height(currentNode->left), height(currentNode->right)) + 1;

        currentNode->data   = currentNode->idata * 100 + currentNode->height;

        text = "Balanced!\r\nCurrent Node -> " +
                std::to_string(currentNode->idata) +
                "\r\nCurrent Node height: " +
                std::to_string(currentNode->height) +
                "\r\n" +
                "\r\nNodes: " +
                nodes.getStr() +
                "\r\nHeights: " +
                heights.getStr();

        this->exportToFile(text);
    }
}

template <typename T>
void AVL<T>::rotateLeft(Node*& root)
{
    Node* oldRoot {root};
    root = root->right;
    oldRoot->right = root->left;
    root->left = oldRoot;
    this->exportToFile("Rotate: Left, from" + std::to_string(oldRoot->data));
}

template <typename T>
void AVL<T>::rotateRight(Node*& root)
{
    Node* oldRoot {root};
    root = root->left;
    oldRoot->left = root->right;
    root->right = oldRoot;
    this->exportToFile("Rotate: Right, from " + std::to_string(oldRoot->data));
}

template <typename T>
void AVL<T>::rotateRightLeft(Node*& root)
{
    this->exportToFile("Rotate: Right-Left, from " + std::to_string(root->data));
    rotateRight(root->right);
    rotateLeft(root);
}

template <typename T>
void AVL<T>::rotateLeftRight(Node*& root)
{
    this->exportToFile("Rotate: Left-Right, from " + std::to_string(root->data));
    rotateLeft(root->left);
    rotateRight(root);
}

template <typename T>
void AVL<T>::test()
{
    rotateRightLeft(m_root->right);
}

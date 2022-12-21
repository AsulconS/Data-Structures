template <typename T, typename Node>
bool IBST<T, Node>::debugMode {false};

template <typename T, typename Node>
uint32 IBST<T, Node>::filesCount {};

template <typename T, typename Node>
IBST<T, Node>::~IBST()
{
    makeEmpty();
    std::cout << "Tree fully destructed" << std::endl;
}

template <typename T, typename Node>
void IBST<T, Node>::makeEmpty()
{
    makeEmpty(m_root);
}

template <typename T, typename Node>
void IBST<T, Node>::makeEmpty(Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    Stack<Node*> trash;
    Stack<Node*> stack;
    while(true)
    {
        if(root != nullptr)
        {
            stack.push(root);
            root = root->left;
        }
        else
        {
            if(stack.empty())
            {
                break;
            }

            root = stack.pop();
            trash.push(root);
            root = root->right;
        }
    }

    while(!trash.empty())
    {
        delete trash.pop();
    }
}

template <typename T, typename Node>
Node* IBST<T, Node>::find(const T& value)
{
    m_nodes.clear();
    return find(value, m_root);
}

template <typename T, typename Node>
Node* IBST<T, Node>::find(const T& value, Node*& root)
{
    if(root == nullptr)
    {
        return nullptr;
    }

    Node* currentNode {root};
    while((currentNode != nullptr) && (value != currentNode->data))
    {
        if(value < currentNode->data)
        {
            m_nodes.push(currentNode);
            currentNode = currentNode->left;
        }
        else
        {
            m_nodes.push(currentNode);
            currentNode = currentNode->right;
        }
    }

    return currentNode;
}

template <typename T, typename Node>
Node* IBST<T, Node>::findMinNode()
{
    m_nodes.clear();
    return findMinNode(m_root);
}

template <typename T, typename Node>
Node* IBST<T, Node>::findMinNode(Node*& root)
{
    if(root == nullptr)
    {
        return nullptr;
    }

    Node* currentNode {root};
    while(currentNode->left != nullptr)
    {
        m_nodes.push(currentNode);
        currentNode = currentNode->left;
    }

    return currentNode;
}

template <typename T, typename Node>
Node* IBST<T, Node>::findMaxNode()
{
    m_nodes.clear();
    return findMaxNode(m_root);
}

template <typename T, typename Node>
Node* IBST<T, Node>::findMaxNode(Node*& root)
{
    if(root == nullptr)
    {
        return nullptr;
    }

    Node* currentNode {root};
    while(currentNode->right != nullptr)
    {
        m_nodes.push(currentNode);
        currentNode = currentNode->right;
    }

    return currentNode;
}

template <typename T, typename Node>
void IBST<T, Node>::traverseInOrder()
{
    traverseInOrder(m_root);
}

template <typename T, typename Node>
void IBST<T, Node>::traversePreOrder()
{
    traversePreOrder(m_root);
}

template <typename T, typename Node>
void IBST<T, Node>::traversePostOrder()
{
    traversePostOrder(m_root);
}

template <typename T, typename Node>
void IBST<T, Node>::traverseInOrder(Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    Stack<Node*> stack;
    while(true)
    {
        if(root != nullptr)
        {
            stack.push(root);
            root = root->left;
        }
        else
        {
            if(stack.empty())
            {
                break;
            }

            root = stack.pop();
            std::cout << root->data << ' ';
            root = root->right;
        }
    }
}

template <typename T, typename Node>
void IBST<T, Node>::traversePreOrder(Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    Stack<Node*> stack;
    while(true)
    {
        if(root != nullptr)
        {
            std::cout << root->data << ' ';
            stack.push(root);
            root = root->left;
        }
        else
        {
            if(stack.empty())
            {
                break;
            }

            root = stack.pop();
            root = root->right;
        }
    }
}

template <typename T, typename Node>
void IBST<T, Node>::traversePostOrder(Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    Stack<Node*> stack;
    while(true)
    {
        if(root != nullptr)
        {
            stack.push(root);
            root = root->left;
        }
        else
        {
            if(stack.empty())
            {
                break;
            }

            Node* temp = stack.top()->right;
            if(temp == nullptr)
            {
                temp = stack.pop();
                std::cout << temp->data << ' ';
                while(!stack.empty() && temp == stack.top()->right)
                {
                    temp = stack.pop();
                    std::cout << temp->data << ' ';
                }
            }
            else
            {
                root = temp;
            }  
        }
    }
}

template <typename T, typename Node>
void IBST<T, Node>::recursiveTInOrder()
{
    recursiveTInOrder(m_root);
}

template <typename T, typename Node>
void IBST<T, Node>::recursiveTPreOrder()
{
    recursiveTPreOrder(m_root);
}

template <typename T, typename Node>
void IBST<T, Node>::recursiveTPostOrder()
{
    recursiveTPostOrder(m_root);
}

template <typename T, typename Node>
void IBST<T, Node>::recursiveTInOrder(Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    recursiveTInOrder(root->left);
    std::cout << root->data << ' ';
    recursiveTInOrder(root->right);
}

template <typename T, typename Node>
void IBST<T, Node>::recursiveTPreOrder(Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    std::cout << root->data << ' ';
    recursiveTPreOrder(root->left);
    recursiveTPreOrder(root->right);
}

template <typename T, typename Node>
void IBST<T, Node>::recursiveTPostOrder(Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    recursiveTPostOrder(root->left);
    recursiveTPostOrder(root->right);
    std::cout << root->data << ' ';
}

template <typename T, typename Node>
void IBST<T, Node>::exportToFile(const std::string& title)
{
    if(m_root == nullptr)
    {
        return;
    }

    std::string fn {thisName() + std::to_string(filesCount++) + ".dot"};
    std::ofstream of;
    of.open(fn, std::ios::binary);

    std::string header1
    {
        "graph IBST\r\n"
        "{\r\n"
        "    // Title Properties\r\n"
        "    // --------------------------------------------------------------------------------\r\n"
        "    labelloc = \"t\";\r\n"
        "    label = "
    };
    header1 += '\"' + title + "\";\r\n";

    std::string header2
    {
        "\r\n"
        "    // Binary Search Tree Properties\r\n"
        "    // --------------------------------------------------------------------------------\r\n"
        "    graph [ dpi = 300, nodesep = 0.25, ranksep = 0.3, splines = line, margin = 0.8 ];\r\n"
        "    node  [ fontname = \"Bitstream Vera Sans\",\r\n"
        "            fontsize = 14,\r\n"
        "            style = filled, fillcolor = lightblue,\r\n"
        "            shape = circle, fixedsize = true, width = 0.7 ];\r\n"
        "    // --------------------------------------------------------------------------------\r\n"
    };

    std::string header {header1 + header2};

    std::string labels
    {
        "    // Labels\r\n"
        "    // --------------------------------------------------------------------------------\r\n"
    };

    std::string lDummies {};
    std::string mDummies {};
    std::string rDummies {};

    std::string relations
    {
        "    // Relations\r\n"
        "    // --------------------------------------------------------------------------------\r\n"
    };

    std::string lSeparations {"    edge [ style = dotted, weight = 10 ];\r\n"};
    std::string mSeparations {"    edge [ style = invis , weight = 20 ];\r\n"};
    std::string rSeparations {"    edge [ style = dotted, weight = 10 ];\r\n"};

    Node* root {m_root};
    labels += "    l" + std::to_string(root->data);
    labels += " [ " + root->label + " ];\r\n";
    labels += "\r\n";

    Stack<Node*> stack;
    while(true)
    {
        if(root != nullptr)
        {
            // --------------------------------------------------------------------
            bool hasLC = root->left != nullptr;
            bool hasRC = root->right != nullptr;

            std::string llabel {"    ld" + std::to_string(root->data) + ";\r\n"};
            std::string rlabel {"    rd" + std::to_string(root->data) + ";\r\n"};
            std::string relation {};
            if(hasLC)
            {
                llabel  = "    l" + std::to_string(root->left->data);
                llabel += " [ " + root->left->label + " ];\r\n";

                relation += 'l' + std::to_string(root->left->data) + ' ';
            }
            if(hasRC)
            {
                rlabel  = "    l" + std::to_string(root->right->data);
                rlabel += " [ " + root->right->label + " ];\r\n";

                relation += 'l' + std::to_string(root->right->data) + ' ';
            }

            if(hasLC | hasRC)
            {
                labels += llabel;
                labels += "    m" + std::to_string(root->data) + ";\r\n";
                labels += rlabel;
                labels += "\r\n";

                if(!hasLC)
                {
                    lDummies += "    ld" + std::to_string(root->data) + ",\r\n";
                    lSeparations += "    l" + std::to_string(root->data) + " -- ";
                    lSeparations += "ld" + std::to_string(root->data) + ";\r\n";
                }

                mDummies += "    m" + std::to_string(root->data) + ",\r\n";
                mSeparations += "    l" + std::to_string(root->data) + " -- ";
                mSeparations += "m" + std::to_string(root->data) + ";\r\n";

                if(!hasRC)
                {
                    rDummies += "    rd" + std::to_string(root->data) + ",\r\n";
                    rSeparations += "    l" + std::to_string(root->data) + " -- ";
                    rSeparations += "rd" + std::to_string(root->data) + ";\r\n";
                }

                relations += "    l" + std::to_string(root->data);
                relations += " -- { " + relation + "};\r\n";
            }
            // --------------------------------------------------------------------

            stack.push(root);
            root = root->left;
        }
        else
        {
            if(stack.empty())
            {
                break;
            }

            root = stack.pop();
            root = root->right;
        }
    }
    if(!lDummies.empty())
    {
        lDummies[lDummies.size() - 3] = ' ';
        lDummies += "    [ style = dotted, label = \"\" ];\r\n";
    }
    if(!mDummies.empty())
    {
        mDummies[mDummies.size() - 3] = ' ';
        mDummies += "    [ style = invis , label = \"\" ];\r\n";
    }
    if(!rDummies.empty())
    {
        rDummies[rDummies.size() - 3] = ' ';
        rDummies += "    [ style = dotted, label = \"\" ];\r\n";
    }

    std::string dummies
    {
        "    // Dummies\r\n"
        "    // --------------------------------------------------------------------------------\r\n"
    };
    dummies += lDummies + "\r\n" + mDummies + "\r\n" + rDummies;

    std::string separations
    {
        "    // Separations\r\n"
        "    // --------------------------------------------------------------------------------\r\n"
    };
    separations += lSeparations + "\r\n" + mSeparations + "\r\n" + rSeparations;

    std::string content {header + "\r\n" + labels + "\r\n" + dummies + "\r\n" + relations + "\r\n" + separations + "}\r\n"};
    of << content;
    of.close();
}

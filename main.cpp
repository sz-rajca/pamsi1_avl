#include <iostream>
#include <queue>

struct Node {
    int value;
    int height;
    Node *right_prt;
    Node *left_prt;
};

Node *get_node(int value) {
    auto new_node = new Node();
    new_node->value = value;
    new_node->height = 0;
    new_node->left_prt = nullptr;
    new_node->right_prt = nullptr;
    return new_node;
}

Node *find_min(Node *root) {
    while (root->left_prt != nullptr) {
        root = root->left_prt;
    }
    return root;
}

void pre_order(Node *root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->value << ' ';
    pre_order(root->left_prt);
    pre_order(root->right_prt);
}

void in_order(Node *root) {
    if (root == nullptr) {
        return;
    }
    in_order(root->left_prt);
    std::cout << root->value << ' ';
    in_order(root->right_prt);
}

void post_order(Node *root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->value << ' ';
    post_order(root->left_prt);
    post_order(root->right_prt);
}

void print_root(Node *root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->value;
}

int height(Node *root) {
    if (!root) {
        return -1;
    }
    return std::max(height(root->left_prt), height(root->right_prt)) + 1;
}

Node *right_rotation(Node *root) {
    Node *temp = root->left_prt;
    root->left_prt = temp->right_prt;
    temp->right_prt = root;
    root->height = std::max(height(root->left_prt), height(root->right_prt)) + 1;
    temp->height = std::max(height(temp->left_prt), root->height) + 1;
    return temp;
}

Node *left_rotation(Node *root) {
    Node *temp = root->right_prt;
    root->right_prt = temp->left_prt;
    temp->left_prt = root;
    root->height = std::max(height(root->left_prt), height(root->right_prt)) + 1;
    temp->height = std::max(height(root->right_prt), root->height) + 1;
    return temp;
}

Node *left_right_rotation(Node *root) {
    root->right_prt = right_rotation(root->right_prt);
    return left_rotation(root);
}

Node *right_left_rotation(Node *root) {
    root->left_prt = left_rotation(root->left_prt);
    return right_rotation(root);
}

Node *insert(Node *root, int value) {
    if (root == nullptr) {
        root = get_node(value);
    } else if (value < root->value) {
        root->left_prt = insert(root->left_prt, value);
        if (height(root->left_prt) - height(root->right_prt) == 2) {
            if (value < root->left_prt->value) {
                root = right_rotation(root);
            } else {
                root = right_left_rotation(root);
            }
        }
    } else if (value > root->value) {
        root->right_prt = insert(root->right_prt, value);
        if (height(root->right_prt) - height(root->left_prt) == 2) {
            if (value > root->right_prt->value) {
                root = left_rotation(root);
            } else {
                root = left_right_rotation(root);
            }
        }
    }
    root->height = std::max(height(root->left_prt), height(root->right_prt) + 1);
    return root;
}

Node *remove(Node *root, int value) {
    Node *temp;
    if (root == nullptr) {
        return nullptr;
    } else if (value < root->value) {
        root->left_prt = remove(root->left_prt, value);
    } else if (value > root->value) {
        root->right_prt = remove(root->right_prt, value);
    }
    else if (root->left_prt && root->right_prt) {
        temp = find_min(root->right_prt);
        root->value = temp->value;
        root->right_prt = remove(root->right_prt, root->value);
    } else {
        temp = root;
        if (root->left_prt == nullptr) {
            root = root->right_prt;
        } else if (root->right_prt == nullptr) {
            root = root->left_prt;
        }
        delete temp;
    }
    if (root == nullptr) {
        return root;
    }
    root->height = std::max(height(root->left_prt), height(root->right_prt)) + 1;
    if (height(root->left_prt) - height(root->right_prt) == 2) {
        if (height(root->left_prt->left_prt) - height(root->left_prt->right_prt) == 1) {
            return left_rotation(root);
        } else {
            return left_right_rotation(root);
        }
    } else if (height(root->right_prt) - height(root->left_prt) == 2) {
        if (height(root->right_prt->right_prt) - height(root->right_prt->left_prt) == 1) {
            return right_rotation(root);
        } else {
            return right_left_rotation(root);
        }
    }
    return root;
}

void level_order(Node *root) {
    if (root == nullptr) {
        return;
    }
    std::queue<Node *> Q;
    Q.push(root);
    while (!Q.empty()) {
        Node *current = Q.front();
        Q.pop();
        std::cout << current->value << " ";
        if (current->left_prt != nullptr) {
            Q.push(current->left_prt);
        }
        if (current->right_prt != nullptr) {
            Q.push(current->right_prt);
        }
    }
}

int main() {
    int a[] = {50, 14, 8, 32, 40, 80, 1, 22, 30, 4, 48, 75, 42, 45, 53};
    Node *root = nullptr;
    for (int i : a) {
        root = insert(root, i);
    }
    std::cout << "level_order: ";
    level_order(root);
    std::cout << std::endl << "pre_order: ";
    pre_order(root);
    std::cout << std::endl << "in_order: ";
    in_order(root);
    std::cout << std::endl << "post_order: ";
    post_order(root);
    remove(root, 40);
    std::cout << std::endl << "root: ";
    print_root(root);
    std::cout << std::endl << "in_order: ";
    in_order(root);
    std::cout << std::endl << "height: " << height(root) << std::endl;
    return 0;
}
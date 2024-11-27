#include<iostream>
#include<queue>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int value){
        data = value;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int value){
    if(root == nullptr){
        return new Node(value);
    }
    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if(temp->left == NULL){
            temp->left = new Node(value);
            break;
        }
        else{
            q.push(temp->left);
        }

        if(temp->right == NULL){
            temp->right = new Node(value);
            break;
        }
        else{
            q.push(temp->right);
        }
    }

    return root;
}

void display(Node* root){
    if(root){
        display(root->left);
        cout << root->data << " ";
        display(root->right);
    }
}

int findDepth(Node* root){
    if(root == NULL) return 0;
    int leftDepth = findDepth(root->left);
    int rightDepth = findDepth(root->right);
    return max(leftDepth,rightDepth) + 1;    
}

void displayLeafNodes(Node* root){
    if(root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        cout << root->data << " ";
    }
    displayLeafNodes(root->left);
    displayLeafNodes(root->right);
}

Node* copyTree(Node* root){
    if(root == NULL) return NULL;
    Node* newRoot = new Node(root->data);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}

int main(){
    Node* root = NULL;
    int choice, value;

    while(true){
        cout << "Menu:\n";
        cout << "1. Display Tree\n";
        cout << "2. Insert Values into Tree\n";
        cout << "3. Find Tree Depth\n";
        cout << "4. Display Leaf Nodes\n";
        cout << "5. Display Copied Tree\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                cout<<"My Tree: ";
                display(root);
                cout<<endl;
                break;
            case 2:
                cout<<"Enter  value to insert: ";
                cin>>value;
                root = insert(root, value);
                break;
            case 3:
                cout<<"Tree Depth:"<<findDepth(root)<<endl;
                break;
            case 4:
                cout<<"Leaf Nodes: ";
                displayLeafNodes(root);
                cout<<endl;
                break;
            case 5:{
                Node* copiedTree = copyTree(root);
                cout<<"Copied Tree: ";
                display(copiedTree);
                cout<<endl;
                break;
            }
            case 6:
                return 0;

            default:
                cout<<"Invalid choice. Please choose a valid option.\n";
                break;
        }
    }

    return 0;
}
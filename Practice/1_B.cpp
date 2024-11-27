#include<iostream>
#include<queue>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value){
        data = value;
        left = right = NULL;
    }
};

Node* insert(Node* root, int value){
    if(root == NULL){
        return new Node(value);
    }
    if (value < root->data){
        root->left = insert(root->left, value);
    } else{
        root->right = insert(root->right, value);
    }

    return root;
}

Node* findMin(Node* root){
    while(root->left != NULL) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int value){
    if(root == NULL) return root;
    if(value < root->data){
        root->left = deleteNode(root->left, value);
    } else if (value > root->data){
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL){
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void display(Node* root){
    if (root == NULL){
        return;
    }
    display(root->left);
    cout<<root->data<<" ";
    display(root->right);
}

Node* search(Node* root, int value){
    if(root == NULL  || root->data == value) return root;
    if (value < root->data) return search(root->left, value);
    return search(root->right, value);
}

void bfs(Node* root){
    if(root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* current = q.front();
        q.pop();
        cout<<current->data << " ";
        if(current->left != NULL) q.push(current->left);
        if(current->right != NULL) q.push(current->right);
    }
}

int main(){
    Node* root = NULL;
    int choice, value;

    while(true){
        cout<<"Menu:\n";
        cout<<"1. Insert\n";
        cout<<"2. Delete\n";
        cout<<"3. Display Tree (In-Order Traversal)\n";
        cout<<"4. Search\n";
        cout<<"5. Breadth-First Search (BFS)\n";
        cout<<"6. Exit\n";
        cout<<"Enter your choice:";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter value to insert: ";
                cin>>value;
                root = insert(root, value);
                break;
            case 2:
                cout<<"Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                break;
            case 3:
                cout<<"BST In-Order Traversal: ";
                display(root);
                cout<<endl;
                break;
            case 4:
                cout<<"Enter value to search: ";
                cin>>value;
                if(search(root, value)){
                    cout<<"Node "<<value<<" found in BST."<<endl;
                } else {
                    cout<<"Node "<<value<<" not found in BST."<<endl;
                }
                break;
            case 5:
                cout<<"BFS (Level-wise Print): ";
                bfs(root);
                cout<<endl;
                break;
            case 6:
                return 0;
            default:
                cout<<"Invalid choice, please try again"<<endl;
        }
    }

    return 0;
}
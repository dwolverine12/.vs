#include<iostream>
#include<stack>
#include<string>
#include<sstream>

using namespace std;

struct Node{
    string data;
    Node *lchild ;
    Node *rchild ;

    Node(string datavalue) : data(datavalue), lchild(nullptr), rchild(nullptr) {}
};

struct ExpressionTree{
    int precedence(char c){
        if(c == '+' || c == '-') return 1;
        if(c == '*' || c == '/') return 2;
        if(c == '^') return 3;
        return -1;
    }

    string infixToPostfix(const string& infix){
        stack<char> st;
        string postfix;
        int n = infix.length();

        for (int i = 0; i < n; i++){
            char c = infix[i];

            if(isalnum(c)){
                postfix += c;
                while(i + 1 < n && isalnum(infix[i+1])){
                    postfix += infix[++i];
                }
                postfix += ' ';
            } else if(c == '(') {
                st.push(c);
            }else if (c == ')') {
                while (!st.empty() && st.top() != '(') {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                if (st.empty()){
                    cout<<"Mismatched parantheses"<< endl;
                    return "";
                }
                st.pop();
            } else if(c == '-'){
                if(i==0 ||(!isalnum(infix[i-1] && infix[i-1] != ')'))){
                    postfix += c;
                    while(i + 1 < n && isalnum(infix[i + 1])) {
                        postfix += infix[++i];
                    }
                    postfix += ' ';
                } else {
                    while (!st.empty() && precedence(st.top()) >= precedence(c) && st.top() != '(') {
                        postfix += st.top();
                        postfix += ' ';
                        st.pop();
                    }
                    st.push(c);
                }
            } else {
                while (!st.empty() && precedence(st.top()) >= precedence(c) && st.top()!= '(')  {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                st.push(c);
            }
        }

        while(!st.empty()){
            if(st.top() == '('){
                cout<<"Mismatched parantheses"<< endl;
                return "";
            }
            postfix += st.top();
            postfix += ' ';
            st.pop();
        }
        return postfix;
    }

    Node* constructTree(const string& postfix){
        stack<Node*> st;
        istringstream iss(postfix);
        string token;

        while(iss >> token) {
            if(token.length() == 1 && !isalnum(token[0])) {
                if (st.size() < 2) {
                    cout << "Invalid postfix expression" << endl;
                    return nullptr;
                }
                Node* t = new Node(token);

                Node* t1 = st.top(); st.pop();
                Node* t2 = st.top(); st.pop();

                t->lchild = t2;
                t->rchild = t1;

                st.push(t);
            }else{
                Node* t = new Node(token);

                st.push(t);
            }
        }

        if(st.size()!=1){
            cout << "Invalid postfix expression" << endl;
            return nullptr;
        }

        return st.top();
    }

    void nonRecursiveInorder(Node* root){
        if (root == nullptr){
            cout<<"Tree is empty."<<endl;
            return;
        }

        stack<Node*> s;
        Node* curr = root;

        while(curr!=nullptr || !s.empty()){
            while(curr!=nullptr){
                s.push(curr);
                curr = curr->lchild;
            }
            curr = s.top();
            s.pop();
            cout<<curr->data<<" ";
            curr = curr->rchild;
        }
    }

    void nonRecursivePreorder(Node* root){
        if (root == nullptr){
            cout<<"Tree is empty."<<endl;
            return;
        }

        stack<Node*> nodeStack;
        nodeStack.push(root);

        while(!nodeStack.empty()) {
            Node* node = nodeStack.top();
            cout<< node->data<<" ";
            nodeStack.pop();

            if(node->rchild) nodeStack.push(node->rchild);
            if(node->lchild) nodeStack.push(node->lchild);
        }
    }

    void nonRecursivePostorder(Node* root){
        if (root == nullptr){
            cout<<"Tree is empty."<<endl;
            return;
        }

        stack<Node*> s1, s2;
        s1.push(root);
        Node* node;

        while(!s1.empty()){
            node = s1.top();
            s1.pop();
            s2.push(node);

            if(node->lchild) s1.push(node->lchild);
            if(node->rchild) s1.push(node->rchild);
        }
        
        while(!s2.empty()){
            node = s2.top();
            s2.pop();
            cout<<node->data<<" ";
        }
    }
};

int main(){
    ExpressionTree et;
    Node* root = nullptr;
    string infix, postfix;
    int choice;

    while(true){
        cout<<"1. Convert Infix to Postfix and Construct Expression Tree\n";
        cout<<"2. Non-recursive Inorder Traversal\n";
        cout<<"3. Non-recursive Preorder Traversal\n";
        cout<<"4. Non-recursive Postorder Traversal\n";
        cout<<"5. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice) {
            case 1:
                cout<<"Enter Infix Expression: ";
                cin >> infix;
                postfix = et.infixToPostfix(infix);
                if(postfix.empty()) break;
                cout<<"Postfix Expression: " << postfix << endl;

                root = et.constructTree(postfix);
                if(root){
                    cout<<"Expression Tree constructed:\n";
                }
                break;
            case 2:
                cout<<"Non-recursive Inorder Traversal: ";
                et.nonRecursiveInorder(root);
                cout<<endl;
                break;

            case 3:
                cout<<"Non-recursive Preorder Traversal: ";
                et.nonRecursivePreorder(root);
                cout<<endl;
                break;
            
            case 4:
                cout<<"Non-recursive Postorder Traversal: ";
                et.nonRecursivePostorder(root);
                cout<<endl;
                break;
            case 5:
                cout<<"Exiting Program."<<endl;
                return 0;
            default:
                cout<<"Invalid Choice. Please choose a valid option."<<endl;
        }
    }
}
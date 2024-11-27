#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class User{
    public:
        string name;
        string dob;
        int comments;
        vector<string> friends;

        User(string n, string d, int c) : name(n), dob(d), comments(c) {}
};

class SocialNetwork{
    unordered_map<string, User*> users;

    public:
        void addUser(string name, string dob, int comments){
            if(users.find(name) == users.end()){
                users[name] = new User(name,dob,comments);
            } else{
                cout<<"User already exists! "<<endl;
            }
        }

        void addFriendship(string user1, string user2){
            if (users.find(user1) != users.end() && users.find(user2) != users.end()) {
                users[user1] -> friends.push_back(user2);
                users[user2] -> friends.push_back(user1);
            } else{
                cout<<"One or both users do not exist! "<<endl;
            }
        }

        void maxFriends(){
            int max_count = 0;
            string max_user = "";
            for (auto& pair: users){
                if (pair.second->friends.size() > max_count) {
                    max_count = pair.second->friends.size();
                    max_user = pair.first;
                }
            }

            if(max_user!=""){
                cout<<"User with maximum friends: "<< max_user<<" (" << max_count << " friends)"<<endl;
            } else{
                cout<<"No users found!" << endl;
            }
        }

        void maxMinComments(){
            if(users.empty()) {
                cout<<"No users found!"<<endl;
                return;
            }

            auto max_user = users.begin();
            auto min_user = users.begin();

            for (auto it = users.begin(); it!=users.end(); ++it){
                if (it->second->comments > max_user->second->comments) {
                    max_user = it;
                }
                if(it->second->comments < min_user->second->comments) {
                    min_user = it;
                }
            }
            cout<<"User with maximum comments: "<<max_user->first << " (" << max_user->second->comments << " comments)" << endl;
            cout<<"User with minimum comments: "<<min_user->first << " (" << min_user->second->comments << " comments)" << endl;
        }

        void birthdayInMonth(int month){
            bool found = false;
            for (auto& pair: users) {
                int user_month = stoi(pair.second->dob.substr(3, 2));
                if(user_month == month){
                    cout<<pair.first<<" has a birthday this month ("<<pair.second->dob << ")" <<endl;
                    found = true;
                }
            }
            if(!found){
                cout<<"No users with birthday in this month!" << endl;
            }
        }
};

int main(){
    SocialNetwork sn;
    int choice;

    do {
        cout<<"1. Add User\n";
        cout<<"2. Add Friendship\n";
        cout<<"3. Find User with Maximum Friends\n";
        cout<<"4. Find User with maximum and minimum comments\n";
        cout<<"5. Find users with Birthdays in this month\n";
        cout<<"6. Exit\n";
        cout<<"Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:{
                string name, dob;
                int comments;
                cout<<"Enter name: ";
                cin>>name;
                cout<<"Enter DOB (DD/MM/YYYY): ";
                cin>>dob;
                cout<<"Enter number of comments: ";
                cin>>comments;
                sn.addUser(name, dob, comments);
                cout<<"User added successfully"<<endl;
                break;
            }
            case 2:{
                string user1, user2;
                cout<<"Enter user1: ";
                cin>>user1;
                cout<<"Enter user2: ";
                cin>>user2;
                sn.addFriendship(user1, user2);
                cout<<"Friendship created !"<< endl;
                break;
            }
            case 3:
                sn.maxFriends();
                break;
            case 4:
                sn.maxMinComments();
                break;
            case 5:{
                int month;
                cout<< "Enter the month (1-12): ";
                cin>>month;
                sn.birthdayInMonth(month);
                break;
            }
            case 6:
                cout<<"Exiting... "<<endl;
                break;
            default:
                cout<<"Invalid choice!"<<endl;
        }
    } while(choice != 6);

    return 0;
}

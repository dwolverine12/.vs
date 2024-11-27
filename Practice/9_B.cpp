#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Job {
    int id, deadline, profit;
};

vector<Job> getJobInput()
{
    int n;
    cout<<"Enter the number of jobs: ";
    cin>>n;

    vector<Job> jobs(n);

    for(int i=0; i<n; i++){
        cout<<"Enter deadline and profit for job "<<(i + 1) << ": ";
        cin>>jobs[i].deadline>>jobs[i].profit;
        jobs[i].id = i + 1;
    }

    return jobs;
}

vector<int> selectJobs(vector<Job> &jobs){
    sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b){
        return a.profit > b.profit;
    });
    vector<int> seq;
    int time = 0;

    for(const auto &curr : jobs){
        if(curr.deadline > time){
            seq.push_back(curr.id);
            time++;
        }
    }
    return seq;
}

int main(){
    vector<Job> jobs = getJobInput();
    vector<int> selectedJobs = selectJobs(jobs);

    cout<<"Max jobs: " << selectedJobs.size() << endl;
    cout<<"Selected Job IDs: ";
    for(int id: selectedJobs){
        cout<<id<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}
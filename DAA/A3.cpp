#include <bits/stdc++.h>
using namespace std;

// Function to solve the 0/1 Knapsack problem using memoization
int knapsackUtil(vector<int>& wt, vector<int>& val, int ind, int W, vector<vector<int>>& dp) {
    // Base case: If there are no items left or the knapsack has no capacity, return 0
    if (ind == 0 ) {
        if(wt[0]<=W)
        {
            return val[0];
        }
        else return 0;
    }

    // If the result for this state is already calculated, return that stored value
    if (dp[ind][W] != -1) {
        return dp[ind][W];
    }

    // Calculate the maximum value by either excluding the current item or including it
    int notTaken = knapsackUtil(wt, val, ind - 1, W, dp);
    int taken = INT_MIN;

    // Check if the current item can be included without exceeding the knapsack's capacity
    if (wt[ind] <= W) {
        taken = val[ind] + knapsackUtil(wt, val, ind - 1, W - wt[ind], dp);
    }

    // Store the result in the DP table and return
    return dp[ind][W] = max(notTaken, taken);
}

// Function to solve the 0/1 Knapsack problem
int knapsack(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n, vector<int>(W + 1, -1)); //intial val =-1, W+1 cause if capacity is 
    return knapsackUtil(wt, val, n - 1, W, dp);        //6 matrix has 0 to 6 ie. 7 places- W+1 =6+1
}

int main() {
    int W, n;
    cout<<"enter number of items"<<endl;
    cin>>n;

   // int temp; //ig local scope
    vector<int> wt(n);
    cout<<"enter weights"<<endl;
    for(int i=0;i<n;i++) 
    {    
       // cin>>temp;
       // wt.push_back(temp);
       cin>>wt[i];
    }

    vector<int> val;
    cout<<"enter values"<<endl;
    for(int i=0;i<n;i++)
    {
        //cin>>temp;
        //val.push_back(temp);
        cin>>val[i];
    }

    cout<<"enter capacity"<<endl;
    cin>>W;

    //vector<int> wt = {1, 2, 4, 5};
    //vector<int> val = {5, 4, 8, 6};
    //int W = 5;
    //int n = wt.size();

    cout << "The Maximum value of items the thief can steal is " << knapsack(wt, val, n, W);

    return 0;
}


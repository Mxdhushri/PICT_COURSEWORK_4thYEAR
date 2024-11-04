#include<bits/stdc++.h>
using namespace std;
void nqueens(vector<vector<int>>board,int row,vector<int>cols,vector<int>diags,vector<int>rdiags, int n)
{
    if(row==n)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    for(int col=0;col<n;col++) // For current row 'row' try to place the queen in every column
    {
        if(cols[col]==0 && diags[row+col]==0 && rdiags[row-col+board[0].size()-1]==0) 
        // Check if the queen can be placed (By checking whether column, and diagonals are occupied or not)
        {
            board[row][col]=1; //place queen
            cols[col]=1;
            diags[row+col]=1;
            rdiags[row-col+board[0].size()-1]=1;

            nqueens(board,row+1,cols,diags,rdiags,n); // place queen in next queen

            // backtrack
            cols[col]=0;
            diags[row+col]=0;
            rdiags[row-col+board[0].size()-1]=0;
            board[row][col]=0;
        }
    }
}
int main()
{
    int n;
    cin>>n;
    vector<vector<int>>board(n,vector<int>(n,0));
    vector<int>cols(n,0);
    vector<int>diags(2*n-1,0); 
    vector<int>rdiags(2*n-1,0);
    int row=0;
    nqueens(board,row,cols,diags,rdiags,n);
    return 0;
}
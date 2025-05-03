#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono; //time

class Graph
{
    int V; //vertices
    vector<vector<int>> adj; //adjacency list

public:
    Graph(int V)
    {
        this->V = V;         // initializes no.of vertices
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);  //0->1
        adj[v].push_back(u); // 1->0 , Undirected(both ways)
    }

    void sequentialBFS(int start, vector<int> &sbfsSequence) //seq bfs sequence
    {
        vector<bool> visited(V,false);  //size:5
        queue <int> q;
        q.push(start);   //q mai 0
        visited[start]=true;

        while(!q.empty())
        {
            int node= q.front();     //0 ko q mai daalo
            q.pop();                 //then pop 0
            sbfsSequence.push_back(node); //push it in sbfs (stores the bfs sequence)

            for( auto neighbor : adj[node]) //find neighbors of 0
            {
                if(!visited[neighbor])  
                {
                    q.push(neighbor); //1,2 push in q
                    visited[neighbor]= true;
                }
            }
        }
    }
//uses multithreading-openmp to process nodes in parallel
    void parallelBFS(int start, vector<int> & pbfsSequence)
    {
        vector<bool> visited(V,false);
        queue<int>q;
        q.push(start);
        visited[start]=true;

        while(!q.empty())
        {
            int size=q.size();
            vector<int> currentlevel;
            for(int i=0; i<size; i++)
            {
                int node=q.front();
                q.pop();
                currentlevel.push_back(node);
                pbfsSequence.push_back(node);
            }
            #pragma omp parallel for //tells compiler to run loop in multiple threads to reduce time
            for(int i=0; i<currentlevel.size();i++)
            {
                int node=currentlevel[i];
                for(auto neighbor:adj[node])
                {
                    if(!visited[neighbor])
                    {
                        #pragma omp critical //one thread at a time can modify shared data(q and visited) to avoid conflict
                        {
                            if(!visited[neighbor])
                            {
                                q.push(neighbor);
                                visited[neighbor]=true;
                            }
                        }
                    }
                }
            }
        }
    }

    void sequentialDFS(int start,vector<int> &sdfsSequence)
    {
        vector<bool> visited(V,false);
        stack <int> s;
        s.push(start);
        visited[start]=true;

        while(!s.empty())
        {
            int node= s.top();     
            s.pop();                 
            sdfsSequence.push_back(node); 

            for( auto neighbor : adj[node]) 
            {
                if(!visited[neighbor])  
                {
                    s.push(neighbor);
                    visited[neighbor]= true;
                }
            }
        }
    }

    void parallelDFS(int start, vector<int> & pdfsSequence)
    {
        vector<bool> visited(V,false); //visited array
        stack<int>s;
        s.push(start);       //push start node in stack
        visited[start]=true; // make it true in visited array

        while(!s.empty())
        {
           int node= s.top();
           s.pop();
           pdfsSequence.push_back(node);

           vector <int> neighbors= adj[node];
            #pragma omp parallel for
            for(int i=0; i<neighbors.size();i++)
            {
                int neighbor= neighbors[i];
                if(!visited[neighbor])
                {
            #pragma omp critical
                        {
                            if(!visited[neighbor])
                            {
                                s.push(neighbor);
                                visited[neighbor]=true;
                            }
                        }
                    
                }
                
            }
        }
    } 
};
    int main()
    {
        int V=100000; //graph of 100000 nodes connected to 100 nodes
        int K=100;
        Graph g(V);

        for(int i=0;i<V;i++){
            for(int j=1;j<=K;j++){
                int neighbor =(i+j)%V;
                g.addEdge(i,neighbor);
            }
        }

        vector <int> sbfsSequence, pbfsSequence, sdfsSequence, pdfsSequence;
        auto start = high_resolution_clock::now();
    g.sequentialBFS(0, sbfsSequence);
    auto end = high_resolution_clock::now();
    duration<double> sbfstime = end - start;
    cout << "Sequential BFS Time: " << sbfstime.count() << " seconds" << endl;
    // cout << "Sequential BFS Traversal: ";
    // for (auto node : sbfsSequence)
    //     cout << node << " ";
    // cout << endl;
    // cout << endl;

    start = high_resolution_clock::now();
    g.parallelBFS(0, pbfsSequence);
    end = high_resolution_clock::now();
    duration<double> pbfstime = end - start;
    cout << "Parallel BFS Time: " << pbfstime.count() << " seconds" << endl;
    // cout << "Parallel BFS Traversal: ";
    // for (auto node : pbfsSequence)
    //     cout << node << " ";
    // cout << endl;
    // cout << endl;

    start = high_resolution_clock::now();
    g.sequentialDFS(0, sdfsSequence);
    end = high_resolution_clock::now();
    duration<double> sdfstime = end - start;
    cout << "Sequential DFS Time: " << sdfstime.count() << " seconds" << endl;
    // cout << "Sequential DFS Traversal: ";
    // for (auto node : sdfsSequence)
    //     cout << node << " ";
    // cout << endl;
    // cout << endl;

    start = high_resolution_clock::now();
    g.parallelDFS(0, pdfsSequence);
    end = high_resolution_clock::now();
    duration<double> pdfstime = end - start;
    cout << "Parallel DFS Time: " << pdfstime.count() << " seconds" << endl;
    // cout << "Parallel DFS Traversal: ";
    // for (auto node : pdfsSequence)
    //     cout << node << " ";
    // cout << endl;
    // cout << endl;
        
    }
//chair example
/*
COMPILE USING
inside the folder g++ -pthread -o program  program.cpp
TO run 
run ./<program_name>
eg ./program
Preferably use a LINUX system to compile and run this program.
*/
//18103033
#include <bits/stdc++.h>
using namespace std;
int flag = 0;
float p = 0.5;  //=0;
//Semaphores and mutex Declaration
mutex north_mutex;
mutex south_mutex;
mutex east_mutex;
mutex west_mutex;
mutex junction_mutex;
mutex file_mutex;
int n, m;
vector<int> read_sequence_file();
void create_file();
vector<vector<int>> read_file();
void write_file(int x, int y, int v);
bool check_right(int checker);
bool check_for_cycle(vector<vector<int>> matrix, int degree_matrix);
bool bfs_iterative(vector<vector<int>> graph, int key, vector<int> degree);
void check_deadlock();
void north_train(int serial_no)
{
    cout << "Train " << serial_no << " North train Started\n";
    cout << "Train " << serial_no << " requests for North-Lock\n";
    write_file(serial_no, 0, 1);
    if(1)
    {
        lock_guard<mutex> lock(north_mutex);
        cout << "Train " << serial_no << " acquired North-Lock\n";
        cout << "Train " << serial_no << " requests for West-Lock\n";
        write_file(serial_no, 0, 2);
        write_file(serial_no, 1, 1);  
    }
    if (1)
    {
        lock_guard<mutex> lock(west_mutex);
        cout << "Train " << serial_no << " acquired West-Lock\n";
        write_file(serial_no, 1, 2);
        cout << "Train " << serial_no << " requests for Junction-Lock\n";
    }
    if (1)
    {
        lock_guard<mutex> lock(junction_mutex);
        cout << "Train " << serial_no << " acquired Junction-Lock"
             << " Passing Junction\n";
        //std::chrono::milliseconds timespan(2000);
        //std::this_thread::sleep_for(timespan);
    }
    cout << "Train " << serial_no << " releases Junction-Lock\n";
    if (1)
    {
        lock_guard<mutex> lock(west_mutex);
        write_file(serial_no, 1, 0);
        cout << "Train " << serial_no << " releases West-Lock\n";
    }
    if(1)
    {
        lock_guard<mutex> lock(north_mutex);
        write_file(serial_no, 0, 0);
        cout << "Train " << serial_no << " releases North-Lock\n";
    }
    return;
}
void west_train(int serial_no)
{
    cout << "Train " << serial_no << " West train Started\n";
    cout << "Train " << serial_no << " requests for West-Lock\n";
    if (1)
    {
        lock_guard<mutex> lock(west_mutex);
        cout << "Train " << serial_no << " acquired West-Lock\n";
        cout << "Train " << serial_no << " requests for South-Lock\n";
        write_file(serial_no, 1, 2);
        write_file(serial_no, 2, 1);  
    }
    if (1)
    {
        lock_guard<mutex> lock(south_mutex);
        cout << "Train " << serial_no << " acquired South-Lock\n";
        write_file(serial_no, 2, 2);
    }
    cout << "Train " << serial_no << " requests for Junction-Lock\n";
    if (1)
    {
        lock_guard<mutex> lock(junction_mutex);
        cout << "Train " << serial_no << " acquired Junction-Lock"
             << " Passing Junction\n";
        //std::chrono::milliseconds timespan(2000);
        //std::this_thread::sleep_for(timespan);
        cout << "Train " << serial_no << " releases Junction-Lock\n";
    }
    if (1)
    {
        lock_guard<mutex> lock(south_mutex);
        write_file(serial_no, 2, 0);
        cout << "Train " << serial_no << " releases for South-Lock\n";
    }
    if (1)
    {
        lock_guard<mutex> lock(west_mutex);
        write_file(serial_no, 1, 0);
        cout << "Train " << serial_no << " releases for West-Lock\n";
    }
    return;
}
void south_train(int serial_no)
{
    cout << "Train " << serial_no << " South train Started\n";
    cout << "Train " << serial_no << " requests for South-Lock\n";
    write_file(serial_no, 2, 1);
    if (1)
    {
        lock_guard<mutex> lock(south_mutex);
        cout << "Train " << serial_no << " acquired South-Lock\n";
        cout << "Train " << serial_no << " requests for East-Lock\n";
        write_file(serial_no, 2, 2);
        write_file(serial_no, 3, 1);
    }
    if (1)
    {
        lock_guard<mutex> lock(east_mutex);
        cout << "Train " << serial_no << " acquired East-Lock\n";
        write_file(serial_no, 3, 2);
        cout << "Train " << serial_no << " requests for Junction-Lock\n";
    }
    if (1)
    {
        lock_guard<mutex> lock(junction_mutex);
        cout << "Train " << serial_no << " acquired Junction-Lock"
             << " Passing Junction\n";
        //std::chrono::milliseconds timespan(2000);
        //std::this_thread::sleep_for(timespan);
        cout << "Train " << serial_no << " releases Junction-Lock\n";
    }
    if (1)
    {
        lock_guard<mutex> lock(east_mutex);
        write_file(serial_no, 3, 0);
        cout << "Train " << serial_no << " releases for East-Lock\n";
    }
    if (1)
    {
        lock_guard<mutex> lock(south_mutex);
        write_file(serial_no, 2, 0);
        cout << "Train " << serial_no << " releases for South-Lock\n";
    }
    return;
}
void east_train(int serial_no)
{
    cout << "Train " << serial_no << " East train Started\n";
    cout << "Train " << serial_no << " requests for East-Lock\n";
    write_file(serial_no, 3, 1);
    if (1)
    {
        lock_guard<mutex> lock(east_mutex);
        cout << "Train " << serial_no << " acquired East-Lock\n";
        cout << "Train " << serial_no << " requests for North-Lock\n";
        write_file(serial_no, 3, 2);
        write_file(serial_no, 0, 1);   
    }
    if (1)
    {
        lock_guard<mutex> lock(north_mutex);
        cout << "Train " << serial_no << " acquired North-Lock\n";
        write_file(serial_no, 0, 2);
        cout << "Train " << serial_no << " requests for Junction-Lock\n";
    }
    if (1)
    {
        lock_guard<mutex> lock(junction_mutex);
        cout << "Train " << serial_no << " acquired Junction-Lock"
             << " Passing Junction\n";
        //std::chrono::milliseconds timespan(2000);
        //std::this_thread::sleep_for(timespan);
        cout << "Train " << serial_no << " releases Junction-Lock\n";
    }
    if (1)
    {
        //lock_guard<mutex> lock(north_mutex);
        write_file(serial_no, 0, 0);
        cout << "Train " << serial_no << " releases for North-Lock\n";
    }
    if (1)
    {
        //lock_guard<mutex> lock(east_mutex);
        write_file(serial_no, 3, 0);
        cout << "Train " << serial_no << " releases for East-Lock\n";
    }
    return;
}
vector<vector<int>> make_graph(vector<vector<int>> matrix, vector<int> &degree, int degree_matrix);
void check_deadlock()
{
    while(1)
    {
        vector<vector<int>> ans;
        if (1)
        {
            lock_guard<mutex> lock(file_mutex);
            cout << "Deadlock Check\n";
            ifstream file_obj("matrix.txt");
            string str_line;
            while (getline(file_obj, str_line))
            {
                vector<int> tmp;
                for (int i = 0; i < str_line.size(); i++)
                {
                    tmp.push_back(str_line[i] - '0');
                }
                ans.push_back(tmp);
            }
            file_obj.close();
        }
        int degree_matrix = ans.size() + 4;
        //cout<<".....\n";
        if(ans.size()>4)
        {
            if (check_for_cycle(ans, degree_matrix))
            {
                for(int i=0;i<ans.size();i++)
                {
                    for (int j = 0; j < ans[i].size(); j++)
                    {
                        cout<<ans[i][j]<<" ";
                    }
                    cout<<"\n";
                }
                cout << "\n\nDeadlock Detected !!\n\n";
                exit(1);
            }
        }
        if(flag)
        {
            exit(1);
        }
    }
}
void manager()
{
    vector<int> train_sequence = read_sequence_file();
    create_file();
    std::vector<std::thread> threadList;
    int i = 0;
    float pr = p;
    pr = pr * 100;
    srand(time(0));
    std::thread dead(check_deadlock);
    while (train_sequence.size())
    {
        float q_select = rand() % 100;
        if (q_select < pr)
        {
            cout<<"Deadlock Check\n";
           /* if(train_sequence.size()<7)
            {
                exit(1);
            }*/
        }
        else
        {
            if (train_sequence[i] == 0)
            {
                threadList.push_back(std::thread(north_train, i));
                i++;
                train_sequence.erase(train_sequence.begin());
            }
            else if (train_sequence[i] == 1)
            {
                threadList.push_back(std::thread(west_train, i));
                i++;
                train_sequence.erase(train_sequence.begin());
            }
            else if (train_sequence[i] == 2)
            {
                threadList.push_back(std::thread(south_train, i));
                i++;
                train_sequence.erase(train_sequence.begin());
            }
            else
            {
                threadList.push_back(std::thread(east_train, i));
                i++;
                train_sequence.erase(train_sequence.begin());
            }
        }
    }
    std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
    if (train_sequence.size() == 0)
    {
        flag = 1;
    }
    dead.join();
}
int main(void)
{
    //cout<<"Enter the p: \n";
    //cin>>p;
    manager();
}
vector<int> read_sequence_file()
{
    lock_guard<mutex> lock(file_mutex);
    vector<int> ans;
    ifstream file_obj("sequence.txt");
    if(file_obj.fail())
    {
        cout<<"No file named sequence.txt present, please make a file containing the questions sequence\n";
        exit(1);
    }
    cout << "Reading Sequence File \n";
    string str_read;
    string tmp;
    while (getline(file_obj, tmp))
    {
        str_read += tmp;
        cout << ".. ";
    }
    cout << "\n";
    n = str_read.size();
    for (int i = 0; i < str_read.size(); i++)
    {
        if (str_read[i] == 'N')
        {
            ans.push_back(0);
        }
        else if (str_read[i] == 'W')
        {
            ans.push_back(1);
        }
        else if (str_read[i] == 'S')
        {
            ans.push_back(2);
        }
        else if (str_read[i] == 'E')
        {
            ans.push_back(3);
        }
        else
        {
            cout << "Error\n";
            exit(0);
        }
    }
    file_obj.close();
    return ans;
}
void create_file()
{
    cout << "Creating matrix.txt\n";
    ofstream file_obj("matrix.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            file_obj <<"0";
        }
        file_obj << "\n";
    }
    file_obj.close();
}
void write_file(int x, int y, int v)
{
    lock_guard<mutex> lock(file_mutex);
    vector<vector<int>> ans;
    ifstream file_obj("matrix.txt");
    string str_line;
    while (getline(file_obj, str_line))
    {
        vector<int> tmp;
        for (int i = 0; i < str_line.size(); i++)
        {
            tmp.push_back(str_line[i] - '0');
        }
        ans.push_back(tmp);
    }
    file_obj.close();
    ans[x][y] = v;
    ofstream file_obj1("matrix.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            file_obj1 << ans[i][j];
        }
        file_obj1 << "\n";
    }
    file_obj1.close();
}
bool check_right(int checker)
{
    lock_guard<mutex> lock(file_mutex);
    vector<vector<int>> ans;
    ifstream file_obj("matrix.txt");
    string str_line;
    while (getline(file_obj, str_line))
    {
        vector<int> tmp;
        for (int i = 0; i < str_line.size(); i++)
        {
            tmp.push_back(str_line[i] - '0');
        }
        ans.push_back(tmp);
    }
    file_obj.close();
    int j = (checker+1)%4;
    for(int i=0;i<ans.size();i++)
    {
        if(ans[i][j]==1)
        {
            return false;
        }
    }
    return true;
}
vector<vector<int>> read_file()
{
    lock_guard<mutex> lock(file_mutex);
    vector<vector<int>> ans;
    ifstream file_obj("matrix.txt");
    string str_line;
    while (getline(file_obj, str_line))
    {
        vector<int> tmp;
        for (int i = 0; i < str_line.size(); i++)
        {
            tmp.push_back(str_line[i] - '0');
        }
        ans.push_back(tmp);
    }
    file_obj.close();
    return ans;
}
bool bfs_iterative(vector<vector<int>> graph, int key, vector<int> degree)
{
    queue<int> queue;
    queue.push(key);
    int temp;
    while (!queue.empty())
    {
        temp = queue.front();
        degree[temp]--;
        queue.pop();
        int count = 0;
        for (int z = 0; z < graph[temp].size(); z++)
        {
            if (!(degree[graph[temp][z]] < 0))
            {
                queue.push(graph[temp][z]);
                count++;
            }
        }
        if (count != graph[temp].size())
        {
            return false;
        }
    }
    return true;
}
vector<vector<int>> make_graph(vector<vector<int>> matrix, vector<int> &degree, int degree_matrix)
{
    vector<vector<int>> graph(degree_matrix);
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            if (matrix[i][j] == 0)
            {
                continue;
            }
            else if (matrix[i][j] == 1)
            {
                graph[i + 4].push_back(j);
                degree[i + 4]++;
            }
            else if (matrix[i][j] == 2)
            {
                graph[j].push_back(i + 4);
                degree[j]++;
            }
            else
            {
                cout << "Error!\n";
            }
        }
    }
    return graph;
}
bool check_for_cycle(vector<vector<int>> matrix, int degree_matrix)
{
    vector<int> degree(degree_matrix);
    for (int i = 0; i < degree_matrix; i++)
    {
        degree[i] = 0; // not visited yet
    }
    vector<vector<int>> graph = make_graph(matrix, degree, degree_matrix);
    for (int i = 0; i < degree_matrix; i++)
    {
        if (!(bfs_iterative(graph, i, degree)))
        {
            return true;
        }
    }
    return false;
}
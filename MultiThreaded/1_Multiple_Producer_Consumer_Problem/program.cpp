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
int no_of_resources = 2;
int no_cnsmr = 5;
int no_prd = 5;
mutex mt_q1;
mutex mt_q2;
mutex file_mutex;
int semaphore_q1 = 0;
int semaphore_q2 = 0;
void create_matrix_file();
vector<vector<int>> make_graph(vector<vector<int>> matrix, vector<int> &degree);
bool bfs_iterative(vector<vector<int>> graph, int key, vector<int> degree);
bool check_for_cycle(vector<vector<int>> matrix);
vector<vector<int>> read_file();
void write_file(int i, int q, int s, vector<vector<int>> ans);
vector<vector<int>> read_file();
void producers(vector<int> *msg_que1, vector<int> *msg_que2, int *ptr_p)//, int *semaphore_q1, int *semaphore_q2)
{
    while (true)
    {
        srand(time(0));
        int q_select = rand() % 2;
        if (q_select == 0)
        {
            cout << "Producer " << *ptr_p << " Trying to Insert in queue" << 1 << "\n";
            cout << "Producer " << *ptr_p << " Acquiring Lock\n";
            vector<vector<int>> ans = read_file();
            if(1)
            {
                lock_guard<mutex> lock(mt_q1);
                write_file(*ptr_p, 0, 1, ans);
            }
            if (semaphore_q1 <= (no_prd + no_cnsmr - 1))
            {
                lock_guard<mutex> lock(mt_q1);
                cout << "Producer " << *ptr_p << " Acquired Lock\n";
                ans = read_file();
                write_file(*ptr_p, 0, 2, ans);
                int inrt_no = (rand() % 50) + 1;
                semaphore_q1 = semaphore_q1 + 1;
                //(*msg_que1).push_back(inrt_no);
            }
            ans = read_file();
            if (1)
            {
                lock_guard<mutex> lock(mt_q1);
                write_file(*ptr_p, 0, 0, ans);
            }
            cout << "Producer " << *ptr_p << " Released Lock\n";
            //cout << "Producer "<< " Failed to Insert\n";
        }
        else
        {
            cout << "Producer " << *ptr_p << " Trying to Insert in queue" << 2 << "\n";
            cout << "Producer " << *ptr_p << " Acquiring Lock\n";
            vector<vector<int>> ans = read_file();
            if (1)
            {
                lock_guard<mutex> lock(mt_q1);
                write_file(*ptr_p, 1, 1, ans);
            }
            if (semaphore_q2 <= (no_prd + no_cnsmr - 1))
            {
                lock_guard<mutex> lock(mt_q2);
                cout << "Producer " << *ptr_p << " Acquired Lock\n";
                ans = read_file();
                write_file(*ptr_p, 1, 2, ans);
                int inrt_no = (rand() % 50) + 1;
                //(*msg_que2).push_back(inrt_no);
                semaphore_q2 = semaphore_q2 + 1;
            }
            ans = read_file();
            if (1)
            {
                lock_guard<mutex> lock(mt_q1);
            }
            write_file(*ptr_p, 1, 0, ans);
            cout << "Producer " << *ptr_p << " Released Lock\n";
            //cout << "Producer "<< " Failed to Insert\n";
        }
        //cout << *semaphore_q1 << " " << *semaphore_q2 << "\n";
        //std::chrono::milliseconds timespan(1000);
        //std::this_thread::sleep_for(timespan);
    }
}
void consumers(vector<int> *msg_que1, vector<int> *msg_que2, int *ptr_p) //, int *semaphore_q1, int *semaphore_q2, int *p)
{
    while (true)
    {
        int o_q = 100 * (*ptr_p);
        int b_q = 100 - o_q;
        srand(time(0));
        int prob = (100 + rand()) % 100;
        cout << "Consumer "
             << " Trying to Consume\n";
        if (1)
        {
            srand(time(0));
            int q_select = rand() % 2;
            if (q_select == 0)
            {
                cout << "Consumer " << *ptr_p << " Trying to Remove in queue" << 1 << "\n";
                cout << "Consumer " << *ptr_p << " Acquiring Lock\n";
                vector<vector<int>> ans = read_file();
                if (1)
                {
                    lock_guard<mutex> lock(mt_q1);
                    write_file(*ptr_p, 0, 1, ans);
                }
                if (semaphore_q1 > 0)
                {
                    lock_guard<mutex> lock(mt_q1);
                    cout << "Consumer " << *ptr_p << " Acquired Lock\n";
                    ans = read_file();
                    write_file(*ptr_p, 0, 2, ans);
                    semaphore_q1 = semaphore_q1 - 1;
                    //(*msg_que1).pop_back();
                }
                ans = read_file();
                if (1)
                {
                    lock_guard<mutex> lock(mt_q1);
                    write_file(*ptr_p, 0, 0, ans);
                }
                cout << "Consumer " << *ptr_p << " Released Lock\n";
                //cout << "Producer "<< " Failed to Insert\n";
            }
            else
            {
                cout << "Consumer " << *ptr_p << " Trying to Remove in queue" << 2 << "\n";
                cout << "Consumer " << *ptr_p << " Acquiring Lock\n";
                vector<vector<int>> ans = read_file();
                if (1)
                {
                    lock_guard<mutex> lock(mt_q2);
                    write_file(*ptr_p, 1, 1, ans);
                }
                if (semaphore_q2 > 0)
                {
                    lock_guard<mutex> lock(mt_q2);
                    cout << "Consumer " << *ptr_p << " Acquired Lock\n";
                    ans = read_file();
                    write_file(*ptr_p, 1, 2, ans);
                    semaphore_q2 = semaphore_q2 - 1;
                    //(*msg_que2).pop_back();
                }
                ans = read_file();
                if (1)
                {
                    lock_guard<mutex> lock(mt_q2);
                    write_file(*ptr_p, 1, 0, ans);
                }
                cout << "Consumer " << *ptr_p << " Released Lock\n";
                //cout << "Producer "<< " Failed to Insert\n";
            }
            //cout << *semaphore_q1 << " " << *semaphore_q2 << "\n";
        }
        else
        {
            cout << "Consumer " << *ptr_p << " Trying to Remove in queue" << 1 << "\n";
            cout << "Consumer " << *ptr_p << " Acquiring Lock\n";
            vector<vector<int>> ans = read_file();
            if (1)
            {
                lock_guard<mutex> lock(mt_q1);
                write_file(*ptr_p, 0, 1, ans);
            }
            if (semaphore_q1 > 0)
            {
                lock_guard<mutex> lock(mt_q1);
                cout << "Consumer " << *ptr_p << " Acquired Lock\n";
                ans = read_file();
                write_file(*ptr_p, 0, 2, ans);
                semaphore_q1 = semaphore_q1 - 1;
                //(*msg_que1).pop_back();
            }
            ans = read_file();
            if (1)
            {
                lock_guard<mutex> lock(mt_q1);
                write_file(*ptr_p, 0, 0, ans);
            }
            cout << "Consumer " << *ptr_p << " Released Lock\n";
            cout << "Consumer " << *ptr_p << " Trying to Remove in queue" << 2 << "\n";
            cout << "Consumer " << *ptr_p << " Acquiring Lock\n";
            if (1)
            {
                lock_guard<mutex> lock(mt_q2);
                write_file(*ptr_p, 1, 1, ans);
            }
            if (semaphore_q2 > 0)
            {
                lock_guard<mutex> lock(mt_q2);
                cout << "Consumer " << *ptr_p << " Acquired Lock\n";
                ans = read_file();
                write_file(*ptr_p, 1, 2, ans);
                semaphore_q2 = semaphore_q2 - 1;
                //(*msg_que2).pop_back();
            }
            ans = read_file();
            if (1)
            {
                lock_guard<mutex> lock(mt_q2);
                write_file(*ptr_p, 1, 0, ans);
            }
            cout << "Consumer " << *ptr_p << " Released Lock\n";
        }
        //std::chrono::milliseconds timespan(1000);
        //std::this_thread::sleep_for(timespan);
    }
}
void deadlock_check()
{
    int flag = 1;
    while (flag)
    {
        std::chrono::milliseconds timespan(2000);
        std::this_thread::sleep_for(timespan);
        vector<vector<int>> tmp_r = read_file();
        if (check_for_cycle(tmp_r))
        {
            flag = 0;
            cout << "\nDEADLOCK DETECTED\n";
            cout << "\nDEADLOCK DETECTED\n";
            cout << "\nDEADLOCK DETECTED\n";
            cout<<"The Last Matrix Displayed has a Deadlock\n";
            exit(1);
            return;
        }
    }
}
void manager()
{
    create_matrix_file();
    //creating message queues
    vector<int> msg_que1;
    vector<int> msg_que2;
    vector<int> *ptr_msg1 = &msg_que1;
    vector<int> *ptr_msg2 = &msg_que2;
    //int sem_q1 = 10;
    //int sem_q2 = 10;
    //int *semaphore_q1 = &sem_q1;
    //int *semaphore_q2 = &sem_q2;
    int p1 = 1;
    int *ptr_p1 = &p1;
    int p2 = 2;
    int *ptr_p2 = &p2;
    int p3 = 3;
    int *ptr_p3 = &p3;
    int p4 = 4;
    int *ptr_p4 = &p4;
    int p5 = 5;
    int *ptr_p5 = &p5;
    int c1 = 6;
    int *ptr_c1 = &c1;
    int c2 = 7;
    int *ptr_c2 = &c2;
    int c3 = 8;
    int *ptr_c3 = &c3;
    int c4 = 9;
    int *ptr_c4 = &c4;
    int c5 = 10;
    int *ptr_c5 = &c5;
    int probability = 0.2;
    int *p = &probability;
    std::thread t_p1(producers, ptr_msg1, ptr_msg2, ptr_p1); //semaphore_q1, semaphore_q2);
    std::thread t_p2(producers, ptr_msg1, ptr_msg2, ptr_p2 ); // semaphore_q1, semaphore_q2);
    std::thread t_p3(producers, ptr_msg1, ptr_msg2, ptr_p3 ); // semaphore_q1, semaphore_q2);
    std::thread t_p4(producers, ptr_msg1, ptr_msg2, ptr_p4 ); // semaphore_q1, semaphore_q2);
    std::thread t_p5(producers, ptr_msg1, ptr_msg2, ptr_p5 ); // semaphore_q1, semaphore_q2);
    std::thread t_c1(consumers, ptr_msg1, ptr_msg2, ptr_c1 ); // semaphore_q1, semaphore_q2, p);
    std::thread t_c2(consumers, ptr_msg1, ptr_msg2, ptr_c2 ); // semaphore_q1, semaphore_q2, p);
    std::thread t_c3(consumers, ptr_msg1, ptr_msg2, ptr_c3); // semaphore_q1, semaphore_q2, p);
    std::thread t_c4(consumers, ptr_msg1, ptr_msg2, ptr_c4 ); // semaphore_q1, semaphore_q2, p);
    std::thread t_c5(consumers, ptr_msg1, ptr_msg2, ptr_c5 ); // semaphore_q1, semaphore_q2, p);
    std::thread dead(deadlock_check);
    dead.join();
    t_p1.join();
    t_p2.join();
    t_p3.join();
    t_p4.join();
    t_p5.join();
    t_c1.join();
    t_c2.join();
    t_c3.join();
    t_c4.join();
    t_c5.join();

}
int main(void)
{
    manager();
}
vector<vector<int>> make_graph(vector<vector<int>> matrix, vector<int> &degree)
{
    vector<vector<int>> graph(no_cnsmr + no_prd + no_of_resources);
    for (int i = 0; i < matrix.size(); i++)
    {
        //resource 1 given index 0 and resource 2 index 1
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == 0)
            {
                continue;
            }
            else if (matrix[i][j] == 1)
            {
                graph[j + 2].push_back(i);
                degree[j + 2]++;
            }
            else if (matrix[i][j] == 2)
            {
                graph[i].push_back(j + 2);
                degree[i]++;
            }
            else
            {
                cout << "Error!\n";
            }
        }
    }
    return graph;
}
void create_matrix_file()
{
    cout << "Creating matrix.txt\n";
    ofstream file_obj("matrix.txt");
    for (int i = 0; i < no_of_resources; i++)
    {
        for (int j = 0; j < no_prd + no_cnsmr; j++)
        {
            file_obj << 0 << " ";
        }
        file_obj << "\n";
    }
    file_obj.close();
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
bool check_for_cycle(vector<vector<int>> matrix)
{
    vector<int> degree(no_of_resources + no_prd + no_cnsmr);
    for (int i = 0; i < no_of_resources + no_prd + no_cnsmr; i++)
    {
        degree[i] = 0; // not visited yet
    }
    vector<vector<int>> graph = make_graph(matrix, degree);
    for (int i = 0; i < no_of_resources + no_prd + no_cnsmr; i++)
    {
        if (!(bfs_iterative(graph, i, degree)))
        {
            return true;
        }
    }
    return false;
}
void write_file(int i, int q, int s, vector<vector<int>> ans)
{
    lock_guard<mutex> lock(file_mutex);
    ans[q][i - 1] = s;
    ofstream file_obj("matrix.txt");
    for (int i = 0; i < no_of_resources; i++)
    {
        for (int j = 0; j < no_prd + no_cnsmr; j++)
        {
            file_obj << ans[i][j] << " ";
        }
        file_obj << "\n";
    }
    file_obj.close();
}
vector<vector<int>> read_file()
{
    lock_guard<mutex> lock(file_mutex);
    vector<vector<int>> ans;
    ifstream file_obj("matrix.txt");
    cout << "Matrix State: \n";
    for (int i = 0; i < no_of_resources; i++)
    {
        vector<int> tmp;
        string line;
        getline(file_obj, line);
        {
            for (int j = 0; j < line.size(); j += 2)
            {
                tmp.push_back(line[j] - '0');
            }
        }
        ans.push_back(tmp);
    }
    file_obj.close();
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "________________________\n";
    return ans;
}
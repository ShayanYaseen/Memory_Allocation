//First In First Out Simulation Paging
#include<bits/stdc++.h>
using namespace std;
int global_state = 0;
void print_queue(vector<int> page_q,vector<int> page_seq)
{
    if(global_state)
    {
        //Printing the state of the queue
        cout << "Page State: \n";
        cout << "-----------------------\n";
        for (int j = 0; j < page_q.size(); j++)
        {
            if (j >= page_q.size())
            {
                cout << "NULL | ";
            }
            else
            {
                cout << page_q[j] << " | ";
            }
        }
        cout << "\n-----------------------\n";
    }
}
int fifo(vector<int> page_seq, int p_size,int q_size)
{
    /*
    FIFO → in this algorithm, a queue is maintained. The page which is assigned the frame 
    first will be replaced first. In other words, the page which resides at the rare end of the queue w
    be replaced on the every page fault.
    */
    int page_faults = 0;
    vector<int> page_q;
    for (int i = 0; i < p_size; i++)
    {
        print_queue(page_q,page_seq);
        //Checking if the page is already present in the queue
        auto it = find(page_q.begin(), page_q.end(), page_seq[i]);
        if (it != page_q.end())
        {
            continue;
        }
        page_faults++;
        if(global_state)
        {
            cout << "Page Fault for " << page_seq[i] << "\n";
        }
        //Entering the page based on fifo strategy
        if (page_q.size() >= q_size)
        {
            page_q[0] = page_seq[i];
        }
        else
        {
            page_q.push_back(page_seq[i]);
        }
    }
    if (global_state)
    {
        cout << "Page Faults: " << page_faults << "\n";
        cout << "________________________________\n";
    }
    return page_faults;
}
int lru(vector<int> page_seq, int p_size, int q_size)
{
    /*
    Least recent used (LRU) page replacement 
    algorithm → this algorithm replaces the 
    page which has not been referred for a 
    long time. This algorithm is just opposite 
    the optimal page replacement algorithm. In this,
     we look at the past instead of staring at future.
    */
    int page_faults = 0;
    vector<int> page_q;
    for (int i = 0; i < p_size; i++)
    {
        print_queue(page_q, page_seq);
        //Checking if the page is already present in the queue
        auto it = find(page_q.begin(), page_q.end(), page_seq[i]);
        if (it != page_q.end())
        {
            page_q.erase(it);
            page_q.push_back(page_seq[i]);
            continue;
        }
        page_faults++;
        if(global_state)
        {
            cout << "Page Fault for " << page_seq[i] << "\n";
        }
        //Entering the page based on lru strategy
        if (page_q.size() >= q_size)
        {
            page_q[0] = page_seq[i];
        }
        else
        {
            page_q.push_back(page_seq[i]);
        }
    }
    if (global_state)
    {
        cout << "Page Faults: " << page_faults << "\n";
        cout << "________________________________\n";
    }
    return page_faults;
}
int opr(vector<int> page_seq, int p_size, int q_size)
{
    /*
    Optimal Page Replacement algorithm → this 
    algorithms replaces the page which will
    not be referred for so long in future. 
    Although it can not be practically implementable but it can be used 
    as a benchmark. Other algor
    are compared to this in terms of optimality.
    */
    int page_faults = 0;
    vector<int> page_q;
    for (int i = 0; i < p_size; i++)
    {
        print_queue(page_q, page_seq);
        //Checking if the page is already present in the queue
        auto it = find(page_q.begin(), page_q.end(), page_seq[i]);
        if (it != page_q.end())
        {
            continue;
        }
        page_faults++;
        if(global_state)
        {
            cout << "Page Fault for " << page_seq[i] << "\n";
        }
        //Entering the page based on orp strategy
        if (page_q.size() >= q_size)
        {
            unordered_set<int> hash_set;// set to check if we encountered the element in future
            vector<pair<int,int>> htmp; //vector of pair first storing the location and second the elment 
            for(int e=0;e<page_q.size();e++)
            {
                pair<int,int> tmp6;
                tmp6.first = INT_MAX;//BY Default the keys are ssumed never to come in future
                tmp6.second = page_q[e];
                htmp.push_back(tmp6);
            }
            for(int k=i+1;k<page_seq.size();k++)
            {
                //if key is found then put into the hash set and set the location
                for(int w=0;w<htmp.size();w++)
                {
                    if(hash_set.find(htmp[w].second) == hash_set.end())
                    {
                        if(htmp[w].second == page_seq[k])
                        {
                            htmp[w].first = k - (i);
                            hash_set.insert(htmp[w].second);
                            break;
                        }
                    }
                }                
            }
            //replacing witht the most optimal page with the call in future at last
            sort(htmp.begin(), htmp.end());
            for(int w=0;w<page_q.size();w++)
            {
                if(page_q[w]==htmp[htmp.size()-1].second)
                {
                    page_q[w] = page_seq[i];
                    break;
                }
            }
        }
        else
        {
            page_q.push_back(page_seq[i]);
        }
    }
    if(global_state)
    {
        cout << "Page Faults: " << page_faults << "\n";
        cout << "________________________________\n";
    }
    return page_faults;
}
int main(void)
{
    srand(time(NULL));
    //Answer pair
    vector<pair<float, pair<float, pair<float, float>>>> ans;
    cout << "DO you want to print the working of the algorithms?\n\n Press 1 for printing else 0\n";
    int response;
    cin >> response;
    switch (response)
    {
    case 1:
        global_state = 1;
        break;
    default:
        break;
    }
    int nor = 20;
    cout << "DO you want to CHANGE parameters or use random \n Press 1 for changing else 0\n";
    cin >> response;
    switch (response)
    {
    case 1:
        cout << "Number of Iterations \n";
        cin>>nor;
        break;
    default:
        break;
    }
    for(int itr=1;itr<nor;itr++)
    {
        //Setting the range of random generated variables
        //range of the queue size ( number of page in main memory)
        /*
        //range of the page sequeunce size ( number of pages request)
        int p_r_beg = 1;
        int p_r_end = 10;
        */
        //int q_r_beg = 1;
        //int q_r_end = 2;
        int q_size = 10;
        int p_size = 100;
        //range of the pages number
        int p_beg = 1;
        int p_end = 15;
        //Generating and setting the queue size, page sequence and other seed variables
        cout<<"Simulation Number: "<<itr<<"\n";
        //int q_size = rand() % ((q_r_end - q_r_beg) + 1) + q_r_beg;
        cout<<"Queue Size: "<<q_size<<"\n";
        vector<int> page_seq;
        //int p_size = rand() % ((p_r_end - p_r_beg) + 1) + p_r_beg;
        cout << "Number of pages: " << p_size << "\n";
        cout<<"Page Sequence: \n";
        //Populating the page sequence with random variable within a range
        for(int i=0;i<p_size;i++)
        {
            page_seq.push_back(rand() % ((p_end - p_beg) + 1) + p_beg);
            cout<<" "<<page_seq[i]<<" ";
        }
        cout<<"\n";
        cout<<"Algorithm Strategy : FIFO\n_________________________________\n";
        float fifo_faults = fifo(page_seq,p_size,q_size);
        cout << "Algorithm Strategy : LRU\n_________________________________\n";
        float lru_faults = lru(page_seq, p_size, q_size);
        cout << "Algorithm Strategy : OPR\n_________________________________\n";
        float opr_faults = opr(page_seq, p_size, q_size);
        pair<float, pair<float, pair<float, float>>> tmp;
        pair<float, pair<float, float>> tmp1;
        pair<float, float> tmp2;
        tmp2.first = (1-fifo_faults/p_size);
        tmp2.second = (1-lru_faults / p_size);
        tmp1.second = tmp2;
        tmp1.first = (1-opr_faults / p_size);
        tmp.first = q_size;
        tmp.second = tmp1;
        ans.push_back(tmp);
    }
    //Printing all the results
    sort(ans.begin(),ans.end());
    cout << "____________________________________________________________________\n";
    cout<<"Page_Queue_Size "<<"| "<<"Hit Ratio OPR "<<"| "<<"Hit Ratio FIFO "<<"| "<<"Hit Ratio LRU \n";
    cout << "____________________________________________________________________\n";
    float avg_opr=0;
    float avg_fifo = 0;
    float avg_lru = 0;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << "||      " << ans[i].first << "       |       " << ans[i].second.first << "        |       " << ans[i].second.second.first << "        |       " << ans[i].second.second.second << "      || \n";
        avg_opr += ans[i].second.first;
        avg_fifo += ans[i].second.second.first;
        avg_lru += ans[i].second.second.second;
    }
    cout << "\n____________________________________________________________________\n";
    cout << "||   " << "AVERAGE" << "    |    " << avg_opr / ans.size() << "      |     " << avg_fifo / ans.size() << "      |     " << avg_lru / ans.size() << "    || \n";
    cout << "\n____________________________________________________________________\n";
    cout << "\n\n";
    vector<pair<int, string>> min_ext = {make_pair(avg_opr / ans.size(), "OPR Optimal Replacement"), make_pair(avg_fifo / ans.size(), "FIFO First in First Out"), make_pair(avg_lru / ans.size(), "LRU Least Recently Used")};
    sort(min_ext.begin(), min_ext.end());
    cout << "Best Algorithm is :" << min_ext[2].second << "\n";
    cout << "\n\n";
    return 0;
}
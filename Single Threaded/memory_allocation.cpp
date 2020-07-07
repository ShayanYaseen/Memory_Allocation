#include <bits/stdc++.h>
using namespace std;
int global_flag = 0;
void print_memory(vector<pair<int, int>> mem_snp, vector<pair<int, int>> p_s)
{
    // print memory for debugging or checking how the algorithms work
    if (global_flag)
    {
        cout << "Memory Snapshot\n";
        cout << "___________________________\n";
        cout << "|| Partion size | filled ||\n";
        for (int i = 0; i < p_s.size(); i++)
        {
            cout << "|| " << mem_snp[i].first << "          |      " << mem_snp[i].second << " ||\n";
        }
        cout << "___________________________\n";
    }
}
pair<float, float> first_fit_fixed(vector<pair<int, int>> mem_snp, vector<pair<int, int>> p_s)
{
    float intrl_frag = 0;
    float extl_frag = 0;
    int avail_space = 0;
    //calculate the overall avail space that is not allocated right now
    for (int j = 0; j < mem_snp.size(); j++)
    {
        if (mem_snp[j].second == 0)
        {
            avail_space += mem_snp[j].first;
        }
    }
    vector<pair<int, int>> tmp1; //stores unallocated processes
    for (int i = 0; i < p_s.size(); i++)
    {
        int flag = 0;
        for (int j = 0; j < mem_snp.size(); j++)
        {
            if (mem_snp[j].second == 0 && mem_snp[j].first >= p_s[i].first)
            {
                if (global_flag)
                {
                    cout << "Allocating " << p_s[i].second << " " << p_s[i].first << " to memory of size " << mem_snp[j].first << "\n";
                }
                intrl_frag += mem_snp[j].first - p_s[i].first;
                mem_snp[j].second = 1;
                flag = 1;
                avail_space -= mem_snp[j].first;
                break;
            }
        }
        if (flag == 0)
        {
            // could not allocate will check for external frag later
            if (global_flag)
            {
                cout << "Could not allocate will check for external frag later" << p_s[i].second << " " << p_s[i].first << "\n";
            }
            tmp1.push_back(p_s[i]);
        }
        print_memory(mem_snp, p_s);
    }
    print_memory(mem_snp, p_s);
    sort(tmp1.begin(), tmp1.end());
    reverse(tmp1.begin(), tmp1.end());
    //sorted in descending order
    for (int i = 0; i < tmp1.size(); i++)
    {
        //find the largest process size that could not be allocated even after having avail space
        if (avail_space >= tmp1[i].first)
        {
            if (global_flag)
            {
                cout << "External Fragmentation of " << tmp1[i].first << "\n";
            }
            extl_frag += tmp1[i].first;
            break;
        }
    }
    return make_pair(intrl_frag, extl_frag);
}
pair<float, float> best_fit_fixed(vector<pair<int, int>> mem_snp, vector<pair<int, int>> p_s)
{
    float intrl_frag = 0;
    float extl_frag = 0;
    int avail_space = 0;
    //calculate the overall avail space that is not allocated right now
    for (int j = 0; j < mem_snp.size(); j++)
    {
        if (mem_snp[j].second == 0)
        {
            avail_space += mem_snp[j].first;
        }
    }
    vector<pair<int, int>> tmp1; //stores unallocated processes
    for (int i = 0; i < p_s.size(); i++)
    {
        int flag = 0;
        vector<pair<int, int>> mem_snp_tmp = mem_snp;
        sort(mem_snp_tmp.begin(), mem_snp_tmp.end());
        //finding the smallest partition that fits the incoming block
        pair<int, int> match;
        for (int j = 0; j < mem_snp_tmp.size(); j++)
        {
            if (mem_snp_tmp[j].second == 0 && mem_snp_tmp[j].first >= p_s[i].first)
            {
                flag = 1;
                match = mem_snp_tmp[j];
                break;
            }
        }
        if (flag)
        {
            for (int j = 0; j < mem_snp_tmp.size(); j++)
            {
                if (mem_snp[j] == match)
                {
                    if (global_flag)
                    {
                        cout << "Allocating " << p_s[i].second << " " << p_s[i].first << " to memory of size " << mem_snp[j].first << "\n";
                    }
                    intrl_frag += mem_snp[j].first - p_s[i].first;
                    mem_snp[j].second = 1;
                    avail_space -= mem_snp[j].first;
                    break;
                }
            }
        }
        if (flag == 0)
        {
            // could not allocate will check for external frag later
            if (global_flag)
            {
                cout << "Could not allocate will check for external frag later" << p_s[i].second << " " << p_s[i].first << "\n";
            }
            tmp1.push_back(p_s[i]);
        }
        print_memory(mem_snp, p_s);
    }
    print_memory(mem_snp, p_s);
    sort(tmp1.begin(), tmp1.end());
    reverse(tmp1.begin(), tmp1.end());
    //sorted in descending order
    for (int i = 0; i < tmp1.size(); i++)
    {
        //find the largest process size that could not be allocated even after having avail space
        if (avail_space >= tmp1[i].first)
        {
            if (global_flag)
            {
                cout << "External Fragmentation of " << tmp1[i].first << "\n";
            }
            extl_frag += tmp1[i].first;
            break;
        }
    }
    return make_pair(intrl_frag, extl_frag);
}
pair<float, float> worst_fit_fixed(vector<pair<int, int>> mem_snp, vector<pair<int, int>> p_s)
{
    float intrl_frag = 0;
    float extl_frag = 0;
    int avail_space = 0;
    //calculate the overall avail space that is not allocated right now
    for (int j = 0; j < mem_snp.size(); j++)
    {
        if (mem_snp[j].second == 0)
        {
            avail_space += mem_snp[j].first;
        }
    }
    vector<pair<int, int>> tmp1; //stores unallocated processes
    for (int i = 0; i < p_s.size(); i++)
    {
        int flag = 0;
        vector<pair<int, int>> mem_snp_tmp = mem_snp;
        sort(mem_snp_tmp.begin(), mem_snp_tmp.end());
        reverse(mem_snp_tmp.begin(), mem_snp_tmp.end());
        //finding the largest partition that fits the incoming block
        pair<int, int> match;
        for (int j = 0; j < mem_snp_tmp.size(); j++)
        {
            if (mem_snp_tmp[j].second == 0 && mem_snp_tmp[j].first >= p_s[i].first)
            {
                flag = 1;
                match = mem_snp_tmp[j];
                break;
            }
        }
        if (flag)
        {
            for (int j = 0; j < mem_snp_tmp.size(); j++)
            {
                if (mem_snp[j] == match)
                {
                    if (global_flag)
                    {
                        cout << "Allocating " << p_s[i].second << " " << p_s[i].first << " to memory of size " << mem_snp[j].first << "\n";
                    }
                    intrl_frag += mem_snp[j].first - p_s[i].first;
                    mem_snp[j].second = 1;
                    avail_space -= mem_snp[j].first;
                    break;
                }
            }
        }
        if (flag == 0)
        {
            // could not allocate will check for external frag later
            if (global_flag)
            {
                cout << "Could not allocate will check for external frag later" << p_s[i].second << " " << p_s[i].first << "\n";
            }
            tmp1.push_back(p_s[i]);
        }
        print_memory(mem_snp, p_s);
    }
    print_memory(mem_snp, p_s);
    sort(tmp1.begin(), tmp1.end());
    reverse(tmp1.begin(), tmp1.end());
    //sorted in descending order
    for (int i = 0; i < tmp1.size(); i++)
    {
        //find the largest process size that could not be allocated even after having avail space
        if (avail_space >= tmp1[i].first)
        {
            if (global_flag)
            {
                cout << "External Fragmentation of " << tmp1[i].first << "\n";
            }
            extl_frag += tmp1[i].first;
            break;
        }
    }
    return make_pair(intrl_frag, extl_frag);
}
void var_combine_cont_free(vector<pair<int, int>> &vect)
{
    //function to clean a memory partitons after
    // allocation in variable scheme
    int f = 1;
    while (f)
    {
        f = 0;
        for (int p = 0; p + 1 < vect.size(); p++)
        {
            if (vect[p].second == 0 && vect[p + 1].second == 0)
            {
                //if two contiguos partitions
                //are empty join them together
                int temp = vect[p].first + vect[p + 1].first;
                vect.erase(vect.begin() + p + 1);
                vect[p].first = temp;
                f = 1;
            }
        }
    }
}
void var_allocation(vector<pair<int, int>> &vect, int p, int m)
{
    // p is the place to allocate ( parition number)
    // m is the memory size of the incoming block
    int lft = vect[p].first - m;
    if (lft != 0)
    {
        vect[p].first = m;
        // if a space is left then make it a new parttiion
        // with space as the difference from m
        pair<int, int> tmp;
        tmp.first = lft;
        tmp.second = 0;
        vect.insert(vect.begin() + p + 1, tmp);
    }
    vect[p].second = 1; // the partiions is now filled
    return;
}
float first_fit_variable(vector<pair<int, int>> mem_snp, vector<pair<int, int>> p_s)
{
    float extl_frag = 0;
    int avail_space = 0;
    //calculate the overall avail space that is not allocated right now
    var_combine_cont_free(mem_snp);
    for (int j = 0; j < mem_snp.size(); j++)
    {
        if (mem_snp[j].second == 0)
        {
            avail_space += mem_snp[j].first;
        }
    }
    vector<pair<int, int>> tmp1; //stores unallocated processes
    for (int i = 0; i < p_s.size(); i++)
    {
        int flag = 0;
        for (int j = 0; j < mem_snp.size(); j++)
        {
            //finding the first partition that fits the process
            if (mem_snp[j].second == 0 && mem_snp[j].first >= p_s[i].first)
            {
                if (global_flag)
                {
                    cout << "Allocating " << p_s[i].second << " " << p_s[i].first << " to memory of size " << mem_snp[j].first << "\n";
                }
                mem_snp[j].second = 1;
                flag = 1;
                avail_space -= p_s[i].first;
                var_allocation(mem_snp, j, p_s[i].first); //function made to allocate variable allocation reference the defination
                var_combine_cont_free(mem_snp);
                break;
            }
        }
        if (flag == 0)
        {
            // could not allocate will check for external frag later
            if (global_flag)
            {
                cout << "Could not allocate will check for external frag later" << p_s[i].second << " " << p_s[i].first << "\n";
            }
            tmp1.push_back(p_s[i]);
        }
        print_memory(mem_snp, p_s);
    }
    print_memory(mem_snp, p_s);
    sort(tmp1.begin(), tmp1.end());
    reverse(tmp1.begin(), tmp1.end());
    //sorted in descending order
    for (int i = 0; i < tmp1.size(); i++)
    {
        //find the largest process size that could not be allocated even after having avail space
        if (avail_space >= tmp1[i].first)
        {
            if (global_flag)
            {
                cout << "External Fragmentation of " << tmp1[i].first << "\n";
            }
            extl_frag += tmp1[i].first;
            break;
        }
    }
    return extl_frag;
}
float best_fit_variable(vector<pair<int, int>> mem_snp, vector<pair<int, int>> p_s)
{
    float extl_frag = 0;
    int avail_space = 0;
    //calculate the overall avail space that is not allocated right now
    var_combine_cont_free(mem_snp);
    for (int j = 0; j < mem_snp.size(); j++)
    {
        if (mem_snp[j].second == 0)
        {
            avail_space += mem_snp[j].first;
        }
    }
    vector<pair<int, int>> tmp1; //stores unallocated processes
    for (int i = 0; i < p_s.size(); i++)
    {
        int flag = 0;
        vector<pair<int, int>> mem_snp_tmp = mem_snp;
        sort(mem_snp_tmp.begin(), mem_snp_tmp.end());
        //finding the smallest partition that fits the incoming block
        pair<int, int> match;
        for (int j = 0; j < mem_snp_tmp.size(); j++)
        {
            if (mem_snp_tmp[j].second == 0 && mem_snp_tmp[j].first >= p_s[i].first)
            {
                flag = 1;
                match = mem_snp_tmp[j];
                break;
            }
        }
        if (flag)
        {
            for (int j = 0; j < mem_snp_tmp.size(); j++)
            {
                if (mem_snp[j] == match)
                {
                    if (global_flag)
                    {
                        cout << "Allocating " << p_s[i].second << " " << p_s[i].first << " to memory of size " << mem_snp[j].first << "\n";
                    }
                    mem_snp[j].second = 1;
                    avail_space -= p_s[i].first;
                    var_allocation(mem_snp, j, p_s[i].first); //function made to allocate variable allocation reference the defination
                    var_combine_cont_free(mem_snp);
                    break;
                }
            }
        }
        if (flag == 0)
        {
            // could not allocate will check for external frag later
            if (global_flag)
            {
                cout << "Could not allocate will check for external frag later" << p_s[i].second << " " << p_s[i].first << "\n";
            }
            tmp1.push_back(p_s[i]);
        }
        print_memory(mem_snp, p_s);
    }
    print_memory(mem_snp, p_s);
    sort(tmp1.begin(), tmp1.end());
    reverse(tmp1.begin(), tmp1.end());
    //sorted in descending order
    for (int i = 0; i < tmp1.size(); i++)
    {
        //find the largest process size that could not be allocated even after having avail space
        if (avail_space >= tmp1[i].first)
        {
            if (global_flag)
            {
                cout << "External Fragmentation of " << tmp1[i].first << "\n";
            }
            extl_frag += tmp1[i].first;
            break;
        }
    }
    return extl_frag;
}
float worst_fit_variable(vector<pair<int, int>> mem_snp, vector<pair<int, int>> p_s)
{
    float extl_frag = 0;
    int avail_space = 0;
    //calculate the overall avail space that is not allocated right now
    var_combine_cont_free(mem_snp);
    for (int j = 0; j < mem_snp.size(); j++)
    {
        if (mem_snp[j].second == 0)
        {
            avail_space += mem_snp[j].first;
        }
    }
    vector<pair<int, int>> tmp1; //stores unallocated processes
    for (int i = 0; i < p_s.size(); i++)
    {
        int flag = 0;
        vector<pair<int, int>> mem_snp_tmp = mem_snp;
        sort(mem_snp_tmp.begin(), mem_snp_tmp.end());
        reverse(mem_snp_tmp.begin(), mem_snp_tmp.end());
        //finding the smallest partition that fits the incoming block
        pair<int, int> match;
        for (int j = 0; j < mem_snp_tmp.size(); j++)
        {
            if (mem_snp_tmp[j].second == 0 && mem_snp_tmp[j].first >= p_s[i].first)
            {
                flag = 1;
                match = mem_snp_tmp[j];
                break;
            }
        }
        if (flag)
        {
            for (int j = 0; j < mem_snp_tmp.size(); j++)
            {
                if (mem_snp[j] == match)
                {
                    if (global_flag)
                    {
                        cout << "Allocating " << p_s[i].second << " " << p_s[i].first << " to memory of size " << mem_snp[j].first << "\n";
                    }
                    mem_snp[j].second = 1;
                    avail_space -= p_s[i].first;
                    var_allocation(mem_snp, j, p_s[i].first); //function made to allocate variable allocation reference the defination
                    var_combine_cont_free(mem_snp);
                    break;
                }
            }
        }
        if (flag == 0)
        {
            // could not allocate will check for external frag later
            if (global_flag)
            {
                cout << "Could not allocate will check for external frag later" << p_s[i].second << " " << p_s[i].first << "\n";
            }
            tmp1.push_back(p_s[i]);
        }
        print_memory(mem_snp, p_s);
    }
    print_memory(mem_snp, p_s);
    sort(tmp1.begin(), tmp1.end());
    reverse(tmp1.begin(), tmp1.end());
    //sorted in descending order
    for (int i = 0; i < tmp1.size(); i++)
    {
        //find the largest process size that could not be allocated even after having avail space
        if (avail_space >= tmp1[i].first)
        {
            if (global_flag)
            {
                cout << "External Fragmentation of " << tmp1[i].first << "\n";
            }
            extl_frag += tmp1[i].first;
            break;
        }
    }
    return extl_frag;
}
int main(void)
{
    //Setting the range of random generated variables
    //range of the queue size ( number of page in main memory)
    srand(time(NULL));
    cout << "DO you want to print the working of the algorithms?\n Press 1 for printing else 0\n";
    int response;
    cin >> response;
    switch (response)
    {
    case 1:
        global_flag = 1;
        break;
    default:
        break;
    }
    int np_s = 40;  // number of processes
    int p_beg = 20; // size of processes
    int p_end = 200;
    //Partuiton random settings
    int part = 10;
    int prt_beg = 20;
    int prt_end = 90;
    int nor = 20;
    cout << "DO you want to CHANGE parameters or use random \n Press 1 for changing else 0\n";
    cin >> response;
    switch (response)
    {
    case 1:
        cout << "Enter Number of procceses     Number of partitions   Number of Iterations \n";
        cin >> np_s >> part >> nor;
        break;
    default:
        break;
    }
    vector<vector<float>> ans;
    for (int itr = 1; itr < nor; itr++)
    {
        int memory_size = 0;        // decided by the generation of random partitions
        vector<pair<int, int>> p_s; // process snapshot with process size and number
        for (int i = 0; i < np_s; i++)
        {
            pair<int, int> tmp;
            tmp.first = rand() % ((p_end - p_beg) + 1) + p_beg;
            tmp.second = i + 1;
            p_s.push_back(tmp);
        }
        cout << "Process Table:\n";
        cout << "_____________________\n";
        cout << "|| P Size | Number ||\n";
        for (int i = 0; i < p_s.size(); i++)
        {
            cout << "|| " << p_s[i].first << "       |    " << p_s[i].second << " ||\n";
        }
        cout << "_____________________\n";
        cout << "\n Memory snapshot Initial\n";
        vector<pair<int, int>> mem_snp; // snapshot of memorty with first partition size and then if filled or not indicated by 1 or 0
        //generating random partitions
        for (int i = 0; i < np_s; i++)
        {
            pair<int, int> tmp;
            tmp.first = rand() % ((prt_end - prt_beg) + 1) + prt_beg;
            memory_size += tmp.first;
            tmp.second = rand() % 2;
            mem_snp.push_back(tmp);
        }
        cout << "___________________________\n";
        cout << "|| Partion size | filled ||\n";
        for (int i = 0; i < p_s.size(); i++)
        {
            cout << "|| " << mem_snp[i].first << "          |      " << mem_snp[i].second << " ||\n";
        }
        cout << "___________________________\n";
        cout << "Total Memory size:: "
             << "\n"
             << memory_size << "\n";
        cout << "\n\n\n";
        //variable to store internal fragmentation
        pair<float, float> fff_if;
        pair<float, float> bff_if;
        pair<float, float> wff_if;
        //variable to store external fragmentation
        float ffv_ef;
        float bfv_ef;
        float wfv_ef;
        cout << "Fixed Allocation\n";
        cout << "First Fit Fixed\n";
        fff_if = first_fit_fixed(mem_snp, p_s);
        cout << "Best Fit Fixed\n";
        bff_if = best_fit_fixed(mem_snp, p_s);
        cout << "Worst Fit Fixed\n";
        wff_if = worst_fit_fixed(mem_snp, p_s);
        cout << "\n\n\n";
        cout << "Variable Allocation\n";
        cout << "First Fit Variable\n";
        ffv_ef = first_fit_variable(mem_snp, p_s);
        cout << "Best Fit Variable\n";
        bfv_ef = best_fit_variable(mem_snp, p_s);
        cout << "Worst Fit Variable\n";
        wfv_ef = worst_fit_variable(mem_snp, p_s);
        vector<float> tempp;
        tempp = {fff_if.first, fff_if.second, bff_if.first, bff_if.second, wff_if.first, wff_if.second, ffv_ef, bfv_ef, wfv_ef};
        ans.push_back(tempp);
    }
    cout << "\n\nResults\n\n";
    vector<float> average = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // storing the average values of final;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << "Iteration Number:: " << i << "\n";
        cout << "Fixed Partition -- Internal Fragmentation-- External Fragmentation\n";
        cout << "||Allocation Scheme|Internal Fragmenation|External Fragmenation||\n";
        cout << "_________________________________\n";
        cout << "|| "
             << " First Fit       "
             << "  |     " << ans[i][0] << "  |     " << ans[i][1] << "    ||\n";
        cout << "|| "
             << " Best  Fit       "
             << "  |     " << ans[i][2] << "  |     " << ans[i][3] << "   ||\n";
        cout << "|| "
             << " Worst Fit       "
             << "  |     " << ans[i][4] << "  |     " << ans[i][5] << "   ||\n";
        cout << "\n\n";
        cout << "Variable Partition -- External Fragmentation\n";
        cout << "||Allocation Scheme|External Fragmenation||\n";
        cout << "_________________________________\n";
        cout << "|| "
             << " First Fit        "
             << "  |     " << ans[i][6] << " ||\n";
        cout << "|| "
             << " Best  Fit        "
             << "  |     " << ans[i][7] << " ||\n";
        cout << "|| "
             << " Worst Fit        "
             << "  |     " << ans[i][8] << " ||\n";
        cout << "_________________________________\n";
        for (int r = 0; r < 9; r++)
        {
            average[r] += ans[i][r];
        }
    }
    for (int r = 0; r < 9; r++)
    {
        average[r] += average[r] / ans.size();
    }
    cout << "\n\n\n\nAVERAGE VALUES\n\n\n\n";
    cout << "Fixed Partition -- Internal Fragmentation-- External Fragmentation\n";
    cout << "||Allocation Scheme|Internal Fragmenation|External Fragmenation||\n";
    cout << "_________________________________\n";
    cout << "|| "
         << " First Fit       "
         << "  |     " << average[0] << "   |     " << average[1] << "    ||\n";
    cout << "|| "
         << " Best  Fit       "
         << "  |     " << average[2] << "  |     " << average[3] << "   ||\n";
    cout << "|| "
         << " Worst Fit       "
         << "  |     " << average[4] << "  |     " << average[5] << "   ||\n";
    cout << "_________________________________\n";
    cout << "\n\n";
    vector<pair<int, string>> min_internal = {make_pair(average[0], "First Fit"), make_pair(average[2], "Best Fit"), make_pair(average[0], "Worst Fit")};
    vector<pair<int, string>> min_external = {make_pair(average[1], "First Fit"), make_pair(average[3], "Best Fit"), make_pair(average[5], "Worst Fit")};
    sort(min_internal.begin(), min_internal.end());
    sort(min_internal.begin(), min_internal.end());
    cout << "Best Algorithm for Fixed Internal Fragmentation is :" << min_internal[0].second << "\n";
    cout << "Best Algorithm for Fixed External Fragmentation is :" << min_external[0].second << "\n";
    cout << "\n\n";
    cout << "Variable Partition -- External Fragmentation\n";
    cout << "||Allocation Scheme|External Fragmenation||\n";
    cout << "_________________________________\n";
    cout << "|| "
         << " First Fit        "
         << "  |     " << average[6] << " ||\n";
    cout << "|| "
         << " Best  Fit        "
         << "  |     " << average[7] << " ||\n";
    cout << "|| "
         << " Worst Fit        "
         << "  |     " << average[8] << " ||\n";
    cout << "_________________________________\n";
    cout << "\n\n";
    vector<pair<int, string>> min_ext = {make_pair(average[6], "First Fit"), make_pair(average[7], "Best Fit"), make_pair(average[8], "Worst Fit")};
    sort(min_ext.begin(), min_ext.end());
    cout << "Best Algorithm for Variable External Fragmentation is :" << min_ext[0].second << "\n";
    cout << "\n\n";
}
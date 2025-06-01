#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

string input_file;
string output_file = "cfg.txt";
ofstream outfile;

int intermediate_count = 1;

bool find_string(string str, string str1)
{
    size_t found = str.find(str1);
    if (found != string::npos)
        return true;
    else
        return false;
}

bool find_char(string str, char ch)
{
    size_t found = str.find(ch);
    if (found != string::npos)
        return true;
    else
        return false;
}

string if_block(vector<string> v, string curr);
string else_block(vector<string> v, string curr);
string else_if_block(vector<string> v, string curr);
void for_block(vector<string> v, string curr);
void while_block(vector<string> v, string curr);
string case_block(vector<string> v, string curr);
string always_block(vector<string> v, string curr);

vector<string> parse_for(string str)
{
    vector<string> v;
    v.push_back("for");
    string cond = "";
    int cnt = 0;
    for (auto i : str)
    {
        if (i == '(')
        {
            cnt++;
            continue;
        }
        else if (i == ')')
        {
            cnt--;
            continue;
        }
        if (cnt > 0)
        {
            if (i == ';')
            {
                v.push_back(cond);
                cond = "";
            }
            else
                cond += i;
        }
    }
    v.push_back(cond);
    return v;
}

vector<string> parse_while(string str)
{
    vector<string> v;
    v.push_back("while");
    string cond = "";
    int cnt = 0;
    for (auto i : str)
    {
        if (i == '(')
        {
            cnt++;
            continue;
        }
        else if (i == ')')
        {
            cnt--;
            if (cnt == 0)
                break;
            continue;
        }
        if (cnt > 0)
        {
            cond += i;
        }
    }
    v.push_back(cond);
    return v;
}

string if_block(vector<string> v, string curr)
{
    int i = 0;
    string start = "";
    string end = "";
    while (i < v.size())
    {
        string str = v[i];
        if (find_string(str, "else if"))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "else") && !(find_string(str, "end")))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "if") && !find_string(str, "fifo"))
        {
            if (end != "")
            {
                start = end;
            }
            else
                start = curr;
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr, curr);
            string intermediate_node = "intermediate node " + to_string(intermediate_count);
            intermediate_count++;
            cout << temp << "  -->  " << intermediate_node << endl;
            outfile << temp << "  -->  " << intermediate_node << endl;
            end = intermediate_node;
        }
        else if (find_string(str, "for"))
        {
            vector<string> for_arr = parse_for(str);
            cout << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            outfile << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + for_arr[2] + " )";
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "while"))
        {
            vector<string> while_arr = parse_while(str);
            cout << curr << "  -->  " << while_arr[0] << endl;
            outfile << curr << "  -->  " << while_arr[0] << endl;
            cout << while_arr[0] << "  -->  " << while_arr[1] << endl;
            outfile << while_arr[0] << "  -->  " << while_arr[1] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + while_arr[1] + " )";
            cout << while_arr[0] << "  -->  " << temp << endl;
            outfile << while_arr[0] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "case") && !(find_string(str, "endcase")))
        {
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
            str = v[i];
            vector<string> arr;
            while (find_string(str, "endcase") == false)
            {
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr, curr);
        }
        else
        {
            if (end != "")
            {
                curr = end;
                start = "";
                end = "";
            }
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
        }
    }
    if (end == "")
        return curr;
    return end;
}

string else_if_block(vector<string> v, string curr)
{
    int i = 0;
    string start = "";
    string end = "";
    while (i < v.size())
    {
        string str = v[i];
        if (find_string(str, "else if"))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "else") && !(find_string(str, "end")))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "if") && !find_string(str, "fifo"))
        {
            if (end != "")
            {
                start = end;
            }
            else
                start = curr;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr, curr);
            string intermediate_node = "intermediate node " + to_string(intermediate_count);
            intermediate_count++;
            cout << temp << "  -->  " << intermediate_node << endl;
            outfile << temp << "  -->  " << intermediate_node << endl;
            end = intermediate_node;
        }
        else if (find_string(str, "for"))
        {
            vector<string> for_arr = parse_for(str);
            cout << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            outfile << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + for_arr[2] + " )";
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "while"))
        {
            vector<string> while_arr = parse_while(str);
            cout << curr << "  -->  " << while_arr[0] << endl;
            outfile << curr << "  -->  " << while_arr[0] << endl;
            cout << while_arr[0] << "  -->  " << while_arr[1] << endl;
            outfile << while_arr[0] << "  -->  " << while_arr[1] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + while_arr[1] + " )";
            cout << while_arr[0] << "  -->  " << temp << endl;
            outfile << while_arr[0] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "case") && !(find_string(str, "endcase")))
        {
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
            str = v[i];
            vector<string> arr;
            while (find_string(str, "endcase") == false)
            {
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr, curr);
        }
        else
        {
            if (end != "")
            {
                curr = end;
                start = "";
                end = "";
            }
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
        }
    }
    if (end == "")
        return curr;
    return end;
}

string else_block(vector<string> v, string curr)
{
    int i = 0;
    string start = "";
    string end = "";
    while (i < v.size())
    {
        string str = v[i];
        if (find_string(str, "else if"))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "else") && !(find_string(str, "end")))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "if") && !find_string(str, "fifo"))
        {
            if (end != "")
            {
                start = end;
            }
            else
                start = curr;
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr, curr);
            string intermediate_node = "intermediate node " + to_string(intermediate_count);
            intermediate_count++;
            cout << temp << "  -->  " << intermediate_node << endl;
            outfile << temp << "  -->  " << intermediate_node << endl;
            end = intermediate_node;
        }
        else if (find_string(str, "for"))
        {
            vector<string> for_arr = parse_for(str);
            cout << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            outfile << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + for_arr[2] + " )";
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "while"))
        {
            vector<string> while_arr = parse_while(str);
            cout << curr << "  -->  " << while_arr[0] << endl;
            outfile << curr << "  -->  " << while_arr[0] << endl;
            cout << while_arr[0] << "  -->  " << while_arr[1] << endl;
            outfile << while_arr[0] << "  -->  " << while_arr[1] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + while_arr[1] + " )";
            cout << while_arr[0] << "  -->  " << temp << endl;
            outfile << while_arr[0] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "case") && !(find_string(str, "endcase")))
        {
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
            str = v[i];
            vector<string> arr;
            while (find_string(str, "endcase") == false)
            {
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr, curr);
        }
        else
        {
            if (end != "")
            {
                curr = end;
                start = "";
                end = "";
            }
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
        }
    }
    if (end == "")
        return curr;
    return end;
}

void for_block(vector<string> v, string curr)
{
    vector<string> for_arr = parse_for(curr);
    int i = 0;
    string start = "";
    string end = "";
    curr = for_arr[2];
    while (i < v.size())
    {
        string str = v[i];
        if (find_string(str, "else if"))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "else") && !(find_string(str, "end")))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "if") && !find_string(str, "fifo"))
        {
            if (end != "")
            {
                start = end;
            }
            else
                start = curr;
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr, curr);
            string intermediate_node = "intermediate node " + to_string(intermediate_count);
            intermediate_count++;
            cout << temp << "  -->  " << intermediate_node << endl;
            outfile << temp << "  -->  " << intermediate_node << endl;
            end = intermediate_node;
        }
        else if (find_string(str, "for"))
        {
            vector<string> for_arr = parse_for(str);
            cout << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            outfile << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + for_arr[2] + " )";
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "while"))
        {
            vector<string> while_arr = parse_while(str);
            cout << curr << "  -->  " << while_arr[0] << endl;
            outfile << curr << "  -->  " << while_arr[0] << endl;
            cout << while_arr[0] << "  -->  " << while_arr[1] << endl;
            outfile << while_arr[0] << "  -->  " << while_arr[1] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + while_arr[1] + " )";
            cout << while_arr[0] << "  -->  " << temp << endl;
            outfile << while_arr[0] << "  -->  " << temp << endl;
            curr = temp;
        }

        else if (find_string(str, "case") && !(find_string(str, "endcase")))
        {
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
            str = v[i];
            vector<string> arr;
            while (find_string(str, "endcase") == false)
            {
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr, curr);
        }
        else
        {
            if (end != "")
            {
                curr = end;
                start = "";
                end = "";
            }
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
        }
    }
    cout << curr << "  -->  " << for_arr[3] << endl;
    outfile << curr << "  -->  " << for_arr[3] << endl;
    curr = for_arr[3];
    cout << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
    outfile << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
    return;
}

void while_block(vector<string> v, string curr)
{
    vector<string> while_arr = parse_while(curr);
    int i = 0;
    string start = "";
    string end = "";
    curr = while_arr[1];
    while (i < v.size())
    {
        string str = v[i];
        if (find_string(str, "else if"))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "else") && !(find_string(str, "end")))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "if") && !find_string(str, "fifo"))
        {
            if (end != "")
            {
                start = end;
            }
            else
                start = curr;
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr, curr);
            string intermediate_node = "intermediate node " + to_string(intermediate_count);
            intermediate_count++;
            cout << temp << "  -->  " << intermediate_node << endl;
            outfile << temp << "  -->  " << intermediate_node << endl;
            end = intermediate_node;
        }
        else if (find_string(str, "for"))
        {
            vector<string> for_arr = parse_for(str);
            cout << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            outfile << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + for_arr[2] + " )";
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "while"))
        {
            vector<string> while_arr = parse_while(str);
            cout << curr << "  -->  " << while_arr[0] << endl;
            outfile << curr << "  -->  " << while_arr[0] << endl;
            cout << while_arr[0] << "  -->  " << while_arr[1] << endl;
            outfile << while_arr[0] << "  -->  " << while_arr[1] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + while_arr[1] + " )";
            cout << while_arr[0] << "  -->  " << temp << endl;
            outfile << while_arr[0] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "case") && !(find_string(str, "endcase")))
        {
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
            str = v[i];
            vector<string> arr;
            while (find_string(str, "endcase") == false)
            {
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr, curr);
        }
        else
        {
            if (end != "")
            {
                curr = end;
                start = "";
                end = "";
            }
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
        }
    }
    cout << curr << "  -->  " << while_arr[0] << endl;
    outfile << curr << "  -->  " << while_arr[0] << endl;
    curr = while_arr[0];
    return;
}

string case_block(vector<string> v, string curr)
{
    int i = 0;
    string initial_case_node = curr;                                                 // The "case(...)" statement node
    string end_node_label = "endcase_merge_node_" + to_string(intermediate_count++); // Common merge point for all case branches

    while (i < v.size())
    {
        string line_content = v[i];
        if (find_char(line_content, ':')) // This is a case item line e.g., "STATE_A:" or "default:"
        {
            cout << initial_case_node << "  -->  " << line_content << endl;
            outfile << initial_case_node << "  -->  " << line_content << endl;
            string current_case_item_label_node = line_content;

            vector<string> item_body_lines;
            i++; // Move past the "case_item_label:" line

            // Check if there are more lines and if the next line is "begin"
            if (i < v.size() && v[i] == "begin")
            {
                i++; // Consume "begin"
                int begin_end_counter = 1;
                while (i < v.size() && begin_end_counter > 0)
                {
                    string current_block_line = v[i];
                    if (current_block_line == "begin")
                    {
                        begin_end_counter++;
                    }
                    else if (current_block_line == "end")
                    {
                        begin_end_counter--;
                    }

                    if (begin_end_counter > 0) // Don't add the final "end" to item_body_lines
                    {
                        item_body_lines.push_back(current_block_line);
                    }
                    i++; // Consume current line (statement or "end")
                }
                // i is now pointing to the line *after* the "end" of this item's block
            }
            else if (i < v.size()) // Single statement for this case item (or empty if next line is another case item/endcase)
            {
                // Check if the current line is not another case label or endcase.
                if (i < v.size() && !find_char(v[i], ':') && v[i] != "endcase" && v[i] != "default:")
                {
                    item_body_lines.push_back(v[i]);
                    i++; // Consume the single statement line
                }
            }
            // If i >= v.size() or next line is another case item, item_body_lines might be empty.

            string end_of_item_body_node = always_block(item_body_lines, current_case_item_label_node);
            cout << end_of_item_body_node << "  -->  " << end_node_label << endl;
            outfile << end_of_item_body_node << "  -->  " << end_node_label << endl;
            // i is already advanced past the processed block or single line by the logic above.
        }
        else
        {
            // If the line is not a case item (e.g. "default:" or "case_label:"),
            // and it's not an empty line or comment that should be skipped,
            // it might be an error in input or parsing logic for simple statements within case.
            // For now, just increment to avoid infinite loop on unexpected lines.
            i++;
        }
    }

    return end_node_label; // Return the common merge point for case statements
}

string always_block(vector<string> v, string curr)
{
    int i = 0;
    string start = ""; // Represents the node from which a new structure (if, for, etc.) branches
    string end = "";   // Represents the common merge point after an if-else-if chain

    // If the block is empty, return the current node
    if (v.empty())
    {
        return curr;
    }

    while (i < v.size())
    {
        string str = v[i];
        if (find_string(str, "else if"))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_if_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
        }
        else if (find_string(str, "else") && !(find_string(str, "end")))
        {
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = else_block(arr, curr);
            cout << temp << "  -->  " << end << endl;
            outfile << temp << "  -->  " << end << endl;
            curr = end;
            end = "";
        }
        else if (find_string(str, "if") && !find_string(str, "fifo"))
        {
            if (end != "")
            {
                start = end;
            }
            else
                start = curr;
            cout << start << "  -->  " << str << endl;
            outfile << start << "  -->  " << str << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            string temp = if_block(arr, curr);
            string intermediate_node = "intermediate node " + to_string(intermediate_count);
            intermediate_count++;
            cout << temp << "  -->  " << intermediate_node << endl;
            outfile << temp << "  -->  " << intermediate_node << endl;
            end = intermediate_node;
        }
        else if (find_string(str, "for"))
        {
            vector<string> for_arr = parse_for(str);
            cout << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            outfile << curr << "  -->  " << for_arr[0] << " , " << for_arr[1] << endl;
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << for_arr[2] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            for_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + for_arr[2] + " )";
            cout << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            outfile << for_arr[0] << " , " << for_arr[1] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "while"))
        {
            vector<string> while_arr = parse_while(str);
            cout << curr << "  -->  " << while_arr[0] << endl;
            outfile << curr << "  -->  " << while_arr[0] << endl;
            cout << while_arr[0] << "  -->  " << while_arr[1] << endl;
            outfile << while_arr[0] << "  -->  " << while_arr[1] << endl;
            curr = str;
            int count = 0;
            vector<string> arr;
            i++;
            str = v[i];
            if (str == "begin")
            {
                count++;
                i++;
                str = v[i];
            }
            while (count > 0)
            {
                if (str == "begin")
                {
                    count++;
                }
                else if (str == "end")
                {
                    count--;
                }
                if (count != 0)
                {
                    arr.push_back(str);
                    i++;
                    str = v[i];
                }
            }
            i++;
            while_block(arr, curr);
            string temp = "";
            temp = temp + "!( " + while_arr[1] + " )";
            cout << while_arr[0] << "  -->  " << temp << endl;
            outfile << while_arr[0] << "  -->  " << temp << endl;
            curr = temp;
        }
        else if (find_string(str, "case") && !(find_string(str, "endcase")))
        {
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
            str = v[i];
            vector<string> arr;
            while (find_string(str, "endcase") == false)
            {
                arr.push_back(str);
                i++;
                str = v[i];
            }
            i++;
            curr = case_block(arr, curr);
        }
        else
        {
            if (end != "")
            {
                curr = end;
                start = "";
                end = "";
            }
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str;
            i++;
        }
    }
    if (end == "")
        return curr;
    return end;
}

int main()
{
    auto start_time = high_resolution_clock::now();
    cout << "Give the input file name :- " << endl;
    // outfile << "Give the output file name :- " << endl; // Corrected: This was a typo, likely intended for cout
    // cin>>input_file;
    // cout<<"Give the output file name :- "<<endl;
    // cin>>outfile_file; // Assuming output_file is the intended variable
    // cout<<endl;

    input_file = "my_output.txt";
    // output_file = "cfg.txt"; // Default is already set at the top

    outfile.open(output_file);
    if (!outfile.is_open())
    {
        cerr << "Error: Could not open output file: " << output_file << endl;
        return 1; // Indicate an error
    }

    string str;
    ifstream file(input_file);
    if (!file.is_open())
    {
        cerr << "Error: Could not open input file: " << input_file << endl;
        outfile.close(); // Close output file if input fails
        return 1;        // Indicate an error
    }

    string curr = "START";

    while (getline(file, str))
    {
        if (find_string(str, "always"))
        {
            // graph[curr].push_back(str); // 'graph' map is not used for CFG generation, so this line is removed.
            cout << curr << "  -->  " << str << endl;
            outfile << curr << "  -->  " << str << endl;
            curr = str; // Current node is now the "always" statement itself
            int count = 0;
            vector<string> v; // Lines within the always block

            string next_line;
            // Check if the line immediately following "always" is "begin"
            // This assumes that if an always block has content, it starts with "begin"
            // or the content is on the same line as "always" (which this parser doesn't handle for "always")
            // For multi-line always blocks, we expect "begin" on the next line.
            if (getline(file, next_line))
            {
                str = next_line;
                if (str == "begin")
                {
                    count++;
                    // Read lines until the corresponding 'end' of the always block
                    while (getline(file, str))
                    {
                        if (str == "begin")
                        {
                            count++;
                        }
                        else if (str == "end")
                        {
                            count--;
                        }

                        if (count > 0) // Don't add the final "end" to v
                        {
                            v.push_back(str);
                        }
                        else if (count == 0)
                        { // Matched the 'end' for the initial 'begin'
                            break;
                        }
                        // If count < 0, it's an unbalanced begin/end, potential error in input
                    }
                }
                else
                {
                    // If the line after "always" is not "begin",
                    // this parser currently assumes it's an empty always block
                    // or a syntax it doesn't support for multi-line content without begin/end.
                    // `v` will remain empty, and `always_block` will handle it.
                    // If `str` (the line read as `next_line`) was meant to be part of a single-line always,
                    // then `v.push_back(str)` would be needed here, but current logic focuses on begin/end blocks.
                }
            }
            curr = always_block(v, curr);
        }
        // else if(find_char(str,'=')){ // Example of handling other statements
        //     cout<<curr<<"  -->  "<<str<<endl;
        //     outfile<<curr<<"  -->  "<<str<<endl;
        //     curr = str;
        // }
    }
    cout << curr << "  -->  " << "END" << endl;
    outfile << curr << "  -->  " << "END" << endl;

    file.close();
    outfile.close();

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);
    cout << "Processing time: " << duration.count() << " ms" << endl;

    return 0;
}

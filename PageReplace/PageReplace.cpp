// PageReplace.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void Work();
void Welcome();
void Opt();
void Fifo();
void Lru();
void Input(unsigned &, unsigned &);
void Output(vector<int>::iterator);
void Outputmem(vector<int>&);
void Inputpages(vector<int>&, const unsigned &);
vector<int>::iterator Found(vector<int>&, vector<int>::iterator, unsigned);

vector<int>pages, mem;
vector<int>::iterator pagesIter, memIter;
unsigned size, pagesNum;

int main()
{
    Work();
    return 0;
}

void Work()
{
    int comd;
    while (true)
    {
        Welcome();
        cin >> comd;
        system("cls");
        switch (comd)
        {
        case 1: {
            Input(size, pagesNum);
            Inputpages(pages, pagesNum);
            break;
        }
        case 2: {
            Opt();
            break;
        }
        case 3: {
            Fifo();
            break;
        }
        case 4: {
            Lru();
            break;
        }
        case 0: {
            return;
        }
        default: {
            cout << endl << "请输入正确选项" << endl << endl;
            break;
        }
        }
        system("pause");
        system("cls");
    }
}

void Welcome()
{
    cout << "*************  请选择选项  *************" << endl;
    cout << "* 1. 输入数据                          *" << endl;
    cout << "* 2. OPT算法(最佳置换算法)             *" << endl;
    cout << "* 3. FIFO算法(先进先出置换算法)        *" << endl;
    cout << "* 4. LRU算法(最近最久未使用)           *" << endl;
    cout << "* 0. 退出                              *" << endl;
    cout << "****************************************" << endl;
}

void Opt()
{
    vector<int>tmp;
    vector<int>::iterator tmpIter;
    map<unsigned, int>mp;
    tmp.clear();
    mp.clear();
    mem.clear();
    int cnt = 0;
    for (pagesIter = pages.begin(); pagesIter != pages.end(); pagesIter++)
    {
        Output(pagesIter);
        if (mp[*pagesIter] == 0)
        {
            cnt++;
            if (mem.size() < size)
            {
                mem.push_back(*pagesIter);
                mp[*pagesIter] = 1;
                tmp = mem;
            }
            else
            {
                for (auto ixIter = pagesIter + 1; ixIter != pages.end(); ixIter++)
                {
                    if (tmp.size() == 1)
                        break;
                    tmpIter = Found(tmp, tmpIter, *ixIter);
                    if (tmpIter != tmp.end())
                        tmp.erase(tmpIter);
                }
                tmpIter = tmp.begin();
                memIter = Found(mem, memIter, *tmpIter);
                mem.insert(memIter, *pagesIter);
                memIter = Found(mem, memIter, *tmpIter);
                mp[*memIter] = 0;
                mem.erase(memIter);
                mp[*pagesIter] = 1;
                tmp = mem;
            }
            Outputmem(mem);
        }
    }
}

void Fifo()
{
    queue<unsigned>que;
    map<unsigned, int>mp;
    while (!que.empty())
        que.pop();
    mp.clear();
    mem.clear();
    int cnt = 0;
    for (pagesIter = pages.begin(); pagesIter != pages.end(); pagesIter++)
    {
        Output(pagesIter);
        if (mp[*pagesIter] == 0)
        {
            cnt++;
            if (mem.size() < size)
            {
                mem.push_back(*pagesIter);
                que.push(*pagesIter);
                mp[*pagesIter] = 1;
            }
            else
            {
                unsigned x = que.front();
                que.pop();
                memIter = Found(mem, memIter, x);
                mem.insert(memIter, *pagesIter);
                que.push(*pagesIter);
                mp[*pagesIter] = 1;
                memIter = Found(mem, memIter, x);
                mem.erase(memIter);
                mp[x] = 0;
            }
            Outputmem(mem);
        }
    }
}

void Lru()
{
    vector<int>tmp;
    vector<int>::iterator tmpIter;
    map<unsigned, int>mp;
    mem.clear();
    tmp.clear();
    mp.clear();
    int cnt = 0;
    for (pagesIter = pages.begin(); pagesIter != pages.end(); pagesIter++)
    {
        Output(pagesIter);
        if (mp[*pagesIter] == 0)
        {
            cnt++;
            if (mem.size() < size)
            {
                mem.push_back(*pagesIter);
                mp[*pagesIter] = 1;
                tmp.push_back(*pagesIter);
            }
            else
            {
                tmpIter = tmp.begin();
                memIter = Found(mem, memIter, *tmpIter);
                mem.insert(memIter, *pagesIter);
                memIter = Found(mem, memIter, *tmpIter);
                mem.erase(memIter);
                mp[*tmpIter] = 0;
                mp[*pagesIter] = 1;
                tmp.erase(tmpIter);
                tmp.push_back(*pagesIter);
            }
            Outputmem(mem);
        }
        else
        {
            tmpIter = Found(tmp, tmpIter, *pagesIter);
            tmp.erase(tmpIter);
            tmp.push_back(*pagesIter);
        }
    }
}

void Input(unsigned &size, unsigned &pagesNum)
{
    cout << "请输入内存大小和页面数量" << endl;
    cin >> size >> pagesNum;
}

void Inputpages(vector<int>&ivec, const unsigned &pagesNum)
{
    cout << "请输入" << pagesNum << "个页面" << endl;
    for (unsigned ix = 0; ix < pagesNum; ix++)
    {
        unsigned page;
        cin >> page;
        ivec.push_back(page);
    }
}

void Output(vector<int>::iterator iter)
{
    cout << *iter << endl;
}

void Outputmem(vector<int>&ivec)
{
    for (auto ix : ivec)
    {
        cout << " " << ix;
    }
    cout << endl;
}

vector<int>::iterator Found(vector<int>&ivec, vector<int>::iterator iter, unsigned x)
{
    for (iter = ivec.begin(); iter != ivec.end(); iter++)
    {
        if (*iter == x)
        {
            return iter;
        }
    }
    return ivec.end();
}

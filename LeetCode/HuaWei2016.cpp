#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <sstream>
#include "BTree.hpp"
#include "01_ListNode.hpp"
#include <unordered_set>
using namespace std;
#include "HuaWei2016.hpp"

int findMaxInArray(vector<int> vec, int l, int r){
    //他询问ID从A到B（包括A,B）只是给了一个区间范围
    if(l > r) swap(l, r);
    //从最左l开始遍历所以初始时不能等于vec[1]
    int max = vec[l];
    //[l,r]闭区间
    for(int i = l; i <= r; ++i)
        if(vec[i] > max) max = vec[i];
    return max;
}

int stuTableQandU(){
    string cd1, cd2;
    cd1[2] = '2';
    int n, k;
    //注意⚠️一般多组测试数据需要while循环保证可以输入下一组测试用例
    while(cin >> n >>k){
        //下标从1开始
        vector<int> stu(n+1);
        //输入流会存到下一个合法输出为止
        for(int i = 1; i <= n; ++i) cin>>stu[i];
        
        char op; int l, r;
        for(int i = 0; i < k; ++i){
            cin >> op >> l >> r;
            if(op == 'Q') cout << findMaxInArray(stu, l, r) << endl;
            if(op == 'U') stu[l] = r;
        }
    }
    return 0;
}

int comparePoker(){
//    string input;
//    cin >> input;
//    bool tag = false;
//    string cd1, cd2;
//    for(int i = 0; i < input.size(); i++){
//        if(input[i] == '-') {tag = true; i++; }
//        if(!tag) cd1.push_back(input[i]);
//        if(tag) cd2.push_back(input[i]);
//    }
    string input;
    while(getline(cin, input)){
        if(input.find("joker JOKER") != string::npos) cout << "joker JOKER";
        else{
            int idx = input.find('-');
            string cd1 = input.substr(0, idx);
            string cd2 = input.substr(idx+1, input.size());
            int num1 = count(cd1.begin(), cd1.end(), ' ');
            int num2 = count(cd2.begin(), cd2.end(), ' ');
            
            //自己写个位置大小用find找相对位置来比较大小！！
            string all = "345678910JQKA2jokerJOKER";
            //first card1
            int fc1 = all.find(cd1.substr(0, cd1.find(' ')));
            int fc2 = all.find(cd2.substr(0, cd2.find(' ')));
            
            //用空格个数来算牌的个数,
            if(num1 == num2){
                if(fc1 >= fc2) cout << cd1;
                else cout << cd2;
            }
            else{
                //个数不同且有一个是炸弹,仅能一个输出
                if(num1 == 3) cout << cd1;
                else if(num2 == 3) cout << cd2;
                else cout << "ERROR";
            }
        }
    }
    return 0;
}

bool compare(pair<string, int> a, pair<string, int> b){
    //返回>=不行???
    return a.second > b.second;
}

int fileRecord(void){
    string input, file;
    vector<pair<string, int>> errors;
    while (getline(cin, input)){
        //直接回车跳出,由于读入字符串用0也无法跳出
        if (input.size() == 0)
            break;
        //找到文件名开始位置
        size_t idx = input.rfind('\\');
        //存文件名
        file = input.substr(idx + 1);
        //以pari的方式存,key代表次数
        errors.push_back(make_pair(file, 1));
        //看之前是否出现过同文件名,出现则次数second++当前退出
        for (int i = 0; i<(errors.size() - 1); i++){
            if (errors[i].first == file){
                errors[i].second++;
                errors.pop_back(); break;
            }
        }
    }
    stable_sort(errors.begin(), errors.end(), compare);
    int k = 0;
    //记录最多八条(仅输出8条),文件名不同之前已记录,这里只倒着截取16即可
    while (k<8 && k<errors.size()){
        string check = errors[k].first;
        size_t idx = check.find(' ');
        //也可以check.substr(idx-16)逆取16,右开直接-16
        //正截取右开直接+16,右闭再-1
        if (idx>16)
            errors[k].first.erase(0, idx - 16);
        cout << errors[k].first << ' ' << errors[k].second << endl;
        k++;
    }
    return 0;
}

//招商银行笔试2019.04.09
//2 1 3 2 输出3 4
int personOfSeated(){
    int n, m;
    while (cin >> n >> m) {
        vector<int> pn(n);
        for(int i = 0; i < n; ++i) cin >> pn[i];
        sort(pn.begin(), pn.end());
        if(m < n)
        {
            int idx = pn[0], count = 0;
            for(int i = 0; i < n; ++i)
                if(pn[i] == idx) count++;
                else {idx = pn[i]; count = 1;}
            if(count > 0 && m > pn.size() - count){
                int min = int(pn.size() - count)/count;
                if(min == 0) min = 1;
                cout << pn[n-1]+min << ' ' << pn[n-1]+m;
            }
            else
                cout << pn[n-1] << ' ' << pn[n-1]+m;
        }
        else{
            int min = pn[n-1]+m/n, max = pn[n-1]+m;
            if(max > 100) max = 100;
            cout << min << ' ' << max;
        }
    }
    return 0;
}
bool cmp(const int &l, const int &r)
{
    string ll = to_string(l) + to_string(r);
    string rr = to_string(r) + to_string(l);
    return ll < rr;
}

//华为2019软件题<二>04.10
string add(string s){
    //i=0；i < 8-s.size()行不通因为push后size会变
    for(size_t i = s.size(); i < 8; ++i)
        s.push_back('0');
    return s;
}

int cutString(){
    int n;
    cin >> n;
    
    vector<string> arr(n);
    for(int i  = 0; i < n; i++)
        cin >> arr[i];
    vector<string> vec;
    for(int i =0; i < arr.size(); ++i){
        if(arr[i].length() < 8){
            vec.push_back(add(arr[i]));
        }
        else{
            //vec.push_back(vec[i].substr(8));
            //vec[i] = vec[i].substr(0, 8);
            string temp = arr[i];
            while(temp.length() > 8){
                vec.push_back(temp.substr(0,8));
                temp = temp.substr(8);
            }
            vec.push_back(add(temp));
        }
    }
    sort(vec.begin(), vec.end());
    int i = 0;
    for(; i < vec.size() - 1; ++i){
        cout << vec[i] << " ";
    }
    cout << vec[i];
    
    return 0;
}

//第二题
string input;
string multi(int t, string s){
    string ans;
    for(int i =1; i <=t; ++i)
        //拷贝n次
        ans+=s;
    return ans;
}

void replace(string lefts, string rights){
    int leftindex = input.rfind(lefts);
    while(leftindex != string::npos){
        //左括号向右的子串里找右括号
        int rightindex = input.substr(leftindex).find(rights) + leftindex;
        //左开右闭
        int nend = leftindex-1;int nstart = nend;
        while(input[nstart] >= '0' && input[nstart] <= '9' && nstart>=0)
            --nstart;
        //num所在区间
        string num = input.substr(nstart+1, nend-nstart);
        int times = atoi(num.c_str());
        string iner = multi(times, input.substr(leftindex+1, rightindex-leftindex-1));
        //拼起来,注意拼到nstart而不是leftindex
        input = input.substr(0, nstart+1)+iner+input.substr(rightindex+1);
        //继续向左找'('
        leftindex = input.rfind(lefts);
    }
    return;
}

int exbandInBracket(){

    cin >> input;
    replace("(", ")");
    replace("[", "]");
    replace("{", "}");
    reverse(input.begin(), input.end());
    cout << input << endl;
    return 0;
}

//第三题60%通过
int h[606][606];
const int mm = pow(10,9);
class point {
public:
    int x, y;
    point(int a, int b) :x(a), y(b){}
};

int maina()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> h[i][j];
        }
    }
    int x, y, z, w;
    cin >> x >> y >> z >> w;
    queue<point> q;
    q.push(point(x, y));
    int count = 0;
    while (!q.empty()) {
        point cur = q.front();
        q.pop();
        if (cur.x == z && cur.y == w) {
            ++count;
            count %= mm;
        }
        if (cur.x - 1 >= 0 && h[cur.x - 1][cur.y] > h[cur.x][cur.y])
            q.push(point(cur.x - 1, cur.y));
        if (cur.x + 1 < n && h[cur.x + 1][cur.y] > h[cur.x][cur.y])
            q.push(point(cur.x + 1, cur.y));
        if (cur.y - 1 >= 0 && h[cur.x][cur.y - 1] > h[cur.x][cur.y])
            q.push(point(cur.x, cur.y - 1));
        if (cur.y + 1 < m && h[cur.x][cur.y + 1] > h[cur.x][cur.y])
            q.push(point(cur.x, cur.y + 1));
    }
    cout << count << endl;
    
    return 0;
}

//2019.04.21 pony.ai
int pony1Office(){
    int n;
    cin >> n;
    vector<vector<int>> input(n, vector<int>(n));
    for(int i = 0;i < n; ++i)
        for(int j = 0;j < n; ++j)
            cin >> input[i][j];
    int a,b,k;
    cin >> a >> b >> k;
    int res = k-1-input[a][b];
    if(res < 0) res = -1;
    cout << res;
    return 0;
}

bool whetherH(int xCur, int yCur, int xPre, int yPre,int h0){
    float k = float((yCur - h0)/(xCur - 0.0));
    float hNormal = float(k*xPre+h0);
    return yPre >= hNormal;
}

//9 5
//5 4 3 4 3 3 3 3 3
//0 1 2 1 4 4 4 4 1
//10%shit
int crossGreenLight(){
    int n, h0;
    cin >> n >> h0;
    vector<int> input(n+1);
    input[0] = h0;
    for(int i = 1; i <=n; ++i)
        cin >> input[i];
    for(int i = 1; i <=n; ++i){
        int pre = i - 1;
        while(pre >= 1){
            if(whetherH(i, input[i], pre, input[pre], h0)){
                cout << pre << endl;
                break;
            }
            else
                pre--;
        }
        if(pre == 0) cout << 0 << endl;
    }
    return 0;
}

void findMax(vector<int>&num, int &cnt, int &max, int &ncnt, int  &next){
    map<int,int>mp;
    cnt = 0;
    ncnt = 0;
    for(int i=0; i<num.size(); ++i)
        mp[num[i]]++;
    max = num[0];
    for(int i=0; i<num.size(); ++i){
        int j=num[i];
        if(mp[j] > cnt){
            ncnt = cnt;
            next = max;
            max = j;
            cnt = mp[j];
        }
    }
}
//美团点评2019.04.23笔试
int changeMatrix(){
    int n,m;
    cin >>n >> m ;
    vector<vector<int>> array(n,vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; ++j)
            cin>>array[i][j];
    }
    int cnt = 0;
    vector<int> list1;
    vector<int> list2;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            cnt++;
            if(cnt%2 == 1)
                list1.push_back(array[i][j]);
            else
                list2.push_back(array[i][j]);
        }
    }
    int cnt1,max1,ncnt1,next1;
    findMax(list1,cnt1,max1,ncnt1,next1);
    int cnt2,max2,ncnt2,next2;
    findMax(list2,cnt2,max2,ncnt2,next2);
    if(max1 == max2){
        if(cnt1 + ncnt2 > cnt2 +ncnt1)
            cout << m*n -cnt1-ncnt2<<endl;
        else
            cout << m*n -cnt2-ncnt1<<endl;
    }
    else{
        cout<<m*n -cnt1 -cnt2 << endl;
    }
    return 0;
}
bool compareByVal(const pair<int,int> p1, const pair<int,int> p2){
    return p1.second >= p2.second;
}

int main11(){
    int n,m;
    cin >> n >> m;
    vector<int> input(n*m);
    map<int,int> m1;
    map<int,int> m2;
    int i,j,temp;
    for(i=0; i<n; ++i)
        for(j=0; j<m; ++j){
            if((i*m+j) % 2 == 0){
                cin >> temp;
                input[i*m+j] = temp;
                m1[temp]++;
            }
            else{
                cin >> temp;
                input[i*m+j] = temp;
                m2[temp]++;
            }
        }
    vector<pair<int, int>> v1(m1.begin(), m1.end());
    vector<pair<int, int>> v2(m2.begin(), m2.end());
    sort(v1.begin(), v1.end(), compareByVal);
    sort(v2.begin(), v2.end(), compareByVal);
    if(v1[0].second != v2[0].second)
        cout << m*n - v1[0].second - v2[0].second << endl;
    else{
        if(v1[0].second+v2[1].second > v2[0].second+v1[1].second)
            cout << m*n - v1[0].second - v2[1].second << endl;
        else
            cout << m*n - v2[0].second - v1[1].second << endl;
    }
    return 0;
}


static bool cmpByVal(const pair<int,int> p1, const pair<int,int> p2){
    return p1.second >= p2.second;
}
vector<int> topKFrequent(vector<int>& nums, int k) {
    map<int,int> mp;
    for(int i=0; i<nums.size(); ++i)
        mp[nums[i]]++;
    vector<pair<int,int>> v(mp.begin(), mp.end());
    sort(v.begin(), v.end(), cmpByVal);
    vector<int> res(k);
    for(int i = 0; i < k; ++i){
        res[i] = v[i].second;
    }
    return res;
}
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> map;
        for(int num : nums){
            map[num]++;
        }
        vector<int> res;
        // pair<first, second>: first is frequency,  second is number
        priority_queue<pair<int,int>> pq;
        for(auto it = map.begin(); it != map.end(); it++){
            pq.push(make_pair(it->second, it->first));
        }
        return res;
    }
};


//2019.05.08华为上合笔试
void dfs(vector<char> &input, int len, int dep, vector<int> &visit, set<vector<char>> &res, vector<char> cur){
    
    if(dep == len)
        res.insert(cur);
    
    
    for (int i = 0; i < len; ++i)
        if(visit[i] == 0){
            visit[i] = 1;
            cur.push_back(input[i]);
            dfs(input, len, dep + 1, visit, res, cur);
            cur.pop_back();
            visit[i] = 0;
        }
    
}


int giftDevide(){
    int n, k;
    cin >> n >> k;
    vector<char> input(n+k-1);
    vector<int> visit(n+k-1, 0);
    for(int i = 0; i < n; ++i)
        input[i] = '*';
    for(int i = n; i < n + k - 1; ++i)
        input[i] = '|';
    set<vector<char>> res;
    vector<char> cur;
    dfs(input, n + k - 1, 0, visit, res, cur);
    
    for(auto &i : res){
        for(auto j : i)
            cout << j << " ";
        cout << endl;
    }
    
    cout << res.size();
    return 0;
}


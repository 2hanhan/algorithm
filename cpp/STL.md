# 容器
各个容器的时间复杂度
 操作|访问，一般是指下标`[n]`访问，关联容器应该是用key|`push_back()`|`push_front()`|`insert()`|`pop_back()`|`pop_front()`|`erase()`|`find()`
-|-|-|-|-|-|-|-|-
顺序容器|
list|$O(n)$|$O(1)$|$O(1)$|$O(1)$，但是确定迭代器的位置需要$O(n)$|$O(1)$|$O(1)$|$O(1)$|不支持
vector|$O(1)$|$O(1)$|不支持|$O(n)$|$O(1)$|不支持|$O(n)$|不支持
deque|$O(1)$|$O(1)$|$O(1)$|$O(n)$|$O(1)$|$O(1)$|$O(n)$|不支持
关联容器红黑树实现|
map、multimap、set、multiset|$O(log(n))$|不支持|不支持|$O(log(n))$|不支持|不支持|$O(log(n))$|$O(log(n))$
关联容器 hashtable实现|
unordered_map、unordered_multimap、unordered_set、unordered_multiset|$O(1)$|不支持|不支持|$O(1)$|不支持|不支持|$O(1))$|$O(1))$|$O(1))$
最坏情况：出现哈希冲突时|$O(n)$|不支持|不支持|$O(n)$|不支持|不支持|$O(n))$|$O(n))$|$O(n))$
> 哈希冲突的时间复杂度，不应该取决于hash的桶内用什么方式存储key value吗？
## 容器适配器
### stack
栈
```c++
int value = 0;
stack<int> mySta;
//顶部
mySta.pop(value);
int x = mySta.top();
mySta.pop();
```

### queue
队列
```c++
int value;
//头部
queue<int> myQue;
myQue.push(value);
int x = myQue.front();
myQue.pop();
//尾部
int x = myQue.back();
```
### priority_queue
优先级队列
```c++
// 自定义比较器，从大到小排列，小根堆
class MyComparison
{
public:
    bool operator()(const int &x1, const int &x2)
    {
        return x1 > x2;
    }
}

int value = 0;
priority_queue<int, vector<int, int>, MyComparison> myPri_que;
//根
int x = myPri_que.top();
myPri_que.pop();
//插入自动排序
myPri_que.push(value)//插入操作
myPri_que.emplace(10);//也是插入操作，直接构造，节省了拷贝复制的时间
```


## 顺序容器
### list
```c++
int size = 10
int value = 0;

list<int> myList(10);//10个默认值为0
list<int> myList(size, value);//size个默认值为value
list<int>::iterator iter  = myList.begin();

myList.insert(iter,value);//向iter位置插入元素，iter之后的元素后移


```

### deque
双向队列
```c++
int value = 0;
deque<int> myDeq;
//头部
myDeq.push_front(value);
int x = myDeq.front();
myDeq.pop_front();
//尾部
myDeq.push_back(value);
int x = myDeq.back();
myDeq.pop_back();

```
### vector
```c++
int value = 0;
vector<int> myVec;
//尾部
myVec.push_back(value);
```

## 关联容器
### unordered_map
无序容器、哈希映射
```c++
int num = 0;
int key = 0;
pair<int, string> keyValue;
unordered_map<int,string> myMap;
auto iter = myMap.begin();
// 插入
myMap.insert(keyValue);
//访问
myMap[key];      //通过重载的[]访问，没有key时value自动插入填充默认值
//查找
iter = myMap.find(key);  //查找key,value，返回迭代器，没找到返回myMap.end();
num =myMap.count(key); //返回匹配key的个数 
//删除
num = myMap.erase(key); //根据key删除，返回成功删除的键值对的数量。
iter = myMap.erase(iter);//根据迭代器，返回一个指向被删除键值对之后位置的迭代器
iter = myMap.erase(iter,myMap.end());//更加迭代器范围删除，返回一个指向被删除的最后一个键值对之后一个位置的迭代器。
//删除容器内所有键值对
myMap.clear();
```

### map
有序容器，红黑树
```c++
int num = 0;
int key = 0;
map<int, int> myMap;
pair<int, int> keyValue;
auto iter = myMap.begin();

// 插入 
myMap.insert(keyValue);
// 查找
iter = myMap.find(key) //查询key，如果找到返回迭代器，找不到返回myMap.end()

myMap.count(key);//查询key，如果找到返回1，找不到返回0
```


# 迭代器
> 测试下来的迭代器超过end()会从begin()重新开始，至少list是这样
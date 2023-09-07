# 容器
各个容器的时间复杂度
 操作|访问，一般是指下标`[n]`访问，关联容器应该是用key|`push_back()`|`push_front()`|`insert()`|`pop_back()`|`pop_front()`|`erase()`|`find()`
-|-|-|-|-|-|-|-|-
顺序容器|
list|$O(n)$|$O(1)$|$O(1)$|$O(1)$，但是确定迭代器的位置需要$O(n)$|$O(1)$|$O(1)$|$O(1)$`iter = l.easse(iter)`|不支持
vector|$O(1)$|$O(1)$|不支持|$O(n)$|$O(1)$|不支持|$O(n)$ `iter = v.erase(iter)`|不支持
deque|$O(1)$|$O(1)$|$O(1)$|$O(n)$|$O(1)$|$O(1)$|$O(n)$`iter = d.easse(iter)`|不支持
关联容器红黑树实现|
map、multimap、set、multiset|$O(log(n))$|不支持|不支持|$O(log(n))$|不支持|不支持|$O(log(n))$`m.erase(iter++)`|$O(log(n))$
关联容器 hashtable实现|
unordered_map、unordered_multimap、unordered_set、unordered_multiset|$O(1)$|不支持|不支持|$O(1)$|不支持|不支持|$O(1))$|$O(1))$|$O(1))$
最坏情况：出现哈希冲突时|$O(n)$|不支持|不支持|$O(n)$|不支持|不支持|$O(n))$|$O(n))$|$O(n))$
> 哈希冲突的时间复杂度，不应该取决于hash的桶内用什么方式存储key value吗？

# 迭代器
### 迭代器失效
>本质原因后续的增加删除操作导致原本存放数据的内存发生变化（被删除或者被扩容拷贝到了其他地方），而先前定义的迭代器还指向原来的位置造成的。
1. `vector`和`string`这种在内存中连续位置存储的容器。`vector`和`string`内存中只有一块连续区域，扩容时在内存中另外找一份更大的连续区域（一般2倍or1.5倍扩容大概），然后将原本的数据拷贝到新的内存中并删除释放原有的数据。这会导致迭代器失效。
    - 增加元素导致扩容机制作用时，导致**所有的迭代器**失效。因为扩容机制导致搬运。
    - 在非尾部位置插入元素时，导致**插入位置后的所有迭代器**失效。因为插入元素，后面的元素会向后移动的一段位置。
    - 删除元素，导致**删除位置后的迭代器失效（包括`end()`）**。所以只能`iter = a.erase(iter)`

2. `deque`在内存中时一片、一片、一片....的连续区域的容器，不过数据前后位置都会预留一定的空余空间。扩容是只需再开辟一片内存不需要进行搬运。
    - 在非`front`和`back`位置插入元素时，导致**所有迭代器**失效，因为插入元素，前面或后面的元素会向前或向后移动的一段位置。
    - 在`front`和`back`位置插入元素时，导致`end()`失效，不会导致其他迭代器失效。因为扩容机制不会搬运。
    - 删除元素，导致**删除位置后的迭代器失效（包括`end()`）**。所以只能`iter = a.erase(iter)`
3. `list`和`forward_list`这种在内存中完全分散开存储，通过指针相互连接的容器。没有所谓的扩容操作。
    - 一般**不存在迭代器失效**问题。
4. `map`、`multimap`、`set`、`multiset`和`unordered_map`、`unordered_set` 这些关联性迭代器
    - 一般**不存在迭代器失效**问题。
    - 删除节点使用`a.erase(iter++) 或者 it = a.erase(iter)`，测试下来效果是一样的。


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


// 也可以使用lambda表达式进行处理
vector<int> nums;
int size = nums.size();
vector<int> next(size, 0);

// 引用传递捕获next数组变量，
auto cmp = [&](const int &a, const int &b)
{ return nums[a][next[a]] > nums[b][next[b]]; };

priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
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



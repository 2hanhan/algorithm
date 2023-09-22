# 模板
模板实例化需要知道具体函数的定义。

- `std::funtion`
- `std::bind`

## 容器
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

## 迭代器
#### 迭代器失效
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


### 容器适配器
适配器是标准库中通用的概念，包括容器适配器、迭代器适配器和函数适配器。本质上，适配器是使一事物的行为类似于另一类事物的行为的一种机制。容器适配器让一种已存在的容器类型采用另一种不同的抽象类型的工作方式实现。
#### stack 栈
后进先出。栈的底层实现vector，deque，list 都是可以的，STL标准库默认是以deque为缺省情况实现的。不提供迭代器(iterator)进行遍历。 
```c++
int value = 0;
stack<int> mySta;
mySta.push(value);
mystack.emplace(1);//c++11：也是放入新的元素。这个新元素是通过传递 args 作为其构造函数的参数来构造的，效率更高。
int value = mySta.top();
mySta.pop();
bool isempty = mySta.empty();
int size = mySta.size();
mySta.swap(stack<int>());
```

#### queue 队列
先进先出。STL标准库默认是以deque为缺省情况实现的。同样不提供迭代器(iterator)进行遍历。 
```c++
int value;
queue<int> myQue;
myQue.push(value);
myQue.emplace(1);
int value_top = myQue.front();
myQue.pop();
int value_back = myQue.back();
bool isempty = myQue.empty();
int size = mySta.size();
mySta.swap(queue<int>());
```
#### priority_queue 优先级队列
内部维持某种有序，然后确保优先级最高的元素总是位于头部。最高优先级元素总是第一个出列。大顶堆（堆头是最大元素），小顶堆（堆头是最小元素）一般使用  priority_queue 进行实现，且默认情况下是大顶堆（比较函数为less ） 。
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
int value_top = myPri_que.top();
myPri_que.pop();
myPri_que.push(value)//插入操作
myPri_que.emplace(10);//也是插入操作，直接构造，节省了拷贝复制的时间
bool isempty = myPri_que.empty();
int size = myPri_que.size();
mySta.swap(priority_queue<int, vector<int, int>, MyComparison>());

// 也可以使用lambda表达式进行处理
vector<int> nums;
int size = nums.size();
vector<int> next(size, 0);

// 引用传递捕获next数组变量，
auto cmp = [&](const int &a, const int &b)
{ return nums[a][next[a]] > nums[b][next[b]]; };

priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
```


### 顺序容器
#### list
```c++
int size = 10
int value = 0;

list<int> myList(10);//10个默认值为0
list<int> myList(size, value);//size个默认值为value
list<int>::iterator iter  = myList.begin();

myList.insert(iter,value);//向iter位置插入元素，iter之后的元素后移


```

#### deque
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
#### vector
```c++
int value = 0;
vector<int> myVec;
//尾部
myVec.push_back(value);
```

### 关联容器
#### unordered_map
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

#### map
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



## 算法
### accumulate
### equal
使用`==`运算符比较实现
### fill
写入元素
```c++
fill(vec.begin(), vec.end(), 0);//将全部元素置0
```
### fill_n
```c++
fill_n(vec.begin(), 10, 0);//从vec.begin()开始填充10个元素0，要程序员保证不能序列长度从vec.begin()不能超过10个
```
#### back_inserter 
返回插入迭代器
```c++
auto it = back_inserter(vec);
fill_n(back_inserter(vec), 10, 0);
```

### copy
```c++
int a1[] = {0,1,2,3,4,5}
int a2[sizeof(a1)/sizeof(*a1)];//a2与a1大小一致
// 将a1拷贝到a2
auto it = copy(begin(a1), end(a1), a2);//返回拷贝到a2的尾元素之后的位置
```

### replace
### replace_copy
### sort
使用`<`运算符比较实现
### unique
```c++
auto end_unique = unique(vec.begin(), vec.end());//并不删除只是覆盖相同元素，返回应该删除的位置
```
### stable_sort
与sort相比使用归并排序实现能保证算法的稳定性
### find_if
获取满足条件的第一个迭代器
### for_each


# 迭代器test
> 测试下来的迭代器超过end()会从begin()重新开始，至少list是这样
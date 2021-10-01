### my-json

简单的json分析器

### 基本思想

因为list和dict中的值可以是null、string、number、bool、dict、list中的任何一种，因此不能使用固定的类型
所以使用父类指针，null、string、number、bool、dict、list继承Json_value，Json_value指针可以指向任意子类对象

为了避免忘记释放内存导致内存泄漏使用智能指针管理资源，同时也可以在Json对象赋值给别的Json对象时，节省内存空间


![](https://github.com/foregic/my-json/blob/main/images/Json%E8%A7%A3%E6%9E%90%E5%99%A8_drawio.png)
![](https://github.com/foregic/my-json/blob/main/images/states_automate_drawio.png)

解析性能

| 文件大小 | my-json | rapidJson |
| :-:  | :-:  | :-:|
|22M|858ms|578ms|
|302M|11314ms|7812ms|

### 改进方向

1. number类型目前是用long double简单固定，比较浪费空间也不太实用，目前改进方向是采取Redis的数字类型
2. dict存储数据使用的是unordered_map，改进方向是重写一个key-value数据类型，支持快速查找key对应的value，同时也能增加key-value对，目前改进方向也是使用Redis的Hashtable类型
3. list存储数据使用的是vector存储，可以支持随机读取，但是从末尾增加元素比较快，暂时没有封装才从头部插入数据的方法，目前改进方向暂无，因为list必须要支持随机读写，插入元素速度要求不是很高
4. string用的也是STL的string类型，改进方向暂无
5. bool用的bool
6. null用的是string存储一个null字符串

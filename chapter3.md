# Chapter2 字符串、向量和数组

## 3.1 命名空间的using声明

1. 作用域操作符（::）：编译器应从操作符左侧的名字所示的作用域中寻找右侧那个名字。因此，std::cin的意思就是要使用命名空间std中的名字cin。

1. 使用using就可以声明就无需专门的前缀::也能使用所需的名字。

1. 头文件一般不应包含using声明，因为头文件的内容会拷贝到所有引用它的文件中去，由此可能产生始料未及的名字冲突。

## 3.2 标准库类型string

1. 作为标准库的一部分，string定义在命名空间std中。所以当我们直接使用string的时候，需要包含

    ```c++
    #include <string>
    using std::string; // 注意不要忽略后面这个分号
    ```

1. string初始化的方式

    |                     |                                                     |
    | ------------------- | --------------------------------------------------- |
    | string s1           | 默认初始化，s1是空串                                |
    | string s2(s1)       | s2是s1的副本                                        |
    | string s2 = s1      | 等价于上一条，s2是s1的副本                          |
    | string s3("value")  | s3是字面值“value”的副本，除了字面值最后那个空字符外 |
    | string s3 = "value" | 等价于上一条，s3使字面值“value”的副本               |
    | string s4(n, 'c)    | 把s4初始化为连续n个字符                             |

1. 拷贝初始化与直接初始化：
    - 拷贝初始化：使用‘=’来初始化
    - 不使用‘=’则是直接初始化

    ```c++
    string s5 = "haha"; // 拷贝初始化
    string s6("haha"); // 直接初始化
    string s7(10, 'c'); // 直接初始化，s7内容是cccccccccc
    ```

1. 需要注意的string操作

    |           |                                                                                      |
    | --------- | ------------------------------------------------------------------------------------ |
    | s.size()  | 返回s中的字符数                                                                      |
    | s1+s2     | 返回s1和s2连接后的结果                                                               |
    | s1==s2    | 如果s1和s2中所含的字符完全一样，则他们相等，string对象对相等性判断对字母的大小写敏感 |
    | s2!=s2    | 同上                                                                                 |
    | <,>=,<=,> | 利用字符在字典中的顺序进行比较                                                       |

1. getline函数的参数是一个输入流和一个string对象（getline(cin， str)），函数从给定的输入流中读取内容，知道遇到换行符位置（**注意换行符也被读进来了**）然后把所读的内容存入到那个string对象中去（**注意此时不存换行符**，实际上换行符被丢弃掉了，string对象中不包含该换行符）。如果getline一开始就遇到了换行符，那么它将存入string一个空串。

1. string的成员函数size()返回的并不是一个int或unsigned，而是string::size_type类型的值。size_type是一种无符号类型的值而且能足够存放下任何string对象的大小。所有用于存放string类的size函数返回值的变量，都应该是string::size_type类型的。

1. c++11新标准中auto或者decltype可以推断size_type的类型：

    ```c++
    auto len = line.size() // len的类型是string::size_type
    ```

1. 由于size函数返回的是一个无符号整型数，所以此时如果混用带符号的类型数可能会产生意想不到的后果。

    ```c++
    int n = -20;
    if(s.size() < n){ // 此处n会被转成unsigned类型的求模数，此条件永远为true
        // code_block
    }
    ```

1. 两个string对象之间的比较：
    - 如果两个string对象长度不同，且较短string对象的每个字符都与长对象的字符相同，则会返回长度比较的结果
    - 如果两个string对象在某些位置上的字符不同，那么就直接返回第一对不同字符之间的比较结果

1. 当把string对象和字符字面值及字符串字面值混用在一条语句中使用时，必须确保每个加法运算符（+）的两侧的运算对象至少有一个是string

    ```c++
    string s4 = s1 + ", "; // 正确：把一个string对象和一个字面值相加
    string s5 = "Hello" + ", "; // 错误，两个运算对象都不是string
    string s6 = s1 + "," + "world";
    string s7 = "Hello" + ", " + s2; // 错误，不能把字面值直接相加
    // string7的编译过程如下：
    string s7 = ("Hello" + ", ") + s2;
    // 然而("Hello" + ", ")这个过程编译器无法做到，所以是错的
    ```

1. 为了与c兼容，c++语言中的**字符串字面值不是标准库类型的string对象**。而是字符串数组

1. cctype头文件中的函数：

    |             |                                                   |
    | ----------- | ------------------------------------------------- |
    | usalnum(c)  | 当c是字母或数字时为真                             |
    | isalpha(c)  | 当c是字母时为真                                   |
    | iscntrl(c)  | 当c是控制字符时为真                               |
    | isdigit(c)  | 当c是数字时为真                                   |
    | isgraph(c)  | 当c不是空格但可以打印时为真                       |
    | islower(c)  | 当c是小写字母时为真                               |
    | isprint(c)  | 当c是可打印字符时为真（即c是空格或c具有可视形式） |
    | ispunct(c)  | 当c是标点符号时为真                               |
    | isspace(c)  | 当c为空白时为真                                   |
    | isupper(c)  | 当c为大写字母时为真                               |
    | isxdigit(c) | 当c为十六进制数字时为真                           |
    | tolower(c)  | 转换成小写字母                                    |
    | toupper     | 转换成大写字母                                    |

1. cctype是c语言中的ctype.h标准库，只不过cctype命名规范上符合c++对标准库的文件名的要求（不包含.h）。所以去掉.h同时在开头加上c，表示这个=是一个属于c语言标准的头文件。

1. range for语句：其中expression是一个对象，用于表示一个序列。declaration负责定义一个变量，该变量将被用于访问序列中的基础元素。每次迭代，declaration部分的变量会被初始化为expression部分的一个元素值。

    ```c++
    \\ for (declaration: expression){
    \\    statement;
    \\ }
    string str("Hello World");
    for(auto c: str)
        cout << c << endl;
    ```

1. 一个更复杂的例子：

    ```c++
    string str("Hello World!!!!");
    decltype (str.size()) count = 0;
    for(auto c: str){
        if(ispunct(c)){
            count++;
        }
    }
    cout << count << "punctuation characters in " << str << endl; // count is 4
    ```

1. 如果想要改变string对象中字符的值，则**必须把循环变量定义成引用类型**。

    ```c++
    string str("Hello World!!!!");
    for(auto &s: str){
        s = toupper(s);
    }
    cout << str << endl;
    ```

1. string的下标的值被称作“下标”或“索引”。任何表达式只要它的值是一个整型就能作为索引。所有带符号的类型都会被转换成string::size_type表达的无符号类型。切记，每次**使用下标访问string时都需要判断那个位置是否为空**（isempty()），否则结果将是未定义的。

1. 使用下标进行迭代：

    ```c++
    for(decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]); index++){
        s[index] = toupper(s[index]);
    }
    ```

1. 应该总是将下标设置为string::size_type，因为此类型是无符号数，可以确保下标不会小于0。

## 3.3 标准库类型

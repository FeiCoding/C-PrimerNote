# chapter 9 顺序容器

## 9.1 顺序容器概述

1. 顺序容器类型：
   | 容器名称     | 容器简介                                                                   |
   | ------------ | -------------------------------------------------------------------------- |
   | vector       | 可变大小数组，支持快速随机访问，在尾部之外的位置插入或删除元素可能会很慢   |
   | deque        | 双端队列，支持快速随机访问，在头尾位置插入或删除很快                       |
   | list         | 双向链表，只支持双向顺序访问，在list中任何位置进行插入或删除都很快         |
   | forward_list | 单项链表，只支持单向顺序访问。在链表任何位置进行插入、删除操作都很快       |
   | array        | 固定大小数组，支持快速随机访问，不能天假或删除元素                         |
   | string       | 与vector相似的容器，但专门用于保存字符，随机访问快，在尾部插入、删除速度快 |

1. list和forward_list两个容器的设计目的是令容器任何位置的添加和删除操作都很快速。作为代价，**这两个容器不支持元素的随机访问**：为了访问一个元素，我们只能遍历整个容器。另外和vector、deque和array相比，这**两个容器的额外内存开销也很大**。

1. **string和vector将元素保存在连续的内存空间中。**由于元素是连续存储，由元素的下标来计算其地址是非常快速的。但是每次添加或删除元素，需要移动插入、删除位置之后的所有元素来保持连续存储。

1. **deque支持随机快速访问。deque在中间位置添加或删除元素的代价可能很高。**但是在deque的两段添加或删除元素都是很快的。与list和forward_list添加删除元素的速度相当。

1. 相比于内置数组，array是一种更安全更容易使用的数组类型。array对象的大小是固定的。**因此array不支持添加和删除元素以及改变容器大小的操作。**

1. forward_list的设计目标是达到与最好的手写的单项链表数据结构相当的性能。因此，**forward_list没有size操作**，因为保存或计算其大小就会比手写链表多出额外的开销。对其他容器而言，size保证是一个快速的常量时间的操作。

1. **现代c++程序应该使用标准库容器，而不是更原始的数据结构（比如内置数组）。**

1. **通常来说，使用vector是最好的选择，除非有更好的理由选择其他容器。**

1. 选择容器的基本原则：
   - 除非有很好的理由，否则使用vector
   - 如果程序有很多小的元素，且**空间的额外开销很重要，则不要使用list或forward_list**
   - 如果程序要**求随机访问元素**，应使用vector或deque
   - 如果程序要求**在容器的中间插入或删除元素**，应使用list或forward_list
   - 如果程序需要**在头尾位置插入或删除元素**，但不会在中间位置进行插入或删除操作，则使用deque
   - 如果程序只在读取输入时才需要在容器中间位置插入元素，随后需要随机访问元素，则有两种选择：
      - 先添加到vector，然后进行sort操作
      - 先添加到list，然后拷贝到vector

1. 一般来说，应用中占主导地位的操作（执行的访问操作更多还是插入、删除操作更多）来决定容器类型的选择。

## 9.2 容器库概览

1. 一般来说，每个容器都定义在一个头文件中，文件名与类型名相同。即deque定义头文件deque中，list定义在头文件list中，以此类推。

1. 我们可以定义一个容器，其元素的类型是另一个容器：

    ```c++
    vector<vector<string> > lines; // vector的vector
    ```

1. 顺序容器的构造函数的一个版本可以接受容器大小参数，它使用了元素类型的默认构造函数。但某些类没有默认构造函数，我们可以定义一个保存这种类型对象的容器，但我们在构造这种容器时不能只传递给它一个元素数目参数。

    ```c++
    vector<noDefault> v1(10, init); // 正确：提供了元素初始化器
    vecotr<noDefault> v2(10); // 错误：必须提供一个元素初始化器
    ```

1. 容器操作表：
   | 名称                   | 作用                                                        |
   | ---------------------- | ----------------------------------------------------------- |
   | iterator               | 容器类型的迭代器类型                                        |
   | const_iterator         | 可以读取元素，但不能修改元素的迭代器类型                    |
   | size_type              | 无符号整数类型，足够保存此种容器类型最大可能容器的大小      |
   | difference_type        | 带符号整数类型，足够保存两个迭代器之间的距离                |
   | value_type             | 元素类型                                                    |
   | reference              | 元素的左值类型：与value_type&含义相同                       |
   | const_reference        | 元素的const左值类型                                         |
   | C c;                   | 默认构造函数，构造空容器                                    |
   | C c1(c2);              | 构造c2的拷贝c1                                              |
   | C c(b, e);             | 构造c，将迭代器b和e指定的范围内的元素拷贝到c（array不支持） |
   | C c{a, b, c}           | 列表初始化c                                                 |
   | c1 = c2                | 将c1中的元素替换成c2中的元素                                |
   | c1 = {a, v, c}         | 将c1中的元素替换为列表中的元素（不适用于array）             |
   | a.swap(b)              | 交换a和b的元素                                              |
   | swap(a, b)             | 与上面相同                                                  |
   | c.size()               | c中的元素个数                                               |
   | c.max_size()           | c可保存的最大元素数目                                       |
   | c.empty()              | 若c中存储了元素，返回false，否则返回true                    |
   | c.insert(args)         | 将args中的元素拷贝进c                                       |
   | c.emplace(init)        | 使用inits构造c中的一个元素                                  |
   | c.erase(args)          | 删除args指定的元素                                          |
   | c.clear()              | 删除c中的所有元素，返回void                                 |
   | ==, !=                 | 所有容器都支持相等（不等）运算符                            |
   | <, <=, >, >=           | 关系运算符（无序关联容器不支持）                            |
   | c.begin(), c.end()     | 返回指向c的首元素和尾元素之后位置的迭代器                   |
   | c.cbegin(), c.cend()   | 返回const_iterator                                          |
   | reverse_iterator       | 按逆序寻址元素的迭代器                                      |
   | const_reverse_iterator | 不能修改元素的逆序迭代器                                    |
   | c.rbegin(), c.rend()   | 返回指向c尾元素和首元素之前位置的迭代器                     |
   | c.crbegin(), c.crend() | 返回const_reverse_iterator                                  |

### 9.2.1 迭代器

1. **forward_list迭代器不支持递减运算符。**

1. 迭代器支持的算术运算符，只能应用于string、vector、deque和array的迭代器。不适用于其他任何容器类型的迭代器。

1. 一个迭代器范围（iterator range）由一对迭代器表示，两个迭代器分别指向同一个容器中的元素或者是尾元素之后的位置（one past the last element)。这两个迭代器通常被称为begin和end，或者是first和last，它们标记了容器中元素的一个范围。

1. 第二个迭代器虽然叫last，但并不指向最后一个元素，而是最后一个元素之后的位置。这种元素范围被称为左闭合区间（left-inclusive interval），其标准数学描述为：[begin, end)。

1. 迭代器范围的三种性质：
   - 如果begin和end相等，则范围为空
   - 如果begin和end不等，则范围至少包含一个元素，且begin指向该范围中的第一个元素
   - 我们可以对begin递增若干次，使得begin==end

    ```c++
    while(begin != end){
        *begin = val; // 正确：范围非空，因此begin指向第一个元素
        ++begin; // 移动迭代器，获取下一个元素
    }
    ```

1. **list的迭代器不支持大小比较。**

    ```c++
    list<int> lst1;
    list<int>::iterator iter1 = lst1.begin(), iter2 = lst1.end();
    while(iter1 < iter2){ // 错误，使用iter2 != iter2
        // code block
    }
    ```

1. begin和end函数是重载过的，也就是说，实际上有两个名为begin的成员，一个是const成员，返回容器的const_iterator类型，另一个是非常量成员，返回容器的iterator类型的。当我们对一个非常量对象对用这些成员函数时，得到的是返回iterator版本，而常量对象则返回const_iterator。c++11引入了cbegin和cend。

1. 当不需要写访问时，应当使用cbegin和cend函数，用以支持搭配auto使用。

1. 将一个容器初始化为另一个容器的拷贝，两个容器的类型及其元素类型必须匹配。不过，**当传递迭代器参数来拷贝一个范围时，就不要求容器类型是相同的了。而且，新容器和原容器中的元素类型也可以不同，只要能将要拷贝的元素转换为要初始化的容器的元素类型即可。**

1. **当将一个容器初始化为（而非上条中的传递迭代器作为参数）另一个容器的拷贝时，则必须两个容器的类型和元素类型完全相同。**

    ```c++
    list<string> authors = {"milton", "shakespeare", "austen"}; // 新标准，列表初始化
    vector<const char*> article = {"a", "an", "the"};
    list<string> list2(authors); // 正确，类型匹配
    deque<string> authList(authors); // 错误，类型不匹配
    vector<string> words(articles); // 错误，类型不匹配
    forward_list<string> words(articles.begin(), articles.end()); // 正确，可以把char*转换成string
    ```

1. 列表初始化不仅显示的定义了容器中每个元素的值，对于除array之外的容器类型，初始化列表还隐含地制定了容器的大小。（即与初始值一样多的元素）

1. **只有顺序容器的构造函数才接受大小参数，关联容器并不支持。**

1. **当定义一个array时，除了指定元素类型，还要指定容器大小：**

    ```c++
    array<int, 10>::size_type i; // 数组类型必须包括元素类型和大小
    array<int>::size_type j; // 错误，array<int>不是一个类型
    ```

1. **虽然不能对内置数组类型进行拷贝或对象赋值操作，但标准库array并无此限制：**

    ```c++
    int digs[10] = {0, 1, 2, 3, 4, 5};
    int cpy[10] = digs; // 错误，内置数组不支持直接拷贝或赋值
    array<int, 10> digits = {1, 2, 3, 4, 5, 6};
    array<int, 10> copy = digits; // 正确，只要数组类型匹配即可
    ```

1. 如果我们对array进行列表初始化，初始值数目必须等于或小于array的大小，如果初始值数目小于array的大小，则他们被用来初始化array中靠前的元素，所有剩余元素都会进行值初始化。**如果元素类型是一个类类型，那么该类必须有一个默认构造函数**。

1. 标准库array类型允许赋值，赋值号左右两边的运算对象**必须有相同的类型**：

    ```c++
    array<int, 10> a1 = {0, 1, 2, 3, 4, 5};
    array<int, 10> a2 = {0}; // 所有元素都为0
    a1 = a2; // 替换a1中的元素
    a2 = {0}; // 错误，不能将一个花括号列表赋予数组
    ```

1. assign操作（assign操作不适用与关联容器和array）：

   | 操作             | 解释                                                                           |
   | ---------------- | ------------------------------------------------------------------------------ |
   | seq.assign(b, e) | 将seq中的元素替换为迭代器b和e所表示范围中的元素，迭代器b和e不能指向seq中的元素 |
   | seq.assign(il)   | 将seq中的元素替换为初始化列表il中的元素                                        |
   | seq.assign(n, t) | 将seq中的元素替换为n个值为t的元素                                              |

1. assign操作允许我们从一个**不同但相容的类型赋值**，或者从容器的一个子序列赋值。例如我们可以使用assign实现一个vector中的一段char*值赋予一个list中的string。

    ```c++
    list<string> names;
    vector<const char*> oldstyle;
    names = oldstyle; // 错误
    names.assign(oldstyle.cbegin(), oldstyle.cend()); //正确，可以将const char*转换为string
    ```

1. **赋值相关运算会导致指向左边容器内部的迭代器、引用和指针失效。而swap操作将容器内容交换不会导致指向容器的迭代器、引用和指针失效（容器类型为array和string的情况除外）**

1. **赋值运算符要求左边和右边的运算对象具有相同的类型**，它将右边的运算对象中所有元素拷贝到左边运算对象中。顺序容器（array除外）还定义了一个名为assign的成员，允许我们从一个不同但相容的类型赋值，或者从容器的一个子序列赋值。

    ```c++
    list<string> names;
    vector<const, char*> oldstyle;
    names = oldstyle; // 错误，容器类型不匹配
    names.assign(oldstyle.cbegin(), oldstyle.cend()); // 正确，可以将const char*转换为string
    ```

1. swap操作交换**两个相同类型容器的内容**。除了array以外，交换两个容器内容的操作保证会很快，**元素本身并未交换，swap只是交换了两个容器的内部数据结构。**

1. 除array外，swap不对任何元素进行拷贝、删除或插入操作，因此可以保证在常数时间内完成。

1. **除string外，指向容器的迭代器、引用和指针在swap操作之后都不会失效**。他们仍指向swap操作**之前所指向的那些元素**，但是在swap操作之后，这些元素已经属于不同的容器了。

1. string调用swap会导致迭代器、引用和指针失效。

1. swap两个array会真正交换他们的元素，因此，交换两个array所需的时间与array中元素的数目成正比。对于array，在sawp操作之后，**指针、引用和迭代器所绑定的元素保持不变**，但元素值已经与另一个array中对应元素的值进行了交换。

1. 每个容器类型都有三个与大小相关的操作，成员函数size返回容器中元素的个数，empty当size为0时返回布尔值true，否则返回false，max_size返回一个大于或等于该类型容器所能容纳的最大元素数的值。forward_list支持max_size和empty，**但不支持size**。

1. **每个容器都支持相等运算符（==和！=），除了无序关联容器外的所有容器都支持关系运算符（>、>=、<、<=）。**关系运算符左右两边的运算对象必须是相同类型的容器，且必须保存相同类型的元素。即，我们只能将一个vector<int>与另一个vector<int>进行比较，而不能讲一个vector<int>与一个list<int>或一个vector<double>进行比较。

1. 比较两个容器实际上是进行元素的比较。与string的关系运算类似。

    ```c++
    vector<int> v1 = {1, 3, 5, 7, 9, 12};
    vector<int> v2 = {1, 3, 9};
    vector<int> v3 = {1, 3, 5, 7};
    v1 < v2; // true,第三个元素v2 > v1
    v3 < v1; // true,v3少于v1
    ```

1. 只有当元素类型定义了相应的比较运算符时，我们才可以使用关系运算符来比较两个容器。容器的相等使用元素的“==”来实现的，而其他关系符是通过“<”来实现的。所以如果自定义的类并未定义“==”和“<”运算，就不能比较两个保存该类元素的容器。

## 9.3 顺序容器操作

1. 向顺序容器添加元素的操作：

    | 操作名                                  | 解释                                                                                                                                      |
    | --------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------- |
    | forward_list                            | 有自己专有版本的insert和emplace                                                                                                           |
    | array                                   | array不支持该类操作                                                                                                                       |
    | vector、string                          | 不持之push_front和emplace_front                                                                                                           |
    | c.push_back(t) & c.emplace_back(args)   | 在尾部创建一个值为t或由args创建的元素，返回void                                                                                           |
    | c.push_front(t) & c.emplace_front(args) | 在头部创建一个值为t或由args创建的元素，返回void                                                                                           |
    | c.insert(p, t) & c.emplace(p, args)     | 在迭代器p指向的元素之前插入n哥值为t的元素，返回指向新添加的第一个元素的迭代器，若n为0，则返回p                                            |
    | c.insert(p, n, t)                       | 在迭代器p指向的元素之前插入n个值为t的元素。返回指向新添加的第一个元素的迭代器，若n为0，则返回p                                            |
    | c.insert(p, b, e)                       | 在迭代器b和e指定的范围内的元素插入到迭代器p指向的元素之前。b和e不能指向c中的元素。返回指向新添加的第一个元素的迭代器，若范围为空，则返回p |
    | c.insert(p, il)                         | il是一个花括号包围的元素列表，将这些给定值插入到迭代器p指向的元素之前。返回指向新添加的第一个元素的迭代器，若列表为空，则返回p            |

1. **向一个vector、string或deque插入元素会使所有指向容器的迭代器、引用和指针失效。**

1. 向一个vector或string添加元素可能引起整个对象存储空间的重新分配。重新分配一个对象的存储空间需要分配新的内存，并将元素从旧的空间移动到新的空间中。

1. 除了array和forward_list之外，所有顺序容器都支持push_back(**包括string**，等价于 +='c' )。

1. **当我们用一个对象来初始化容器时，或将一个对象插入到容器中时，实际上放入到容器中的是对象值得一个拷贝，而不是对象本身**。就像我们把一个对象传递给非引用参数一样，容器中的元素和提供值的对象之间没有任何关联。

1. 每个insert函数都接受一个迭代器作为其第一个参数，迭代器指出了在容器中什么位置放置新元素，包括指向尾后元素的迭代器。由于迭代器可能指向容器尾部之后不存在的元素的位置，而且在容器开始位置插入元素是很有用的功能，所以insert函数将元素插入到迭代器所指的位置之前。

1. 我们可以将元素插入到容器开始的位置，而不必担心容器是否支持push_front。

1. deque向vector一样提供了随机访问元素的能力，但它提供了vector所不支持的push_front。deque保证在容器首尾进行插入和删除元素的操作都只花费常熟时间，与vector一样，在deque首尾之外的位置插入元素会很耗时。

    ```c++
    vector<string> svec;
    list<string> slist;
    // 下句等价于在slist首部插入元素
    slist.insert(slist.begin(), "Hello");
    // 下句等价于在svec首部插入元素
    svec.insert(svec.begin(), "Hello");
    ```

1. 将元素插入到vector、deque和string中的任何位置都是合法的。然而，这样做可能很耗时。

1. insert函数其中一个版本接受一个元素数目和一个值，他将指定数量的元素添加到指定位置之前，这些元素都按给定值初始化：

    ```c++
    svec.insert(svec.end(), 10, "Anna");
    ```

1. 接受一堆迭代器或一个初始化列表的insert版本将给定范围中的元素插入到指定位置之前：

    ```c++
    vector<string> v = {"quasi", "simba", "frollo", "scar"};
    slist.insert(slist.begin(), v.end() - 2, v.end());
    slist.insert(slist.end(), {"theese", "words", "will", "go", "at", "the", "end"});
    // 运行时错误，迭代器表示要拷贝的范围，不能指向与目的为止相同的容器
    slist.insert(slist.begin(), slist.begin(), slist.end());
    ```

1. **如果我们传递给一对迭代器，他们不能指向添加元素的目标容器。**

1. 新标准下，**接受元素个数或范围的insert版本返回指向第一个新加入元素的迭代器**。如果范围为空，不插入任何元素，insert操作会将第一个参数返回。

1. 使用insert的返回值，可以再容器中一个特定位置反复插入元素：

    ```c++
    list<string> lst;
    auto iter = lst.begin();
    while(cin >> word)
        iter = lst.insert(iter, word); // 等价于调用push_front
    ```

1. 新标准引入是三个新成员：emplace_front\emplace\emplace_back三个函数，这些操作构造而不是拷贝元素。这些操作分IE对应push_front\insert和push_back，允许我们将元素放置在容器头部、一个指定位置之前或容器尾部。当我们调用push或insert函数时，**我们传递的是一个对象的拷贝。**而当我们调用emplace函数时，则是将参数传递给元素类型的构造函数。**emplace成员使用这些参数在容器管理的内存空间中直接构造元素。**

    ```c++
    // 直接在c的末尾构造一个Sales_date对象
    // 使用三个参数的Sales_data构造函数
    c.emplace_back("978-0590353403", 25, 15.99);
    // 错误：没有接受三个参数的push_back版本
    c.push_back("978-0590353403", 25, 15.99);
    // 正确，创建一个临时的Sales_data对象传递给push_back
    c.push_back(Sales_date("978-0590353403", 25, 15.99));
    ```

1. emplace 函数的参数根据元素类型而变化，**参数必须与元素类型的构造函数相匹配**。

   ```c++
   c.emplace_back();//使用Sale_data的默认构造函数
   c.emplace(iter, "99-99999999");
   // 使用Sales_data的接受一个ISBN，一个count和一个price的构造函数
   c.emplace_front("978-0590353403", 25, 15.99);
   ```

1. 例题9.22:

    ```c++
    vector<int>::iterator iter = iv.begin(), mid = iv.begin() + iv.size() / 2;
    while(iter != mid)
        if(*iter == some_value)
            iv.insert(iter, some_value*2);
    ```

    上述代码错在while为无限循环。且当插入一个新元素后，mid将失效，因此需加上mid--:

    ```c++
    while(iter != mid)
        if(*iter == some_value)
            iv.insert(iter, some_value*2);
        else  iter++;
    ```

1. 若果容器中没有元素，访问操作的结果是未定义的。

1. 包括array在内的每个顺序容器都有一个front成员函数，而除forward_list之外的所有顺序容器都有一个back成员函数。这两个操作分别返回首元素和尾元素的**引用**。

1. 对一个空容器调用front和back函数，就像使用一个越界的下标一样，是一种严重的程序设计错误。

1. 如果容器是一个const对象，则 front\back\下标\at 函数返回的都是const的引用。如果不是const，则返回普通引用，也因此我们可以改变元素的值：

    ```c++
    if(!c.empty()){
        c.front() = 42;     // 将42赋予c中的第一个元素
        auto &v = c.back(); // 获得指向最后一个元素的引用
        v = 1024;           // 改变c中的元素
        auto v2 = c.back(); // v2不是一个引用，他是c.back()的一个拷贝。
        v2 = 0;             // 未改变c中的元素
    }
    ```

1. 提供快速随机访问的容器（string，vector，deque和array）也都提供下标运算符。下标运算符接受一个下标参数，返回容器中该位置的元素的引用。给定下标必须在范围内（即大于等于0，小于容器的大小）。

1. 如果我们希望确保下标是合法的，可以使用at成员函数，at成员函数类似下标运算符，但如果下标越界，at会抛出一个out_of_range异常。

    ```c++
    vector<string> svec; 
    cout << svec[0];     // 运行时错误:sve中没有元素
    cout << svec.at(0);  // 抛出一个out_of_range异常
    ```

1. pop_back和pop_front分别删除首元素和尾元素。vector和string不支持push_front，所以也不支持pop_front。不能对一个空容器执行弹出操作。这些操作返回一个void，所以如果需要弹出的元素的值，就必须在执行弹出操作之前保存它。

1. 成员函数erase函数从容器中指定位置删除元素。可以删除一个迭代器指定的单个元素，也可以删除一对迭代器指定的范围内的所有元素。两种形式的erase都返回指向删除的元素之后位置的迭代器。

   ```c++
   list<int> li = {1, 2, 3, 4, 5};
   auto it = li.begin();
   while(it != li.end())
        if(*it % 2 == 1)
            li.erase(it);
        ++it;
    ```

1. 接受一堆迭代器的erase版本允许我们删除一个范围内的元素：

    ```c++
    // 删除两个迭代器表示的范围内的元素
    // 返回指向最后一个被删元素之后位置的迭代器
    elem1 = slist.erase(elem1, elem2); // 调用后，elem1 == elem2
    ```

1. 删除一个容器中的所有元素，我们既可以调用clear，也可以用begin和end获得的迭代器作为参数调用erase。

1. forward_list并未定义insert、emplace和erase，而是定义了名为insert_after、emplace_after和erase_after的操作。原因在于，为了添加或删除一个元素，我们需要访问其前驱，以便改变前驱的链接，但是forward_list是单向链表，在一个单向链表中，没有简单地方法来获取一个元素的前驱。所以单向链表只能在给定元素之后添加删除元素来实现。

1. forward_list还定义了before_begin，它返回一个首前（off-the-beginning）迭代器。这个迭代器允许我们在链表首元素之前并不存在的元素“之后”添加或删除元素。

1. 从forward_list中删除元素：

    ```c++
    using FLI = forward_list<int>;

    int main(int argc, char const *argv[])
    {
        FLI fl = {1, 2, 3, 4, 5, 6};
        auto prev = fl.before_begin();
        auto cur = fl.begin();
        while(cur != fl.end()){
            if(*cur % 2)                    // 若元素为奇数
                cur = fl.erase_after(prev); // 删除它并移动cur，指向删除元素的后一个元素
            else
            {
                prev = cur; // 移动迭代器，指向下一个元素，prev指向cur之前的元素
                ++cur;
            }

        }
        for(auto i : fl){
            cout << i << " ";
        }
        cout << endl;
        return 0;
    }
    ```

1. 我们可以用resize来增大或缩小容器，arra不支持resize。如果当前大小大于所要求的的大小，容器后部的元素都会被删除，如果当前大小小于新大小，则会将新元素添加到容器后部。

   ```c++
   list<int> ilist(10,20); // 10个int，每个都是20
   ilist.resize(15);    // 将5个值为0的元素添加到ilist的末尾
   ilist.resize(25, -1); // 将10个值为-1的元素添加到ilist的末尾
   ilist.resize(5); // 从ilist末尾删除20个元素
   ```

1. 容器操作对迭代器的影响：
   - 添加元素：
     - 如果容器是vector或string，且存储空间被重新分配，则指向容器的迭代器、指针和引用都会失效。如果存储空间未重新分配，指向插入位置之前元素的迭代器、指针和引用仍然有效，但指向插入位置之后元素的迭代器、指针和引用将会失效。
     - 对于deque，擦入到除首尾之外的任何位置都会导致迭代器、指针和引用失效。如果在首尾位置添加元素，迭代器会失效，但指向存在的元素的引用和指针不会失效。
     - **对于list和forward_list，指向容器的迭代器（包括尾后和首前迭代器）、指针和引用仍然有效。**
   - 删除元素：
     - **对于list和forward_list，指向容器的迭代器（包括尾后和首前迭代器）、指针和引用仍然有效。**
     - 对于deque，如果在首尾之外的任何位置删除元素，那么指向被删除元素外其他元素的迭代器、引用或指针也会失效，如果是删除deque的尾元素，则尾后迭代器也会失效，但其他迭代器、引用和指针不受影响，如果是删除首元素，这些也不会受影响。
     - 对于vector和string，指向被删除元素之前元素的迭代器、引用和指针仍然有效，注意，当我们删除元素时，尾后迭代器总是会失效。

1. 由于向迭代器添加元素和从迭代器删除元素的代码可能会使迭代器失效，因此必须保证每次改变容器的操作之后都能正确重新定位迭代器。这个建议对vector、string和deque尤为重要。

1. 我们在调用erase和insert后都更新迭代器，因为两者都会使迭代器失效。在调用erase后，不用递增迭代器，因为erase返回的迭代器已经指向序列中下一个元素。调用insert后，iter指向新插入元素，位于我们正在处理的元素之前。

1. **不要保存end返回的迭代器**，因为每次添加、删除vector或string的元素后，或者deque中首元素之外任何位置添加、删除元素后，原来end返回的迭代器总是会失效。

1. 
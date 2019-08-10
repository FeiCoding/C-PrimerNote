# chapter 8 文件输入输出

## 8.1 IO类

1. iostream定义了用于读写流的基本类型，fstream定义了读写命名文件的类型，sstream定义了读写内存string对象的类型。

    | 头文件   | 类型                                          |
    | -------- | --------------------------------------------- |
    | iostream | istream, wistream从流读取数据                 |
    |          | ostream, wostream向流写入数据                 |
    |          | iostream，wiostream读写流                    |
    | fstream  | ifstream，wifstream从文件读取数据             |
    |          | ofstream，wofstream向文件写入数据             |
    |          | fstream，wfstream读写文件                     |
    | sstream  | istringstream, wistringstream从string读取数据 |
    |          | ostringstream，wostringstream向string写入数据 |
    |          | stringstream, wstringstream读写string         |

1. 为了支持使用宽字符的语言，标准库定义了一组类型和对象来曹总wchar_t类型的数据。宽字符版本的类型和函数的名字以一个w开头。例如，wcin、wcout、wcerr分别对应相应的宽字符版本对象。宽字符版本的类型和对象与其对应的普通char版本的类型定义在同一个头文件中。例如，头文件fstream定义了ifstream和wifstream。

1. 类型ifstream和istringstream都继承自istream，因此我们可以像使用istream对象一样来使用ifstream和istringstream对象。也就是说，我们是如何使用cin的，就可以同样的使用这些类型的对象，例如可以对一个ifstream或istringstream对象调用getline，也可以使用>>从一个ifstream或istringstream对象中兑取数据。类似的，类型ofstream和ostringstream都继承自ostream，因此我们如何使用cout，就可以同样地使用这些类型的对象。

1. **我们不能拷贝或对IO对象赋值**。

    ```c++
    ofstream out1, out2;
    out1 = out2; // 错误，不能对流对象赋值
    ofstream print(ofstream); // 错误，不能初始化ofstream参数
    out2 = print(out2); // 错误，不能拷贝流对象
    ```

1. 由于不能拷贝IO对象，因此我们也不能将形参或返回类型设置为流类型。进行IO操作的函数通常以引用方式传递和返回流。读写一个IO对象会改变其状态，因此传递和返回的引用不能是const的。

1. IO操作可能发生错误，一些错误是可恢复的，而其他错误则发生在系统深处，已经超出了应用程序可以修正的范围。

1. 如果我们在int对象的标准输入键入字符串，读操作就会失败。这样cin会进入错误状态。类似的，如果我们输入一个文件结束标志，cin也会进入错误状态。一个流一旦发生错误，其上后续的IO操作都会失败。只有当一个流处于无措状态时，我们才可以从它读取数据，向它写入数据。由于流可能处于错误状态，因此代码通常应该在使用一个流之前是否处于良好状态，最好的方法就是把它当做一个条件来使用：

    ```c++
    while(cin >> ival){
        // ok: 读入成功
    }
    ```

1. 
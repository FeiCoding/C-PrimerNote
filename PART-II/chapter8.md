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

1. 为了支持使用宽字符的语言，标准库定义了一组类型和对象来操作wchar_t类型的数据。宽字符版本的类型和函数的名字以一个w开头。例如，wcin、wcout、wcerr分别对应相应的宽字符版本对象。宽字符版本的类型和对象与其对应的普通char版本的类型定义在同一个头文件中。例如，头文件fstream定义了ifstream和wifstream。

1. 类型ifstream和istringstream都继承自istream，因此我们可以像使用istream对象一样来使用ifstream和istringstream对象。也就是说，我们是如何使用cin的，就可以同样的使用这些类型的对象，例如可以对一个ifstream或istringstream对象调用getline，也可以使用'>>'从一个ifstream或istringstream对象中兑取数据。类似的，类型ofstream和ostringstream都继承自ostream，因此我们如何使用cout，就可以同样地使用这些类型的对象。

1. **我们不能拷贝或对IO对象赋值**。

    ```c++
    ofstream out1, out2;
    out1 = out2; // 错误，不能对流对象赋值
    ofstream print(ofstream); // 错误，不能初始化ofstream参数
    out2 = print(out2); // 错误，不能拷贝流对象
    ```

1. 由于不能拷贝IO对象，因此我们也不能将形参或返回类型设置为流类型。进行IO操作的函数通常以引用方式传递和返回流。**读写一个IO对象会改变其状态，因此传递和返回的引用不能是const的**。

1. IO操作可能发生错误，一些错误是可恢复的，而其他错误则发生在系统深处，已经超出了应用程序可以修正的范围。

1. 如果我们在int对象的标准输入键入字符串，读操作就会失败。这样cin会进入错误状态。类似的，如果我们输入一个文件结束标志，cin也会进入错误状态。**一个流一旦发生错误，其上后续的IO操作都会失败**。只有当一个流处于无措状态时，我们才可以从它读取数据，向它写入数据。由于流可能处于错误状态，因此代码通常应该在使用一个流之前检查是否处于良好状态，最好的方法就是把它当做一个条件来使用：

    ```c++
    while(cin >> ival){
        // ok: 读入成功
    }
    ```

1. 有时候我们需要知道流为什么失败，此时IO库定义了一个与机器无关的iostate类型，它提供了表达流状态的完整功能。这个类型应该作为一个位集合来使用。IO库定义了4个iostate类型的constexpr值(badbit, failbit, eofbit, goodbit)，表示特定的位模式。这些值用来表示特定类型的IO条件，可以与位运算符一起使用来一次性检测或设置多个标志位。

1. iostate类型的constexpr值：
    - badbit表示系统级错误，如不可恢复的读写错误。一旦badbit被置位，流就无法再使用。
    - failbit表示发生了可恢复的错误，如期望读取数值却读出一个字符等错误，这种问题通常是可以修正的，流还可以继续使用。
    - 如果达到文件结束位置，eofbit和failbit都会被置位。
    - **goodbit的值为0表示流未发生错误**，如果badbit、failbit和eofbit任一被置位，则检测流状态条件会失败。

1. 标准库还定义了一组函数来查询这些标志位的状态。操作good在所有错误位均未置位的情况下返回true，而bad、fail和eof则在对应错误位被置位时返回true。此外，**在badbit被置位时，fail也会返回true**。这意味着，使用good或fail是确定流的总体状态的正确方法。**实际上，我们将流当作条件使用的代码就等价于!fail()。而eof和bad操作只能表示特定的错误。**

1. 我们可以通过几个成员函数来管理流的状态：
   - rdstate 返回一个iostate值，对应当前状态。
   - setstate 操作将给定条件置位，表示发生了对应错误。
   - clear 接受一个iostate类型的参数，用于复位单一的条件状态位。
   - clear 无参数版本则清楚所有错误标志位。

   ```c++
   auto old_state = cin.rdstate(); // 保存旧的流状态
   cin.clear(); // 使cin有效
   process_input(cin); // 使用cin
   cin.setstate(old_state); // 将cin置为原有状态
   ```

1. 对于接受一个参数版本的clear函数可以使用如下方法来复位所需位：

    ```c++
    cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit());
    ```

1. 例题8.1：编写函数，接受一个istream&参数，返回值类型也是istream&。此函数从给定流中读取数据，直至遇到文件结束标志时停止。它将读取的数据打印在标准输出上。完成这些操作后，在返回流之前，对流进行复位，使其处于有效状态。

   ```c++
   istream& func(istream& input){
       string str;
       while(input >> str){
           cout << str << endl;
       }
       str.clear();
       retrun input;
   }
   ```

1. 例题8.3：什么情况下while(cin >> i)会终止？
   - failbit被置位，IO操作失败
   - eofbit被置位，到达流的尾部
   - badbit被置位，流已崩溃

1. 每个流都管理一个缓冲区，用来保存程序读写的数据。例如，如果执行 cout << "Hello"; 文本串可能立即打印出来，但也有可能被操作系统保存在缓存区，随后再打印。缓冲机制可以帮助操作系统将程序的多个输出操作组合成单一的系统级写操作。这一机制可以给单一的设备写操作打来很大的性能提升（写操作很耗时）。

1. 缓冲刷新：
   - 程序正常结束，main函数执行return操作
   - 缓冲区满，需刷新才能写入新的数据
   - **使用操作符如endl来显示刷新缓冲区**
   - 在每个输出操作之后，我们可以用操作符unitbuf设置流的内部状态，来清空缓冲区。（默认情况下对cerr是设置unitbuf的，因此写到cerr的内容都是立即刷新的）
   - 一个输出流可能被关联到另一个流，在这种情况下，当读写被关联的流时，关联到的流会被刷新。例如cin和cerr都关联到cout，因此cin或者cerr操作都会刷新cout的缓冲区

1. 显示刷新缓冲区：
   - endl，换行并刷新缓冲区的工作
   - flush刷新缓冲区，但不输出任何额外的字符
   - ends向缓冲区插入一个空字符，然后刷新缓冲区

1. 使用unitbuf可以使流在接下来的每次写操作之后都进行一次flush操作，而nounitbuf操纵符则重置流，使其恢复使用正常的系统管理的缓冲区刷新机制：

    ```c++
    cout << unitbuf; // 所有输出操作都会立即刷新缓冲区
    cout << nounitbuf; // 回到正常的缓冲方式
    ```

1. **如果程序崩溃，输出缓冲区不会被刷新。当一个程序崩溃以后，它所输出的数据很可能停留在输出缓冲区中等待打印。**

1. tie函数不带参数的版本返回指向输出流的指针，如果对象关联到一个输出流，则返回的就是指向这个流的指针，如果对象未关联到流，则返回空指针。tie第二个版本接受一个指向ostream的指针，将自己关联到此ostream，即x.tie(&o)将流关联到输出流o。

1. 我们可以将一个istream对象关联到另一个ostream，也可以将ostream关联到另一个ostream：

    ```c++
    cin.tie(&cout);
    ostream *old_tie = cin.tie(nullptr); // cin不再关联任何流
    cin.tie(&cerr); // 读取cin会刷新cerr而不是cout,这不是一个好主意
    cin.tie(old_tie); // 重建cin和cout之间的正常关联
    ```

## 8.2 文件输入输出

1. 头文件fstream定义了三个类型来支持文件IO：
   - ifstream，从一个给定文件读取数据
   - ofstream，想一个给定文件写入数据
   - fstream可以读写给定文件

1. 我们可以使用IO运算符<<和>>来读写文件，也可以用getline从一个ifstream读取数据。

1. fstream独有的操作：

    ```c++
    fstream fstrm; // 创建一个未绑定的文件流
    fstream fstrm(s); // 创建一个fstream并打开名为s的文件，s可以使string也可以是一个指向C风格字符串的指针。这些构造函数都是explict的。
    fstream fstrm(s, mode); // 按照指定mode打开文件
    fstrm.open(s); // 打开名为s的文件，并将文件与fstrm绑定
    fstrm.close(); // 关闭与fstrm绑定的文件，返回void
    fstrm.is_open(); // 返回一个bool值，指出与fstrm关联的文件是否成功打开且尚未关闭
    ```

1. 创建文件流对象时，我们可以提供文件名，此时open自动调用：

    ```c++
    ifstream in(ifile); // 构造一个ifstream并打开给定文件
    ofstream out; // 输出文件流未关联到任何文件
    ```

1. **接受一个iostream类型引用（或指针）参数的函数，可以用一个对应的fstream类型调用，也就是说，如果有一个函数接受一个ostream&参数，我们在调用这个函数时，可以传递给他一个ofstream对象，对istream&和ifstream也是类似的。**

1. 当我们调用open函数失败时，failbit会被置位，所以我们需要检测open是否成功：

    ```c++
    if(out){ // 检查open是否成功

    }
    ```

1. **对一个已经打开的文件流调用open会失败，并会导致failbit被置位，随后对文件流的使用或操作都会失败。所以当我们想要把文件流绑定到另一个文件时，必须先关闭已经关联的文件。**

1. 当一个fstream对象被销毁时，close会自动被调用。所以我们可以再循环语句中创建文件流并打开进行处理，而循环结束该文件流对象将会自动销毁。（自动调用close()函数）

1. 文件模式：
   - in，以读方式打开
   - out, 以写方式打开
   - app，每次写操作均定位到文件末尾
   - ate，打开文件后立即定位到文件末尾
   - trunc，截断文件
   - binary，以二进制方式进行IO

1. 每个文件流类型都定义了一个默认的文件模式，当我们未指定文件模式时，就是用此默认模式：
   - 与ifstream关联的文件默认以in模式打开
   - 与ofstream关联的文件以out模式打开
   - 与fstream关联的文件以in和out模式打开

1. 文件模式有如下限制：
   - 只可以对ofstream或fstream对象设定out模式
   - 只可以对ifstream或fstream对象设定in模式
   - 只有当out被设定时才可以设定trunc模式
   - 只要trunc模式没被设定，就可以设定app模式。在app模式下，即使没有显示的指定out模式，文件也总是以输出方式被打开。
   - 默认情况下，即使我们没有指定trunc，以out模式打开的文件也会被截断
   - ate和binary可以用于任何类型的文件流对象，且可以与其他任何文件模式组合使用

1. 默认情况下，当我们打开ofstream时，文件的内容会被丢弃，**阻止一个ofstream清空给定文件的方法是同时指定app模式**：

    ```c++
    ofstream out("file1"); // 隐含以输出模式打开文件并截断文件
    ofstream out2("file1", ofstream::out); // 隐含地截断文件
    ofstream out3("file1", ofstream::out | ofstream::trunc);
    ofstream app("file2", ofstream::app); // 隐含为输出模式，显示指定app模式
    ofstream app2("file1", ofstream::out | ofstream::app);
    ```

1. 每次打开文件时，都要设置文件模式，可能是显式也可能是隐式的。当程序未指定打开模式时，就是用默认值。

## 8.3 string 流

1. string头文件定义了三个类型来支持内存IO：
   - istringstream从string读取数据
   - ostringstream从string写数据
   - stringstream既可以向string读也可以写数据

1. stringstream中的独有操作：

    ```c++
    sstream strm; // strm是一个未绑定的stringstream对象。sstream是头文件sstream中定义的一个类型
    sstream strm; // strm是一个sstream对象，保存string s的一个拷贝，此构造函数时explicit的
    strm.str();   // 返回strm所保存的string中的拷贝
    strm.str(s); // 将string s拷贝到strm中，返回void
    ```

1. 使用istringstream的例子：假设有一个文件列出了一个人的姓名和他所有的号码：

    ```c++
    morgan 20124232 123123412
    drew 1233412
    lee 123342003 241239024 9891234123
    ```

    那么我们就可以使用istringstream这个类来处理这一类数据：

    ```c++
    struct PersonInfo{
        string name;
        vector<string> phones;
    };

    string line, word;
    vector<PersonInfo> people;
    while(getline(cin, line)){
        PersonInfo person;
        istringstream iss(line); // 利用istringstream来绑定读取的那一行
        line >> person.name;
        while(line >> word)
            person.phones.push_back(word);
        people.push_back(person)
    }
    ```

1. ostringstream适用于我们希望逐步构造输出，最后一起打印的情况。

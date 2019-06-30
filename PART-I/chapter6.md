# chapter 6 函数

## 6.1 函数基础

1. 一个典型的函数定义包括以下部分：返回类型（return type）、函数名字、由 0 个或多个形参（parameter）组成的列表以及函数体。

1. return 语句完成两项任务：一是返回 return 语句中的值，而是将控制权从被调函数转移回主调函数。

1. 实参的类型必须与形参额类型相匹配。函数有几个形参，我们就必须提供相同数量的实参。

1. 参数传递允许形参是实参可转换的类型

   ```c++
   double fact(double i){
       return i;
   }
   int d = 1;
   fact(d); // 可以，int可以转换成double
   ```

1. 函数的形参列表可以为空。但是不能省略。为了与 c 语言兼容，也可以使用关键字 void 表示函数没有形参。

   ```c++
   void f1(){ } // 隐式的定义空形参列表
   void f2(void){ } // 显式的定义空形参列表
   ```

1. **形参列表中所有的参数类型都必须写出来，几遍类型相同。任意两个形参的名称都不可以相同。函数最外层作用域的局部变量也不能喝函数形参一样的名字。**

1. 函数的返回值不能是数组类型或者函数类型，但可以是指向数组或函数的指针。

1.  形参和函数体内部定义的变量统称为局部变量（loacl variable）他们对函数而言是“局部”的，仅在函数的作用域内可见，同时局部变量还会隐藏（hide）在外部同名的其他所有声明中。在所有函数体之外定义的对象存在于程序的整个执行过程。此类对象在程序启动时被创建，知道程序结束才会销毁。

1. 我们把只存在于块执行期间的对象称为自动对象（automatic object），当块的执行结束后，块中创建的自动对象的值就变成未定义的了。形参是一种自动对象，函数开始时为形参申请存储空间，因为形参定义在函数体作用域之内，所以一旦函数终止，形参也就被销毁了。

1. 形参初始化的三种方式：

   - 传递给参数的实参初始化形参对应的自动对象
   - 变量本身含有初始值
   - 本身不含有初始值，则执行默认初始化，这意味着内置类型的未初始化局部变量将产生未定义的值。

1. 当有必要令局部变量的生命周期贯穿函数调用及之后的时间，可以将局部变量定义成 static 类型从而获得这样的对象。局部静态对象（loacl static object）在程序的执行路径第一次经过对象定义语句时初始化 ，并指导程序终止才被销毁。在此期间即使对象所在的函数结束执行也不会对它有影响。

   ```c++
   size_t count_calls(){
       static size_t c = 0;
       return c++； // 可以return这个局部变量，因为它是static
       // 如果c不是static将报错
   }
   int main(){
       for(size_t i = 0; i != 10;++i){
           cout << count_calls() << endl;
       }
       return 0;
   }
   ```

1. **如果局部静态变量没有显示初始值，他将执行值初始化，内置类型的局部静态变量初始化为 0**

1. 与变量类似，函数只能定义一次，但可以声明多次，唯一的例外是如果一个函数永远也不会被我们用到，那么它可以只有声明没有定义。

1. 函数声明（也称函数原型 function prototype）无须函数体，用一个分号代替即可，同时也无须形参的名字。然而写上形参的名字可以帮助使用者更好的理解函数的功能。

   ```c++
   // 函数声明加上名字beg和end使我们更好地理解函数的功能
   void print(vector<int>::const_iterator beg,
               vector<int>::const_iterator end);
   ```

1. **函数也应该在头文件中声明，在原文件中定义。把函数放在头文件中声明，就能确保同一函数的所有声明保持一致，而且一旦我们想改变函数的接口，只需改变一条声明即可。含有函数生命的头文件，应当被包含到含有函数定义的源文件中**

## 6.2 参数传递

1. 形参的类型决定了形参和实参交互的方式。如果形参是引用类型，他将被绑定到对应的实参上（引用传递 passed by reference），否则，将实参的值拷贝给形参（值传递 passed by value）。

1. 对于指针形参，当执行指针拷贝操作时，拷贝的是指针的值，拷贝之后，两个指针是不同的指针。下面的代码中，指针形参可以改变实参的值，但无法改变实参的地址。

   ```c++
   void reset(int *p){
       *p = 0; //改变了p所指对象的值
       p = 0; // 只改变了p的局部拷贝，实参无影响
   }
   int main(){
       int i = 42;
       reset(&i); // i的值被改变，但i的地址未被改变
       cout << i << end; // 输出0
   }
   ```

1. 通过使用引用形参，允许函数改变一个或多个实参的值。引用形参绑定初始化它的对象，改变引用形参也就是改变其引用对象的值。

1. 尽量使用引用形参而避免拷贝，因为拷贝某些大的类类型对象或者容器对象比较低效，甚至有的类类型（包括 IO）就不支持拷贝操作。此时我们也只能使用引用形参。

1. **当函数无须改变引用形参的值时，最好将其声明为常量引用。**

1. 我们可以给函数传入一个额外的引用实参，令其保存我们想要的变量，从而实现让函数返回额外的信息。

   ```c++
   string::size_type find_char(const string &s, char c, string::size_type &occurs){
       auto ret = s.size();
       occurs = 0;
       for(decltype(ret) i = 0; i != s.size(); ++i){
           if(s[i] == c){
               if(ret == s.size())
                   ret = i; // 记录第一次出现的位置
               ++occurs; // 将出现次数加一
           }
       }
       return ret; // 出现次数通过occurs隐式的返回
   }
   ```

1. 当实参初始化形参时会忽略掉形参的顶层 const，也就是说当形参有顶层 const 时，传给他常量对象或非常量对象都是可以的。

1. 因为顶层 const 被忽略掉，所以对于相同名字的函数，形参表中的 const 不能区分这些函数，导致重复定义（而非函数重载）。

   ```c++
   void func(int i);
   void func(const int i); // 重复定义
   ```

1. 把函数不会改变的形参定义成普通引用是一种比较常见的错误，这么做带给函数调用者一种误导，即函数可以修改他的实参的值。此外，使用引用而非常量引用也会极大地限制函数所能接受的实参类型。例如，我们不能把 const 对象、字面值或者需要类型转换的对象、传递给普通的引用形参。

   ```c++
   string::size_type find_char(string &s, char c, string::size_type &occurs){
       // string &s是一个不良设计，因为此时find_char（“Hello World", 'o', ctr)将会报错
   }
   ```

1. 另一种情况是当函数嵌套时，外部函数接收了一个常量参数，而内部函数却只能接收一般参数，那么就会导致无法使用内部函数处理参数。

   ```c++
   void find(string &s){
       // code block
   }
   void countUpper(const string &s){
       find(s); // 出错，find无法处理s，此时可以重新定义
                // 一个s的一般拷贝来处理
   }
   ```

1. 数组形参，数组的两个特殊性质限制了我们对数组的参数传递：

   - 不允许直接拷贝数组
   - 数组在使用时自动转换成指针

1. 由此我们无法传递数组，因为当我们传递时，实际上传递的是指向数组首元素的指针。

1. 我们不能以值传递的方式传递数组，但可以把形参写成类似数组的形式：

   ```c++
   void print(const int*);
   void print(const int[]); // 表明传递数组的意图
   void print(const int[10]); //实际并不一定要10个元素的数组传递
   ```

1. 以上三种函数都是等价的，每个函数的唯一形参都是 const int\*类型的，当编译器处理对 print 函数的调用时，只检查传入的参数是否是 const int\*。

1. 三种常用的指针形参的管理办法：

   - 使用标记指定数组长度（例如 c 风格字符串的末尾后面跟着一个空字符作为结束标记）
   - 使用标准库规范，定义一个 begin 指针和一个指向尾元素后方的 end 指针，传参时使用相应的标准库方法

     ```c++
     void print(const int *beg, const int *end){
         // code_block
     }

     int j[2] = {1, 2};
     print(begin(j), end(j));
     ```

   - 显式传递一个表示数组大小的形参

     ```c++
     void print(const int* p, size_t st){
         // code_block
     }

     int j[] = {1,2};
     print(j, end(j) - begin(j))
     ```

1. 当不需要对数组元素进行修改的时候，数组形参应该是 const 的指针。

1. 可以使用数组的引用形参来传递，但是需要注意不要忽略对引用的名称加上括号。

   ```c++
   void print(int (&arr)[10]){ //不加括号则错误，意为引用的数组（不存在）
       //code_block
   }
   ```

1. 二维数组实际是一个数组的数组。数组第二维的大小都是数组类型的一部分，不能省略。有两种参数定义方法：

   ```c++
   void print(int (*matrix)[10], int row_size); // 注意不要忽略括号，同上
   void print(int matrix[][10], int row_size); // 注意不要忽略第二个维度10
   ```

1. main 函数传递参数，第二个形参 argv 是一个数组，它的元素是指向 c 风格的字符串数组，第一个形参 argc 表示的是**数组（切记，是数组中的）**中字符串的数量，因为第二个形参是数组，所以 main 函数也可以定义成下方代码中的第二种：

   ```c++
   int main(int argc, char *argv[]){...}
   int main(int argc, char argv[][]){...}
   ```

1. argv 的第一个参数指向程序的名字，或者一个空字符串，接下来的元素依次为传递命令行提供的实参，最后一个指针之后的元素保证为 0。

1. 如果函数的实参数量未知但是全部实参的类型都相同，我们可以使用 initializer_list 类型的形参。initializer_list 是一种标准库类型，用于表示某种特定类型的值的数组，定义在同名的头文件中。

1. initializer_list 中的元素永远是 const，我们无法改变这些元素的值。使用方法：

   ```c++
   void eror_msg(initilizer_list<string> il){
       for(auto beg = il.begin(); beg != il.end(); ++beg){
           cout << *beg << " ";
       }// 和vector类似，我们也可以使用begin和end方法获取对应指针
   }

   if(expected != actual){ // expected和actual都是string
       error_msg({"functionX", expected, acutal});
   }
   else{
       error_msg({"functionX", "ok"}); // 注意，和上述方法传递参数个数不同
   }
   ```

1. 省略符形参是为了便于 C++程序访问某些特殊的 C 代码而设置的，这些代码使用了 varargs 的 C 标准库功能。省略符形参应该仅仅用于 C 和 C++通用的类型，大多数类类型的对象在传递给省略符时都无法正常拷贝。

   ```c++
   // 对于parm_list会执行正常的类型检查。省略符对应的实参则无须类型检查
   void foo(parm_list, ...);

   void foo(...)
   ```

## 6.3 返回类型和 return 语句

### 6.3.1 无返回值函数

1. void 函数的最后一句后面会有隐式地执行 return，所以不要求非得有 return 语句。

1. void 函数如果想提前退出也可以在语句的中间位置加上 return。

   ```c++
   void swap(int &v1, int &v2){
       if(v1 == v2)
           return; // 如果发现v1和v2相等则提前return
       int temp = v2;
       v2 = v1;
       v1 = temp;
       // 此处无需执行显示的return语句
   }
   ```

### 6.3.2 有返回值函数

1. return 语句返回值的类型必须是函数的返回类型相同，**或者能隐式地转换成函数的返回类型**。

1. 函数的返回值用于初始化调用点的一个临时量，该临时量就是函数调用的结果。例如，如果一个返回类型为 string 的函数成功返回一个 string 值，该值将被拷贝到调用点，函数返回的是函数内临时变量的一个副本或者一个未命名的临时 string 对象。

1. 如果函数返回一个引用，那么该函数返回的是它所引用对象的一个别名。

1. 函数完成后它所占的存储空间也会随之被释放。因此函数终止意味着局部变量的引用（或指针）将引用（或指针）指向不再有效的内存区域。所以切记不可返回局部对象的引用或指针，这一行为将导致返回的值是一个未定义的值。

   ```c++
   const string &manip(){
       string ret;
       if(!ret.empty())
           return ret; // 错误，返回局部对象的引用
       else:
           return "Empty"; // 错误，Empty是一个局部临时量
   }
   ```

1. 函数的返回类型决定函数调用是否是左值。调用一个返回引用的函数得到左值，其他类型则得到右值。可以像使用其他左值那样来使用返回引用的函数的调用。**如果返回类型是常量引用，我们不能给调用的结果赋值**。

   ```c++
   char &get_val(string &str, string::size_type ix){
       return str(ix);
   }
   int main(){
       string s("a value");
       cout << s << endl;
       get_val(s, 0) = 'A'; // 将s[0]的值该位A
       cout << s << endl;
       return 0;
   }
   ```

1. C++11 新标准规定，函数可以返回花括号包围的值的列表。类似于其他返回结果，此处的列表也用来对表示函数返回的临时量进行初始化。如果列表为空，临时量执行值初始化（如果 vector 对象的元素是内置类型，比如 int，则元素初始值自动设置为 0，如果元素是某种类类型，比如 string，则元素由类默认初始化），否则返回的值由函数的返回类型决定。

   ```c++
   vector<string> process(){
       if(expected.empty())
           return{}; // 返回一个空vector对象
       else if(expected == actual)
           return {"FunctionX", "okay"}; // 返回列表初始化的vector对象
       else
           return {"functionX:, expected, actual};
   }
   ```

1. 如果函数返回的是内置类型，则花括号包围的列表最多包含一个值，而且该值所占空间不应该大于目标类型的空间。如果函数返回的是类类型，由类本身定义初始值如何使用。

1. main 函数可以没有 return 语句直接结束，如果控制到达了 main 函数的结尾处而且没有 return 语句，编译器将隐式地插入一条返回 0 的 return 语句。

1. cstdlib 头文件定义了两个预处理变量（所以既不需要在前面加上::，也不能在 using 声明中出现），我们可以使用这两个变量分别表示成功与失败：

   ```c++
   int main(){
       if(some_failure)
           return EXIT_FAILURE;  // 定义在cstdlib头文件中
       else
           return EXIT_SUCCESS; // 定义在cstdlib头文件中
   }
   ```

1. main 函数不能调用他自己，其他函数调用自己时则称为递归函数

### 6.3.3 返回数组指针

1. 因为数组不能拷贝，所以函数不能返回数组。但是函数可以返回数组的指针或引用。以下几种可以返回数组指针的引用或指针的方式：

    1. 使用类型别名：

        ```c++
        typedef int arrT[10]; // arrT是一个类型别名
        using arrT[10] = int[10]; // arrT的等价声明
        arrT* func(int i); // func返回一个指向含有10个整数的数组的指针
        ```

    2. 声明一个返回数组指针的函数( *Type (\*function(parameter_list) [dimention]*))：

        ```c++
        int (*func(int i))[10];
        ```

        上述代码的解释含义：
        1. func(int i)表示调用func函数时需要一个int类型的实参
        2. (*func(int i))意味着我们可以对函数调用的结果执行解引用操作
        3. (*func(int i))[10]表示解引用func的调用将得到一个大小是10的数组
        4. int (*func(int i))[10]表示数组中的元素是int类型的

    3. 使用尾置返回类型：

        ```c++
        // func接受一个int类型的实参，返回一个指针，该指针指向含有10个整数的数组
        auto func(int i) -> int(*)[10]
        ```

    4. 使用decltype

        ```c++
        int odd[] = {1, 3, 5, 7, 9};
        int even[] = {2, 4, 6, 8, 10};

        // arrPtr返回一个指针，并且类型和odd一致
        decltype(odd) *arrPtr(int i){
            return (i % 2) ? &odd : &even; // 返回一个指向数组的指针
        }
        ```

## 6.4 函数重载

1. 如果同意作用域内的几个函数名字相同但形参列表不同，我们称之为重载函数（overload）。这些函数接收的形参类型不同，但执行的操作非常类似。当调用这些函数时，编译器会根据传递的参数类型推断想要绑定的是哪个函数。

1. main函数不能重载。

1. 不允许两个函数除了返回类型外其他所有的要素都相同，假设有两个函数，它们的形参列表一样但是返回类型不同，则第二个函数的声明是错误的。

    ```c++
    Record lookup(const Account&);
    bool lookup(const Account&); // 错误，与上一个函数除了返回类型以外相同

    Record lookup(const Account&);
    Record lookup(const Account& var); //错误，只是多了形参名

    typedef Phone Telno；
    Record lookup(const Phone&);
    Record loopup(const Telno&); // Telno和Phone的类型相同
    ```

### 6.4.1 重载和const形参

1. **顶层const不影响传入函数的对象。一个拥有顶层const的形参无法和另一个没有顶层const的形参区分开来。**

    ```c++
    Record lookup(Account);
    Record lookup(const Account); // 重复声明
    Record lookup(Account* p);
    Record lookup(Account* const p); // 重复声明
    ```

1. 如果形参是某种类型的指针或者引用，则通过区分其指向的是常量对象还是费常量对象可以实现函数重载。**也就是底层const可以区分函数重载。**

    ```c++
    Record lookup(Account &);
    Record lookup(const Account &); // 新函数
    Record lookup(Account* p);
    Record lookup(const Account* p); // 新函数
    ```

1. 

# chapter 6 函数

## 6.1 函数基础

1. 一个典型的函数定义包括以下部分：返回类型（return type）、函数名字、由 0 个或多个形参（parameter）组成的列表以及函数体。

1. return 语句完成两项任务：一是返回 return 语句中的值，二是将控制权从被调函数转移回主调函数。

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

1. **形参列表中所有的参数类型都必须写出来，即便类型相同。任意两个形参的名称都不可以相同。函数最外层作用域的局部变量也不能和函数形参一样的名字。**

1. **函数的返回值不能是数组类型或者函数类型，但可以是指向数组或函数的指针。**

1. 形参和函数体内部定义的变量统称为局部变量（loacl variable）他们对函数而言是“局部”的，仅在函数的作用域内可见，同时局部变量还会隐藏（hide）在外部的其他所有声明中的同名变量。在所有函数体之外定义的对象存在于程序的整个执行过程。此类对象在程序启动时被创建，直到程序结束才会销毁。

1. **我们把只存在于块执行期间的对象称为自动对象（automatic object）**，当块的执行结束后，块中创建的自动对象的值就变成未定义的了。形参是一种自动对象，函数开始时为形参申请存储空间，因为形参定义在函数体作用域之内，所以一旦函数终止，形参也就被销毁了。

1. 形参初始化的三种方式：

   - 传递给参数的实参初始化形参对应的自动对象
   - 变量本身含有初始值
   - 本身不含有初始值，则执行默认初始化，这意味着内置类型的未初始化局部变量将产生未定义的值。

1. 当有必要令局部变量的生命周期贯穿函数调用及之后的时间，可以将局部变量定义成 static 类型。局部静态对象（loacl static object）在程序的执行路径第一次经过对象的定义语句时初始化 ，并直到程序终止才被销毁。在此期间即使对象所在的函数结束执行也不会对它有影响。

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

1. **如果局部静态变量没有显示初始值，他将执行值初始化，内置类型的局部静态变量初始化为 0**。

1. **与变量类似，函数只能定义一次，但可以声明多次，唯一的例外是如果一个函数永远也不会被我们用到，那么它可以只有声明没有定义**。

1. 函数声明（也称函数原型 function prototype）无须函数体，用一个分号代替即可，同时也无须形参的名字。然而写上形参的名字可以帮助使用者更好的理解函数的功能。

   ```c++
   // 函数声明加上名字beg和end使我们更好地理解函数的功能
   void print(vector<int>::const_iterator beg,
               vector<int>::const_iterator end);
   ```

1. **函数也应该在头文件中声明，在原文件中定义。把函数放在头文件中声明，就能确保同一函数的所有声明保持一致，而且一旦我们想改变函数的接口，只需改变一条声明即可。含有函数声明的头文件，应当被包含到含有函数定义的源文件中。**

## 6.2 参数传递

1. 形参的类型决定了形参和实参交互的方式。如果形参是引用类型，他将被绑定到对应的实参上（引用传递 passed by reference），否则，将实参的值拷贝给形参（值传递 passed by value）。

1. 对于指针形参，当执行指针拷贝操作时，拷贝的是指针的值，拷贝之后，两个指针是不同的指针。下面的代码中，**指针形参可以改变实参的值，但无法改变实参的地址**。

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

1. 通过使用引用形参，允许函数改变一个或多个实参的值。引用形参绑定初始化它的对象，**改变引用形参也就是改变其引用对象的值**。

1. **尽量使用引用形参而避免拷贝**，因为拷贝某些大的类类型对象或者容器对象比较低效，甚至有的类类型（包括 IO）就不支持拷贝操作。此时我们也只能使用引用形参。

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

1. 当实参初始化形参时会**忽略掉形参的顶层 const**，也就是说当形参有顶层 const 时，传给他常量对象或非常量对象都是可以的。

1. 因为顶层 const 被忽略掉，**所以对于相同名字的函数，形参表中的 const 不能区分这些函数，导致重复定义（而非函数重载）**。

   ```c++
   void func(int i);
   void func(const int i); // 重复定义
   ```

1. 把函数不会改变的形参定义成普通引用是一种比较常见的错误，这么做带给函数调用者一种误导，即函数可以修改他的实参的值。此外，使用一般引用而非常量引用也会极大地限制函数所能接受的实参类型。例如，我们不能把 const 对象、字面值或者需要类型转换的对象，传递给普通的引用形参。

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
       find(s); // 出错，find无法处理s，
                // 此时可以重新定义一个s的一般拷贝来处理
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

1. argv 的第一个元素指向程序的名字，或者一个空字符串，接下来的元素依次为传递命令行提供的实参，最后一个指针之后的元素保证为 0。

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

1. return 语句返回值的类型必须与函数的返回类型相同，**或者能隐式地转换成函数的返回类型**。

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

1. 函数的返回类型决定函数调用是否是左值。**调用一个返回引用的函数得到左值**，其他类型则得到右值。可以像使用其他左值那样来使用返回引用的函数的调用。**如果返回类型是常量引用，我们不能给调用的结果赋值**。

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

   2. 声明一个返回数组指针的函数( _Type (\*function(parameter_list)) [dimention]_ )：

      ```c++
      int (*func(int i))[10];
      ```

      上述代码的解释含义：

      1. func(int i)表示调用 func 函数时需要一个 int 类型的实参
      2. (\*func(int i))意味着我们可以对函数调用的结果执行解引用操作
      3. (\*func(int i))[10]表示解引用 func 的调用将得到一个大小是 10 的数组
      4. int (\*func(int i))[10]表示数组中的元素是 int 类型的

   3. 使用尾置返回类型：

      ```c++
      // func接受一个int类型的实参，返回一个指针，该指针指向含有10个整数的数组
      auto func(int i) -> int(*)[10];
      ```

   4. 使用 decltype

      ```c++
      int odd[] = {1, 3, 5, 7, 9};
      int even[] = {2, 4, 6, 8, 10};

      // arrPtr返回一个指针，并且类型和odd一致
      decltype(odd) *arrPtr(int i){
          return (i % 2) ? &odd : &even; // 返回一个指向数组的指针
      }
      // decltype简洁，尽量使用decltype
      ```

## 6.4 函数重载

1. 如果同一作用域内的几个函数名字相同但形参列表不同，我们称之为重载函数（overload）。这些函数接收的形参类型不同，但执行的操作非常类似。当调用这些函数时，编译器会根据传递的参数类型推断想要绑定的是哪个函数。

1. main 函数不能重载。

1. **不允许两个函数除了返回类型外其他所有的要素都相同**，假设有两个函数，它们的形参列表一样但是返回类型不同，则第二个函数的声明是错误的。

   ```c++
   Record lookup(const Account&);
   bool lookup(const Account&); // 错误，与上一个函数除了返回类型以外相同

   Record lookup(const Account&);
   Record lookup(const Account& var); //错误，只是多了形参名

   typedef Phone Telno;
   Record lookup(const Phone&);
   Record loopup(const Telno&); // Telno和Phone的类型相同
   ```

### 6.4.1 重载和 const 形参

1. **顶层 const 不影响传入函数的对象。一个拥有顶层 const 的形参无法和另一个没有顶层 const 的形参区分开来。**

   ```c++
   Record lookup(Account);
   Record lookup(const Account); // 重复声明
   Record lookup(Account* p);
   Record lookup(Account* const p); // 重复声明
   ```

2. 如果形参是某种类型的指针或者引用，则通过区分其指向的是常量对象还是非常量对象可以实现函数重载。**底层 const 可以区分函数重载。**

   ```c++
   Record lookup(Account &);
   Record lookup(const Account &); // 新函数
   Record lookup(Account* p);
   Record lookup(const Account* p); // 新函数
   ```

3. 底层 const 可以区分的原因：

   - const 不能转换成其他类型，所以我们只能把 const 对象或指向 const 的指针传递给 const 形参。
   - 因为非常量可以转换成 const，所以函数都能作用于非常量对象或者指向非常量对象的指针。
   - 但是，当我们传递一个非常量对象或者指向非常量对象的指针时，编译器会优先选择非常量版本的函数。

4. 使用 const_cast 可以使得某些非常量转换成常量来进行函数调用时的传参操作。

   ```c++
   const string &shorterString(const string &s1, const string &s2){
       return s1.size() < s2.size() ? s1 : s2;
   }

   string &shorterString(string &s1, string &s2){
       auto &r = shorterString(const_cast<const string &>(s1), const_cast<const string &>(s2));
       return const_cast<string>(r);
   }
   ```

5. 函数匹配（function matching）是指一个过程，在这个过程中我们把函数调用与一组重载函数中的某一个关联起来，函数匹配也叫重载确定（overload resolution）。编译器首先将调用的实参与重载集合中每一个函数的形参进行比较，然后根据比较的结果决定到底调用哪个函数。

6. 调用重载函数时有三种可能的结果：

   - 编译器找到一个与实参最佳匹配的函数，并生成调用该函数的代码。
   - 找不到任何一个函数与调用的实参匹配，此时编译器发出无匹配的错误信息。
   - 有多于一个函数可以匹配，但是每一个都不是明显的最佳选择。此时也将发生错误，称为二义性调用（ambiguous call）

7. 如果我们在内层作用域声明名字，它将隐藏外层作用域中声明的同名实体。在不同的作用域中无法重载函数名。

   ```c++
   string read();
   void print(const string &);
   void print(double);
   void foobar(int ival);{
       bool read = false; // 新作用域：隐藏外层的read
       string s = read(); // 错误：read是一个布尔值，而非函数
       // 在局部作用域中声明函数是一个不好的选择。
       void print(int); // 新作用域，隐藏外层print函数
       print("Value: "); // 错误，外层print被隐藏掉了
       print(ival); // 正确，调用的是print(int)
       print(3.14); //正确，调用的是print(int)
   }
   ```

8. 当我们把上述代码中函数体里的 print(int)放到外层是就会发生 print 函数重载。

## 6.5 特殊用途语言特性

### 6.5.1 默认实参

1. 某些函数有这样一种形参，在函数的很多次调用中它们都被赋予了一个相同的值，此时我们把这个反复出现的值称为默认实参(default argument)。调用含有默认实参的函数时，可以包含该实参，也可以省略该实参。

   ```c++
   typedef string::size_type sz;
   string screen(sz ht = 24, sz wid = 80, char backgrnd = ' ')'
   // 当我们使用screen方法时，我们只需忽略前面实参就可以了。

   string window;
   window = screen(); //等价于screen(24, 80, ' ')
   window = screen(66); // 等价于screen(66, 80, ' ')
   window = screen(66, 256); // 等价于screen(66, 256, ' ')
   window = screen(66, 256, '#'); // 等价于screen(66, 256, '#')

   window = screen(, , '?'); // 错误
   window = screen('?'); // 实际是调用screen('?', 80, ' ')
   ```

2. **注意，一旦某个形参被赋予了默认值，它后面的所有形参都必须有默认值。所以上述代码中如果一定要为 backgrnd 覆盖默认值，则必须为 ht 和 wid 提供实参。所以当设计含有默认实参的函数时，尽量让不怎么使用默认值的形参出现在前面，让那些经常使用默认值的形参出现在后面。**

3. **在给定的作用域中，一个形参只能被赋值一次默认实参。在函数的多次声明中，函数的后续声明只能为之前那些没有默认值的形参添加默认实参，而且该形参右侧的所有形参必须都有默认值。**

   ```c++
   string screen(sz, sz, char = ' '); // 初次声明
   // 错误，char已经被赋值了一次默认实参，不能重复声明
   string screen(sz, sz, char = '*');
   // 正确，为之前没有添加默认实参的形参添加默认实参
   string screen(sz = 24, sz = 80, char);
   ```

4. 局部变量不能作为默认实参。同时，只要表达式的类型能转换成形参所需的的类型，该表达式就能作为默认实参。

   ```c++
   // ht、wd、def的声明必须出现在函数之外
   // ht的返回值必须类型了sz相同
   string screen(sz = ht(), sz = wd, char = def);
   ```

### 6.5.2 内联函数和 constexpr 函数

1. 函数调用一般比求等价表达式的值要慢一些，一次函数调用包含着一系列工作，需要耗费资源和时间。

1. 将函数定义成内联函数(inline)，函数在编译过程中将直接展开从而消除函数的运行开销。

   ```c++
   inline const string &shortString(const string &s1, const string &s2){
       return s1.size() < s2.size() ? s1 : s2;
   }

   cout << shortStirng(s1, s2) << endl;
   // 如果将shortString()定义成inline,函数将展开成如下形式
   cout << (s1.size() < s2.size() ? s1 : s2) << endl;
   ```

1. **内联说明只是向编译器发出的一个请求，编译器可以选择忽略这个请求，所以内联机制一般只用于优化规模较小、流程直接、频繁调用的函数**。很多编译器都不支持内联递归函数，而且一个 75 行的函数也不大可能在调用点内联地展开。

1. **constexpr 函数是指能用于常量表达式的函数。函数的返回类型及所有形参的类型都得是字面值类型，而且函数体中必须只有一条 return 语句。**

   ```c++
   constexpr int new_sz(){ return 42; }
   constexpr int foo = new_sz(); // 正确，foo是一个常量表达式
   ```

1. **编译器把 constexpr 函数的调用替换成其结果值，为了能在编译过程中随时展开，constexpr 函数被隐式的定义成内联函数。**

1. **constexpr 函数体内也可以包含其他语句，只要这些语句在运行时不执行任何操作就行，例如空语句、类型别名或者 using 声明。constexpr 函数的返回值可以不是一个常量（或常量表达式）。**

   ```c++
   constexpr size_t scale(size_t cnt){
       return new_sz() * cnt;
   }

   int arr[scale(2)]; // 正确，scale(2)是常量表达式
   int i = 2;
   int a2[scale(i)]; // 错误，scale(i)不是常量表达式
   ```

1. 内联函数或 constexpr 函数可以多次定义。对于某个给定的内联函数或者 constexpr 函数来说，它的多个定义必须完全一致，基于这个原因，内联函数和 constexpr 函数通常定义在头文件中。

1. 两种具有调试帮助的预处理功能，assert 和 NDEBUG：

   - assert 是一种预处理宏(preprocessor marco)。其实就是一个预处理变量，行为类似内联函数，表达式为 assert(_expr_),如果表达式为假，assert 输出信息并终止程序的执行。如果为真，则 assert 什么也不做。使用 assert 时不需要提供 using 声明。宏名字在程序内必须唯一，含有 cassert 头文件的程序不能定义 assert 变量。（即便没包含也最好不要定义该变量）assert 应该仅用于验证那些确实不可能发生的事，我们不能用它代替真正的运行时逻辑检查，也不能替代程序本身应该包含的错误检查。
   - NDEBUG 是一种预处理变量的状态，如果定义了 NDEBUG，则 assert 什么也不做，默认状态下是没有定义 NDEBUG，此时 assert 将执行运行时检查。我们可以使用#define 来定义 NDEBUG 从而关闭调试状态。我们也可以使用如下的命令行来定义 DEBUG 从而关闭调试。我们也可以利用 NDEBUG 自定义条件调试代码：

     ```c++
     command line: $ CC -D NDEBUG main.C #在命令行定义了NDEBUG来跳过调试

     // _ _func_ _是编译器定义的一个局部静态变量，用于存放函数的名字
     void print(const int ia[], size_t size){
         #ifndef NDEBUG
             cerr << _ _func_ _ << ":array size is" << size << endl;
         #endif
     }
     ```

1. 用于程序调试的名字：

   | 名称               | 作用                           |
   | ------------------ | ------------------------------ |
   | \_ \_ _FILE_ \_ \_ | 存放文件名的字符串字面值       |
   | \_ \_ _LINE_ \_ \_ | 存放当前行号的整型字面值       |
   | \_ \_ _TIME_ \_ \_ | 存放文件编译时间的字符串字面值 |
   | \_ \_ _DATE_ \_ \_ | 存放文件编译日期的字符串字面值 |

## 6.6 函数匹配

1. 函数匹配的第一步是选定本次调用对应的重载函数集，集合中的函数称为候选函数(candidate function)。候选函数具备两个特征，一是与被调用的函数同名，二是其声明在调用点可见。

   ```c++
   void f();
   void f(int);
   void f(int, int);
   void f(double, double = 3.14);
   f(2.5); // 实际调用f(double, double)
   f(40, 2.5); // 二义性调用，错误。
   ```

1. 第二步考察本次调用提供的实参，然后从候选函数中选出能被这组实参调用的函数，这些新选出的函数称为可行函数(viable function)。可行函数的两个特征：一是其形参数量与本次调用提供的实参数量相等，二是每个实参的类型与对应的形参类型相同，或者能转换成形参的类型。

1. 如果没找到可行函数，编译器将报告无匹配函数的错误。

1. 函数匹配第三步是从可行函数中选择与本次调用最匹配的函数。在这一过程中，逐一检查函数调用提供的实参，寻找形参类型与实参类型最匹配的那个可行函数。基本思想是，实参类型和形参类型越接近，他们就匹配的越好。

1. 代码中 f(40, 2.5)的调用符合 f(int,int)和 f(double,double)，然而两者实际都需要一次强制类型转换，也就是说该调用具有二义性，从整体上编译器无法判断优劣，此时编译器会报错。

1. **调用重载函数时应尽量避免强制类型转换。如果在实际应用中确实需要强制类型转换，则说明我们设计的形参集合不合理。**

1. 编译器对实参类型到形参类型的转换划分成几个等级：

   1. 精确匹配
      - 实参类型和形参类型相同
      - 实参从数组类型或函数类型转换成对应的指针类型（通常为自动转换）
      - 向实参添加顶层 const 或者从实参中删除顶层 const
   1. 通过 const 转换实现的匹配
   1. 通过类型提升实现的匹配(char转int)
   1. 通过算术类型转换或指针转换实现的匹配
   1. 通过类类型转换实现的匹配（14 章介绍）

1. 当有两个函数一个接受 int 一个接受 short，则当且仅当调用提供的是 short 类型的值时才会调用 short 版本的函数。大部分情况下小整型都会被提升为 int 型（char或者short都会先转成int）。

   ```c++
   void ff(int);
   void ff(short);
   ff('a'); // char提升为int型

   void manp(long);
   void manp(float);

   manip(3.14); // double既能转换成long又能转换成float，二义性调用，错误
   ```

1. 所有算术类型转换的级别都一样，int 向 unsigned int 转换并不比 int 向 double 的转换级别高。如上述代码中 double 转换成 float 或者 long 都可，并无级别高低的区别，因此产生二义性错误。

1. 如果重载函数的区别在于它们的引用类型的形参是否引用了 const，或者指针类型的形参是否指向 const，那么当调用发生时编译器通过实参是否是常量来决定选用哪个函数：

    ```c++
        Record lookup(Account &);
        Record lookup(const Account &);
        const Account a;
        Account b;

        lookup(a); // 调用lookup(const Account &)
        lookup(b); // 调用lookup(Account &)
        // 对于lookup(b)调用，其实上面两个函数都可以
        // 但是由于精确匹配的原则，实际调用的是无需类型转换的第一个函数
    ```

## 6.7 函数指针

1. 函数指针指向的是函数而非对象。和其他指针一样，函数指针指向某种个特定类型。函数的类型由它的返回类型和形参类型共同决定，与函数名无关。

    ```c++
    bool lengthCompare(const string &, const string &);
    // 指向一个函数的指针，pf两侧的括号不能少，否则变成返回bool指针的函数
    bool (*pf)(const string &, const string &);
    ```

1. 当我们把函数名作为一个值使用时，该函数自动转换成指针。

    ```c++
    pf = lengthCompare; // pf指向名为lengthCompare的指针
    pf = &lengthCompare; // 等价赋值语句
    ```

1. 我们可以直接使用指向函数的指针调用该函数，无需再做解引用。

    ```c++
    bool b1 = pf("Hello", "good"); // 直接调用lengthCompare函数
    bool b1 = (*pf)("Hello", "good"); // 等价调用，实际可以省略解引用操作
    bool b1 = lengthCompare("Hello", "good"); //等价语句
    ```

1. 我们可以为函数指针赋值一个0或者nullptr来表示该指针没有指向任何函数。

1. 重载函数的指针，其类型必须与多个重载函数中的某一个精确匹配。

    ```c++
    void ff(int *);
    void ff(unsigned int);

    void (*pf1)(unsigned int) = ff; // pf1指向ff(unsigned int)
    void (*pf2)(int) = ff; // 错误，无ff可与此指针匹配
    double (*pf1)(unsigned int) = ff; // 错误，返回类型不同
    ```

1. **函数类型不可作为形参，但是我们可以使用函数指针来作为形参。此时形参看起来像是函数类型，但实际上是函数指针。**

    ```c++
    // 第三个参数是函数类型，但它会被自动转换成函数指针
    void useBigger(const string &s, const string &s2,
                        bool pf(const string &, const string &));
    // 等价声明，显示的定义函数指针
    void useBigger(const string &s, const string &s2,
                        bool (*pf)(const string &, const string &));

    // 实际调用时，可以直接传递一个函数名，它会自动被转换成函数指针
    useBigger(s1, s2, lengthCompare);
    ```

1. 直接使用函数指针类型显得冗长而繁琐。类型别名和decltype能让我们简化使用函数指针的代码。

    ```c++
    // Func和Func2都是函数类型
    typedef bool Func(const string&, const string&);
    typedef decltype(lengthCompare) Func2;  //等价的类型

    // FuncP和FuncP2都是函数指针类型
    typedef bool (*FuncP)(const string&, const string&);
    typedef decltype(lengthCompare) *FuncP2;  //等价的类型
    // 注意，此处decltype不会自动把lengthCompare转换成指针类型，
    // 所以需要加上*来显示说明FuncP2是指针类型
    ```

1. 使用类型别名重新声明函数指针的形参将会变得十分简洁：

    ```c++
    // 第三个参数是函数类型，但它会被自动转换成函数指针
    void useBigger(const string &s, const string &s2, Func);
    // 等价声明，此时第三个参数是函数指针
    void useBigger(const string &s, const string &s2, FuncP2);
    ```

1. 函数不能作为一个返回值，但是我们可以返回指向函数类型的指针。书写返回函数指针的函数时返回类型的声明将会十分冗长，最简单的方法仍然是使用类型别名。

    ```c++
    using F = int(int*, int); // F是函数类型
    using PF = int (*)(int*, int); // PF是函数指针类型
    ```

1. **和函数类型的形参不同，返回类型为函数类型时不会自动转换成函数指针类型，所以我们必须显示的将返回类型定义成指针。**

    ```c++
    PF f1(int); // 正确，返回类型为函数指针

    F f1(int); // 错误，F是函数类型，f1不能返回一个函数类型
    F *f1(int); // 正确，F *是函数指针类型

    // 我们也可以直接声明f1的返回值为函数指针
    // 由内而外阅读，f1(int)是函数体，前面有*则是返回一个指针
    // 该指针也有形参列表，为（*int，int），该函数返回类型为int
    int (*f1(int))(int*, int);

    // 尾置返回类型
    auto f1(int) -> int(*)(int*, int);
    ```

1. 当我们明确知道要返回的函数是哪一个时，就能使用decltype简化书写函数指针返回类型的过程。**但是注意，decltype只能返回函数类型而非函数指针类型，因此我们需要显示的加上*以表明我们需要返回的是函数指针。**

    ```c++
    string::size_type sumLength(const string&, const string&);
    string::size_type largeLength(const string&, const string&);
    // getFcn函数可以返回指向上面两个函数中任意一个的指针
    decltype(sumLength) *getFcn(const string &);
    ```

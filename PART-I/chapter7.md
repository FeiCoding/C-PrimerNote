# chapter 7 类

## 7.1 定义抽象数据类型

### 7.1.1 类的概念

1. 类的基本思想是数据抽象（data abstraction）和封装（encapsulation）。数据抽象是一种依赖于接口（interface）和实现（implementation）分离的编程技术。类的接口包括用户所能执行的操作，类的实现则包括类的数据成员、负责接口实现的函数体以及定义类所需的各种私有函数。

1. 封装实现了类的接口和实现的分离。封装后的类隐藏了它的实现细节，也就是说，类的用户只能使用接口而无法访问实现部分。

1. 类要想实现数据抽象和封装，需要首先定义一个抽象数据类型（abstract data type）。在抽象数据类型中，由类的设计者负责考虑类的实现过程，使用该类的程序员则只需要抽象的思考类型做了什么，而无需了解类型的工作细节。

### 7.1.2 类的成员函数

1. 定义和声明成员函数的方式与普通函数差不多。成员函数的声明必须在类的内部，它的定义则既可以在类的内部也可以在类的外部。作为接口组成部分的非成员函数，他们的定义和声明都在类的外部。

1. 定义在类的内部的函数是隐式的inline函数。

### 7.1.3 this关键字

1. 成员函数可以通过this这样一个额外的隐式参数来访问调用它的那个对象。当我们用一个成员函数时，用请求该函数的对象地址初始化this。例如当我们调用total.isbn()，则编译器负责把total的地址传给isbn的隐式形参this，可以等价的认为编译器将该调用重写成了Sales_data::isbn(&total)。其中，调用sales_data的isbn成员时传入了total的地址。

1. 实际上在成员函数内部我们可以直接使用该函数的对象的成员而无需通过成员访问运算符来做到这一点，因为this所指的正是这个对象。

1. 任何对类成员的直接访问都被看做this的隐式引用，也就是说，当isbn使用bookNo时，它隐式的使用this指向的成员，就像我们书写this->bookNo一样。

1. **任何自定义名为this的参数或变量的行为都是非法的。this的目的总是指向“这个”对象，所以this是一个常量指针（*const），我们不允许改变this中保存的地址。**

### 7.1.3 const成员函数

1. 紧随参数列表之后的const关键字，作用是修改隐式this指针的类型，将this变为指向const的指针（而且this自身还是一个常量指针，所以此时this就是指向常量的常量指针）。

    ```c++
    std::string isbn() const { 
        return bookNo;
    }
    ```

1. 常量对象不可以被一个非指向常量的指针绑定。所以当我们想要让this指针既能指向常量对象，又能指向非常量对象，我们就应该将其声明成一个指向常量的指针，但是this是一个隐式声明的指针，此时C++允许我们在函数的参数列表后面加上const来把this声明成一个指向const的指针，同时也表明了isbn这个函数的内部无法改变对象的值。

1. 像上述这样声明的const的成员函数被称作常量成员函数（const member function）

1. **常量对象，以及常量对象的引用或指针只能调用常量成员函数**。

1. 由于编译器分两步处理类：先编译成员的声明，然后才轮到成员函数体。因此成员函数体可以随意使用类中的其他成员而无须在意这些成员出现的次序。（上述代码中，即便先定义函数isbn再定义变量bookNo依然可以编译。）

1. 当我们在类的外部定义成员函数时，成员函数的定义必须与他的声明匹配。也就是说，返回的类型、参数列表和函数名都得与类内部的声明保持一致。如果成员函数被声明成常量成员函数，那么他的定义也必须在参数列表后明确指定const属性。

    ```c++
    double Sales_data::avg_price() const{
        if(units_sold)
            return revenue/units_sold;
        else
            return 0;
    }
    ```

### 7.1.3 自定义IO成员函数

1. 一般来说，当我们定义的函数类似于某个内置运算符时，应该令该函数的行为尽量模仿这个运算符。内置的运算符把它的左侧运算对象当成左值返回，因此当我们模仿此类函数时也应当返回一个引用类型（只有返回引用类型时才是左值）。

    ```c++
    Sales_data& Sales_data::combine(const Sales_data &rhs){
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
        return *this; // 解引用this返回调用该函数的对象
    }
    ```

1. 类的作者常常需要定义一些辅助函数，比如add、read和print等。尽管这些函数定义的操作从概念上来说属于类的接口的组成部分，但他们实际上并不属于类本身。

1. 如果函数在概念上属于类但是不定义在类中，则一般他们应与类声明（而非定义）在同一个头文件中。

1. 如果非成员函数是类接口的组成部分，则这些函数的声明应该与类在同一头文件内。

1. 下面代码定义了read和print函数，比较重要的一点是，read和print分别接收一个来自IO类型的引用作为其参数，这是因为**IO类属于不能被拷贝的类型**，因此我们只能通过引用来传递他们。而且因为**读取和写入的操作会改变数据流中的内容，所以两个函数接收的都是普通引用，而非对常量的引用**。

    ```c++
    istream &read(istream &is, Sales_data &item){
        double price = 0;
        is >> item.bookNo >> item.units_sold >> price;
        item.revenue = price * item.units_sold;
        return is;
    }

    //将Sales_data对象定义成const，原因是无须改变对象的内容
    ostream &print(ostream &os, const Sales_data &item){
        os << item.isin() << " " << item.units_sold << " "
            << item.revenue << " " << item.avg_price();

        return  os;
    }
    ```

1. 此处的print函数一般不负责换行，**一般来说，执行输出任务的函数应尽量减少对格式的控制，这样可以确保由用户代码来决定是否换行**。

### 7.1.4 构造函数

1. 构造函数（constructor）的任务是初始化类对象的数据成员，无论何时只要类的对象被创建，就会执行构造函数。

1. **构造函数的名字和类相同，没有返回类型**。类可以包含多个构造函数，但是每个构造函数必须在参数数量或参数类型上有所区别。构造函数不能被声明成const。**构造函数在const对象的构造过程中可以向其写值。**

1. 类通过一个特殊的构造函数来控制默认初始化过程，这个函数叫默认构造函数（default constructor）。默认构造函数无须任何实参。

1. 编译器创建的构造函数又被称为合成的默认构造函数（synthesized default constructor）。该构造函数将按如下规则初始化类的数据成员：
    - 如果存在类内初始值，用它来初始化成员。
    - 否则，默认初始化该成员。

1. 只有当类没有声明任何构造函数时编译器才会默认生成构造函数。**一旦我们定义了其他构造函数，那么除非我们再定义一个默认的构造函数，否则类将没有默认构造函数**。

1. **如果定义在块中的内置类型或复合类型（数组、指针等）的对象被编译器默认初始化将出现未定义的值。所以当我们使用内置类型或复合类型成员的类，应该在类的内部初始化这些成员，或者定义一个自己的默认构造函数**。

1. 如果类中包含了其他的类类型的成员且这个成员的类型没有默认构造函数，那么编译器将无法初始化该成员。对于这样的类来说，我们必须自定义默认构造函数，否则该类将没有可用的默认构造函数。

1. 定义默认构造函数，我们可以使用C++11新标准中，通过在参数列表后面写上=default来要求编译器生成构造函数。=default既可以声明在类内部（那么就是内联的），也可以声明在类外部（非内联）。

    ```c++
    Sales_data() = default;
    ```

1. 构造函数初始值列表（constructor initialize list），他负责为新创建的对象的一个或几个数据成员赋初始值。构造函数初始值是成员名字的一个列表，每个名字后面紧跟括号起来的（或者在花括号内的）成员初始值。不同成员的初始化通过逗号分隔开来。

    ```c++
    Sales_data(const std::string &s):bookNo(s){ }
    Sales_data(const std::string &s, unsigned n, double p):
        bookNo(s),units_sold(n), revenue(p*n){ }
    ```

1. 当某个数据成员被构造函数初始值列表忽略时，他将以与合成默认构造函数相同的方式隐式初始化。此时我们可以将其进行类内初始值初始化(在类中直接用一个值声明定义变量)，因此只接受一个string参数的构造函数等价于下列代码：

    ```c++
    Sales_data(const std::string &s):
        bookNo(s), units_sold(0), revenue(0){ }
    ```

1. 构造函数不应轻易覆盖掉类内初始值，除非新赋的值与原值不同。如果不能使用类内初始值，则所有构造函数都应该显式的初始化每个内置类型的成员。

### 7.1.5 拷贝、赋值和析构

1. 如果我们不定义拷贝、赋值和析构，编译器将自动帮我们生成，一般来说编译器生成的版本将对对象的每个成员进行直接拷贝、赋值和销毁。然而，对于某些类来说，例如当类需要分配类的对象之外的资源时（使用new），合成的版本将会失效。

1. 很多需要动态内存的类，能而且应该使用vector对象或者string对象管理必要的存储空间。使用vector或者string的类能避免分配和释放内存带来的复杂性。原因在于当我们对含有vector成员的对象执行拷贝或赋值操作时，vector类会设法拷贝或者赋值成员中的元素。当这样的对象被销毁时，将销毁vector对象，也就是依次销毁vector中的每一个元素。（string也是如此）

## 7.2 访问能控制与封装

### 7.2.1 访问说明符

1. 我们使用访问说明符（access specifiers）加强类的封装性：
    - 定义在public说明符之后的成员在整个程序内可被访问，public成员定义类的接口
    - 定义在private说明符之后的成员可以被类的成员函数访问，但是不能被使用该类的代码访问，private部分封装了（即隐藏了）类的实现细节。

1. 对于一个类可以出现0或多个访问说明符，对于某个访问限定符能出现多少次没有严格的规定，每个访问说明符制定了接下来的成员的访问级别，其有效范围直到出现下一个访问说明符或者到达类的结尾为止。

1. **struct和class的唯一区别是他们的默认访问权限不一样。如果我们使用struct，则默认访问符是public，而class则是private**。我们希望定义的类的所有成员是public的时候使用struct，反之则使用class。

### 7.2.2 友元

1. 类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的友元（friend），此时只需要添加一条以friend关键字开始的函数声明即可。

1. 友元声明只能出现在类定义的内部，但是在类内出现的具体位置不限，**一般来说我们需要在类的定义开始或结束前的位置集中声明友元**，友元不是类的成员也**不受它所在区域访问控制级别的约束**。

1. 封装的益处：
   - 确保用户代码不会无意间破坏封装对象的状态
   - 封装的类的具体实现细节可以随时改变，而无须调整用户级别的代码。

1. **友元的声明仅仅是指定了访问权限，我们仍然必须在友元之外再专门对函数进行一次声明**。为了使友元对类的用户可见，我们通常把友元的声明与类本身放置在同一个头文件中（类的外部）。

1. 大部分编译器不会强制限定友元函数必须在使用之前在类的外部声明。

## 7.3 类的其他特性

1. 定义一个Screen类：

    ```c++
    using namepsace std;
    class Screen{
        public:
            using pos = string::size_type;
            Screen() = default;
            Screen(pos ht, pos wi, char c):height(hi),width(wi),
            contents(hi*wi, c){ }
            char get() const{ // 隐式指定inline
                return content;
            }
            inline char get(pos ht, pos wd) const; // 显式指定inline
            Screen &move(pos r, pos c); // 可以在之后设置为内联函数

        private:
            pos height = 0, width = 0;
            pos cursor = 0;
            string contents;
    };

    // 也可以在函数的定义处指定inline
    inline Screen &Screen::move(pos r, pos c){
        pos row = r * width; // 计算行的位置
        cursor = row + c; // 在行内将光标移动到指定的列
        return *this; // 以左值形式返回对象
    }
    char Screen::get(pos ht, pos wd) const{
        pos row = r * width; // 计算行的位置
        return contents[row + c]; // 返回给定列的字符
    }
    ```

1. 我们无需在声明和定义的地方同时说明inline，虽然这么做合法。**不过最好只在类外部定义的地方说明inline，这样可以使类更容易理解。**

1. 成员函数之间也可以重载，只要函数之间在参数的数量或类型上有区别即可。例如上述代码中的get函数，一个版本返回光标当前位置的字符，另一个版本返回由行号和列号确定的位置的字符。编译器根据实参的数量来决定运行哪个版本的函数。

    ```c++
    Screen myscreen;
    char ch = myscreen.get(); // 调用Screen::get()
    ch = myscreen.get(0,0);   // 调用Screen::get(pos, pos)
    ```

1. **当我们享有修改类的某个成员，即使是在一个const成员函数内，此时可以使用mutable关键字来声明该变量。一个可变数据成员（mutable data member）永远不会是const，即使他是const对象的成员**。我们可以为上述代码加入一个access_ctr的可变成员来追踪每个Screen成员函数被调用了多少次：

    ```c++
    class Screen{
        public:
            void some_member() const;
        private:
            mutable size_t access_ctr; //即使在一个const对象内也可以被修改
    };

    void Screen::some_member() const{
        ++access_ctr; // 即便some_member是一个const成员函数，
                      // 它仍然能改变access_ctr的值
    }
    ```

1. 当我们提供类内初始值时，必须使用符号“=”或者花括号表示。

    ```c++
    // 我们定义了一个窗口管理类并用它表示显示器上的一组Screen
    using namespace std;
    class Window_mgr{
        private:
            vector<Screen> screens{Screen(24, 80, ' ')}; //使用花括号进行类内初始化
    };
    ```

1. 下面代码中我们添加了两个新的成员函数set，负责设置光标所在位置的字符或者其他任意给定未知的字符：

    ```c++
    class Screen{
        public:
            Screen &set(char);
            Screen &set(pos, pos, char);
    };

    inline Screen &Screen::set(char c){
        contents[cursor] = c; // 设置给定未知的新值
        return *this;
    }

    inline Screen &Screen::set(pos r, pos col, char ch){
        contents[r*width + col] = ch; // 设置给定未知的新值
        return *this;
    }
    ```

    上述代码中，我们的set成员的返回值是调用set的对象的引用。返回引用的函数是左值的，意味着这些函数返回的是对象本身而非对象的副本，于是我们可以把一系列这样的操作连接在一条表达式中的话：

    ```c++
    myScreen.move(4, 0).set('#');
    // 等价于下面
    myScreen.move(4, 0);
    myScreen.set('#');
    ```

    如果上述代码中返回的时Screen而不是Screen&，那么则等价于：

    ```c++
    Screen temp = myScreen.move(4, 0); // 对返回值进行拷贝
    temp.set('#'); // 不会改变myScreen的contents
    ```

    于是此时move的返回值将是\*this的拷贝，因此调用set只能改变临时副本，而不能改变myScreen的值。

1. 在上述代码逻辑之后我们想再加入一个display函数用于打印Screen的内容，同时可以向set和move一样出现在同一序列中，那么此时就会出现问题，**display不会改变打印的值，于是我们希望将display设置为返回值为const Screen&的函数**，然而如果这样做了，在同一序列中，display后面就不能再跟set函数来改变对象的值了。对于这个问题，我们可以设置一个基于const的重载函数。

    ```c++
    class Screen{
        public:
            // 根据对象是否是const重载了display函数
            Screen &display(std::ostream &os){
                do_display(os);
                return *this;
            }
            const Screen &display(std::ostream &os){
                do_display(os);
                return *this;
            }

        private:
            // 这个函数将用于显示Screen的内容
            void do_display(ostream &os) const{
                os << contents;
            }
    };
    ```

1. 上述重载函数中，this指针在其中隐式的传递，**当display调用do_display时，它的this指针隐式地传递给do_display，而当display的非常量版本调用do_display时，它的this指针将隐式地从指向非常量的指针转换成指向常量的指针**。当do_display完成后，display函数各自返回解引用this所得的对象。在非常量版本中，this指向一个非常量对象，因此display返回一个普通的（非常量）引用，而const成员则返回一个常量引用。所以当我们再某个对象上调用display时，该对象是否是const决定了应该调用display的哪个版本。

1. 上述代码中我们使用了do_display这样一个函数，目的在于
   - 避免在多处使用同样的代码
   - 预期随着类的发展，display函数有可能变得更加复杂，此时把相应的操作写在一处而非两处的作用会更清晰
   - 我们在开发过程中可能会为do_display添加一些调试信息，而这些信息将在代码的最终产品版本中去掉。此时删除将更加容易
   - 因为我们把do_display定义在了类的内部，所以其实该类的调用并没有带来额外的开销。

1. **每个类定义了唯一的类型，即便两个类的所有成员都一样，这两个类也是两个不同的类型**。

1. 我们可以把类名作为类型的名字使用，从而直接指向类类型。或者，我们也可以把类名跟在class或struct后面：

    ```c++
    Sales_data item1;
    class Sales_data item1; // 一条等价的声明,从C继承而来
    ```

1. **我们可以仅仅声明一个类而暂时不定义它，此时叫做向前声明（forward declaration），它向程序中引入了类名，并且指明该类名是一种类类型。对于这样的类型来说，在他声明之后、定义之前是一个不完全类型（incomplete type）对于不完全类型，我们可以定义指向这种类型的指针或者引用，也可以声明（但是不能定义）以不完全类型作为参数或返回类型的函数。**

1. **创建对象或通过指针、引用之前，该类必须有定义，而不能仅仅被声明。（原因是如果只声明，编译器将不知道需要分配多少内存）**

1. **一个类的成员类型不能是该类自己**。然而，一旦一个类名出现后，他就被认为是声明过了（但尚未定义），因此**类允许包含指向它自身类型的引用或指针**。

    ```c++
    class Link_Screen{
        Screen window;
        Link_Screen *next;
        Link_Screen *prev;
    };
    ```

1. 类可以把其他的类定义成友元，也**可以把其他类的成员函数定义成友元。如果友元函数定义在类的内部，这样的函数也是隐式内联的。友元关系不存在传递性**。例如我们想在window_mgr类中添加一个方法clear可以清空一个指定的Screen的内容，此时clear需要访问Screen的私有成员content，我们就必须将clear添加为Screen的友元函数。
   - 首先先定义window_mgr类，在其中声明clear函数，但是不能定义它。而在clear使用Screen的成员之前必须先声明Screen
   - 接下来定义Screen，包括对于clear的友元声明
   - 最后定义clear，此时它才可以使用Screen的成员

1. **如果一个类想把一组重载函数声明成友元，那么它需要对这组函数中的每一个都分别声明**。

1. 友元声明的作用是影响访问权限，它本身并非普通意义上的声明。**所以即便我们在类的内部定义该函数，我们也必须在类的外部提供相应的声明从而使得函数可见。**

    ```c++
    struct X{
        friend void f() {  /*友元被定义在类的内部*/ }
        X(){ f(); } // 错误，f还没有被声明
        void g();
        void h();
    };
    void X::g(){return f(); } // 错误，f还没有被声明
    void f(); // 声明定义在X中的f
    void X::h() { return f(); } //正确，f现在已经在作用域中了
    ```

## 7.4 类的作用域

1. 一个类就是一个作用域，因此在类的外部使用类内定义的成员时我们必须加上“类名:: ”来说明作用域。一旦遇到了该类名，那么参数列表和函数体内的其他成员就无须再次授权。而返回类型往往设置在类名之前，此时返回类型就需要我们指定它是哪个类的成员。

1. 一般名字查找过程：
   - 在名字所在的块中寻找，只考虑出现在名字的使用之前出现的声明
   - 如果没找到，继续查找外层作用域
   - 如果最终没找到，报错

1. 编译器处理完类中的全部声明后才会处理成员函数的定义。声明中使用的名字，包括返回类型或参数列表中的名字，都必须在使用前确保可见。如果某个成员的声明使用了类中尚未出现的名字，则编译器将会在定义该类的作用域中继续查找。

    ```c++
    typedef double Money;
    string bal;
    class Account{
        public:
            // Money在类内声明中未发现，将去类外查找
            Money balance() { return bal; } // 此处的bal是下方类内定义的
        private:
            Money bal;
    };
    ```

1. 一般来说，内层作用域可以重新定义外层作用域的名字，即使该名字已经在内层作用域中使用过。然而在类中，**如果成员使用了外层作用域的某个名字，而该名字代表一种类型，则类不能再之后重新定义该名字**：

    ```c++
    typedef double Money;
    string bal;
    class Account{
        private:
            typedef Money; // 错误，不能重新定义Money
            Money bal;
    };
    ```

1. **类型名的定义通常出现在类的开始处，这样就能确保所有使用该类型的成员都出现在类名的定义之后。**

1. 成员函数名字的查找流程：
   - 先在函数体内查找该名字的声明。和前面一样，只有在函数使用之前出现的声明才被考虑。
   - 如果在成员函数内没有找到，则在类内继续查找，此时类的所有成员都可以被考虑。
   - 如果类内也没有找到该名字的声明，则在成员函数定义之前的作用域内继续查找

    ```c++
    int height;
    class Screen{
        public:
            typedef std::string::size_type pos;
            // 如下写法非常不好，推荐不要把成员名字作为参数或其他局部变量使用
            void dummy_fcn(pos height){
                cursor = width * height; //此时使用传入的参数height

                // 通过加上类名或this指针来强制访问类成员
                cursor = width * Screen::height; //成员height
                cursor = width * this->height; //成员height

                // 通过外层作用域的运算符来使用外部定义的height
                cursor = width * ::height; // 外部height

            }
        private:
            pos cursor;
            pos height = 0, width = 0;
    }
    ```

1. 名字查找的第三步不仅要考虑类定义之前的全局作用域的声明，还需要考虑在成员函数定义之前的全局作用域的声明。

    ```c++
    int height;
    class Screen{
        public:
            typedef std::string::size_type pos;
            void setHeight(pos var);
        private:
            pos cursor;
            pos height = 0, width = 0;
    }
    // 定义一个全局函数verify()
    Screen::pos verify(Screen::pos);
    void Screen::setHeight(pos var){
        // var:传入参数
        // height:类的成员height
        // verify:全局函数
        // 此时verify声明在setHeight函数定义之前，所以此时可以使用
        height = verify(var);
    }
    ```

## 7.5 构造函数再探

### 7.5.1 构造函数初始值列表

1. 如果没有在构造函数的初始值列表中显示的初始化成员，则该成员将在构造函数体之前执行默认初始化。

    ```c++
    Sales_data::Sales_data(const string &s, unsigned cnt, double price){
        bookNo = s;
        units_sold = cnt;
        revenue = cnt * price;
    }
    ```

    此段代码和我们之前使用的列表初始化的功能相同，**但是此段代码使用的是赋值操作**。而列表初始化则是直接初始化。

1. 上述初始化过程具有一定的局限性，例如**当我们的成员变量是const或者引用时，此时必须使用列表初始化而不能使用赋值操作**。类似的，**当成员属于某种类类型且该类没有定义默认构造函数时，也必须对该成员进行初始化**。

    ```c++
    class ConstRef{
        public:
            ConstRef(int ii);
        private:
            int i;
            const int ci;
            int &ri;
    }
    ConstRef::ConstRef(int ii){
        i = ii;
        ci = ii; // 错误，ci是const int
        ri = ii; // 错误，ri没有初始化
    }
    // 列表初始化
    ConstRef::ConstRef(int ii):i(ii), ci(ii), ri(ii){ }
    ```

1. **初始化和赋值操作的区别事关底层效率问题，前者直接初始化数据成员，后者则先初始化再赋值**。除此以外，一些数据成员必须被初始化。所以我们应该养成使用构造函数初始值的习惯，这样可以避免意想不到的编译错误。

1. 成员的初始化顺序与他们在类定义中的出现顺序一致，构造函数初始值列表中初始值的顺序不会影响这一初始化顺序。所以**成员初始化顺序最好与成员声明的顺序保持一致**，而且如果可能，**尽量避免使用某些成员初始化其他的成员**，以避免初始化顺序不一致导致未定义的错误。

1. **如果一个构造函数为所有参数都提供了默认实参，则它实际上也定义了默认构造函数**。

### 7.5.2 委托构造函数

1. 一个委托构造函数使用他所属类的其他构造函数执行它自己的初始化过程，或者说把他自己的一些（或者全部）职责委托给了其他构造函数。

    ```c++
    class Sales_data{
        public:
            // 非委托构造函数使用对应的实参初始化成员
            Sales_data(std::string s, unsigned cnt, double price):
            bookNo(s), units_sold(cnt), revenue(cnt*price){ }
            // 其余构造函数全都委托给另上述构造函数
            Sales_data(): Sales_data("", 0, 0) { }
            Sales_data(std::string s): Sales_data(s, 0, 0) { }
            Sales_data(std""istream &is): Sales_data() { read(is, *this); }
    }
    ```

### 7.5.3 默认构造函数

1. 默认初始化在以下情况发生：
   - 当我们在块作用域内不使用任何初始值定义一个非静态变量或者数组时。
   - 当一个类本身含有类类型的成员且使用合成的默认构造函数时。
   - 当类类型的成员没有在构造函数初始值列表中显示地初始化时。

1. 值初始化在以下情况发生：
   - 在数组初始化的过程中如果我们提供的初始值数量少于数组的大小时
   - 当我们不使用初始值定义一个局部静态变量时
   - 当我们通过书写形如 T() 的表达式显示的请求值初始化时，其中T是类型名，她就是使用一个这种形式的实参来对他的元素初始化器进行值初始化

1. 类必须包含一个默认构造函数以便在上述情况下使用。**即便定义了其他构造函数，最好也提供一个默认构造函数**。

1. 使用默认构造函数时必须避免包含以下错误：

    ```c++
    Sales_data obj(); // 此时obj是一个函数，而非对象
    if(obj.isbn() == Primer_5TH_end.isbn()) // 错误，obj是一个函数
    Sales_data obj; // 正确，obj是一个对象，调用默认构造函数
    ```

### 7.5.4隐式的类类型转换

1. 如果构造函数只接受一个实参，则它实际上定义了转换为此类类型的隐式转换机制，有时我们把这种构造函数称作转换构造函数（converting constructor）。

1. 能通过一个实参调用的构造函数定义了一条从构造函数的参数类型向类类型隐式转换的规则。

    ```c++
    string null_book = "9-999-999-9";
    // null_book实际被隐式转换成了一个Sales_data的对象
    // units_sold和revenue等于0，bookNo等于null_book
    item.combine(null_book);
    // 只允许一步类类型转换，下面的代码是错误的
    // 需要先将9-999-999-9转换成string然后再转换成Sales_data
    item.combine("9-999-999-9");
    ```

1. **隐式的类类型转换只允许一步类类型转换**，如果我们想完成上述调用，可以显式的把字符串转换成string或者Sales_data对象，再传给combine函数。

    ```c++
    item.combine(string("9-999-999-9"));
    item.combine(Sales_data("9-999-999-9"));
    // 下面是利用Sales_data可以接受istream的输入流
    // 然后创建临时的Sales_data对象
    item.combine(cin);
    ```

1. 在类类型的转换过程中产生的临时量，一旦在使用的那行代码执行完成后就不能再被访问。

1. 如果我们想要阻断这种隐式类类型转换，那么**加上关键字explicit就能阻止**:

    ```c++
    class Sales_data{
        public:
            Sales_data() = default;
            Sales_data(const std::string &s, unsigned n, double p):
                bookNo(s), units_sold(n), revenue(p*n){ }
            explicit Sales_data(const std::string &s): bookNo(s){ }
            explicit Sales_data(std::istream&);
    }
    ```

1. 关键字explicit只对一个实参的构造函数有效，**需要多个实参的构造函数不能用于执行隐式转换，所以无需将这些构造函数指定为explicit的**。只需在类内声明构造函数时使用explicit关键字，在类外定义时无需重复。

1. 一旦我们直接声明了explicit于构造函数前，那么我们**只能使用直接初始化，而不能使用拷贝初始化**。

    ```c++
    Sales_data item1(null_book);
    Sales_data item2 = null_book; // 错误，不能使用拷贝初始化
    ```

1. 我们仍然可以使用explicit修饰的构造函数显式地强制转换：

   ```c++
   // 直接使用构造函数接受一个string
   // 创建了一个临时的Sales_data对象
   item.combine(Sales_data(null_book));
   // 显示的强制转换，使用了istream的构造函数
   // 创建了一个临时的Sales_data
   item.combine(static_cast<Sales_data>(cin));
   ```

1. 标准库中含有显示构造函数的类：
   - 接受一个单参数的const char*的string构造函数不是explicit的
   - 接受一个容量参数的vector构造函数是explicit的

### 7.5.5 聚合类

1. 聚合类（aggregate class）使得用户可以直接访问其成员，并且具有特殊的初始化语法形式。当一个类满足以下条件时我们可以称它为聚合的：
   - 所有成员都是public的
   - 没有定义任何构造函数
   - 没有类内初始值
   - 没有基类，没有virtual函数

    ```c++
    struct Data{
        int ival;
        string s;
    };

    Data val1 = {0, "Anna"};
    // 错误，初始值的顺序必须和声明的顺序一致
    Data val1 = {"Anna", 0};
    ```

1. **如果初始值列表中的元素个数少于类的成员数量，则靠后的成员被值初始化，初始值列表的元素个数不能超过类的成员数量**。

1. 显示初始化类的对象的问题：
   - 要求类的所有成员都是public的
   - 将正确初始化每个对象的每个成员的任务交给了类的用户而非作者，因为用户很容易忘掉某个初始值或者提供一个不恰当的初始值，这样的初始化过程冗长乏味且容易出错
   - 添加或删除一个成员之后所有的初始化语句都需要更新。

### 7.5.6 字面值常量类

1. **constexpr函数的参数和返回值必须是字面值类型**。除了算数类型、引用和指针外，某些类也是字面值类型。

1. **字面值类型的类可能含有constexpr函数成员，而这样的成员也必须符合constexpr函数的所有要求，他们是隐式的const**。

1. **数据成员都是字面值类型的聚合类是字面值常量类**。如果一个类不是聚合类，那么符合以下要求他也是字面值常量类：
   - 数据成员都是字面值类型
   - 类必须至少含有一个constexpr构造函数
   - 如果一个数据成员含有类内初始值，则内置类型成员的初始值必须是一条常量表达式，或者如果成员属于某种类类型，则初始值必须使用成员自己的constexpr构造函数
   - 类必须使用析构函数的默认定义，该成员负责销毁类的对象

1. **构造函数不能是const的，但是字面值常量类的构造函数可以是constexpr函数**。（一个字面值常量类必须至少提供一个constexpr构造函数）

1. constexpr构造函数可以声明成=default的形式。**因为构造函数不能有返回语句，而constexpr函数必须只能有一条可执行的语句且必须是返回语句，那么符合这两种的情况只能是函数体为空**：

   ```c++
   class Debug{
        public:
            constexpr Debug(bool b = true): hw(b),io(b),other(b){ }
            constexpr Debug(bool h, bool i, bool o): hw(h),io(i),other(o){ }
            constexpr bool any(){ return hw || io || other;}
            void set_io(bool b){ io = b; }
            void set_hw(bool b){ hw = b; }
            void set_other(bool b){ hw = b; }
        private:
            bool hw;    // 硬件错误
            bool io;    // IO错误
            bool other; // 其他错误
   };
   ```

1. **constexpr构造函数必须初始化所有数据成员，初始值或者使用constexpor构造函数，或者是一条常量表达式**。constexpr构造函数用于生成constexpr对象以及constexpr函数的参数或返回类型。

    ```c++
    constexpr Debug io_sub(false, true, false); //
    if(io_sub.any())
        cerr << "print appropriate error messages" << endl;
    constexpr Debug prod(false); // 无调试
    if(prod.any() ) // 等价于if(false)
        cerr << "print an error message" << endl;
    ```

## 7.6 类的静态成员

1. 我们通过在成员的声明之前加上关键字static使得其与类关联在一起。和其他成员一样，**静态成员可以是public的或private的。静态数据成员的类型可以是常量，引用或指针、类类型等等**。

1. 类的静态成员存在于任何对象之外，对象中不包含任何与静态数据成员有关的数据。静态成员函数也不与任何对象绑定在一起，他们不包含this指针。**静态成员函数不能声明成const，而且也不能在static函数内使用this指针**。这一限制既适用于this的显示使用，也对调用非静态成员的隐式使用有效。

    ```c++
    class Account{
        public:
            void calculate(){ amount += amount * interestRate; }
            static double rate() { return interestRate; }
            static void rate(double);
        private:
            std::string owner;
            double amount;
            static double interestRate;
            static double initRate();
    };
    ```

1. 我们可以使用作用域运算符直接访问静态成员，我们也可以使用类的对象、引用或者指针来访问静态成员：

    ```c++
    double r;
    r = Account::rate(); // 使用作用域访问

    Account ac1;
    Account *ac2 = &ac1;

    r = ac1.rate();  // 通过对象调用
    r = ac2->rate(); // 通过指针调用
    ```

1. 类的成员可以不通过作用域运算符直接使用静态成员：

    ```c++
    class Account{
        public:
            void calculate(){ amount += amount * interestRate; }
        private:
            static double itnerestRate;
    }
    ```

1. 和其他成员函数一样，我们既可以在类的内部也可以在类的外部定义静态成员函数，当在类外定义静态成员函数时，**不能重复static关键字，该关键字只出现在类内部的声明语句**：

    ```c++
    void Account::rate(double newRate){
        interestRate = newRate;
    }
    ```

1. **由于静态成员不属于任何一个类的对象，所以一般情况下他们不能在类的内部被定义，必须在类的外部定义和初始化每个静态成员。和其他对象一样，一个静态数据成员只能定义一次**。类似于全局变量，静态数据成员定义在任何函数之外，因此一旦被定义，就将一直存在于程序的整个生命周期中。

    ```c++
    double Account::initerestRate = initRate();
    ```

1. 要想确保对象只定义一次，最好的办法是把静态数据成员的定义与其他非内联函数的定义放在同一个文件中。

1. 一般情况下类的静态成员不应该在类的内部初始化，但是**我们可以为静态成员提供const整数类型的类内初始值**。不过要求静态成员必须是字面值常量类型的constexpr。初始值也必须是常量表达式，因为这些成员本身就是常量表达式，所以他们也可以用于所有适合常量表达式的地方。

   ```c++
   class Account{
        public:
            static double rate(){ return interestRate; }
            static void rate(double);
        private:
            static constexpr int period = 30;
            double daily_tbl(period);
   };

   // 在类外的一个不带初始值的静态成员的定义
   constexpr int Account::period; // 初始值已经在类内提供
   ```

1. **即使一个常量静态数据成员在类内部被初始化了，通常情况下也应该在类的外定义一下该成员**。

1. **静态数据成员可以是不完全类型**，静态数据成员的类型可以就是它所属的类类型，而非静态数据成员则受到限制，只能声明成它所属类的指针或引用：

   ```c++
   class Bar{
       public:
            // ...
        private:
            static Bar mem1; // 正确，静态成员可以是不完全类型
            Bar *mem2;  // 正确，指针成员可以是不完全类型
            Bar mem3; // 错误，数据成员必须是完全类型
   };
   ```

1. 静态成员和普通成员的另一个区别是**我们可以使用静态成员作为默认实参，而非静态数据成员不能作为默认实参**，因为它的值本身就属于对象的一部分，这么做的结果是无法真正提供一个对象以便从中获取成员的值，最终将引发错误：

    ```c++
    class Screen{
        public:
            Screen& clear(char = background);
        private:
            static const char background;
    }
    ```

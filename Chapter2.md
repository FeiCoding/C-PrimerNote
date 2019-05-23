# Chapter2 变量和基本类型

## 2.1 基本内置类型

1. C++算数类型表：

   | 类型        | 含义           | 最小尺寸（至少）     |
   | :---------- | :------------- | :----------- |
   | bool        | 布尔           | Not defined  |
   | char        | 字符           | 8 bit        |
   | wchar_t     | 宽字符         | 16 bit       |
   | char16_t    | Unicode字符    | 16 bit       |
   | char32_t    | Unicode字符    | 32 bit       |
   | short       | 短整型         | 16 bit       |
   | int         | 整型           | 16 bit       |
   | long        | 长整型         | 16 bit       |
   | long long   | 长整型         | 64 bit       |
   | float       | 单精度浮点数   | 至少6位有效数字  |
   | double      | 双精度浮点数   | 至少10位有效数字 |
   | long double | 扩展精度浮点数 | 至少10位有效数字 |

2. 字符类型：
   - 一个char的空间应确保可以存放机器基本字符集中任意字符对应的数字值，也就是说一个char的大小刚好和一个机器字节一样（1 byte）
   - wchar_t类型用于确保可以存放机器最大扩展字符集中的任意一个字符
   - char16_t和char32_t为unicode字符集服务

3. 内置类型的机器实现
   - 可寻址的最小内存块称为字节（byte），存储的基本单元称为字（Word）
   - 大多数机器的字节由8 bit组成，字则有32或者64 bit，也就是4或8字节

4. 通常float以一个字节来表示，double由两个字节来表示（64 bit），long double则有3或4个字节。long double通常被用于有特殊浮点需求的硬件。

5. 符号类型
   - 带符号类型（signed）可以表示整数、负数或者0，无符号则只能表示大于0的数
   - int、short、long和long long都是带符号的，前面加上unsigned就是无符号类型
   - **unsigned int可以简写成unsigned**
   - char也有char， unsigned char， signed char。但是此处**signed char 和 char类型不一样**，char实际上只有signed char和unsigned char，而char则由编译器决定表示两种中的哪一种
   - 无符号类型所有bit都用来存储值（首bit不是符号位）
   - 为保证正负值的表示范围平衡，8 bit的signed char虽然理论上可以表示-128 到 128，但实际上是-128 到 127（**0算作正方向上的值从而使得正负范围平衡**）

6. <b> 类型选择的建议：
   - 当明确知道数值不为负，选用unsigned
   - 优先使用int。short太短，long长度往往和int相同，过长数据则选用long long
   - 算术表达式中不要选择char或者bool（因为char在不同的机器上可能表现signed或者unsigned，如果不得不使用，明确是signed char还是unsigned char）
   - 浮点运算优先使用double，float常常精度不够，两者计算代价相差不大，某些机器double更快
   - 往往不需要long double精度，而且运行消耗比较大

7. 

## 2.2 变量

## 2.3 复合类型

## 2.4 const限定符

## 2.5 处理类型

## 2.6 自定义数据结构
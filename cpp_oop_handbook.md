# C++ 面向对象程序设计 · 知识点手册

> 适用：课程复习 / 期末速查 / 面试准备。以 **C++11 ~ C++17** 为准；片段以可编译示例为主，完整可运行程序见 `cpp_oop_demo.cpp`。
> 配套文件：`cpp_oop_demo.cpp`（可直接 `g++ -std=c++14` 编译运行的综合示例；本机 Dev-C++ 实测通过）。

---

## 0. 总览：面向对象到底是什么

**面向过程**以「步骤 / 函数」为中心：数据散落在各处，函数操作数据。
**面向对象（OOP）**以「对象」为中心：把数据（属性）和操作数据的函数（行为）**捆绑**在一起，对外只暴露必要接口。

| 概念 | 说明 | 类比 |
| --- | --- | --- |
| 类 `class` | 对象的模板 / 蓝图，描述「有什么 + 能做什么」 | 建筑设计图 |
| 对象 `object` | 类的一个实例，占用真实内存 | 按图纸盖出来的一栋楼 |
| 成员变量 | 对象的状态 / 属性 | 楼的高度、层数 |
| 成员函数 | 对象的行为 / 接口 | 开门、关门 |
| 实例化 | 根据类创建对象（调用构造函数） | 施工 |

**四大特性**及其在 C++ 中的语法载体：

| 特性 | 解决的问题 | C++ 语法载体 |
| --- | --- | --- |
| 抽象 Abstraction | 忽略无关细节，只暴露本质接口 | `class`、纯虚函数、访问控制 |
| 封装 Encapsulation | 隐藏内部实现，防止外部随意破坏状态 | `private` / `protected` / `public`、getter/setter |
| 继承 Inheritance | 复用已有代码，建立 is-a 关系 | `class D : public B`、虚继承 |
| 多态 Polymorphism | 同一接口，不同对象有不同行为 | `virtual` + 基类指针/引用、函数重载、模板 |

> **判断口诀**：`is-a` 用继承（Circle **是一种** Shape）；`has-a` 用组合（Car **有一个** Engine）。能组合就别继承，耦合更低。

### 0.1 代码约定：关于 `using namespace std;`

为了让示例聚焦语法本身，本手册和配套 `cpp_oop_demo.cpp` 统一采用下面的写法：

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "hello";
    cout << s << endl;
}
```

`using namespace std;` 把 `std` 命名空间里的**全部名字**引入当前作用域，之后可直接写 `cout`、`string`、`vector`、`move`、`make_unique`…… 而不必写 `std::cout`。三种写法对比：

| 写法 | 示例 | 评价 |
| --- | --- | --- |
| 完全限定 | `std::cout << std::endl;` | 最安全，工程代码首选 |
| 逐个引入 | `using std::cout; using std::string;` | 折中，推荐 |
| 整体引入 | `using namespace std;` | 教学 / 竞赛最省事，本手册采用 |

**为什么工程里不推荐写在头文件中**：头文件里写 `using namespace std;` 会污染**所有**包含它的源文件；别人定义的 `count`、`distance`、`data`、`begin`、`move` 等名字很容易和 `std` 里的同名模板撞车，报出很难排查的二义性错误。安全的做法是只放在 `.cpp` 文件里，或干脆限制在函数体内部：

```cpp
#include <iostream>

void f() {
    using namespace std;  // 作用域仅限这个函数
    cout << "ok\n";
}
```

> 本手册**正文叙述**里仍写全名（如 `std::move`、`std::vector`）以明确所指，但**所有代码块**都省略了 `std::` 前缀。唯一例外是 3.4 的 `using std::swap;`：那里必须在块作用域显式引入 `std::swap`，否则 `swap(...)` 会被名字查找命中成员函数 `Buffer::swap` 而编译失败。

---

### 0.2 代码风格约定（依据教材 p238–240 / p292–293）

> 本版按《C++ 语言程序设计（第 5 版）》的注释风格排版；完整规则与教材原码摘录见 `教材代码风格_整理版.md`，按教材章节编号重排的版本见 `cpp_oop_handbook_textbook.html`。

| 项目 | 教材写法 | 本版写法 |
| --- | --- | --- |
| `std::` 前缀 | `.h` 全限定 / `.cpp` 用 `using namespace std;` | **统一 `using namespace std;`**（按你的要求省略前缀）；唯一例外 `using std::swap;` |
| 注释 | 中文行尾注释、注释列对齐、函数组前有段注释 | **一致且更详细**：短注释扩写为「为什么」，重点代码块前加 3–5 行观察点 |
| 术语 | 复制构造 / 深复制 / 浅复制 | **一致**（全稿已统一） |
| 成员命名 | 不带下划线、形参与成员同名 | 保留 `xxx_` 后缀，避免同名赋值歧义 |
| 大括号 / 缩进 | K&R、访问控制符顶格 | **一致** |

> 教材把 `using namespace std;` 只写在 `.cpp`，是因为头文件会被多个源文件包含，写了会污染所有包含者；本版示例代码都是单一编译单元，按你的要求统一省略前缀，但**写多文件工程时请照教材分开处理**。

---

## 1. 类与对象基础

### 1.1 定义一个类

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:                                        // class 成员默认 private；改成 struct 则默认 public（教材 4.6）
    string name_;
    int age_;
    static int count_;                          // 静态成员：属于类，不属于某个对象

public:
    Student(const string& name, int age)
        : name_(name), age_(age) { ++count_; }  // 构造函数 + 初始化列表

    void print() const {                        // const 成员函数：承诺不修改对象
        cout << name_ << " / " << age_ << '\n';
    }
    void setAge(int age) { age_ = age; }

    static int count() { return count_; }       // 静态成员函数：没有 this
};

int Student::count_ = 0;                        // 类外定义（C++17 起可写 inline static int count_ = 0;）

int main() {
    Student a("Alice", 18);
    a.print();

    const Student b("Bob", 20);
    b.print();                                  // OK：const 对象只能调用 const 成员函数
    // b.setAge(21);           // 编译错误

    cout << Student::count() << '\n';           // 2
}
```

**访问权限速查**

| 限定符 | 类内 | 派生类 | 类外（对象.成员） |
| --- | --- | --- | --- |
| `public` | 可 | 可 | 可 |
| `protected` | 可 | 可 | 不可 |
| `private` | 可 | 不可 | 不可 |

> `class` 与 `struct` **唯一**区别：默认访问权限（private vs public）和默认继承方式（private vs public）。其余完全一样。

### 1.2 对象创建与内存布局

```cpp
// 片段：接 1.1 的 Student 类定义，这里只展示对象创建语句
Student a("Ann", 19);                            // 栈对象：作用域结束自动析构
Student* p = new Student("Bob", 20);             // 堆对象：必须手动 delete
delete p;

Student arr[3] = { {"A",1}, {"B",2}, {"C",3} };  // 对象数组：调用 3 次构造
// delete[] 用于 new[] 分配的数组，delete / delete[] 必须配对
```

- 对象大小 = **非静态成员变量之和 + 内存对齐 + 虚表指针（若有虚函数）**。
- 成员函数、静态成员都不存储在每个对象里，全类共享一份代码。
- 空类 `sizeof == 1`（编译器插入占位字节，保证两个对象地址不同）。
- 含虚函数的类，对象头部通常有一个 `vptr`（8 字节，64 位）。

### 1.3 `this` 指针

每个**非静态成员函数**都隐含一个参数 `T* const this`，指向调用该函数的对象。

```cpp
class Point {
    int x_, y_;
public:
    Point(int x, int y) : x_(x), y_(y) {}  // 参数名与成员名冲突时靠初始化列表区分
    Point& moveTo(int x, int y) {
        this->x_ = x;                      // 显式使用 this 消除歧义
        this->y_ = y;
        return *this;                      // 返回自身引用 → 支持链式调用 p.moveTo(1,2).show();
    }
};
```

- 静态成员函数**没有** `this`，因此不能访问非静态成员。
- `const` 成员函数里 `this` 的类型是 `const T* const`，所以不能改成员；想改需把成员声明为 `mutable`。

### 1.4 初始化列表（三种必须使用）

```cpp
struct NoDefault {
    explicit NoDefault(int) {}
};

class Widget {
    const int id_;  // (1) const 成员
    int& ref_;      // (2) 引用成员
    NoDefault nd_;  // (3) 没有默认构造函数的成员
public:
    Widget(int id, int& r) : id_(id), ref_(r), nd_(id) {}
    // 若写成函数体内赋值：id_ 不可赋值、ref_ 必须绑定、nd_ 找不到默认构造 → 全部编译失败
};
```

- 初始化列表的顺序由**成员声明顺序**决定，与书写顺序无关；建议始终按声明顺序写。
- 初始化列表是「初始化」，函数体里是「赋值」：对类类型成员，前者少一次默认构造 + 一次赋值，**效率更高**。

### 1.5 `explicit` 与隐式转换

```cpp
class Meter {
    double v_;
public:
    explicit Meter(double v) : v_(v) {}
};
void f(Meter m) {}

int main() {
    // f(3.14);                 // 不加 explicit：double 被隐式转成 Meter（容易出隐蔽 bug）
    f(Meter(3.14));  // 加 explicit 后必须显式构造
}
```

> **习惯**：单参数构造函数（以及 C++11 起的多参数转换构造）默认都加 `explicit`。

### 1.6 `static` 成员与友元

```cpp
class Config;                              // 前置声明
class Logger {
    static int level_;                     // 静态数据成员属于类而非对象：全类只有一份，必须在类外定义一次
public:
    friend void debugDump(const Logger&);  // 友元函数不是成员函数，但被授权访问本类私有成员（单向、不可继承）
    friend class Config;                   // 友元类
};
int Logger::level_ = 0;

void debugDump(const Logger& l) { /* 可访问 l 的私有成员 */ }
```

- 静态成员函数只能访问静态成员；友元**破坏封装**，能不用就不用。
- 友元关系**不传递、不继承、不双向**。

---

## 2. 构造函数与析构函数：对象生命周期

| 函数 | 调用时机 | 特点 |
| --- | --- | --- |
| 构造函数 | 创建对象时 | 无返回类型、可重载、名字 = 类名 |
| 默认构造函数 | 无参 / 全部参数有默认值 | 一旦你写了任意构造函数，编译器**不再**自动生成 |
| 析构函数 | 对象销毁时 | `~类名()`、无参、无返回、**不能重载**、通常应为 `virtual`（作为基类时） |
| 复制构造函数 | 用已有对象初始化新对象 | 见第 3 章 |
| 移动构造函数 | 用右值（临时对象）初始化 | 见第 4 章 |

```cpp
#include <iostream>

using namespace std;
class Box {
    int w_, h_;
public:
    Box() : Box(1, 1) {}          // 委托构造（C++11）
    Box(int w, int h) : w_(w), h_(h) { cout << "构造\n"; }
    ~Box() { cout << "析构\n"; }  // 释放资源的地方（RAII）
};
```

**构造 / 析构顺序**（继承 + 组合同时存在时，面试常考）：

```cpp
#include <iostream>

using namespace std;
struct Base   { Base(){ cout<<"Base "; }   ~Base(){ cout<<"~Base "; } };
struct Member { Member(){ cout<<"Member "; } ~Member(){ cout<<"~Member "; } };
struct Derived : Base {
    Member m;
    Derived(){ cout<<"Derived\n"; }
    ~Derived(){ cout<<"~Derived "; }
};
// 构造：Base → Member → Derived
// 析构：~Derived → ~Member → ~Base（严格反序）
```

---

## 3. 【重点】复制构造函数 `A(const A& a)`

### 3.1 函数签名逐字拆解

```cpp
class A {
    int x_;                      // 演示用的数据成员
public:
    explicit A(int x = 0) : x_(x) {}
    A(const A& a) : x_(a.x_) {}  // 复制构造函数：用 a 的成员初始化新对象
};
```

| 片段 | 含义 | 为什么必须这样 |
| --- | --- | --- |
| `A` | 函数名与类名相同，且**没有返回类型**（连 `void` 都不能写） | 构造函数的语法规定 |
| `const A& a` 中的 `&` | 引用传参 | 如果写成值传递 `A(A a)`，调用时必须先复制实参 → 又要调用复制构造 → **无限递归**，编译器直接报错：`invalid constructor; you probably meant A(const A&)` |
| `const` | 不修改源对象 | ① 语义上「复制」不该改动原对象；② 可以接收 `const A` 对象和临时对象（`A(A& a)` 无法绑定右值） |
| 参数只有一个 | 且必须是本类类型的引用 | 可以有额外参数，但必须有默认值；否则不是复制构造 |

**四种写法对比：**

| 写法 | 是否复制构造 | 评价 |
| --- | --- | --- |
| `A(A a)` | 否，且**无法编译** | 值传递导致无限递归 |
| `A(A& a)` | 是 | 能编译，但不能复制 `const` 对象和临时对象，不推荐 |
| `A(const A& a)` | 是 | **标准写法** |
| `A(A&& a)` | 否（是移动构造） | C++11，见第 4 章 |

```cpp
// 反例（故意无法编译）：为什么不能按值传参
A(A a) { }  // 编译错误：调用 A b(x) 时，为把 x 传给 a 又要调用 A(A a)……无穷递归
```

> **编译器合成的默认复制构造**：如果你不写，编译器会生成一个，逐个成员做**浅复制**（对类类型成员调用它的复制构造，对指针/内置类型直接复制值）。一旦类持有 `new` 出来的资源，这个默认版本就是 bug 之源。

### 3.2 被调用的三种时机（必背）

```cpp
// 示例 3-2：复制构造函数的三种调用时机
// 观察点：(1) 定义新对象并用已有对象初始化；(2) 实参按值传给形参；
//         (3) 函数按值返回对象 —— 这三种都会调用复制构造函数。
// 易错：z = x 中 z 已存在，走的是复制赋值运算符，不是复制构造。
// 提示：加 -fno-elide-constructors 关闭 RVO，才能看全第 (3) 种的调用。

#include <iostream>
using namespace std;
class A {
public:
    A()                      { cout << "默认构造\n"; }
    A(const A&)              { cout << "复制构造\n"; }
    A& operator=(const A&)   { cout << "复制赋值\n"; return *this; }
};

void byValue(A a) {}          // 时机 (2)：函数参数按值传递
A makeA() { A x; return x; }  // 时机 (3)：函数按值返回（可能被 RVO 优化）

int main() {
    A a;                      // 默认构造
    A b(a);                   // (1) 复制构造：用一个已有对象初始化新对象
    A c = a;                  // (1) 复制构造（注意：这是「初始化」，不是赋值！）
    A d;                      // 默认构造
    d = a;                    // 复制赋值：两边对象都已存在，不走复制构造
    byValue(a);               // (2) 复制构造
    A e = makeA();            // (3) 可能只打印一次「默认构造」——RVO/NRVO 返回值优化
}
```

**区分技巧**：看等号左边是不是**正在诞生**的对象。
`A c = a;` → `c` 此刻还不存在 → 复制构造；`d = a;` → `d` 已存在 → 复制赋值。

> **RVO 提醒**：C++17 起「保证复制消除」（guaranteed copy elision）覆盖返回纯右值的场景，NRVO 仍是可选优化。因此**永远不要**在复制构造/析构里写影响程序正确性的副作用（如计数、打印判断逻辑）。可用 `-fno-elide-constructors` 关闭优化来观察完整调用链。

### 3.3 浅复制的坑：默认复制构造 + 指针成员

```cpp
class Bad {
    int* data_;
public:
    explicit Bad(int n) : data_(new int[n]) {}
    ~Bad() { delete[] data_; }
    // 没有手写复制构造 → 编译器合成版本：data_ = rhs.data_（只复制指针值）
};

int main() {
    Bad a(4);
    Bad b(a);  // b.data_ 与 a.data_ 指向同一块堆内存
}              // 析构 b：释放内存；析构 a：再次释放同一地址 → double free / 崩溃
```

内存示意：

```
浅复制                              深复制
a ──┐                              a ──► [ 0 0 0 0 ]
    ├──► [ 0 0 0 0 ]              b ──► [ 0 0 0 0 ]   （各自独立的一块内存）
b ──┘   ↑ 两个指针共用一个资源
        任一对象改动，另一个被"连坐"；析构两次 → 崩溃
```

### 3.4 深复制的标准写法（完整可运行）

```cpp
// 示例 3-5：copy-and-swap 惯用法（比传统写法更简洁、天然异常安全）
// 关键：operator= 的形参按值传递，进函数前已由复制构造完成深复制；
//       随后 swap 交换资源，rhs 带着旧资源在函数结束时被析构自动释放。
// 唯一保留 std:: 之处：using std::swap; 不能省，否则会命中成员函数 swap。

// 示例 3-4：手写深复制 —— 传统写法
// 三条规则：(1) 复制构造中重新 new 并复制内容，绝不与源对象共享地址；
//           (2) 赋值运算先判自我赋值，否则 a = a 会先释放自己的资源；
//           (3) 先申请新内存、成功后再 delete 旧的，保证 new 抛异常时对象不变。

#include <iostream>
#include <cstddef>
#include <cstring>
#include <utility>
using namespace std;

class Buffer {
    size_t size_ = 0;
    char* data_ = nullptr;
public:
    explicit Buffer(size_t n) : size_(n), data_(new char[n]{}) {
        cout << "构造 size=" << n << '\n';
    }

    // ★ 复制构造：自己申请新内存，再复制内容
    Buffer(const Buffer& rhs) : size_(rhs.size_), data_(new char[rhs.size_]) {
        if (size_ > 0) memcpy(data_, rhs.data_, size_);  // 源对象可能已被移动过
        cout << "复制构造（深复制）\n";
    }

    // ★ 复制赋值：copy-and-swap 惯用法，天然处理自我赋值 + 强异常安全
    Buffer& operator=(Buffer rhs) {                      // 形参按值传递 → 自动调用一次复制构造
        swap(rhs);                                       // 交换后 rhs 持有旧资源，函数结束时由析构释放
        return *this;
    }

    void swap(Buffer& o) noexcept {
        using std::swap;                                 // 唯一例外：这里不能省略 std::，否则名字查找会命中成员函数 swap(Buffer&) 而编译失败
        swap(size_, o.size_);
        swap(data_, o.data_);
    }

    ~Buffer() { delete[] data_; cout << "析构\n"; }

    size_t size() const { return size_; }
};

int main() {
    Buffer a(8);
    Buffer b(a);                                         // 深复制：重新申请内存并复制内容，两个对象各自持有独立资源
    Buffer c(4);
    c = a;                                               // 形参复制构造 + 复制赋值（copy-and-swap）
    cout << b.size() << ' ' << c.size() << '\n';
}
```

**手写复制赋值时最容易漏的三件事**：

1. `if (this == &rhs) return *this;` —— 防止自我赋值时先 `delete` 掉自己的资源；
2. 先申请新内存成功，再释放旧内存 —— 保证 `new` 抛异常时对象仍有效（**强异常安全**）；
3. 返回 `A&` —— 支持 `a = b = c` 链式赋值。

```cpp
#include <cstddef>
#include <cstring>
using namespace std;

// 传统写法（对照）：这里给出完整类，复制出去即可单独编译
class Buffer {
    size_t size_ = 0;
    char* data_ = nullptr;
public:
    explicit Buffer(size_t n) : size_(n), data_(new char[n]{}) {}
    ~Buffer() { delete[] data_; }
    Buffer(const Buffer& rhs) : size_(rhs.size_), data_(new char[rhs.size_]) {
        if (size_ > 0) memcpy(data_, rhs.data_, size_);
    }

    Buffer& operator=(const Buffer& rhs) {
        if (this != &rhs) {
            char* tmp = new char[rhs.size_];  // 先申请新内存：若 new 抛异常，原对象仍保持原状（强异常安全）
            if (rhs.size_ > 0) memcpy(tmp, rhs.data_, rhs.size_);
            delete[] data_;                   // 再释放旧的
            data_ = tmp; size_ = rhs.size_;
        }
        return *this;
    }
};
```

### 3.5 Rule of Three / Five / Zero

| 规则 | 内容 |
| --- | --- |
| **Rule of Three**（C++98） | 如果需要自定义「析构函数 / 复制构造 / 复制赋值」中的**任意一个**，通常三个都要自定义 |
| **Rule of Five**（C++11） | 再加上「移动构造 / 移动赋值」，共五个特殊成员函数 |
| **Rule of Zero**（推荐） | 用 `std::vector` / `std::string` / `std::unique_ptr` 管理资源，自己的类**一个都不要写**，让编译器自动生成 |

```cpp
#include <vector>
#include <cstddef>

using namespace std;
// Rule of Zero：最现代、最不容易错的写法
class Good {
    vector<int> data_;  // 资源交给标准库成员管理：合成的特殊成员函数天然正确，无需手写（Rule of Zero）
public:
    explicit Good(size_t n) : data_(n) {}
    // 析构、复制构造、复制赋值、移动构造、移动赋值 全部交给编译器，且都是正确的深复制
};
```

**五个特殊成员函数完整实现：**

```cpp
#include <algorithm>
#include <cstddef>
using namespace std;

class RuleOfFive {
    size_t n_ = 0;
    int* p_ = nullptr;
public:
    explicit RuleOfFive(size_t n) : n_(n), p_(new int[n]{}) {}

    ~RuleOfFive() { delete[] p_; }                              // (1) 析构

    RuleOfFive(const RuleOfFive& o) : n_(o.n_), p_(new int[o.n_]) {  // (2) 复制构造
        copy(o.p_, o.p_ + n_, p_);
    }

    RuleOfFive& operator=(const RuleOfFive& o) {                // (3) 复制赋值
        if (this != &o) {
            int* tmp = new int[o.n_];
            copy(o.p_, o.p_ + o.n_, tmp);
            delete[] p_;  p_ = tmp;  n_ = o.n_;
        }
        return *this;
    }

    RuleOfFive(RuleOfFive&& o) noexcept : n_(o.n_), p_(o.p_) {  // (4) 移动构造
        o.p_ = nullptr; o.n_ = 0;                               // 把源对象置于可安全析构的状态
    }

    RuleOfFive& operator=(RuleOfFive&& o) noexcept {            // (5) 移动赋值
        if (this != &o) {
            delete[] p_;
            p_ = o.p_; n_ = o.n_;
            o.p_ = nullptr; o.n_ = 0;
        }
        return *this;
    }
};
```

> **注意**：一旦声明了复制构造/复制赋值/析构中的任意一个，编译器就**不会**自动生成移动构造和移动赋值（会退化成复制）。要么五个全写，要么 `= default` 显式要回来。

### 3.6 `= default` 与 `= delete`

```cpp
class NonCopyable {
public:
    NonCopyable() = default;                              // 显式要求编译器生成默认构造
    NonCopyable(const NonCopyable&) = delete;             // 禁止复制构造
    NonCopyable& operator=(const NonCopyable&) = delete;  // 禁止复制赋值
    NonCopyable(NonCopyable&&) = default;                 // 允许移动
};
```

`std::unique_ptr`、`std::thread`、IO 流对象都是典型的「不可复制」类型。

### 3.7 高频易错点

| 坑 | 说明 |
| --- | --- |
| `A a();` | 这不是创建对象，而是**声明了一个返回 A、无参的函数**（most vexing parse）。写成 `A a;` 或 `A a{};` |
| `A c = a;` 当成赋值 | 实为复制构造，发生在对象初始化阶段 |
| 复制构造忘记 `const` | 无法从 `const A` / 临时对象复制，容器 `push_back` 等场景报错 |
| 忘记自我赋值检查 | `a = a` 时释放自身内存 → 悬空指针 |
| 基类析构非 `virtual` | 通过基类指针 `delete` 派生对象 → 只析构基类部分，资源泄漏（未定义行为） |
| 返回局部对象担心性能 | RVO/NRVO + 移动语义已消除绝大多数复制，直接 `return x;` 即可，别 `return std::move(x);`（会抑制 NRVO） |
| 引用成员 / 指针成员 | 默认复制是浅的，必须明确要不要深复制 |

---

## 4. 移动语义与 RAII

### 4.1 左值 / 右值 / `std::move`

```cpp
#include <string>
#include <utility>

using namespace std;
int x = 1;           // x 是左值（有名字、可取地址）
int&& r = x + 1;     // x + 1 是右值（临时量）
string s = "abc";
string t = move(s);  // move 只是「强制转成右值引用」，不搬任何东西
                                // 此后 s 仍有效但内容未指定（通常为空），不要再读它
```

- 移动构造 `A(A&& rhs) noexcept`：直接「偷」走 `rhs` 的指针，再把 `rhs` 置空，避免一次深复制。
- 标 `noexcept` 很重要：`std::vector` 扩容时只有确认移动不会抛异常才会用移动而非复制。

### 4.2 RAII 与智能指针

**RAII**（Resource Acquisition Is Initialization）：把资源的获取绑定到对象构造、释放绑定到析构，靠栈对象自动析构保证异常安全。

| 智能指针 | 语义 | 典型用途 |
| --- | --- | --- |
| `std::unique_ptr<T>` | 独占所有权，不可复制、可移动 | 默认首选，`std::make_unique` |
| `std::shared_ptr<T>` | 共享所有权，引用计数 | 多方共享；注意循环引用 |
| `std::weak_ptr<T>` | 不增加计数的观察者 | 打破 `shared_ptr` 循环引用 |

```cpp
#include <memory>
#include <utility>
using namespace std;
auto p = make_unique<int>(42);  // 离开作用域自动 delete，绝不会泄漏
// auto q = p;                          // 编译错误：unique_ptr 不可复制
auto q = move(p);               // OK：转移所有权，p 变为 nullptr
```

---

## 5. 继承

### 5.1 语法与访问控制

```cpp
// 示例 6-2：虚函数、纯虚函数、抽象类与虚析构
// 三个条件：基类声明 virtual、派生类签名一致地重写、通过基类指针或引用调用。
// 观察点：p->draw() 的静态类型是 Shape*，运行期经 vtable 调到 Circle::draw()。
// 必背：基类析构必须 virtual，否则 delete p 时派生部分不会被析构。

#include <string>
#include <utility>

using namespace std;
class Shape {
protected:                                                 // 派生类可见，外部不可见
    string name_;
public:
    explicit Shape(string n) : name_(move(n)) {}
    virtual ~Shape() = default;                            // 基类析构必须是虚函数
    virtual double area() const { return 0; }
};

class Circle : public Shape {                              // public 继承 = is-a
    double r_;
public:
    Circle(double r, string n) : Shape(move(n)), r_(r) {}  // 显式调用基类构造
    double area() const override { return 3.1415926 * r_ * r_; }
};
```

**继承方式对基类成员可见性的影响：**

| 基类成员 \ 继承方式 | `public` 继承 | `protected` 继承 | `private` 继承 |
| --- | --- | --- | --- |
| `public` | `public` | `protected` | `private` |
| `protected` | `protected` | `protected` | `private` |
| `private` | 不可直接访问 | 不可直接访问 | 不可直接访问 |

> 派生类**永远无法直接访问**基类的 `private` 成员，只能通过基类提供的 `protected`/`public` 接口。实际开发中 99% 用 `public` 继承。

### 5.2 名字隐藏与 `using`

```cpp
struct Base { void f(int) { } void f(double) { } };
struct D : Base {
    void f(int) { }  // 隐藏了 Base 中所有名为 f 的重载（不是覆盖！）
};
D d;
// d.f(3.14);               // 若 D::f(int) 存在，Base::f(double) 被隐藏
struct D2 : Base {
    using Base::f;   // 把基类重载集引入派生类作用域
    void f(int) { }
};
D2 d2; d2.f(3.14);   // OK
```

### 5.3 对象切片（slicing）

```cpp
#include <iostream>

using namespace std;
struct Base   { int x = 1; virtual void f() const { cout << "Base\n"; } };
struct Derived: Base { int y = 2; void f() const override { cout << "Derived\n"; } };

Derived d;
Base b = d;   // 按值复制 → 只保留 Base 部分，y 被"切掉"，虚函数表也变回 Base
b.f();        // Base
Base& r = d;  // 引用/指针不切片
r.f();        // Derived
```

> **结论**：多态必须通过**基类指针或引用**实现；把派生对象按值传给 `Base` 参数会丢失多态性（且抽象类根本无法按值传递）。

### 5.4 多重继承与菱形继承

```cpp
struct A { int x; };
struct B : A {};        // B 有一份 A
struct C : A {};        // C 有一份 A
struct D : B, C {};     // D 有两份 A → d.x 二义性，编译错误

// 虚继承解决：让最底层派生类只保留一份共享基类子对象
struct B2 : virtual A {};
struct C2 : virtual A {};
struct D2 : B2, C2 {};  // D2 中只有一份 A，d2.x 无二义性
```

虚继承的构造顺序：虚基类由**最底层派生类**负责构造（且最先构造），B2/C2 中对 A 的构造调用会被忽略。

---

## 6. 多态

### 6.1 两种多态

| | 静态多态（编译期） | 动态多态（运行期） |
| --- | --- | --- |
| 机制 | 函数重载、运算符重载、模板 | 虚函数 + 虚表 |
| 绑定时机 | 编译期（早绑定） | 运行期（晚绑定 / 动态绑定） |
| 开销 | 无 | 一次间接寻址 + 无法内联 |
| 前提 | 参数类型不同 | 继承 + 重写虚函数 + 基类指针/引用调用 |

### 6.2 虚函数、纯虚函数、抽象类

```cpp
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;                            // 纯虚函数 → Shape 成为抽象类，不能实例化
    virtual void draw() const { cout << "Shape\n"; }
    virtual ~Shape() { cout << "~Shape\n"; }                    // ★ 基类析构必须 virtual
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }  // override 让编译器检查签名
    void draw() const override { cout << "Circle\n"; }
    ~Circle() override { cout << "~Circle\n"; }                 // 析构函数也可标 override
};

int main() {
    Shape* p = new Circle(2.0);                                 // 基类指针指向派生对象
    p->draw();                                                  // 动态绑定 → Circle
    cout << p->area() << '\n';
    delete p;                                                   // virtual 析构 → ~Circle 然后 ~Shape（顺序正确）
    // 若 ~Shape 非 virtual：只调用 ~Shape，Circle 特有资源泄漏 → 未定义行为
}
```

- `override`：显式声明「我要重写」，签名写错（少 `const`、参数不同）时编译报错。
- `final`：禁止继续重写 / 禁止被继承。
- 含纯虚函数的类是**抽象类**，只能作为指针/引用类型使用；派生类若不实现全部纯虚函数，仍是抽象类。
- **构造函数和析构函数内部调用虚函数不会发生多态**（此时对象被视为当前类类型）；静态成员函数、`friend`、内联的普通成员调用也不参与动态绑定。

### 6.3 虚函数表（vtable）原理

每个含虚函数的**类**有一张虚表，每个**对象**头部有一个隐藏指针 `vptr` 指向它：

```
Shape* p ──► Circle 对象
             ┌──────────┐
             │ vptr  ───┼──► Circle 的 vtable
             │ r_ = 2.0 │      ┌──────────────────────┐
             └──────────┘      │ [0] &Circle::~Circle │
                               │ [1] &Circle::draw    │
                               │ [2] &Circle::area    │
                               └──────────────────────┘
p->draw() 编译成： (*(p->vptr)[1])(p)   → 运行时才决定调用哪个函数
```

重写（override）的本质：派生类虚表中对应槽位被替换成派生类版本的函数地址。

**动态绑定成立的三个条件（缺一不可）**：① 有继承关系；② 派生类重写了 `virtual` 函数且签名完全一致；③ 通过基类**指针或引用**调用。

---

## 7. 运算符重载

```cpp
#include <iostream>
using namespace std;

class Vec2 {
    double x_, y_;
public:
    Vec2(double x, double y) : x_(x), y_(y) {}

    Vec2 operator+(const Vec2& o) const { return {x_ + o.x_, y_ + o.y_}; }
    bool operator==(const Vec2& o) const { return x_ == o.x_ && y_ == o.y_; }
    double operator[](int i) const { return i == 0 ? x_ : y_; }

    Vec2& operator++()    { ++x_; ++y_; return *this; }         // 前置 ++，返回引用
    Vec2  operator++(int) { auto t = *this; ++*this; return t; }  // 后置 ++，int 仅作区分标记

    // << 的左操作数是 ostream，不能作为成员函数 → 用友元
    friend ostream& operator<<(ostream& os, const Vec2& v) {
        return os << '(' << v.x_ << ", " << v.y_ << ')';
    }
};

int main() {
    Vec2 a(1, 2), b(3, 4);
    cout << a + b << ' ' << (a == b) << ' ' << a[0] << '\n';
}
```

**规则速记**

- 不能创造新运算符，不能改变优先级/结合性/操作数个数；至少有一个操作数是类类型。
- **不能重载**：`.` `.*` `::` `?:` `sizeof` `typeid` 及预处理符 `#` `##`。
- `=` `[]` `()` `->` 必须是**成员**函数；`<<` `>>` 通常是**非成员友元**。
- `=`、`+=` 等一般返回 `T&`；`+`、`-` 等返回新对象（按值）。
- 复制赋值 `operator=` 必须自己定义（编译器合成的是浅复制），且要处理自我赋值。

---

## 8. 与 OOP 配套的其他机制（简述）

```cpp
#include <vector>
#include <utility>
#include <memory>
#include <stdexcept>

using namespace std;
// 函数模板 / 类模板：编译期多态
template <typename T>
T maximum(T a, T b) { return a > b ? a : b; }

template <typename T>
class Stack {
    vector<T> elems_;
public:
    void push(const T& v) { elems_.push_back(v); }
    T pop() { T v = move(elems_.back()); elems_.pop_back(); return v; }
    bool empty() const { return elems_.empty(); }
};

// 异常 + RAII：析构函数会在栈展开时自动调用，资源不会泄漏
void risky() {
    auto p = make_unique<int>(42);
    throw runtime_error("oops");  // p 在异常传播过程中自动析构
}
```

| 机制 | 要点 |
| --- | --- |
| 模板 | 泛型编程，编译期生成代码；`typename` / `class` 等价 |
| 异常 | `try / catch / throw`；按值抛出、按 const 引用捕获；析构函数不要抛异常 |
| 类型转换 | `static_cast` / `dynamic_cast`（需多态，失败返回 nullptr 或抛异常）/ `const_cast` / `reinterpret_cast` |
| STL | `std::string` `std::vector` 都是遵循 RAII 和 Rule of Zero 的类，是「该怎么写类」的最佳范本 |

---

## 9. 速查表 & 面试高频问题

### 9.1 特殊成员函数一览

| 函数 | 典型签名 | 何时自动生成 | 关键注意点 |
| --- | --- | --- | --- |
| 默认构造 | `A();` | 未声明任何构造函数时 | 声明了带参构造就没了，用 `A() = default;` |
| 析构 | `~A();` | 总是 | 作为基类时 `virtual` |
| 复制构造 | `A(const A&);` | 未声明复制/移动操作时 | 默认浅复制；有堆资源必须深复制 |
| 复制赋值 | `A& operator=(const A&);` | 同上 | 自我赋值检查、返回 `A&` |
| 移动构造 | `A(A&&) noexcept;` | 未声明任何复制/移动/析构时 | 偷资源后置空源对象 |
| 移动赋值 | `A& operator=(A&&) noexcept;` | 同上 | 先释放自身资源 |

### 9.2 十个高频问题（简答）

1. **复制构造为什么必须用引用？** 值传递需要先复制实参，会再次调用复制构造，形成无限递归，编译期即报错。
2. **为什么加 `const`？** 复制不应修改源对象；且 `const A&` 能绑定 `const` 对象和临时对象（右值）。
3. **`A a; a = b;` 与 `A a = b;` 区别？** 前者先默认构造再复制赋值；后者直接复制构造。
4. **浅复制危害？** 多个对象共享同一堆内存 → 重复释放、悬空指针、互相干扰。
5. **Rule of Three 是什么？** 自定义析构/复制构造/复制赋值之一，通常三者都要自定义；C++11 扩展为 Rule of Five。
6. **基类析构为什么必须 virtual？** 否则 `delete 基类指针` 只析构基类子对象，派生资源泄漏，属未定义行为。
7. **多态的实现原理？** 虚表 vtable + 对象内 vptr，调用时通过 vptr 索引函数地址，运行时绑定。
8. **构造/析构里调用虚函数会多态吗？** 不会，此时虚表指针指向当前正在构造/析构的类。
9. **重载、重写（override）、隐藏的区别？** 重载=同作用域不同参数；重写=派生类覆盖基类虚函数；隐藏=派生类同名成员遮蔽基类所有同名重载。
10. **`std::move` 做了什么？** 只是把左值强制转换为右值引用，真正的「移动」由移动构造/移动赋值完成。

### 9.3 编译与调试建议（已在本机实测）

> **本机实测环境**：Dev-C++ 5.11 自带 **TDM-GCC 4.9.2**（2014 年），位于
> `D://Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe`。
> 它**最高只支持 `-std=c++14`**，写 `-std=c++17` 会直接报
> `unrecognized command line option '-std=c++17'`。以下命令均已实际编译运行通过。

```bash
# 本手册全部示例只用 C++11/14 特性，Dev-C++ 直接可编译
g++ -std=c++14 -Wall -Wextra -pedantic cpp_oop_demo.cpp -o demo
g++ -std=c++14 -fno-elide-constructors demo.cpp -o demo_no_elide   # 观察完整复制链

# GBK 备选版：必须指定输入 / 输出字符集
g++ -std=c++14 -finput-charset=GBK -fexec-charset=GBK cpp_oop_demo_gbk.cpp -o demo_gbk

# 较新的编译器（GCC 7+ / MinGW-w64 / MSVC）才可用 C++17 与 ASan
g++ -std=c++17 -fsanitize=address,undefined demo.cpp -o demo_asan    # 抓 double free
```

| 项目 | Dev-C++ 5.11 自带 TDM-GCC 4.9.2 | 说明 |
| --- | --- | --- |
| 查版本 | `g++ --version` | 或 Dev-C++ 菜单「帮助 → 关于」 |
| 支持标准 | C++11 / C++14（`-std=c++1y` 亦可） | **不支持** C++17 |
| C++17 特性 | `inline static` 成员、结构化绑定等不可用 | 静态数据成员仍须「类内声明 + 类外定义」 |
| ASan / UBSan | 不支持（MinGW 无对应运行时库） | 需 MSVC / Linux / WSL / Clang |
| 中文乱码 | 见 9.4 | UTF-8 BOM + 65001，或 GBK + 936 |
| 想用 C++17 | 换装 MinGW-w64 / TDM-GCC 新版，或在 Dev-C++「工具 → 编译选项」里换编译器目录 | 教材课程一般到 C++11 就够 |

> **一键验证**：`python verify_examples.py --run` 会自动定位本机 g++，逐个编译两份手册里的
> 全部 C++ 代码块，并实际编译运行两份 demo。当前结果：**60 块中 56 块通过编译、
> 4 块为已标注的示意/反例片段、0 个真实错误**。

### 9.4 Windows 下中文乱码：原因与三种解法

**先分清三种现象**（原因完全不同，别乱试）：

| 现象 | 原因 | 该改哪里 |
| --- | --- | --- |
| 编辑器里中文注释/字符串**本身就是乱码** | 源文件编码 ≠ 编辑器打开时用的编码（UTF-8 被按 GBK 读，或反过来） | 文件编码 / 编辑器设置 |
| 编译报 `illegal byte sequence`、`C2018 unknown character`、`C4819` | 编译器读源码的输入字符集不对 | 编译参数 / 保存编码 |
| 编译通过、运行**输出**是乱码或问号 | 控制台默认代码页 **936(GBK)**，而字符串字节是 **UTF-8** | 运行时代码页 |

> **根因一句话**：中文 Windows 控制台默认按 GBK 解码字节，而现代编辑器/编译器默认 UTF-8。`std::cout << "中文"` 只是把源码里那几个字节原样写出去，中途**不做任何转换**。

**方案 A（推荐，通杀 Dev-C++ / VS / VS Code）**：源文件存为 **UTF-8 带 BOM**，并在 `main()` 开头把控制台切到 UTF-8：

```cpp
#include <iostream>
#ifdef _WIN32
#include <windows.h>
using namespace std;
#endif

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);        // 输入代码页切到 65001(UTF-8)，让 cin 读到的中文按 UTF-8 解析
    SetConsoleOutputCP(65001);  // 输出代码页切到 65001(UTF-8)：关键一句，否则 UTF-8 字节被按 GBK 显示成乱码
#endif
    cout << "中文正常显示\n";
}
```

- BOM（文件头 3 字节 `EF BB BF`）让 Dev-C++ / Visual Studio 正确识别源码是 UTF-8，编辑器里不再乱码；MSVC 也不会再按系统 ANSI 误读中文。
- `#ifdef _WIN32` 保证这份代码在 Linux/macOS 上照样能编译。
- 如果中文变成**方块或问号**而不是乱码：这是控制台字体问题。右键控制台标题栏 → 属性 → 字体，把「点阵字体」换成 **Consolas / Lucida Console / 新宋体**。

**方案 B（老版 Dev-C++ 4.9 不认 BOM 时）**：把源文件另存为 **ANSI/GBK**，并显式设回 936：

```cpp
// 片段：放进 main() 开头，需 #include <windows.h>
SetConsoleCP(936);
SetConsoleOutputCP(936);
```

MinGW GCC 编译 GBK 源码必须指定字符集，否则报 `converting to execution character set: Illegal byte sequence`：

```bash
g++ -std=c++14 -finput-charset=GBK -fexec-charset=GBK main.cpp -o main
# Dev-C++：工具 → 编译选项 → 勾选「编译时加入以下命令」→ 填入上面两个参数
```

**方案 C（临时验证，不改代码）**：在 cmd / PowerShell 里先执行 `chcp 65001`，再运行程序。只对当前窗口有效，适合快速判断问题是不是出在代码页。

**各环境速查**

| 环境 | 编辑器里乱码 | 运行时输出乱码 |
| --- | --- | --- |
| Dev-C++ | 文件 → 另存为 → 编码选 **UTF-8 (BOM)**；工具 → 编辑器选项 → 默认编码 UTF-8 | 用方案 A；控制台字体别用点阵字体 |
| Visual Studio | 文件 → 高级保存选项 → `Unicode (UTF-8 带签名) - 代码页 65001` | 方案 A；项目属性 → C/C++ → 命令行加 `/utf-8` |
| VS Code | 右下角 UTF-8 → 通过编码保存（VS Code 默认已是 UTF-8） | 集成终端先 `chcp 65001`，或直接用方案 A |
| MSVC 编译 | 加 `/utf-8` 编译选项，或给文件加 BOM | 同左 + 方案 A |

> **别踩的坑**：`system("chcp 65001 > nul")` 会闪黑框且不一定生效；`std::locale("")` / `std::wcout` 在 MinGW 上支持不稳定，初学阶段不如直接调 `SetConsoleOutputCP`。另外 `u8"..."` 只保证字面量是 UTF-8 字节，**并不能**改变控制台的解码方式。

---

## 10. 配套综合示例

见同目录 `cpp_oop_demo.cpp`，按编号覆盖：

1. 类、封装、`const` 成员函数、`static` 成员
2. 复制构造的三种调用时机（复制构造 vs 复制赋值对照）
3. 浅复制：打印两个对象共享同一块内存的地址（用 `disown()` 避免真的崩溃，可自行注释掉并用 ASan 复现）
4. 深复制 + Rule of Five + `std::move`
5. 继承、构造/析构顺序、`virtual` 析构、多态与对象切片
6. `Rule of Zero`：`std::vector` / `std::string` 等标准库成员托管资源

> **编码提示**：`cpp_oop_demo.cpp` 为 **UTF-8 带 BOM**，且 `main()` 已按 9.4 方案 A 设置好控制台代码页，Windows 下直接编译运行即可正常显示中文。若你的 Dev-C++ 太老不认 BOM，改用同目录的 `cpp_oop_demo_gbk.cpp`（GBK 编码版，编译时需加 `-finput-charset=GBK -fexec-charset=GBK`）。

> 建议学习顺序：第 1、2 章 → 第 3 章（重点）→ 第 5、6 章 → 第 4、7 章 → 第 8、9 章。第 3 章的深复制代码务必自己敲一遍并加上打印语句观察调用次数。

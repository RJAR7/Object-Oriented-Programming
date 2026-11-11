# C++ 面向对象程序设计 · 教材同步版知识点手册

> **依据教材**：《C++ 语言程序设计（第 5 版）》目录（你提供的 9 张照片，已整理为 `教材目录_整理版.md`）。
> **章节编号全部按教材**：`4.3.4` 就是教材第 4 章 4.3 节第 4 小节，可直接对着课本找。
> **配套**：`cpp_oop_handbook.html`（按知识体系组织的原版，讲解更展开）、`cpp_oop_demo.cpp` / `cpp_oop_demo_gbk.cpp`（可运行综合示例）。
> **代码约定**：所有片段统一 `using namespace std;`，省略 `std::` 前缀；唯一例外是块作用域的 `using std::swap;`（见 4.3 说明）。
> **术语约定**：本版一律采用教材用语 **复制构造函数**、**深复制 / 浅复制**；「拷贝构造」「深拷贝 / 浅拷贝」是同一概念的其他叫法。

---

## 0. 这份手册怎么用

### 0.1 两个版本的分工

| 文件 | 组织方式 | 适合 |
| --- | --- | --- |
| `cpp_oop_handbook.html`（原版） | 按 C++ 知识体系，由浅入深 | 系统理解、面试准备、查某个机制 |
| **`cpp_oop_handbook_textbook.html`（本版）** | **按教材章 → 节 → 小节编号** | **跟课复习、对着作业/考纲找知识点** |
| `教材目录_整理版.md` | 教材目录纯文本 | 自己划重点、做 checklist |

两份都是离线单文件网页，左侧目录可筛选、代码可一键复制、支持打印。本版**不是**把原版内容换个编号抄一遍：重点章（4/5/7/8）按教材顺序重写并补齐教材专有考点，非重点章给出要点与「了解即可」的边界。

### 0.2 覆盖度标记

| 标记 | 含义 |
| --- | --- |
| ✅ | 原版手册已覆盖，本版按教材编号重排 |
| ⚠️ | 原版部分覆盖 / 讲解角度不同，本版已对齐教材 |
| ➕ | **教材有、原版没有** —— 本版新增补齐（考试可能考） |
| ⭐ | **超纲**：原版讲得比教材深，入门课一般不要求，选读 |

### 0.3 术语对照表（考试填空注意）

| 教材用语（本版采用） | 其他常见叫法 | 说明 |
| --- | --- | --- |
| 复制构造函数 | 拷贝构造函数、copy constructor | 你最初写的 `A(const A& a)` 就是它，教材 4.3.4 |
| 深复制 / 浅复制 | 深拷贝 / 浅拷贝、深层复制 / 浅层复制 | 教材在 **6.5** 讲，不在第 4 章 |
| 类成员的访问控制 | 访问权限 | `public` / `protected` / `private` |
| 常对象 / 常成员函数 | const 对象 / const 成员函数 | 教材 5.5 |
| 常引用 | const 引用 | 教材 5.5.3 |
| 静态函数成员 | 静态成员函数 | 教材 5.3.2 |
| 类型兼容规则 | 里氏替换、向上转型 | 教材 7.3 |
| 作用域分辨符 | 作用域限定符、`::` 运算符 | 教材 7.5.1 |
| 包含多态 | 运行期多态、动态多态 | 教材 8.1.1，靠虚函数实现 |
| 抽象类 | 抽象基类 | 教材 8.4.2，含纯虚函数 |
| 类的组合 | 组合 / 聚合、has-a | 教材 4.4 |

> **最容易吃亏的一点**：教材把「深复制与浅复制」放在 **6.5**（数组指针章），而原版手册把它并进第 3 章一起讲。复习时请按 6.5 找，但**概念要和 4.3.4 复制构造函数连起来理解**——浅复制正是默认复制构造的行为。

### 0.4 按课时权重的复习顺序

1. **第 4 章 类与对象**（最核心）：类定义 → 访问控制 → 构造/析构 → **4.3.4 复制构造函数** → 组合
2. **第 5 章 数据的共享与保护**：`static` / `const` / 友元 / 作用域，选择题高频
3. **第 7 章 继承** → **第 8 章 多态**：两者连着考，虚函数和虚析构是大题常客
4. **6.5 深复制与浅复制**：回头补，配合 4.3.4
5. 第 1 / 2 / 3 章：概念与语法，了解或快速复习
6. 第 9 ~ 12 章：模板、STL、流、异常，多为了解性内容（依老师划的范围）

---

### 0.5 代码风格约定（依据教材 p238–240 / p292–293）

> 依据你提供的 5 张「代码风格」照片整理，完整规则与教材原码摘录见 `教材代码风格_整理版.md`。

| 项目 | 教材实际写法 | 本手册采用的写法 |
| --- | --- | --- |
| `std::` 前缀 | `.h` 里全限定 `std::string`；`.cpp` 里 `using namespace std;` 后用裸名字 | **统一 `using namespace std;`**（按你的要求省略 `std::`）；唯一例外是 4.3.4 的 `using std::swap;` |
| 注释 | 中文行尾注释、注释列对齐、函数组前有段注释 | **一致，且比教材更详细**：短注释扩写成「为什么」，重点代码块前加 3–5 行观察点 |
| 术语 | 复制构造 / 深复制 / 浅复制 | **一致**（全稿统一，对照表见 0.3） |
| 数据成员命名 | 不带下划线：`id`、`balance`、`rate` | 保留 `id_`、`r_`、`data_` 等后缀 |
| 构造函数形参 | 与成员同名：`: year(year), month(month)` | 用 `n` / `r` / `v` 区分：`: r_(r)` |
| 大括号 / 缩进 | K&R、访问控制符顶格、4 空格 | **一致** |
| 头文件保护 | `#ifndef __ACCOUNT_H__` | 用 `POINT_H`（双下划线开头是 C++ 保留标识符，工程上不推荐） |

> **为什么命名没按教材改**：教材让形参与成员同名，函数体里必须靠 `this->` 区分，漏写就变成自我赋值；改成 `size` 还会和现有的 `size()` 成员函数撞名。考试答题按教材写没问题，本手册为避免示例出歧义保留了下划线后缀。需要全部改成教材命名，说一声即可。

**教材风格原码片段**（`account.h` —— 注意 `.h` 里不写 `using`，这是全稿唯一出现 `std::` 的地方，仅作对照）：

```cpp
//account.h
// 片段：教材原码摘录，依赖同项目的 date.h，单独编译会找不到头文件
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include <string>
class SavingsAccount {          //储蓄账户类
private:
    std::string id;             //账号
    double balance;             //余额
    double rate;                //存款的年利率
public:                         //公有接口
    //构造函数
    SavingsAccount(const Date &date, const std::string &id, double rate);
    const std::string &getId() const { return id; }
    double getBalance() const { return balance; }
    //存入现金
    void deposit(const Date &date, double amount, const std::string &desc);
    //显示账户信息
    void show() const;
};
#endif //__ACCOUNT_H__
```

> 对照：本手册的类定义写成 `using namespace std;` + `string id_;` + 更详细的中文注释 —— 形式不同，知识点完全一致。**`using namespace std;` 只能写在 `.cpp` 里**，写进头文件会污染所有包含它的源文件（原版手册 0.1 节有详细说明）。

---

## 1. 教材章节 ↔ 手册章节 对照表

> 「原版章节」指 `cpp_oop_handbook.html` 的编号；「本版位置」是本文件的小节号。

| 教材章节 | 原版章节 | 覆盖 | 本版位置 | 说明 |
| --- | --- | --- | --- | --- |
| 第 1 章 绪论 | 0. 总览 | ⚠️ | 第 2 节 | 原版缺「面向对象方法、软件开发过程、信息表示与存储」，属了解性内容 |
| 第 2 章 C++ 简单程序设计 | — | ➕ | 略 | 语法基础，非 OOP 范围；`auto`/`decltype`/`constexpr` 见原版 8 章简述 |
| 第 3 章 函数 | — | ➕ | 第 3 节 | **参数传递（值/引用/常引用）是复制构造的前置知识**，本版补 |
| **第 4 章 类与对象** | 1、2、3、4 | ✅ | **第 4 节** | 核心。4.3.4 复制构造 = 原版第 3 章，本版沿用教材用语重写 |
| 4.4 类的组合 | — | ➕ | 4.5 | 原版几乎没有，教材单独一节，常考构造顺序 |
| 4.5 UML 图形标识 | — | ➕ | 4.6 | 原版没有，读图题会考 |
| 4.6 / 4.7 结构体、联合体、枚举 | — | ➕ | 4.7 | 原版没有 |
| 4.9 位域 / 构造类型转换 / 对象传递 | 1.5、3.7 | ⚠️ | 4.8 | `explicit` 已覆盖；位域、对象作为返回值传递需补 |
| **第 5 章 数据的共享与保护** | 1.6（部分） | ⚠️ | **第 5 节** | 静态成员、友元已覆盖；**作用域/可见性/生存期/常对象/多文件结构全缺** |
| 第 6 章 数组、指针与字符串 | 4.2（部分） | ⚠️ | 第 6 节 | 智能指针已覆盖；对象数组/对象指针/动态分配/`string` 需补 |
| **6.5 深复制与浅复制** | 3.3 / 3.4 | ✅ | 6.2 | 内容一致，但教材位置在 6.5 |
| **第 7 章 类的继承** | 5 | ⚠️ | **第 7 节** | 三种继承、菱形继承已覆盖；**类型兼容规则、作用域分辨符、虚基类**需补 |
| **第 8 章 多态性** | 6、7 | ⚠️ | **第 8 节** | 虚函数/vtable/运算符重载已覆盖；**多态四种类型、重载规则、RTTI**需补 |
| 第 9 章 模板与群体数据 | 8（简述） | ⚠️ | 第 9 节 | 教材讲得比原版细（数组类、链表类、栈、队列、排序查找） |
| 第 10 章 泛型与 STL | 8（简述） | ⚠️ | 第 9 节 | 迭代器、容器、函数对象、算法 |
| 第 11 章 流类库与输入输出 | — | ➕ | 第 9 节 | 原版没有，教材有整章 |
| 第 12 章 异常处理 | 8（简述） | ⚠️ | 第 9 节 | 教材含异常安全、`noexcept`、资源泄露 |
| 原版 4 移动语义 / RAII | 4 | ⭐ | 4.4 | 教材 4.3.6 / 12.6 有浅尝，**Rule of Five、智能指针偏深** |
| 原版 9 面试问答 / 速查 | 9 | ⭐ | 第 12 节 | 超出课程，但适合期末与面试 |

---

## 2. 第 1 章 绪论：面向对象的基本概念（了解）

### 2.1 四大基本特点（教材 4.1 会再展开）

| 特点 | 一句话 | C++ 里的对应物 |
| --- | --- | --- |
| 抽象 | 只暴露必要特征，忽略细节 | 类（`class`）、`public` 接口 |
| 封装 | 数据与操作捆绑，隐藏实现 | `private` / `protected` + 成员函数 |
| 继承 | 在已有类上扩展，复用代码 | `class B : public A` |
| 多态 | 同一接口，不同实现 | 虚函数 `virtual`、运算符重载 |

**面向过程 vs 面向对象**（教材 1.2）：面向过程以「函数/步骤」为中心，数据是分散的；面向对象以「对象」为中心，数据和方法绑在一起，通过消息（调用成员函数）交互。

```cpp
#include <iostream>
using namespace std;

// 面向过程：数据和函数分离
double r = 3.0;
double area_of(double radius) { return 3.14159 * radius * radius; }

// 面向对象：数据 + 行为封装进类
class Circle {
    double radius_;              // 数据成员私有：外部不能直接读写，只能通过 public 接口间接访问
public:
    explicit Circle(double r) : radius_(r) {}
    double area() const { return 3.14159 * radius_ * radius_; }
    void setRadius(double r) { radius_ = r; }
    double radius() const { return radius_; }
};

int main() {
    cout << area_of(r) << '\n';  // 数据裸露在全局，任何代码都能改，无法保证取值合法
    Circle c(3.0);
    cout << c.area() << '\n';    // 访问被收敛到成员函数，类可在其中校验并维护不变量
}
```

### 2.2 教材其余小节（了解，不考代码）

- **1.1** 机器语言 → 汇编 → 高级语言 → 面向对象语言；**1.3** 面向对象的软件开发：分析 → 设计 → 编程 → 调试 → 维护。
- **1.4 信息的表示与存储**：二/八/十/十六进制转换、原码/反码/补码、定点数与浮点数、ASCII/汉字编码 —— 属计算机基础，常出选择题，与 C++ 语法无关。
- **1.5** 源程序 / 目标程序 / 翻译程序、编辑→编译→连接→运行。连接（link）这一步在教材 5.8.2 还会细讲。

---

## 3. 第 3 章 函数：OOP 的前置知识（➕ 补齐）

### 3.1 三种参数传递 ★

这是理解复制构造函数的关键：值传递会**复制对象**，引用传递不会。

```cpp
#include <iostream>
using namespace std;

void byValue(int x)      { x = 100; }         // 值传递：形参是实参的独立副本，函数内修改形参不影响外部
void byRef(int& x)       { x = 100; }         // 引用传递：形参是实参的别名，不产生复制，修改会反映到外部
void byConstRef(const int& x) { cout << x; }  // const 引用：不复制、不可改、还能绑定临时对象，传类对象的首选

int main() {
    int a = 1;
    byValue(a);     cout << a << '\n';        // 1
    byRef(a);       cout << a << '\n';        // 100
    byConstRef(a);
}
```

| 方式 | 是否复制对象 | 能否改实参 | 传类对象时 |
| --- | --- | --- | --- |
| `void f(A a)` | 是 | 否 | **调用复制构造函数**，开销大 |
| `void f(A& a)` | 否 | 是 | 高效，但可能误改 |
| `void f(const A& a)` | 否 | 否 | **推荐**，且能接收临时对象 |

> 结论：类对象作参数，一律写 `const A&`。这既解释了为什么复制构造函数自己必须写成 `A(const A& a)`，也解释了教材 4.9.3「对象作为函数参数和返回值的传递方式」。

### 3.2 其余要点（教材 3.2 ~ 3.7）

- **内联函数** `inline`：建议编译器在调用点展开，省去调用开销；适合短小函数，类内定义的成员函数**默认内联**。
- **`constexpr` 函数**：编译期即可求值，能用于常量表达式；教材 2.2.5 也有 `constexpr` 常量。
- **带默认形参值的函数**：默认值从右往左连续给；**只能在声明处给一次**（通常放头文件），定义处不能再写。
- **函数重载**：同一作用域内名字相同、参数表不同（类型/个数/顺序）；**仅返回值不同不能重载**。
- **3.7.1 运行栈**：每次函数调用压入一个栈帧（形参、局部变量、返回地址），返回时弹出 —— 理解「局部对象析构时机」和「为什么不能返回局部对象的引用」的基础。

---

## 4. 第 4 章 类与对象【核心 · 权重最高】

### 4.1 类的定义、访问控制与对象（教材 4.2）

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:                                   // class 成员默认 private；改成 struct 则默认 public（教材 4.6）
    string name_;
    int score_ = 0;                        // C++11 类内初值：构造函数未显式初始化该成员时采用它
public:
    explicit Student(string n) : name_(n) {}
    void setScore(int s) { score_ = s; }   // 类内定义的成员函数被隐式 inline（只是给编译器的展开建议）
    int  score() const { return score_; }  // const 成员函数：承诺不修改对象；常对象只能调用这类函数
    void print() const;                    // 类内仅声明，定义在类外（必须写 类名:: 指明归属）
private:
    int id_ = 0;                           // 访问说明符可多次出现，作用范围到下一个说明符或类结束
};

void Student::print() const {              // 类外定义必须用 类名:: 限定，否则会被当成普通的全局函数
    cout << name_ << ' ' << score_ << '\n';
}

int main() {
    Student s("张三");                     // 栈上对象：离开作用域时由编译器自动调用析构函数
    s.setScore(90);
    s.print();
    // s.score_ = 100;                    // 编译错误：private
    Student* p = new Student("李四");      // 堆上对象：new 触发构造，必须配对 delete 才会触发析构
    delete p;
}
```

| 访问属性 | 类内成员函数 | 派生类 | 类外（对象.成员） |
| --- | --- | --- | --- |
| `public` | ✅ | ✅ | ✅ |
| `protected` | ✅ | ✅ | ❌ |
| `private` | ✅ | ❌ | ❌ |

- `class` 默认 `private`，`struct` 默认 `public`（见 4.7）。
- **对象**是类的实例；每个对象有独立的数据成员，成员函数代码只有一份，靠隐含的 `this` 指针区分是谁在调用。
- `this` 是指向当前对象的常量指针（`A* const`）；常成员函数里是 `const A* const`。

### 4.2 构造函数与析构函数全家族（教材 4.3.1 ~ 4.3.5）

**必须用初始化列表的三种情况**：`const` 成员、引用成员、没有默认构造函数的类类型成员。初始化列表的顺序**由成员声明顺序决定**，与书写顺序无关。

```cpp
#include <iostream>
using namespace std;

class Point {
    int x_, y_;
public:
    Point() : Point(0, 0) { cout << "默认构造(委托)\n"; }  // 委托构造（教材 4.3.3）：复用同类另一个构造函数，避免重复初始化代码
    Point(int x, int y) : x_(x), y_(y) { cout << "带参构造\n"; }
    Point(const Point& p) : x_(p.x_), y_(p.y_) { cout << "复制构造\n"; }
    ~Point() { cout << "析构\n"; }
    void show() const { cout << x_ << ',' << y_ << '\n'; }
};

int main() {
    Point a(1, 2);
    Point b(a);                                            // 复制构造：用一个已有对象初始化新对象（教材 4.3.4 重点）
    Point c = a;                                           // 同样是「定义并初始化」，不是赋值，因此仍调用复制构造函数
}
```

| 函数 | 触发时机 | 默认行为 |
| --- | --- | --- |
| 默认构造函数 | `A a;` / `new A` | 不写任何构造函数时编译器才合成；成员按类内初值/默认初始化 |
| 带参构造函数 | `A a(1);` | 一旦写了任意构造函数，默认构造函数就不再自动提供 |
| 委托构造函数 | 一个构造函数调用同类的另一个 | C++11，避免重复初始化代码 |
| 析构函数 `~A()` | 对象生命周期结束 / `delete` | 逆序调用成员析构；**不释放指针成员指向的堆内存**，要自己 `delete` |

**构造顺序**：基类 → 成员对象（按声明顺序）→ 派生类自身；**析构顺序完全相反**。有虚函数时，基类析构函数必须声明为 `virtual`（见 8.3）。

### 4.3 ⭐ 复制构造函数 `A(const A& a)`（教材 4.3.4，你点名的重点）

#### 4.3.1 签名逐字拆解

```cpp
class A {
public:
    A(const A& a);  // 复制构造函数：无返回类型、函数名 == 类名、参数是本类 const 引用
};
```

| 部件 | 为什么必须这样 |
| --- | --- |
| **没有返回类型** | 构造函数都不写返回类型，连 `void` 都不能写 |
| **名字 = 类名 `A`** | 构造函数专属规则 |
| **参数必须是 `A&` 引用** | 若写 `A(A a)`，传参时又要复制实参 → 又要调复制构造 → **无限递归**，编译器直接报错 |
| **`const`** | ① 不修改源对象；② 能接收 `const A` 对象和临时对象（右值），否则 `A b = makeA();` 会失败 |
| 可以带额外参数 | `A(const A& a, int n = 0)` 仍是复制构造，但极少用 |

#### 4.3.2 三种调用时机（必背）

```cpp
// 示例 4-3：复制构造函数的三种调用时机（对应教材 4.3.4）
// 观察点：(1) 定义新对象并用已有对象初始化；(2) 实参按值传给形参；
//         (3) 函数按值返回对象 —— 这三种都会调用复制构造函数。
// 易错：z = x 中 z 已存在，走的是复制赋值运算符，不是复制构造。
// 提示：加 -fno-elide-constructors 关闭 RVO，才能看全第 (3) 种的调用。

#include <iostream>
using namespace std;

class A {
public:
    A()            { cout << "构造\n"; }
    A(const A& a)  { cout << "复制构造\n"; }
    A& operator=(const A& a) { cout << "赋值运算符\n"; return *this; }
    ~A()           { cout << "析构\n"; }
};

A makeA()  { A t; return t; }  // (3) 返回值（值传递，可能被 RVO 优化掉）
void use(A a) { }              // (2) 值传参

int main() {
    A x;
    A y(x);                    // (1) 用一个已存在对象初始化新对象
    A z = x;                   // (1) 同样是初始化，不是赋值
    use(x);                    // (2) 实参 → 形参，值传递
    A w = makeA();             // (3) 返回对象（C++17 起多数被 RVO 省略）
    z = x;                     // × 不调用复制构造：z 已存在，走的是赋值运算符
}
```

> **① 与赋值的分界线**：变量**定义并同时给初值** → 复制构造；**已存在的对象**被赋值 → 复制赋值运算符。考试常在这里设陷阱。

#### 4.3.3 默认复制构造 = 浅复制（教材 6.5 提前理解）

不写复制构造时，编译器合成一个：对**每个成员逐字节/逐个复制**。指针成员只复制**地址值**，于是两个对象指向同一块堆内存：

```cpp
// 示例 4-4：默认复制构造执行的是浅复制（对应教材 4.3.4 / 6.5）
// 观察点：编译器合成的版本只逐个复制成员，指针成员复制的是「地址值」。
// 结果：a 与 b 的 data_ 指向同一块堆内存，两次析构会 double free。
// 说明：本例只打印地址对比；配套 demo 用安全方式演示，不会真的崩溃。

#include <iostream>
using namespace std;

class Shallow {
    int* data_;
public:
    explicit Shallow(int n) : data_(new int[n]{}) {}
    ~Shallow() { delete[] data_; }
    int* raw() const { return data_; }
};

int main() {
    Shallow a(4);
    Shallow b(a);  // 合成版：b.data_ == a.data_
    cout << (a.raw() == b.raw() ? "地址相同" : "地址不同") << '\n';
    // 函数结束时 b 先 delete，a 再 delete 同一块 → double free，程序崩溃
}
```

> `cpp_oop_demo.cpp` 的 demo3 用安全方式演示了这一点（不会真崩），可用 `-fsanitize=address` 复现。

#### 4.3.4 深复制的两种标准写法

**写法一：传统版（先申请、后释放，异常安全 + 处理自我赋值）**

```cpp
// 示例 4-5：手写深复制 —— 传统写法（对应教材 4.3.4 / 6.5）
// 三条规则：(1) 复制构造中重新 new 并复制内容，绝不与源对象共享地址；
//           (2) 赋值运算先判自我赋值，否则 a = a 会先释放自己的资源；
//           (3) 先申请新内存、成功后再 delete 旧的，保证 new 抛异常时对象不变。

#include <cstring>
#include <cstddef>
using namespace std;

class Buffer {
    size_t size_;
    char*  data_;
public:
    explicit Buffer(size_t n = 0) : size_(n), data_(n ? new char[n]{} : nullptr) {}

    Buffer(const Buffer& rhs)                                   // 深复制：重新申请内存并复制内容，两个对象各自持有独立资源
        : size_(rhs.size_), data_(rhs.size_ ? new char[rhs.size_] : nullptr) {
        if (size_ > 0) memcpy(data_, rhs.data_, size_);
    }

    Buffer& operator=(const Buffer& rhs) {
        if (this != &rhs) {                                     // 防自我赋值：a = a 时若先 delete 会把自己的资源释放掉
            char* tmp = rhs.size_ ? new char[rhs.size_] : nullptr;  // 先申请新内存：若 new 抛异常，原对象仍保持原状（强异常安全）
            if (rhs.size_ > 0) memcpy(tmp, rhs.data_, rhs.size_);
            delete[] data_;                                     // 新资源就绪后才释放旧资源，避免异常让对象停在半毁状态
            data_ = tmp; size_ = rhs.size_;
        }
        return *this;                                           // 返回自身引用，才能支持链式赋值 a = b = c
    }

    ~Buffer() { delete[] data_; }
    size_t size() const { return size_; }
};
```

**写法二：copy-and-swap（更简洁、天然异常安全，推荐）**

```cpp
// 示例 4-6：手写深复制 —— copy-and-swap 惯用法（比传统版更简洁）
// 关键：operator= 的形参按值传递，进函数前已由复制构造完成深复制；
//       随后 swap 交换资源，rhs 带着旧资源在函数结束时被析构自动释放。
// 唯一保留 std:: 之处：using std::swap; 不能省，否则会命中成员函数 swap。

#include <utility>
#include <cstring>
#include <cstddef>
using namespace std;

class Buffer {
    size_t size_ = 0;
    char*  data_ = nullptr;
public:
    explicit Buffer(size_t n = 0) : size_(n), data_(n ? new char[n]{} : nullptr) {}

    Buffer(const Buffer& rhs)
        : size_(rhs.size_), data_(rhs.size_ ? new char[rhs.size_] : nullptr) {
        if (size_ > 0) memcpy(data_, rhs.data_, size_);
    }

    void swap(Buffer& o) noexcept {
        using std::swap;             // 唯一例外：这里不能省略 std::，否则名字查找会命中成员函数 swap(Buffer&) 而编译失败
        swap(size_, o.size_);
        swap(data_, o.data_);
    }

    Buffer& operator=(Buffer rhs) {  // 按值传参：形参 rhs 已由复制构造生成，深复制在进函数前就完成了
        swap(rhs);                   // 交换后 rhs 持有本对象的旧资源，函数结束时由析构函数自动释放
        return *this;
    }
    ~Buffer() { delete[] data_; }
};
```

> **为什么 `using std::swap;` 不能省**：成员函数本身就叫 `swap`，非限定名字查找会在类作用域命中 `Buffer::swap(Buffer&)` 就停下，不会去全局找 `std::swap`，参数对不上直接编译失败。这是全书唯一保留 `std::` 的地方。

#### 4.3.5 Rule of Three / Five / Zero

| 法则 | 内容 | 适用 |
| --- | --- | --- |
| **Rule of Three** | 需要手写「析构 / 复制构造 / 复制赋值」中的任一个，通常三个都要手写 | 管理裸资源的类 |
| **Rule of Five** ⭐ | C++11 再加「移动构造 / 移动赋值」，共五个特殊成员函数 | 需要高性能移动时 |
| **Rule of Zero** ⭐ | 用 `vector` / `string` / `unique_ptr` 等标准库成员管理资源，**什么都不用手写**，编译器合成的版本天然正确 | 现代 C++ 首选 |

```cpp
#include <vector>
#include <string>
#include <cstddef>
using namespace std;

class Playlist {            // Rule of Zero
    vector<string> songs_;  // 资源交给标准库成员管理：编译器合成的复制/移动/析构天然正确（Rule of Zero）
public:
    void add(string s) { songs_.push_back(s); }
    size_t size() const { return songs_.size(); }
    // 五个特殊成员函数全部由编译器生成，且天然正确
};
```

> 教材只在 4.3.6 简单提了移动构造；Rule of Five / Zero 属**⭐ 超纲**，写在这里是为了让你知道「现代工程里更推荐别手写复制构造」。考试仍按教材要求写深复制。

#### 4.3.6 高频易错点

1. `A a();` 是**函数声明**不是定义对象（most vexing parse）；写 `A a;` 或 `A a{};`。
2. `A b = a;` 是复制构造，`b = a;` 是赋值 —— 别混。
3. 复制构造参数写成 `A(A a)` 会无限递归，必须 `const A&`。
4. 类里有指针成员 + 手写析构，一定要检查三个法则。
5. 复制构造里别忘记初始化**所有**成员，尤其新增成员时。
6. 返回值优化（RVO/NRVO）会省略复制构造，**别把副作用写进复制构造函数**（例如靠打印计数判断调用次数会不准）。
7. 派生类的复制构造要显式调用基类：`D(const D& d) : B(d), member_(d.member_) {}`（教材 7.4.2）。

### 4.4 移动构造与 `default` / `delete`（教材 4.3.6 ~ 4.3.7）

```cpp
#include <utility>
using namespace std;

class A {
public:
    A() = default;                                            // = default：显式要求编译器按默认规则生成该特殊成员函数
    A(const A&) = default;                                    // = default 生成的仍是浅复制；含裸指针时不要这样写
    // A(const A&) = delete;                                  // 二选一：与上一行只能留一个，否则重复声明会编译报错
    A(A&& rhs) noexcept { /* 窃取 rhs 资源，把 rhs 置空 */ }  // 移动构造 A(A&&)：接管右值对象的资源，不复制；教材 4.3.6
    A& operator=(A&& rhs) noexcept { return *this; }          // 移动赋值：释放自身旧资源后接管右值资源，通常标 noexcept
};
```

- **移动构造 `A(A&&)`**：参数是右值引用，直接「接管」临时对象的资源而不复制，典型场景 `vector` 扩容、`std::move`。
- `= default` 只能用于特殊成员函数；`= delete` 可用于任意函数，用来禁止某些调用（如 `unique_ptr` 禁止复制）。
- ⭐ 移动语义、`noexcept`、智能指针、RAII 在教材里只是浅尝，原版手册第 4 章讲得较深，**入门课选读**。

### 4.5 ➕ 类的组合与前向引用声明（教材 4.4，原版缺）

**组合**：一个类的数据成员是另一个类的对象（`has-a`）。

```cpp
#include <iostream>
using namespace std;

class Engine {
public:
    Engine() { cout << "Engine 构造\n"; }
    ~Engine() { cout << "Engine 析构\n"; }
};

class Car {
    Engine engine_;  // 组合成员（has-a）：构造时先于本类、按声明顺序初始化
    int    wheels_;
public:
    Car() : engine_(), wheels_(4) { cout << "Car 构造\n"; }
    ~Car() { cout << "Car 析构\n"; }
};                   // 构造顺序：组合成员 → 本类；析构顺序严格相反

int main() { Car c; }
```

- 组合成员的初始化**必须放在初始化列表**（若它没有默认构造函数，则必须在列表中显式给参数）。
- 构造顺序：组合成员按**声明顺序**先构造，再执行本类构造函数体；析构严格逆序。
- **判断口诀**：`is-a` 用继承，`has-a` 用组合；能组合就别继承（教材 7.8.1 会再讲）。

**前向引用声明**：`class B;` 只告诉编译器「B 是个类」，用于打破相互引用。

```cpp
class B;                          // 前向声明：只告诉编译器「B 是个类」，此时 B 仍是不完整类型
class A {
    B* pb_;                       // ✅ 可以：指针/引用的大小与 B 的定义无关
    B& rb_;                       // ✅ 可以（引用成员必须在初始化列表初始化）
public:
    A(B* p, B& r) : pb_(p), rb_(r) {}
    // void f() { pb_->g(); }  // ❌ 不完整类型，不能访问 B 的成员
    // B b_;                    // ❌ 不能定义对象，编译器不知道要分配多少内存
};

class B { public: void g() {} };  // 完整定义之后才能使用 B 的成员
```

> 常考结论：前向声明**只能**用于声明指针、引用、函数参数/返回类型；不能定义对象、不能访问成员、不能做 `sizeof`。

### 4.6 ➕ UML 图形标识（教材 4.5，原版缺）

UML 类图用**三段矩形**表示类：

```text
┌───────────────────────────┐
│         Student           │  ← 类名（斜体 = 抽象类）
├───────────────────────────┤
│ - name : string           │  ← 属性（数据成员）
│ - score : int = 0         │
├───────────────────────────┤
│ + Student(n : string)     │  ← 操作（成员函数）
│ + setScore(s : int) : void│
│ + score() : int {const}   │
└───────────────────────────┘
```

| 符号 | 含义 |
| --- | --- |
| `+` / `-` / `#` | `public` / `private` / `protected` |
| 斜体类名 / 斜体方法 | 抽象类 / 纯虚函数 |
| 实线 + 空心三角（指向父类） | **继承**（泛化 generalization） |
| 实线 + 空心菱形（指向整体） | **聚合**：弱拥有，部分可独立存在 |
| 实线 + 实心菱形（指向整体） | **组合**：强拥有，生命周期一致 |
| 实线 + 箭头 / 普通实线 | 关联 / 依赖（虚线箭头） |
| 数字 `1`、`0..*`、`1..*` | 多重性 |

> 教材 4.5.2 的读图题常问「A 与 B 是什么关系」「某个成员可见性」——记住**空心三角=继承、实心菱形=组合**就能拿分。

### 4.7 ➕ 结构体、联合体、枚举、位域（教材 4.6 / 4.7 / 4.9.1，原版缺）

```cpp
#include <iostream>
using namespace std;

struct Point {                            // struct 默认 public
    int x, y;                             // class 里这两行会是 private
};

union Value {                             // union 的所有成员共用同一块内存：改写一个成员会覆盖其他成员
    int   i;
    float f;
    char  c[4];
};                                        // sizeof(Value) == 最大成员的大小

enum Color { RED, GREEN, BLUE };          // 不限定作用域枚举，RED 会泄漏到外层作用域
enum class Level { LOW = 1, HIGH = 10 };  // C++11 作用域枚举，必须写 Level::LOW

struct Flags {                            // 位域（教材 4.9.1）：按 bit 而非字节分配成员，常用于标志位压缩
    unsigned int readable   : 1;
    unsigned int writable   : 1;
    unsigned int mode       : 3;          // 只能存 0~7
};

int main() {
    Point p{1, 2};
    Value v; v.i = 65;
    cout << v.c[0] << '\n';               // 同一块内存被按 char 解读
    cout << sizeof(Value) << ' ' << sizeof(Flags) << '\n';
    Level l = Level::HIGH;                // 不限定作用域枚举不能这样写
}
```

| 对比 | `struct` | `class` |
| --- | --- | --- |
| 默认访问权限 | `public` | `private` |
| 默认继承方式 | `public` | `private` |
| 其他 | **完全相同**（都能有构造、析构、虚函数、继承） | 同左 |

> 易错：`class D : B` 默认是**私有继承**，`struct D : B` 默认是公有继承（教材 7.2）。

### 4.8 构造类型转换与对象传递方式（教材 4.9.2 / 4.9.3）

```cpp
#include <iostream>
using namespace std;

class A {
    int v_;
public:
    explicit A(int v) : v_(v) {}
    int get() const { return v_; }
};

void f(const A& a) { cout << a.get() << '\n'; }

int main() {
    A a(1);
    // f(5);        // ❌ explicit 禁止 int → A 的隐式转换
    f(A(5));  // ✅ 显式构造
    // A b = 5;     // ❌ 去掉 explicit 才允许（教材 4.9.2）
}
```

- **单参数构造函数**定义了「其他类型 → 本类」的隐式转换；加 `explicit` 可关闭，避免 `f(5)` 这种意外转换。
- **对象作为函数参数**：值传递触发复制构造 → 用 `const A&`；**作为返回值**：值返回可能触发复制构造，但编译器通常做 RVO/NRVO 优化；返回局部对象的引用/指针是严重错误。

---

## 5. 第 5 章 数据的共享与保护【核心】

### 5.1 ➕ 作用域、可见性与生存期（教材 5.1 / 5.2，原版缺）

| 作用域 | 范围 |
| --- | --- |
| 函数原型作用域 | 函数声明中形参名只在声明内有效 |
| 块作用域 | `{}` 内声明，从声明处到块结束 |
| 类作用域 | 类的成员在整个类内可见，类外用 `类名::` 或 `对象.` |
| 命名空间作用域 | 命名空间/全局，跨文件可用 `extern` 声明 |

**可见性规则**：内层同名标识符**屏蔽**外层；被屏蔽的外层名字可用 `::name`（全局）或 `Base::f()`（基类）访问。

```cpp
#include <iostream>
using namespace std;

int x = 1;                            // 命名空间作用域，静态生存期
void f() {
    int x = 2;                        // 屏蔽全局 x
    cout << x << ' ' << ::x << '\n';  // 2 1
    static int count = 0;             // 静态生存期：只初始化一次，跨调用保留
    cout << ++count << '\n';
}
int main() { f(); f(); }              // 输出 2 1 / 1 / 2 1 / 2
```

| 生存期 | 对象 | 初始化时机 |
| --- | --- | --- |
| **静态生存期** | 全局变量、`static` 局部变量、类的静态数据成员 | 程序首次执行到定义处（全局在 main 前） |
| **动态生存期** | 局部自动对象、`new` 出来的对象 | 声明处 / `new` 处；结束于 `}` / `delete` |

### 5.2 静态成员与友元（教材 5.3 / 5.4，原版 1.6 已覆盖）

```cpp
#include <iostream>
using namespace std;

class Counter {
    static int total_;                     // 静态数据成员属于类而非对象：全类只有一份，必须在类外定义一次
    int id_;
public:
    explicit Counter(int id) : id_(id) { ++total_; }
    static int total() { return total_; }  // 静态函数成员没有 this：只能访问静态成员，不能是 const / virtual
    friend void peek(const Counter& c);    // 友元函数不是成员函数，但被授权访问本类私有成员（单向、不可继承）
};
int Counter::total_ = 0;                   // 静态数据成员必须在某个 .cpp 中类外定义一次；写在头文件里会被重复定义

void peek(const Counter& c) { cout << c.id_ << '\n'; }

int main() {
    Counter a(1), b(2);
    cout << Counter::total() << '\n';      // 2，也可写 a.total()
    peek(a);
}
```

- 静态数据成员**不属于任何对象**，`sizeof(对象)` 不含它；必须在类外定义一次。
- 静态函数成员没有 `this`，不能调用非静态成员，也不能是 `const` / `virtual`。
- **友元**：`friend` 破坏了封装，是单向、不可继承、不可传递的。友元类 `friend class B;` 让 B 的所有成员函数都能访问本类私有成员。

### 5.3 ➕ 常对象、常成员、常引用（教材 5.5，原版部分覆盖）

```cpp
#include <iostream>
using namespace std;

class A {
    int v_;
    mutable int calls_ = 0;                    // mutable 成员是例外：即使在 const 成员函数里也允许修改（常用于缓存/计数）
public:
    explicit A(int v) : v_(v) {}
    int  get() const { ++calls_; return v_; }  // const 成员函数：承诺不修改对象；常对象只能调用这类函数
    void set(int v) { v_ = v; }                // 非常成员函数
};

void show(const A& a) {                        // const 引用作参数：不复制、不可改，还能绑定临时对象（教材 5.5.3）
    cout << a.get() << '\n';
    // a.set(3);                // ❌ 常对象只能调用常成员函数
}

int main() {
    const A a(5);                              // 常对象必须在定义时初始化，且此后只能调用 const 成员函数
    show(a);
    A b(1);
    show(b);                                   // 非常对象也能绑定 const 引用
}
```

| 形式 | 含义 |
| --- | --- |
| `const A a(5);` | 常对象，只能调用常成员函数 |
| `int f() const;` | 常成员函数，不能修改非 `mutable` 数据成员，也不能调用非常成员函数 |
| `const int* p` / `int* const p` | 指向常量的指针 / 常量指针（看 `const` 在 `*` 哪侧） |
| `const A&` | 常引用，类对象传参首选 |
| `mutable` | 允许在常成员函数里修改（如缓存、访问计数） |

> **声明原则（教材 5.8.1）**：不修改数据成员的成员函数**一律加 `const`**，否则常对象/常引用用不了它。`const` 也是函数重载的区分依据。

### 5.4 ➕ 多文件结构与编译预处理（教材 5.6，原版缺）

一个典型工程按「**声明放 .h，定义放 .cpp**」组织：

```text
Point.h      → class Point { ... }; 成员函数声明
Point.cpp    → #include "Point.h" + 成员函数定义
main.cpp     → #include "Point.h" + 使用 Point
```

```cpp
// Point.h —— 头文件保护，防止同一编译单元重复包含
#ifndef POINT_H
#define POINT_H
class Point {
public:
    explicit Point(int x);
    int get() const;
private:
    int x_;
};
#endif
```

| 预处理命令 | 作用 |
| --- | --- |
| `#include <...>` / `#include "..."` | 尖括号找系统库，双引号先找当前目录 |
| `#define` / `#undef` | 宏定义 / 取消；**没有类型检查**，能用 `const`/`inline` 就别用宏 |
| `#ifndef` / `#define` / `#endif` | 头文件保护（或 `#pragma once`） |
| `#ifdef` / `#if` / `#else` | 条件编译，常用于跨平台与调试开关 |
| `extern int g;` | **声明**外部变量（不分配内存）；定义在且仅在一个 .cpp 中 |

> **5.8.2 编译、连接与执行**：预处理 → 编译（每个 .cpp 单独生成 .obj，此时只检查声明）→ 连接（把各 .obj 和库拼起来，解析外部符号）→ 运行。常见错误「unresolved external symbol」就是**声明了但没定义**，属于连接期错误，不是编译错误。

---

## 6. 第 6 章 数组、指针与字符串（衔接章）

### 6.1 ➕ 对象数组、对象指针、动态内存分配（教材 6.1.4 / 6.2.11 / 6.3，原版缺）

```cpp
#include <iostream>
#include <vector>
using namespace std;

class A {
    int v_;
public:
    A() : v_(0) { cout << "默认构造\n"; }
    explicit A(int v) : v_(v) { cout << "构造 " << v << '\n'; }
    void show() const { cout << v_ << '\n'; }
};

int main() {
    A arr[3];                    // 对象数组需要默认构造函数：每个元素各调用一次，共 3 次
    A arr2[2] = { A(1), A(2) };  // 用初始化列表指定初值

    A* p = &arr2[0];             // 对象指针
    p->show();                   // 等价于 (*p).show()
    (p + 1)->show();             // 对象指针也支持算术运算

    A* q = new A(9);             // new 分两步：先分配内存，再自动调用构造函数初始化对象
    q->show();
    delete q;                    // delete 也分两步：先调用析构函数，再释放内存

    A* list = new A[3];          // 数组形式：调用 3 次默认构造
    delete[] list;               // new[] 必须配对 delete[]，混用 delete 是未定义行为（教材 6.3）

    vector<A> v(2);              // 教材 6.4：vector 创建数组对象，自动管理内存
}
```

> 必背配对：`new` ↔ `delete`，`new[]` ↔ `delete[]`。混用是考试与工程里的经典错误。

### 6.2 ⭐ 深复制与浅复制（教材 6.5，原版 3.3 / 3.4）

**教材位置提醒**：这一节在第 6 章，但它讲的就是 4.3.4 默认复制构造的行为，务必连起来看。

| | 浅复制 | 深复制 |
| --- | --- | --- |
| 行为 | 只复制指针**地址值** | 重新申请内存并复制**内容** |
| 结果 | 两个对象共享同一块堆内存 | 两个对象各自独立 |
| 释放 | 第二次 `delete` 同一地址 → **double free / 崩溃** | 各释放各的，安全 |
| 产生方式 | 编译器合成的默认复制构造 | 手写复制构造 + 复制赋值运算符 |
| 典型触发 | 类含 `new` 出来的裸指针成员 | 需要「三法则」/ Rule of Zero |

完整可运行的深复制 `Buffer` 类请直接看 **4.3.4**（传统版 + copy-and-swap 两版），或 `cpp_oop_demo.cpp` 的 demo4。

> 教材 6.8.2 讲「指针安全隐患」、6.8.3 讲 `const_cast`；现代解法是 5.3 的 `const` 正确性 + 智能指针（⭐ 超纲）。

### 6.3 `string` 类（教材 6.6.2）

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "Hello";
    s += " C++";
    cout << s.size() << ' ' << s[0] << ' ' << s.substr(0, 5) << '\n';
    string t = s;                     // string 已自行实现深复制：直接赋值即可，不必像裸指针那样手写复制构造
    t[0] = 'h';
    cout << s << " / " << t << '\n';  // 互不影响
}
```

> 对比 6.6.1 的 C 风格字符数组：`char s[] = "abc";` 需要自己管长度、`strcpy`、结尾 `'\0'`，容易越界。**教材用这个对比引出「为什么需要类」**。

---

## 7. 第 7 章 类的继承【核心】

### 7.1 派生类的定义与生成过程（教材 7.1）

```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    int b_;
public:
    explicit Base(int b) : b_(b) { cout << "Base 构造\n"; }
    virtual ~Base() { cout << "Base 析构\n"; }               // 基类析构必须 virtual：否则通过基类指针 delete 时派生部分不会被析构
    void f() const { cout << "Base::f " << b_ << '\n'; }
};

class Derived : public Base {
    int d_;
public:
    Derived(int b, int d) : Base(b), d_(d) { cout << "Derived 构造\n"; }
    ~Derived() override { cout << "Derived 析构\n"; }
    void f() const { cout << "Derived::f " << d_ << '\n'; }  // 名字隐藏：派生类的同名函数会遮蔽基类所有 f 重载（不是重写，也不是重载）
};
```

**派生类生成过程（教材 7.1.3）**：① 吸收基类成员（构造/析构除外）→ ② 改造基类成员（访问控制、名字隐藏）→ ③ 添加新成员。

### 7.2 三种继承方式的访问控制（教材 7.2）

| 基类成员 \ 继承方式 | `public` 继承 | `protected` 继承 | `private` 继承 |
| --- | --- | --- | --- |
| `public` | `public` | `protected` | `private` |
| `protected` | `protected` | `protected` | `private` |
| `private` | 不可直接访问 | 不可直接访问 | 不可直接访问 |

> 记忆：取「基类权限」与「继承方式」中**更严格**的那个；基类 `private` 永远不可直接访问（但可通过基类 `public`/`protected` 接口间接访问）。`class D : B` 默认 `private` 继承，`struct` 默认 `public`。

### 7.3 ➕ 类型兼容规则（教材 7.3，原版以「对象切片」部分覆盖）

在 `public` 继承下，**派生类对象可以当作基类对象用**（向上转型，安全）：

```cpp
#include <iostream>
using namespace std;

class B { public: virtual void f() const { cout << "B\n"; } virtual ~B() = default; };
class D : public B { public: void f() const override { cout << "D\n"; } void g() const {} };

int main() {
    D d;
    B  b  = d;   // ✅ 派生类对象 → 基类对象：发生【对象切片】，d 的独有部分被切掉
    B* p  = &d;  // ✅ 基类指针指向派生类对象（多态的前提）
    B& r  = d;   // ✅ 基类引用绑定派生类对象
    p->f();      // 动态绑定：p 的静态类型是 B*，运行期经 vtable 调用到 D::f
    // p->g();         // ❌ 通过基类指针只能访问基类成员
    // D* q = &b;      // ❌ 反过来不行：基类对象不是派生类对象
}
```

| 方向 | 是否允许 | 说明 |
| --- | --- | --- |
| 派生 → 基类（对象赋值/指针/引用） | ✅ | 公有继承下的类型兼容 |
| 基类 → 派生（隐式） | ❌ | 需要 `dynamic_cast` 且对象本身确实是派生类（教材 7.8.3 / 8.7.2） |

### 7.4 派生类的构造、复制构造与析构（教材 7.4）

```cpp
// 示例 7-4：派生类的构造、复制构造与析构顺序（对应教材 7.4）
// 易错：派生类复制构造必须在初始化列表显式写 B(o)，
//       否则编译器改调用基类默认构造函数，基类部分就没有被复制。
// 顺序：构造 B → D，析构 D → B；复制构造同样先 B(o) 再复制派生部分。

#include <iostream>
using namespace std;

class B {
    int b_;
public:
    B() : b_(0) {}
    explicit B(int b) : b_(b) {}
    B(const B& o) : b_(o.b_) { cout << "B 复制构造\n"; }
    virtual ~B() { cout << "B 析构\n"; }
};

class D : public B {
    int d_;
public:
    D() : B(), d_(0) {}
    D(int b, int d) : B(b), d_(d) {}
    D(const D& o) : B(o), d_(o.d_) { cout << "D 复制构造\n"; }  // 必须显式 B(o)！
    ~D() override { cout << "D 析构\n"; }
};

int main() { D x(1, 2); D y(x); }
// 构造：B → D；复制构造：B(o) → D；析构：D → B → D → B
```

> **易错**：派生类复制构造函数如果不写 `B(o)`，编译器会自动调用基类的**默认构造函数**，导致基类部分没被复制。教材 7.4.2 专门考这个。
> `= delete` 可用于禁止派生类的某些构造函数（教材 7.4.4）。

### 7.5 作用域分辨符与虚基类（教材 7.5）

```cpp
#include <iostream>
using namespace std;

class B { public: void f() const { cout << "B::f\n"; } };
class D : public B {
public:
    void f() const { cout << "D::f\n"; }                    // 名字隐藏：派生类同名函数遮蔽基类的全部同名重载，与参数表无关
    void call() const {
        f();                                                // D::f
        B::f();                                             // ✅ 用作用域分辨符访问被隐藏的基类同名成员
    }
};

// 菱形继承：不用虚继承会有两份 A 子对象，访问 a.x 产生二义性
class A { public: int x; explicit A(int v = 0) : x(v) {} };
class B1 : virtual public A {};                             // virtual 继承：多条路径共享唯一一份基类子对象，消除菱形继承的二义性
class B2 : virtual public A {};
class C  : public B1, public B2 {
public:
    C(int v) : A(v) {}                                      // 虚基类由最远派生类初始化：中间类 B1/B2 的初始化列表会被忽略
};

int main() { D d; d.call(); C c(7); cout << c.x << '\n'; }  // 只有一份 x
```

- **作用域分辨符 `::`**：访问被隐藏的同名基类成员、类外定义成员函数、访问全局/命名空间名字。
- **虚基类 `virtual public A`**：让多条继承路径共享**唯一一份**基类子对象，消除二义性；**由最远派生类负责初始化虚基类**，中间类的初始化会被忽略。

### 7.6 组合与继承（教材 7.8.1）

| | 继承（`is-a`） | 组合（`has-a`） |
| --- | --- | --- |
| 关系 | 「是一种」，可向上转型 | 「有一个」，黑盒复用 |
| 耦合 | 高（白盒复用，暴露基类细节） | 低（只依赖 `public` 接口） |
| 灵活性 | 编译期确定 | 运行期可替换成员对象 |

> 口诀：**能组合就别继承**。教材 7.8.2 还会讲派生类对象的内存布局（基类子对象在前，新增成员在后）。

---

## 8. 第 8 章 多态性【核心】

### 8.1 ➕ 多态的四种类型（教材 8.1.1，原版只分了两种）

| 类型 | 又称 | 实现机制 | 绑定时机 |
| --- | --- | --- | --- |
| 重载多态 | 专用多态 | 函数重载、运算符重载 | 编译期（静态绑定） |
| 强制多态 | 强制类型转换 | 隐式/显式类型转换 | 编译期 |
| 参数多态 | 泛型 | 函数模板、类模板（第 9 章） | 编译期实例化 |
| **包含多态** | **运行期多态 / 动态多态** | **`virtual` 虚函数 + 基类指针/引用** | **运行期（动态绑定）** |

> 考试爱问「C++ 支持哪几种多态」，按上表四类答；狭义的「多态」通常特指**包含多态**。

### 8.2 运算符重载（教材 8.2，原版第 7 章）

```cpp
#include <iostream>
using namespace std;

class Complex {
    double r_, i_;
public:
    Complex(double r = 0, double i = 0) : r_(r), i_(i) {}
    Complex operator+(const Complex& o) const {                 // 成员函数版本
        return Complex(r_ + o.r_, i_ + o.i_);
    }
    friend ostream& operator<<(ostream& os, const Complex& c);  // 非成员 + 友元
    void show() const { cout << r_ << '+' << i_ << "i\n"; }
};

ostream& operator<<(ostream& os, const Complex& c) {
    return os << c.r_ << '+' << c.i_ << 'i';
}

int main() {
    Complex a(1, 2), b(3, 4);
    cout << (a + b) << '\n';                                    // operator+ 成员版；operator<< 非成员版
}
```

**重载规则（教材 8.2.1，选择题高频）**：

- 不能创造新运算符，只能重载 C++ 已有运算符；**不能改变优先级、结合性、操作数个数**。
- 至少有一个操作数是**自定义类型**（不能重写 `int + int`）。
- **不能重载**：`.`、`.*`、`::`、`?:`、`sizeof`、`typeid` 等。
- 必须是**成员函数**：`=`、`[]`、`()`、`->`；`<<` / `>>` 的第一个操作数是流对象，通常写成**非成员函数 + 友元**。
- 成员函数版左操作数必须是本类对象，且隐含 `this` 占一个参数位置（`a + b` → `a.operator+(b)`，只写一个形参）。

### 8.3 虚函数、虚析构、纯虚函数与抽象类（教材 8.3 / 8.4）

```cpp
// 示例 8-3：虚函数、纯虚函数、抽象类与虚析构（对应教材 8.3 / 8.4）
// 三个条件：基类声明 virtual、派生类签名一致地重写、通过基类指针或引用调用。
// 观察点：p->draw() 的静态类型是 Shape*，运行期经 vtable 调到 Circle::draw()。
// 必背：基类析构必须 virtual，否则 delete p 时派生部分不会被析构。

#include <iostream>
using namespace std;

class Shape {                                    // 抽象类
public:
    virtual double area() const = 0;             // 纯虚函数 = 0：只声明接口；含纯虚函数的类成为抽象类，不能实例化
    virtual void draw() const { cout << "Shape\n"; }
    virtual ~Shape() { cout << "~Shape\n"; }     // 虚析构：通过基类指针释放派生对象时，保证派生析构先执行、基类后执行
    // 若这里不加 virtual，delete 基类指针时只会调用 ~Shape，派生部分泄漏
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }
    void draw() const override { cout << "Circle\n"; }
    ~Circle() override { cout << "~Circle\n"; }  // 析构函数也可标 override：让编译器确认基类析构确实是 virtual
};

int main() {
    Shape* p = new Circle(2.0);
    p->draw();                                   // Circle：动态绑定
    cout << p->area() << '\n';
    delete p;                                    // 虚析构保证析构链完整：先 ~Circle 再 ~Shape，派生部分不会泄漏
}
```

**动态绑定的三个必要条件**：① 基类有 `virtual` 函数；② 派生类**签名完全一致**地重写（用 `override` 让编译器帮你检查）；③ 通过**基类指针或引用**调用。

| 概念 | 要点 |
| --- | --- |
| `virtual` | 声明虚函数；**基类写了，派生类不写也自动是虚函数** |
| `override` | 显式标注重写，签名写错时编译报错（强烈建议） |
| `final` | 禁止继续重写 / 禁止被继承 |
| 纯虚函数 `= 0` | 只给接口；含纯虚函数的类是**抽象类，不能实例化** |
| 虚析构 | 通过基类指针 `delete` 派生对象时，必须虚析构，否则派生部分不析构 |
| **不能是虚函数** | 构造函数、静态成员函数、友元函数；**内联函数可以是虚函数**（`inline` 只是给编译器的建议） |

### 8.4 动态绑定原理与 RTTI（教材 8.7）

- **vtable**：编译器为每个含虚函数的类生成一张虚函数表，对象内隐含一个 `vptr` 指向它；调用 `p->f()` 时通过 `vptr` 查表找到实际类型的函数地址，这就是运行期绑定的开销（一个间接寻址）。
- **RTTI（运行时类型识别）**：`dynamic_cast<D*>(basePtr)` 安全向下转型（失败返回 `nullptr`，引用版抛 `bad_cast`）；`typeid(obj)` 返回 `type_info`，`typeid(*ptr)` 得到动态类型。二者都要求基类**有虚函数**。
- ⭐ 原版手册的 vtable 内存布局讲得更细，属超纲，了解「有虚函数就多一个指针大小」即可。

---

## 9. 第 9 ~ 12 章：了解 / 选读

> 这几章教材讲得比原版手册细，但**多数入门课只考概念与简单应用**。按老师划的范围复习；标 ⭐ 的是明显超纲内容。

| 教材章节 | 必须掌握的要点 | 边界 |
| --- | --- | --- |
| 第 9 章 模板与群体数据 | 函数模板 `template <typename T> T max(T a, T b)`、类模板 `template <class T> class Stack`；实例化发生在编译期 | 数组类/链表类/栈/队列的实现、插入/选择/交换排序属数据结构；⭐ 模板元编程、可变参数模板、模板特化不必深究 |
| 第 10 章 泛型与 STL | STL 四组件：**容器、迭代器、算法、函数对象**；`vector` / `map` / `set` 基本用法；迭代器区间是**左闭右开** `[first, last)` | ⭐ lambda、参数绑定、类型特征、Boost 一般了解即可 |
| 第 11 章 流类库与 I/O | `cout` / `cin` 与插入符 `<<`、提取符 `>>`；`ofstream` / `ifstream` 文件读写；文本方式 vs 二进制方式；`stringstream` | 宽字符与宽流、对象串行化（11.6）属了解 |
| 第 12 章 异常处理 | `try` / `throw` / `catch`；**栈展开**时会调用已构造局部对象的析构；`catch (const exception& e)` 放最后 | ⭐ 异常安全保证、`noexcept`、RAII 防资源泄露是进阶内容（原版 4 章讲了，选读） |

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
T myMax(T a, T b) { return a > b ? a : b; }  // 函数模板（教材第 9 章）：编译期按实参类型实例化，不是运行期多态

int main() {
    vector<int> v{3, 1, 4, 1, 5};            // 容器（第 10 章）
    sort(v.begin(), v.end());                // 算法 + 迭代器
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << ' ';                  // STL 迭代器区间是左闭右开 [begin, end)：end 指向尾后位置，不可解引用
    cout << '\n' << myMax(2, 5) << '\n';     // 实例化为 myMax<int>
}
```

---

## 10. 缺口清单：教材有、原版手册没有（本版已补齐）

| 教材位置 | 考点 | 本版位置 | 常考形式 |
| --- | --- | --- | --- |
| 3.1.3 | 值/引用/常引用参数传递 | 3.1 | 选择、改错 |
| 4.4 | **类的组合**、构造顺序、前向引用声明 | 4.5 | 填空、输出构造/析构顺序 |
| 4.5 | **UML 类图**（可见性符号、四种关系） | 4.6 | 读图题 |
| 4.6 / 4.7 / 4.9.1 | struct / union / enum / 位域 | 4.7 | 选择、`sizeof` |
| 4.9.2 / 4.9.3 | 构造类型转换、对象作为返回值传递 | 4.8 | `explicit`、复制构造调用次数 |
| 5.1 / 5.2 | 作用域、可见性、静态/动态生存期 | 5.1 | 输出题（屏蔽、`static`） |
| 5.5 / 5.8.1 | 常对象、常成员、常引用、`mutable` | 5.3 | 判断合法性 |
| 5.6 / 5.8.2 | 多文件结构、头文件保护、`extern`、编译 vs 连接 | 5.4 | 概念、错误归因 |
| 6.1.4 / 6.2.11 / 6.3 | 对象数组、对象指针、`new[]`/`delete[]` | 6.1 | 构造函数调用次数 |
| 6.6 | `string` 类 | 6.3 | 编程小题 |
| 7.3 | **类型兼容规则** | 7.3 | 判断赋值是否合法 |
| 7.5.1 / 7.5.2 | 作用域分辨符、**虚基类** | 7.5 | 菱形继承二义性 |
| 8.1.1 | **多态的四种类型** | 8.1 | 简答 |
| 8.2.1 | 运算符重载规则、必须成员函数的 4 个运算符 | 8.2 | 选择题高频 |
| 8.7.2 | RTTI / `dynamic_cast` | 8.4 | 概念 |
| 11 / 12 | 流类库、异常处理全章 | 第 9 节 | 依考纲 |

---

## 11. 超纲清单：原版手册有、教材不作要求（⭐ 选读）

| 原版位置 | 内容 | 教材情况 | 建议 |
| --- | --- | --- | --- |
| 4.1 | 左值/右值、`std::move` 深入 | 4.3.6 只提移动构造 | 知道「移动 = 不复制、接管资源」即可 |
| 4.2 | RAII、`unique_ptr` / `shared_ptr` / `weak_ptr` | 12.6.2 提到资源泄露 | 入门课不考；工程里很重要 |
| 3.5 | Rule of Five / **Rule of Zero** | 无 | 选读；考试仍按三法则写深复制 |
| 5.2 / 5.3 | 名字隐藏与 `using`、对象切片深入 | 7.5.1 / 7.3 有简化版 | 概念了解 |
| 6.3 | vtable 内存布局细节 | 8.7.3 有原理 | 知道「查表」即可 |
| 8 | 模板元编程、异常、STL 深入 | 9.5 / 10.9 标为「深度探索」 | 教材自己都标 depth，通常不考 |
| 9.2 | 十个面试高频问答 | 无 | 期末/面试用 |

> 判断原则：教材每章末尾的「**深度探索**」小节（2.6 / 3.7 / 4.9 / 5.8 / 6.8 / 7.8 / 8.7 / 9.5 / 10.9 / 11.6 / 12.6）通常是**拔高内容**，老师不划就先跳过。

---

## 12. 速查与考试易错点

### 12.1 特殊成员函数一览

| 函数 | 签名 | 何时必须手写 |
| --- | --- | --- |
| 默认构造 | `A();` | 需要自定义初始化且还想 `A a;` |
| 复制构造 | `A(const A&);` | **类管理裸资源（指针）时，做深复制** |
| 复制赋值 | `A& operator=(const A&);` | 同上，与复制构造成对出现 |
| 移动构造 ⭐ | `A(A&&) noexcept;` | 需要高效转移资源 |
| 移动赋值 ⭐ | `A& operator=(A&&) noexcept;` | 同上 |
| 析构 | `~A();` | 需要 `delete` 资源 / 基类要 `virtual` |

### 12.2 复制构造高频问答（简答版）

1. **为什么参数必须是引用？** 值传递会再调复制构造，无限递归。
2. **为什么加 `const`？** 不修改源对象，且能接收常对象与临时对象。
3. **`A b = a;` 和 `b = a;` 区别？** 前者初始化（复制构造），后者赋值（复制赋值）。
4. **默认复制构造有什么问题？** 浅复制，指针成员共享内存导致 double free。
5. **什么时候必须手写复制构造？** 类含 `new` 出来的资源 / 需要深复制 / 有引用或 `const` 成员需特殊处理（三法则）。
6. **派生类复制构造怎么写？** `: Base(o), member_(o.member_)`，别漏基类。
7. **值传参 / 值返回会调用几次？** 各一次（可能被 RVO 优化掉，别把副作用写进复制构造）。

### 12.3 Windows（Dev-C++）下中文乱码（保留原版 9.4）

| 现象 | 原因 | 解法 |
| --- | --- | --- |
| 编辑器里注释/字符串本身乱码 | UTF-8 文件被按 GBK 打开 | 另存为 **UTF-8 带 BOM**；文件改编码后要**关闭再重开** |
| 编译报 `illegal byte sequence` / `C4819` | 编译器输入字符集不对 | `-finput-charset=UTF-8`（MSVC 用 `/utf-8`） |
| 编译通过、**运行输出**乱码 | 控制台 936(GBK) vs 字符串 UTF-8 字节 | `main()` 开头 `SetConsoleOutputCP(65001)` |
| 中文变方块/问号 | 控制台字体 | 标题栏右键 → 属性 → 字体，换 Consolas / 新宋体 |

```cpp
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    cout << "中文正常\n";
}
```

> `cpp_oop_demo.cpp` 已是 UTF-8 BOM 版并含上述设置；`cpp_oop_demo_gbk.cpp` 是给不认 BOM 的老版 Dev-C++ 的 GBK 备选（设 936，编译加 `-finput-charset=GBK -fexec-charset=GBK`）。`u8"..."` 只影响字符串字面量编码，**不能**改变控制台的解码方式；`system("chcp 65001")` 会闪黑框，不推荐。

### 12.4 编译与调试命令（已在本机实测）

> 你的 Dev-C++ 5.11 自带 **TDM-GCC 4.9.2**，最高只支持 **`-std=c++14`**；
> 写 `-std=c++17` 会报 `unrecognized command line option`。路径：
> `D://Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe`。

```text
g++ -std=c++14 -Wall -Wextra -pedantic cpp_oop_demo.cpp -o demo
g++ -std=c++14 -fno-elide-constructors demo.cpp -o demo_all       # 关闭 RVO，观察完整复制链
g++ -std=c++14 -finput-charset=GBK -fexec-charset=GBK cpp_oop_demo_gbk.cpp -o demo_gbk
g++ --version                                                    # 查编译器版本
```

| 限制 | 影响 |
| --- | --- |
| 不支持 `-std=c++17` | `inline static` 成员、结构化绑定等不能用；静态成员仍要类外定义 |
| 没有 ASan / UBSan | `-fsanitize=address` 无法用，抓 double free 需 MSVC / Linux / WSL |
| 换编译器可解除限制 | 装 MinGW-w64 新版，或在 Dev-C++「工具 → 编译选项」里改编译器目录 |

> 一键验证：`python verify_examples.py --run`（自动找 g++、逐块编译、运行两份 demo）。
> 当前结果：**60 块中 56 块通过编译、4 块为已标注的示意/反例片段、0 个真实错误**。

---

## 附：文件清单

| 文件 | 用途 |
| --- | --- |
| `cpp_oop_handbook_textbook.html` / `.md` | **本手册**（按教材编号） |
| `教材目录_整理版.md` | 教材完整目录（12 章，带标记） |
| `cpp_oop_handbook.html` / `.md` | 原版（按知识体系，讲解更展开） |
| `cpp_oop_demo.cpp` | 综合示例，UTF-8 BOM，6 段 demo |
| `cpp_oop_demo_gbk.cpp` | 同上，GBK 备选版 |
| `build_handbook.py` | 无依赖的 MD → HTML 构建脚本 |

> 本版按你提供的**目录**对齐，讲解内容依据标准 C++（C++11 ~ C++17）编写；所有代码示例已按本机 Dev-C++ 的 C++14 实测编译，未拿到教材正文，因此具体定义的表述顺序可能与课本略有出入；若老师有指定考纲或课后习题，发来可以进一步收敛到考点。

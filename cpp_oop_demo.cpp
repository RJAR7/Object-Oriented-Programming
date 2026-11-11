// ============================================================
//  C++ 面向对象程序设计 · 配套综合示例
//  编译：g++ -std=c++14 -Wall -Wextra -pedantic cpp_oop_demo.cpp -o demo
//  说明：Dev-C++ 5.11 自带 TDM-GCC 4.9.2，最高支持 -std=c++14；
//        换用较新的 MinGW / VS 时可改成 -std=c++17。
//  观察完整复制链：追加 -fno-elide-constructors
//  检查内存问题：追加 -fsanitize=address,undefined
//        注意：Dev-C++ 自带的 MinGW 不含 ASan，需 MSVC / Linux / WSL 才可用
// ============================================================

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <windows.h>                                            // 仅 Windows 生效：控制台默认按 GBK 解码，需把输入/输出代码页设成与源文件一致
#endif

using namespace std;                                            // 按教学约定引入整个 std，省略 std:: 前缀；注意头文件里不能这样写

static void banner(const string& title) {
    cout << "\n========== " << title << " ==========\n";
}

// ------------------------------------------------------------
// 1. 类、封装、const 成员函数、static 成员
// ------------------------------------------------------------
class Student {
private:                                                        // class 成员默认 private；改成 struct 则默认 public（教材 4.6）
    string name_;
    int age_;
    static int count_;                                          // 静态数据成员属于类而非对象：全类只有一份，必须在类外定义一次

public:
    Student(const string& name, int age) : name_(name), age_(age) { ++count_; }

    void print() const { cout << name_ << " / " << age_ << '\n'; }
    void setAge(int age) { age_ = age; }
    static int count() { return count_; }                       // 无 this 指针
};

int Student::count_ = 0;                                        // 静态数据成员的类外定义（C++17 起可写 inline static int count_ = 0;）

void demo1() {
    banner("1 类与封装");
    Student a("Alice", 18);
    a.print();
    const Student b("Bob", 20);
    b.print();                                                  // const 对象调用 const 成员函数
    a.setAge(19);
    cout << "学生总数 = " << Student::count() << '\n';
}

// ------------------------------------------------------------
// 2. 复制构造的三种调用时机（对照复制赋值）
// ------------------------------------------------------------
class Trace {
public:
    Trace()                    { cout << "  [默认构造]\n"; }
    Trace(const Trace&)        { cout << "  [复制构造]\n"; }
    Trace& operator=(const Trace&) { cout << "  [复制赋值]\n"; return *this; }
};

static void passByValue(Trace) {}                               // 时机 (2)
static Trace returnByValue() { Trace t; return t; }             // 时机 (3)

void demo2() {
    banner("2 复制构造调用时机");
    Trace a;
    cout << "A b(a);\n";        Trace b(a);                     // (1)
    cout << "A c = a;\n";       Trace c = a;                    // (1) 初始化，不是赋值
    Trace d;
    cout << "d = a;\n";         d = a;                          // 复制赋值
    cout << "passByValue(a);\n"; passByValue(a);                // (2)
    cout << "Trace e = returnByValue();  (RVO/NRVO 会消除复制)\n";
    Trace e = returnByValue();                                  // (3)
    (void)b; (void)c; (void)e;
}

// ------------------------------------------------------------
// 3. 浅复制的坑（仅作说明，默认不实际触发 double free）
// ------------------------------------------------------------
class Shallow {
    int* data_ = nullptr;
public:
    explicit Shallow(int n) : data_(new int[n]{}) {}
    ~Shallow() { delete[] data_; }
    // 未手写复制构造 → 编译器合成版本只复制指针值（浅复制）
    const int* raw() const { return data_; }
    void disown() { data_ = nullptr; }                          // 仅供本演示：放弃所有权，避免真的 double free
};

void demo3() {
    banner("3 浅复制：两个对象共享同一块内存");
    Shallow x(4);
    Shallow y(x);                                               // 合成复制构造：y.data_ == x.data_
    cout << "x.data_ = " << static_cast<const void*>(x.raw()) << '\n'
              << "y.data_ = " << static_cast<const void*>(y.raw()) << '\n'
              << "地址相同 → 两个对象析构时会释放同一块内存（double free）\n";
    y.disown();                                                 // 演示程序里临时规避崩溃；真实代码请用深复制或 Rule of Zero
    cout << "（想看真实崩溃：注释掉上一行，并用 -fsanitize=address 编译）\n";
}

// ------------------------------------------------------------
// 4. 深复制 + Rule of Five
// ------------------------------------------------------------
class Buffer {
    size_t size_ = 0;
    char* data_ = nullptr;
public:
    explicit Buffer(size_t n) : size_(n), data_(new char[n]{}) {
        cout << "  构造 size=" << n << '\n';
    }

    Buffer(const Buffer& rhs) : size_(rhs.size_), data_(new char[rhs.size_]) {  // 深复制：重新申请内存并复制内容，两个对象各自持有独立资源
        if (size_ > 0) memcpy(data_, rhs.data_, size_);
        cout << "  复制构造（深复制）\n";
    }

    Buffer& operator=(const Buffer& rhs) {                      // 传统写法：自我赋值 + 异常安全
        if (this != &rhs) {
            char* tmp = new char[rhs.size_];                    // 先申请新内存：若 new 抛异常，原对象仍保持原状（强异常安全）
            if (rhs.size_ > 0) memcpy(tmp, rhs.data_, rhs.size_);
            delete[] data_;                                     // 新资源就绪后才释放旧资源，避免异常让对象停在半毁状态
            data_ = tmp; size_ = rhs.size_;
        }
        cout << "  复制赋值\n";
        return *this;
    }

    Buffer(Buffer&& rhs) noexcept : size_(rhs.size_), data_(rhs.data_) {
        rhs.data_ = nullptr; rhs.size_ = 0;                     // 置空源对象
        cout << "  移动构造（只偷指针，不复制数据）\n";
    }

    Buffer& operator=(Buffer&& rhs) noexcept {
        if (this != &rhs) {
            delete[] data_;
            data_ = rhs.data_; size_ = rhs.size_;
            rhs.data_ = nullptr; rhs.size_ = 0;
        }
        cout << "  移动赋值\n";
        return *this;
    }

    ~Buffer() { delete[] data_; }
    size_t size() const { return size_; }
    const char* raw() const { return data_; }
};

void demo4() {
    banner("4 深复制 / 移动语义");
    Buffer a(8);
    Buffer b(a);                                                // 复制构造：用一个已有对象初始化新对象（教材 4.3.4 重点）
    Buffer c(4);
    c = a;                                                      // 复制赋值
    c = Buffer(16);                                             // 移动赋值：释放自身旧资源后接管右值资源，通常标 noexcept
    Buffer d(move(c));                                          // 移动构造 A(A&&)：接管右值对象的资源，不复制；教材 4.3.6
    cout << "a=" << a.size() << " b=" << b.size()
              << " c=" << c.size() << " d=" << d.size() << '\n';
    cout << "堆缓冲区地址不同 → 深复制生效："
              << (a.raw() != b.raw() ? "是" : "否") << '\n';
}

// ------------------------------------------------------------
// 5. 继承、构造/析构顺序、virtual 析构、多态
// ------------------------------------------------------------
class Shape {
protected:
    string name_;
public:
    explicit Shape(string n) : name_(move(n)) {
        cout << "  Shape 构造\n";
    }
    virtual ~Shape() { cout << "  ~Shape 析构\n"; }             // 基类析构必须 virtual：否则通过基类指针 delete 时派生部分不会被析构
    virtual double area() const = 0;                            // 纯虚函数 → 抽象类
    virtual void draw() const { cout << "Shape::draw\n"; }
};

class Circle : public Shape {
    double r_;
public:
    Circle(double r, string n) : Shape(move(n)), r_(r) {
        cout << "  Circle 构造\n";
    }
    ~Circle() override { cout << "  ~Circle 析构\n"; }
    double area() const override { return 3.1415926 * r_ * r_; }
    void draw() const override { cout << "Circle::draw  r=" << r_ << '\n'; }
};

class Rect : public Shape {
    double w_, h_;
public:
    Rect(double w, double h, string n)
        : Shape(move(n)), w_(w), h_(h) { cout << "  Rect 构造\n"; }
    ~Rect() override { cout << "  ~Rect 析构\n"; }
    double area() const override { return w_ * h_; }
    void draw() const override { cout << "Rect::draw\n"; }
};

static void render(const Shape& s) { s.draw(); }                // 基类引用 → 动态绑定

void demo5() {
    banner("5 继承与多态");
    cout << "-- 构造顺序：基类 → 成员 → 派生；析构严格反序 --\n";
    {
        Circle c(2.0, "c1");
        Rect   r(3.0, 4.0, "r1");
        cout << "-- 通过基类指针/引用调用，运行时绑定 --\n";
        Shape* p = &c;
        p->draw();
        cout << "area = " << p->area() << '\n';
        render(r);
    }
    cout << "-- delete 基类指针：virtual 析构保证派生部分被释放 --\n";
    Shape* heap = new Circle(1.0, "c2");
    heap->draw();
    delete heap;

    cout << "-- 对象切片：按值赋给基类会丢失派生信息与多态 --\n";
    struct B { virtual void f() const { cout << "B::f\n"; } virtual ~B() = default; };
    struct D : B { void f() const override { cout << "D::f\n"; } };
    D d;
    B sliced = d;  sliced.f();                                  // B::f
    B& ref   = d;  ref.f();                                     // D::f
}

// ------------------------------------------------------------
// 6. Rule of Zero：现代 C++ 推荐写法
// ------------------------------------------------------------
class Playlist {
    vector<string> songs_;                                      // 动态资源交给标准库管理
    string title_ = "My list";                                  // 另一个自带 RAII 的成员
public:
    void add(string s) { songs_.push_back(move(s)); }
    size_t size() const { return songs_.size(); }
    const string& title() const { return title_; }
    // 五个特殊成员函数全部由编译器自动生成，且天然是正确的深复制 / 移动
};

void demo6() {
    banner("6 Rule of Zero");
    Playlist p1;
    p1.add("Song A"); p1.add("Song B");
    Playlist p2 = p1;                                           // 自动深复制
    p2.add("Song C");
    cout << "p1=" << p1.size() << "  p2=" << p2.size()
              << "  (互不影响，title=" << p2.title() << ")\n";
    Playlist p3 = move(p1);                                     // 自动移动
    cout << "p3=" << p3.size() << '\n';
}

int main() {
#ifdef _WIN32
    // 本文件保存为 UTF-8；Windows 控制台默认是 936(GBK)，会把 UTF-8 字节显示成乱码。
    // 把输入/输出代码页切到 65001(UTF-8) 即可正常显示中文。
    // 若仍显示为方块，请把控制台窗口字体改为「Consolas / Lucida Console / 新宋体」，
    // 不要用「点阵字体」(Raster Fonts)。
    SetConsoleCP(65001);                                        // 设置输入代码页：让 cin 按源文件编码解析中文
    SetConsoleOutputCP(65001);                                  // 设置输出代码页：关键一句，编码不一致就会把中文显示成乱码
#endif

    demo1();
    demo2();
    demo3();
    demo4();
    demo5();
    demo6();
    cout << "\n全部示例运行完毕。\n";
    return 0;
}

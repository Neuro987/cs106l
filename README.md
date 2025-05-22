# CS106L Assignments

This repository contains assignments for Stanford CS106L, a course on Standard C++ programming.
Official website:[cs106l sp25](https://web.stanford.edu/class/cs106l/)

# Notes

## Assignment 0: Environment Setup

**To compile a C++ source code (in Windows):**
```cpp
g++ -static-libstdc++ -std=c++20 main.cpp -o main
```
*   `-static-libstdc++`: Links the standard C++ library statically.
*   `-std=c++20`: Specifies the C++20 standard.

## Assignment 1: Types, Structs, Streams, Containers, References

Focuses on fundamental C++ elements.

**Key Concepts:**
*   **Uniform Initialization**:
    ```cpp
    struct MyType { int id; double val; };
    MyType item1{1, 2.5}; // Initializes id to 1, val to 2.5
    // int a{12.0}; // Error: narrowing conversion from double to int
    ```
*   **Type Aliases (`using`)**:
    ```cpp
    using String = std::string;
    String message = "Hello";
    ```
*   **Input/Output Streams**:
    *   `std::getline(inputStream, line);`
        *   Reads a line from `inputStream`. Note: `getline()` extracts the newline character `\n` but doesn't store it in `line`.
    *   `std::cout << ... << '\n';`
        *   Using `\n` for newlines is generally more performant than `std::endl` because `std::endl` also flushes the buffer.
    *   `std::cerr << "Error: ..." << std::endl;`
        *   Standard error stream; `std::endl` is often used here to ensure immediate output of error messages.
*   **Constant References (`const &`)**:
    ```cpp
    void processVector(const std::vector<int>& data) {
        // 'data' is a constant reference, its content cannot be changed here.
        // This avoids copying the vector and protects the original data.
    }
    ```

## Assignment 2: Containers, Iterators, Pointers

Explores common data structures and memory management.

**Key Concepts:**
*   **Iterators**:
    *   Containers must provide iterator methods (e.g., `begin()`, `end()`) to be used with iterators. `std::queue` and `std::stack` are adaptors and don't offer direct iterators.
    ```cpp
    std::vector<int> myContainer = {10, 20, 30};
    for (auto it = myContainer.begin(); it != myContainer.end(); ++it) { // Prefer ++it
        auto& element = *it; // Dereference to access the element
        // Process element
    }

    // Range-based for loop (often simpler):
    for (const auto& element : myContainer) {
        // Process element (read-only)
    }
    ```
*   **Pointers**: Variables storing memory addresses.

## Assignment 3: Classes, Inheritance, Polymorphism

Covers object-oriented programming principles.

**Key Concepts:**
*   **Classes**:
    *   **Constructors**: Initialize objects. Member initializer lists are preferred.
        ```cpp
        class Circle {
        public:
            Circle(double radius) : _radius{radius} {} // Member initializer list
        // ...
        private:
            double _radius;
        };
        ```
    *   **Destructors**: Clean up resources when an object is destroyed.
        ```cpp
        class IntVector {
        private:
            int* _data;
            size_t _size;
        public:
            IntVector(size_t size) : _data{new int[size]}, _size{size} {}
            ~IntVector() { // Destructor
                delete[] _data; // Release dynamically allocated memory
            }
            // ...
        };
        ```
    *   **Operator Overloading**: Customize operator behavior for classes.
        ```cpp
        // In IntVector class
        int& operator[](size_t index) {
            return _data[index]; // Assumes index is valid
        }
        ```
*   **Inheritance**:
    *   **Basic Inheritance**:
        ```cpp
        class Shape {
        public:
            virtual double area() const = 0; // Pure virtual function (makes Shape abstract)
            virtual ~Shape() = default; // Always provide a virtual destructor in base classes
        };

        class Circle : public Shape { // Circle inherits from Shape
        public:
            Circle(double radius) : _radius{radius} {}
            double area() const override { // Override base class method
                return 3.14159 * _radius * _radius;
            }
        private:
            double _radius;
        };
        ```
    *   **Virtual Inheritance**: Solves the "diamond problem" in multiple inheritance.
        ```cpp
        // class A {};
        // class B : public virtual A {};
        // class C : public virtual A {};
        // class D : public B, public C {}; // D has only one instance of A
        ```
        By default, class inheritance is `private` if no specifier is used. `struct` inheritance defaults to `public`.
*   **Polymorphism**:
    *   Achieved using base class pointers or references to derived class objects.
    *   **Slicing**: Storing derived objects by value in a container of base objects causes slicing (derived-specific parts are lost). Use pointers (preferably smart pointers) or references.
        ```cpp
        // std::vector<Shape*> shapes;
        // shapes.push_back(new Circle(5.0));
        // ... later, delete allocated memory ...
        ```

### Templates

Enable writing generic, type-safe code.

*   **Class Templates (Typename Parameters)**:
    ```cpp
    template <typename T>
    class GenericVector {
    public:
        T& at(size_t index);
        // ...
    private:
        T* _elements;
        size_t _count;
    };
    // GenericVector<int> intVec;
    ```
*   **Non-Typename Template Parameters**: Compile-time constant values.
    ```cpp
    template <typename T, int FixedSize>
    class StaticArray {
    private:
        T data[FixedSize];
    public:
        T& operator[](int index) { return data[index]; /* Add bounds check */ }
        int size() const { return FixedSize; }
    };
    // StaticArray<int, 100> myFixedArray;
    ```
*   **Implementation Note**: Template definitions (implementations) usually need to be in header files or included at the end of the header file. This is because the compiler needs the full definition to instantiate the template for a specific type.

### Const Correctness

Using `const` to prevent unintended modifications and clarify intent.

*   **`const` Member Functions**: Promise not to modify the object's observable state. Can be called on `const` and non-`const` objects.
    ```cpp
    class Data {
    public:
        int getValue() const { return _value; } // const member function
        void setValue(int v) { _value = v; }   // non-const member function
    private:
        int _value;
    };
    // const Data cData;
    // int val = cData.getValue(); // OK
    // cData.setValue(10); // Error
    ```
*   **Overloading on `const`**: Provide `const` and non-`const` versions of a member function.
    ```cpp
    template <typename T>
    class MyCollection {
    public:
        T& at(size_t index) { return _data[index]; }
        const T& at(size_t index) const { return _data[index]; }
    private:
        T* _data; // Example member
    };
    // MyCollection<int> collection;
    // collection.at(0) = 42; // Calls non-const at()
    // const MyCollection<int> constCollection = collection;
    // int value = constCollection.at(0); // Calls const at()
    // constCollection.at(0) = 100; // Error: constCollection.at(0) returns const T&
    ```
*   **`const_cast`**: Used to add or remove `const` (or `volatile`). Use with extreme caution. Modifying an object originally declared `const` via `const_cast` is undefined behavior.
    ```cpp
    // A common pattern (use carefully):
    // template <typename T>
    // const T& Vector<T>::findElement(const T& value) const {
    //   // Non-const version might call this const version
    //   // or vice-versa by casting 'this'
    //   return const_cast<Vector<T>&>(*this).findElement(value); // Example of one way
    // }
    ```
*   **`mutable` Keyword**: Allows a member variable to be modified even in a `const` member function or on a `const` object. Useful for things like internal caches or mutexes.
    ```cpp
    struct Cacheable {
        mutable int accessCount = 0; // Can be modified by const methods
        std::string data;
        std::string getData() const {
            accessCount++;
            return data;
        }
    };
    // const Cacheable c;
    // c.getData(); // accessCount is now 1
    ```
ex: 
class.h
```cpp
class Object {
public:
    Object();
    Object(const std::string& objName);
    virtual ~Object();
    ...

protected:
    virtual void OnDestroy();

private:
    const unsigned int _id;
    static unsigned int _nextId;  // Static
    std::string name;
};
```
class.cpp
```cpp
unsigned int Object::_nextId = 0; 
Object::Object()
    : _id{_nextId++} // list init
{
    name = "Default";
}
Object::Object(const std::string& objName) 
    : Object() // delegating constructor
{
    name = objName;
}
Object::~Object(){
    OnDestroy();
}
...
```

## Assignment 4
### Function Templates
```cpp
template <typename T>
T min(const T& a, const T& b) {
    return a < b ? a : b;
} // operator< overload must exist
min<int>(1, 2);
min<double>(1.2, 3.4);
// Implicit kinda like auto
min(1, 2);
min(1.2, 3.4);
// min(1, 2.3); // Does not complie
auto min(const T& a, const T& b) {
    return a < b ? a : b;
}
min(1, 2.3); // Compile

// find
template <typename Iterator, typename TElem>
Iterator find(Iterator begin, Iterator end, TElem value) {
    for (Iterator it = begin; it != end; ++it) {
        if (*it == value) return it;
        return end;
    }
}

// Put constrains on templates: Concept
template <typename T> 
concept Comparable = requires(const T a, const T b) {
    { a < b } -> std::convertible_to<bool> // Anything in {} must compile without error; convertible_to is also a concept
};
template <typename T> requires Comparable<T>  // Or: template <Comparable T>
auto min(const T& a, const T& b);

// Variadic templates
// min(1.2, 2.3, 3.4, 4.5); // to sovle this
// Method 1: use vector recursively
template <Comparable T>
T min(const std::vector<T>& values) {
    if (values.size() == 1) return values[0];
    const auto& first = values[0];
    std::vector<T> rest(++values.begin(), values.end()); // Construct with iterators
    auto m = min(rest);
    return first < m ? first : m;
}
// Method 2: variadic template
template <Comparable T>
T min (const T& v) { return v; }
template <Comparable T, Comparable... Args> // Variadic template: matches 0 or more types
T min (const T& v, const Args&... args) { // Parameter Pack: 0 or more paras
    auto m = min(args...); // Pack expansion
    return v < m ? v : m;   
}// Compiler will automatically generate overloads
// Variadic types do not have to be the same

// Template Metaprogramming(TMP)
// Do work at compile time, ex:
template <>
Struct Fibonacci<0>{
    enum { value = 0 };
}
template <>
Struct Fibonacci<1>{
    enum { value = 2 };
}
template <size_t N>
Struct Fibonacci<N>{
    enum { value = Fibonacci<N-1>::value + Fibonacci<N-2>::value };
}
// Use constexpr/consteval to have both compile-time execution and readable code
constexpr size_t factorial(size_t n) {
    if (n==0) return 1;
    return n * factorial(n-1);
}
```
### Functions and Lambdas
What is a predivate: isPrime(v), isVowel(v) ...
Pass pred as a parameter with template:
```cpp
template <typename It, typename Pred>
It find_if(It first, It last, Pred pred) {
    for (auto it = first; it != last; ++it) {
        if(pred(*it)) return it;
    }
    return last;
}
...
auto it = find_if(ints.begin(), ints.end(), isPrime);
// The pred function can only take one parameter(isPrime(int value))
```
If we want to give our function extra state without introducing other parameters:
Lambda Functions
```cpp
int n:
std::cin >> n;
auto lessThanN = [n](int x){ return x < n; }; // Capture clause [n], let us use outside variables
find_if(ints.begin(), ints.end(), lessThanN)
```
Note on captures:
```c
[] // capture nothing
[x] // by value
[x&] // by ref
[x, y] // by value
[&] // capture everything by ref
[&, x] // capture everything except x by ref
[=] // capture everything by value
```
STL: Functor: an obj that acts like a function
When using lambda, a functor is generated
```cpp
// lambda
auto lessThanN = [n](int x){return x < n;};
// equals to:
class __lambda_6_18 // random name
{
public:
    bool operator()(int x) const {return x < n; } // function call operator
    __lambda_6_18(int& _n) : n{_n} {} // Constructor
private:
    int n;
};
auto lessThanN{n};
```
STL: <algorithm>
```cpp
std::sort(RandomIt first, RandomIt last, Compare comp);
std::copy_if(InputIt r1, InputIt r2, OutputIt o, UnaryPred p);
...
```
Range is a type with begin and end
std::ranges provides new versions of <algorithm> for ranges
```cpp
std::vector<char> v = {'a','b','c'};
auto it = std::ranges::find(v, 'c');
// equals to: std::find(v.begin(), v.end(), 'c');
```
std::ranges::views
view is lazy
view is composable `auto f = std::views::filter(isVowel);`
views can be chained using operator |
```cpp
std::vector<int> v = {1, 2, 3, 4, 5, 6};

auto even_squares = v
    | std::views::filter([](int n) { return n % 2 == 0; }) // std::views = std::ranges::views
    | std::views::transform([](int n) { return n * n; })
    | std::ranges::to<std::vector<int>>(); // C++23: std::ranges::to<container> 

for (int n : even_squares) {
    std::cout << n << " ";  // 4 16 36
}
```
ex: soundexRange
```cpp
std::string soundexRanges(const std::string& s)
{
  namespace rv = std::ranges::views;

  auto first = *std::ranges::find_if(s, ::isalpha);       // Get first letter 
  auto v = s | rv::filter(::isalpha) | rv::transform(soundexEncode);

  std::string encoded;
  std::ranges::unique_copy(v, std::back_inserter(encoded));
  encoded[0] = std::toupper(first);

  return encoded 
         | rv::filter(notZero)             // Get rid of zeros
      // | rv::concat("0000")              // Ensure length >= 4 (C++26)
         | rv::take(4)                     // Take first four
         | std::ranges::to<std::string>(); // Convert to string
}
```
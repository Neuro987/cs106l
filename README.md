# CS106L Assignments 

This repository contains assignments for Stanford CS106L, a course on Standard C++ programming.
Official website:[cs106l sp25](https://web.stanford.edu/class/cs106l/)

# Notes

## Assignment 0
Setting up environment. To compile a c++ source code: 
```
g++ -static-libstdc++ -std=c++20 main.cpp -o main
```
## Assignment 1
Type, struct, stream, container, reference`&`
```c++
struct Type{...}; Type var{...}; // Uniform initialization
int a{12.0}; //error
using String = std::string; 
std::getline(inputstream, line);  //getline() will get '\n' as the last element
std::cout << ... << '\n'; // For output '\n' has better performance than std::endl
std::cerr << "Error: ..." << std::endl; // Standard error
void function(const std::vector<int> & vec) // Constant ref, avoid changing the original value.
```
## Assignment 2
Container, iterator, pointer
```c++
// To use iterator, the container has to have the iterator method. For example, std::queue does not offer iterator.
for(auto it = c.begin(); it < c.end(); ++it) { // Always use ++i
  auto& elem = *it; // Dereference, undefined when it == c.end()
  ...
}
for(auto elem : c) // Commonly
```
## Assignment 3
Class(constructor, deconstructor, virtual), inheritance
```c++
class Shape {
public:
  virtual double area() const = 0; // Pure virtual function by adding =0, has to be overriden. (Dynamic Polymorphism) A class with pure virtual functions can not be instantiated.
};
class Circle : public Shape { // inherit :
public:
  // constructor
  Circle(double radius): _radius{radius} {}; // list initialization: ObjName(para): member1{value1}, member2{value2} {}
  double area() const override { // double area(const Shape* this); override isn't required but for better readability
  return 3.14 * _radius * _radius;
}
private:
  double _radius;
};
...
class Student : public virtual Person {...}; // virtual inherit solve the Diamond Problem; by default classes are inherited privately

...
std::vector<Entitiy*> entities { &p, &t, &b }; // Storing pointers instead of the entities themselves. If not using pointers, the derived classes would not fit in the bass class, and get sliced.

// Deconstructor
IntVector::~IntVector(){
  delete[] _data;
}

// Overload operator[], letting IntVector can be used as an normal vector: IntVector[index]
int& IntVector::operator[](size_t index){
  return _data[index];
}
```
Template
```c++
template <typename T>
class Vector {
  T& at(size_t index);
  ...
};
Vector<int> v;

// non-typename template parameters
template <typename T, int Size>
class Array {
private:
    T data[Size];
public:
    T& operator[](int index) { return data[index]; }
    int size() const { return Size; }
};
Array<int, 10> intArray; 

// For template classes the .h file needs to includes the .cpp file at bottom
```
Const
```c++
// When calling a const obj's method, the declaration and impletation have to be const. Obj marked as const can only make use of the const interface.

template <typename T>
class Vector {
public:
  T& at(size_t index) {
    return _data[index];
  }
  const T& at(size_t index) const {
    return _data[index]; 
  }
private:
  T* _data;
};//method at() has two overloads: const version and none const version.
Vector<int> v;
v.at(0) = 42; // Correct
const Vector<int> cv = v;
cv.at(0) = 100; // Error: const ref cannot be modified


template <typename T>
T& Vector<T>::findElement(const T& value) {...}
// const_cast<target_type>(expression)
// Valid uses of const_cast are few and far between
template <typename T>
const T& Vector<T>::findElement(const T& value) const {
  return const_cast<Vector<T>&>(*this).findElement(value); 
}

// mutable keyword (Carefully!)
struct MutableStruct { mutable int value; }
const MutableStruct cm;
cm.value = 111; // Correct
```
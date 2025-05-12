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
```
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
```
// To use iterator, the container has to have the iterator method. For example, std::queue does not offer iterator.
for(auto it = c.begin(); it < c.end(); ++it) { // Always use ++i
  auto& elem = *it; // Dereference, undefined when it == c.end()
  ...
}
for(auto elem : c) // Commonly
```
## Assignment 3

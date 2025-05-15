/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include"class.h"
#include<iostream>

void sandbox() {
  Object obj = Object("TestObj");
  std::cout << "Name: " << obj.getName() << " Id: " << obj.getId() << "\n";
}
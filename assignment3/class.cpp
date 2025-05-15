#include<iostream>
#include"class.h"

unsigned int Object::_nextId = 0;

Object::Object()
    : _id{_nextId++}
{
    name = "Default";
    position[0] = position[1] = 0;
}
Object::Object(const std::string& objName) 
    : Object()
{
    name = objName;
}
Object::~Object(){
    OnDestroy();
}

void Object::Update(float deltaTime){
    std::cout << "Update Object id: " << _id << "with deltaTime=" << deltaTime << "\n"; 
}
void Object::Render(){
    std::cout << "Render Object id: " << _id << "\n";
}
void Object::OnDestroy(){
    std::cout << "Destroy Object id: " << _id << "\n";
}

const std::string& Object::getName() const{
    return name;
}
void Object::setName(std::string& objName){
    name = objName;
}
const unsigned int Object::getId() const{
    return _id;
}

void Object::LogInfo() const {
    std::cout << "[Info] Object Created - ID: " << _id << ", Name: " << name << std::endl;
}
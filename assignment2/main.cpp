/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <sstream>
#include <random>

std::string kYourName = "Fuuko Neuro"; // Don't forget to change this!

/**
 * 生成一个随机布尔值（true或false）
 * 
 * @param seed 可选的字符串种子，用于初始化随机数生成器
 * @return 随机的布尔值，有50%的概率返回true或false
 */
bool random_bool(const std::string& seed = "") {
  static std::random_device rd;
  
  static std::mt19937 gen = [&seed]() {
    if (!seed.empty()) {
      std::size_t seed_hash = std::hash<std::string>{}(seed);
      return std::mt19937(static_cast<unsigned int>(seed_hash));
    } else {
      return std::mt19937(rd());
    }
  }();
  
  static std::bernoulli_distribution dist(0.5);
  
  return dist(gen);
}

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> applicants;
  std::ifstream ifs(filename);
  if (ifs.is_open()) {
    std::string name;
    while (std::getline(ifs, name)) {
      applicants.insert(name);
    }
  } else {
    std::cerr << "Error: Could not open file " << filename << std::endl;
  }
  ifs.close();
  return applicants;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> matched_students;

  std::istringstream iss(name);
  std::string first, last;
  iss >> first >> last;
  
  if (first.empty() || last.empty()) {
    std::cerr << "Error: Invalid name format: " << name << std::endl;
    return matched_students;
  }
  
  for (const auto& student_name : students) {
    std::istringstream iss1(student_name);
    std::string first1, last1;
    iss1 >> first1 >> last1;
    
    if (first1.empty() || last1.empty()) {
      std::cerr << "Error: Invalid name format: " << student_name << std::endl;
      continue;
    }
    if (first1[0] == first[0] && last1[0] == last[0]) {
      matched_students.push(&student_name);
    }
  }
  
  return matched_students;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matchse) {
  for(int i = 0; i < matchse.size(); ++i) {
    if (random_bool(kYourName)) matchse.pop();
  }
  if (matchse.size() == 0) return "NO MATCHES FOUND.";
  return *matchse.front();
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"

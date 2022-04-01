#pragma once
#include <set>
#include <string>
#include <map>
#include<vector>
#include <future>

class Tasks
{
private:
  std::vector<int> tasks;
  std::map<int,std::string> result;
  std::future<std::map<int, std::string>> future;
public:
  Tasks(std::vector<int> tasks);
  void start();
  std::map<int, std::string> get();
  bool get_page_data(int page, std::set<std::string> &data);
  bool data_storage(std::set<std::string> data, const std::string path);
};
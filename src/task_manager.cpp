#include "task_manager.h"
#include "tasks.h"
#include "net_spider.h"
#include "data_processor.h"
#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <tuple>
#include <future>

/**
 * @brief TaskManager
 *
 */
TaskManager::TaskManager()
{
  this->current_task_num = 0;
  this->get_total();
}
TaskManager *TaskManager::_instance = nullptr;
TaskManager *TaskManager::get()
{
  if (!_instance)
  {
    _instance = new TaskManager();
  }
  return _instance;
}

void TaskManager::get_total()
{
  std::string str;
  auto net_spider = NetSpider::get();
  auto page = net_spider->getHtmlPage(1, str);
  if (page)
  {
    std::regex reg("[\\w]{3}(?=\\W+\">尾页)", std::regex::icase);
    std::smatch result;
    int total_page;
    while (regex_search(str, result, reg))
    {
      for (const auto &re : result)
      {
        total_page = stoi(re);
      }
      str = result.suffix().str();
    }
    this->total_page_num = total_page;
  }
  else
  {
    this->total_page_num = 0;
  }
}

void TaskManager::run()
{
  this->get_total();
  if (!this->total_page_num)
  {
    std::cerr << "get total page num failed !" << std::endl;
    return;
  }
  std::vector<std::vector<int>> jobs;
  jobs.resize(7);
  int every_tasks = this->total_page_num / 7;
  int surplus_tasks = this->total_page_num % 7;
  for (int i = 1; i <= every_tasks; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      jobs[j].push_back(i + j * every_tasks);
    }
  }
  for (int i = 0; i < surplus_tasks; i++)
  {
    jobs[i].push_back(this->total_page_num - i);
  }
  std::vector<Tasks*> tasks;
  tasks.resize(7);
  for (int i = 0; i < 7; i++)
  {
    tasks[i] = new Tasks(jobs[i]);
    tasks[i]->start();
  }
  for (auto& task : tasks)
  {
      task->get();
      delete task;
  }
}
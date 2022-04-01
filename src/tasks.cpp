#include "tasks.h"
#include "net_spider.h"
#include "data_processor.h"
#include <fstream>
#include <future>
#include <mutex>
#include <iostream>
std::mutex m;

bool Tasks::get_page_data(int page, std::set<std::string> &data)
{
  std::string buffer;
  auto net_spider = NetSpider::get();
  bool is_success = net_spider->getHtmlPage(page, buffer);
  if (is_success)
  {
    PageDataProcessor::search_name(buffer, data);
    return true;
  }
  else
  {
    return false;
  }
}

bool Tasks::data_storage(std::set<std::string> data, const std::string path)
{
  std::fstream fs(path, std::ios::app | std::ios::out | std::ios::ate);
  if (fs.is_open())
  {
    for (const auto it : data)
    {
      fs << it << std::endl;
    }
    return true;
  }
  return false;
}
Tasks::Tasks(std::vector<int> tasks) : tasks(tasks) {}
void Tasks::start()
{
  this->future = std::async(
      std::launch::async,
      [this]()
      {
        for (const auto task : tasks)
        {
          std::set<std::string> data;
          bool net_result = get_page_data(task, data);
          if (net_result)
          {
            std::cout << "this page is:" << task << std::endl;
            std::unique_lock<std::mutex> lk(m);
            bool memory_result = data_storage(data, "all_movies.txt");
            if (!memory_result)
            {
              this->result[task] = "memory_err";
            }
          }
          else
          {
            this->result[task] = "net_err";
          }
        }
        return this->result;
      });
}

std::map<int, std::string> Tasks::get()
{
  auto result = this->future.get();
  return result;
}
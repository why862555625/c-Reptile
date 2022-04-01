#include <iostream>
#include <string.h>
#include <set>
#include <functional>
#include <thread>
#include "task_manager.h"
using namespace std;



int main()
{
  std::string buffer;
  auto taskMgr = TaskManager::get();
  taskMgr->run();
  return 0;
}
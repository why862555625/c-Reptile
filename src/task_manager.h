/**
 * @file task_manager.h
 * @author your name (you@domain.com)
 * @brief 任务管理器类，用来管理多个下载和处理线程并对最终结果进行汇总
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <set>

class TaskManager
{
private:
  TaskManager();

public:
  static TaskManager *get();
  /**
   * @brief 核心执行函数
   *  内部分配线程进行多线程下载和数据处理
   *  并最终对结果进行汇总
   *
   * @param url
   * @return true
   * @return false
   */
  void run();
  void get_total();


private:
  static TaskManager *_instance;
  static const int max_task = 7;
  int current_task_num;
  int total_page_num;
};
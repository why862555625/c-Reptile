/**
 * @file data_processor.h
 * @author your name (you@domain.com)
 * @brief 数据处理核心类
 * @version 0.1
 * @date 2022-03-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>
#include <set>
#include <regex>
/**
 * @brief 对单页数据的处理逻辑
 *
 */
class PageDataProcessor
{
public:
  static std::string substring(const std::string &content, const std::string &start, const std::string &end);
  static std::string find_name(const std::string str)
  {
    return PageDataProcessor::substring(str, "title=\\\"", "\\\"");
  };
  static void search_name(std::string str, std::set<std::string> &result);
};
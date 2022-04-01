#include "data_processor.h"

std::string PageDataProcessor::substring(const std::string &content, const std::string &start, const std::string &end)
{
  auto pos1 = content.find_first_of(start);
  if (pos1 == std::string::npos)
    return "";
  pos1 += start.length();
  auto pos2 = content.find_first_of(end, pos1);
  if (pos2 == std::string::npos)
    return "";
  auto result = content.substr(pos1, pos2 - pos1);
  return result;
}
void PageDataProcessor::search_name(std::string str, std::set<std::string> &res)
{
  std::regex reg("(?=title=)[\\w|\\W]{1,50}", std::regex::icase);
  std::smatch result;
  while (std::regex_search(str, result, reg))
  {
    for (const auto &re : result)
    {
      res.insert(PageDataProcessor::find_name(re));
    }
    str = result.suffix().str();
  }
}
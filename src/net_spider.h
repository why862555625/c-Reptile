#pragma once
#include <string>
#include <curl/curl.h>

#define BASEURL "http://www.wanfugd.com/index.php?s=home-vod-type-id-1-mcid-6-area--year--letter--order--picm-1-p-"

struct WriteThis
{
  const char *readptr;
  long sizeleft;
};

/**
 * @brief 下载功能封装
 *
 */
class NetSpider
{
private:
  NetSpider(){};

public:
  /**
   * @brief 获取单例
   *
   * @return NetSpider*
   */
  static NetSpider *get();
  /**
   * @brief http get获取一页
   *
   * @param pageId
   * @param buffer
   * @return true
   * @return false
   */
  bool getHtmlPage(int pageId, std::string &buffer);
  /**
   * @brief  写数据
   *
   * @param buffer
   * @param size
   * @param nmemb
   * @param userdata
   * @return size_t
   */
  static size_t OnWriteData(void *buffer, size_t size, size_t nmemb, void *userdata);
  std::string get_url(int pageId);

private:
  static NetSpider *_instance;
};
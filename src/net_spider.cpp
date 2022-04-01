#include "net_spider.h"
NetSpider *NetSpider::_instance = nullptr;
NetSpider *NetSpider::get()
{
  if (!_instance)
  {
    _instance = new NetSpider();
  }
  return _instance;
}
size_t NetSpider::OnWriteData(void *buffer, size_t size, size_t nmemb, void *userdata)
{
  std::string *str = dynamic_cast<std::string *>((std::string *)userdata);
  if (NULL == str || NULL == buffer)
  {
    return -1;
  }

  char *pData = (char *)buffer;
  str->append(pData, size * nmemb);
  return nmemb;
}
std::string NetSpider::get_url(int pageId)
{
  return std::string(BASEURL).append(std::to_string(pageId));
}

bool NetSpider::getHtmlPage(int pageId, std::string &buffer)
{
  std::string head;
  CURL *curl;
  CURLcode res;
  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Accept: */*");
  headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
  headers = curl_slist_append(headers, "Accept-Language: zh-CN,zh;q=0.9");
  headers = curl_slist_append(headers, "Connection: keep-alive");
  headers = curl_slist_append(headers, "Host: www.wanfugd.com");
  headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.82 Safari/537.36");
  headers = curl_slist_append(headers, "X-Requested-With: XMLHttpRequest");

  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, this->get_url(pageId).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData); ///                 ******方式2*********
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&buffer); //读入string
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate");
    res = curl_easy_perform(curl);
    if (res != 0)
    {
      curl_slist_free_all(headers);
    }
  }
  curl_easy_cleanup(curl);
  return true;
}

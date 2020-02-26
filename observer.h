#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class observer
{
public:
  virtual void update(std::vector<std::string>& v) = 0;
};

class handler
{
private:
  std::vector<std::string> v;
  std::time_t tim;
  std::vector<observer*> view;
public:
  handler(){}

  void subscribe(observer *obs) {
    view.push_back(obs);
  }
  void push(std::string& str)
  {
    if (!str.empty())
      v.push_back(str);
  }
  std::time_t& getTime()
  {
    return tim;
  }
  auto size()
  {
    return v.size();
  }

  void show()
  {
    if (!v.empty())
    {
      for (auto s : view)
      {
        s->update(v);
      }
      v.clear();
    }
  }
};

class output_observer : public observer
{
public:
  output_observer(handler *ha)
  {
    ha->subscribe(this);
  }
  void update(std::vector<std::string>& v) override
  {
    std::cout << "bulk:";
    for(auto &i: v)
    {
      std::cout << " " << i;
    }
    std::cout << std::endl;
  }
};

class record_observer : public observer
{
private:
  std::time_t& tim;
public:
  record_observer(handler *ha):tim(ha->getTime())
  {
    ha->subscribe(this);
  }
  void update(std::vector<std::string>& v) override
  {
    std::string t = std::to_string(tim);
    std::cout << "unixtime " << t << std::endl;
  }
};


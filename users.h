#ifndef _USER_H
#define _USER_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

namespace myftp {

/**
 *@The users class
 */
class Users {

public:
  using Dictionary = std::unordered_map<std::string, std::string>;

  /**
   * @ read user name and pwd from file
   */
  explicit Users(const std::string& filename = "users"):
    _data{}
  {
    std::ifstream ifs{filename};
    for (std::string name, pwd; ifs >> name >> pwd; /*  */)
      _data.insert({name, pwd});
  }
  
  std::ostream& print()const
  {
    for (const auto& user : _data)
      std::cout << user.first << " " << user.second << std::endl;

    return std::cout;
  }
  
  bool empty() const
  {
    return _data.empty();
  }

  /**
   * @check user'name with password
   */
  bool check(const std::string& uname, const std::string& pwd) const
  {
    auto it = _data.find(uname);
    if ( it != _data.end() && it-> second == pwd)
      return true;
    return false;
  }

private:
  Dictionary _data;
};

} // myftpd namespace ends.

#endif /* _USER_H */


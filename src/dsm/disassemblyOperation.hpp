#include <string>
#include <iostream>

namespace dism{

  struct DissassemblyOperation{
    DissassemblyOperation(std::string&& message):
      m_message{std::move(message)}{}

    void operator()() const{std::cout << m_message << '\n';}

    const std::string m_message;
  };

  struct DDFDPrefixOperation{
    DDFDPrefixOperation(std::string&& message):
      m_message{std::move(message)}
    {
    }

    enum class Mode{DD, FD};
    const std::string m_message;

    void operator()(Mode prefixmode) const {
      switch(prefixmode){
        case Mode::DD:
          std::cout << "dd prefix: " << m_message << '\n';
          break;
        case Mode::FD:
          std::cout << "fd prefix: " << m_message << '\n';
          break;
      }
    }
  };

}

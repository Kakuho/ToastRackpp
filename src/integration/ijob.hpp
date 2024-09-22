#ifndef IJOB_HPP
#define IJOB_HPP

#include <string>
#include <iostream>

namespace Trpp::Integration{

  template<typename T>
  concept Callable = requires(T a){
    a();
  };

  template<typename T>
    requires Callable<T>
  class IJob{
    private:
      static constexpr std::size_t width = 100;

    public:
      // the only constructors we allow
      IJob(std::string&& name, T proc): m_name{name}, m_proc{proc}{
      }

      IJob(T proc): m_name{"unnamed procedure"}, m_proc{proc}{    // should not really allow this, but yk if lazy is ok
      }

      // do not allow copying / moving to provide function-like semantics
      IJob() = delete;
      IJob(const IJob& src) = delete;
      IJob(const IJob&& src) = delete;
      IJob& operator=(const IJob& src) = delete;
      IJob& operator=(const IJob&& src) = delete;

      void PrintHeader(std::size_t width){
        for(int i = 0; i < width; i++){
          std::cout << '-';
        }

        std::cout << "\nIntegration Prodcedure :: " << m_name << "\nStarting...\n\n";
      };

      void PrintFooter(std::size_t width){
        
        std::cout << "\nEnding...\nIntegration Prodcedure :: " << m_name << '\n';
        for(int i = 0; i < width; i++){
          std::cout << '-';
        }
        std::cout << '\n';
      };

      void operator()(){
        PrintHeader(IJob::width);
        m_proc();
        PrintFooter(IJob::width);
      }

    private:
      T m_proc;
      std::string m_name;
  };

inline void PrintSeparator(){
  std::cout << "\n----------\n";
}

}; // namespace Trpp::Integration

#endif

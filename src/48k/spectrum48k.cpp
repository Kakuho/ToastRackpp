#include "spectrum48k.hpp"
#include <memory>
#include <stdexcept>

namespace Trpp{

// ------------------------------------------------------ //
//  Lifetime
// ------------------------------------------------------ //

Spectrum48K::Spectrum48K()
  :
    m_memory{std::make_unique<ZxMemory48K>()},
    m_cpuBridge{std::make_unique<CPU::Z80Bridge>(m_memory.get())}
{
}

//-------------------------------------------------------------
// File Loading Routines
//-------------------------------------------------------------

void Spectrum48K::LoadFile(std::string&& filename){
  // The client facing code for loading a file into system ram
  using namespace Loader;
  m_filename = std::move(filename);
  Extension ext = ParseExtension(m_filename);
  switch(ext){
    using enum Extension;
    case Z80:
      LoadZ80();
      return;
    case Tap:
      LoadTap();
      return;
    case Unknown:
      throw std::runtime_error{"ERROR::LoadFile::Unknown file ext"};
      return;
  }
}

void Spectrum48K::LoadZ80(){
  using namespace Trpp::Loader;
  Z80Loader loader{m_filename};
  loader.Load(*m_memory);
}

// ------------------------------------------------------ //
//  Driving code
// ------------------------------------------------------ //

void Spectrum48K::Run(){
  m_cpuBridge->Step();
  m_cpuBridge->TriggerNmi();
  m_cpuBridge->Step();
}

} // namespace Trpp

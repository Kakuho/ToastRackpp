// utility library

#include <cstdint>

namespace trpp{
  inline bool DetermineBorrow(bool a, bool b, bool borrowIn){
    // a - b
    return (!a & b) | (!a & borrowIn) | (b & borrowIn) ;
  }

  inline bool HalfBorrow8bit(std::uint8_t a, std::uint8_t b){
    // a - b, half borrow => 4th bit
    bool borrowout = 0;
    for(int i = 0; i < 4; i++){
      borrowout = DetermineBorrow(a & (1 << i), b & (1 << i), 0);
    }
    return borrowout;
  }

  inline bool Borrow8bit(std::uint8_t a, std::uint8_t b){
    // a - b, half borrow => 4th bit
    bool borrowout = 0;
    for(int i = 0; i < 7; i++){
      borrowout = DetermineBorrow(a & (1 << i), b & (1 << i), 0);
    }
    return borrowout;
  }


  inline bool HalfBorrow16bit(std::uint8_t a, std::uint8_t b){
    // a - b, half borrow => 12th bit
    bool borrowout = 0;
    for(int i = 0; i < 12; i++){
      borrowout = DetermineBorrow(a & (1 << i), b & (1 << i), 0);
    }
    return borrowout;
  }

  /* Carries */

  inline bool DetermineCarry(bool a, bool b, bool carryIn){
    // a + b
    return (a & b) | (a & carryIn) | (b & carryIn) ;
  }

  inline bool HalfCarry8bit(std::uint8_t a, std::uint8_t b){
    // a - b, half borrow => 4th bit
    bool carryout = 0;
    for(int i = 0; i < 4; i++){
      carryout = DetermineCarry(a & (1 << i), b & (1 << i), 0);
    }
    return carryout;
  }

  inline bool Carry8bit(std::uint8_t a, std::uint8_t b){
    // a - b, half borrow => 4th bit
    bool carryout = 0;
    for(int i = 0; i < 7; i++){
      carryout = DetermineCarry(a & (1 << i), b & (1 << i), 0);
    }
    return carryout;
  }
}

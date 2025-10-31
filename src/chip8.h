#include <cstdint>

class Chip8 {
private:
  uint8_t V[16];
  uint8_t memory[4096];

  uint16_t index;
  uint16_t pc;
  uint16_t opcode;

  uint16_t stack[16];
  uint8_t sp;

  uint8_t delay_timer;
  uint8_t sound_timer;

  void init();

public:
  uint8_t key[16];
  uint32_t video[64 * 32];

  bool drawFlag;

  Chip8();
  ~Chip8();

  bool loadROM(const char *file_path);
  void emulateCycle();
};

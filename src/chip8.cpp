#include "time.h"
#include <fstream>
#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>

#include "chip8.h"


const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;

uint8_t fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


const unsigned int START_ADDRESS = 0x200;

void Chip8::init() {
  pc = START_ADDRESS; 
  opcode = 0;         
  index = 0;          
  sp = 0;             

  for (int i = 0; i < 2048; ++i) {
    video[i] = 0;
  }

  for (int i = 0; i < 16; ++i) {
    stack[i] = 0;
    keypad[i] = 0;
    registers[i] = 0;
  }

  for (int i = 0; i < FONTSET_SIZE; ++i) {
    memory[FONTSET_START_ADDRESS + i] = fontset[i];
  }

  delay_timer = 0;
  sound_timer = 0;

  // Seed rng
  srand(time(NULL));
}


bool Chip8::loadROM(char const *filename) {
  init();

  printf("Loading ROM: %s\n", filename);

  // Open ROM file
  FILE *rom = fopen(filename, "rb");
  if (rom == NULL) {
    std::cerr << "Failed to open ROM" << std::endl;
    return false;
  }

  // Get file size
  fseek(rom, 0, SEEK_END);
  long rom_size = ftell(rom);
  rewind(rom);

  // Allocate memory to store rom
  char *rom_buffer = (char *)malloc(sizeof(char) * rom_size);
  if (rom_buffer == NULL) {
    std::cerr << "Failed to allocate memory for ROM" << std::endl;
    return false;
  }

  // Copy ROM into buffer
  size_t result = fread(rom_buffer, sizeof(char), (size_t)rom_size, rom);
  if (result != rom_size) {
    std::cerr << "Failed to read ROM" << std::endl;
    return false;
  }

  // Copy buffer to memory
  if ((4096 - 512) > rom_size) {
    for (int i = 0; i < rom_size; ++i) {
      memory[i + 512] =
          (uint8_t)rom_buffer[i]; // Load into memory starting at 0x200
    }
  } else {
    std::cerr << "ROM too large to fit in memory" << std::endl;
    return false;
  }

  // Clean up
  fclose(rom);
  free(rom_buffer);

  return true;
}


void Chip8::emulateCycle() {

}


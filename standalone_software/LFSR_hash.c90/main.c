/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <stdio.h>
#include <string.h>
#include <sqtype.h>
#include <sqres.h>

#define BUFSIZE 512
#define LFSR_SIZE 8

u8 buffer[BUFSIZE];

u8 lfsr_state[LFSR_SIZE];

const u8 lfsr_init[LFSR_SIZE] = {0x19, 0x92, 0xbb, 0xa7, 0x8f, 0xd2, 0x68, 0xba};

/* LFSR 64 bit with polynomial x^63 + x^62 + 1*/
void Lfsr8Step(u8 *lfsr_state)
{
  usize i;
  u8 first_lsb = lfsr_state[0] & 0x01;
  u8 lsb;
  for (i = 0; i < 7; i++)
  {
    lfsr_state[i] = lfsr_state[i] >> 1;
    lsb = lfsr_state[i + 1] & 0x01;
    if (lsb)
      lfsr_state[i] = lfsr_state[i] | 0x80;
  }
  lfsr_state[7] = lfsr_state[7] >> 1;
  if (first_lsb)
    lfsr_state[7] = lfsr_state[7] ^ 0xC0;
}

void InitLfsr8State(u8 *lfsr_state)
{
  memcpy(lfsr_state, lfsr_init, LFSR_SIZE);
}

void PrintLfsr8State(u8 *lfsr_state)
{
  int i;
  for (i = LFSR_SIZE - 1; i >= 0; i--)
  {
    printf("%02x", lfsr_state[i]);
  }
  printf("\n");
}

Results HashFile(FILE *input_file, u8 *hash)
{
  usize data_read = fread(buffer, 1, BUFSIZE, input_file);
  usize i;
  while (ferror(input_file) == 0 && data_read != 0)
  {
    size_t hash_index;
    /* process block */
    printf("processing block %lu size\n", data_read);
    for (i = 0; i < data_read; i++)
    {
      hash_index = i & 0x07;
      hash[hash_index] = hash[hash_index] ^ buffer[i];
      if (hash_index == 7)
        Lfsr8Step(hash);
    }
    data_read = fread(buffer, 1, BUFSIZE, input_file);
  }
  if (ferror(input_file))
    return kError;
  if (feof(input_file))
    return kOk;
  return kError;
}

int main(int argc, char *argv[])
{
  FILE *input_file;
  if (argc != 2)
  {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }
  input_file = fopen(argv[1], "r");
  if (input_file == NULL)
  {
    printf("File %s not found\n", argv[1]);
    return 1;
  }
  InitLfsr8State(lfsr_state);
  HashFile(input_file, lfsr_state);
  PrintLfsr8State(lfsr_state);
  fclose(input_file);
  return 0;
}

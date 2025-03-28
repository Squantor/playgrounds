/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <stdio.h>
#include <sqtype.h>
#include <sqres.h>

u8 buffer[512];

Results hash_file(FILE *input_file, u64 *hash)
{
  usize data_read = fread(buffer, 1, 512, input_file);
  return kOk;
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
  fclose(input_file);
  return 0;
}

// 2011 Ninjas
// Licensed under the terms of the GNU GPL, version 2
// http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt

#include "tools.h"
#include "types.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define die(format, ...) {                      \
    fprintf (stderr, format, ## __VA_ARGS__);   \
    exit (-1);                                  \
  }

static void
sc_encrypt_with_portability (int type, u8 *buffer, u8 *iv)
{
  static u8 keys[][16] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0xFA, 0x72, 0xCE, 0xEF, 0x59, 0xB4, 0xD2, 0x98,
     0x9F, 0x11, 0x19, 0x13, 0x28, 0x7F, 0x51, 0xC7},
    {0xD4, 0x13, 0xB8, 0x96, 0x63, 0xE1, 0xFE, 0x9F,
     0x75, 0x14, 0x3D, 0x3B, 0xB4, 0x56, 0x52, 0x74},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  };

  static u8 expected[][0x40] = {
    {0x38,0xDC,0x47,0x42,0x95,0x58,0x2B,0xD8, 0x49,0xC4,0xF4,0x5E,0xB6,0x22,0x63,0xBB,
     0xFA,0x81,0x91,0x64,0x60,0x8C,0x4F,0x9A, 0x5C,0x5A,0xC3,0x5C,0x42,0x17,0x36,0xBB,
     0x95,0x29,0x2C,0x24,0xD6,0x51,0x3E,0xB1, 0x2F,0xF8,0x85,0x04,0x73,0xB1,0x11,0xE7,
     0xCF,0x0D,0xFC,0xE3,0xB6,0xDB,0x3A,0xD4, 0xCF,0x64,0x9A,0x9A,0xBA,0xBA,0xBD,0x94},
    {0},
    {0},
    {0x38,0xDC,0x47,0x42,0x95,0x58,0x2B,0xD8, 0x49,0xC4,0xF4,0x5E,0xB6,0x22,0x63,0xBB,
     0xFA,0x81,0x91,0x64,0x60,0x8C,0x4F,0x9A, 0x5C,0x5A,0xC3,0x5C,0x42,0x17,0x36,0xBB,
     0x95,0x29,0x2C,0x24,0xD6,0x51,0x3E,0xB1, 0x2F,0xF8,0x85,0x04,0x73,0xB1,0x11,0xE7,
     0xCF,0x0D,0xFC,0xE3,0xB6,0xDB,0x3A,0xD4, 0xCF,0x64,0x9A,0x9A,0xBA,0xBA,0xBD,0x94},
  };

  printf ("encrypt_with_portability type=%d\n", type);

  switch ( type )
    {
      case 0:
        memcpy (buffer, expected[type], 0x40);
        //aes128cbc_enc (keys[type], iv, buffer, 0x40, buffer);
        break;
      case 1:
        aes128cbc_enc (keys[type], iv, buffer, 0x40, buffer);
        break;
      case 2:
        aes128cbc_enc (keys[type], iv, buffer, 0x40, buffer);
        break;
      case 3:
        memcpy (buffer, expected[type], 0x40);
        //aes128cbc_enc (keys[type], iv, buffer, 0x40, buffer);
        break;
    }

  return;
}

static void
sc_encrypt (int type, u8 *buffer, u8 *iv)
{
  static u8 keys[][16] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  };

  static u8 expected[][0x40] = {
    {0x0B,0xCF,0x9D,0x06,0x47,0x6D,0x59,0x6F, 0x85,0xD4,0x1F,0xD9,0x4B,0xBA,0x60,0x58,
     0xFC,0xAD,0x5A,0xBF,0xC6,0x53,0x47,0xE1, 0xE3,0x79,0x24,0x43,0x18,0xAF,0x3B,0xCC,
     0x0D,0x1E,0xEA,0xA0,0xA3,0x3F,0x98,0x52, 0x8C,0x35,0xB1,0x25,0x12,0xB6,0x3A,0x36,
     0xAF,0x73,0xBA,0x7C,0x43,0x4B,0x24,0xEB, 0x25,0x86,0x64,0x3D,0x70,0x8F,0x0D,0x71},
 
    {0x19,0x30,0x37,0xFA,0x8F,0x48,0xB6,0x6B, 0x80,0x8B,0xAE,0x92,0xCB,0x0D,0xB4,0x4D,
     0x18,0xF6,0xF9,0x79,0xC1,0xDF,0x71,0xAF, 0x68,0x77,0xBC,0x36,0x35,0x75,0x56,0x4F,
     0x59,0x11,0x09,0x64,0xB7,0x4A,0xE1,0x4C, 0x98,0x38,0x06,0xDE,0x17,0x54,0x84,0x52,
     0x00,0xB4,0x75,0xDE,0xA0,0xDC,0xCB,0xCF, 0x4B,0x38,0x7B,0x31,0x43,0xEF,0xC7,0x1F},
 
    {0x30,0x2E,0xDA,0xF2,0xAB,0xCA,0xD4,0x84, 0x59,0x0B,0x04,0x24,0x77,0x1D,0x1C,0x9F,
     0xB4,0xD2,0x73,0x54,0xD3,0xB3,0x04,0xED, 0x5A,0x68,0xB6,0xFB,0x02,0xA4,0x68,0x78,
     0xF9,0xDC,0x4B,0xFD,0x6B,0xA9,0x8A,0x28, 0x12,0x6B,0x2B,0x32,0x9C,0x1F,0x08,0x80,
     0xF5,0x71,0xC6,0xD4,0x69,0x3D,0xDE,0x25, 0x70,0x3F,0x21,0xB7,0x89,0x7C,0xDC,0x25},
 
    {0x61,0x83,0xD6,0xAE,0xD0,0x41,0xE9,0x48, 0xEF,0xD8,0x35,0xE4,0x00,0xCE,0x79,0x0F,
     0x58,0xAB,0xE7,0x8C,0xC2,0x7E,0x62,0x0B, 0xA2,0xAC,0x77,0xCF,0xEB,0x86,0xA3,0x32,
     0x16,0xAC,0x3B,0xDC,0xE6,0x32,0x75,0x75, 0xBB,0xCC,0xEE,0x81,0xE7,0x0C,0xBB,0x79,
     0x9F,0x88,0xFB,0x3C,0x68,0x9A,0x2D,0x88, 0xFB,0x69,0x6F,0xC8,0x58,0x96,0x94,0xBE},
  };

  printf ("encrypt type=%d\n", type);

  switch ( type )
    {
      case 0:
        memcpy (buffer, expected[type], 0x40);
        //aes128cbc_enc (keys[type], iv, buffer, 0x40, buffer);
        break;
      case 1:
        memcpy (buffer, expected[type], 0x40);
        //aes128cbc_enc (keys[type], iv, buffer, 0x40, buffer);
        break;
      case 2:
        memcpy (buffer, expected[type], 0x40);
        //aes128cbc_enc (keys[type], iv, buffer, 0x40, buffer);
        break;
      case 3:
        memcpy (buffer, expected[type], 0x40);
        //aes128cbc_enc (keys[type], iv, buffer, 0x40, buffer);
        break;
    }

  return;
}

int
main (int argc, char *argv[])
{
  int i;
  FILE *in;
  u8 *data;
  unsigned int len;
  unsigned int j;
  int type;

  if (argc != 3)
    die ("Usage : %s method filename\n"
        "\tTest binary file for keys using sc_encrypt* method (0-7)\n", argv[0]);

  if (argv[1][1] != 0)
    die ("Method must be between 0 and 7\n");
  type = argv[1][0] - '0';
  if (type < 0 || type > 7)
    die ("Method must be between 0 and 7\n");

  in = fopen (argv[2], "rb");
  if (in == NULL)
    die ("Unable to open %s", argv[2]);
  fseek (in, 0, SEEK_END);
  len = ftell (in);
  fseek (in, 0, SEEK_SET);
  data = malloc (len);

  if (fread (data, 1, len, in) != len)
    die ("Unable to read index.dat file");
  fclose (in);
  {
    u8 seed[0x14] = {0};
    u8 iv[0x10] = {0};
    u8 key[0x40] = {0};
    u8 expected[0x40];
    u8 input[0x40] = {0};
    u8 output[0x40];

    memset (expected, 0, 0x40);
    memset (output, 0, 0x40);
    memset (input, 0, 0x40);
    memset (key, 0, 0x40);
    memset (iv, 0, 0x10);

    printf("\n");

    switch (type) {
      case 0:
        sc_encrypt_with_portability (0, expected, iv);
        break;
      case 1:
        sc_encrypt_with_portability (1, expected, iv);
        break;
      case 2:
        sc_encrypt_with_portability (2, expected, iv);
        break;
      case 3:
        sc_encrypt_with_portability (3, expected, iv);
        break;
      case 4:
        sc_encrypt (0, expected, iv);
        break;
      case 5:
        sc_encrypt (1, expected, iv);
        break;
      case 6:
        sc_encrypt (2, expected, iv);
        break;
      case 7:
        sc_encrypt (3, expected, iv);
        break;
      default:
        die ("Method must be between 0 and 7\n");
    }

    //hex_dump (expected, 0x40);

    for (j = 0; j < len - 0x10; j++) {
      memset (output, 0, 0x40);
      memset (input, 0, 0x40);
      memset (key, 0, 0x40);
      memset (iv, 0, 0x10);
      memcpy (key, data + j, 0x40);
      //aes256cbc_enc (data + j, iv, input, 0x40, output);
      aes256cbc_enc (key, iv, input, 0x40, output);
      if (memcmp (expected, output, 0x10) == 0) {
        printf ("\nFound the key for method %s %d\n",
            type < 4 ? "sc_encrypt_with_portability" : "sc_encrypt", type);
        printf ("aes256cbc_enc key:\n");
        hex_dump (data + j, 0x10);
        /*
          printf ("expected:\n");
          hex_dump (expected, 0x40);
          printf ("output:\n");
          hex_dump (output, 0x40);
        */
        printf ("\n");
        break;
      }

      memset (output, 0, 0x40);
      memset (input, 0, 0x40);
      memset (key, 0, 0x40);
      memset (iv, 0, 0x10);
      memcpy (key, data + j, 0x40);
      //aes128ctr (data + j, iv, input, 0x40, output);
      aes128ctr (key, iv, input, 0x40, output);
      if (memcmp (expected, output, 0x10) == 0) {
        printf ("\nFound the key for method %s %d\n",
            type < 4 ? "sc_encrypt_with_portability" : "sc_encrypt", type);
        printf ("aes128ctr key:\n");
        hex_dump (data + j, 0x10);
        /*
          printf ("expected:\n");
          hex_dump (expected, 0x40);
          printf ("output:\n");
          hex_dump (output, 0x40);
        */
        printf ("\n");
        break;
      }

      memset (output, 0, 0x40);
      memset (input, 0, 0x40);
      memset (key, 0, 0x40);
      memset (iv, 0, 0x10);
      memcpy (key, data + j, 0x40);
      //aes128cfb (data + j, iv, input, 0x40, output);
      aes128cfb_enc (key, iv, input, 0x40, output);
      if (memcmp (expected, output, 0x10) == 0) {
        printf ("\nFound the key for method %s %d\n",
            type < 4 ? "sc_encrypt_with_portability" : "sc_encrypt", type);
        printf ("aes128cfb key:\n");
        hex_dump (data + j, 0x10);
        /*
          printf ("expected:\n");
          hex_dump (expected, 0x40);
          printf ("output:\n");
          hex_dump (output, 0x40);
        */
        printf ("\n");
        break;
      }

      memset (output, 0, 0x40);
      memset (input, 0, 0x40);
      memset (key, 0, 0x40);
      memset (iv, 0, 0x10);
      memcpy (key, data + j, 0x40);
      //aes128cbc_enc (data + j, iv, input, 0x40, output);
      aes128cbc_enc (key, iv, input, 0x40, output);
      if (memcmp (expected, output, 0x10) == 0) {
        printf ("\nFound the key for method %s %d\n",
            type < 4 ? "sc_encrypt_with_portability" : "sc_encrypt", type);
        printf ("aes128cbc_enc key:\n");
        hex_dump (data + j, 0x10);
        /*
          printf ("expected:\n");
          hex_dump (expected, 0x40);
          printf ("output:\n");
          hex_dump (output, 0x40);
        */
        printf ("\n");
        break;
      }
    }
    printf("\n");
    free (data);
  }
}
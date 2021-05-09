//
// Copyright (c) 2021 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#ifndef ABN_PRIVATE_H
#define ABN_PRIVATE_H

#ifndef MIN
#define MIN(a,b)    ((a)<(b)?(a):(b))
#endif

#ifndef MAX
#define MAX(a,b)    ((a)>(b)?(a):(b))
#endif

// TODO: this calculations assumes that abn.bitsize if multiply of ABN_UNIT_BITSIZE
//       There is plan to enable creating abn that has not aligned bitsize like 42.
//       It should looks like this: (number.bitsize == 0 ? 0 : (((number.bitsize-1) / ABN_UNIT_BITSIZE) + 1)))
#define     GET_VOLUME(number)                  (number.bitsize / ABN_UNIT_BITSIZE)

#define     GET_MOST_SIGNIFICANT_UNIT(number)   (number.chain[GET_VOLUME(number)-1])
#define     GET_LESS_SIGNIFICANT_UNIT(number)   (number.chain[0])

#define     GET_MOST_SIGNIFICANT_BYTE(number)   (0xFF & (GET_MOST_SIGNIFICANT_UNIT(number) >> (ABN_UNIT_BITSIZE-8)))
#define     GET_LESS_SIGNIFICANT_BYTE(number)   (0xFF & GET_LESS_SIGNIFICANT_UNIT(number))

#define     GET_MOST_SIGNIFICANT_BIT(number)    (0x01 & (GET_MOST_SIGNIFICANT_BYTE(number) >> 7))
#define     GET_LESS_SIGNIFICANT_BIT(number)    (0x01 & GET_LESS_SIGNIFICANT_BYTE(number))

#endif  /* ABN_PRIVATE_H */

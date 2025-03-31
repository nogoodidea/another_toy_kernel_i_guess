#ifndef COMMON_ENDIAN
#define COMMON_ENDIAN

#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
#define endian16(value)  __builtin_bswap32(value)
#else
#define endian16(value)  (value)
#endif

#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
#define endian32(value)  __builtin_bswap32(value)
#else
#define endian32(value)  (value)
#endif

#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
#define endian64(value)  __builtin_bswap64(value)
#else
#define endian64(value)  (value)
#endif


#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
#define endian128(value)  __builtin_bswap64(value)
#else
#define endian128(value)  (value)
#endif

#endif // COMMON_ENDIAN

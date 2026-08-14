/* ctype.h - Shadow header for ArcaOS/EMX
 *
 * The EMX <ctype.h> macros reference the __ctype symbol which wlink
 * cannot resolve.  This local shadow provides the same functionality
 * using simple character arithmetic, avoiding the __ctype dependency.
 *
 * Intercepted via "-I sources" in CFLAGS (same pattern as our errno.h).
 */
#ifndef _2H4U_CTYPE_H_
#define _2H4U_CTYPE_H_

/* Character classification */
#define isdigit(c)  ((unsigned char)(c) >= '0' && (unsigned char)(c) <= '9')
#define islower(c)  ((unsigned char)(c) >= 'a' && (unsigned char)(c) <= 'z')
#define isupper(c)  ((unsigned char)(c) >= 'A' && (unsigned char)(c) <= 'Z')
#define isalpha(c)  (isupper(c) || islower(c))
#define isalnum(c)  (isdigit(c) || isalpha(c))
#define isspace(c)  ((unsigned char)(c) == ' '  || \
                     (unsigned char)(c) == '\t' || \
                     (unsigned char)(c) == '\n' || \
                     (unsigned char)(c) == '\r' || \
                     (unsigned char)(c) == '\f' || \
                     (unsigned char)(c) == '\v')
#define isprint(c)  ((unsigned char)(c) >= ' ' && (unsigned char)(c) <= '~')
#define iscntrl(c)  (((unsigned char)(c) >= 0 && (unsigned char)(c) <= 31) || \
                     (unsigned char)(c) == 127)
#define isxdigit(c) (isdigit(c) || \
                     ((unsigned char)(c) >= 'A' && (unsigned char)(c) <= 'F') || \
                     ((unsigned char)(c) >= 'a' && (unsigned char)(c) <= 'f'))
#define ispunct(c)  (isprint(c) && !isalnum(c) && !isspace(c))
#define isgraph(c)  (isprint(c) && !isspace(c))
#define isblank(c)  ((unsigned char)(c) == ' ' || (unsigned char)(c) == '\t')

/* Character conversion */
#define tolower(c)  (isupper(c) ? (int)((unsigned char)(c) - 'A' + 'a') : (int)(c))
#define toupper(c)  (islower(c) ? (int)((unsigned char)(c) - 'a' + 'A') : (int)(c))

#endif /* _2H4U_CTYPE_H_ */

/*
 * errno.h — local shadow of the system errno.h for OS/2 GCC 9.
 *
 * Problem: the system C:/usr/include/errno.h has no include guards and
 * contains:
 *   extern int _near _cdecl volatile errno;
 * GCC's include-fixed stdlib.h first declares "extern int * _errno(void)"
 * and then "#define errno (*_errno())", and then includes <errno.h>.
 * The macro expansion of errno turns the variable declaration into a
 * conflicting function-pointer declaration for _errno.
 *
 * Solution: intercept all <errno.h> includes via "-I sources" (which is
 * searched before system directories).  This file has proper include guards
 * and uses "#ifndef errno" to skip the _errno declaration when the macro is
 * already active, preventing the type conflict.
 */

#ifndef _2H4U_ERRNO_H_
#define _2H4U_ERRNO_H_

#ifndef errno
/* errno not yet a macro — declare the thread-safe accessor and define it */
extern int * _errno(void);
#define errno (*_errno())
#endif

/* Standard ANSI / POSIX error constants */
#ifndef EPERM
#define EPERM         1
#define ENOENT        2
#define ESRCH         3
#define EINTR         4
#define EIO           5
#define ENXIO         6
#define E2BIG         7
#define ENOEXEC       8
#define EBADF         9
#define ECHILD       10
#define EAGAIN       11
#define ENOMEM       12
#define EACCES       13
#define EFAULT       14
#define EBUSY        16
#define EEXIST       17
#define EXDEV        18
#define ENODEV       19
#define ENOTDIR      20
#define EISDIR       21
#define EINVAL       22
#define ENFILE       23
#define EMFILE       24
#define ENOTTY       25
#define EFBIG        27
#define ENOSPC       28
#define ESPIPE       29
#define EROFS        30
#define EMLINK       31
#define EPIPE        32
#define EDOM         33
#define ERANGE       34
#define EDEADLK      36
#define ENAMETOOLONG 38
#define ENOLCK       39
#define ENOSYS       40
#define ENOTEMPTY    41
#define ELOOP        114
#define ENOTSUP      129
#endif /* EPERM */

#endif /* _2H4U_ERRNO_H_ */

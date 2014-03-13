#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "../../deps/regex/regex.h"

#include <io.h>
#include <direct.h>
#ifdef GIT_THREADS
 #include "pthread.h"
#endif

#include "../../include/git2.h"
#include "../common.h"

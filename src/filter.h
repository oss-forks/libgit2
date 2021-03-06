/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_filter_h__
#define INCLUDE_filter_h__

#include "common.h"
#include "../include/git2/filter.h"

/* Amount of file to examine for NUL byte when checking binary-ness */
#define GIT_FILTER_BYTES_TO_CHECK_NUL 8000

/* Possible CRLF values */
typedef enum {
	GIT_CRLF_GUESS = -1,
	GIT_CRLF_BINARY = 0,
	GIT_CRLF_TEXT,
	GIT_CRLF_INPUT,
	GIT_CRLF_CRLF,
	GIT_CRLF_AUTO,
} git_crlf_t;

extern void git_filter_free(git_filter *filter);

/*
 * Available filters
 */

extern git_filter *git_crlf_filter_new(void);
extern git_filter *git_ident_filter_new(void);

#endif

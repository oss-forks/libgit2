
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(libgit2)

##################################################################################################################
## Dependencies

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/")

FIND_PACKAGE(Threads)
IF(CMAKE_USE_WIN32_THREADS_INIT OR CMAKE_USE_PTHREADS_INIT)
	ADD_DEFINITIONS(-DGIT_THREADS)
ENDIF()

FIND_PACKAGE(OpenSSL REQUIRED)
INCLUDE_DIRECTORIES(${OPENSSL_INCLUDE_DIR})
INCLUDE("${OPENSSL_INCLUDE_DIR}/openssl.cmake" OPTIONAL)

FIND_PACKAGE(ZLIB REQUIRED)
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIRS})
INCLUDE("${ZLIB_INCLUDE_DIRS}/zlib.cmake" OPTIONAL)

FIND_PACKAGE(LIBSSH2 REQUIRED)
INCLUDE_DIRECTORIES(${LIBSSH2_INCLUDE_DIR})
INCLUDE("${LIBSSH2_INCLUDE_DIR}/libssh2.cmake" OPTIONAL)

FIND_PACKAGE(ICONV QUIET)
IF(ICONV_FOUND AND NOT LIBGIT2_ICONV_FOUND_REPORTED)
	INCLUDE_DIRECTORIES(${ICONV_INCLUDE_DIR})
	ADD_DEFINITIONS(-DGIT_USE_ICONV)
	MESSAGE(STATUS "Found iconv: ${ICONV_INCLUDE_DIR}/iconv.h")
	SET(LIBGIT2_ICONV_FOUND_REPORTED TRUE CACHE INTERNAL "" FORCE)
ENDIF()

INCLUDE(CheckLibraryExists)
CHECK_LIBRARY_EXISTS(rt clock_gettime "time.h" HAVE_LIBRT)

##################################################################################################################
## Preprocessor definitions

ADD_DEFINITIONS(-DGIT_SSH -DGIT_SSL -DOPENSSL_SHA1 -D_FILE_OFFSET_BITS=64)

IF (WIN32)
	ADD_DEFINITIONS(-DWIN32 -D_WIN32_WINNT=0x0501 -DGIT_WINHTTP)
ENDIF()

IF(MSVC)
	ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
	ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_DEPRECATE)
ENDIF()

IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
	ADD_DEFINITIONS(-DGIT_ARCH_64)
ELSE()
	ADD_DEFINITIONS(-DGIT_ARCH_32)
ENDIF()

##################################################################################################################
## Compilation

SET(WIN32_SOURCES
	src/hash/hash_win32.c
	src/transports/winhttp.c
	src/win32/dir.c
	src/win32/dir.h
	src/win32/error.c
	src/win32/error.h
	src/win32/findfile.c
	src/win32/findfile.h
	src/win32/map.c
	src/win32/mingw-compat.h
	src/win32/msvc-compat.h
	src/win32/posix.h
	src/win32/posix_w32.c
	src/win32/precompiled.c
	src/win32/precompiled.h
	src/win32/pthread.c
	src/win32/pthread.h
	src/win32/utf-conv.c
	src/win32/utf-conv.h
	src/win32/version.h
)

ADD_LIBRARY(libgit2 STATIC EXCLUDE_FROM_ALL
	${WIN32_SOURCES}
	deps/http-parser/http_parser.c
	deps/http-parser/http_parser.h
	deps/regex/config.h
	deps/regex/regcomp.c
	deps/regex/regex.c
	deps/regex/regex.h
	deps/regex/regex_internal.c
	deps/regex/regex_internal.h
	deps/regex/regexec.c
	include/git2/sys/commit.h
	include/git2/sys/config.h
	include/git2/sys/filter.h
	include/git2/sys/index.h
	include/git2/sys/odb_backend.h
	include/git2/sys/refdb_backend.h
	include/git2/sys/reflog.h
	include/git2/sys/refs.h
	include/git2/sys/repository.h
	include/git2/attr.h
	include/git2/blame.h
	include/git2/blob.h
	include/git2/branch.h
	include/git2/buffer.h
	include/git2/checkout.h
	include/git2/clone.h
	include/git2/commit.h
	include/git2/common.h
	include/git2/config.h
	include/git2/cred_helpers.h
	include/git2/diff.h
	include/git2/errors.h
	include/git2/filter.h
	include/git2/graph.h
	include/git2/ignore.h
	include/git2/index.h
	include/git2/indexer.h
	include/git2/inttypes.h
	include/git2/merge.h
	include/git2/message.h
	include/git2/net.h
	include/git2/notes.h
	include/git2/object.h
	include/git2/odb.h
	include/git2/odb_backend.h
	include/git2/oid.h
	include/git2/pack.h
	include/git2/patch.h
	include/git2/pathspec.h
	include/git2/push.h
	include/git2/refdb.h
	include/git2/reflog.h
	include/git2/refs.h
	include/git2/refspec.h
	include/git2/remote.h
	include/git2/repository.h
	include/git2/reset.h
	include/git2/revert.h
	include/git2/revparse.h
	include/git2/revwalk.h
	include/git2/signature.h
	include/git2/stash.h
	include/git2/status.h
	include/git2/stdint.h
	include/git2/strarray.h
	include/git2/submodule.h
	include/git2/sys
	include/git2/tag.h
	include/git2/threads.h
	include/git2/trace.h
	include/git2/transport.h
	include/git2/tree.h
	include/git2/types.h
	include/git2/version.h
	include/git2.h
	src/transports/cred.c
	src/transports/cred_helpers.c
	src/transports/git.c
	src/transports/http.c
	src/transports/local.c
	src/transports/smart.c
	src/transports/smart.h
	src/transports/smart_pkt.c
	src/transports/smart_protocol.c
	src/transports/ssh.c
	src/unix/map.c
	src/unix/posix.h
	src/unix/realpath.c
	src/xdiff/xdiff.h
	src/xdiff/xdiffi.c
	src/xdiff/xdiffi.h
	src/xdiff/xemit.c
	src/xdiff/xemit.h
	src/xdiff/xhistogram.c
	src/xdiff/xinclude.h
	src/xdiff/xmacros.h
	src/xdiff/xmerge.c
	src/xdiff/xpatience.c
	src/xdiff/xprepare.c
	src/xdiff/xprepare.h
	src/xdiff/xtypes.h
	src/xdiff/xutils.c
	src/xdiff/xutils.h
	src/array.h
	src/attr.c
	src/attr.h
	src/attr_file.c
	src/attr_file.h
	src/attrcache.h
	src/bitvec.h
	src/blame.c
	src/blame.h
	src/blame_git.c
	src/blame_git.h
	src/blob.c
	src/blob.h
	src/branch.c
	src/branch.h
	src/bswap.h
	src/buf_text.c
	src/buf_text.h
	src/buffer.c
	src/buffer.h
	src/cache.c
	src/cache.h
	src/cc-compat.h
	src/checkout.c
	src/checkout.h
	src/clone.c
	src/commit.c
	src/commit.h
	src/commit_list.c
	src/commit_list.h
	src/common.h
	src/config.c
	src/config.h
	src/config_cache.c
	src/config_file.c
	src/config_file.h
	src/crlf.c
	src/date.c
	src/delta-apply.c
	src/delta-apply.h
	src/delta.c
	src/delta.h
	src/diff.c
	src/diff.h
	src/diff_driver.c
	src/diff_driver.h
	src/diff_file.c
	src/diff_file.h
	src/diff_patch.c
	src/diff_patch.h
	src/diff_print.c
	src/diff_tform.c
	src/diff_xdiff.c
	src/diff_xdiff.h
	src/errors.c
	src/fetch.c
	src/fetch.h
	src/fetchhead.c
	src/fetchhead.h
	src/filebuf.c
	src/filebuf.h
	src/fileops.c
	src/fileops.h
	src/filter.c
	src/filter.h
	src/fnmatch.c
	src/fnmatch.h
	src/global.c
	src/global.h
	src/graph.c
	src/hash
	src/hash.c
	src/hash.h
	src/hashsig.c
	src/hashsig.h
	src/ident.c
	src/ignore.c
	src/ignore.h
	src/index.c
	src/index.h
	src/indexer.c
	src/iterator.c
	src/iterator.h
	src/khash.h
	src/map.h
	src/merge.c
	src/merge.h
	src/merge_file.c
	src/merge_file.h
	src/message.c
	src/message.h
	src/mwindow.c
	src/mwindow.h
	src/netops.c
	src/netops.h
	src/notes.c
	src/notes.h
	src/object.c
	src/object.h
	src/object_api.c
	src/odb.c
	src/odb.h
	src/odb_loose.c
	src/odb_pack.c
	src/offmap.h
	src/oid.c
	src/oid.h
	src/oidmap.h
	src/pack-objects.c
	src/pack-objects.h
	src/pack.c
	src/pack.h
	src/path.c
	src/path.h
	src/pathspec.c
	src/pathspec.h
	src/pool.c
	src/pool.h
	src/posix.c
	src/posix.h
	src/pqueue.c
	src/pqueue.h
	src/push.c
	src/push.h
	src/refdb.c
	src/refdb.h
	src/refdb_fs.c
	src/refdb_fs.h
	src/reflog.c
	src/reflog.h
	src/refs.c
	src/refs.h
	src/refspec.c
	src/refspec.h
	src/remote.c
	src/remote.h
	src/repo_template.h
	src/repository.c
	src/repository.h
	src/reset.c
	src/revert.c
	src/revparse.c
	src/revwalk.c
	src/revwalk.h
	src/settings.c
	src/sha1_lookup.c
	src/sha1_lookup.h
	src/signature.c
	src/signature.h
	src/sortedcache.c
	src/sortedcache.h
	src/stash.c
	src/status.c
	src/status.h
	src/strmap.c
	src/strmap.h
	src/strnlen.h
	src/submodule.c
	src/submodule.h
	src/sysdir.c
	src/sysdir.h
	src/tag.c
	src/tag.h
	src/thread-utils.c
	src/thread-utils.h
	src/trace.c
	src/trace.h
	src/transport.c
	src/transports
	src/tree-cache.c
	src/tree-cache.h
	src/tree.c
	src/tree.h
	src/tsort.c
	src/unix
	src/userdiff.h
	src/util.c
	src/util.h
	src/vector.c
	src/vector.h
	src/win32
	src/xdiff
	src/zstream.c
	src/zstream.h
)

SET_SOURCE_FILES_PROPERTIES(
		deps/regex/regcomp.c
		deps/regex/regex_internal.c
		deps/regex/regexec.c
	PROPERTIES
		HEADER_FILE_ONLY TRUE
)

IF(NOT WIN32)
	SET_SOURCE_FILES_PROPERTIES(${WIN32_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)
ENDIF()

SET_TARGET_PROPERTIES(libgit2 PROPERTIES OUTPUT_NAME "git2")
TARGET_LINK_LIBRARIES(libgit2 ${LIBSSH2_LIBRARIES} ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES}
	${ICONV_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

IF(WIN32)
	TARGET_LINK_LIBRARIES(libgit2 ws2_32 winhttp rpcrt4)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "(Solaris|SunOS)")
	TARGET_LINK_LIBRARIES(libgit2 socket nsl)
ENDIF()

IF(HAVE_LIBRT)
	TARGET_LINK_LIBRARIES(git2 rt)
ENDIF()

#include "clar_libgit2.h"
#include "config.h"

static git_repository *_repo;
static git_config *_config;

void test_config_lock__initialize(void)
{
	cl_git_pass(git_repository_open(&_repo, cl_fixture("testrepo.git")));
	cl_git_pass(git_repository_config__weakptr(&_config, _repo));
}

void test_config_lock__cleanup(void)
{
	git_repository_free(_repo);
}

void test_config_lock__deny_refresh(void)
{
	cl_git_pass(git_config_refresh(_config));

	cl_git_pass(git_config__lock(_config));
	cl_git_fail_with(GIT_ELOCKED, git_config_refresh(_config));
	cl_git_pass(git_config__unlock(_config));

	cl_git_pass(git_config_refresh(_config));
}

void test_config_lock__multiple_locks(void)
{
	cl_git_pass(git_config_refresh(_config));

	cl_git_pass(git_config__lock(_config));
	cl_git_pass(git_config__lock(_config));
	cl_git_fail_with(GIT_ELOCKED, git_config_refresh(_config));
	cl_git_pass(git_config__unlock(_config));
	cl_git_fail_with(GIT_ELOCKED, git_config_refresh(_config));
	cl_git_pass(git_config__unlock(_config));

	cl_git_pass(git_config_refresh(_config));
}

#!/bin/sh
git remote add upstream git@github.com:libgit2/libgit2.git
git fetch upstream
git rebase upstream/development

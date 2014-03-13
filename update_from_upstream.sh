#!/bin/sh
git remote add upstream git@github.com:libgit2/libgit2.git
git fetch
git rebase upstream/development

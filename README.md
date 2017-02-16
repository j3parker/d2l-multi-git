# d2l-multi-git

A tool for working with multiple git repos at once. Particularly D2L's checkout folder.

## Usage

### `mgit CMD`

Reads a newline-delimited list of git repo dirs (e.g `./foo/bar/.git`) from `stdin` and executes `CMD` once for each of them with the following environment variables:

* `GIT_REPO`: the relative path to the repo (e.g. `foo/bar`)
* `GIT_DIR`: the original git dir (e.g. `./foo/bar/.git`)
* `MULTI_GIT_INDEX`: a sequential integer (starting from 0) incremented for each line of input

If `CMD` needs to be inside the git repo you can `cd $GIT_REPO` inside `CMD` (but `git` itself doesn't require this; it will respect the `GIT_DIR` environment variable.) For example, to delete all files named `Foo.cs` you can do 

```sh
mgit 'cd $GIT_REPO; find -name Foo.cs -type f | xargs rm'
```

### `mgit -cwd CMD`

Finds all the repos that are immediate subdirectories of the current working directory and executes `CMD` in the same way as the vanilla version above (with the same environment variables.)

This is equivalent but more typing and less efficient:

```sh
mgit cwd 'echo $GIT_DIR' | mgit CMD
```

### `mgit filter CMD`

Executes `CMD` once for each git repo specified by `stdin`. Silences `stdout` and `stderr` of `CMD`. If `CMD` has a 0 exit code, `$GIT_DIR` is output. The output of this command can thus be passed back into further invocations of `mgit` (see the examples section.)

### `mgit -cwd filter CMD`

The same as `mgit filter CMD` but rather than taking a list of repos from `stdin` it finds them as immediate subdirectories of the current working directory.

## Examples

Print all git repo names:

```sh
mgit -cwd 'echo $GIT_REPO'
```

Pull every repo:

```sh
mgit -cwd `git pull origin master`
```

Print current branch for all repos:

```sh
mgit -cwd 'echo -n "$GIT_REPO: "; git rev-parse --abbrev-ref HEAD'
```

Reset every repo to updated `origin/master`

```sh
mgit -cwd 'git fetch origin; git checkout master; git reset --hard origin/master'
```

Push every repo that has a branch `foo` and open a pull request (requires [Bitbucket CLI tools](http://todo)):

```sh
mgit -cwd filter 'git rev-parse foo' | mgit 'git push origin foo; stash pull-request foo master'
```

Push local branches named `foo` to unique remote branches (to get independent CI runs) and open PRs

```sh
mgit -cwd filter 'git rev-parse foo' | mgit 'git push origin foo-$MUTLI_GIT_INDEX; stash pull-request foo-$MULTI_GIT_INDEX master'
```

Find every repo that has changed files, create a branch and make a commit:

```sh
mgit -cwd filter 'git diff-index --quiet HEAD' && mgit 'git checkout -b my-branch; git commit -am "All the changes excluding new files"'
```

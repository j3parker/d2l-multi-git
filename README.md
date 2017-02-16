# d2l-multi-git
A tool for using D2L's checkout folder (folder of git repos)

## Examples

Print all git repo names:

```sh
mgit cwd 'echo $GIT_REPO'
```

Pull every repo:

```sh
mgit cwd `git pull origin master`
```

Print current branch for all repos:

```sh
mgit cwd 'echo -n "$GIT_REPO: "; git rev-parse --abbrev-ref HEAD'
```

Reset every repo to updated `origin/master`

```sh
mgit cwd 'git fetch origin; git checkout master; git reset --hard origin/master'
```

Push every repo that has a branch `foo` and open a pull request (requires [Bitbucket CLI tools](http://todo)):

```sh
mgit cwd filter 'git rev-parse foo' | mgit 'git push origin foo; stash pull-request foo master'
```

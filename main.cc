#include <iostream>
#include <memory>
#include <boost/filesystem.hpp>
#include <uv.h>

namespace fs = boost::filesystem;

std::vector<fs::path> get_repos_in_cwd() {
  std::vector<fs::path> res{};

  auto cwd = fs::current_path();

  for (auto& elem : fs::directory_iterator(cwd)) {
    if (!fs::is_directory(elem)) {
      continue;
    }

    if (fs::exists(elem / ".git")) {
      res.push_back(elem);
    }
  }

  return res;
}

void print_dirs(const std::vector<fs::path>& paths) {
  for (auto& path : paths) {
    // TODO: should following symlinks be optional?
    std::cout << fs::canonical(path).string() << "\n";
  }
}

int main(int argc, char** argv, char** envp) {
  auto loop = std::make_unique<uv_loop_t>();
  uv_loop_init(loop.get());

  auto paths = get_repos_in_cwd();
  print_dirs(paths);

  uv_loop_close(loop.get());
}

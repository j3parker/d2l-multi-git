#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void print_repos_from_cwd() {
  auto cwd = fs::current_path();


  for (auto& elem : fs::directory_iterator(cwd)) {
    if (!fs::is_directory(elem)) {
      continue;
    }

    if (fs::exists(elem / ".git")) {
      // TODO: should following symlinks be optional?
      std::cout << fs::canonical(elem).string() << "\n";
    }
  }
}

int main() { print_repos_from_cwd(); }

http_archive(
    name = "com_github_nelhage_boost",
    strip_prefix = "rules_boost-80f513f07641aa6fe77880fb97f881b4ebb6b51d",
    type = "tar.gz",
    urls = [
        "https://github.com/j3parker/rules_boost/archive/80f513f07641aa6fe77880fb97f881b4ebb6b51d.tar.gz"
    ],
)

bind(
  name = "libuv",
  actual = "//third_party:libuv"
)

load("@com_github_nelhage_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

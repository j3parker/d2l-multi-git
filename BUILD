cc_binary(
  name = "mgit",
  srcs = ["main.cc"],
  copts = ["--std=c++1y"],
  linkopts = ["-lpthread"],
  deps = [
    "//external:libuv",
    "@boost//:filesystem",
  ],
)

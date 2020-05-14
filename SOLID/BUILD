load("@rules_cc//cc:defs.bzl", "cc_library")

package(
  default_visibility = ["//:__subpackages__"],
)

cc_library(
  name = "solid_principles",
  hdrs = glob(["*.hpp"]),
  srcs = glob(["*.cpp"]),
  copts = ["-Werror", "-ggdb", "-O0",],
)

load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

package(
  default_visibility = ["//:__subpackages__"],
)

cc_library(
  name = "single_responsibility_principle",
  hdrs = ["single_responsibility_principle.hpp"],
  copts = ["-Werror", "-ggdb", "-O0",],
)

cc_test(
  name = "solid_principles_unit_tests",
  srcs = ["single_responsibility_principle_test.cpp"],
  deps = [
    "@googletest//:gtest",
    "@googletest//:gtest_main",
    "//SOLID:single_responsibility_principle",
  ]
)

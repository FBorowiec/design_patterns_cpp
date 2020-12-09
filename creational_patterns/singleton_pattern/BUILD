load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "singleton_pattern",
    srcs = ["singleton_pattern.cpp"],
    data = ["capitals.txt"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "monostate_pattern",
    srcs = ["monostate_pattern.cpp"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "multiton_pattern",
    srcs = ["multiton_pattern.cpp"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

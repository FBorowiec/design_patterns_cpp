load("@rules_cc//cc:defs.bzl",  "cc_test",  "cc_library")

cc_library(
  name = "chat_room",
  srcs = [
    "chat_room/chat_room.cpp",
    "chat_room/person.cpp",
    ],
  hdrs = glob(["chat_room/*.hpp"]),
)

cc_test(
  name = "mediator_pattern_chat_room",
  srcs = ["chat_room/mediator_pattern.cpp"],
  deps = [
    "@googletest//:gtest",
    "@googletest//:gtest_main",
    ":chat_room",
  ]
)

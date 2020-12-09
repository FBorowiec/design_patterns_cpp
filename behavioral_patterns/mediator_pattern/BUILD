load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

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
        ":chat_room",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

#cc_library(
#  name = "event_broker",
#  hdrs = glob(["event_broker/*.hpp"]),
#  copts = ["-w"],
#  deps = ["@boost//:signals2",],
#)
#
## Uncomment WORKSPACE'S boost and:
## bazel run --copt=-w //behavioral_patterns/mediator_pattern:mediator_pattern_event_broker
#cc_test(
#  name = "mediator_pattern_event_broker",
#  srcs = ["event_broker/event_broker_test.cpp"],
#  deps = [
#    "@googletest//:gtest",
#    "@googletest//:gtest_main",
#    ":event_broker",
#  ]
#)
#

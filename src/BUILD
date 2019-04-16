cc_library(
    name = "partition",
    srcs = ["partition.hpp"],
)

cc_library(
	name = "merge",
	srcs = ["merge.hpp"],
)

cc_binary(
    name = "test",
    srcs = ["test.cpp"],
    deps = [
    	":partition"
    	":merge"
    ],
)
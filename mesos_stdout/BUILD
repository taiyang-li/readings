cc_binary(
  name = 'stout-test',
  srcs = [
    'src/singleton.cpp',
  ],
incs = ['src'],
deps = [
  # '#rt',
  # '#pthread',
  "//common/base-1.0.0:base",
  # "//thirdparty/boost-1.55.0:boost_system",
  # "//thirdparty/boost-1.55.0:boost_filesystem",
  # "//thirdparty/boost-1.55.0:boost_date_time",
  # "//thirdparty/boost-1.55.0:boost_thread",
  # "//thirdparty/protobuf-2.5.0/src:protobuf",
  # "//thirdparty/glog:glog",
],
optimize=[
  '-Wno-error=sign-compare',
  '-Wno-error=unused-function',
  '-Wno-error=unused-variable',
  '-Wno-error=uninitialized',
  '-Wno-error=non-virtual-dtor',
  '-Wno-error=overloaded-virtual',
  '-Wno-error=sign-compare',
],
)

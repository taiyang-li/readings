cc_binary(
  name = "test-benchmark",
  srcs = [
    "test_benchmark.cpp",
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
  ],  
)

cc_binary(
  name = "test-trace",
  srcs = [
    "test_trace.cpp",
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
    '-Wno-error=uninitialized',
    '-Wno-error=non-virtual-dtor',
    '-Wno-error=overloaded-virtual',
  ],  
)

cc_binary(
  name = "test-lock",
  srcs = [
    "test_lock.cpp",
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
    '-Wno-error=uninitialized',
    '-Wno-error=non-virtual-dtor',
    '-Wno-error=overloaded-virtual',
  ],  
)

cc_binary(
  name = "test-superstring",
  srcs = [
    "test_superstring.cpp",
    "superstring.cpp",
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
    '-Wno-error=uninitialized',
    '-Wno-error=non-virtual-dtor',
    '-Wno-error=overloaded-virtual',
  ],  
)

cc_binary(
  name = "test-person",
  srcs = [
    "test_person.cpp",
    "superstring.cpp",
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
    '-Wno-error=uninitialized',
    '-Wno-error=non-virtual-dtor',
    '-Wno-error=overloaded-virtual',
  ],  
)

cc_binary(
  name = "test-complex-rvo",
  srcs = [
    'test_complex.cpp'
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
    '-Wno-error=uninitialized',
    '-Wno-error=non-virtual-dtor',
    '-Wno-error=overloaded-virtual',
  ],  
)

cc_binary(
  name = "test-complex-norvo",
  srcs = [
    'test_complex.cpp'
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
    '-Wno-error=uninitialized',
    '-Wno-error=non-virtual-dtor',
    '-Wno-error=overloaded-virtual',
    '-fno-elide-constructors',
  ],  
)

cc_binary(
  name = "test-rational",
  srcs = [
    'test_rational.cpp'
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
    '-Wno-error=uninitialized',
    '-Wno-error=non-virtual-dtor',
    '-Wno-error=overloaded-virtual',
    '-fno-elide-constructors',
  ],  
)

cc_binary(
  name = "test-string",
  srcs = [
    'test_string.cpp'
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
    '-Wno-error=uninitialized',
    '-Wno-error=non-virtual-dtor',
    '-Wno-error=overloaded-virtual',
    '-fno-elide-constructors',
  ],  
)

cc_binary(
  name = "test-complex1",
  srcs = [
    'test_complex1.cpp'
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
    '-Wno-error=sign-compare',
    '-Wno-error=unused-function',
    '-Wno-error=unused-variable',
    '-Wno-error=uninitialized',
    '-Wno-error=non-virtual-dtor',
    '-Wno-error=overloaded-virtual',
  ],  
)

cc_binary(
  name = "test-mempool",
  srcs = [
    './rational_v1.cpp',
    './rational_v2.cpp',
    './rational_v3.cpp',
    './rational_v4.cpp',
    './test_mempool.cpp',
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
  ],  
)

cc_binary(
  name = "test-inline",
  srcs = [
    './test_inline.cpp',
    './calc.cpp',
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
  ],  
)

cc_binary(
  name = "test-container",
  srcs = [
    './test_container.cpp',
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
  ],  
)

cc_binary(
  name = "test-funcobj",
  srcs = [
    './test_funcobj.cpp',
  ],
  incs = ["./"],
  deps = [
    "#rt",
  ],
  optimize=[
  ],  
)


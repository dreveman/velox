# Copyright (c) Facebook, Inc. and its affiliates.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_library(velox_dwrf_test_utils E2EWriterTestUtil.cpp)

target_link_libraries(
  velox_dwrf_test_utils
  Folly::folly
  velox_dwio_common
  velox_dwio_common_exception
  velox_dwio_dwrf_reader
  velox_dwio_common_test_utils
  velox_dwio_dwrf_writer
  velox_exception
  velox_memory
  velox_type
  velox_vector
  GTest::gtest
  GTest::gtest_main)

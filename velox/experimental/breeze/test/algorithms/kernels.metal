/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Copyright (c) 2024 by Rivos Inc.
 * Licensed under the Apache License, Version 2.0, see LICENSE for details.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "generated/algorithms/kernels-metal.h"

// kernel specializations

using namespace breeze::algorithms;

#define _C(X, Y) X##Y
#define C(X, Y) _C(X, Y)

#define NAME(F, T, BT, IPT) C(, F##_##T##_##BT##x##IPT)

#define add_reduce_op ReduceOpAdd
#define min_reduce_op ReduceOpMin
#define max_reduce_op ReduceOpMax

#define GEN_REDUCE_T(O, T, BT, IPT)                                     \
  kernel void NAME(reduce_##O##_##T, T, BT, IPT)(                       \
      const device T *in [[buffer(0)]], device T *out [[buffer(1)]],    \
      const device int *num_items [[buffer(2)]],                        \
      uint thread_idx [[thread_index_in_threadgroup]],                  \
      uint block_idx [[threadgroup_position_in_grid]]) {                \
    MetalPlatform<BT, WARP_THREADS> p{thread_idx, block_idx};           \
    threadgroup typename DeviceReduce<decltype(p), T>::Scratch scratch; \
    reduce<O##_reduce_op, BT, IPT>(p, in, out, &scratch, *num_items);   \
  }

#define GEN_REDUCE(O)         \
  GEN_REDUCE_T(O, int, 32, 2) \
  GEN_REDUCE_T(O, uint, 32, 2)

GEN_REDUCE(add)
GEN_REDUCE(min)
GEN_REDUCE(max)
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
#include "velox/functions/Registerer.h"
#include "velox/functions/prestosql/Comparisons.h"
#include "velox/functions/prestosql/types/IPAddressRegistration.h"
#include "velox/functions/prestosql/types/IPAddressType.h"
#include "velox/functions/prestosql/types/IPPrefixRegistration.h"
#include "velox/functions/prestosql/types/IPPrefixType.h"
#include "velox/functions/prestosql/types/TimestampWithTimeZoneRegistration.h"
#include "velox/functions/prestosql/types/TimestampWithTimeZoneType.h"

namespace facebook::velox::functions {
namespace {

template <template <class> class T, typename TReturn>
void registerNonSimdizableScalar(const std::vector<std::string>& aliases) {
  registerFunction<T, TReturn, Varchar, Varchar>(aliases);
  registerFunction<T, TReturn, Varbinary, Varbinary>(aliases);
  registerFunction<T, TReturn, bool, bool>(aliases);
  registerFunction<T, TReturn, Timestamp, Timestamp>(aliases);
  registerFunction<T, TReturn, TimestampWithTimezone, TimestampWithTimezone>(
      aliases);
  registerFunction<T, TReturn, IPAddress, IPAddress>(aliases);
}
} // namespace

void registerComparisonFunctions(const std::string& prefix) {
  // Comparison functions also need TimestampWithTimezoneType,
  // independent of DateTimeFunctions
  registerTimestampWithTimeZoneType();
  registerIPAddressType();
  registerIPPrefixType();

  registerNonSimdizableScalar<EqFunction, bool>({prefix + "eq"});
  VELOX_REGISTER_VECTOR_FUNCTION(udf_simd_comparison_eq, prefix + "eq");
  registerFunction<EqFunction, bool, Generic<T1>, Generic<T1>>({prefix + "eq"});

  registerNonSimdizableScalar<NeqFunction, bool>({prefix + "neq"});
  VELOX_REGISTER_VECTOR_FUNCTION(udf_simd_comparison_neq, prefix + "neq");
  registerFunction<NeqFunction, bool, Generic<T1>, Generic<T1>>(
      {prefix + "neq"});

  registerNonSimdizableScalar<LtFunction, bool>({prefix + "lt"});
  VELOX_REGISTER_VECTOR_FUNCTION(udf_simd_comparison_lt, prefix + "lt");
  registerFunction<LtFunction, bool, Orderable<T1>, Orderable<T1>>(
      {prefix + "lt"});

  registerNonSimdizableScalar<GtFunction, bool>({prefix + "gt"});
  VELOX_REGISTER_VECTOR_FUNCTION(udf_simd_comparison_gt, prefix + "gt");
  registerFunction<GtFunction, bool, Orderable<T1>, Orderable<T1>>(
      {prefix + "gt"});

  registerNonSimdizableScalar<LteFunction, bool>({prefix + "lte"});
  VELOX_REGISTER_VECTOR_FUNCTION(udf_simd_comparison_lte, prefix + "lte");
  registerFunction<LteFunction, bool, Orderable<T1>, Orderable<T1>>(
      {prefix + "lte"});

  registerNonSimdizableScalar<GteFunction, bool>({prefix + "gte"});
  VELOX_REGISTER_VECTOR_FUNCTION(udf_simd_comparison_gte, prefix + "gte");
  registerFunction<GteFunction, bool, Orderable<T1>, Orderable<T1>>(
      {prefix + "gte"});

  registerFunction<DistinctFromFunction, bool, Generic<T1>, Generic<T1>>(
      {prefix + "distinct_from"});

  registerFunction<BetweenFunction, bool, int8_t, int8_t, int8_t>(
      {prefix + "between"});
  registerFunction<BetweenFunction, bool, int16_t, int16_t, int16_t>(
      {prefix + "between"});
  registerFunction<BetweenFunction, bool, int32_t, int32_t, int32_t>(
      {prefix + "between"});
  registerFunction<BetweenFunction, bool, int64_t, int64_t, int64_t>(
      {prefix + "between"});
  registerFunction<BetweenFunction, bool, double, double, double>(
      {prefix + "between"});
  registerFunction<BetweenFunction, bool, float, float, float>(
      {prefix + "between"});
  registerFunction<BetweenFunction, bool, Varchar, Varchar, Varchar>(
      {prefix + "between"});
  registerFunction<BetweenFunction, bool, Date, Date, Date>(
      {prefix + "between"});
  registerFunction<BetweenFunction, bool, Timestamp, Timestamp, Timestamp>(
      {prefix + "between"});
  registerFunction<
      BetweenFunction,
      bool,
      LongDecimal<P1, S1>,
      LongDecimal<P1, S1>,
      LongDecimal<P1, S1>>({prefix + "between"});
  registerFunction<
      BetweenFunction,
      bool,
      ShortDecimal<P1, S1>,
      ShortDecimal<P1, S1>,
      ShortDecimal<P1, S1>>({prefix + "between"});
  registerFunction<
      BetweenFunction,
      bool,
      IntervalDayTime,
      IntervalDayTime,
      IntervalDayTime>({prefix + "between"});
  registerFunction<
      BetweenFunction,
      bool,
      IntervalYearMonth,
      IntervalYearMonth,
      IntervalYearMonth>({prefix + "between"});
  registerFunction<
      BetweenFunction,
      bool,
      TimestampWithTimezone,
      TimestampWithTimezone,
      TimestampWithTimezone>({prefix + "between"});
  registerFunction<BetweenFunction, bool, IPAddress, IPAddress, IPAddress>(
      {prefix + "between"});
  registerFunction<BetweenFunction, bool, IPPrefix, IPPrefix, IPPrefix>(
      {prefix + "between"});
}

} // namespace facebook::velox::functions

/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NNCC_CORE_ADT_FEATURE_LAYOUT_H__
#define __NNCC_CORE_ADT_FEATURE_LAYOUT_H__

#include "nncc/core/ADT/feature/Shape.h"

namespace nncc
{
namespace core
{
namespace ADT
{
namespace feature
{

class Layout
{
public:
  using Func = uint32_t (*)(const Shape &, uint32_t ch, uint32_t row, uint32_t col);

public:
  explicit Layout(const Func &func);

public:
  uint32_t offset(const Shape &shape, uint32_t ch, uint32_t row, uint32_t col) const
  {
    return _func(shape, ch, row, col);
  }

private:
  Func _func;
};

} // namespace feature
} // namespace ADT
} // namespace core
} // namespace nncc

#endif // __NNCC_CORE_ADT_FEATURE_LAYOUT_H__

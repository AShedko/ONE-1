/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ONERT_BACKEND_CPU_OPS_SLICELAYER_H__
#define __ONERT_BACKEND_CPU_OPS_SLICELAYER_H__

#include "../Tensor.h"

#include <exec/IFunction.h>

namespace onert
{
namespace backend
{
namespace cpu
{
namespace ops
{

class SliceLayer : public ::onert::exec::IFunction
{
public:
  SliceLayer();

public:
  void configure(const Tensor *input, const Tensor *begin, const Tensor *size, Tensor *output);

  void run();

private:
  void sliceFloat32();
  void sliceQuant8();

  template <typename T>
  void GetBeginAndSizeVectors(int dimensions, const Tensor *begin, const Tensor *size,
                              std::vector<int> *begins, std::vector<int> *sizes);

private:
  const Tensor *_input;
  const Tensor *_begin;
  const Tensor *_size;
  Tensor *_output;
};

} // namespace ops
} // namespace cpu
} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_CPU_OPS_SLICELAYER_H__

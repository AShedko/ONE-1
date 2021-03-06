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

#ifndef __ONERT_BACKEND_CPU_OPS_REDUCESUMLAYER_H__
#define __ONERT_BACKEND_CPU_OPS_REDUCESUMLAYER_H__

#include "../Tensor.h"

#include <exec/IFunction.h>
#include <memory>

namespace nnfw
{
namespace cker
{
class Reduce;
}
} // namespace nnfw

namespace onert
{
namespace backend
{
namespace cpu
{
namespace ops
{

enum class ReduceType
{
  kSum,
  kProd,
  kMax,
  kMin,
  kAny,
  kAll,
};

class ReduceLayer : public ::onert::exec::IFunction
{
public:
  ReduceLayer();
  ~ReduceLayer();

public:
  void configure(const Tensor *input, Tensor *output, ReduceType reduceType,
                 const std::vector<int> &axes, bool keep_dims);

  void run();

private:
  const Tensor *_input;
  Tensor *_output;
  ReduceType _reduceType;
  std::vector<int> _axes;
  bool _keep_dims;

  std::unique_ptr<nnfw::cker::Reduce> _reduce_kernel;
};

} // namespace ops
} // namespace cpu
} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_CPU_OPS_REDUCESUMLAYER_H__

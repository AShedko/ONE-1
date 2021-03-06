/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "ConstantInitializer.h"

namespace onert
{
namespace backend
{
namespace cpu
{

ConstantInitializer::ConstantInitializer(const ir::Operands &operands,
                                         const std::shared_ptr<TensorBuilder> &tensor_builder)
    : IConstantInitializer{operands}, _tensor_builder{tensor_builder}
{
  // DO NOTHING
}

void ConstantInitializer::visit(const ir::operation::Conv2D &node)
{
  const auto &kernel_index = node.getInputs().at(ir::operation::Conv2D::KERNEL);
  const auto &kernel_obj = _operands.at(kernel_index);
  registerCopyInitializer(kernel_index, kernel_obj);

  const auto &bias_index = node.getInputs().at(ir::operation::Conv2D::BIAS);
  const auto &bias_obj = _operands.at(bias_index);
  registerCopyInitializer(bias_index, bias_obj);
}

void ConstantInitializer::visit(const ir::operation::DepthwiseConv2D &node)
{
  const auto &kernel_index = node.getInputs().at(ir::operation::DepthwiseConv2D::KERNEL);
  const auto &kernel_obj = _operands.at(kernel_index);
  registerCopyInitializer(kernel_index, kernel_obj);

  const auto &bias_index = node.getInputs().at(ir::operation::DepthwiseConv2D::BIAS);
  const auto &bias_obj = _operands.at(bias_index);
  registerCopyInitializer(bias_index, bias_obj);
}

void ConstantInitializer::visit(const ir::operation::FullyConnected &node)
{
  const auto &weight_index = node.getInputs().at(ir::operation::FullyConnected::WEIGHT);
  const auto &weight_obj = _operands.at(weight_index);
  registerCopyInitializer(weight_index, weight_obj);

  const auto &bias_index = node.getInputs().at(ir::operation::FullyConnected::BIAS);
  if (!bias_index.undefined())
  {
    const auto &bias_obj = _operands.at(bias_index);
    registerCopyInitializer(bias_index, bias_obj);
  }
}

} // namespace cpu
} // namespace backend
} // namespace onert

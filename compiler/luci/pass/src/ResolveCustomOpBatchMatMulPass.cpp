/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "luci/Pass/ResolveCustomOpBatchMatMulPass.h"

#include <luci/IR/CircleNodes.h>

namespace
{

void resolve_custom_op(luci::CircleCustom *cop)
{
  const std::string custom_code = cop->custom_code();
  const std::vector<uint8_t> custom_options = cop->custom_options();

  if (custom_code == "BatchMatMulV2")
  {
    auto batch_matmul = cop->graph()->nodes()->create<luci::CircleBatchMatMul>();
    // input
    batch_matmul->x(cop->inputs(0));
    batch_matmul->y(cop->inputs(1));
    // adj
    assert(custom_options.size() == 29);
    batch_matmul->adj_x(custom_options[22]);
    batch_matmul->adj_y(custom_options[23]);

    replace(cop).with(batch_matmul);
  }
}

} // namespace

namespace luci
{

bool ResolveCustomOpBatchMatMulPass::run(loco::Graph *g)
{
  bool changed = false;
  for (auto node : loco::active_nodes(loco::output_nodes(g)))
  {
    auto cop = dynamic_cast<luci::CircleCustom *>(node);
    if (not cop)
      continue;

    resolve_custom_op(cop);
    changed = true;
  }

  return changed;
}

} // namespace luci
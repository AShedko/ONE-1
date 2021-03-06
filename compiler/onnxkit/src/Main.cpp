/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "EncodeCommand.hpp"
#include "DecodeCommand.hpp"

#include <cli/App.h>
#include <stdex/Memory.h>

int main(int argc, char **argv)
{
  cli::App app{argv[0]};

  app.insert("encode", stdex::make_unique<EncodeCommand>());
  app.insert("decode", stdex::make_unique<DecodeCommand>());

  return app.run(argc - 1, argv + 1);
}

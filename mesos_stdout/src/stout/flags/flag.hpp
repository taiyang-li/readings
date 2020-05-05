// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __STOUT_FLAGS_FLAG_HPP__
#define __STOUT_FLAGS_FLAG_HPP__

#include <string>

#include <stout/error.hpp>
#include <stout/lambda.hpp>
#include <stout/nothing.hpp>
#include <stout/try.hpp>

namespace flags {

// Forward declaration.
class FlagsBase;

struct Flag
{
  std::string name;
  std::string help;
  bool boolean;
  lambda::function<Try<Nothing>(FlagsBase*, const std::string&)> load;
  lambda::function<Option<std::string>(const FlagsBase&)> stringify;
  lambda::function<Option<Error>(const FlagsBase&)> validate;
};

} // namespace flags {

#endif // __STOUT_FLAGS_FLAG_HPP__

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

#ifndef __STOUT_STOPWATCH_HPP__
#define __STOUT_STOPWATCH_HPP__

#include <string>
#include <sstream>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

class Stopwatch
{
public:
  Stopwatch()
    : running(false)
  {
    started.tv_sec = 0;
    started.tv_nsec = 0;
    stopped.tv_sec = 0;
    stopped.tv_nsec = 0;
  }

  void start()
  {
    started = now();
    running = true;
  }

  void stop()
  {
    stopped = now();
    running = false;
  }

  std::string elapsed() const
  {
    uint64_t interval;
    if (!running)
      interval = diff(stopped, started);
    else
      interval = diff(now(), started);
    std::ostringstream oss;
    oss << (float)interval/1000000000LL;
    return oss.str();
  }

private:
  static timespec now()
  {
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts;
  }

  static uint64_t diff(const timespec& from, const timespec& to)
  {
    return ((from.tv_sec - to.tv_sec) * 1000000000LL)
      + (from.tv_nsec - to.tv_nsec);
  }

  bool running;
  timespec started, stopped;
};

#endif // __STOUT_STOPWATCH_HPP__

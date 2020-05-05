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

#ifndef __STOUT_POSIX_OS_HPP__
#define __STOUT_POSIX_OS_HPP__

#include <errno.h>
#ifdef __sun
#include <sys/loadavg.h>
#define dirfd(dir) ((dir)->d_fd)
#ifndef NAME_MAX
#define NAME_MAX MAXNAMLEN
#endif // NAME_MAX
#else
#include <fts.h>
#endif // __sun
#include <glob.h>
#include <grp.h>
#include <limits.h>
#include <netdb.h>
#include <pwd.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utime.h>

#ifdef __linux__
#include <linux/version.h>
#include <sys/sysinfo.h>
#endif // __linux__

#include <sys/utsname.h>
#include <sys/wait.h>

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <stout/os/close.hpp>
#include <stout/os/environment.hpp>
#include <stout/os/fcntl.hpp>
#include <stout/os/find.hpp>
#include <stout/os/fork.hpp>
#include <stout/os/getcwd.hpp>
#include <stout/os/killtree.hpp>
#include <stout/os/os.hpp>
#include <stout/os/permissions.hpp>
#include <stout/os/read.hpp>
#include <stout/os/realpath.hpp>
#include <stout/os/rename.hpp>
#include <stout/os/sendfile.hpp>
#include <stout/os/signals.hpp>
#include <stout/os/strerror.hpp>
#include <stout/os/touch.hpp>
#include <stout/os/utime.hpp>
#include <stout/os/write.hpp>

#ifdef __FreeBSD__
#include <stout/os/freebsd.hpp>
#endif
#ifdef __linux__
#include <stout/os/linux.hpp>
#endif // __linux__
#include <stout/os/open.hpp>
#ifdef __APPLE__
#include <stout/os/osx.hpp>
#endif // __APPLE__
#ifdef __sun
#include <stout/os/sunos.hpp>
#endif // __sun

#include <stout/os/posix/chown.hpp>
#include <stout/os/raw/environment.hpp>

#include <stout/os/shell.hpp>

namespace os {

// Forward declarations.
inline Try<Nothing> utime(const std::string&);

// Sets the value associated with the specified key in the set of
// environment variables.
inline void setenv(const std::string& key,
                   const std::string& value,
                   bool overwrite = true)
{
  ::setenv(key.c_str(), value.c_str(), overwrite ? 1 : 0);
}


// Unsets the value associated with the specified key in the set of
// environment variables.
inline void unsetenv(const std::string& key)
{
  ::unsetenv(key.c_str());
}


// This function is a portable version of execvpe ('p' means searching
// executable from PATH and 'e' means setting environments). We add
// this function because it is not available on all systems.
//
// NOTE: This function is not thread safe. It is supposed to be used
// only after fork (when there is only one thread). This function is
// async signal safe.
inline int execvpe(const char* file, char** argv, char** envp)
{
  char** saved = os::raw::environment();

  *os::raw::environmentp() = envp;

  int result = execvp(file, argv);

  *os::raw::environmentp() = saved;

  return result;
}


inline Try<Nothing> chmod(const std::string& path, int mode)
{
  if (::chmod(path.c_str(), mode) < 0) {
    return ErrnoError();
  }

  return Nothing();
}


inline Try<Nothing> mknod(
    const std::string& path,
    mode_t mode,
    dev_t dev)
{
  if (::mknod(path.c_str(), mode, dev) < 0) {
    return ErrnoError();
  }

  return Nothing();
}




// Suspends execution for the given duration.
inline Try<Nothing> sleep(const Duration& duration)
{
  timespec remaining;
  remaining.tv_sec = static_cast<long>(duration.secs());
  remaining.tv_nsec =
    static_cast<long>((duration - Seconds(remaining.tv_sec)).ns());

  while (nanosleep(&remaining, &remaining) == -1) {
    if (errno == EINTR) {
      continue;
    } else {
      return ErrnoError();
    }
  }

  return Nothing();
}


// Returns the list of files that match the given (shell) pattern.
inline Try<std::list<std::string>> glob(const std::string& pattern)
{
  glob_t g;
  int status = ::glob(pattern.c_str(), GLOB_NOSORT, NULL, &g);

  std::list<std::string> result;

  if (status != 0) {
    if (status == GLOB_NOMATCH) {
      return result; // Empty list.
    } else {
      return ErrnoError();
    }
  }

  for (size_t i = 0; i < g.gl_pathc; ++i) {
    result.push_back(g.gl_pathv[i]);
  }

  globfree(&g); // Best-effort free of dynamically allocated memory.

  return result;
}


// Returns the total number of cpus (cores).
inline Try<long> cpus()
{
  long cpus = sysconf(_SC_NPROCESSORS_ONLN);

  if (cpus < 0) {
    return ErrnoError();
  }
  return cpus;
}


// Returns load struct with average system loads for the last
// 1, 5 and 15 minutes respectively.
// Load values should be interpreted as usual average loads from
// uptime(1).
inline Try<Load> loadavg()
{
  double loadArray[3];
  if (getloadavg(loadArray, 3) == -1) {
    return ErrnoError("Failed to determine system load averages");
  }

  Load load;
  load.one = loadArray[0];
  load.five = loadArray[1];
  load.fifteen = loadArray[2];

  return load;
}


// Return the system information.
inline Try<UTSInfo> uname()
{
  struct utsname name;

  if (::uname(&name) < 0) {
    return ErrnoError();
  }

  UTSInfo info;
  info.sysname = name.sysname;
  info.nodename = name.nodename;
  info.release = name.release;
  info.version = name.version;
  info.machine = name.machine;
  return info;
}


inline Try<std::list<Process>> processes()
{
  const Try<std::set<pid_t>> pids = os::pids();

  if (pids.isError()) {
    return Error(pids.error());
  }

  std::list<Process> result;
  foreach (pid_t pid, pids.get()) {
    const Result<Process> process = os::process(pid);

    // Ignore any processes that disappear.
    if (process.isSome()) {
      result.push_back(process.get());
    }
  }
  return result;
}


// Overload of os::pids for filtering by groups and sessions.
// A group / session id of 0 will fitler on the group / session ID
// of the calling process.
inline Try<std::set<pid_t>> pids(Option<pid_t> group, Option<pid_t> session)
{
  if (group.isNone() && session.isNone()) {
    return os::pids();
  } else if (group.isSome() && group.get() < 0) {
    return Error("Invalid group");
  } else if (session.isSome() && session.get() < 0) {
    return Error("Invalid session");
  }

  const Try<std::list<Process>> processes = os::processes();

  if (processes.isError()) {
    return Error(processes.error());
  }

  // Obtain the calling process group / session ID when 0 is provided.
  if (group.isSome() && group.get() == 0) {
    group = getpgid(0);
  }
  if (session.isSome() && session.get() == 0) {
    session = getsid(0);
  }

  std::set<pid_t> result;
  foreach (const Process& process, processes.get()) {
    // Group AND Session (intersection).
    if (group.isSome() && session.isSome()) {
      if (group.get() == process.group &&
          process.session.isSome() &&
          session.get() == process.session.get()) {
        result.insert(process.pid);
      }
    } else if (group.isSome() && group.get() == process.group) {
      result.insert(process.pid);
    } else if (session.isSome() && process.session.isSome() &&
               session.get() == process.session.get()) {
      result.insert(process.pid);
    }
  }

  return result;
}


/* TODO: MOVE BACK TO stout/os.hpp*/

// Looks in the environment variables for the specified key and
// returns a string representation of its value. If no environment
// variable matching key is found, None() is returned.
inline Option<std::string> getenv(const std::string& key)
{
  char* value = ::getenv(key.c_str());

  if (value == NULL) {
    return None();
  }

  return std::string(value);
}


inline Try<bool> access(const std::string& path, int how)
{
  if (::access(path.c_str(), how) < 0) {
    if (errno == EACCES) {
      return false;
    } else {
      return ErrnoError();
    }
  }
  return true;
}


// Creates a tar 'archive' with gzip compression, of the given 'path'.
inline Try<Nothing> tar(const std::string& path, const std::string& archive)
{
  Try<std::string> tarOut =
    os::shell("tar %s %s %s", "-czf", archive.c_str(), path.c_str());

  if (tarOut.isError()) {
    return Error("Failed to archive " + path + ": " + tarOut.error());
  }

  return Nothing();
}


// Return the operating system name (e.g. Linux).
inline Try<std::string> sysname()
{
  Try<UTSInfo> info = uname();
  if (info.isError()) {
    return Error(info.error());
  }

  return info.get().sysname;
}


// Return the OS release numbers.
inline Try<Version> release()
{
  Try<UTSInfo> info = uname();
  if (info.isError()) {
    return Error(info.error());
  }

  int major, minor, patch = 0;
#ifndef __FreeBSD__
  // TODO(karya): Replace sscanf with Version::parse() once Version
  // starts supporting labels and build metadata.
  if (::sscanf(
          info.get().release.c_str(),
          "%d.%d.%d",
          &major,
          &minor,
          &patch) != 3) {
    return Error("Failed to parse: " + info.get().release);
  }
#else
  // TODO(dforsyth): Handle FreeBSD patch versions (-pX).
  if (::sscanf(info.get().release.c_str(), "%d.%d-%*s", &major, &minor) != 2) {
    return Error("Failed to parse: " + info.get().release);
  }
#endif
  return Version(major, minor, patch);
}


inline Option<Process> process(
    pid_t pid,
    const std::list<Process>& processes)
{
  foreach (const Process& process, processes) {
    if (process.pid == pid) {
      return process;
    }
  }
  return None();
}


inline std::set<pid_t> children(
    pid_t pid,
    const std::list<Process>& processes,
    bool recursive = true)
{
  // Perform a breadth first search for descendants.
  std::set<pid_t> descendants;
  std::queue<pid_t> parents;
  parents.push(pid);

  do {
    pid_t parent = parents.front();
    parents.pop();

    // Search for children of parent.
    foreach (const Process& process, processes) {
      if (process.parent == parent) {
        // Have we seen this child yet?
        if (descendants.insert(process.pid).second) {
          parents.push(process.pid);
        }
      }
    }
  } while (recursive && !parents.empty());

  return descendants;
}


inline Try<std::set<pid_t> > children(pid_t pid, bool recursive = true)
{
  const Try<std::list<Process>> processes = os::processes();

  if (processes.isError()) {
    return Error(processes.error());
  }

  return children(pid, processes.get(), recursive);
}


namespace libraries {

// Returns the full library name by adding prefix and extension to
// library name.
inline std::string expandName(const std::string& libraryName)
{
  const char* prefix = "lib";
  const char* extension =
#ifdef __APPLE__
    ".dylib";
#else
    ".so";
#endif

  return prefix + libraryName + extension;
}


// Returns the current value of LD_LIBRARY_PATH environment variable.
inline std::string paths()
{
  const char* environmentVariable =
#ifdef __APPLE__
    "DYLD_LIBRARY_PATH";
#else
    "LD_LIBRARY_PATH";
#endif
  const Option<std::string> path = getenv(environmentVariable);
  return path.isSome() ? path.get() : std::string();
}


// Updates the value of LD_LIBRARY_PATH environment variable.
// Note that setPaths has an effect only for child processes
// launched after calling it.
inline void setPaths(const std::string& newPaths)
{
  const char* environmentVariable =
#ifdef __APPLE__
    "DYLD_LIBRARY_PATH";
#else
    "LD_LIBRARY_PATH";
#endif
  setenv(environmentVariable, newPaths);
}


// Append newPath to the current value of LD_LIBRARY_PATH environment
// variable.
inline void appendPaths(const std::string& newPaths)
{
  if (paths().empty()) {
    setPaths(newPaths);
  } else {
    setPaths(paths() + ":" + newPaths);
  }
}

} // namespace libraries {

/* /TODO */

} // namespace os {

#endif // __STOUT_POSIX_OS_HPP__

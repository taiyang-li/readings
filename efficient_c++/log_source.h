#ifndef __EFFECTIVE_CPP_LOG_SOURCE_H__
#define __EFFECTIVE_CPP_LOG_SOURCE_H__

class BaseLogSource
{
  public:
    BaseLogSource() {}
    virtual ~BaseLogSource() {}
};

class LogSource : public BaseLogSource 
{
  public:
    LogSource(const char* file, const char* func, int line) 
      : file_(file), func_(func), line_(line) {}
    ~LogSource() {}

    const char* file() {return file_;}
    const char* func() {return func_;}
    int line() {return line_;}

  private:
      const char* file_;
      const char* func_;
      int line_;
};

#endif  /*LOG_SOURCE_H*/

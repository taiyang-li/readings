#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
using std::vector;

class Bucket 
{
  public:
    Bucket(float begin, float end) : begin_(begin), end_(end), max_(0), min_(0), empty_(true) {}
    ~Bucket() {}

    bool add(int n)
    {
      if ((float)n < begin_ || (float)n >= end_)
        return false;

      if (empty_)
      {
        max_ = n;
        min_ = n;
        empty_ = false;
        return true;
      }
      if (n > max_)
        max_ = n;
      if (n < min_)
        min_ = n;
      return true;
    }

    bool empty() const
    {
      return empty_;
    }

    friend int distance(const Bucket& left, const Bucket& right)
    {
      assert(left.begin_ < right.begin_);
      return right.min_ - left.max_;
    }

    
  private:
    float begin_;
    float end_;
    int max_;
    int min_;
    bool empty_;
};

int maximumGap(vector<int>& nums) 
{
  if (nums.size() <= 1)
    return 0;

  int max_v = nums[0];
  int min_v = nums[0];
  for (size_t i=1; i<nums.size(); ++i)
  {
    if (nums[i] > max_v)
      max_v = nums[i];
    if (nums[i] < min_v)
      min_v = nums[i];
  }
  if (max_v == min_v)
    return 0;

  int len = nums.size();
  float delta = (max_v-min_v)/(float)len;
  vector<Bucket*> buckets(len+1, NULL);
  for (size_t i=0; i<len+1; ++i)
    buckets[i] = new Bucket(min_v+delta*i, min_v+delta*(i+1));

  for (size_t i=0; i<len; i++)
  {
    int idx = (nums[i] - min_v)/delta;
    bool ret = buckets[idx]->add(nums[i]);
    assert(ret != false);
  }

  int max_gap = 0;
  Bucket* last_bucket = NULL;
  for (size_t i=0; i<len+1; i++)
  {
    if (buckets[i]->empty())
      continue;
    
    if (! last_bucket)
    {
      last_bucket = buckets[i];
      continue;
    }

    int gap = distance(*last_bucket, *buckets[i]);
    if (gap > max_gap)
      max_gap = gap;
    last_bucket = buckets[i];
  }
  for (size_t i=0; i<len+1; ++i)
    delete buckets[i];

  return max_gap;
}

int main()
{
  vector<int> nums = {1, 3, 5, 7, 19};
  std::cout << maximumGap(nums) << std::endl;
  return 0;
}


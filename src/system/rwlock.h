#ifndef SRC_SYSTEM_RWLOCK_H
#define SRC_SYSTEM_RWLOCK_H

#include <pthread.h>

namespace testlab {

class RWlock {
 public:
  RWlock();
  // RWlock(const pthread_rwlockattr_t* rwlockattr);
  RWlock(const RWlock& rwlock) = delete;
  RWlock& operator=(const RWlock& rwlock) = delete;
  ~RWlock();

  // shared ownership
  void LockShared();
  bool TryLockShared();

  // exclusive ownership
  void Lock();
  bool TryLock();

  void Unlock();

 private:
  pthread_rwlock_t rwlock_;
  bool is_rwlock_static_allocation_;
};

class RWlockGuard {
 public:
  enum RWlockOwnership {
    kSharedLock,
    kSharedTryLock,
    kExclusiveLock,
    kExclusiveTryLock
  };
  explicit RWlockGuard(RWlock& rwlock, RWlockOwnership ownership);
  ~RWlockGuard();

 private:
  RWlock& rwlock_;
};

}  // namespace testlab

#endif

#include "rwlock.h"

#include <string.h>

#include <iostream>

namespace testlab {

namespace {

// void PrintRWLockInfo(const std::string& msg, int return_code) {
//  if (return_code != 0)
//    std::cerr << msg << " return code - " << return_code << strerror(errno)
//              << std::endl;
//  else
//    std::cout << msg << "return code - " << return_code << std::endl;
//}
//}  // namespace

// RWlock::RWlock() {
//  rwlock_ = PTHREAD_RWLOCK_INITIALIZER;
//  is_rwlock_static_allocation_ = true;
//}

//// RWlock::RWlock(const pthread_rwlockattr_t* rwlockattr) {
////  int return_code = pthread_rwlock_init(&rwlock_, rwlockattr);
////  if (return_code != 0) PrintRWLockInfo("rwlock init failure", return_code);

////  if (return_code == ENOMEM)
////    throw std::bad_alloc();
////  else if (return_code == EAGAIN || return_code == EPERM)
////    throw std::system_error();

////  is_rwlock_static_allocation_ = false;
////}

// RWlock::~RWlock() {
//  if (!is_rwlock_static_allocation_) pthread_rwlock_destroy(&rwlock_);
//}

// void RWlock::LockShared() {
//  int return_code;
//  do
//    return_code = pthread_rwlock_rdlock(&rwlock_);
//  while (return_code == EAGAIN);
//  if (return_code == EDEADLK) {
//    PrintRWLockInfo("LockShared() - failure resource_deadlock_would_occur",
//                    return_code);
//    throw std::system_error();
//  }
//}

// bool RWlock::TryLockShared() {
//  int return_code = pthread_rwlock_tryrdlock(&rwlock_);
//  if (return_code == EBUSY || return_code == EAGAIN) {
//    PrintRWLockInfo("TryLockShared() - failure ", return_code);
//    return false;
//  }
//  return true;
//}

// void RWlock::Lock() {
//  int return_code = pthread_rwlock_wrlock(&rwlock_);
//  if (return_code == EDEADLK) {
//    PrintRWLockInfo("Lock() - failure resource_deadlock_would_occur",
//                    return_code);
//    throw std::system_error();
//  }
//}

// bool RWlock::TryLock() {
//  int return_code = pthread_rwlock_trywrlock(&rwlock_);
//  if (return_code == EBUSY) {
//    PrintRWLockInfo("TryLock() - failure ", return_code);
//    return false;
//  }
//  return true;
//}

// void RWlock::Unlock() { pthread_rwlock_unlock(&rwlock_); }

// RWlockGuard::RWlockGuard(RWlock& rwlock, RWlockOwnership ownership)
//    : rwlock_(rwlock) {
//  switch (ownership) {
//    case kSharedLock:
//      rwlock_.LockShared();
//      break;

//    case kSharedTryLock:
//      rwlock_.TryLockShared();
//      break;

//    case kExclusiveLock:
//      rwlock_.Lock();
//      break;

//    case kExclusiveTryLock:
//      rwlock_.TryLock();
//      break;
//  }
//}

// RWlockGuard::~RWlockGuard() { rwlock_.Unlock(); }

}  // namespace
}  // namespace testlab

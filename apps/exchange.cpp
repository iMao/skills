/**
 * C++14 feature: std::exchange<T,U>(T& a, U&& b)
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// possible realization
template <typename _Tp, typename _Up = _Tp>
_Tp exchange(_Tp& obj, _Up&& new_value) {
  _Tp old_value = std::move(obj);
  obj = std::forward<_Up>(new_value);
  return old_value;
}

class Stream {
 public:
  enum StreamStatus { kIdle, kActive, kStopped };
  Stream() : stream_status_(kIdle) {}
  StreamStatus GetStreamStatus() const noexcept { return stream_status_; }
  StreamStatus SetStreamStatus(StreamStatus new_status) noexcept {
    return std::exchange(stream_status_, new_status);
  }

 private:
  StreamStatus stream_status_;
};

std::string CvtStreamStatus(Stream::StreamStatus stream_status) {
  switch (stream_status) {
    case Stream::StreamStatus::kIdle:
      return std::string("Idle");
    case Stream::StreamStatus::kActive:
      return std::string("Active");
    case Stream::StreamStatus::kStopped:
      return std::string("Stopped");
  }
  return std::string("");
}

int main() {
  Stream stream;

  std::cout << "Stream status: " << CvtStreamStatus(stream.GetStreamStatus())
            << std::endl;

  std::cout << "Stream status: "
            << CvtStreamStatus(
                   stream.SetStreamStatus(Stream::StreamStatus::kActive))
            << std::endl;

  std::cout << "Stream status: "
            << CvtStreamStatus(
                   stream.SetStreamStatus(Stream::StreamStatus::kStopped))
            << std::endl;

  std::cout << "Stream status: "
            << CvtStreamStatus(
                   stream.SetStreamStatus(Stream::StreamStatus::kIdle))
            << std::endl;

  // exchange of  STL containers
  std::vector<int> vec(5, 5);
  auto stlcontainer = std::exchange(vec, {1, 3, 5, 7, 9});
  for (auto& a : vec) {
    std::cout << a << " ";
  }
  std::cout << std::endl;

  if (std::is_same<std::vector<int>, decltype(stlcontainer)>::value) {
    std::cout << "Yes this is std::vector<int>\n";
  }

  for (auto& a : stlcontainer) {
    std::cout << a << " ";
  }
  std::cout << std::endl;

  return 0;
}

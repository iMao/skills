#include <chrono>
#include <memory>
#include <thread>

#include "../patterns/pattern_observer.h"

int main() {
  std::shared_ptr<patterns::WeatherStation> weather_station(
      new patterns::WeatherStation);
  std::shared_ptr<patterns::Observer> current_weather(
      new patterns::CurrentWeather(weather_station.get()));
  std::shared_ptr<patterns::Observer> average_weather(
      new patterns::AverageWeather(weather_station.get()));

  int j = 5;
  while (j--) {
    weather_station->NotifyObservers();
    current_weather->Display();
    average_weather->Display();

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}

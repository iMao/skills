#include "pattern_observer.h"

#include <iostream>

namespace patterns {
WeatherStation::WeatherStation() {
  std::cout << "Object WeatherStation created" << std::endl;
}

WeatherStation::~WeatherStation() {
  observers_.clear();
  std::cout << "Object WeatherStation deleted" << std::endl;
}

void patterns::WeatherStation::RegisterObserver(Observer *observer) {
  observers_.push_back(observer);
}

void patterns::WeatherStation::RemoveObserver(Observer *observer) {
  if (!observers_.empty()) observers_.remove(observer);
}

void WeatherStation::NotifyObservers() {
  for (auto observer : observers_) {
    observer->Update();
  }
}

void WeatherStation::ChangeWeather(float &temperature, float &pressure,
                                   float &humidity) {
  temperature += 5.0f;
  pressure += 5.0f;
  humidity += 5.0f;
}
//------------------observers----------------------------------
CurrentWeather::CurrentWeather(WeatherStation *weather_station)
    : weather_station_(weather_station) {
  std::cout << "Object CurrentWeather created" << std::endl;
  weather_station_->RegisterObserver(this);
}

CurrentWeather::~CurrentWeather() {
  std::cout << "Object CurrentWeather deleted" << std::endl;
}

void CurrentWeather::Update() {
  weather_station_->ChangeWeather(temperature_, pressure_, humidity_);
}

void CurrentWeather::Display() {
  std::cout << std::endl;
  std::cout << "Current weather: " << std::endl;
  std::cout << "current temperature: " << temperature_ << std::endl;
  std::cout << "current pressure: " << pressure_ << std::endl;
  std::cout << "current humidity: " << humidity_ << std::endl;
}

AverageWeather::AverageWeather(WeatherStation *weather_station)
    : weather_station_(weather_station),
      n_(1),
      avg_temperature_(0),
      avg_pressure_(0),
      avg_humidity_(0) {
  std::cout << "Object AverageWeather created" << std::endl;
  weather_station_->RegisterObserver(this);
}

AverageWeather::~AverageWeather() {
  std::cout << "Object AverageWeather deleted" << std::endl;
}

void AverageWeather::Update() {
  float temperature;
  float pressure;
  float humidity;

  weather_station_->ChangeWeather(temperature, pressure, humidity);

  avg_temperature_ *= n_;
  avg_pressure_ *= n_;
  avg_humidity_ *= n_;

  avg_temperature_ += temperature;
  avg_pressure_ += pressure;
  avg_humidity_ += humidity;

  avg_temperature_ /= n_;
  avg_pressure_ /= n_;
  avg_humidity_ /= n_;
  ++n_;
}

void AverageWeather::Display() {
  std::cout << std::endl;
  std::cout << "Average weather: " << std::endl;
  std::cout << "average temperature: " << avg_temperature_ << std::endl;
  std::cout << "average pressure: " << avg_pressure_ << std::endl;
  std::cout << "average humidity: " << avg_humidity_ << std::endl;
}

}  // namespace patterns

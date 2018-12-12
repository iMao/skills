#ifndef PATTERN_OBSERVER_H
#define PATTERN_OBSERVER_H

#include <list>
#include <stdint.h>

namespace patterns {

class Observer {
public:
  virtual void Update() = 0;
  virtual void Display() = 0;
  virtual ~Observer() = default;
};

class Subject {
public:
  virtual void RegisterObserver(Observer *observer) = 0;
  virtual void RemoveObserver(Observer *observer) = 0;
  virtual void NotifyObservers() = 0;
  virtual ~Subject() = default;
};

class WeatherStation : public Subject {
public:
  WeatherStation();
  virtual ~WeatherStation() override;
  virtual void RegisterObserver(Observer *observer) override;
  virtual void RemoveObserver(Observer *observer) override;
  virtual void NotifyObservers() override;

  void ChangeWeather(float &temperature, float &pressure, float &humidity);

private:
  std::list<Observer *> observers_;
};

class CurrentWeather : public Observer {
public:
  CurrentWeather() = delete;
  CurrentWeather(WeatherStation *weather_station);
  virtual ~CurrentWeather() override;
  virtual void Update() override;
  virtual void Display() override;

private:
  WeatherStation *weather_station_;
  float temperature_;
  float pressure_;
  float humidity_;
};

class AverageWeather : public Observer {
public:
  AverageWeather() = delete;
  AverageWeather(WeatherStation *weather_station);
  virtual ~AverageWeather() override;
  virtual void Update() override;
  virtual void Display() override;

private:
  WeatherStation *weather_station_;

  int n_;
  float avg_temperature_;
  float avg_pressure_;
  float avg_humidity_;
};

} // namespace patterns

#endif // PATTERN_OBSERVER_H

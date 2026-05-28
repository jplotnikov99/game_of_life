#pragma once
#include "grid.hpp"
#include <QObject>
#include <mutex>
#include <condition_variable>

class Communicator : public QObject {
  Q_OBJECT
public:
  explicit Communicator(Grid &grid, QObject *parent = nullptr);
  ~Communicator() = default;

public slots:
  void nextState();
  void togglePlayPause();
  void run();

private:
  Grid &grid;
  std::mutex m_mutex;
  std::condition_variable m_cv;
  std::atomic<bool> isPlaying{true};
  std::atomic<int> delay{100}; // Delay in milliseconds for play mode

signals:
  void updated();
};
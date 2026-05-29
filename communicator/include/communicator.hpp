#pragma once
#include "grid.hpp"
#include <QObject>
#include <condition_variable>
#include <mutex>

class Communicator : public QObject {
  Q_OBJECT
public:
  std::atomic<bool> isPlaying{false};
  std::atomic<int> delay{100}; // Delay in milliseconds for play mode
  explicit Communicator(Grid &grid, QObject *parent = nullptr);
  ~Communicator() = default;

public slots:
  void nextState();
  void togglePlayPause();
  void run();
  void randomizeGrid();

private:
  Grid &grid;
  std::mutex m_mutex;
  std::condition_variable m_cv;

signals:
  void updated();
};
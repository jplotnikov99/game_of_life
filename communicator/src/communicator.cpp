#include "communicator.hpp"
#include "state_updater.hpp"
#include <QThread>
#include <qobject.h>

Communicator::Communicator(Grid &grid, QObject *parent)
    : QObject(parent), grid(grid) {}

void Communicator::run() {
  while (true) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock,
              [this] { return isPlaying.load(); }); // sleeps until playing
    nextState();
    lock.unlock();
    QThread::msleep(delay); // Sleep for the specified delay
  }
}

void Communicator::togglePlayPause() {
  isPlaying = !isPlaying;
  m_cv.notify_one();
}

void Communicator::nextState() {
  StateUpdater updater(1);
  updater.update(grid);
  emit updated();
}

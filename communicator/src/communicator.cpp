#include "communicator.hpp"
#include "rule_book.hpp"
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
  RuleBook rulebook(1);
  rulebook.applyRules(grid);
  emit updated();
}

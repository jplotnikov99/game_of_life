#include "communicator.hpp"
#include "grid.hpp"
#include "window.hpp"
#include <QApplication>
#include <QPushButton>
#include <QThread>
#include <QVBoxLayout>
#include <qthread.h>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Grid grid(200, 200);
  Communicator *communicator = new Communicator(grid);

  QThread *thread = new QThread();

  communicator->moveToThread(thread);
  QObject::connect(thread, &QThread::started, communicator, &Communicator::run);
  thread->start();

  MainWindow window(grid, communicator);
  window.show();
  return app.exec();
}
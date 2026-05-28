#include "window.hpp"
#include "communicator.hpp"
#include <qobject.h>

MainWindow::MainWindow(Grid &grid, Communicator *communicator, QWidget *parent)
    : QWidget(parent), gridWidget(new GridWidget(grid, 10, this)),
      communicator(communicator) {

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  QHBoxLayout *buttonLayout = new QHBoxLayout();

  buttonLayout->addWidget(nextStateButton);
  buttonLayout->addWidget(playPauseButton);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addWidget(gridWidget);
  QObject::connect(communicator, &Communicator::updated, gridWidget,
                   qOverload<>(&GridWidget::update));
  QObject::connect(nextStateButton, &QPushButton::clicked, this,
                   &MainWindow::nextState);
  QObject::connect(playPauseButton, &QPushButton::clicked, this,
                   &MainWindow::togglePlayPause);
};

void MainWindow::nextState() { communicator->nextState(); }

void MainWindow::togglePlayPause() {}
#include "window.hpp"
#include "communicator.hpp"
#include <QStyle>
#include <qobject.h>

MainWindow::MainWindow(Grid &grid, Communicator *communicator, QWidget *parent)
    : QWidget(parent), gridWidget(new GridWidget(grid, 5, this)),
      communicator(communicator) {

  loadStyles();

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  QHBoxLayout *buttonLayout = new QHBoxLayout();

  buttonLayout->addWidget(nextStateButton);
  buttonLayout->addWidget(resetButton);
  buttonLayout->addWidget(playPauseButton);
  buttonLayout->addWidget(speedSlider);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addWidget(gridWidget);
  QObject::connect(communicator, &Communicator::updated, gridWidget,
                   qOverload<>(&GridWidget::update));
  QObject::connect(nextStateButton, &QPushButton::clicked, this,
                   &MainWindow::nextState);
  QObject::connect(resetButton, &QPushButton::clicked, gridWidget,
                   &GridWidget::resetGrid);
  QObject::connect(playPauseButton, &QPushButton::clicked, this,
                   &MainWindow::togglePlayPause);
  QObject::connect(
      speedSlider, &QSlider::valueChanged, this,
      [communicator](int value) { communicator->delay = (510 - value); });
};

void MainWindow::nextState() { communicator->nextState(); }

void MainWindow::togglePlayPause() {
  communicator->togglePlayPause();
  if (communicator->isPlaying.load()) {
    playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
  } else {
    playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
  }
}

void MainWindow::loadStyles() {
  // playPauseButton style
  playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

  // speedSlider style
  speedSlider->setRange(10, 500);
  speedSlider->setValue(410);
  speedSlider->setTickInterval(10);
  speedSlider->setFixedWidth(250);
}
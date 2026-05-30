#include "window.hpp"
#include "communicator.hpp"
#include <QLabel>
#include <QStyle>
#include <qobject.h>

MainWindow::MainWindow(Grid &grid, Communicator *communicator, QWidget *parent)
    : QWidget(parent), gridWidget(new GridWidget(grid, 5, this)),
      communicator(communicator) {
  loadNames();
  loadStyles();
  makeLayers();
  connectSignals();

  QObject::connect(
      speedSlider, &QSlider::valueChanged, this,
      [communicator](int value) { communicator->delay = (510 - value); });
};

void MainWindow::nextState() { communicator->nextState(); }

void MainWindow::randomizeGrid() { communicator->randomizeGrid(); }

void MainWindow::togglePlayPause() {
  communicator->togglePlayPause();
  if (communicator->isPlaying.load()) {
    playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
  } else {
    playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
  }
}

void MainWindow::loadNames() {
  nextStateButton = new QPushButton("Next State");
  resetButton = new QPushButton("Reset");
  randomizeButton = new QPushButton("Randomize");
  playPauseButton = new QPushButton();
  speedSlider = new QSlider(Qt::Horizontal);
  basicLabel = new QPushButton("Basic Cell");
  hungerLabel = new QPushButton("Hunger Cell");
  vegitationLabel = new QPushButton("Vegitation Cell");
}

void MainWindow::loadStyles() {
  // window style
  setStyleSheet("background-color: #222; color: white; font-family: Arial;");

  // playPauseButton style
  playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
  playPauseButton->setStyleSheet("background-color: #444; color: white;");

  // nextStateButton, resetButton, randomizeButton styles
  QString buttonStyle =
      "background-color: #444; color: white; padding: 5px 10px;";
  nextStateButton->setStyleSheet(buttonStyle);
  resetButton->setStyleSheet(buttonStyle);
  randomizeButton->setStyleSheet(buttonStyle);

  // speedSlider style
  speedSlider->setRange(10, 500);
  speedSlider->setValue(410);
  speedSlider->setTickInterval(10);
  speedSlider->setFixedWidth(250);

  // cell type labels
  basicLabel->setStyleSheet("background-color: gray; color: black;");

  hungerLabel->setStyleSheet("background-color: #800000; color: black;");
  vegitationLabel->setStyleSheet("background-color: #006400; color: black;");
}

void MainWindow::makeLayers() {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  QHBoxLayout *firstLayer = new QHBoxLayout();
  firstLayer->addWidget(nextStateButton);
  firstLayer->addWidget(resetButton);
  firstLayer->addWidget(randomizeButton);
  firstLayer->addWidget(playPauseButton);

  QHBoxLayout *secondLayer = new QHBoxLayout();
  secondLayer->addWidget(speedSlider);

  QHBoxLayout *thirdLayer = new QHBoxLayout();
  QVBoxLayout *cellTypeLegend = new QVBoxLayout();
  cellTypeLegend->addWidget(basicLabel);
  cellTypeLegend->addWidget(hungerLabel);
  cellTypeLegend->addWidget(vegitationLabel);
  thirdLayer->addWidget(gridWidget);
  thirdLayer->addLayout(cellTypeLegend);

  mainLayout->addLayout(firstLayer);
  mainLayout->addLayout(secondLayer);
  mainLayout->addLayout(thirdLayer);
}

void MainWindow::connectSignals() {
  QObject::connect(communicator, &Communicator::updated, gridWidget,
                   qOverload<>(&GridWidget::update));
  QObject::connect(nextStateButton, &QPushButton::clicked, this,
                   &MainWindow::nextState);
  QObject::connect(resetButton, &QPushButton::clicked, gridWidget,
                   &GridWidget::resetGrid);
  QObject::connect(randomizeButton, &QPushButton::clicked, this,
                   &MainWindow::randomizeGrid);
  QObject::connect(playPauseButton, &QPushButton::clicked, this,
                   &MainWindow::togglePlayPause);
  QObject::connect(basicLabel, &QPushButton::clicked, gridWidget,
                   [this]() { gridWidget->updateCellType(CellType::BASIC); });
  QObject::connect(hungerLabel, &QPushButton::clicked, gridWidget,
                   [this]() { gridWidget->updateCellType(CellType::HUNGER); });
  QObject::connect(
      vegitationLabel, &QPushButton::clicked, gridWidget,
      [this]() { gridWidget->updateCellType(CellType::VEGITATION); });
}
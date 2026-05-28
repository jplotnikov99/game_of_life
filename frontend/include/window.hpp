#pragma once

#include "communicator.hpp"
#include "grid_widget.hpp"
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <qpushbutton.h>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(Grid &grid, Communicator *communicator,
                      QWidget *parent = nullptr);

  ~MainWindow() = default;

  void nextState();
  void togglePlayPause();
  void loadStyles();

private:
  QPushButton *nextStateButton = new QPushButton("Next State");
  QPushButton *resetButton = new QPushButton("Reset");
  QPushButton *playPauseButton = new QPushButton();
  QSlider *speedSlider = new QSlider(Qt::Horizontal);
  GridWidget *gridWidget;
  Communicator *communicator;
};
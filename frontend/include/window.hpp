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
  void randomizeGrid();
  void loadStyles();
  void loadNames();

private:
  QPushButton *nextStateButton;
  QPushButton *resetButton;
  QPushButton *randomizeButton;
  QPushButton *playPauseButton;
  QSlider *speedSlider;
  QPushButton *basicLabel;
  QPushButton *hungerLabel;
  GridWidget *gridWidget;
  Communicator *communicator;
};
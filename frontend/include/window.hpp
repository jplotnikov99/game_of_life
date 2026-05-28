#pragma once

#include "communicator.hpp"
#include "grid_widget.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <qpushbutton.h>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(Grid &grid, Communicator *communicator, QWidget *parent = nullptr);

  ~MainWindow() = default;

  void nextState();
  void togglePlayPause();

private:
  QPushButton *nextStateButton = new QPushButton("Next State");
  QPushButton *playPauseButton = new QPushButton("Play/Pause");
  GridWidget *gridWidget;
  Communicator *communicator;
};
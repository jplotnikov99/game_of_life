#pragma once

#include "grid_widget.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(Grid &grid, QWidget *parent = nullptr);

  ~MainWindow() = default;

private:
  QVBoxLayout *layout = new QVBoxLayout(this);
  QPushButton *button = new QPushButton("Next State");
  GridWidget *widget;
};
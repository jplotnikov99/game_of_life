#pragma once

#include "grid.hpp"
#include <QObject>
#include <QWidget>

class GridWidget : public QWidget {
  Q_OBJECT

public:
  Grid &m_grid;

  explicit GridWidget(Grid &grid, int cellSize = 20, QWidget *parent = nullptr);
  ~GridWidget() = default;

protected:
  void paintEvent(QPaintEvent *) override;

private:
  int m_cellSize;
};
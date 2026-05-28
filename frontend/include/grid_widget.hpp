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

  void resetGrid();

protected:
  void paintEvent(QPaintEvent *) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  void handleMouseEvent(QMouseEvent *event);
  int m_cellSize;
};
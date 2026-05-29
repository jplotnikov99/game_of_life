#pragma once

#include "grid.hpp"
#include <QObject>
#include <QWidget>
#include <qcolor.h>

class GridWidget : public QWidget {
  Q_OBJECT

public:
  Grid &m_grid;

  explicit GridWidget(Grid &grid, int cellSize = 20, QWidget *parent = nullptr);
  ~GridWidget() = default;

  void resetGrid();
  QColor cellTypeToColor(BasicCell &cell) const;
  void updateCellType(CellType type) { currentCellType = type; }
  void setCellTypeAt(int row, int col);

protected:
  void paintEvent(QPaintEvent *) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  void handleMouseEvent(QMouseEvent *event);
  CellType currentCellType = CellType::BASIC;
  int m_cellSize;
};
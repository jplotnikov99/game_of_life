#include "grid_widget.hpp"
#include <QPainter>

GridWidget::GridWidget(Grid &grid, int cellSize, QWidget *parent)
    : QWidget(parent), m_grid(grid), m_cellSize(cellSize) {
  setFixedSize(m_grid.getrows() * cellSize, m_grid.getcols() * cellSize);
}

void GridWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  for (int r = 0; r < m_grid.getrows(); r++) {
    for (int c = 0; c < m_grid.getcols(); c++) {
      QRect cell(c * m_cellSize, r * m_cellSize, m_cellSize, m_cellSize);
      painter.fillRect(cell,
                       m_grid.getCell(r, c).alive ? Qt::black : Qt::white);
      painter.drawRect(cell);
    }
  }
}
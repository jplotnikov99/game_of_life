#include "grid_widget.hpp"
#include "grid.hpp"
#include <QMouseEvent>
#include <QPainter>

GridWidget::GridWidget(Grid &grid, int cellSize, QWidget *parent)
    : QWidget(parent), m_grid(grid), m_cellSize(cellSize) {
  setFixedSize(m_grid.getrows() * cellSize, m_grid.getcols() * cellSize);
}

void GridWidget::resetGrid() {
  for (int r = 0; r < m_grid.getrows(); r++) {
    for (int c = 0; c < m_grid.getcols(); c++) {
      m_grid.setCellState(r, c, false);
    }
  }
  update();
}

QColor GridWidget::cellTypeToColor(BasicCell &cell) const {
  if (cell.getType() == "Basic") {
    return Qt::black;
  } else if (cell.getType() == "Hunger") {
    return Qt::red;
  }
  return Qt::gray; // Default color for unknown types
}

void GridWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  for (int r = 0; r < m_grid.getrows(); r++)
    for (int c = 0; c < m_grid.getcols(); c++) {
      QRect cell(c * m_cellSize, r * m_cellSize, m_cellSize, m_cellSize);
      painter.fillRect(cell, m_grid.getCell(r, c).alive
                                 ? cellTypeToColor(m_grid.getCell(r, c))
                                 : Qt::white);
    }
}

void GridWidget::mousePressEvent(QMouseEvent *event) {
  handleMouseEvent(event);
}

void GridWidget::mouseMoveEvent(QMouseEvent *event) { handleMouseEvent(event); }

void GridWidget::handleMouseEvent(QMouseEvent *event) {
  int col = event->position().x() / m_cellSize;
  int row = event->position().y() / m_cellSize;

  if (row >= 0 && row < m_grid.getrows() && col >= 0 &&
      col < m_grid.getcols()) {
    m_grid.setCellState(row, col, true);
    update();
  }
}

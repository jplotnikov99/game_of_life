#include "grid_widget.hpp"
#include "grid.hpp"
#include <QMouseEvent>
#include <QPainter>
#include <memory>

GridWidget::GridWidget(Grid &grid, int cellSize, QWidget *parent)
    : QWidget(parent), m_grid(grid), m_cellSize(cellSize) {
  setFixedSize(m_grid.getrows() * cellSize, m_grid.getcols() * cellSize);
}

void GridWidget::resetGrid() {
  for (int r = 0; r < m_grid.getrows(); r++) {
    for (int c = 0; c < m_grid.getcols(); c++) {
      m_grid.setCell(r, c, std::make_unique<BasicCell>(false));
    }
  }
  update();
}

QColor GridWidget::cellTypeToColor(BasicCell &cell) const {
  switch (cell.getType()) {
  case CellType::BASIC:
    return Qt::gray;
  case CellType::HUNGER:
    return Qt::darkRed;
  case CellType::VEGITATION:
    return Qt::darkGreen;
  default:
    return Qt::gray; // Default color for unknown types
  }
}

void GridWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  for (int r = 0; r < m_grid.getrows(); r++)
    for (int c = 0; c < m_grid.getcols(); c++) {
      QRect cell(c * m_cellSize, r * m_cellSize, m_cellSize, m_cellSize);
      painter.fillRect(cell, m_grid.getCell(r, c).alive
                                 ? cellTypeToColor(m_grid.getCell(r, c))
                                 : Qt::black);
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
    setCellTypeAt(row, col);
    update();
  }
}

void GridWidget::setCellTypeAt(int row, int col) {
  switch (currentCellType) {
  case CellType::BASIC:
    m_grid.setCell(row, col, std::make_unique<BasicCell>(true));
    break;
  case CellType::HUNGER:
    m_grid.setCell(row, col, std::make_unique<HungerCell>(true));
    break;
  case CellType::VEGITATION:
    m_grid.setCell(row, col, std::make_unique<VegitationCell>(true, 0));
    break;
  }
}
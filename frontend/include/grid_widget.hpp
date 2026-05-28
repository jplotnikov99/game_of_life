#pragma once

#include "grid.hpp"
#include "state_updater.hpp"
#include <QObject>
#include <QWidget>

class GridWidget : public QWidget {
  Q_OBJECT

public:
  explicit GridWidget(Grid &grid, int cellSize = 20, QWidget *parent = nullptr);

  ~GridWidget() = default;

public slots:
  void nextState() { m_stateUpdater.update(m_grid); }

protected:
  void paintEvent(QPaintEvent *) override;

private:
  int m_cellSize;
  Grid &m_grid;
  StateUpdater m_stateUpdater;
};
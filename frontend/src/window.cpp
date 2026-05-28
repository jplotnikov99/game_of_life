#include "window.hpp"

MainWindow::MainWindow(Grid &grid, QWidget *parent)
    : QWidget(parent), widget(new GridWidget(grid, 10, this)) {
  layout->addWidget(button);
  layout->addWidget(widget);
  QObject::connect(button, &QPushButton::clicked, widget,
                   &GridWidget::nextState);
};
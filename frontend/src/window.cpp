#include "window.hpp"
#include "communicator.hpp"

MainWindow::MainWindow(Grid &grid, QWidget *parent)
    : QWidget(parent), gridWidget(new GridWidget(grid, 10, this)) {
  layout->addWidget(button);
  layout->addWidget(gridWidget);
  QObject::connect(button, &QPushButton::clicked, this, &MainWindow::nextState);
  QObject::connect(communicator, &Communicator::updated, gridWidget,
                   qOverload<>(&GridWidget::update));
};

void MainWindow::nextState() { communicator->stateUpdate(gridWidget->m_grid); }
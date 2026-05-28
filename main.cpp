#include "grid.hpp"
#include "window.hpp"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);



  Grid grid(100, 100);
  grid.setCellState(10, 10, true);
  grid.setCellState(10, 11, true);
  grid.setCellState(10, 12, true);

  MainWindow window(grid);
  window.show();
  return app.exec();
}
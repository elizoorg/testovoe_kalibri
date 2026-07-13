#include <QApplication>
#include "server_window.h"

/**
 * @brief Точка входа серверного GUI-приложения.
 *
 * Создаёт экземпляр ServerWindow и запускает цикл обработки событий Qt.
 */
int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  app.setApplicationName("QtTelecomServer");
  app.setApplicationVersion("1.0.0");
  app.setOrganizationName("TelecomDemo");

  ServerWindow window;
  window.show();

  return app.exec();
}
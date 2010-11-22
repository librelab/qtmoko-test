#ifndef APPRUNNINGSCREEN_H
#define APPRUNNINGSCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QEvent>
#include <QApplication>
#include <QMouseEvent>
#include <QTimer>
#include <QDesktopWidget>

// This is fullscreen dialog displayed when X application is running. We need
// to avoid any Qtopia drawing when X app is running so that it's screen is not
// damaged by Qtopia redraws. After long (5s) press we take screenshot of the X
// app, hide and give control back to QX main dialog.
class AppRunningScreen : public QWidget
{
    Q_OBJECT

public:
    AppRunningScreen();
    void showScreen();
    QPixmap pixmap;

signals:
    void deactivated();

protected:
    bool event(QEvent *);
    void paintEvent(QPaintEvent *);
    void enterFullScreen();
};

#endif // APPRUNNINGSCREEN_H

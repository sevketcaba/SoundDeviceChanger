#ifndef BCONTROLLER_H
#define BCONTROLLER_H

#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>

class QtAwesome;

class BController : public QObject
{
    Q_OBJECT

public:
    explicit BController(QObject *parent = nullptr);
    ~BController();

protected slots:
    void createMenu();
    void clearMenu();
    void menuClicked();

    void defaultChanged();
protected:
    QSystemTrayIcon *mTray;
    QMenu *mMenu;
    QtAwesome *mFont;
};

#endif // BCONTROLLER_H

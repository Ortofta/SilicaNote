#include <QGuiApplication>
#include <QDir>

#ifdef DESKTOP
#include <QGLWidget>
#endif

#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickView>

#ifdef HAS_BOOSTER
#include <MDeclarativeCache>
#endif

#include "sailfishapplication.h"

QGuiApplication *Sailfish::createApplication(int &argc, char **argv)
{
#ifdef HAS_BOOSTER
    return MDeclarativeCache::qApplication(argc, argv);
#else
    return new QGuiApplication(argc, argv);
#endif
}

QQuickView *Sailfish::createView(const QString &file)
{
    QQuickView *view;
#ifdef HAS_BOOSTER
    view = MDeclarativeCache::qDeclarativeView();
#else
    view = new QQuickView;
#endif
    
    bool isDesktop = qApp->arguments().contains("-desktop");
    
    QString path;
    if (isDesktop) {
        path = qApp->applicationDirPath() + QDir::separator();
#ifdef DESKTOP
        view->setViewport(new QGLWidget);
#endif
    } else {
        path = QString(DEPLOYMENT_PATH);
    }
    view->setSource(QUrl::fromLocalFile(path + file));
    
    return view;
}

void Sailfish::showView(QQuickView* view) {
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    
    bool isDesktop = qApp->arguments().contains("-desktop");
    
    if (isDesktop) {
        view->setFixedSize(480, 854);
        view->rootObject()->setProperty("_desktop", true);
        view->show();
    } else {
        view->setAttribute(Qt::WA_OpaquePaintEvent);
        view->setAttribute(Qt::WA_NoSystemBackground);
        view->viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
        view->viewport()->setAttribute(Qt::WA_NoSystemBackground);
        
        view->showFullScreen();
    }
}



#include "mainwindow.h"

#include <QApplication>
#include <QLoggingCategory>
#include <QFile>
#include <QDateTime>


QScopedPointer<QFile> logFile;


void messageLogger(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logFile.reset(new QFile("/home/roachhh/loggers/logFile.txt"));
    logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageLogger);
    MainWindow w;
    w.show();
    return a.exec();
}

void messageLogger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream out(logFile.data());
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    if (type == QtInfoMsg){
        out << "INF ";
    } else if (type == QtDebugMsg) {
        out << "DBG ";
    } else if (type == QtWarningMsg) {
        out << "WRN ";
    } else if (type == QtCriticalMsg) {
        out << "CRT ";
    } else if (type == QtFatalMsg) {
        out << "FTL ";
    }

    out << context.category << ": " << msg << Qt::endl;
    out.flush();
}

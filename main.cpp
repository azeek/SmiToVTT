#include <QCoreApplication>
#include <QDebug>
#include "ConvertVTT.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConvertVTT cvt ;

    cvt.SmiTo("Test.smi", "Test.vtt") ;
    qDebug() << "SmiTo close " ;
    return a.exec();
}

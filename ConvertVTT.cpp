//
// Created by zkdlf on 2018-07-23.
//
#include "ConvertVTT.h"
#include <QFile>
#include <QtCore/qtextstream.h>
#include <QDebug>

bool ConvertVTT::SmiTo(const QString &in_file_path, const QString &out_file_path) {
    QFile in_file(in_file_path) ;
    QFile out_file(out_file_path) ;


    if (!in_file.open(QIODevice::ReadOnly) || !out_file.open(QIODevice::WriteOnly | QFile::Truncate)) {
         ; qDebug() << "File Open error.... " ;
        return false ;
    }
    QTextStream in_stream(&in_file) ;
    in_stream.setCodec("EUC-KR") ;
    in_stream.setAutoDetectUnicode(true) ;


    QTextStream out_stream(&out_file) ;
    out_stream.setCodec("UTF-8") ;
    out_stream.setGenerateByteOrderMark(true) ;
    out_stream << QString::fromLocal8Bit("WEBVTT\n\n");


    int line =  0;
    QString line_string  ;
    QStringList  line_list ;
    while (in_stream.readLineInto(&line_string)) {
        line_list << line_string ;
    }


    while (line < line_list.size()) {
        if(line_list[line].toLower().contains(QRegExp("sync start=[0-9]+"))){
            QRegExp rx("[0-9]+") ;
            rx.indexIn(line_list.at(line));
            QString start_number =rx.cap(0);
            QString temp = "" ;
            int p = line + 1 ;

            while (p < line_list.size() && !line_list[p].toLower().contains(QRegExp("sync start=[0-9]+>"))) {
                temp += line_list[p] ;
                p++;
            }

            if (p >= line_list.size() )
                break ;

            if (rx.indexIn(line_list[p]) == -1 )
                break ;

            QString end_number = rx.cap(0) ;
            if (temp != "") {
                temp = temp.replace("\n", "").replace("<br>", "\n") ;
                temp = temp.replace(QRegExp(".*<P"), "<P") ;
                temp = temp.replace(QRegExp("\n\n| \n"), "\n") ;
                temp = temp.replace(QRegExp("<b>|</b>|&nbsp;"), "") ;
            }

            if (temp == "<P CLASS=SUBTTL>") {
                line = p ;
                continue ;
            }

            QString  str_write= QString("%1 --> %2\n")
                    .arg(numberToTime(start_number))
                    .arg(numberToTime(end_number)) ;

            out_stream << str_write ;
            out_stream << QString("%1\n\n").arg(temp) ;
            line = p ;
        }
        else
            line++;
    }


    in_file.close();
    out_file.close();
    return true;
}

QString ConvertVTT::numberToTime(const QString &number) {
    int number_time = number.toInt() ;
    int r, s, m, h;

    r = number_time % 1000;
    s = number_time / 1000;
    m = s / 60;
    s = s % 60;
    h = m / 60;
    m = m % 60;
    return QString("%1:%2:%3.%4")
            .arg(h)
            .arg(m)
            .arg(s)
            .arg(r) ;
}


//
// Created by zkdlf on 2018-07-23.
//

#ifndef SMITOVTT_CONVERTSMI2VTT_H
#define SMITOVTT_CONVERTSMI2VTT_H

#include <QObject>

class ConvertVTT : public QObject {
    Q_OBJECT
public:
    explicit ConvertVTT(QObject *parent = nullptr) : QObject(parent) {}

    bool SmiTo(const QString &in_file_path, const QString &out_file_path) ;

private:
    QString numberToTime(const QString& number) ;
};


#endif //SMITOVTT_CONVERTSMI2VTT_H

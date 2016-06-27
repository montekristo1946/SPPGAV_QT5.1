#ifndef MYCRYPTO_H
#define MYCRYPTO_H

#include <QObject>
//#include <QDebug>
#include<QMessageBox>

#define STOLB 16


class MyCrypto : public QObject
{
    Q_OBJECT
public:
    explicit MyCrypto(QObject *parent = 0);
    QString Crypt(QString InText);
    QString DeCrypt(QString InText);

private:

    QByteArray password_1 [STOLB];
    QByteArray password_2 [STOLB];

    QByteArray CruptTextin [STOLB][STOLB];
    QByteArray CruptTextOut [STOLB][STOLB];
    QByteArray test [STOLB][STOLB];

    void Crupt_1(QByteArray InText[STOLB][STOLB],QByteArray OutText[STOLB][STOLB]);
    void DeCrupt_1(QByteArray InText[STOLB][STOLB],QByteArray OutText[STOLB][STOLB]);
    QString PrintText(QByteArray tmp[STOLB][STOLB]);
    QString OutNormalText(QString InText);
    void ConvertCruptTextin(QString intext, QByteArray OutText[STOLB][STOLB]);
    void InitParam();

signals:

public slots:

};

#endif // MYCRYPTO_H

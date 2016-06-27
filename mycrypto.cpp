#include "mycrypto.h"

MyCrypto::MyCrypto(QObject *parent) :
    QObject(parent)
{
    InitParam();
}

QString MyCrypto::Crypt(QString InText)
{
  // qDebug ()<<InText;

    ConvertCruptTextin(InText,CruptTextin);
    Crupt_1(CruptTextin,CruptTextOut);

   // qDebug ()<<PrintText(CruptTextOut);
   // qDebug ()<<"------------------------------";
    DeCrupt_1(CruptTextOut,test);
   // qDebug ()<<PrintText(test);


    return PrintText(CruptTextOut);



    /*
        ConvertCruptTextin("PutCamera = http://admin:admin#%&192.168.2.5/video/mjpg.cgi?.mjpg#%&",CruptTextin);//конвертирует в массив, забивай пустые байты мусором


        qDebug ()<<PrintText(CruptTextin);
        qDebug ()<<"------------------------------";

       Crupt_1(CruptTextin,CruptTextOut);
       qDebug ()<<PrintText(CruptTextOut);
       qDebug ()<<"------------------------------";

          DeCrupt_1(CruptTextOut,test);
          qDebug ()<<PrintText(test);
      qDebug ()<<"------------------------------";
          qDebug ()<<OutNormalText(PrintText(test));

    */

}

QString MyCrypto::DeCrypt(QString InText)
{
   if (InText.isEmpty())return "NULL";

   if (InText.length()!=STOLB*STOLB)
   {
      /* QMessageBox::information(NULL,QObject::tr("Информация"),
                                tr("Проблема с файлом setting.ini"));*/
       return "NULL";
   }
    // qDebug ()<<"------------------------------Krypt_1";
   // qDebug ()<<InText;

    QString SChar;
    QByteArray ar;
    QByteArray OutText[STOLB][STOLB];

    int sizeintextTMP(0);

    for (int i(0);i<STOLB;i++)//прошлись по строкам
    {
        for (int j(0);j<STOLB;j++)//прошлись по столбцы
        {
            SChar =InText.at(sizeintextTMP);//костыль конвертации
            ar = SChar.toUtf8();
            OutText[i][j] = ar.data();

            sizeintextTMP++;
        }
    }
//qDebug ()<<"------------------------------Krypt_2";

//qDebug ()<<PrintText(OutText);

//qDebug ()<<"------------------------------";
    DeCrupt_1(OutText,CruptTextOut);
  //  qDebug ()<<PrintText(CruptTextOut);

    return OutNormalText(PrintText(CruptTextOut));

}

void MyCrypto::Crupt_1(QByteArray InText[STOLB][STOLB], QByteArray OutText[STOLB][STOLB])
{
    QByteArray tmp_1[STOLB][STOLB];
    QByteArray tmp_2[STOLB][STOLB];

    for (int i(0);i<STOLB;i++)//перемешивает столбцы
    {
        for (int j(0);j<STOLB;j++)
        {
            tmp_1[i][password_1[j].toInt()]=InText[i][j];
        }
    }

    for (int i(0);i<STOLB;i++)//перемешивает столбцы
    {
        for (int j(0);j<STOLB;j++)
        {
            tmp_2[password_2[j].toInt()][i]=tmp_1[j][i];
        }
    }


    for (int i(0);i<STOLB;i++)//прошлись по строкам
    {
        for (int j(0);j<STOLB;j++)//прошлись по столбцы
        {
           OutText[i][j]=tmp_2[j][i];
        }
    }
}

void MyCrypto::DeCrupt_1(QByteArray InText[STOLB][STOLB], QByteArray OutText[STOLB][STOLB])
{
    QByteArray tmp_1[STOLB][STOLB];
    QByteArray tmp_2[STOLB][STOLB];

    for (int i(0);i<STOLB;i++)//прошлись по строкам
    {
        for (int j(0);j<STOLB;j++)//прошлись по столбцы
        {
           tmp_1[i][j]=InText[j][i];
        }
    }

    for (int i(0);i<STOLB;i++)//перемешивает столбцы
    {
        for (int j(0);j<STOLB;j++)
        {
            tmp_2[j][i]=tmp_1[password_2[j].toInt()][i];
        }
    }

    for (int i(0);i<STOLB;i++)//перемешивает столбцы
    {
        for (int j(0);j<STOLB;j++)
        {
            OutText[i][j]=tmp_2[i][password_1[j].toInt()];
        }
    }
}

QString MyCrypto::PrintText(QByteArray tmp[STOLB][STOLB])
{
    QString Return;
    for (int i(0);i<STOLB;i++)//прошлись по строкам
    {
        for (int j(0);j<STOLB;j++)//прошлись по столбцы
        {
            Return.append(*tmp[i][j]);
        }
    }
    return Return;
}

QString MyCrypto::OutNormalText(QString InText)
{
    QString Return = "NULL";
    for (int i(0);i<(STOLB*STOLB-3);i++)//"#%&"
    {
        if (InText.at(i)=='#'&&InText.at(i+1)=='%'&&InText.at(i+2)=='&')
        {
          Return ="";
            for (int j(0);j<i;j++)
          {
            Return.append(InText.at(j));
          }
        }
    }
    return Return;
}

void MyCrypto::ConvertCruptTextin(QString intext, QByteArray OutText[STOLB][STOLB])
{
    if ((STOLB *STOLB)-3 <intext.length()) //проверка чтоб уложится в массив данных
    {
        //qDebug() <<"Error 1"; //"слишком длинное слово"
        return;
    }

    if  ((STOLB *STOLB) != intext.length())//добавляем спец разделители "#%&"
    {
        intext.append("#%&");
    }

    while ((STOLB *STOLB) != intext.length())//забиваем мусорам оставшееся место до длинны слова
    {
        intext.append(char (48+qrand() % 75));

    }

    QString SChar;
    QByteArray ar;

    int sizeintextTMP(0);

    for (int i(0);i<STOLB;i++)//прошлись по строкам
    {
        for (int j(0);j<STOLB;j++)//прошлись по столбцы
        {
            SChar =intext.at(sizeintextTMP);//костыль конвертации
            ar = SChar.toUtf8();
            OutText[i][j] = ar.data();

            sizeintextTMP++;
        }
    }
}

void MyCrypto::InitParam()
{
    password_1 [0]="13";
    password_1 [1]="0";
    password_1 [2]="11";
    password_1 [3]="2";
    password_1 [4]="3";
    password_1 [5]="1";
    password_1 [6]="12";
    password_1 [7]="15";
    password_1 [8]="7";
    password_1 [9]="4";
    password_1 [10]="9";
    password_1 [11]="6";
    password_1 [12]="14";
    password_1 [13]="10";
    password_1 [14]="5";
    password_1 [15]="8";

    password_2  [0]="12";
    password_2  [1]="7";
    password_2  [2]="15";
    password_2  [3]="6";
    password_2  [4]="11";
    password_2  [5]="8";
    password_2  [6]="3";
    password_2  [7]="14";
    password_2  [8]="1";
    password_2  [9]="0";
    password_2 [10]="2";
    password_2 [11]="13";
    password_2 [12]="4";
    password_2 [13]="10";
    password_2 [14]="5";
    password_2 [15]="9";
}









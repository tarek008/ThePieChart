#include "mainwindow.h"
#include "clientaff.h"
#include "ui_clientaff.h"
#include "client.h"
#include "produit.h"
#include <QtDebug>
#include <QApplication>
#include <QMessageBox>
#include<QIntValidator>
#include<QComboBox>
#include "smtp.h"
#include <QSslSocket>
#include <QCoreApplication>
#include <QtWidgets/QMessageBox>
#include <QMediaPlayer>




ClientAff::ClientAff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientAff)
{
   // setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);

     ui->LE_cin->setValidator(new QIntValidator(0, 99999999, this));
     ui->Tab_client->setModel(etmp.afficher());
     ui->LE_ID1->setValidator(new QIntValidator(0, 9999999, this));
     ui->Tab_produit->setModel(etmp_prod.afficher());
    ui->pushButton_6->setEnabled(false);
    ui->SelectModifConfirm->setEnabled(false);
    qDebug()<<QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
    connect(ui->SendMail, SIGNAL(clicked()),this, SLOT(sendMail()));
}

ClientAff::~ClientAff()
{
    delete ui;
}

void ClientAff::on_pushButton_clicked() //ajouter client
{
    int cin=ui->LE_cin->text().toInt();
    QString nom=ui->LE_nom->text();
    QString prenom=ui->LE_prenom->text();
    QString adresse=ui->LE_adresse->text();
    QString email=ui->LE_email->text();
    int nbrpt=ui->LE_nbrpt->text().toInt();
    int NumTelephone=ui->LE_NumTelephone->text().toInt();
    bool test=false;
    if((QString::number(cin).size()==8)&&(email.contains("@"))&&(email.contains(".")))
    {
        Client E(cin,nom,prenom,adresse,email,nbrpt,NumTelephone);
        ui->LE_cin->clear();
        test=E.ajouter();

    }


    if(test==true)
    {
      qDebug()<<"Ajouter avec success";
      QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("Ajouter avec success\n""click ok to exit"),QMessageBox::Ok);
      ui->Tab_client->setModel(etmp.afficher());
      ui->LE_cin->clear();
      ui->LE_nom->clear();
      ui->LE_prenom->clear();
      ui->LE_adresse->clear();
      ui->LE_email->clear();
      ui->LE_nbrpt->clear();
      ui->LE_NumTelephone->clear();
    }
    else
    {
        qDebug()<<"connection failed";
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Ajout non effectue\n""click cancel to exit"),QMessageBox::Cancel);
    }
    qDebug()<<"button clicked";
}

void ClientAff::on_pushButton_2_clicked() //supprimer client
{
    int cin=ui->LE_CIN_Supp->text().toInt();
    qDebug()<<cin;
    bool test=etmp.supprimer(cin);
    if(test==true)
    {
      //qDebug()<<"connection reussite";
      QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("Suppression effectuee\n""click ok to exit"),QMessageBox::Ok);
      ui->Tab_client->setModel(etmp.afficher());
    }
    else
    {
        //qDebug()<<"connection failed";
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Suppression non effectue\n""click cancel to exit"),QMessageBox::Cancel);
    }
}
//Produit::Produit(int id,QString nom,int QTE,float prixProd)

void ClientAff::on_pushButton_3_clicked() //ajouter produit
{
    int id=ui->LE_ID1->text().toInt();
    QString nom=ui->LE_NOM1->text();
    int QTE=ui->LE_QT1->text().toInt();
    float prixProd=ui->LE_PRIX1->text().toFloat();
     QString Description=ui->TE_description->toPlainText();

    Produit E(id,nom,QTE,prixProd,Description);
    //Etudiant E(id,nom,prenom);
    bool test=E.ajouter();
    if(test==true)
    {
      qDebug()<<"connection reussite";
      QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("Ajouter avec success\n""click ok to exit"),QMessageBox::Ok);
      ui->Tab_produit->setModel(etmp_prod.afficher());
    }
    else
    {
        qDebug()<<"connection failed";
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Ajout non effectue\n""click cancel to exit"),QMessageBox::Cancel);
    }
    qDebug()<<"button clicked";

}

void ClientAff::on_pushButton_4_clicked() //supprimer produit
{
    int id=ui->LE_ID_SUPP->text().toInt();
    qDebug()<<id;
    bool test=etmp_prod.supprimer(id);
    if(test==true)
    {
      //qDebug()<<"connection reussite";
      QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("Suppression effectuee\n""click ok to exit"),QMessageBox::Ok);
      ui->Tab_produit->setModel(etmp_prod.afficher());
    }
    else
    {
        //qDebug()<<"connection failed";
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Suppression non effectue\n""click cancel to exit"),QMessageBox::Cancel);
    }

}

void ClientAff::on_pushButton_5_clicked() //modifier 1 client
{
    int cin=ui->LE_CIN_Supp->text().toInt();
    Client C;
   // qDebug()<<id;

    ui->pushButton->setEnabled(false);
    ui->LE_cin->setEnabled(false);
    C=C.SelectModif(cin);
    ui->pushButton_6->setEnabled(true);
    if(C.Get_cin()!=0)
    {

   ui->LE_cin->setText(QString(QString::number(C.Get_cin())));
   //int cinn=ui->LE_cin->text().toInt();

   ui->LE_nom->setText(QString(C.Get_nom()));
   //QString nomm=ui->LE_nom->text();

   ui->LE_prenom->setText(QString(C.Get_prenom()));
   //QString prenomm=ui->LE_prenom->text();

   ui->LE_adresse->setText(QString(C.Get_adresse()));
   //QString adresse=ui->LE_adresse->text();

   ui->LE_email->setText(QString(C.Get_email()));
  // QString email=ui->LE_email->text();

   ui->LE_NumTelephone->setText(QString(QString::number(C.Get_NumTelephone())));
  // int numTelephone=ui->LE_NumTelephone->text().toInt();

   ui->LE_nbrpt->setText(QString(QString::number(C.Get_nbrpt())));
   // int nbrPoint=ui->LE_nbrpt->text().toInt();
   // qDebug()<<cinn<<"CinModif1";
    qDebug()<<C.Get_cin()<<"CinModif";
}
    //bool test= etmp.Modif()

}

void ClientAff::on_pushButton_6_clicked() //confirmation modification of client
{

    int cin=ui->LE_cin->text().toInt();
    QString nom=ui->LE_nom->text();
    QString prenom=ui->LE_prenom->text();
    QString adresse=ui->LE_adresse->text();
    QString email=ui->LE_email->text();
    int nbrpt=ui->LE_nbrpt->text().toInt();
    int NumTelephone=ui->LE_NumTelephone->text().toInt();

    Client C(cin,nom,prenom,adresse,email,nbrpt,NumTelephone);
    ui->pushButton->setEnabled(true);
    ui->LE_cin->setEnabled(true);

    bool test=C.Modifer(cin);
    if(test==true)
    {
     // qDebug()<<"connection reussite";
      QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("Modifier avec success\n""click ok to exit"),QMessageBox::Ok);
      ui->Tab_client->setModel(etmp.afficher());
      ui->LE_cin->clear();
      ui->LE_nom->clear();
      ui->LE_prenom->clear();
      ui->LE_adresse->clear();
      ui->LE_email->clear();
      ui->LE_nbrpt->clear();
      ui->LE_NumTelephone->clear();
    }
    else
    {
        //qDebug()<<"connection failed";
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
        QObject::tr("modification non effectue\n""click cancel to exit"),QMessageBox::Cancel);
    }
    ui->pushButton_6->setEnabled(false);

}

void ClientAff::on_Rechercher_Client_button_clicked() //rechercher client
{
     QString nom=ui->SearchBar_Client->text();
    // qDebug()<<nom;
    ui->Tab_client->setModel(etmp.rechercher(nom));

}

void ClientAff::on_SortButton_clicked()
{
    int value=ui->comboBox1->currentIndex();

    //qDebug()<<value;
    if (value==0)
    {
        ui->Tab_client->setModel(etmp.afficherTriNomDesc());

    }
    else if (value==1)
    {
        ui->Tab_client->setModel(etmp.afficherTriNomAsc());

    }
    else if (value==2)
    {
        ui->Tab_client->setModel(etmp.afficherTriPrenomDesc());

    }
    else if (value==3)
    {
        ui->Tab_client->setModel(etmp.afficherTriPrenomAsc());
    }
    else if (value==4)
    {
        ui->Tab_client->setModel(etmp.afficherTriNbr_PointAsc());
    }
    else if (value==5)
    {
        ui->Tab_client->setModel(etmp.afficherTriNbr_PointDesc());
    }

}

void ClientAff::sendMail()
{

    Smtp* smtp = new Smtp("visitunisia1@gmail.com", "123456789.V", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("visitunisia1@gmail.com", "mohamedhamadifathallah@gmail.com" , ui->LE_Subject_Mail->text(),ui->PTE_Message_Mail->toPlainText());

}


void ClientAff::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );



}



void ClientAff::on_CreatePDF_clicked()
{
    int idPDF=ui->LE_ID_SUPP->text().toInt();
    QString s = QDateTime::currentDateTime().toString();
    s.replace(" ","_");
    s.replace(":",".");
    qDebug() << s;

    Produit p;
    p.SelectModif(idPDF);
    p.pdf(s+".pdf",idPDF);
}
//
void ClientAff::on_CreateClientPdfFile_clicked()
{
   // int idPDF=ui->LE_ID_SUPP->text().toInt();
    QString s = QDateTime::currentDateTime().toString();
    s.replace(" ","_");
    s.replace(":",".");
    qDebug() << s;
    Client C;
    C.pdf(s+".pdf");




      qDebug()<<"connected succefully";
      QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("Ajouter avec success\n""click ok to exit"),QMessageBox::Ok);
      ui->Tab_produit->setModel(etmp_prod.afficher());



}
void ClientAff::on_SendMail_clicked()
{
}

void ClientAff::on_SelectModifProd_clicked()
{
    int id=ui->LE_ID_SUPP->text().toInt();
    Produit P;
   // qDebug()<<id;

    ui->pushButton_3->setEnabled(false);
    ui->LE_ID1->setEnabled(false);
    P=P.SelectModif(id);
    ui->SelectModifConfirm->setEnabled(true);
    if(P.Get_id()!=0)
    {

   ui->LE_ID1->setText(QString(QString::number(P.Get_id())));
   //int cinn=ui->LE_cin->text().toInt();

   ui->LE_NOM1->setText(QString(P.Get_nom()));
   //QString nomm=ui->LE_nom->text();

   ui->LE_PRIX1->setText(QString(QString::number(P.Get_prixProd())));
  // int numTelephone=ui->LE_NumTelephone->text().toInt();

   ui->LE_QT1->setText(QString(QString::number(P.Get_QTE())));
   // int nbrPoint=ui->LE_nbrpt->text().toInt();
   // qDebug()<<cinn<<"CinModif1";
   ui->TE_description->setText(QString(P.Get_DESC()));
    qDebug()<<P.Get_id()<<"Id Modif";
    }
    //bool test= etmp.Modif()

}

void ClientAff::on_SelectModifConfirm_clicked()
{
    int id=ui->LE_ID_SUPP->text().toInt();
    QString nom=ui->LE_NOM1->text();
    float PRIXX=ui->LE_PRIX1->text().toFloat();
    int QTE=ui->LE_QT1->text().toInt();
    QString Description=ui->TE_description->toPlainText();



    Produit P(id,nom,QTE,PRIXX,Description);
    ui->pushButton_3->setEnabled(true);
    ui->LE_ID1->setEnabled(true);

    bool test=P.Modifer(id);
    if(test==true)
    {
     // qDebug()<<"connection reussite";
      QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("Modifier avec success\n""click ok to exit"),QMessageBox::Ok);
      ui->Tab_produit->setModel(etmp_prod.afficher());
      ui->LE_ID_SUPP->clear();
      ui->LE_NOM1->clear();
      ui->LE_PRIX1->clear();
      ui->LE_QT1->clear();
      ui->TE_description->clear();

    }
    else
    {
        //qDebug()<<"connection failed";
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
        QObject::tr("modification non effectue\n""click cancel to exit"),QMessageBox::Cancel);
    }
    ui->SelectModifConfirm->setEnabled(false);


}

void ClientAff::on_MusicButton_clicked()
{
    player = new QMediaPlayer;
    // ...
    player->setMedia(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    player->setVolume(50);
    player->play();
}
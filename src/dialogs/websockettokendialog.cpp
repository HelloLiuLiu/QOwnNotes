#include "websockettokendialog.h"

#include <QtCore/QSettings>
#include <QtGui/QClipboard>

#include "ui_websockettokendialog.h"

WebSocketTokenDialog::WebSocketTokenDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::WebSocketTokenDialog) {
    ui->setupUi(this);

    QSettings settings;
    QString token = settings.value(QStringLiteral("webSocketServerService/token")).toString();

    if (token.isEmpty()) {
        on_generateButton_clicked();
    } else {
        ui->tokenLineEdit->setText(token);
        on_copyButton_clicked();
    }
}

QString WebSocketTokenDialog::generateToken() const {
    const QString possibleCharacters(
        QStringLiteral("ABCDEFGHKLMNPQRSTUVWXYZabcdefghkmnpqrstuvwxyz23456789"));
    const int randomStringLength = 8;

    QString randomString;
    for (int i = 0; i < randomStringLength; ++i) {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

WebSocketTokenDialog::~WebSocketTokenDialog() { delete ui; }

void WebSocketTokenDialog::on_copyButton_clicked() {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->tokenLineEdit->text());
}

void WebSocketTokenDialog::on_generateButton_clicked() {
    QString token = generateToken();
    QSettings settings;
    settings.setValue(QStringLiteral("webSocketServerService/token"), token);
    ui->tokenLineEdit->setText(token);
    on_copyButton_clicked();
}

void WebSocketTokenDialog::on_buttonBox_accepted() {
    QSettings settings;
    settings.setValue(QStringLiteral("webSocketServerService/token"),
                      ui->tokenLineEdit->text());
}

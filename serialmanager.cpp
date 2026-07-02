#include "serialmanager.h"
#include <QDebug>
#include <QSerialPortInfo>

SerialManager::SerialManager(QObject *parent) : QObject(parent)
{
    m_serial = new QSerialPort(this);

    // Portu tapmaq üçün: sisteminə görə "ttyUSB0" fərqli ola bilər (ttyACM0 da olur)
    m_serial->setPortName("ttyUSB0");
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialManager::handleError);

    // VACIB: ReadOnly əvəzinə ReadWrite - Linux-da DTR/RTS düzgün işləməsi üçün şərtdir
    if (m_serial->open(QIODevice::ReadWrite)) {
        connect(m_serial, &QSerialPort::readyRead, this, &SerialManager::readSerialData);
        qDebug() << "Arduino portu (" << m_serial->portName() << ") uğurla açıldı!";
        emit connectedChanged();
    } else {
        qDebug() << "Port açıla bilmədi! Xəta:" << m_serial->errorString();
        qDebug() << "Mövcud portlar:";
        for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
            qDebug() << " -" << info.portName() << info.description();
        }
    }
}

void SerialManager::readSerialData()
{
    while (m_serial->canReadLine()) {
        QByteArray data = m_serial->readLine().trimmed();
        QString line = QString::fromUtf8(data);

        if (line == "ERROR" || line.isEmpty())
            continue;

        QStringList parts = line.split(',');
        if (parts.size() == 2) {
            bool okT = false, okH = false;
            double t = parts[0].toDouble(&okT);
            double h = parts[1].toDouble(&okH);

            if (okT && okH) {
                m_temperature = t;
                m_humidity = h;
                emit dataChanged();
            } else {
                qDebug() << "Yanlış format gəldi:" << line;
            }
        }
    }
}

void SerialManager::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError)
        return;

    qDebug() << "Serial port xətası:" << m_serial->errorString();
}

SerialManager::~SerialManager()
{
    if (m_serial->isOpen())
        m_serial->close();
}

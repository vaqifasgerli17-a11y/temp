#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QSerialPort>

class SerialManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double temperature READ temperature NOTIFY dataChanged)
    Q_PROPERTY(double humidity READ humidity NOTIFY dataChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    explicit SerialManager(QObject *parent = nullptr);
    ~SerialManager();

    double temperature() const { return m_temperature; }
    double humidity() const { return m_humidity; }
    bool connected() const { return m_serial->isOpen(); }

signals:
    void dataChanged();
    void connectedChanged();

private slots:
    void readSerialData();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_serial;
    double m_temperature = 0.0;
    double m_humidity = 0.0;
};

#endif // SERIALMANAGER_H

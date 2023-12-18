#ifndef SPEAK_H
#define SPEAK_H

#include <QtTextToSpeech>
#include <QObject>
class Speak : public QObject
{
    Q_OBJECT
public:
    explicit Speak(QObject *parent = nullptr);
public slots:
    void talk(const QString &text);

private:
    QTextToSpeech *m_speech = nullptr;
    QList<QVoice> m_voices;
};

#endif // SPEAK_H

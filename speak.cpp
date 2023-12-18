#include "speak.h"

Speak::Speak(QObject *parent) : QObject(parent)
{
    m_speech = new QTextToSpeech("flite",this);
    QLocale locale {"en_US"};
    m_speech->setLocale(locale);
    m_voices = m_speech->availableVoices();

    m_speech->setVoice(m_voices.at(1));
    m_speech->setRate(0.1);
    m_speech->setPitch(0.5);
    m_speech->setVolume(0.5);
}

void Speak::talk(const QString &text)
{
    m_speech->say(text);
}

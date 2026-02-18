#ifndef GESTIONNAIRE_AUDIO_H
#define GESTIONNAIRE_AUDIO_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>
#include <QMap>

enum AudioMode { MENU, JEU };

class GestionnaireAudio : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float musicVolume READ getMusicVolume WRITE setMusicVolumeAnimation)
public:
    GestionnaireAudio(QObject* parent = nullptr);

    // MUSIQUE
    void setPlaylist(const QStringList& musics);
    void playMusic();
    void nextMusic();
    void setMusicVolume(float v);
    float getMusicVolume() const;
    float getMusicVolumeSetting() const;
    float getMaxMusicVolume() const;
    void stopMusic();
    void clearPlaylist();
    void stopAndClearMusic();

    // SFX
    void addSfx(QString name, QString path);
    void playSfx(QString name);
    void setSfxVolume(float v);

private slots:
    void onMediaFinished(QMediaPlayer::MediaStatus status);

private:
    const float volumeMax = 0.025f;

    float musicVolumeSetting = 0.0f;

    QMediaPlayer* musicPlayer;
    QAudioOutput* musicOutput;

    QStringList playlist;
    int index = 0;

    QMap<QString, QSoundEffect*> sfx;
    float sfxVolume = 0.5f;

    void setMusicVolumeAnimation(float v);
};

#endif
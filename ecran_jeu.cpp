#include "ecran_jeu.h"

#include <QPainter>
#include <algorithm>

#include "Reticule.h"


EcranJeu::EcranJeu(QWidget* parent)
    : QWidget(parent)
{
    background = QPixmap(QDir::currentPath() + "/images/jeu/background.png");
    setAttribute(Qt::WA_OpaquePaintEvent);
    elapsed.start();

    timer.setInterval(1000 / 60);
    connect(&timer, &QTimer::timeout, this, [this]() {
        tick();
        });
    timer.start();

    overlay = new FadeOverlay(this);
    overlay->setGeometry(rect());
    overlay->setAlpha(255);
    overlay->show();
    overlay->raise();

    fadeInAnim = new QPropertyAnimation(overlay, "alpha", this);
    fadeInAnim->setEasingCurve(QEasingCurve::InOutQuad);
    fadeInAnim->setDuration(1000);
    fadeInAnim->setStartValue(255);
    fadeInAnim->setEndValue(0);



	//ajout à enlever apres test
    QPoint pos = QCursor::pos();
	pos = mapFromGlobal(pos);

    setCursor(Qt::BlankCursor);
    setMouseTracking(true);
	reticule = new Reticule(this,pos);
    reticule->show();

    //Partie joystick de test
    SDL_Gamepad* gamepad = nullptr;

    int count = 0;
    SDL_GetGamepads(&count);

    if (count > 0)
    {
        gamepad = SDL_OpenGamepad(0);
        qDebug() << "Manette ouverte !";
    }
    else
    {
        qDebug() << "Aucune manette détectée";
    }




    //Fin de la zone de test

    if (SDL_Init(SDL_INIT_GAMEPAD) < 0)
{
    qDebug() << "Erreur SDL:" << SDL_GetError();
}

    connect(fadeInAnim, &QPropertyAnimation::finished, this, [this]() {
        overlay->hide();
        });
}

void EcranJeu::showEvent(QShowEvent* e)
{
    QWidget::showEvent(e);

    if (overlay && fadeInAnim)
    {
        overlay->setGeometry(rect());
        overlay->setAlpha(255);
        overlay->show();
        overlay->raise();

        fadeInAnim->stop();
        fadeInAnim->start();
    }
}

void EcranJeu::resizeEvent(QResizeEvent* e)
{
    QWidget::resizeEvent(e);

    if (overlay)
    {
        overlay->setGeometry(rect());
        overlay->raise();
    }
}

void EcranJeu::tick()
{
    update();
}

void EcranJeu::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    if (!background.isNull()) {
        painter.drawPixmap(rect(), background);
    }
    else {
        painter.fillRect(rect(), Qt::black);
    }
}

void EcranJeu::mouseMoveEvent(QMouseEvent* event)
{
    reticule->setPosition(event->pos());
}
#include "Reticule.h"

Reticule::Reticule(QWidget* parent) : QWidget(parent)
{
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_AlwaysStackOnTop);
	image = QPixmap(QDir::currentPath() + "/images/jeu/reticule.png");
	if (!image || image.isNull()) {
		cout << "RETICULE::impossible de charger: "<<endl;
	}
	else {
		cout << "Chargement réussi " << endl;
	}

}

Reticule::~Reticule() {
}



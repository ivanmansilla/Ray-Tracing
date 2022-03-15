#include "Main.h"

// Metode principal del programa

int main(int argc, char **argv) {

    cout << "Init..." <<endl;
    Q_INIT_RESOURCE(resources);

    // Línia que controla els fitxers a carregar per l'aplicació.
    // Es donen d'alta prèviament a la carpeta de resources del projecte
    // Cal que aquí no hi posis extensió (directament anirà a buscar el fitxer amb extensió .json

    // Exemple d'escena virtual carregada des de json:
    auto controller = make_shared<Controller>(Serializable::Json, "://resources/meshExample", "://resources/setupRenderOneSphere");

    // Exemple d'escena de dades carregada des de json:
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/data0", "://resources/setupRenderTwoSpheres");

    // Pregunta m
   // auto controller = make_shared<Controller>(Serializable::Json, "://resources/threeSpheres", "://resources/setupRenderSpheres");

    // 4.2- apartado b
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/dadesEuropa", "://resources/setupDataEuropa");

    controller->start(argc, argv);

    return(0);
}

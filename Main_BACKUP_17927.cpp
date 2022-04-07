#include "Main.h"

// Metode principal del programa

int main(int argc, char **argv) {

    cout << "Init..." <<endl;
    Q_INIT_RESOURCE(resources);

    // Línia que controla els fitxers a carregar per l'aplicació.
    // Es donen d'alta prèviament a la carpeta de resources del projecte
    // Cal que aquí no hi posis extensió (directament anirà a buscar el fitxer amb extensió .json

    // Fase 1

    // Triangles
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/triangles", "://resources/setupRenderTriangles");


    // Esferes
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/twoSpheres", "://resources/setupRenderTwoSpheres");
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/spheresLambertianes", "://resources/setupRenderSpheres");

    // Malla (cub)
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/meshExample", "://resources/setupCustomRender");

    // Cilindre
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/Cylinder", "://resources/setupCustomRender");

    // Dades món real
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/data0", "://resources/setupCustomRender");


    // Fase 2

    // Escena esferes
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/customSpheres", "://resources/setupCustomRender");

    // Visualitzacio dades
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/data0", "://resources/setupCustomRender");
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/data10", "://resources/setupCustomRender");
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/dadesEuropa", "://resources/setupCustomRender");



    // Fase 3
    auto controller = make_shared<Controller>(Serializable::Json, "://resources/dadesEuropaTextured", "://resources/setupDataEuropa1Light");
    // auto controller = make_shared<Controller>(Serializable::Json, "://resources/dadesJoanic", "://resources/setupDataJoanic");
    //auto controller = make_shared<Controller>(Serializable::Json, "://resources/dadesEarth", "://resources/setupDataEarth");

    controller->start(argc, argv);

    return(0);
}

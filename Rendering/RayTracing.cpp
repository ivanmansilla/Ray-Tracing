#include "RayTracing.h"

// Metode raytracing principal

// Aquesta funcio transforma cada pixel a coordenades de mon, construeix el raig,
// envia el raig des de la camera en aquella direccio cridant al metode RayColor
// per acabar pintant la imatge final:

//Precondicio:
// La Scene ha d'estar creada i inicialitzada

// TO DO: Fase 2: A retocar per a aconseguir imatges sense aliasing

void RayTracing::rendering() {
    // Recorregut de cada pixel de la imatge final

    for (int y = cam->viewportY-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < cam->viewportX; x++) {

            // Apartat A.2 (Fase 2). Antialising
            vec3 col(0, 0, 0);
            vec3 newCol;
            int vx = cam->viewportX;
            float factDiv = (float)1/(float)vx;

            for (int i=0; i<maxNumSamples; i++){
                float sumUV = linearRand(0.0f, factDiv);

                float u = (float(x)) / float(cam->viewportX) + sumUV;
                float v = (float(y)) / float(cam->viewportY) + sumUV;
                if(u > 1){
                    u = 1;
                }
                if(v > 1){
                    v = 1;
                }
                Ray r = cam->getRay(u, v);

                col += scene->RayColor(cam->getLookFrom(), r, 0);
                }
            newCol = vec3(col[0]/maxNumSamples, col[1]/maxNumSamples, col[2]/maxNumSamples);

            // Apartat A.3 (Fase 2). Gamma correction
            vec3 colGamma = vec3(sqrt(newCol[0]), sqrt(newCol[1]),sqrt(newCol[2]));
            setPixelColor(colGamma, x, y);
        }
    }
    std::cerr << "\nDone.\n";
}

void RayTracing::exitRender() {

}

// Metode de suport que fa el rendering per a tots els Renders que no usen GLUT
void RayTracing::startRendering(int argc, char **argv) {
    renderingScene();
}

void RayTracing::renderingScene()  {
    initRender(filename.toStdString());
    rendering();
    exitRender();
}

void RayTracing::setCamera(shared_ptr<Camera> c) {
    cam = c;
}
void RayTracing::setScene(shared_ptr<Scene> s) {
    scene = s;
}

void RayTracing::setOutputFile(QString output) {
    filename = output;
}




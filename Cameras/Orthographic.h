#ifndef ORTHOGRAPHIC_H
#define ORTHOGRAPHIC_H

#include "Camera.h"

/*******************************************************************
 * Class - Orthographic inherits from Camera
 * 
 * A version of the camera that allows for orthographic projection
 * single direction, multiple eye points
 * 
 *******************************************************************/
class Orthographic : public Camera{
    public:
        double zWindow;
	
        Orthographic();
	    Orthographic(const Orthographic& og);
	    ~Orthographic();

	//std::shared_ptr<Camera> Clone() const override;
	    Orthographic& operator=(const Orthographic& rhs);

	    void setZWindow(const double zw);
	    void renderScene(Scene& scenePtr) override;
private:
	
};

#endif
#pragma once 
#include <vector>
#include "DrawElement.hpp"

namespace Stinky
{
    //  forward declaration - using only pointer
    class VAO;
    class VBO;

    class DrawElementManager
    {
    public:
        //  add Drawelements
        void Add(DrawElement* obj);

        DrawElementManager();
        ~DrawElementManager();

        //  vao bind - using drawing
        void VAOBind();
        //  vbo can bind to vao
        void VAOLinkAttrib(VBO* vbo, unsigned int layout, unsigned int numComponenets, unsigned int type, int stride, void* offset);
        //  vao unbind - after drawing models
        void VAOUnBind();

        //  bind all
        void BindAll();
        //  unbind all - after make all of the drawelement use this function
        void UnBindAll();
        //  delete all - after while(!isWindowClosed())
        void DeleteAll();

        //  find certain derived elements
        template<typename T>
        T* GetDrawElement(DrawElement* elements)
        {
            T* ptr = dynamic_cast<T*>(elements);

            if (ptr != nullptr)
            {
                return ptr;
            }

            return nullptr; //  doesn't have certain elements
        }

        //  return vector
        const std::vector<DrawElement*>& Elements() { return drawElements; }
        
    private:
        //  vector for saving derived class
        std::vector<DrawElement*> drawElements;
        //  This engine's model has only one vao
        VAO* vao;
    };
}
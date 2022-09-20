#ifndef DRAWELEMENT_CLASS_H
#define DRAWELEMENT_CLASS_H

namespace Stinky
{
	//	base class for vao, vbo, ebo
	class DrawElement
	{
	public:
		//	all of the derived class has ID
		unsigned int ID;
		
		virtual ~DrawElement() {};

		//	vao, vbo, ebo has each bind, unbind delete function
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void Delete() = 0;
	};
}

#endif // DRAWELEMENT_CLASS_H

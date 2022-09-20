#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "DrawElement.hpp"

namespace Stinky
{
	class EBO : public DrawElement
	{
	public:
		//	using index make EBO
		EBO(unsigned int* indices, int size);

		void Bind() override;
		void UnBind() override;
		void Delete() override;
	};
}

#endif // EBO_CLASS_H

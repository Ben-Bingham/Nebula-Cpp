#include "ImageRegister.h"

namespace Nebula {
	ImageElement::ImageElement(std::string name, Ruby::Image image)
		: image(std::move(image)), name(std::move(name)) {
		
	}

	ImageRegister::ImageRegister() {
		Register(ImageElement{ "UNKNOWN", Ruby::Image{"assets\\images\\textures\\unknown.png" } });
	}

	ImageRegister& ImageRegister::Get() {
		static ImageRegister imageRegister;

		return imageRegister;
	}

	ImageIndex ImageRegister::Register(const ImageElement& image) {
		m_Blocks.push_back(image);

		return m_Blocks.size() - 1;
	}

	ImageElement ImageRegister::operator[](const size_t index) {
		return m_Blocks[index];
	}
}
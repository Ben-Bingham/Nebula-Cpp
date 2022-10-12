#pragma once

#include <tuple>

#include "Image.h"

namespace Nebula {
	//struct BlockTexture {
	//	BlockTexture(Ruby::Image& Image, std::string iName)
	//		: internalName(iName), image(Image) {
	//	}

	//	unsigned int ID{ getNextID() };

	//	std::string internalName;
	//	Ruby::Image image;
	//private:
	//	static unsigned int nextID;
	//	unsigned int getNextID() { return nextID++; }
	//};

	class ImageManager {
	public:
		using ImageElement = std::tuple<Ruby::Image, std::string, unsigned int>;

		ImageManager() { }

		unsigned int addImage(Ruby::Image image, std::string iName) {
			unsigned int id = getNextID();
			images.push_back(ImageElement{ std::move(image), iName, id });
			return id;
		}

		Ruby::Image* getImage(const std::string& name) {
			for (ImageElement& image : images) {
				if (std::get<1>(image) == name) {
					return &std::get<0>(image);
				}
			}
			LOG("Image not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

		Ruby::Image* getImage(unsigned int ID) {
			for (ImageElement& image : images) {
				if (std::get<2>(image) == ID) {
					return &std::get<0>(image);
				}
			}
			LOG("Image not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

		unsigned int* getImageID(const std::string& name) {
			for (ImageElement& image : images) {
				if (std::get<1>(image) == name) {
					return &std::get<2>(image);
				}
			}
			LOG("Image not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

		std::string* getImageName(unsigned int ID) {
			for (ImageElement& image : images) {
				if (std::get<2>(image) == ID) {
					return &std::get<1>(image);
				}
			}
			LOG("Image not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

		std::vector<Ruby::Image*> getImages() {
			std::vector<Ruby::Image*> pics;

			for (ImageElement& image : images) {
				pics.push_back(&std::get<0>(image));
			}

			return pics;
		}

	private:
		std::vector<ImageElement> images;
		static unsigned int nextID;
		unsigned int getNextID() { return nextID++; }
	};
}
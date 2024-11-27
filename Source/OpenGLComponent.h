/*
  ==============================================================================

    OpenGLComponent.h
    Created: 14 Nov 2024 9:16:48pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OpenGLComponent : public juce::Component
    //,public juce::OpenGLRenderer
{
private:
    juce::OpenGLContext openGLContext;
	juce::Image filmstrip{};

public:
    OpenGLComponent()
    {
        //openGLContext.setOpenGLVersionRequired(juce::OpenGLContext::OpenGLVersion::openGL3_2);

        //openGLContext.setRenderer(this);
        //openGLContext.attachTo(*this);
    }

    //void newOpenGLContextCreated() override {}
    //void renderOpenGL() override {}
    //void openGLContextClosing() override {}

	juce::Image getFilmstrip() { return filmstrip; }

	void drawFilmstripKnobImage(juce::Image image, int totalFrames, bool isVertical, double startAngle, double endAngle)
	{
		//openGLContext.setRenderer(this);
		//openGLContext.attachTo(*this);
		//openGLContext.setContinuousRepainting(true);

		int frameW = image.getWidth();
		int frameH = image.getHeight();
		double range = std::abs(startAngle) + std::abs(endAngle);
		double angleInterval = range / (totalFrames - 1);

		juce::Image filmstripImage{};

		if (isVertical)
			filmstripImage = juce::Image(juce::Image::ARGB, frameW, frameH * totalFrames, true);
		else
			filmstripImage = juce::Image(juce::Image::ARGB, frameW * totalFrames, frameH, true);


		juce::Graphics g(filmstripImage);
		g.fillAll(juce::Colours::transparentBlack);
		juce::Image rotary(juce::Image::ARGB, frameW, frameH, true);

		for (size_t i = 0; i < totalFrames; i++)
		{
			rotary.clear(rotary.getBounds(), juce::Colours::transparentBlack);

			juce::Rectangle<int> dest{};

			if (isVertical) {
				int yPos = (int)i * frameH;
				dest = { 0, yPos, frameW, frameH };
			}
			else {
				int xPos = (int)i * frameW;
				dest = { xPos, 0, frameW, frameH };
			}

			double angleNow = int(i) * angleInterval;
			double angleRadian = juce::degreesToRadians(startAngle + angleNow);

			juce::Rectangle<int> temp{ 0,0,frameW, frameH };
			juce::AffineTransform rotating = juce::AffineTransform::rotation((float)angleRadian, float(temp.getCentreX()), float(temp.getCentreY()));

			//juce::Image rotary(juce::Image::PixelFormat::ARGB, frameW, frameH, true);
			juce::Graphics frames(rotary);

			frames.addTransform(rotating);
			frames.drawImage(image, temp.toFloat(), juce::RectanglePlacement::centred, false);

			g.drawImage(rotary, dest.toFloat(), juce::RectanglePlacement::centred, false);

			juce::Rectangle<int> ellipse{ dest.reduced(static_cast<int>(dest.getHeight() * 0.35F)) };
			g.setColour(juce::Colours::darkseagreen.darker(0.5F));
			g.fillEllipse(ellipse.toFloat());

			auto numText = std::to_string(i + 1);
			g.setFont(ellipse.getHeight() * 0.50F);
			g.setColour(juce::Colours::white);
			g.drawText(numText, ellipse.toFloat(), juce::Justification::centred, true);

		}

		if (filmstripImage.isValid()) DBG("VALID FILMSTRIP");

		juce::Image::BitmapData bitmapData(filmstripImage, juce::Image::BitmapData::readOnly);
		DBG("First pixel color: " << bitmapData.getPixelColour(0, 0).toString());


		this->filmstrip = filmstripImage;

		DBG("Pixel at (0, 0): " << filmstripImage.getPixelAt(0, 0).toString());
		DBG("Pixel at (70, 70): " << filmstripImage.getPixelAt(70, 70).toString());

		DBG("Color red: " << juce::Colours::red.toString());

		//juce::Image copyImage = filmstripImage;
		//copyImage.duplicateIfShared();

		//juce::File file("outputOpenGL.png");
		juce::File file = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getChildFile("outputOpenGL.png");
		juce::PNGImageFormat pngFormat;
		std::unique_ptr<juce::OutputStream> streams(file.createOutputStream());

		if (streams)
		{
			if (pngFormat.writeImageToStream(filmstripImage, *streams))
			{
				DBG("-->> SUCCESS EXPORT");
				streams->flush();
			}
			else 
			{
				DBG("-->> FAILED EXPORT");
			}
		}
		else
		{
			DBG("-->> Stream not READY");
		}




		//openGLContext.setContinuousRepainting(false);
		//openGLContext.detach();




		//int frameW = image.getWidth();
		//int frameH = image.getHeight();
		//double range = std::abs(startAngle) + std::abs(endAngle);
		//double angleInterval = range / (totalFrames - 1);

		//juce::Image filmstripImage{};

		//if (isVertical)
		//filmstripImage = juce::Image(juce::Image::ARGB, frameW, frameH * totalFrames, true);
		//else
		//filmstripImage = juce::Image(juce::Image::ARGB, frameW * totalFrames, frameH, true);

		//juce::Graphics g(filmstripImage);
		//g.fillAll(juce::Colours::transparentBlack);
		//juce::Image rotary(juce::Image::ARGB, frameW, frameH, true);

		//for (size_t i = 0; i < totalFrames; i++)
		//{
		//	rotary.clear(rotary.getBounds(), juce::Colours::transparentBlack);

		//	juce::Rectangle<int> dest{};

		//	if (isVertical) {
		//		int yPos = (int)i * frameH;
		//		dest = { 0, yPos, frameW, frameH };
		//	}
		//	else {
		//		int xPos = (int)i * frameW;
		//		dest = { xPos, 0, frameW, frameH };
		//	}

		//	double angleNow = int(i) * angleInterval;
		//	double angleRadian = juce::degreesToRadians(startAngle + angleNow);

		//	juce::Rectangle<int> temp{ 0,0,frameW, frameH };
		//	juce::AffineTransform rotating = juce::AffineTransform::rotation((float)angleRadian, temp.getCentreX(), temp.getCentreY());

		//	juce::Graphics frames(rotary);
		//	frames.addTransform(rotating);
		//	frames.drawImage(image, temp.toFloat(), juce::RectanglePlacement::centred, false);

		//	g.drawImage(rotary, dest.toFloat(), juce::RectanglePlacement::centred, false);

		//	juce::Rectangle<int> ellipse{ dest.reduced(dest.getHeight() * 0.35F) };
		//	g.setColour(juce::Colours::darkseagreen.darker(0.5F));
		//	g.fillEllipse(ellipse.toFloat());

		//	auto numText = std::to_string(i + 1);
		//	g.setFont(ellipse.getHeight() * 0.50F);
		//	g.setColour(juce::Colours::white);
		//	g.drawText(numText, ellipse.toFloat(), juce::Justification::centred, true);
		//}

		//// Ensure the image is valid before accessing pixel data
		//if (filmstripImage.isValid()) {
		//	DBG("VALID FILMSTRIP");

		//	// Lock bitmap data for safe access
		//	juce::Image::BitmapData bitmapData(filmstripImage, juce::Image::BitmapData::readOnly);

		//	// Access pixel data after locking
		//	DBG("First pixel color: " << bitmapData.getPixelColour(0, 0).toString());
		//	DBG("Pixel at (70, 70): " << bitmapData.getPixelColour(70, 70).toString());
		//}

		//// Export to PNG file
		//juce::File file = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getChildFile("outputOpenGL.png");
		//juce::PNGImageFormat pngFormat;
		//std::unique_ptr<juce::OutputStream> streams(file.createOutputStream());

		//if (streams)
		//{
		//	if (pngFormat.writeImageToStream(filmstripImage, *streams))
		//	{
		//		DBG("-->> SUCCESS EXPORT");
		//		streams->flush();
		//	}
		//	else
		//	{
		//		DBG("-->> FAILED EXPORT");
		//	}
		//}
		//else
		//{
		//	DBG("-->> Stream not READY");
		//}

	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OpenGLComponent)
};
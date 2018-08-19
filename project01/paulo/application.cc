#include "application.h"

#include <cinder/gl/gl.h>

static const cinder::ivec2 WindowSize{640, 480};
static const int SquareLength = 10;

static const struct
{
	ci::ivec2 Baseline{0, SquareLength/2};
	ci::Color Color{ci::Color::white()};
	ci::Font Font{"Courier", 2 * SquareLength};
} Score;

Application::Application()
{}

void Application::prepareSettings(Settings* settings)
{
	settings->setWindowSize(WindowSize);
	settings->setFrameRate(35.0f);
	settings->setResizable(false);
	settings->setFullScreen(false);
}

void Application::keyDown(ci::app::KeyEvent)
{}

void Application::setup()
{
	const int width = (WindowSize.x - 2*Score.Font.getSize()) / SquareLength;
	const int height = (WindowSize.y - 2*Score.Font.getSize()) / SquareLength;

	const ci::ivec2 upperLeft{Score.Font.getSize(), Score.Font.getSize()};
	const ci::ivec2 bottomRight = upperLeft + SquareLength * ci::ivec2{width, height};
	mCanvas = Canvas{upperLeft, bottomRight};
}

void Application::draw()
{
	ci::gl::clear();
	ci::gl::color(ci::Color::white());
	ci::gl::drawSolidRect(mCanvas);

	ci::gl::color(ci::Color::black());
	const auto& origin = mCanvas.getUpperLeft();
	const ci::ivec2 upperLeft = SquareLength * mPoint + ci::ivec2{origin.x, origin.y};
	const ci::ivec2 bottomRight = upperLeft + ci::ivec2{SquareLength, SquareLength};
	ci::gl::drawSolidRect({upperLeft, bottomRight});

	ci::gl::drawString("Score: --", Score.Baseline, Score.Color, Score.Font);
}

void Application::update()
{
	const int width = (WindowSize.x - 2*Score.Font.getSize()) / SquareLength;
	mPoint.x += 1;
	mPoint.x %= width;
}

CINDER_APP(Application, ci::app::RendererGl(ci::app::RendererGl::Options().msaa(16)), &Application::prepareSettings)


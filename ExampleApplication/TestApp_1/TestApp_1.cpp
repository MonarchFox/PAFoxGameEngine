#include "TestApp_1.h"
#include <iostream>
#include <random>

TestApp_1::TestApp_1()
= default;

TestApp_1::~TestApp_1()
= default;

bool TestApp_1::Init()
{
    std::cout << "Starting Game Application!\n";
    return FxEngine::Init();
}

void TestApp_1::UpdateScene(const float deltaTime)
{
    if (mUpdateCurrentTime >= mUpdateColorChangeTime)
    {
        GetGraphicsRenderer()->SetBackGroundColor(GenerateRandomColor());
        mUpdateCurrentTime = 0;
    }
    mUpdateCurrentTime += deltaTime;
}

void TestApp_1::DrawScene()
{
    if (!GetGraphicsRenderer()->Render())
    {
        throw std::runtime_error("Render failed");
    }
}

std::vector<float> TestApp_1::GenerateRandomColor()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    float r = distribution(generator);
    float g = distribution(generator);
    float b = distribution(generator);
    float a = distribution(generator);

    return { r, g, b, a };
}

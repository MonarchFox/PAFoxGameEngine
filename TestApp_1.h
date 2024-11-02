#pragma once

#include "GameEngine.h"


class TestApp_1 final: public FoxEngine::FxEngine
{
    float mUpdateColorChangeTime{ 2.f };
    float mUpdateCurrentTime    { 2.f };

public:
    TestApp_1();
    ~TestApp_1() override;

    bool Init() override;

    void UpdateScene(float deltaTime) override;
    void DrawScene() override;

private:
    static std::vector<float> GenerateRandomColor();
};


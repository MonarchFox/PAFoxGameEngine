#include "TestApp_2.h"

using namespace DirectX;

TestApp_2::TestApp_2()
    : mTheta(1.5f * PI), mPhi(0.25f * PI), mRadius(5.f)
{
    SetWindowName(L"Test Application 2");
    mLastMousePosition.x = 0;
    mLastMousePosition.y = 0;

    XMMATRIX IdentityMatrix = DirectX::XMMatrixIdentity();

    XMStoreFloat4x4(&mWorld, IdentityMatrix);
    XMStoreFloat4x4(&mView, IdentityMatrix);
    XMStoreFloat4x4(&mProj, IdentityMatrix);
}

TestApp_2::~TestApp_2()
{
    bool status = true;
}

bool TestApp_2::Init()
{
    if (!FxEngine::Init()) return false;

    return true;
}

void TestApp_2::OnResizeEnd()
{
    FxEngine::OnResizeEnd();

    XMMATRIX proj = XMMatrixPerspectiveFovLH(0.25f * PI,
                                             GetAspectRatio(),
                                             1.0f, 1000.0f);
    XMStoreFloat4x4(&mProj, proj);
}

void TestApp_2::UpdateScene(float deltaTime)
{
    //~ Spherical Coordinates
    float x = mRadius * sinf(mPhi) * cosf(mTheta);
    float z = mRadius * sinf(mPhi) * sinf(mTheta);
    float y = mRadius * cosf(mPhi);

    //~ Matrix View
    XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
    XMStoreFloat4x4(&mView, view);
}

void TestApp_2::DrawScene()
{

}

void TestApp_2::OnMouseDown(WPARAM btnState, int x, int y)
{
    FxEngine::OnMouseDown(btnState, x, y);
}

void TestApp_2::OnMouseUp(WPARAM btnState, int x, int y)
{
    FxEngine::OnMouseUp(btnState, x, y);
}

void TestApp_2::OnMouseMove(WPARAM btnState, int x, int y)
{
    FxEngine::OnMouseMove(btnState, x, y);
}

//
// Game.h
//
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "Shader.h"
#include "modelclass.h"
#include "Light.h"
#include "Input.h"
#include "Camera.h"
#include "RenderTexture.h"
#include "PostProcess.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);
#ifdef DXTK_AUDIO
    void NewAudioDevice();
#endif

    // Properties
    void GetDefaultSize( int& width, int& height ) const;
	
private:

    struct LightBufferType
    {
        DirectX::SimpleMath::Vector4 ambient;
        DirectX::SimpleMath::Vector4 diffuse;
        DirectX::SimpleMath::Vector3 position;
        float padding;
    };

	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	}; 

    struct ColorBufferType
    {
        DirectX::SimpleMath::Vector3 positionCoord;
        DirectX::SimpleMath::Vector4 color;
    };

    void PostProcess();
    void newPostProcess();
    void Update(DX::StepTimer const& timer);
    void Render();
	void RenderTexturePass1();
    void Clear();
    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	//input manager. 
	Input									m_input;
	InputCommands							m_gameInputCommands;

    // DirectXTK objects.
    std::unique_ptr<DirectX::CommonStates>                                  m_states;
    std::unique_ptr<DirectX::BasicEffect>                                   m_batchEffect;	
    std::unique_ptr<DirectX::EffectFactory>                                 m_fxFactory;
    std::unique_ptr<DirectX::SpriteBatch>                                   m_sprites;
    std::unique_ptr<DirectX::SpriteBatch>                                   m_spriteBatch;
    std::unique_ptr<DirectX::SpriteFont>                                    m_font;

	// Scene Objects
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>  m_batch;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>                               m_batchInputLayout;
	std::unique_ptr<DirectX::GeometricPrimitive>                            m_testmodel;
    std::unique_ptr<DirectX::GeometricPrimitive>                            m_shape;

	//lights
	Light																	m_Light;
    Light																	m_Light1;

	//Cameras
	Camera																	m_Camera01;
    Camera                                                                  m_Camera02;

	//textures 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture1;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture2;

	//Shaders
	Shader																	m_BasicShaderPair;
    Shader																	m_BasicShaderPair1;
	ModelClass																m_BasicModel;
	ModelClass																m_BasicModel2;
	ModelClass																m_BasicModel3;
    ModelClass                                                              m_BasicModel4;

	//RenderTextures
	RenderTexture*															m_FirstRenderPass;
	RECT																	m_fullscreenRect;
	RECT																	m_CameraViewRect;
    RECT                                                                    m_bloomRect;
    RenderTexture*                                                          m_offscreenTexture;
    RenderTexture*                                                          m_renderTarget1;
    RenderTexture*                                                          m_renderTarget2;
    RenderTexture*                                                          m_renderTarget3;


#ifdef DXTK_AUDIO
    std::unique_ptr<DirectX::AudioEngine>                                   m_audEngine;
    std::unique_ptr<DirectX::WaveBank>                                      m_waveBank;
    std::unique_ptr<DirectX::SoundEffect>                                   m_soundEffect;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect1;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect2;
#endif
    

#ifdef DXTK_AUDIO
    uint32_t                                                                m_audioEvent;
    float                                                                   m_audioTimerAcc;

    bool                                                                    m_retryDefault;
#endif

    DirectX::SimpleMath::Matrix                                             m_world, m_world1;
    DirectX::SimpleMath::Matrix                                             m_view, m_view1;
    DirectX::SimpleMath::Matrix                                             m_projection, m_projection1, m_projection2;

    Microsoft::WRL::ComPtr<ID3D11Buffer>									m_greyscalebuffer;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>								greycolor_ps;
};
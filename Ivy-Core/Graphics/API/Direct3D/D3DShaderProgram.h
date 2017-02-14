#pragma once

#include <d3dcompiler.h>
#include <d3d11shader.h>

#include "D3DRenderer.h"

namespace Ivy {
    namespace Graphics {
        class D3DShaderProgram : public IShaderProgram {
        public:
            D3DShaderProgram(D3DRenderer* renderer) : m_pRenderer(renderer) {}
            ~D3DShaderProgram();

            virtual void Activate(void) override;
            virtual void Deactivate(void) override;
            virtual bool PushShader(ShaderType shaderType, std::string shaderName) override;
            virtual int GetBlockLocation(ShaderType shaderType, std::string blockName) override;
        
        private:

            bool CreateShader(ShaderType shaderType);
            ComPtr<ID3DBlob>& GetShaderBlob(ShaderType shaderType);
            std::string GetShaderTarget(ShaderType shaderType);
                                                                
            D3DRenderer* m_pRenderer;
            
            ComPtr<ID3DBlob> m_pComputeShaderBlob;
            ComPtr<ID3DBlob> m_pDomainShaderBlob;
            ComPtr<ID3DBlob> m_pGeometryShaderBlob;
            ComPtr<ID3DBlob> m_pHullShaderBlob;
            ComPtr<ID3DBlob> m_pPixelShaderBlob;
            ComPtr<ID3DBlob> m_pVertexShaderBlob;

            ComPtr<ID3D11ComputeShader> m_pComputeShader;
            ComPtr<ID3D11DomainShader> m_pDomainShader;
            ComPtr<ID3D11HullShader> m_pHullShader;
            ComPtr<ID3D11GeometryShader> m_pGeometryShader;
            ComPtr<ID3D11PixelShader> m_pPixelShader;
            ComPtr<ID3D11VertexShader> m_pVertexShader;
        };
    }
}
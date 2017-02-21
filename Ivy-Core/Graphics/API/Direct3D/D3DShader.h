#pragma once

#include "D3DRenderer.h"
#include "../../Shaders/IShader.h"

namespace Ivy {
    namespace Graphics {
        class D3DShader : public IShader {
        public:
               
            D3DShader(D3DRenderer* renderer, ShaderType type, std::string path);
            ~D3DShader();

        protected:

            // Inherited via IShader
            virtual void Activate() override;
            virtual bool Create() override;
            virtual void Deactivate() override;
            virtual std::string GetShaderPath() override;
            virtual std::string GetShaderSource() override;
            virtual ShaderType GetShaderType() override;
            virtual std::string GetVariableName(VariableType variableType, int index) override;
            virtual int GetVariableLocation(VariableType variableType, std::string variableName) override;
            virtual void Release() override;

        private:

            bool CreateInputLayout();
            std::string GetCompilerTarget(ShaderType type);

            D3DRenderer* m_pRenderer;
            ShaderType m_ShaderType;
            std::string m_ShaderPath;
            std::string m_ShaderSource;
            
            ComPtr<ID3DBlob> m_pShaderBlob;
            ComPtr<ID3D11ShaderReflection> m_pShaderReflection;
            ComPtr<ID3D11ComputeShader> m_pComputeShader;
            ComPtr<ID3D11DomainShader> m_pDomainShader;
            ComPtr<ID3D11GeometryShader> m_pGeometryShader;
            ComPtr<ID3D11HullShader> m_pHullShader;
            ComPtr<ID3D11PixelShader> m_pPixelShader;
            ComPtr<ID3D11VertexShader> m_pVertexShader;
            ComPtr<ID3D11InputLayout> m_pInputLayout;
        };
    }
}
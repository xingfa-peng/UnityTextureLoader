#pragma once
#include "RefCounter.h"
#include "Texture.h"
#include "TextureLoadAsyncOpeartionState.h"
namespace Inking
{

    class TextureLoadAsyncOperation : public RefCounter
    {
        String _fileName;
        Texture* _texture = nullptr;

        TextureLoadAsyncOperationState _state = TextureLoadAsyncOperationState::None;
    public:
        TextureLoadAsyncOperation()
        {

        }

        TextureLoadAsyncOperationState GetState()
        {
            return _state;
        }

        void SetState(TextureLoadAsyncOperationState state)
        {
            _state = state;
        }

        Texture* GetTexture() const
        {
            return _texture;
        }

        void SetTexture(Texture* value)
        {
            _texture = value;
        }

        const Char* GetFileName() {
            return _fileName.c_str();
        }

        void SetFileName(const Char* fileName) {
            _fileName = fileName;
        }

        void OnLoadFailed() {
            SetState(TextureLoadAsyncOperationState::LoadFailed);
            SetTexture(nullptr);
        }
    };
}

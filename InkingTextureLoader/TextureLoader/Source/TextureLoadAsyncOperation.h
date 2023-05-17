#pragma once
#include "RefCounter.h"
#include "TextureLoadAsyncOperationState.h"
#include "Texture.h"
#include "ColorSpace.h"
#include "TextureLoadMode.h"

namespace Inking
{

	class TextureLoadAsyncOperation : public RefCounter
	{
		String _fileName;
		Texture* _texture = nullptr;

		TextureLoadMode _loadMode = TextureLoadMode::File;
		ColorSpace _colorSpace = ColorSpace::Linear;

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
			_loadMode = TextureLoadMode::File;
			_fileName = fileName;
		}

        void OnLoadFailed() {
			SetState(TextureLoadAsyncOperationState::LoadFailed);
			SetTexture(nullptr);
		}

		void SetColorSpace(ColorSpace colorSpace)
		{
			_colorSpace = colorSpace;
		}

		ColorSpace GetColorSpace()const
		{
			return _colorSpace;
		}



		void SetBuffer(void* buffer, int bufferLen)
		{
			_loadMode = TextureLoadMode::Memory;
			_buffer = buffer;
			_bufferLen = bufferLen;
		}

		void* _buffer = nullptr;
		int _bufferLen = 0;

		TextureLoadMode GetLoadMode()
		{
			return _loadMode;
		}

		void* GetBuffer()
		{
			return _buffer;
		}

		int GetBufferLen()
		{
			return _bufferLen;
		}
	};
}

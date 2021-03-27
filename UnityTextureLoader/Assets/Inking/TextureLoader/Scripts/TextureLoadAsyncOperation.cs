

using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace Inking
{
    public class TextureLoadAsyncOperation : CustomYieldInstruction
    {
        [DllImport(TextureLoader.DllName)]
        static extern IntPtr Inking_TextureLoadAsyncOperation_New();

        [DllImport(TextureLoader.DllName)]
        static extern IntPtr Inking_TextureLoadAsyncOperation_Release(IntPtr native);

        [DllImport(TextureLoader.DllName)]
        static extern int Inking_TextureLoadAsyncOperation_GetState(IntPtr native);

        [DllImport(TextureLoader.DllName)]
        static extern IntPtr Inking_TextureLoadAsyncOperation_GetTexture(IntPtr native);

        IntPtr _native;

        public TextureLoadAsyncOperation()
        {
            _native = Inking_TextureLoadAsyncOperation_New();
        }

        public TextureLoadAsyncOperation(IntPtr native)
        {
            _native = native;
        }


        ~TextureLoadAsyncOperation()
        {
            Inking_TextureLoadAsyncOperation_Release(_native);
        }

        public TextureLoadAsyncOperationState state
        {
            get
            {
                return (TextureLoadAsyncOperationState)Inking_TextureLoadAsyncOperation_GetState(_native);
            }
        }

        public override bool keepWaiting
        {
            get
            {
                return state == TextureLoadAsyncOperationState.None
                    || state == TextureLoadAsyncOperationState.Loading;
            }
        }

        Texture2D _texture2D;

        public Texture2D texture2D
        {
            get
            {
                if (_texture2D == null)
                {
                    IntPtr nativeTex = Inking_TextureLoadAsyncOperation_GetTexture(_native);
                    _texture2D = new Inking.Texture2D(nativeTex);
                }
                return _texture2D;
            }
        }
    }
}

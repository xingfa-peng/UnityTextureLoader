
using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace Inking
{
    public class Texture2D
    {
        [DllImport(TextureLoader.DllName)]
        static extern int Inking_Texture2D_GetWidth(IntPtr native);

        [DllImport(TextureLoader.DllName)]
        static extern int Inking_Texture2D_GetHeight(IntPtr native);

        [DllImport(TextureLoader.DllName)]
        static extern IntPtr Inking_Texture2D_GetNative(IntPtr native);

        [DllImport(TextureLoader.DllName)]
        static extern void Inking_Texture2D_Release(IntPtr native);

        public string Name;

        IntPtr _native;

        public Texture2D(IntPtr native)
        {
            _native = native;
        }

        ~Texture2D()
        {
            Inking_Texture2D_Release(_native);
        }

        public IntPtr Native
        {
            get
            {
                return Inking_Texture2D_GetNative(_native);
            }
        }

        public int Width
        {
            get
            {
                return Inking_Texture2D_GetWidth(_native);
            }
        }

        public int Height
        {
            get
            {
                return Inking_Texture2D_GetHeight(_native);
            }
        }

        public TextureFormat Format
        {
            get
            {
                return TextureFormat.RGBA32;
            }
        }

        public UnityEngine.Texture2D ToUnityTexture2D()
        {
            var texture = UnityEngine.Texture2D.CreateExternalTexture(Width,
                        Height,
                        Format,
                        false,
                        true,
                        Native);

            texture.name = this.Name;

            return texture;
        }
    };
}

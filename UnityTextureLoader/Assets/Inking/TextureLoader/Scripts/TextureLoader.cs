

using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

namespace Inking
{
    public class TextureLoader : MonoBehaviour
    {
#if UNITY_IOS && !UNITY_EDITOR
        public const string DllName = "__Internal";
#else
        public const string DllName = "InkingTextureLoader";
#endif

        [DllImport(DllName)]
        static extern IntPtr Inking_TextureLoader_GetInstance();

#if UNITY_STANDALONE_WIN || UNITY_EDITOR
        [DllImport(DllName)]
        static extern IntPtr Inking_TextureLoader_LoadAsync(IntPtr _native, [MarshalAs(UnmanagedType.LPWStr)]string fileName);
#else
        [DllImport(DllName)]
        static extern IntPtr Inking_TextureLoader_LoadAsync(IntPtr _native, string fileName);
#endif
        [DllImport(DllName)]
        static extern void Inking_TextureLoader_Update(IntPtr native);

        [DllImport(DllName)]
        static extern IntPtr GetRenderEventFunc();

        IntPtr _native;

        public TextureLoader()
        {
        }

        ~TextureLoader()
        {
        }

        static TextureLoader _instance;
        public static TextureLoader Instance
        {
            get
            {
                if (_instance == null)
                {
                    var obj = new GameObject(typeof(TextureLoader).Name);
                    DontDestroyOnLoad(obj);
                    _instance = obj.AddComponent<TextureLoader>();
                }
                return _instance;
            }
        }

        private void Awake()
        {
            _native = Inking_TextureLoader_GetInstance();
        }

        public void Start()
        {
            GL.IssuePluginEvent(GetRenderEventFunc(), 1);
        }

        public TextureLoadAsyncOperation LoadAsync(string fileName)
        {
            IntPtr ptr = Inking_TextureLoader_LoadAsync(_native, fileName);
            var operation = new TextureLoadAsyncOperation(ptr);
            operation.fileName = fileName;
            return operation;
        }

        public void Update()
        {
            Inking_TextureLoader_Update(_native);
        }

        IEnumerator _LoadAsync(string fileName, Action<Texture2D> onLoadSucceed, Action onLoadFailed)
        {
            var operation = LoadAsync(fileName);

            yield return operation;

            if (operation != null 
                && operation.state == TextureLoadAsyncOperationState.LoadSucceed)
            {
                if(onLoadSucceed != null)
                    onLoadSucceed.Invoke(operation.texture2D);
            }
            else
            {
                if(onLoadFailed != null)
                    onLoadFailed.Invoke();
            }
        }

        public void LoadAsync(string fileName, Action<Texture2D> onLoadSucceed, Action onLoadFailed)
        {
            StartCoroutine(_LoadAsync(fileName, onLoadSucceed, onLoadFailed));
        }
    }
}

using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;

namespace Inking
{

    public class TextureLoaderTest : MonoBehaviour
    {
        [SerializeField]
        RawImage rawImage;

        // Start is called before the first frame update
        void Start()
        {
        }
        
        public void LoadFromFile_Linear()
        {
            NativeGallery.GetImageFromGallery((filePath) =>
            {
                if (filePath == null)
                    return;

                Inking.TextureLoader.Instance.LoadAsync(filePath
                    , ColorSpace.Linear
                    , (texture2D) =>
                    {
                        rawImage.texture = texture2D.ToUnityTexture2D();
                        _texture = texture2D;
                    }
                    , () =>
                    {
                        Debug.LogError("load failed...");
                    });
            });
        }
        
        public void LoadFromFile_Gamma()
        {
            NativeGallery.GetImageFromGallery((filePath) =>
            {
                if (filePath == null)
                    return;

                Inking.TextureLoader.Instance.LoadAsync(filePath
                    , ColorSpace.Gamma
                    , (texture2D) =>
                    {
                        rawImage.texture = texture2D.ToUnityTexture2D();
                        _texture = texture2D;
                    }
                    , () =>
                    {
                        Debug.LogError("load failed...");
                    });
            });
        }

        public void LoadFromMemory_Linear()
        {
            NativeGallery.GetImageFromGallery((filePath) =>
            {
                if (filePath == null)
                    return;

                var bytes = File.ReadAllBytes(filePath);
                Inking.TextureLoader.Instance.LoadAsyncFromMemory(bytes
                    , ColorSpace.Linear
                    , (texture2D) =>
                    {
                        rawImage.texture = texture2D.ToUnityTexture2D();
                        _texture = texture2D;
                    }
                    , () =>
                    {
                        Debug.LogError("load failed...");
                    });
            });
        }

        public void LoadFromMemory_Gamma()
        {
            NativeGallery.GetImageFromGallery((filePath) =>
            {
                if (filePath == null)
                    return;

                var bytes = File.ReadAllBytes(filePath);
                Inking.TextureLoader.Instance.LoadAsyncFromMemory(bytes
                    , ColorSpace.Gamma
                    , (texture2D) =>
                    {
                        rawImage.texture = texture2D.ToUnityTexture2D();
                        _texture = texture2D;
                    }
                    , () =>
                    {
                        Debug.LogError("load failed...");
                    });
            });
        }


        // Update is called once per frame
        void Update()
        {
        }

        string _path;

        Inking.Texture2D _texture;

        private void LateUpdate()
        {
            GC.Collect();
        }

    }

}

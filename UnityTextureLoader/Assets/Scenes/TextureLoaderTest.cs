using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Inking
{
    public class TextureLoaderTest : MonoBehaviour
    {
        [SerializeField]
        RawImage rawImage;

        Texture2D _texture2D;

        // Use this for initialization
        void Start()
        {
            
        }

        // Update is called once per frame
        void Update()
        {
            if(Input.GetMouseButtonUp(0))
            {
                UpdateTexture();
            }
        }

        void UpdateTexture()
        {
            NativeGallery.GetImageFromGallery((filePath) =>
            {
                TextureLoader.Instance.LoadAsync(filePath, (texture) =>
                {
                    rawImage.texture = texture.ToUnityTexture2D();

                    _texture2D = texture;

                }, () =>
                {
                    Debug.LogError("Load Failed : " + filePath);
                });
            });
        }
    }

}

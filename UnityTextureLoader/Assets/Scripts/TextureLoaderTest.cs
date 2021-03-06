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

        Inking.Texture2D _texture2D;

        // Start is called before the first frame update
        void Start()
        {
        }

        private void Update()
        {
            if(Input.GetMouseButtonUp(0))
            {
                OnButtonClicked();
            }
        }

        void LoadTexture(string fileName)
        {
            Inking.TextureLoader.Instance.LoadAsync(fileName,
                (texture2D) =>
                {
                    Debug.Log("Load Texture Succeed : " + fileName);
                    rawImage.texture = texture2D.ToUnityTexture2D();

                    _texture2D = texture2D;
                },
                () =>
                {
                    Debug.LogError("Load Texture Failed : " + fileName);
                });
        }

        public void OnButtonClicked()
        {
            NativeGallery.GetImageFromGallery((fileName)=>
            {
                if (string.IsNullOrEmpty(fileName))
                    return;

                LoadTexture(fileName);
            });
        }
    }

}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TextureLoaderTest : MonoBehaviour
{
    [SerializeField]
    RawImage rawImage;

    Inking.Texture2D _texture2D;

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("pxf...Application.persistentDataPath : " + Application.persistentDataPath);
        var path = @"C:\Users\pxf\Pictures\Camera Roll\1.jpg";
        Inking.TextureLoader.Instance.LoadAsync(path,
            (texture2D) =>
            {
                rawImage.texture = Texture2D.CreateExternalTexture(texture2D.Width,
                    texture2D.Height,
                    texture2D.Format,
                    false,
                    true,
                    texture2D.Native);

                //_texture2D = texture2D;

                System.GC.Collect();
            },
            () =>
            {

            });
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetMouseButtonUp(1))
        {
            Debug.Log("pxf...Application.persistentDataPath : " + Application.persistentDataPath);
            var path = @"C:\Users\pxf\Pictures\Camera Roll\1.jpg";

            Inking.TextureLoader.Instance.LoadAsync(path,
                (texture2D) =>
                {
                    rawImage.texture = Texture2D.CreateExternalTexture(texture2D.Width,
                        texture2D.Height,
                        texture2D.Format,
                        false,
                        true,
                        texture2D.Native);

                    //_texture2D = texture2D;

                    System.GC.Collect();
                },
                () =>
                {

                });
        }
        
    }
}

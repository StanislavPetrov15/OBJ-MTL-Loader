namespace
{
    /*(TO-FIX) (A) it is possible that the different 3D modelling programs use different byte sequence
         to specify a new line; Blender for example uses '\n'; Parse_MTL() must support different new-line sequences */

    /* format of a (unsigned int) typograph:
           - bits 0..23 :: base-types flags
           - bits 24..31 :: identifier of the real type (a value between 24 and 256)
           -> in this format of the typographs are possible 24 base types and 232 real types */

    //(PUBLIC)

    /*  (USAGE)
        list<Material> (materials | materials(<N>, false)) ;
        int result = Parse_MTL(<filepath>, materials);
        //(->)
        Release(materials); */

    //indices of the base types in the (typographs of the real types)
    const short B_AMBIENT_REFLECTIVITY_COLOR = 0;
    const short B_DIFFUSE_REFLECTIVITY_COLOR = 1;
    const short B_SPECULAR_REFLECTIVITY_COLOR = 2;
    const short B_TRANSMISSION_FILTER = 3;
    const short B_TEXTURE_MAP_OPTIONS = 4;
    //identifiers of the real types in (the typographs)
    const short AMBIENT_REFLECTIVITY_COLOR_RGB = 24;
    const short AMBIENT_REFLECTIVITY_COLOR_XYZ = 25;
    const short AMBIENT_REFLECTIVITY_COLOR_SPECTRAL = 26;
    const short DIFFUSE_REFLECTIVITY_COLOR_RGB = 24;
    const short DIFFUSE_REFLECTIVITY_COLOR_XYZ = 25;
    const short DIFFUSE_REFLECTIVITY_COLOR_SPECTRAL = 26;
    const short SPECULAR_REFLECTIVITY_COLOR_RGB = 24;
    const short SPECULAR_REFLECTIVITY_COLOR_XYZ = 25;
    const short SPECULAR_REFLECTIVITY_COLOR_SPECTRAL = 26;
    const short TRANSMISSION_FILTER_COLOR_RGB = 24;
    const short TRANSMISSION_FILTER_COLOR_XYZ = 25;
    const short TRANSMISSION_FILTER_COLOR_SPECTRAL = 26;
    const short BLENDU_OPTION = 50;
    const short BLENDV_OPTION = 51;
    const short BM_OPTION = 52;
    const short BOOST_OPTION = 53;
    const short CC_OPTION = 54;
    const short CLAMP_OPTION = 55;
    const short IMFCHAN_OPTION = 56;
    const short MM_OPTION = 57;
    const short O_OPTION = 58;
    const short S_OPTION = 59;
    const short T_OPTION = 60;
    const short TEXRES_OPTION = 61;

    enum class IlluminationModel
    {
        COLOR_ON_AMBIENT_OFF,
        COLOR_ON_AMBIENT_ON,
        HIGHLIGHT_ON,
        REFLECTION_ON_RAYTRACE_ON,
        TRANSPARENCY_GLASS_ON_REFLECTION_TRACE_ON,
        FRESNEL_ON_RAYTRACE_ON,
        REFRACTION_ON,
        TRANSPARENCY_REFRACTION_ON_REFLECTION_FRESNEL_OFF_RAYTRACE_ON,
        TRANSPARENCY_REFRACTION_ON_REFLECTION_FRESNEL_ON_RAYTRACE_ON,
        REFLECTION_ON_RAYTRACE_OFF,
        TRANSPARENCY_GLASS_ON_REFLECTION_RAYTRACE_OFF,
        CAST_SHADOWS_ONTO_INVISIBLE_SURFACES
    };

    //(IS-BASE-TYPE)
    struct B_AmbientReflectivity_Color
    {
        unsigned int Typograph;
    };

    //(IS B_AmbientReflectivity_Color)
    struct AmbientReflectivity_RGB
    {
        unsigned int Typograph = B_AMBIENT_REFLECTIVITY_COLOR | (AMBIENT_REFLECTIVITY_COLOR_RGB << 24);
        float R;
        float G;
        float B;
    };

    //(IS B_AmbientReflectivity_Color)
    struct AmbientReflectivity_XYZ
    {
        unsigned int Typograph = B_AMBIENT_REFLECTIVITY_COLOR | (AMBIENT_REFLECTIVITY_COLOR_XYZ << 24);
        float X;
        float Y;
        float Z;
    };

    //(IS B_AmbientReflectivity_Color)
    //това вероятно няма да се поддържа тъй като .rfl формата е недокументиран
    struct AmbientReflectivity_Spectral
    {
        unsigned int Typograph = B_AMBIENT_REFLECTIVITY_COLOR | (AMBIENT_REFLECTIVITY_COLOR_SPECTRAL << 24);
        string File;
        float Factor;
    };

    //(IS-BASE-TYPE)
    struct B_DiffuseReflectivity_Color
    {
        unsigned int Typograph;
    };

    //(IS B_DiffuseReflectivity)
    struct DiffuseReflectivity_RGB
    {
        unsigned int Typograph = B_DIFFUSE_REFLECTIVITY_COLOR | (DIFFUSE_REFLECTIVITY_COLOR_RGB << 24);
        float R;
        float G;
        float B;
    };

    //(IS B_DiffuseReflectivity)
    struct DiffuseReflectivity_XYZ
    {
        unsigned int Typograph = B_DIFFUSE_REFLECTIVITY_COLOR | (DIFFUSE_REFLECTIVITY_COLOR_XYZ << 24);
        float X;
        float Y;
        float Z;
    };

    //(IS B_DiffuseReflectivity)
    struct DiffuseReflectivity_Spectral
    {
        unsigned int Typograph =  B_DIFFUSE_REFLECTIVITY_COLOR | (DIFFUSE_REFLECTIVITY_COLOR_SPECTRAL << 24);
        string File;
        float Factor;
    };

    //(IS-BASE-TYPE)
    struct B_SpecularReflectivity_Color
    {
        unsigned int Typograph;
    };

    //(IS B_SpecularReflectivity)
    struct SpecularReflectivity_RGB
    {
        unsigned int Typograph = B_SPECULAR_REFLECTIVITY_COLOR | (SPECULAR_REFLECTIVITY_COLOR_RGB << 24);
        float R;
        float G;
        float B;
    };

    //(IS B_SpecularReflectivity)
    struct SpecularReflectivity_XYZ
    {
        unsigned int Typograph = B_SPECULAR_REFLECTIVITY_COLOR | (SPECULAR_REFLECTIVITY_COLOR_XYZ << 24);
        float X;
        float Y;
        float Z;
    };

    //(IS B_SpecularReflectivity)
    struct SpecularReflectivity_Spectral
    {
        unsigned int Typograph = B_SPECULAR_REFLECTIVITY_COLOR | (SPECULAR_REFLECTIVITY_COLOR_SPECTRAL << 24);
        string File;
        float Factor;
    };

    //(IS-BASE-TYPE)
    struct B_TransmissionFilter
    {
        unsigned int Typograph;
    };

    //(IS B_TransmissionFilter)
    struct TransmissionFilter_RGB
    {
        unsigned int Typograph = B_TRANSMISSION_FILTER | (TRANSMISSION_FILTER_COLOR_RGB << 24);
        float R;
        float G;
        float B;
    };

    //(IS B_TransmissionFilter)
    struct TransmissionFilter_XYZ
    {
        unsigned int Typograph = B_TRANSMISSION_FILTER | (TRANSMISSION_FILTER_COLOR_XYZ << 24);
        float X;
        float Y;
        float Z;
    };

    //(IS B_TransmissionFilter)
    struct TransmissionFilter_Spectral
    {
        unsigned int Typograph = B_TRANSMISSION_FILTER | (TRANSMISSION_FILTER_COLOR_SPECTRAL << 24);
        string File;
        float Factor;
    };

    //(IS-BASE-TYPE)
    struct B_Option
    {
        unsigned char Typograph;
    };

    //(IS B_Option)
    struct blendu_option
    {
        unsigned char Typograph = BLENDU_OPTION;
        bool Value = true;
    };

    //(IS B_Option)
    struct blendv_option
    {
        unsigned char Typograph = BLENDV_OPTION;
        bool Value = true;
    };

    //(IS B_Option)
    struct bm_option
    {
        unsigned char Typograph = BM_OPTION;
        float Multiplier;
    };

    //(IS B_Option)
    struct boost_option
    {
        unsigned char Typograph = BOOST_OPTION;
        float Value;
    };

    //(IS B_Option)
    struct cc_option
    {
        unsigned char Typograph = CC_OPTION;
        bool Value;
    };

    //(IS B_Option)
    struct clamp_option
    {
        unsigned char Typograph = CLAMP_OPTION;
        bool Value = false;
    };

    //(IS B_Option)
    struct imfchan_option
    {
        unsigned char Typograph = IMFCHAN_OPTION;
        float R;
        float G;
        float B;
        float M;
        float L;
        float Z;
    };

    //(IS B_Option)
    struct mm_option
    {
        unsigned char Typograph = MM_OPTION;
        float Base;
        float Gain;
    };

    //(IS B_Option)
    struct o_option
    {
        unsigned char Typograph = O_OPTION;
        float U;
        float V;
        float W;
    };

    //(IS B_Option)
    struct s_option
    {
        unsigned char Typograph = S_OPTION;
        float U;
        float V;
        float W;
    };

    //(IS B_Option)
    struct t_option
    {
        unsigned char Typograph = T_OPTION;
        float U;
        float V;
        float W;
    };

    //(IS B_Option)
    struct texres_option
    {
        unsigned char Typograph = TEXRES_OPTION;
        int Resolution;
    };

    struct AmbientReflectivity_Texture
    {
        list<B_Option*> Options;
        string Filename;

        ~AmbientReflectivity_Texture()
        {
            for (B_Option* __option : Options)
            {
                delete __option;
            }
        }
    };

    struct DiffuseReflectivity_Texture
    {
        list<B_Option*> Options;
        string Filename;

        ~DiffuseReflectivity_Texture()
        {
            for (B_Option* __option : Options)
            {
                delete __option;
            }
        }
    };

    struct SpecularReflectivity_Texture
    {
        list<B_Option*> Options;
        string Filename;

        ~SpecularReflectivity_Texture()
        {
            for (B_Option* __option : Options)
            {
                delete __option;
            }
        }
    };

    struct DissolveFactor_Texture
    {
        list<B_Option*> Options;
        string Filename;

        ~DissolveFactor_Texture()
        {
            for (B_Option* __option : Options)
            {
                delete __option;
            }
        }
    };

    struct SpecularExponent_Texture
    {
        list<B_Option*> Options;
        string Filename;

        ~SpecularExponent_Texture()
        {
            for (B_Option* __option : Options)
            {
                delete __option;
            }
        }
    };

    struct Decal_Texture
    {
        list<B_Option*> Options;
        string Filename;

        ~Decal_Texture()
        {
            for (B_Option* __option : Options)
            {
                delete __option;
            }
        }
    };

    struct Bump_Texture
    {
        list<B_Option*> Options;
        string Filename;

        ~Bump_Texture()
        {
            for (B_Option* __option : Options)
            {
                delete __option;
            }
        }
    };

    struct Displacement_Texture
    {
        list<B_Option*> Options;
        string Filename;

        ~Displacement_Texture()
        {
            for (B_Option* __option : Options)
            {
                delete __option;
            }
        }
    };

    struct DissolveFactor
    {
        bool Halo = false;
        float Value = 1.0;
    };

    enum class ReflectionMapType
    {
        SPHERE,
        CUBE_TOP,
        CUBE_BOTTOM,
        CUBE_FRONT,
        CUBE_BACK,
        CUBE_LEFT,
        CUBE_RIGHT
    };

    struct ReflectionMap
    {
        ReflectionMapType Type;
        list<char*> Options; //(B)

        ~ReflectionMap()
        {
            for (char* __option : Options)
            {
                delete [] __option;
            }
        }
    };

    /* default values:
       bool blendu = true;
       bool blendv = true;
       bool clamp = false
       imfchan (bump & scalar texture) = 'l'; with decal = 'm'
       mm.BaseValue = 0
       mm.Gain = 1 */
    struct Material
    {
         string Name;

         //Color Reflectivity Attributes

         B_AmbientReflectivity_Color* AmbientReflectivity_Color = nullptr; //element Ka
         B_DiffuseReflectivity_Color* DiffuseReflectivity_Color = nullptr; //element Kd
         B_SpecularReflectivity_Color* SpecularReflectivity_Color = nullptr; //element Ks
         B_TransmissionFilter* TransmissionFilter = nullptr; //element Tf
         DissolveFactor DissolveFactor_Color; //element d
         float SpecularExponent_Color = -1.0; //element Ns
         float OpticalDensity_Color = -1.0; //Ni
         float Sharpness_Color = -1.0; //element sharpness
         IlluminationModel IlluminationModel_Color; //element illum

         //Texture Reflectivity Attributes

         bool AntiAliasing = false;
         AmbientReflectivity_Texture* AmbientReflectivity_Texture = nullptr; //element map_Ka
         DiffuseReflectivity_Texture* DiffuseReflectivity_Texture = nullptr;  //element map_Kd
         SpecularReflectivity_Texture* SpecularReflectivity_Texture = nullptr; //element map_Ks
         DissolveFactor_Texture* DissolveFactor_Texture = nullptr; //element map_d
         SpecularExponent_Texture* SpecularExponent_Texture = nullptr; //element map_Ns
         Decal_Texture* Decal_Texture = nullptr; //element decal
         Bump_Texture* Bump_Texture = nullptr; //element bump
         Displacement_Texture* Displacement_Texture = nullptr; //element disp

         //Reflection Map Attributes
         ReflectionMap* ReflectionMap = nullptr; //element refl
    };

    //(!) -о u v w : 'v' and 'w' are optional fields
    //(!) -s u v w : 'v' and 'w' are optional fields
    //(!) -t u v w : 'v' and 'w' are optional fields
    //(!) Ka r g b : 'g' and 'b' are optional parameters
    //(!) Ka xyz x y z : 'y' and 'z' are optional parameters
    //(!) Ka spectral file.rfl factor : 'factor' is an optional parameter
    //(!) Kd r g b : 'g' and 'b' are optional parameters
    //(!) Kd xyz x y z : 'y' and 'z' are optional parameters
    //(!) Kd spectral file.rfl factor : 'factor' is an optional parameter
    //(!) Ks r g b : 'g' and 'b' are optional parameters
    //(!) Ks xyz x y z : 'y' and 'z' are optional parameters
    //(!) Ks spectral file.rfl factor : 'factor' is an optional parameter
    //(!) Tf r g b : 'g' and 'b' are optional parameters
    //(!) Tf xyz x y z : 'y' and 'z' are optional parameters
    //(!) Tf spectral file.rfl factor : 'factor' is an optional parameter

    /* (!) it is possible some programs to include elements that are not part of the .mtl specification (Paul Bourke);
           such elements are ignored by this function */
    //size of the file is too big => -1
    //successful execution => 0
    //_materials is IN parameter
    /* the file specified by _filepath exists and is syntactically and semantically valid (this function does not perform any
            syntactic or semantic validation) -> */
    int Parse_MTL(const string& _filepath, list<Material>& _materials)
    {
        filesystem::File materials(_filepath);

        int filesize = materials.size();

        char* data;

        try
        {
            data = new char[filesize];
        }
        catch (const std::bad_alloc& e)
        {
            return -1;
        }

        materials.ReadBlock(reinterpret_cast<unsigned char*>(data), filesize, false);

        //reading the lines (elements)

        int lineBegin = 0;

        Material* newMaterial;

        for (int i = 0; i < filesize; i++)
        {
            char currentByte = data[i];

            //if this is the beginning of a comment
            if (currentByte == '#')
            {
                for (int n = i + 1; n < filesize; n++)
                {
                    //if the next line is reached (i.e. end of the comment)
                    if (data[n] == 10) //(A)
                    {
                        lineBegin = n + 1;
                        i = n;
                        break;
                    }
                }

                continue; //go to the next line (if there is one), i.e. if the comment is not at the end of the document
            }

            //if a new-line marker is reached
            if (currentByte == 10)
            {
                //traversing the elements of the current line

                int lineLength = i - lineBegin;
                string line(&(data[lineBegin]), ascii, (unsigned int)lineLength);
                line.Trim(' ').Trim('\t');
                list<string> lineElements = line.Split(' ', true);

                //->
                lineBegin = i + 1;

                //if the current line is empty (line with length 0, not just filled with empty spaces)
                if (lineElements.count() == 0)
                {
                    continue;
                }

                //(STATE) the current line is not empty

                list<string> attributes(lineElements, 1, lineElements.count() - 1);
                string tag = lineElements[0];

                if (tag == "newmtl")
                {
                    Material material;
                    material.Name = lineElements[1];
                    _materials.Append(material);
                    newMaterial = &(_materials.last());
                }
                else if (tag == "Ka")
                {
                    //(FORMAT) Ka spectral file.rfl factor | Ka spectral file.rfl
                    if (attributes[0] == "spectral")
                    {
                         AmbientReflectivity_Spectral* reflectivity = new AmbientReflectivity_Spectral;

                         reflectivity->File = attributes[1];

                         if (attributes.count() == 3)
                         {
                             reflectivity->Factor = attributes[2].ToFloat();
                         }

                         newMaterial->AmbientReflectivity_Color = reinterpret_cast<B_AmbientReflectivity_Color*>(reflectivity);
                    }
                    //(FORMAT) Ka xyz <float> | Ka xyz x y z
                    else if (attributes[0] == "xyz")
                    {
                        AmbientReflectivity_XYZ* reflectivity = new AmbientReflectivity_XYZ;

                        //(FORMAT) Ka xyz <float>
                        if (attributes.count() == 2)
                        {
                            float value = attributes[1].ToFloat();
                            reflectivity->X = value;
                            reflectivity->Y = value;
                            reflectivity->Z = value;
                        }
                        //(FORMAT) Ka xyz x y z
                        else
                        {
                            reflectivity->X = attributes[1].ToFloat();
                            reflectivity->Y = attributes[2].ToFloat();
                            reflectivity->Z = attributes[3].ToFloat();
                        }

                        newMaterial->AmbientReflectivity_Color = reinterpret_cast<B_AmbientReflectivity_Color*>(reflectivity);
                    }
                    //(FORMAT) Ka <float>
                    else if (attributes.count() == 1)
                    {
                          AmbientReflectivity_RGB* reflectivity = new AmbientReflectivity_RGB;
                          float value = attributes[0].ToFloat();
                          reflectivity->R = value;
                          reflectivity->G = value;
                          reflectivity->B = value;
                          newMaterial->AmbientReflectivity_Color = reinterpret_cast<B_AmbientReflectivity_Color*>(reflectivity);
                    }
                    //(FORMAT) Ka r g b
                    else if (attributes.count() == 3)
                    {
                         AmbientReflectivity_RGB* reflectivity = new AmbientReflectivity_RGB;
                         reflectivity->R = attributes[0].ToFloat();
                         reflectivity->G = attributes[1].ToFloat();
                         reflectivity->B = attributes[2].ToFloat();
                         newMaterial->AmbientReflectivity_Color = reinterpret_cast<B_AmbientReflectivity_Color*>(reflectivity);
                    }
                }
                else if (tag == "Kd")
                {
                    //(FORMAT) Kd spectral file.rfl factor | Kd spectral file.rfl
                    if (attributes[0] == "spectral")
                    {
                        DiffuseReflectivity_Spectral* reflectivity = new DiffuseReflectivity_Spectral;

                        reflectivity->File = attributes[1];

                        if (attributes.count() == 3)
                        {
                            reflectivity->Factor = attributes[2].ToFloat();
                        }

                        newMaterial->DiffuseReflectivity_Color = reinterpret_cast<B_DiffuseReflectivity_Color*>(reflectivity);
                    }
                    //(FORMAT) Kd xyz <float> | Kd xyz x y z
                    else if (attributes[0] == "xyz")
                    {
                        DiffuseReflectivity_XYZ* reflectivity = new DiffuseReflectivity_XYZ;

                        //(FORMAT) Kd xyz <float>
                        if (attributes.count() == 2)
                        {
                            float value = attributes[1].ToFloat();
                            reflectivity->X = value;
                            reflectivity->Y = value;
                            reflectivity->Z = value;
                        }
                        //(FORMAT) Kd xyz x y z
                        else
                        {
                            reflectivity->X = attributes[1].ToFloat();
                            reflectivity->Y = attributes[2].ToFloat();
                            reflectivity->Z = attributes[3].ToFloat();
                        }

                        newMaterial->DiffuseReflectivity_Color = reinterpret_cast<B_DiffuseReflectivity_Color*>(reflectivity);
                    }
                    //(FORMAT) Kd <float>
                    else if (attributes.count() == 1)
                    {
                        DiffuseReflectivity_RGB* reflectivity = new DiffuseReflectivity_RGB;
                        float value = attributes[0].ToFloat();
                        reflectivity->R = value;
                        reflectivity->G = value;
                        reflectivity->B = value;
                        newMaterial->DiffuseReflectivity_Color = reinterpret_cast<B_DiffuseReflectivity_Color*>(reflectivity);
                    }
                    //(FORMAT) Kd r g b
                    else if (attributes.count() == 3)
                    {
                        DiffuseReflectivity_RGB* reflectivity = new DiffuseReflectivity_RGB;
                        reflectivity->R = attributes[0].ToFloat();
                        reflectivity->G = attributes[1].ToFloat();
                        reflectivity->B = attributes[2].ToFloat();
                        newMaterial->DiffuseReflectivity_Color = reinterpret_cast<B_DiffuseReflectivity_Color*>(reflectivity);
                    }

                    auto egoeg = true;
                }
                else if (tag == "Ks")
                {
                    //(FORMAT) Ks spectral file.rfl factor | Ks spectral file.rfl
                    if (attributes[0] == "spectral")
                    {
                        SpecularReflectivity_Spectral* reflectivity = new SpecularReflectivity_Spectral;

                        reflectivity->File = attributes[1];

                        if (attributes.count() == 3)
                        {
                            reflectivity->Factor = attributes[2].ToFloat();
                        }

                        newMaterial->SpecularReflectivity_Color = reinterpret_cast<B_SpecularReflectivity_Color*>(reflectivity);
                    }
                    //(FORMAT) Ks xyz <float> | Ks xyz x y z
                    else if (attributes[0] == "xyz")
                    {
                        SpecularReflectivity_XYZ* reflectivity = new SpecularReflectivity_XYZ;

                        //(FORMAT) Ks xyz <float>
                        if (attributes.count() == 2)
                        {
                            float value = attributes[1].ToFloat();
                            reflectivity->X = value;
                            reflectivity->Y = value;
                            reflectivity->Z = value;
                        }
                        //(FORMAT) Ks xyz x y z
                        else
                        {
                            reflectivity->X = attributes[1].ToFloat();
                            reflectivity->Y = attributes[2].ToFloat();
                            reflectivity->Z = attributes[3].ToFloat();
                        }

                        newMaterial->SpecularReflectivity_Color = reinterpret_cast<B_SpecularReflectivity_Color*>(reflectivity);
                    }
                    //(FORMAT) Ks <float>
                    else if (attributes.count() == 1)
                    {
                        SpecularReflectivity_RGB* reflectivity = new SpecularReflectivity_RGB;
                        float value = attributes[0].ToFloat();
                        reflectivity->R = value;
                        reflectivity->G = value;
                        reflectivity->B = value;
                        newMaterial->SpecularReflectivity_Color = reinterpret_cast<B_SpecularReflectivity_Color*>(reflectivity);
                    }
                    //(FORMAT) Ks r g b
                    else if (attributes.count() == 3)
                    {
                        SpecularReflectivity_RGB* reflectivity = new SpecularReflectivity_RGB;
                        reflectivity->R = attributes[0].ToFloat();
                        reflectivity->G = attributes[1].ToFloat();
                        reflectivity->B = attributes[2].ToFloat();
                        newMaterial->SpecularReflectivity_Color = reinterpret_cast<B_SpecularReflectivity_Color*>(reflectivity);
                    }

                    auto kegeg = true;
                }
                else if (tag == "tf")
                {
                    //(FORMAT) Tf spectral file.rfl factor | Tf spectral file.rfl
                    if (attributes[0] == "spectral")
                    {
                        TransmissionFilter_Spectral* filter = new TransmissionFilter_Spectral;

                        filter->File = attributes[1];

                        if (attributes.count() == 3)
                        {
                            filter->Factor = attributes[2].ToFloat();
                        }

                        newMaterial->TransmissionFilter = reinterpret_cast<B_TransmissionFilter*>(filter);
                    }
                    //(FORMAT) Tf xyz <float> | Tf xyz x y z
                    else if (attributes[0] == "xyz")
                    {
                        TransmissionFilter_XYZ* filter = new TransmissionFilter_XYZ;

                        //(FORMAT) Tf xyz <float>
                        if (attributes.count() == 2)
                        {
                            float value = attributes[1].ToFloat();
                            filter->X = value;
                            filter->Y = value;
                            filter->Z = value;
                        }
                        //(FORMAT) Tf xyz x y z
                        else
                        {
                            filter->X = attributes[1].ToFloat();
                            filter->Y = attributes[2].ToFloat();
                            filter->Z = attributes[3].ToFloat();
                        }

                        newMaterial->TransmissionFilter = reinterpret_cast<B_TransmissionFilter*>(filter);
                    }
                    //(FORMAT) Tf <float>
                    else if (attributes.count() == 1)
                    {
                        TransmissionFilter_RGB* filter = new TransmissionFilter_RGB;
                        float value = attributes[0].ToFloat();
                        filter->R = value;
                        filter->G = value;
                        filter->B = value;
                        newMaterial->TransmissionFilter = reinterpret_cast<B_TransmissionFilter*>(filter);
                    }
                    //(FORMAT) Tf r g b
                    else if (attributes.count() == 3)
                    {
                        TransmissionFilter_RGB* filter = new TransmissionFilter_RGB;
                        filter->R = attributes[0].ToFloat();
                        filter->G = attributes[1].ToFloat();
                        filter->B = attributes[2].ToFloat();
                        newMaterial->TransmissionFilter = reinterpret_cast<B_TransmissionFilter*>(filter);
                    }

                    auto eeg = true;
                }
                else if (tag == "Ns")
                {
                     newMaterial->SpecularExponent_Color = attributes[0].ToFloat();
                }
                else if (tag == "Ni")
                {
                    newMaterial->OpticalDensity_Color = attributes[0].ToFloat();
                }
                else if (tag == "illum")
                {
                    newMaterial->IlluminationModel_Color = static_cast<IlluminationModel>(attributes[0].ToInteger(DECIMAL_A));
                }
                else if (tag == 'd')
                {
                     //(FORMAT) d factor
                     if (attributes.count() == 1)
                     {
                           newMaterial->DissolveFactor_Color.Value = attributes[0].ToFloat();
                     }
                     //(FORMAT) d -halo factor
                     else
                     {
                         newMaterial->DissolveFactor_Color.Halo = true;
                         newMaterial->DissolveFactor_Color.Value = attributes[1].ToFloat();
                     }
                }
                else if (tag == "sharpness")
                {
                      newMaterial->Sharpness_Color = attributes[0].ToInteger(DECIMAL_A);
                }
                else if (tag == "map_Ka")
                {
                    newMaterial->AmbientReflectivity_Texture = new AmbientReflectivity_Texture;

                    int beginIndex = 0;

                    //until parameter 'filename' is reached
                    while (true)
                    {
                        //if parameter 'filename' is reached
                        if (!attributes[beginIndex].BeginsWith('-'))
                        {
                            break;
                        }

                        //(STATE) beginIndex is the beginning of an option (i.e. parameter 'filename' is not reached yet)

                        if (attributes[beginIndex] == "-blendu")
                        {
                            blendu_option* option = new blendu_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->AmbientReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendv")
                        {
                            blendv_option* option = new blendv_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->AmbientReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-cc")
                        {
                            cc_option* option = new cc_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->AmbientReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-clamp")
                        {
                            clamp_option* option = new clamp_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->AmbientReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-mm")
                        {
                            mm_option* option = new mm_option;
                            option->Base = attributes[beginIndex + 1].ToFloat();
                            option->Gain = attributes[beginIndex + 2].ToFloat();
                            newMaterial->AmbientReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 3;
                        }
                        else if (attributes[beginIndex] == "-o")
                        {
                            o_option* option = new o_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->AmbientReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-s")
                        {
                            s_option* option = new s_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->AmbientReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-t")
                        {
                            t_option* option = new t_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->AmbientReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-texres")
                        {
                            texres_option* option = new texres_option;
                            option->Resolution = attributes[beginIndex + 2].ToInteger(DECIMAL_A);
                            newMaterial->AmbientReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else
                        {
                            break;
                        }
                    }

                    newMaterial->AmbientReflectivity_Texture->Filename = attributes[beginIndex];
                }
                else if (tag == "map_Kd")
                {
                    newMaterial->DiffuseReflectivity_Texture = new DiffuseReflectivity_Texture;

                    int beginIndex = 0;

                    while (true)
                    {
                        if (attributes[beginIndex] == "-blendu")
                        {
                            blendu_option* option = new blendu_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->DiffuseReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendv")
                        {
                            blendv_option* option = new blendv_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->DiffuseReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-cc")
                        {
                            cc_option* option = new cc_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->DiffuseReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-clamp")
                        {
                            clamp_option* option = new clamp_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->DiffuseReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-mm")
                        {
                            mm_option* option = new mm_option;
                            option->Base = attributes[beginIndex + 1].ToFloat();
                            option->Gain = attributes[beginIndex + 2].ToFloat();
                            newMaterial->DiffuseReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 3;
                        }
                        else if (attributes[beginIndex] == "-o")
                        {
                            o_option* option = new o_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->DiffuseReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-s")
                        {
                            s_option* option = new s_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->DiffuseReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-t")
                        {
                            t_option* option = new t_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->DiffuseReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-texres")
                        {
                            texres_option* option = new texres_option;
                            option->Resolution = attributes[beginIndex + 2].ToInteger(DECIMAL_A);
                            newMaterial->DiffuseReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else
                        {
                            break;
                        }
                    }

                    newMaterial->DiffuseReflectivity_Texture->Filename = attributes[beginIndex];
                }
                else if (tag == "map_Ks")
                {
                    newMaterial->SpecularReflectivity_Texture = new SpecularReflectivity_Texture;

                    int beginIndex = 0;

                    while (true)
                    {
                        if (attributes[beginIndex] == "-blendu")
                        {
                            blendu_option* option = new blendu_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->SpecularReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendv")
                        {
                            blendv_option* option = new blendv_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->SpecularReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-cc")
                        {
                            cc_option* option = new cc_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->SpecularReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-clamp")
                        {
                            clamp_option* option = new clamp_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->SpecularReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-mm")
                        {
                            mm_option* option = new mm_option;
                            option->Base = attributes[beginIndex + 1].ToFloat();
                            option->Gain = attributes[beginIndex + 2].ToFloat();
                            newMaterial->SpecularReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 3;
                        }
                        else if (attributes[beginIndex] == "-o")
                        {
                            o_option* option = new o_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->SpecularReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-s")
                        {
                            s_option* option = new s_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->SpecularReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-t")
                        {
                            t_option* option = new t_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->SpecularReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-texres")
                        {
                            texres_option* option = new texres_option;
                            option->Resolution = attributes[beginIndex + 2].ToInteger(DECIMAL_A);
                            newMaterial->SpecularReflectivity_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else
                        {
                            break;
                        }
                    }

                    newMaterial->SpecularReflectivity_Texture->Filename = attributes[beginIndex];
                }
                else if (tag == "map_Ns")
                {
                    newMaterial->SpecularExponent_Texture = new SpecularExponent_Texture;

                    int beginIndex = 0;

                    while (true)
                    {
                        if (attributes[beginIndex] == "-blendu")
                        {
                            blendu_option* option = new blendu_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->SpecularExponent_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendv")
                        {
                            blendv_option* option = new blendv_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->SpecularExponent_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-clamp")
                        {
                            clamp_option* option = new clamp_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->SpecularExponent_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-imfchan")
                        {
                            imfchan_option* option = new imfchan_option;
                            option->R = attributes[beginIndex + 1].ToFloat();
                            option->G = attributes[beginIndex + 2].ToFloat();
                            option->B = attributes[beginIndex + 3].ToFloat();
                            option->M = attributes[beginIndex + 4].ToFloat();
                            option->L = attributes[beginIndex + 5].ToFloat();
                            option->Z = attributes[beginIndex + 6].ToFloat();
                            newMaterial->SpecularExponent_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 7;
                        }
                        else if (attributes[beginIndex] == "-mm")
                        {
                            mm_option* option = new mm_option;
                            option->Base = attributes[beginIndex + 1].ToFloat();
                            option->Gain = attributes[beginIndex + 2].ToFloat();
                            newMaterial->SpecularExponent_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 3;
                        }
                        else if (attributes[beginIndex] == "-o")
                        {
                            o_option* option = new o_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->SpecularExponent_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-s")
                        {
                            s_option* option = new s_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->SpecularExponent_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-t")
                        {
                            t_option* option = new t_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->SpecularExponent_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-texres")
                        {
                            texres_option* option = new texres_option;
                            option->Resolution = attributes[beginIndex + 2].ToInteger(DECIMAL_A);
                            newMaterial->SpecularExponent_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else
                        {
                            break;
                        }
                    }

                    newMaterial->SpecularExponent_Texture->Filename = attributes[beginIndex];
                }
                else if (tag == 'd')
                {
                    newMaterial->DissolveFactor_Texture = new DissolveFactor_Texture;

                    int beginIndex = 0;

                    while (true)
                    {
                        if (attributes[beginIndex] == "-blendu")
                        {
                            blendu_option* option = new blendu_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->DissolveFactor_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendv")
                        {
                            blendv_option* option = new blendv_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->DissolveFactor_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-clamp")
                        {
                            clamp_option* option = new clamp_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->DissolveFactor_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-imfchan")
                        {
                            imfchan_option* option = new imfchan_option;
                            option->R = attributes[beginIndex + 1].ToFloat();
                            option->G = attributes[beginIndex + 2].ToFloat();
                            option->B = attributes[beginIndex + 3].ToFloat();
                            option->M = attributes[beginIndex + 4].ToFloat();
                            option->L = attributes[beginIndex + 5].ToFloat();
                            option->Z = attributes[beginIndex + 6].ToFloat();
                            newMaterial->DissolveFactor_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 7;
                        }
                        else if (attributes[beginIndex] == "-mm")
                        {
                            mm_option* option = new mm_option;
                            option->Base = attributes[beginIndex + 1].ToFloat();
                            option->Gain = attributes[beginIndex + 2].ToFloat();
                            newMaterial->DissolveFactor_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 3;
                        }
                        else if (attributes[beginIndex] == "-o")
                        {
                            o_option* option = new o_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->DissolveFactor_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-s")
                        {
                            s_option* option = new s_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->DissolveFactor_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-t")
                        {
                            t_option* option = new t_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->DissolveFactor_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-texres")
                        {
                            texres_option* option = new texres_option;
                            option->Resolution = attributes[beginIndex + 2].ToInteger(DECIMAL_A);
                            newMaterial->DissolveFactor_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else
                        {
                            break;
                        }
                    }

                    newMaterial->DissolveFactor_Texture->Filename = attributes[beginIndex];
                }
                else if (tag == "map_aat")
                {
                    newMaterial->AntiAliasing = attributes[1] == "on";
                }
                else if (tag == "decal")
                {
                    newMaterial->Decal_Texture = new Decal_Texture;

                    int beginIndex = 0;

                    while (true)
                    {
                        if (attributes[beginIndex] == "-blendu")
                        {
                            blendu_option* option = new blendu_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->Decal_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendv")
                        {
                            blendv_option* option = new blendv_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->Decal_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-clamp")
                        {
                            clamp_option* option = new clamp_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->Decal_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-imfchan")
                        {
                            imfchan_option* option = new imfchan_option;
                            option->R = attributes[beginIndex + 1].ToFloat();
                            option->G = attributes[beginIndex + 2].ToFloat();
                            option->B = attributes[beginIndex + 3].ToFloat();
                            option->M = attributes[beginIndex + 4].ToFloat();
                            option->L = attributes[beginIndex + 5].ToFloat();
                            option->Z = attributes[beginIndex + 6].ToFloat();
                            newMaterial->Decal_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 7;
                        }
                        else if (attributes[beginIndex] == "-mm")
                        {
                            mm_option* option = new mm_option;
                            option->Base = attributes[beginIndex + 1].ToFloat();
                            option->Gain = attributes[beginIndex + 2].ToFloat();
                            newMaterial->Decal_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 3;
                        }
                        else if (attributes[beginIndex] == "-o")
                        {
                            o_option* option = new o_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Decal_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-s")
                        {
                            s_option* option = new s_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Decal_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-t")
                        {
                            t_option* option = new t_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Decal_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-texres")
                        {
                            texres_option* option = new texres_option;
                            option->Resolution = attributes[beginIndex + 2].ToInteger(DECIMAL_A);
                            newMaterial->Decal_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else
                        {
                            break;
                        }
                    }

                    newMaterial->Decal_Texture->Filename = attributes[beginIndex];
                }
                else if (tag == "disp")
                {
                    newMaterial->Displacement_Texture = new Displacement_Texture;

                    int beginIndex = 0;

                    while (true)
                    {
                        if (attributes[beginIndex] == "-blendu")
                        {
                            blendu_option* option = new blendu_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->Displacement_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendv")
                        {
                            blendv_option* option = new blendv_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->Displacement_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-clamp")
                        {
                            clamp_option* option = new clamp_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->Displacement_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-imfchan")
                        {
                            imfchan_option* option = new imfchan_option;
                            option->R = attributes[beginIndex + 1].ToFloat();
                            option->G = attributes[beginIndex + 2].ToFloat();
                            option->B = attributes[beginIndex + 3].ToFloat();
                            option->M = attributes[beginIndex + 4].ToFloat();
                            option->L = attributes[beginIndex + 5].ToFloat();
                            option->Z = attributes[beginIndex + 6].ToFloat();
                            newMaterial->Displacement_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 7;
                        }
                        else if (attributes[beginIndex] == "-mm")
                        {
                            mm_option* option = new mm_option;
                            option->Base = attributes[beginIndex + 1].ToFloat();
                            option->Gain = attributes[beginIndex + 2].ToFloat();
                            newMaterial->Displacement_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 3;
                        }
                        else if (attributes[beginIndex] == "-o")
                        {
                            o_option* option = new o_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Displacement_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-s")
                        {
                            s_option* option = new s_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Displacement_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-t")
                        {
                            t_option* option = new t_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Displacement_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-texres")
                        {
                            texres_option* option = new texres_option;
                            option->Resolution = attributes[beginIndex + 2].ToInteger(DECIMAL_A);
                            newMaterial->Displacement_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else
                        {
                            break;
                        }
                    }

                    newMaterial->Displacement_Texture->Filename = attributes[beginIndex];
                }
                else if (tag == "bump")
                {
                    newMaterial->Bump_Texture = new Bump_Texture;

                    int beginIndex = 0;

                    while (true)
                    {
                        if (attributes[beginIndex] == "-bm")
                        {
                            bm_option* option = new bm_option;
                            option->Multiplier = attributes[beginIndex + 1].ToFloat();
                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendu")
                        {
                            blendu_option* option = new blendu_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendv")
                        {
                            blendv_option* option = new blendv_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-clamp")
                        {
                            clamp_option* option = new clamp_option;
                            option->Value = attributes[beginIndex + 1] == "on";
                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-imfchan")
                        {
                            imfchan_option* option = new imfchan_option;
                            option->R = attributes[beginIndex + 1].ToFloat();
                            option->G = attributes[beginIndex + 2].ToFloat();
                            option->B = attributes[beginIndex + 3].ToFloat();
                            option->M = attributes[beginIndex + 4].ToFloat();
                            option->L = attributes[beginIndex + 5].ToFloat();
                            option->Z = attributes[beginIndex + 6].ToFloat();
                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 7;
                        }
                        else if (attributes[beginIndex] == "-mm")
                        {
                            mm_option* option = new mm_option;
                            option->Base = attributes[beginIndex + 1].ToFloat();
                            option->Gain = attributes[beginIndex + 2].ToFloat();
                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 3;
                        }
                        else if (attributes[beginIndex] == "-o")
                        {
                            o_option* option = new o_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-s")
                        {
                            s_option* option = new s_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-t")
                        {
                            t_option* option = new t_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-texres")
                        {
                            texres_option* option = new texres_option;
                            option->Resolution = attributes[beginIndex + 2].ToInteger(DECIMAL_A);
                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                            beginIndex += 2;
                        }
                        else
                        {
                            break;
                        }
                    }

                    newMaterial->Bump_Texture->Filename = attributes[beginIndex];
                }
                else if(tag == "refl")
                {
                    newMaterial->ReflectionMap = new ReflectionMap;

                    if (attributes[2] == "sphere")
                    {
                        newMaterial->ReflectionMap->Type = ReflectionMapType::SPHERE;
                    }
                    else if (attributes[2] == "cube_top")
                    {
                        newMaterial->ReflectionMap->Type = ReflectionMapType::CUBE_TOP;
                    }
                    else if (attributes[2] == "cube_bottom")
                    {
                        newMaterial->ReflectionMap->Type = ReflectionMapType::CUBE_BOTTOM;
                    }
                    else if (attributes[2] == "cube_front")
                    {
                        newMaterial->ReflectionMap->Type = ReflectionMapType::CUBE_FRONT;
                    }
                    else if (attributes[2] == "cube_back")
                    {
                        newMaterial->ReflectionMap->Type = ReflectionMapType::CUBE_BACK;
                    }
                    else if (attributes[2] == "cube_left")
                    {
                        newMaterial->ReflectionMap->Type = ReflectionMapType::CUBE_LEFT;
                    }
                    else if (attributes[2] == "cube_right")
                    {
                        newMaterial->ReflectionMap->Type = ReflectionMapType::CUBE_RIGHT;
                    }

                    //OPTIONS

                    int beginIndex = 0;

                    //until parameter 'filename' is reached
                    while (true)
                    {
                        //if parameter 'filename' is reached
                        if (!attributes[beginIndex].BeginsWith('-'))
                        {
                            break;
                        }

                        //(STATE) beginIndex is the beginning of an option (i.e. parameter 'filename' is not reached yet)

                        char* option;

                        if (attributes[beginIndex] == "-blendu")
                        {
                            option = new char[2];
                            option[0] = BLENDU_OPTION;
                            option[1] = attributes[beginIndex + 1] == "on";
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-blendv")
                        {
                            option = new char[2];
                            option[0] = BLENDV_OPTION;
                            option[1] = attributes[beginIndex + 1] == "on";
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-cc")
                        {
                            option = new char[2];
                            option[0] = CC_OPTION;
                            option[1] = attributes[beginIndex + 1] == "on";
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-clamp")
                        {
                            option = new char[2];
                            option[0] = CLAMP_OPTION;
                            option[1] = attributes[0] == "on";
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-mm")
                        {
                            option = new char[10];
                            option[0] = MM_OPTION;
                            *(reinterpret_cast<float*>(option[2])) = attributes[beginIndex + 1].ToFloat();
                            *(reinterpret_cast<float*>(option[6])) = attributes[beginIndex + 2].ToFloat();
                            beginIndex += 2;
                        }
                        else if (attributes[beginIndex] == "-o")
                        {
                            o_option* option = new o_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-s")
                        {
                            s_option* option = new s_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-t")
                        {
                            t_option* option = new t_option;

                            option->U =  attributes[beginIndex + 1].ToFloat();;

                            //if there are 'v' and 'w' fields
                            if (attributes[beginIndex + 2].IsInteger() || attributes[beginIndex + 2].IsFractional(true))
                            {
                                option->V = attributes[beginIndex + 2].ToFloat();
                                option->W = attributes[beginIndex + 3].ToFloat();
                                beginIndex += 4;
                            }
                            else
                            {
                                beginIndex += 2;
                            }

                            newMaterial->Bump_Texture->Options.Append(reinterpret_cast<B_Option*>(option));
                        }
                        else if (attributes[beginIndex] == "-texres")
                        {
                            option = new char[6];
                            option[0] = TEXRES_OPTION;
                            *(reinterpret_cast<float*>(option[2])) = attributes[beginIndex + 1].ToFloat();
                            beginIndex += 2;
                        }
                        else
                        {
                            break;
                        }

                        newMaterial->ReflectionMap->Options.Append(option);
                    }

                    newMaterial->Bump_Texture->Filename = attributes[beginIndex];
                }

                lineBegin = i + 1; //(A)
            }
        }

        delete [] data;

        materials.Close();

        return 0;
    }

    void Release(list<Material>& _materials)
    {
        for (Material& __material : _materials)
        {
            if (__material.AmbientReflectivity_Color != nullptr)
            {
                delete __material.AmbientReflectivity_Color;
            }
            else if (__material.DiffuseReflectivity_Color != nullptr)
            {
                delete __material.DiffuseReflectivity_Color;
            }
            else if (__material.SpecularReflectivity_Color != nullptr)
            {
                delete __material.SpecularReflectivity_Color;
            }
            else if (__material.TransmissionFilter != nullptr)
            {
                delete __material.TransmissionFilter;
            }
            else if (__material.AmbientReflectivity_Texture != nullptr)
            {
                delete __material.AmbientReflectivity_Texture;
            }
            else if (__material.DiffuseReflectivity_Texture != nullptr)
            {
                delete __material.DiffuseReflectivity_Texture;
            }
            else if (__material.SpecularReflectivity_Texture != nullptr)
            {
                delete __material.SpecularReflectivity_Texture;
            }
            else if (__material.DissolveFactor_Texture != nullptr)
            {
                delete __material.DissolveFactor_Texture;
            }
            else if (__material.SpecularExponent_Texture != nullptr)
            {
                delete __material.SpecularExponent_Texture;
            }
            else if (__material.Decal_Texture != nullptr)
            {
                delete __material.Decal_Texture;
            }
            else if (__material.Bump_Texture != nullptr)
            {
                delete __material.Bump_Texture;
            }
            else if (__material.Displacement_Texture != nullptr)
            {
                delete __material.Displacement_Texture;
            }
        }
    }
}

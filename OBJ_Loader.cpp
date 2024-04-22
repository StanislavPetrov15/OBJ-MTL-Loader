/* TASKS:

    polygonal geometry:
    + елемент 'l'
    + елемент 'f'
    + елемент 'v'
    + елемент 'vt'
    + елемент 'vn'
    + елемент 'g'
    + елемент 's'
    + елемент 'o'

    free-form geometry (curves/surfaces):
    * елемент 'cstype'
    * елемент 'p'
    * елемент 'vp'
    * елемент 'parm'
    * елемент 'trim'
    * елемент 'hole'
    * елемент 'scrv'
    * елемент 'sp'
    * елемент 'end'
    * елемент 'con'
    * елемент 'deg'
    * елемент 'step'
    * елемент 'curv'
    * елемент 'curv2'
    * елемент 'surf'
    * елемент 'ctech'
    * елемент 'stech'
    * елемент 'mg'

    display/render attributes:
    * елемент 'bevel'
    * елемент 'c_interp'
    * елемент 'd_interp'
    * елемент 'lod'
    + елемент 'usemtl'
    * елемент 'usemap'
    + елемент 'mtllib'
    * елемент 'maplib'
    * елемент 'shadow_obj'
    * елемент 'trace_obj'

    (TO-FIX) (A) it's possible that the different 3D modelling programs use different byte sequence to specify a new line;
               for example Blender uses '\n'; it is also possible that few different new-line sequences are used;
               Parse_MTL() must support different new-line sequences

    (TO-FIX) line-spanning (by using '\' at the end of the line) is not supported */




//(PUBLIC)

using MTL_Loader::Material;

namespace OBJ_Loader
{
    struct GeometricVertex
    {
         float X;
         float Y;
         float Z;
         float W = 1.0;
         Material* Material;
         string* Group;
         string* Object;
    };

    struct TextureVertex
    {
        float U;
        float V = 0.0;
        float W = 0.0;
        string* Group;
        string* Object;
    };

    struct VertexNormal
    {
         float I;
         float J;
         float K;
         string* Group;
         string* Object;
    };

    struct FaceVertexData
    {
         int GeometricVertexIndex;
         int TextureVertexIndex = INT_MIN; //optional attribute
         int VertexNormalIndex = INT_MIN; //optional attribute
         string* Group;
         string* Object;
    };

    struct Face
    {
        int SmoothingGroup;
        list<FaceVertexData> VertexData;
        Material* Material;
        string* Group;
        string* Object;
    };

    /*struct FreeFormGeometry
    {
        float U;
        float V;
        float W;
    };

    struct Degree
    {

    };

    enum class CurveSurfaceType
    {
        BasisMatrix,
        Bezier,
        B_Spline,
        Cardinal,
        Taylor
    };

    struct CurveSurface
    {
        bool RationalForm;
        CurveSurfaceType CurveSurfaceType;
    };

    //element 'bmat'
    struct BasisMatrix
    {

    };

    struct Step
    {
        float U;
        float V;
    };*/

    struct OBJ_Model
    {
        list<string> Groups;
        list<string> Objects;
        list<Material> Materials;
        list<GeometricVertex> GeometricVertices;
        list<TextureVertex> TextureVertices;
        list<VertexNormal> VertexNormals;
        list<Face> Faces;
    };

    //(MUTATES _model)
    //the size of the file is too big => -1
    //successful execution => 0
    /* the file specified by _filepath exists and is syntactically and semantically valid (this function does not perform any
        syntactic or semantic validation) -> */
    int Parse_OBJ(const string& _filepath, OBJ_Model& _model)
    {
        filesystem::File file(_filepath);

        int filesize = file.size();

        char* data;

        try
        {
            data = new char[filesize];
        }
        catch (const std::bad_alloc& e)
        {
            return -1;
        }

        file.ReadBlock(reinterpret_cast<unsigned char*>(data), filesize, false);

        //reading the lines (elements)

        int lineBegin = 0;

        int currentSmoothingGroup = 0;
        _model.Groups.Append("_default_group_");
        _model.Objects.Append("_default_object_");

        string currentMaterialName;

        //(PERFORMANCE-REASONS)
        _model.GeometricVertices.resize(100000);
        _model.TextureVertices.resize(100000);
        _model.VertexNormals.resize(100000);
        _model.Faces.resize(100000);
        _model.GeometricVertices.ExtensionValue = 100;
        _model.TextureVertices.ExtensionValue = 100;
        _model.VertexNormals.ExtensionValue = 100;
        _model.Faces.ExtensionValue = 100;

        string line;
        line.ReleaseMode = ReleaseMode::FUTURE;
        line.StorageEncoding = UTF8;

        for (int i = 0; i < filesize; i++)
        {
              char currentByte = data[i];

              //if this is a new-line character
              if (currentByte == '\n' || currentByte == '\r')
              {
                  //traversing the elements of the current line

                  int lineLength = i - lineBegin;

                  //if the current line is empty (line with length 0, not just filled with empty spaces)
                  if (lineLength == 0)
                  {
                       lineBegin++;
                       continue;
                  }

                  //(STATE) the current line is not empty

                  line.Elements = reinterpret_cast<unsigned char*>(&data[lineBegin]);
                  line.Size = lineLength;
                  line.ByteCount = lineLength;
                  line.CharacterCount = lineLength;

                  lineBegin = i + 1;

                  //ignore the current line if the line is a comment
                  if (line.Elements[0] == '#')
                  {
                      continue;
                  }

                  //(STATE) the current line is not a comment

                 int* elements = split<unsigned char>(line.Elements, line.CharacterCount, ' ', true);

                 int elementsCount = elements[0];

                  string tag(&(line.Elements[elements[1]]), u8, (unsigned int) (elements[2] - elements[1]) + 1);

                  //(PERFORMANCE-CONSTANTS)
                  static const string v_element = 'v';
                  static const string vn_element = "vn";
                  static const string vt_element = "vt";
                  static const string f_element = 'f';
                  static const string g_element = 'g';
                  static const string o_element = 'o';
                  static const string s_element = 's';
                  static const string vp_element = "vp";
                  static const string p_element = 'p';
                  static const string l_element = 'l';
                  static const string curv_element = "curv";
                  static const string curv2_element = "curv2";
                  static const string surf_element = "surf";
                  static const string deg_element = "deg";
                  static const string step_element = "step";
                  static const string bmat_element = "bmat";
                  static const string gm_element = "gm";
                  static const string parm_element = "parm";
                  static const string trim_element = "trim";
                  static const string hole_element = "hole";
                  static const string scr_element = "scr";
                  static const string sp_element = "sp";
                  static const string end_element = "end";
                  static const string con_element = "con";
                  static const string bevel_element = "bevel";
                  static const string c_interp_element = "c_interp";
                  static const string d_interp_element = "d_interp";
                  static const string lod_element = "lod_element";
                  static const string usemtl_element = "usemtl";
                  static const string mtllib_element = "mtllib";
                  static const string maplib_element = "maplib";
                  static const string usemap_element = "usemap";
                  static const string shadow_obj_element = "shadow_obj";
                  static const string trace_obj_element = "trace_obj";
                  static const string c_tech_element = "c_tech";
                  static const string s_tech_element = "s_tech";

                  if (tag == v_element)
                  {
                      GeometricVertex vertex;
                      vertex.Group = &(_model.Groups.last());
                      vertex.Object = &(_model.Objects.last());

                      string attribute_0;
                      attribute_0.StorageEncoding = UTF8;
                      attribute_0.Size = static_cast<unsigned int>((elements[4] - elements[3]) + 1);
                      attribute_0.ByteCount = attribute_0.Size;
                      attribute_0.CharacterCount = attribute_0.Size;
                      attribute_0.Elements = &(line.Elements[elements[3]]);
                      attribute_0.ReleaseMode = ReleaseMode::FUTURE;

                      string attribute_1;
                      attribute_1.StorageEncoding = UTF8;
                      attribute_1.Size = static_cast<unsigned int>((elements[6] - elements[5]) + 1);
                      attribute_1.ByteCount = attribute_1.Size;
                      attribute_1.CharacterCount = attribute_1.Size;
                      attribute_1.Elements = &(line.Elements[elements[5]]);
                      attribute_1.ReleaseMode = ReleaseMode::FUTURE;

                      string attribute_2;
                      attribute_2.StorageEncoding = UTF8;
                      attribute_2.Size = static_cast<unsigned int>((elements[8] - elements[7]) + 1);
                      attribute_2.ByteCount = attribute_2.Size;
                      attribute_2.CharacterCount = attribute_2.Size;
                      attribute_2.Elements = &(line.Elements[elements[7]]);
                      attribute_2.ReleaseMode = ReleaseMode::FUTURE;

                      vertex.X = attribute_0.ToFloat();
                      vertex.Y = attribute_1.ToFloat();
                      vertex.Z = attribute_2.ToFloat();

                      //"v float float float float"
                      if (elementsCount == 5)
                      {
                          string attributes_3(&(line.Elements[elements[9]]), u8, (unsigned int) (elements[10] - elements[9]) + 1);
                          vertex.Z = attributes_3.ToFloat();
                      }

                      if (currentMaterialName.characterCount() > 0)
                      {
                          vertex.Material = _model.Materials.First([&currentMaterialName](const Material& x) {
                              return x.Name == currentMaterialName; });
                      }

                      _model.GeometricVertices.Append(vertex);
                  }
                  else if (tag == vn_element)
                  {
                      VertexNormal normal;
                      normal.Group = &(_model.Groups.last());;
                      normal.Object = &(_model.Objects.last());;

                      string attribute_0;
                      attribute_0.StorageEncoding = UTF8;
                      attribute_0.Size = static_cast<unsigned int>((elements[4] - elements[3]) + 1);
                      attribute_0.ByteCount = attribute_0.Size;
                      attribute_0.CharacterCount = attribute_0.Size;
                      attribute_0.Elements = &(line.Elements[elements[3]]);
                      attribute_0.ReleaseMode = ReleaseMode::FUTURE;

                      string attribute_1;
                      attribute_1.StorageEncoding = UTF8;
                      attribute_1.Size = static_cast<unsigned int>((elements[6] - elements[5]) + 1);
                      attribute_1.ByteCount = attribute_1.Size;
                      attribute_1.CharacterCount = attribute_1.Size;
                      attribute_1.Elements = &(line.Elements[elements[5]]);
                      attribute_1.ReleaseMode = ReleaseMode::FUTURE;

                      string attribute_2;
                      attribute_2.StorageEncoding = UTF8;
                      attribute_2.Size = static_cast<unsigned int>((elements[8] - elements[7]) + 1);
                      attribute_2.ByteCount = attribute_2.Size;
                      attribute_2.CharacterCount = attribute_2.Size;
                      attribute_2.Elements = &(line.Elements[elements[7]]);
                      attribute_2.ReleaseMode = ReleaseMode::FUTURE;

                      normal.I = attribute_0.ToFloat();
                      normal.J = attribute_1.ToFloat();
                      normal.K = attribute_2.ToFloat();

                      _model.VertexNormals.Append(normal);
                  }
                  else if (tag == vt_element)
                  {
                     TextureVertex vertex;
                      vertex.Group = &(_model.Groups.last());;
                      vertex.Object = &(_model.Objects.last());;

                      string attribute_0;
                      attribute_0.StorageEncoding = UTF8;
                      attribute_0.Size = static_cast<unsigned int>((elements[4] - elements[3]) + 1);
                      attribute_0.ByteCount = attribute_0.Size;
                      attribute_0.CharacterCount = attribute_0.Size;
                      attribute_0.Elements = &(line.Elements[elements[3]]);
                      attribute_0.ReleaseMode = ReleaseMode::FUTURE;

                      vertex.U = attribute_0.ToFloat();

                      if (elementsCount > 2)
                      {
                          string attribute_1;
                          attribute_1.StorageEncoding = UTF8;
                          attribute_1.Size = static_cast<unsigned int>((elements[6] - elements[5]) + 1);
                          attribute_1.ByteCount = attribute_1.Size;
                          attribute_1.CharacterCount = attribute_1.Size;
                          attribute_1.Elements = &(line.Elements[elements[5]]);
                          attribute_1.ReleaseMode = ReleaseMode::FUTURE;
                          vertex.V = attribute_1.ToFloat();
                      }

                      if (elementsCount > 3)
                      {
                          string attribute_2;
                          attribute_2.StorageEncoding = UTF8;
                          attribute_2.Size = (elements[8] - elements[7]) + 1;
                          attribute_2.ByteCount = attribute_2.Size;
                          attribute_2.CharacterCount = attribute_2.Size;
                          attribute_2.Elements = &(line.Elements[elements[7]]);
                          attribute_2.ReleaseMode = ReleaseMode::FUTURE;
                          vertex.W = attribute_2.ToFloat();
                      }

                      _model.TextureVertices.Append(vertex);
                  }
                  else if (tag == vp_element)
                  {
                      //
                  }
                  else if (tag == p_element)
                  {
                      //
                  }
                  else if (tag == l_element)
                  {
                      //
                  }
                  else if (tag == f_element)
                  {
                      Face face;

                      face.SmoothingGroup = currentSmoothingGroup;

                      //for every attribute (vertex data)
                      for (int i = 3; i < (elementsCount * 2) + 1; i += 2)
                      {
                          string attribute;
                          attribute.StorageEncoding = UTF8;
                          attribute.Size = static_cast<unsigned int>((elements[i + 1] - elements[i]) + 1);
                          attribute.ByteCount = attribute.Size;
                          attribute.CharacterCount = attribute.Size;
                          attribute.Elements = &(line.Elements[elements[i]]);
                          attribute.ReleaseMode = ReleaseMode::FUTURE;
                          int* vertexDataElements = split<unsigned char>(attribute.Elements, attribute.CharacterCount, '/', true);
                          int vertexDataElementsCount = vertexDataElements[0];

                          string vertexDataElement_0;
                          vertexDataElement_0.StorageEncoding = UTF8;
                          vertexDataElement_0.Size = static_cast<unsigned int>((vertexDataElements[2] - vertexDataElements[1]) + 1);
                          vertexDataElement_0.ByteCount = vertexDataElement_0.Size;
                          vertexDataElement_0.CharacterCount = vertexDataElement_0.Size;
                          vertexDataElement_0.Elements = &(attribute.Elements[vertexDataElements[1]]);
                          vertexDataElement_0.ReleaseMode = ReleaseMode::FUTURE;
                          FaceVertexData vertexData;
                          vertexData.Group = &(_model.Groups.last());
                          vertexData.Object = &(_model.Objects.last());

                          if (vertexDataElementsCount == 0)
                          {
                              vertexData.GeometricVertexIndex = attribute.ToInteger(DECIMAL_A);
                          }
                          else
                          {
                              vertexData.GeometricVertexIndex = vertexDataElement_0.ToInteger(DECIMAL_A);
                          }

                          //if there are two elements, the the second element specifies the vertex normal
                          if (vertexDataElementsCount == 2)
                          {
                              string vertexDataElement_1;
                              vertexDataElement_1.StorageEncoding = UTF8;
                              vertexDataElement_1.Size = static_cast<unsigned int>((vertexDataElements[4] - vertexDataElements[3]) + 1);
                              vertexDataElement_1.ByteCount = vertexDataElement_1.Size;
                              vertexDataElement_1.CharacterCount = vertexDataElement_1.Size;
                              vertexDataElement_1.Elements = &(attribute.Elements[vertexDataElements[3]]);
                              vertexDataElement_1.ReleaseMode = ReleaseMode::FUTURE;
                              vertexData.TextureVertexIndex = vertexDataElement_1.ToInteger(DECIMAL_A);
                          }
                          //(STATE) the attribute has three elements (but the second may be empty)
                          else if (vertexDataElementsCount == 3)
                          {
                              string vertexDataElement_1;
                              vertexDataElement_1.StorageEncoding = UTF8;
                              vertexDataElement_1.Size = static_cast<unsigned int>((vertexDataElements[4] - vertexDataElements[3]) + 1);
                              vertexDataElement_1.ByteCount = vertexDataElement_1.Size;
                              vertexDataElement_1.CharacterCount = vertexDataElement_1.Size;
                              vertexDataElement_1.Elements = &(attribute.Elements[vertexDataElements[3]]);
                              vertexDataElement_1.ReleaseMode = ReleaseMode::FUTURE;

                              string vertexDataElement_2;
                              vertexDataElement_2.StorageEncoding = UTF8;
                              vertexDataElement_2.Size = static_cast<unsigned int>((vertexDataElements[6] - vertexDataElements[5]) + 1);
                              vertexDataElement_2.ByteCount = vertexDataElement_2.Size;
                              vertexDataElement_2.CharacterCount = vertexDataElement_2.Size;
                              vertexDataElement_2.Elements = &(attribute.Elements[vertexDataElements[5]]);
                              vertexDataElement_2.ReleaseMode = ReleaseMode::FUTURE;

                              //if the element contains texture coordinates
                              if (vertexDataElement_1 != "")
                              {
                                  vertexData.TextureVertexIndex = vertexDataElement_1.ToInteger(DECIMAL_A);
                              }

                              //the vertex normal is always the third element
                              vertexData.VertexNormalIndex = vertexDataElement_2.ToInteger(DECIMAL_A);
                          }

                          face.VertexData.Append(vertexData);
                      }

                      if (currentMaterialName.characterCount() > 0)
                      {
                          face.Material = _model.Materials.First([&currentMaterialName](const Material& x) {
                              return x.Name == currentMaterialName; });
                      }

                      _model.Faces.Append(face);
                  }
                  else if (tag == curv_element)
                  {
                      //
                  }
                  else if (tag == curv2_element)
                  {
                      //
                  }
                  else if (tag == surf_element)
                  {
                      //
                  }
                  else if (tag == deg_element)
                  {
                      //
                  }
                  else if (tag == step_element)
                  {
                      //
                  }
                  else if (tag == bmat_element)
                  {
                      //
                  }
                  //(SEGMENT) GROUPING
                  else if (tag == g_element)
                  {
                      _model.Groups.Append(line.Sublist(line.IndexOf(' ') + 1).Trim(' '));
                  }
                  else if (tag == s_element)
                  {
                      string attribute;
                      attribute.StorageEncoding = UTF8;
                      attribute.Size = static_cast<unsigned int>((elements[4] - elements[3]) + 1);
                      attribute.ByteCount = attribute.Size;
                      attribute.CharacterCount = attribute.Size;
                      attribute.Elements = &(line.Elements[elements[3]]);
                      attribute.ReleaseMode = ReleaseMode::FUTURE;

                      if (attribute == "off")
                      {
                           currentSmoothingGroup = 0;
                      }
                      else
                      {
                           currentSmoothingGroup = attribute.ToInteger(DECIMAL_A);
                      }
                  }
                  else if (tag == o_element)
                  {
                      _model.Objects.Append(line.Sublist(line.IndexOf(' ') + 1).Trim(' '));
                  }
                  else if (tag == gm_element)
                  {
                      //
                  }
                  //(SEGMENT) FREE-FORM CURVES/SURFACES
                  else if (tag == parm_element)
                  {
                      //
                  }
                  else if (tag == trim_element)
                  {
                      //
                  }
                  else if (tag == hole_element)
                  {
                      //
                  }
                  else if (tag == scr_element)
                  {
                      //
                  }
                  else if (tag == sp_element)
                  {
                      //
                  }
                  else if (tag == end_element)
                  {
                      //
                  }
                  else if (tag == con_element)
                  {
                      //
                  }
                  //(SEGMENT) DISPLAY/RENDER ATTRIBUTES
                  else if (tag == bevel_element)
                  {
                      //
                  }
                  else if (tag == c_interp_element)
                  {
                      //
                  }
                  else if (tag == d_interp_element)
                  {
                      //
                  }
                  else if (tag == lod_element)
                  {
                      //
                  }
                  else if (tag == usemtl_element)
                  {
                      string attribute;
                      attribute.StorageEncoding = UTF8;
                      attribute.Size = static_cast<unsigned int>((elements[4] - elements[3]) + 1);
                      attribute.ByteCount = attribute.Size;
                      attribute.CharacterCount = attribute.Size;
                      attribute.Elements = &(line.Elements[elements[3]]);
                      attribute.ReleaseMode = ReleaseMode::FUTURE;
                      currentMaterialName = attribute;
                  }
                  else if (tag == mtllib_element)
                  {
                    //for every .mtl file
                    for (int i = 3; i < (elementsCount * 2) + 1; i += 2)
                    {
                        string attribute;
                        attribute.StorageEncoding = UTF8;
                        attribute.Size = static_cast<unsigned int>((elements[i + 1] - elements[i]) + 1);
                        attribute.ByteCount = attribute.Size;
                        attribute.CharacterCount = attribute.Size;
                        attribute.Elements = &(line.Elements[elements[i]]);
                        attribute.ReleaseMode = ReleaseMode::FUTURE;

                         list<Material> materials;

                         //extracting the materials from the current .mtl file
                          Parse_MTL(filesystem::ParentDirectoryOf(_filepath) + "\\" + attribute, materials);

                          _model.Materials.Append(materials);
                    }
                  }
                  else if (tag == maplib_element)
                  {
                      //
                  }
                  else if (tag == usemap_element)
                  {
                      //
                  }
                  else if (tag == shadow_obj_element)
                  {
                      //
                  }
                  else if (tag == trace_obj_element)
                  {
                      //
                  }
                  else if (tag == c_tech_element)
                  {
                      //
                  }
                  else if (tag == s_tech_element)
                  {
                      //
                  }
             }
        }

        delete [] data;

        file.Close();

        return 0;
    }
}

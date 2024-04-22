USAGE 
 
list<Material> materials;
int result = MTL_Loader::Parse_MTL(<filename>, materials);
MTL_Loader::Release(materials);

OBJ_Model model;
int result = Parse_OBJ(<filename>, model);

This project uses the f-code library (in my other repository).

USAGE <br />
 
list<Material> materials; <br />
int result = MTL_Loader::Parse_MTL(<filename>, materials); <br />
MTL_Loader::Release(materials); <br />

OBJ_Model model; <br />
int result = Parse_OBJ(<filename>, model); <br />

This project uses the f-code library (in my other repository).

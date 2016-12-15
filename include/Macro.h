
#ifndef MACRO_H
#define MACRO_H

#define SAFE_DELETE(x) do { if (x) { delete (x); (x) = NULL; }}  while (0)
#define SAFE_DELETE_ARRAY(x)  do { if (x) { delete[] (x); (x) = NULL; }} while (0)

#define UNUSED(x) (void)(x)

#define BXDF_OVERRIDE override
#define LIGHTS_OVERRIDE override

#endif //MACRO_H
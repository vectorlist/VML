
#ifndef CONFIG_H
#define CONFIG_H

#include <qdebug.h>
#include <memory>
#include <color.h>
#include <performance.h>

#define RENDER_SIZE			512

#define CONFIG_SAMPLE			4
#define CONFIG_GI_SAMPLE		12
#define CONFIG_GI_BOUNDS		2

#define CONFIG_NUM_THREADS		8
#define CONFIG_NUM_TASKS_DEVIDES	8

//DEBUG BXDF
#define CONFIG_LIGHT_SAMPLE		true
#define CONFIG_BSDF_SAMPLE		true


#define CONFIG_LIGHT_SAMPLE_HINT 2
#define CONFIG_BOUND	1
//#define CONFIG_LIGHT_SAMPLE_NUM 1

#define CONFIG_ENVIRON		Color(0.7, 0.8, 0.9)

#define CONFIG_PROCESS_DEBUG	true

//#define CONFIG_SCENE
#define CONFIG_TEMP_TEST


#define CONFIG_ENABLE_LIGHT_BRDF
//#define CONFIG_ENABLE_SAMPLE_BRDF


	/*NAME SPACE*/

#define MESH_NAMESPACE_BEGIN namespace MeshUtils{
#define MESH_NAMESPACE_END	}

#define SCENEUTILS_NAMESPACE_BEGIN namespace SceneUtils{
#define SCENEUTILS_NAMESPACE_END	}


	/*IMAGE*/

#define CONFIG_OUTPUT_DIR	"./output/"

#endif //CONFIG_H
